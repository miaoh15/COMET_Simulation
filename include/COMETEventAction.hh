/// \file COMETEventAction.hh
/// \brief Definition of the COMETEventAction class

#ifndef COMETEventAction_h
#define COMETEventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"

class COMETRunAction;

/// Event action class
///

class COMETEventAction : public G4UserEventAction
{
  public:
    COMETEventAction(COMETRunAction* runAction);
    virtual ~COMETEventAction();

    virtual void BeginOfEventAction(const G4Event* event);
    virtual void EndOfEventAction(const G4Event* event);

    void AddEdep(G4double edep) { fEdep += edep; }

  private:
    COMETRunAction* fRunAction;
    G4double     fEdep;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

    
