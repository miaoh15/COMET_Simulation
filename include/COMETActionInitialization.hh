/// \file COMETActionInitialization.hh
/// \brief Definition of the COMETActionInitialization class

#ifndef COMETActionInitialization_h
#define COMETActionInitialization_h 1

#include "G4VUserActionInitialization.hh"

/// Action initialization class.

class COMETActionInitialization : public G4VUserActionInitialization
{
  public:
    COMETActionInitialization();
    virtual ~COMETActionInitialization();

    virtual void BuildForMaster() const;
    virtual void Build() const;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

    
