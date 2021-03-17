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

#include "COMETHistoManager.hh"

using namespace std;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

COMETRunAction::COMETRunAction()
: G4UserRunAction()
  {
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

    analysisManager->CreateNtuple("COMET","event");
    analysisManager->CreateNtupleDColumn("Px");
    analysisManager->CreateNtupleDColumn("Py");
    analysisManager->CreateNtupleDColumn("Pz");
    analysisManager->CreateNtupleDColumn("Posx");
    analysisManager->CreateNtupleDColumn("Posy");
    analysisManager->CreateNtupleDColumn("Posz");
    analysisManager->CreateNtupleDColumn("P");
    analysisManager->FinishNtuple();

    fProcessManager = COMETProcessManager::GetProcessManager();
  }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

COMETRunAction::~COMETRunAction()
{
  delete G4AnalysisManager::Instance();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void COMETRunAction::BeginOfRunAction(const G4Run* aRun)
{ 
G4cout << "### Run " << aRun->GetRunID() << " start." << G4endl;

fProcessManager->BeginOfRunAction();

G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
G4String fileName = "COMET_data";
analysisManager->OpenFile(fileName);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void COMETRunAction::EndOfRunAction(const G4Run*)
{

  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager->Write();
  analysisManager->CloseFile();

  fProcessManager->EndOfRunAction();
}

