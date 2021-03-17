#ifndef COMETPhysicsConstructor_h
#define COMETPhysicsConstructor_h 1

#include "G4VPhysicsConstructor.hh"
#include "globals.hh"

class COMETPhysicsConstructor : public G4VPhysicsConstructor{
    public:
        COMETPhysicsConstructor();
        ~COMETPhysicsConstructor();
    
    protected:
        virtual void ConstructParticle();
        virtual void ConstructProcess();
};

#endif