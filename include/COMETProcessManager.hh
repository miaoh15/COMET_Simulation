#ifndef COMETProcessManager_h
#define COMETProcessManager_h 1

#include "COMETHistoManager.hh"
#include "globals.hh"

#include "G4Track.hh"

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
    void BeginOfEventAction();
    void EndOfEventAction();

    private:
    COMETHistoManager* fHistoManager;
    static COMETProcessManager* fProcessManager;
};

#endif
