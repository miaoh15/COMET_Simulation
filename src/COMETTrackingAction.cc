#include "COMETTrackingAction.hh"
#include "COMETAnalysis.hh"
#include "COMETEventAction.hh"

#include "G4RunManager.hh"
#include "G4Run.hh"
#include "G4Track.hh"

using namespace CLHEP;
using namespace std;

COMETTrackingAction::COMETTrackingAction() 
: G4UserTrackingAction()
{
    fProcessManager = COMETProcessManager::GetProcessManager();
}

COMETTrackingAction::~COMETTrackingAction(){}

void COMETTrackingAction::PreUserTrackingAction(const G4Track* track){
    fProcessManager->PreUserTrackingAction(track);
}

void COMETTrackingAction::PostUserTrackingAction(const G4Track* /*track*/){
}