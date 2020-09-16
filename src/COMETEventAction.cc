/// \file COMETEventAction.cc
/// \brief Implementation of the COMETEventAction class

#include "COMETEventAction.hh"
#include "COMETRunAction.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

COMETEventAction::COMETEventAction(COMETRunAction* runAction)
: G4UserEventAction(),
  fRunAction(runAction)
{} 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

COMETEventAction::~COMETEventAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void COMETEventAction::BeginOfEventAction(const G4Event*)
{    
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void COMETEventAction::EndOfEventAction(const G4Event*)
{   
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
