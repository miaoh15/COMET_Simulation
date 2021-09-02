#ifndef COMETSphereSD_h
#define COMETSphereSD_h 1

#include "G4VSensitiveDetector.hh"
#include "COMETProcessManager.hh"

class COMETSphereSD : public G4VSensitiveDetector{
    public:
    COMETSphereSD(G4String name);
    ~COMETSphereSD();

    virtual void Initialize(G4HCofThisEvent* );
    virtual G4bool ProcessHits(G4Step* , G4TouchableHistory* );
    virtual void EndOfEvent(G4HCofThisEvent* );

    private:
    COMETProcessManager* fProcessManager;
};

#endif