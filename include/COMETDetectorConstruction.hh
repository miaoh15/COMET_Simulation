/// \file COMETDetectorConstruction.hh
/// \brief Definition of the COMETDetectorConstruction class

#ifndef COMETDetectorConstruction_h
#define COMETDetectorConstruction_h 1

#include "COMETParameters.hh"

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;

/// Detector construction class to define materials and geometry.

class COMETDetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    COMETDetectorConstruction();
    virtual ~COMETDetectorConstruction();

    virtual G4VPhysicalVolume* Construct();
  
  private:

    virtual void ConstructSDandField();

    G4LogicalVolume* detectorLV;

    COMETParameters* fParameters;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

