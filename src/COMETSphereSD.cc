#include "COMETSphereSD.hh"

COMETSphereSD::COMETSphereSD(G4String name)
    : G4VSensitiveDetector(name){
        fProcessManager = COMETProcessManager::GetProcessManager();
    }

COMETSphereSD::~COMETSphereSD(){
}

void COMETSphereSD::Initialize(G4HCofThisEvent* ){
}

G4bool COMETSphereSD::ProcessHits(G4Step* step, G4TouchableHistory*){
    return fProcessManager->ProcessHits(step);
}

void COMETSphereSD::EndOfEvent(G4HCofThisEvent* ){
}