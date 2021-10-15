/// \file COMETActionInitialization.cc
/// \brief Implementation of the COMETActionInitialization class

#include "COMETActionInitialization.hh"
#include "COMETPrimaryGeneratorAction.hh"
#include "COMETRunAction.hh"
#include "COMETEventAction.hh"
#include "COMETSteppingAction.hh"
#include "COMETHistoManager.hh"
#include "COMETTrackingAction.hh"
#include "COMETStackingAction.hh"

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
  COMETRunAction* runAction = new COMETRunAction();
  SetUserAction(runAction);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void COMETActionInitialization::Build() const
{ 
  SetUserAction(new COMETPrimaryGeneratorAction);

  SetUserAction(new COMETRunAction());

  SetUserAction(new COMETEventAction());

  SetUserAction(new COMETTrackingAction());

  COMETSteppingAction* steppingAction = new COMETSteppingAction();
  SetUserAction(steppingAction);

  SetUserAction(new COMETStackingAction(steppingAction));
}  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
