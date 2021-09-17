#include "COMETProcessManager.hh"
#include "COMETHistoManager.hh"

using namespace std;

COMETProcessManager* COMETProcessManager::fProcessManager = 0;

COMETProcessManager::COMETProcessManager(){
    fProcessManager = this;
    fHistoManager = COMETHistoManager::GetHistoManager();
}

void COMETProcessManager::BeginOfRunAction(){
    fHistoManager->OpenFile("/media/miaomiao/data/Analysis/COMET-alpha-analysis/results/output_test.root");
    fHistoManager->CreateTree("event");
    fHistoManager->SetBranch();
}

void COMETProcessManager::EndOfRunAction(){
    fHistoManager->Write();
    fHistoManager->Close();
}

void COMETProcessManager::BeginOfEventAction(const G4Event* event){
    if(event->GetEventID()%1000000 == 0) G4cout<<"Processing event "<< event->GetEventID() <<"..."<<G4endl;
    fHistoManager->ClearVector();
}

void COMETProcessManager::EndOfEventAction(){
    fHistoManager->Fill();
}

void COMETProcessManager::PreUserTrackingAction(const G4Track* track){
    fHistoManager->SetValuePre(track);
}

void COMETProcessManager::SteppingAction(const G4Step* step){
    if(step->GetTrack()->GetDefinition()->GetPDGEncoding()==-2212&&step->GetTrack()->GetVertexPosition().mag()>=1.*CLHEP::m) 
    step->GetTrack()->SetTrackStatus(fStopAndKill);
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