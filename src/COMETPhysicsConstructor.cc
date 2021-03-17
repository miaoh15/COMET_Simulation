#include "COMETPhysicsConstructor.hh"
#include "COMETAntiprotonProduction.hh"
#include "COMETAPProduction.hh"

#include "globals.hh"
#include "G4SystemOfUnits.hh"
#include "G4ProcessManager.hh"
#include "G4ProcessVector.hh"

#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"
#include "G4ParticleTable.hh"
#include "G4MesonConstructor.hh"
#include "G4BaryonConstructor.hh"
#include "G4IonConstructor.hh"

#include "G4ios.hh"
#include "G4UserLimits.hh"

COMETPhysicsConstructor::COMETPhysicsConstructor() : G4VPhysicsConstructor(){
    ;
}

COMETPhysicsConstructor::~COMETPhysicsConstructor(){
    ;
}

void COMETPhysicsConstructor::ConstructParticle(){

}

void COMETPhysicsConstructor::ConstructProcess(){
    G4ParticleDefinition* particle = G4ParticleTable::GetParticleTable()->FindParticle("proton");
    G4ProcessManager* pManager = particle->GetProcessManager();
    COMETAntiprotonProduction* APP = new COMETAntiprotonProduction();
    //COMETAPProduction* APP = new COMETAPProduction();
    pManager->AddDiscreteProcess(APP);
}

