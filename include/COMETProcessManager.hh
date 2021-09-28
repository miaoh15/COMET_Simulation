#ifndef COMETProcessManager_h
#define COMETProcessManager_h 1

#include "COMETHistoManager.hh"
#include "COMETParameters.hh"
#include "COMETSteppingAction.hh"
#include "globals.hh"

#include "G4Track.hh"
#include "G4Event.hh"
#include "G4Run.hh"

#include <vector>
#include <string>

class COMETProcessManager{
    public:

    COMETProcessManager();
    ~COMETProcessManager();

    static COMETProcessManager* GetProcessManager();
    void BeginOfRunAction(const G4Run* aRun);
    void EndOfRunAction();
    void PreUserTrackingAction(const G4Track* track);
    void PostUserTrackingAction();
    void BeginOfEventAction(const G4Event* event);
    void EndOfEventAction();
    G4bool ProcessHits(G4Step* step);
    void SteppingAction(const G4Step* );

    inline int GetTag() const;

    private:
    COMETHistoManager* fHistoManager;
    static COMETProcessManager* fProcessManager;
    COMETParameters* fParameters;
    COMETSteppingAction* fSteppingAction;

    int tag;
    // -1 other process of proton
    // 0 proton go through the target
    // 1 anti-proton production
};

inline int COMETProcessManager::GetTag() const {
    return tag;
}

#endif
