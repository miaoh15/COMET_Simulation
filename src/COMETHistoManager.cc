#include "COMETHistoManager.hh"

#include "globals.hh"
#include "G4UnitsTable.hh"
#include "G4Track.hh"

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
 }

COMETHistoManager::~COMETHistoManager()
{
}

void COMETHistoManager::Fill(){
  fTestTree->Fill();
}

void COMETHistoManager::SetBranch(string name, vector<double>* pVecD){
  fTestTree->Branch(name.c_str(), pVecD);
}

void COMETHistoManager::SetBranch(string name, vector<int>* pVecI){
  fTestTree->Branch(name.c_str(), pVecI);
}

void COMETHistoManager::SetBranch(string name, vector<string>* pVecS){
  fTestTree->Branch(name.c_str(), pVecS);
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
  Px.clear();
  Py.clear();
  Pz.clear();
  Posx.clear();
  Posy.clear();
  Posz.clear();
}

void COMETHistoManager::SetBranch(){
    fHistoManager->SetBranch("TrackID", &TrackID);
    fHistoManager->SetBranch("ParentID", &ParentID);
    fHistoManager->SetBranch("CreatorProcess", &CreatorProcess);
    fHistoManager->SetBranch("Pdg", &Pdg);
    fHistoManager->SetBranch("Px", &Px);
    fHistoManager->SetBranch("Py", &Py);
    fHistoManager->SetBranch("Pz", &Pz);
    fHistoManager->SetBranch("Posx", &Posx);
    fHistoManager->SetBranch("Posy", &Posy);
    fHistoManager->SetBranch("Posz", &Posz);
}

void COMETHistoManager::Write(){
  fTestRooFile->Write();
}

void COMETHistoManager::Close(){
  fTestRooFile->Close();
}

void COMETHistoManager::SetValuePre(const G4Track* track){
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

  Px.push_back(momentum.getX());
  Py.push_back(momentum.getY());
  Pz.push_back(momentum.getZ());

  const G4ThreeVector position = track->GetVertexPosition();
  Posx.push_back(position.getX());
  Posy.push_back(position.getY());
  Posz.push_back(position.getZ());
}

COMETHistoManager* COMETHistoManager::GetHistoManager(){
  if(!fHistoManager){
    fHistoManager = new COMETHistoManager;
  }
  return fHistoManager;
}