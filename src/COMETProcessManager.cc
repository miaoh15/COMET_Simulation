#include "COMETProcessManager.hh"
#include "COMETHistoManager.hh"

using namespace std;

COMETProcessManager* COMETProcessManager::fProcessManager = 0;

COMETProcessManager::COMETProcessManager(){
    fProcessManager = this;
    fHistoManager = COMETHistoManager::GetHistoManager();
    fParameters = COMETParameters::GetParameters();
}

void COMETProcessManager::BeginOfRunAction(const G4Run* aRun){
    G4cout << "### Run " << aRun->GetRunID() << " start." << G4endl;
    G4Random::setTheSeed(clock());
    fHistoManager->OpenFile(fParameters->outputName);
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
    tag = -1;
}

void COMETProcessManager::EndOfEventAction(){
    if(!(tag==1)) return;
    fHistoManager->Fill();
}

void COMETProcessManager::PreUserTrackingAction(const G4Track* track){

    if(track->GetTrackID()==1) return;
    if(fParameters->collect_only_AP){
        if(track->GetParticleDefinition()->GetPDGEncoding()!=-2212) return;
    }    
    fHistoManager->SetValuePre(track);
}

void COMETProcessManager::SteppingAction(const G4Step* step){

    G4Track* track = step->GetTrack();

    if(fParameters->kill_secondary == true){

        if(step->GetPreStepPoint()->GetPhysicalVolume()->GetName()=="target"&&step->GetPostStepPoint()->GetPhysicalVolume()->GetName()=="World"){
            if(track->GetTrackID()==1){
                tag = 0; // Primary particle crosses target without anti-proton created.
                track->SetTrackStatus(fStopAndKill);
            }
            if(track->GetDefinition()->GetPDGEncoding()==-2212&&track->GetParentID()==1){
                tag = 1; // Anti-proton has been created.
            }
        }
    }

    if(fParameters->only_target_AP == true){
        if(step->GetTrack()->GetDefinition()->GetPDGEncoding()==-2212&&step->GetTrack()->GetVertexPosition().mag()>=fParameters->detector_radius) 
        step->GetTrack()->SetTrackStatus(fStopAndKill);
    }
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