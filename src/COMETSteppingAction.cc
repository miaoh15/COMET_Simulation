/// \file COMETSteppingAction.cc
/// \brief Implementation of the COMETSteppingAction class

#include "COMETSteppingAction.hh"
#include "COMETEventAction.hh"
#include "COMETDetectorConstruction.hh"

#include "COMETHistoManager.hh"

#include "G4Step.hh"
#include "G4Track.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"
#include "G4UnitsTable.hh"

#include "TVector3.h"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

COMETSteppingAction::COMETSteppingAction(COMETEventAction* eventAction)
: G4UserSteppingAction(),
  fEventAction(eventAction)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

COMETSteppingAction::~COMETSteppingAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void COMETSteppingAction::UserSteppingAction(const G4Step*)
{
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

