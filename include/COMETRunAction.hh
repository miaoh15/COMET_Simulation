/// \file COMETRunAction.hh
/// \brief Definition of the COMETRunAction class

#ifndef COMETRunAction_h
#define COMETRunAction_h 1

#include "COMETProcessManager.hh"

#include "G4UserRunAction.hh"
#include "G4Accumulable.hh"
#include "globals.hh"

#include <vector>
#include <string>

using namespace std;

class G4Run;
class COMETHistoManager;

/// Run action class
///
/// In EndOfRunAction(), it calculates the dose in the selected volume 
/// from the energy deposit accumulated via stepping and event actions.
/// The computed dose is then printed on the screen.

class COMETRunAction : public G4UserRunAction
{
  public:
    COMETRunAction();
    virtual ~COMETRunAction();

    // virtual G4Run* GenerateRun();
    virtual void BeginOfRunAction(const G4Run*);
    virtual void   EndOfRunAction(const G4Run*);

  private:
    COMETHistoManager* fHistoManager;
    COMETProcessManager* fProcessManager;
};

#endif

