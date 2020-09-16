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

#include "TVector3.h"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

COMETSteppingAction::COMETSteppingAction(COMETEventAction* eventAction, COMETHistoManager* histo)
: G4UserSteppingAction(),
  fEventAction(eventAction),
  fHistoManager(histo)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

COMETSteppingAction::~COMETSteppingAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void COMETSteppingAction::UserSteppingAction(const G4Step* step)
{
    const COMETDetectorConstruction* detectorConstruction
      = static_cast<const COMETDetectorConstruction*>
        (G4RunManager::GetRunManager()->GetUserDetectorConstruction());
  
  G4int pdg=0;
  TVector3* momentum=NULL;

  if(step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume()->GetName()=="target"
  &&step->GetPostStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume()->GetName()=="world"){
    G4Track* track = step->GetTrack();
    pdg = track->GetParticleDefinition()->GetPDGEncoding();
    momentum->SetX((track->GetMomentum()).getX());
    momentum->SetY((track->GetMomentum()).getY());
    momentum->SetZ((track->GetMomentum()).getZ());
    fHistoManager->FillNtuple(pdg, momentum);
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

