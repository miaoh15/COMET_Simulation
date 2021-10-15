/// \file COMETEventAction.hh
/// \brief Definition of the COMETEventAction class

#ifndef COMETEventAction_h
#define COMETEventAction_h 1

#include "COMETHistoManager.hh"
#include "COMETProcessManager.hh"

#include "G4UserEventAction.hh"
#include "globals.hh"

class COMETRunAction;
class COMETSteppingAction;

/// Event action class
///

class COMETEventAction : public G4UserEventAction
{
  public:
    COMETEventAction();
    virtual ~COMETEventAction();

    virtual void BeginOfEventAction(const G4Event* event);
    virtual void EndOfEventAction(const G4Event* event);

  private:
    COMETProcessManager* fProcessManager;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

    
