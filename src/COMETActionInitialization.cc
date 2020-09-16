/// \file COMETActionInitialization.cc
/// \brief Implementation of the COMETActionInitialization class

#include "COMETActionInitialization.hh"
#include "COMETPrimaryGeneratorAction.hh"
#include "COMETRunAction.hh"
#include "COMETEventAction.hh"
#include "COMETSteppingAction.hh"
#include "COMETHistoManager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

COMETActionInitialization::COMETActionInitialization()
 : G4VUserActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

COMETActionInitialization::~COMETActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void COMETActionInitialization::BuildForMaster() const
{
  COMETHistoManager* histo = new COMETHistoManager();
  
  COMETRunAction* runAction = new COMETRunAction(histo);
  SetUserAction(runAction);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void COMETActionInitialization::Build() const
{
  COMETHistoManager* histo = new COMETHistoManager();
  
  SetUserAction(new COMETPrimaryGeneratorAction);

  COMETRunAction* runAction = new COMETRunAction(histo);
  SetUserAction(runAction);
  
  COMETEventAction* eventAction = new COMETEventAction(runAction);
  SetUserAction(eventAction);
  
  SetUserAction(new COMETSteppingAction(eventAction,histo));
}  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
