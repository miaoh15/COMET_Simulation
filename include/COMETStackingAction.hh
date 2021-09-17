#ifndef COMETStackingAction_h
#define COMETStackingAction_h 1

#include "G4UserStackingAction.hh"
#include <string>

class G4Track;
class COMETSteppingAction;

class COMETStackingAction : public G4UserStackingAction
{
public:
  COMETStackingAction(COMETSteppingAction* );
  virtual ~COMETStackingAction();

public:
  virtual G4ClassificationOfNewTrack ClassifyNewTrack(const G4Track* aTrack);
  virtual void NewStage();

private:
  COMETSteppingAction* fSteppingAction;
};

#endif