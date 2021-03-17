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

void COMETProcessManager::BeginOfEventAction(){
    fHistoManager->ClearVector();
}

void COMETProcessManager::EndOfEventAction(){
    fHistoManager->Fill();
}

void COMETProcessManager::PreUserTrackingAction(const G4Track* track){
    fHistoManager->SetValuePre(track);
}

COMETProcessManager* COMETProcessManager::GetProcessManager(){
    if(!fProcessManager){
        fProcessManager = new COMETProcessManager;
    }
    return fProcessManager;
}