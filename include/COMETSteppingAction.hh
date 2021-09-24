/// \file COMETSteppingAction.hh
/// \brief Definition of the COMETSteppingAction class

#ifndef COMETSteppingAction_h
#define COMETSteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "globals.hh"

#include "COMETParameters.hh"

class COMETEventAction;

class G4LogicalVolume;

class COMETHistoManager;

class COMETProcessManager;

/// Stepping action class
/// 

class COMETSteppingAction : public G4UserSteppingAction
{
  public:
    COMETSteppingAction();
    virtual ~COMETSteppingAction();

    // method from the base class
    virtual void UserSteppingAction(const G4Step*);
    inline void SetTag(int _tag);
    inline int GetTag() const;

  private:
    COMETHistoManager* fHistoManager;
    COMETProcessManager* fProcessManager;
    COMETParameters* fParameters;

    int tag;
    // -1 other process of proton
    // 0 proton go through the target
    // 1 anti-proton production
};

inline void COMETSteppingAction::SetTag(int _tag){
  tag = _tag;
}

inline int COMETSteppingAction::GetTag() const {
  return tag;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
