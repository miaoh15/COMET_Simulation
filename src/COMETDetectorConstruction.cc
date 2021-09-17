/// \file COMETDetectorConstruction.cc
/// \brief Implementation of the COMETDetectorConstruction class

#include "COMETDetectorConstruction.hh"
#include "COMETSphereSD.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4Tubs.hh"
#include "G4Sphere.hh"
#include "G4SDManager.hh"

static const double     Pi  = 3.14159265358979323846;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

COMETDetectorConstruction::COMETDetectorConstruction()
: G4VUserDetectorConstruction()
{ 
}

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
  G4Material* graphite = nist->FindOrBuildMaterial("G4_GRAPHITE");

  //G4Element* H = new G4Element("Hydrogen", "O", 1., 1.00794*g/mole);
  //G4Material* target_material = new G4Material("LiquidHydrogen", 70.8*kg/m3, 1);
  //target_material->AddElement(H, 2);
  G4Material* target_material = nist->FindOrBuildMaterial("G4_Be");
  //G4Material* target_material = nist->FindOrBuildMaterial("G4_Ta");

  //G4cout<<"Target Density: "<<target_material->GetDensity()/(g/cm3)<<G4endl;
   
  // Option to switch on/off checking of volumes overlaps
  //
  G4bool checkOverlaps = true;

  G4double a;  // mass of a mole;
  G4double z;  // z=mean number of protons;  
  G4double density; 

  // Vacuum
  G4Material* Galactic = new G4Material("Galactic", z=1., a=1.01*g/mole,density= CLHEP::universe_mean_density,
                  kStateGas, 2.73*kelvin, 3.e-18*pascal);

  //     
  // World
  //
  //G4double target_length = 70*cm, target_radius = 13*mm;
  //G4double target_length = 10*cm, target_radius = 2*cm;
  G4double target_length = 100*um, target_radius = 2*cm;
  G4double world_length = 4*m;
  G4double world_radius = 4*m;;
  G4double detector_radius = 1*m;
  G4double detector_thickness = 0.01*m;
  
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

  G4VSolid* detectorS = new G4Sphere("detector", detector_radius, detector_radius+detector_thickness, 0., 2*Pi, 0, Pi*5./6.);

  detectorLV = new G4LogicalVolume(detectorS,
    graphite,
    "detector");

  new G4PVPlacement(0,
    G4ThreeVector(),
    detectorLV,
    "detector",
    worldLV,
    false,
    0,
    checkOverlaps);

  //
  //always return the physical World
  //
  return worldPV;
}

void COMETDetectorConstruction::ConstructSDandField(){
  COMETSphereSD* SphereSD = new COMETSphereSD("/COMETDet/SphereSD");

  SetSensitiveDetector(detectorLV, SphereSD);
  G4SDManager::GetSDMpointer()->AddNewDetector(SphereSD);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
