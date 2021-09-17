/// \file COMETEventAction.cc
/// \brief Implementation of the COMETEventAction class

#include "COMETEventAction.hh"
#include "COMETRunAction.hh"
#include "COMETSteppingAction.hh"
#include "COMETHistoManager.hh"
#include "COMETProcessManager.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

COMETEventAction::COMETEventAction(COMETRunAction* runAction, COMETSteppingAction* steppingAction)
: G4UserEventAction(),
  fRunAction(runAction),
  fSteppingAction(steppingAction)
{
    fProcessManager = COMETProcessManager::GetProcessManager();
} 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

COMETEventAction::~COMETEventAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void COMETEventAction::BeginOfEventAction(const G4Event* event)
{
    fProcessManager->BeginOfEventAction(event);
    fSteppingAction->SetTag(-1);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void COMETEventAction::EndOfEventAction(const G4Event*)
{
    if(!(fSteppingAction->GetTag()==1)) return;
    fProcessManager->EndOfEventAction();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
