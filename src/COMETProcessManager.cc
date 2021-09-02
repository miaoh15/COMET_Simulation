#include "COMETProcessManager.hh"
#include "COMETHistoManager.hh"

using namespace std;

COMETProcessManager* COMETProcessManager::fProcessManager = 0;

COMETProcessManager::COMETProcessManager(){
    fProcessManager = this;
    fHistoManager = COMETHistoManager::GetHistoManager();
}

void COMETProcessManager::BeginOfRunAction(){
    fHistoManager->OpenFile("output.root");
    fHistoManager->CreateTree("event");
    fHistoManager->SetBranch();
}

void COMETProcessManager::EndOfRunAction(){
    fHistoManager->Write();
    fHistoManager->Close();
}

void COMETProcessManager::BeginOfEventAction(const G4Event* event){
    if(event->GetEventID()%100000 == 0) G4cout<<"Processing event "<< event->GetEventID() <<"..."<<G4endl;
    fHistoManager->ClearVector();
}

void COMETProcessManager::EndOfEventAction(){
    fHistoManager->Fill();
}

void COMETProcessManager::PreUserTrackingAction(const G4Track* track){
    fHistoManager->SetValuePre(track);
}

G4bool COMETProcessManager::ProcessHits(G4Step* step){
    fHistoManager->SetSDHit(step);
    return true;
}

COMETProcessManager* COMETProcessManager::GetProcessManager(){
    if(!fProcessManager){
        fProcessManager = new COMETProcessManager;
    }
    return fProcessManager;
}