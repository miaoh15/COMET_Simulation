/// \file COMETRunAction.cc
/// \brief Implementation of the COMETRunAction class

#include "COMETRunAction.hh"
#include "COMETPrimaryGeneratorAction.hh"
#include "COMETDetectorConstruction.hh"
#include "COMETAnalysis.hh"
// #include "COMETRun.hh"

#include "G4RunManager.hh"
#include "G4Run.hh"
#include "G4AccumulableManager.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4RandomTools.hh"

#include "COMETHistoManager.hh"

using namespace std;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

COMETRunAction::COMETRunAction()
: G4UserRunAction()
  {
    fProcessManager = COMETProcessManager::GetProcessManager();
  }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

COMETRunAction::~COMETRunAction()
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void COMETRunAction::BeginOfRunAction(const G4Run* aRun)
{ 
fProcessManager->BeginOfRunAction(aRun);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void COMETRunAction::EndOfRunAction(const G4Run*)
{
  fProcessManager->EndOfRunAction();
}

