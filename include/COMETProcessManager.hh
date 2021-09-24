#ifndef COMETProcessManager_h
#define COMETProcessManager_h 1

#include "COMETHistoManager.hh"
#include "COMETParameters.hh"
#include "globals.hh"

#include "G4Track.hh"
#include "G4Event.hh"

#include <vector>
#include <string>

class COMETProcessManager{
    public:

    COMETProcessManager();
    ~COMETProcessManager();

    static COMETProcessManager* GetProcessManager();
    void BeginOfRunAction();
    void EndOfRunAction();
    void PreUserTrackingAction(const G4Track* track);
    void PostUserTrackingAction();
    void BeginOfEventAction(const G4Event* event);
    void EndOfEventAction();
    G4bool ProcessHits(G4Step* step);
    void SteppingAction(const G4Step* );

    private:
    COMETHistoManager* fHistoManager;
    static COMETProcessManager* fProcessManager;
    COMETParameters* fParameters;
};

#endif
