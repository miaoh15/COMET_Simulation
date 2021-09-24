#include "COMETStackingAction.hh"
#include "COMETSteppingAction.hh"

#include "G4SDManager.hh"
#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4HCofThisEvent.hh"
#include "G4Track.hh"
#include "G4TrackStatus.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"
#include "G4SystemOfUnits.hh"
#include "G4ios.hh"

using namespace std;

COMETStackingAction::COMETStackingAction(COMETSteppingAction* steppingAction)
  : fSteppingAction(steppingAction)
{
        fParameters = COMETParameters::GetParameters();
}

COMETStackingAction::~COMETStackingAction()
{;}

G4ClassificationOfNewTrack COMETStackingAction
::ClassifyNewTrack(const G4Track * aTrack)
{
        G4ClassificationOfNewTrack classification = fUrgent;
        if(!((aTrack->GetParentID()==1&&aTrack->GetDefinition()->GetPDGEncoding()==-2212) || aTrack->GetTrackID()==1)) {
                classification = fWaiting;
        }
        return classification;
}

void COMETStackingAction::NewStage(){
    if(fParameters->kill_secondary == true){
        if(!(fSteppingAction->GetTag()==1)) stackManager->clear();
    }
}
