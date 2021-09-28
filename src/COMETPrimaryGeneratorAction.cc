/// \file COMETPrimaryGeneratorAction.cc
/// \brief Implementation of the COMETPrimaryGeneratorAction class

#include "COMETPrimaryGeneratorAction.hh"

#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4RunManager.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

COMETPrimaryGeneratorAction::COMETPrimaryGeneratorAction()
: G4VUserPrimaryGeneratorAction(),
  fParticleGun(0)
{
  fParameters = COMETParameters::GetParameters();
  fParticleGun  = new G4ParticleGun(fParameters->Nparticle);

  // default particle kinematic
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4ParticleDefinition* particle
    = particleTable->FindParticle(fParameters->particle);
  fParticleGun->SetParticleDefinition(particle);
  fParticleGun->SetParticleMomentumDirection(fParameters->PDirection);
  //fParticleGun->SetParticleEnergy(18.2849*GeV);
  //fParticleGun->SetParticleEnergy(10.8977*GeV);
  fParticleGun->SetParticleEnergy(fParameters->energy);

  random = new TRandom();
  random->SetSeed(clock());
  
  if(fParameters->Smearing) rho = new TF1("rho", "x", 0, fParameters->MaxSmearing);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

COMETPrimaryGeneratorAction::~COMETPrimaryGeneratorAction()
{
  delete fParticleGun;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void COMETPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  if(fParameters->Smearing){
    G4double R = rho->GetRandom(0., fParameters->Smearing);

    G4double x,y;
    random->Circle(x,y,R);

    fParticleGun->SetParticlePosition(G4ThreeVector(x,y,-1.*m));
  }

  else{
    fParticleGun->SetParticlePosition(G4ThreeVector(0.,0.,-2.*m));
  }

  fParticleGun->GeneratePrimaryVertex(anEvent);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

