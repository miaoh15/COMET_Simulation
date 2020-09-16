/// \file COMETPrimaryGeneratorAction.hh
/// \brief Definition of the COMETPrimaryGeneratorAction class

#ifndef COMETPrimaryGeneratorAction_h
#define COMETPrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "globals.hh"
#include "TH1D.h"

class G4ParticleGun;
class G4Event;
class G4Box;

/// The primary generator action class with particle gun.
///
/// The default kinematic is a 6 MeV gamma, randomly distribued 
/// in front of the phantom across 80% of the (X,Y) phantom size.

class COMETPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    COMETPrimaryGeneratorAction();    
    virtual ~COMETPrimaryGeneratorAction();

    // method from the base class
    virtual void GeneratePrimaries(G4Event*);         
  
    // method to access particle gun
    const G4ParticleGun* GetParticleGun() const { return fParticleGun; }
  
  private:
    G4ParticleGun*  fParticleGun; // pointer a to G4 gun class
    G4Box* fEnvelopeBox;
    TH1D* a;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
