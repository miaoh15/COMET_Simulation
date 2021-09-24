/// \file COMETSteppingAction.cc
/// \brief Implementation of the COMETSteppingAction class

#include "COMETSteppingAction.hh"
#include "COMETDetectorConstruction.hh"
#include "COMETProcessManager.hh"

#include "COMETHistoManager.hh"

#include "G4Step.hh"
#include "G4Track.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"
#include "G4UnitsTable.hh"

#include "TVector3.h"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

COMETSteppingAction::COMETSteppingAction()
: G4UserSteppingAction()
{
  fProcessManager = new COMETProcessManager();
  fParameters = COMETParameters::GetParameters();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

COMETSteppingAction::~COMETSteppingAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void COMETSteppingAction::UserSteppingAction(const G4Step* step)
{
  G4Track* track = step->GetTrack();

  if(fParameters->kill_secondary == true){

    if(step->GetPreStepPoint()->GetPhysicalVolume()->GetName()=="target"&&step->GetPostStepPoint()->GetPhysicalVolume()->GetName()=="World"){
      if(track->GetTrackID()==1){
        tag = 0;
        track->SetTrackStatus(fStopAndKill);
      }
      if(track->GetDefinition()->GetPDGEncoding()==-2212&&track->GetParentID()==1){
        tag = 1;
      }
    }
  }

  fProcessManager->SteppingAction(step);
    /*const COMETDetectorConstruction* detectorConstruction
      = static_cast<const COMETDetectorConstruction*>
        (G4RunManager::GetRunManager()->GetUserDetectorConstruction());*/

  //G4Track* track = step->GetTrack();

  /*if(step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume()->GetName()=="target"
  &&step->GetPostStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume()->GetName()=="World"){
    pdg = track->GetParticleDefinition()->GetPDGEncoding();
    trackID = track->GetTrackID();
    momentumX = (track->GetMomentum()).getX();
    momentumY = (track->GetMomentum()).getY();
    momentumZ = (track->GetMomentum()).getZ();
  }*/
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

