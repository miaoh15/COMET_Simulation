#include "COMETHistoManager.hh"
#include "COMETDetectorConstruction.hh"

#include "globals.hh"
#include "G4UnitsTable.hh"
#include "G4Track.hh"
#include "G4RunManager.hh"

#include <TFile.h>
#include <TTree.h>
#include <TVector3.h>
#include <CLHEP/Units/SystemOfUnits.h>

using namespace std;
using namespace CLHEP;

COMETHistoManager* COMETHistoManager::fHistoManager = 0;

COMETHistoManager::COMETHistoManager()
 {
   fHistoManager = this;
   fParameters = COMETParameters::GetParameters();
 }

COMETHistoManager::~COMETHistoManager()
{
}

void COMETHistoManager::Fill(){
  fTestTree->Fill();
}

void COMETHistoManager::OpenFile(string name){
  fTestRooFile = new TFile(name.c_str(), "RECREATE");
}

void COMETHistoManager::CreateTree(string name){
  fTestTree = new TTree(name.c_str(),"release");
}

void COMETHistoManager::ClearVector(){
  TrackID.clear();
  ParentID.clear();
  CreatorProcess.clear();
  Pdg.clear();
  P.clear();
  Pos.clear();
  detP.clear();
  detPos.clear();

  backward = false;
}

void COMETHistoManager::SetBranch(){
    fHistoManager->SetBranch("TrackID", TrackID);
    fHistoManager->SetBranch("ParentID", ParentID);
    fHistoManager->SetBranch("CreatorProcess", CreatorProcess);
    fHistoManager->SetBranch("Pdg", Pdg);
    fHistoManager->SetBranch("P", P);
    fHistoManager->SetBranch("Pos", Pos);
    fHistoManager->SetBranch("detP", detP);
    fHistoManager->SetBranch("detPos", detPos);
}

void COMETHistoManager::Write(){
  fTestRooFile->Write();
}

void COMETHistoManager::Close(){
  fTestRooFile->Close();
}

void COMETHistoManager::SetValuePre(const G4Track* track){

  const G4ThreeVector position = track->GetVertexPosition();

  TrackID.push_back(track->GetTrackID());
  ParentID.push_back(track->GetParentID());

  if(track->GetTrackID()!=1) CreatorProcess.push_back(track->GetCreatorProcess()->GetProcessName());
  else CreatorProcess.push_back("incident");

  Pdg.push_back(track->GetParticleDefinition()->GetPDGEncoding());

  const G4ThreeVector momentumD = track->GetVertexMomentumDirection();
  G4double m = track->GetDefinition()->GetPDGMass()/GeV;
  const G4double kinEnergy = track->GetVertexKineticEnergy();
  G4double E = kinEnergy/GeV+m;
  G4double R = sqrt(E*E-m*m)/momentumD.getR();
  G4ThreeVector momentum = G4ThreeVector(momentumD.getX()*R, momentumD.getY()*R, momentumD.getZ()*R);
  if(momentum.mag()==0) return;

  P.push_back(FV(momentum.getX(), momentum.getY(), momentum.getZ(), E));

  Pos.push_back(FV(position.getX(), position.getY(), position.getZ(), track->GetGlobalTime()));
}

void COMETHistoManager::SetSDHit(G4Step* step){

  //const COMETDetectorConstruction* detectorConstruction = static_cast<const COMETDetectorConstruction*> (G4RunManager::GetRunManager()->GetUserDetectorConstruction());

  //G4VPhysicalVolume* volume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume(0);

  G4bool Enter = step->IsFirstStepInVolume();

  G4Track* track = step->GetTrack();

  if(fParameters->kill_secondary == true){

    if(track->GetTrackID()==1) {
      step->GetTrack()->SetTrackStatus(fStopAndKill);
      return;
    }
    if(track->GetParticleDefinition()->GetPDGEncoding()!=-2212) {
      step->GetTrack()->SetTrackStatus(fStopAndKill);
      return;
    }
  }
  const G4ThreeVector position_ver = track->GetVertexPosition();
  G4double x = position_ver.x();
  G4double y = position_ver.y();
  G4double z = position_ver.z();
  if(sqrt(x*x+y*y)>fParameters->target_radius || TMath::Abs(z)>fParameters->target_length/2.) return;

  if(Enter){
    const G4ThreeVector momentum = track->GetMomentum();
    if(momentum.mag()==0) return;
    G4double m = track->GetDefinition()->GetPDGMass()/GeV;
    const G4double kinEnergy = track->GetKineticEnergy();
    G4double E = kinEnergy/GeV+m;
    detP.push_back(FV(momentum.getX()/GeV, momentum.getY()/GeV, momentum.getZ()/GeV, E));

    const G4ThreeVector position = track->GetPosition();

    if(momentum.mag()<0.001) {
      G4cout<<"Vertex: "<<position_ver.x()<<","<<position_ver.y()<<","<<position_ver.z()<<G4endl;
      G4cout<<"Mom: "<<momentum.mag()<<G4endl;
    }

    detPos.push_back(FV(position.getX(), position.getY(), position.getZ(), track->GetGlobalTime()/ns));
    if(fParameters->kill_secondary == true){
      step->GetTrack()->SetTrackStatus(fStopAndKill);
    }

    if(position.getZ()<0.) backward = true;
  }
}

COMETHistoManager* COMETHistoManager::GetHistoManager(){
  if(!fHistoManager){
    fHistoManager = new COMETHistoManager;
  }
  return fHistoManager;
}