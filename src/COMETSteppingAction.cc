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
    /*const COMETDetectorConstruction* detectorConstruction
      = static_cast<const COMETDetectorConstruction*>
        (G4RunManager::GetRunManager()->GetUserDetectorConstruction());*/
  
  G4int pdg=0;
  G4double momentumX = 0.;
  G4double momentumY = 0.;
  G4double momentumZ = 0.;

  //G4cout<<"The volume name: "<<step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume()->GetName()<<G4endl;

  if(step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume()->GetName()=="target"
  &&step->GetPostStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume()->GetName()=="World"){
    //G4cout<<"Bingo!"<<G4endl;
    G4Track* track = step->GetTrack();
    pdg = track->GetParticleDefinition()->GetPDGEncoding();
    //G4cout<<"The pdg: "<<track->GetParticleDefinition()->GetPDGEncoding()<<G4endl;
    //G4cout<<"The X momentum: "<<(track->GetMomentum()).getX()<<G4endl;
    momentumX = (track->GetMomentum()).getX();
    momentumY = (track->GetMomentum()).getY();
    momentumZ = (track->GetMomentum()).getZ();
    fHistoManager->FillNtuple(pdg, momentumX, momentumY, momentumZ);
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

