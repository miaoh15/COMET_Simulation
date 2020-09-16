/// \file COMETDetectorConstruction.cc
/// \brief Implementation of the COMETDetectorConstruction class

#include "COMETDetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4Tubs.hh"

static const double     Pi  = 3.14159265358979323846;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

COMETDetectorConstruction::COMETDetectorConstruction()
: G4VUserDetectorConstruction(),
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

COMETDetectorConstruction::~COMETDetectorConstruction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* COMETDetectorConstruction::Construct()
{  
  // Get nist material manager
  G4NistManager* nist = G4NistManager::Instance();
  
  // Target parameters
  //
  G4double target_length = 70*cm, target_radius = 13*mm;
  G4Material* target_material = nist->FindOrBuildMaterial("G4_GRAPHITE");
   
  // Option to switch on/off checking of volumes overlaps
  //
  G4bool checkOverlaps = true;

  G4double a;  // mass of a mole;
  G4double z;  // z=mean number of protons;  
  G4double density; 

  // Vacuum
  G4Material* Galactic = new G4Material("Galactic", z=1., a=1.01*g/mole,density= universe_mean_density,
                  kStateGas, 2.73*kelvin, 3.e-18*pascal);

  //     
  // World
  //
  G4double world_length = 2*m;
  G4double world_radius = 4*m;;
  
  G4VSolid* worldS = new G4Tubs("world", 0., world_radius, world_length/2, 0., 2*Pi);
      
  G4LogicalVolume* worldLV =                         
    new G4LogicalVolume(worldS,          //its solid
                        Galactic,           //its material
                        "World");            //its name
                                   
  G4VPhysicalVolume* worldPV = 
    new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(),       //at (0,0,0)
                      worldLV,            //its logical volume
                      "World",               //its name
                      0,                     //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      checkOverlaps);        //overlaps checking
                     
  //     
  // Target
  //  
  G4VSolid* targetS = new G4Tubs("target", 0., target_radius, target_length/2, 0., 2*Pi);

  G4LogicalVolume* targetLV =                         
    new G4LogicalVolume(targetS,            //its solid
                        target_material,             //its material
                        "target");         //its name
               
  new G4PVPlacement(0,                       //no rotation
                    G4ThreeVector(),         //at (0,0,0)
                    targetLV,                //its logical volume
                    "target",              //its name
                    worldLV,              //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking

  //
  //always return the physical World
  //
  return worldPV;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
