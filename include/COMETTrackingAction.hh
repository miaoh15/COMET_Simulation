#ifndef COMETTrackingAction_h
#define COMETTrackingAction_h 1

#include "COMETHistoManager.hh"
#include "COMETRunAction.hh"
#include "COMETProcessManager.hh"

#include "G4UserTrackingAction.hh"
#include "globals.hh"

class COMETTrackingAction : public G4UserTrackingAction {

    public:
        COMETTrackingAction();
        ~COMETTrackingAction();

        void PreUserTrackingAction(const G4Track*);
        void PostUserTrackingAction(const G4Track*);
    
    private:
        COMETRunAction* fRunAction;
        COMETProcessManager* fProcessManager;
};

#endif