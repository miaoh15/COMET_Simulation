/// \file COMET-alpha.cc
/// \brief Main program of the COMET-alpha Simulation

#include "COMETDetectorConstruction.hh"
#include "COMETActionInitialization.hh"
#include "COMETPhysicsConstructor.hh"
#include "QGSP_BERT_HP.hh"

//#ifdef G4MULTITHREADED
//#include "G4MTRunManager.hh"
//#else
#include "G4RunManager.hh"
//#endif

#include "G4UImanager.hh"
#include "QBBC.hh"

#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

#include "Randomize.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int main(int argc,char** argv)
{
  // Detect interactive mode (if no arguments) and define UI session
  //
  G4double t = clock();
  G4UIExecutive* ui = 0;
  if ( argc == 1 ) {
    ui = new G4UIExecutive(argc, argv);
  }

  // Optionally: choose a different Random engine...
  // G4Random::setTheEngine(new CLHEP::MTwistEngine);
  
  // Construct the default run manager
  //
//#ifdef G4MULTITHREADED
//  G4MTRunManager* runManager = new G4MTRunManager;
//#else
  G4RunManager* runManager = new G4RunManager;
//#endif

  // Set mandatory initialization classes
  //
  // Detector construction
  runManager->SetUserInitialization(new COMETDetectorConstruction());

  // Physics list
  G4VModularPhysicsList* physicsList = new QGSP_BERT_HP;
  //COMETPhysicsConstructor* fConstructor = new COMETPhysicsConstructor();
  //physicsList->RegisterPhysics(fConstructor);
  //physicsList->SetVerboseLevel(0);
  runManager->SetUserInitialization(physicsList);
    
  // User action initialization
  runManager->SetUserInitialization(new COMETActionInitialization());
  
  // Initialize visualization
  //
  G4VisManager* visManager = new G4VisExecutive;
  // G4VisExecutive can take a verbosity argument - see /vis/verbose guidance.
  // G4VisManager* visManager = new G4VisExecutive("Quiet");
  visManager->Initialize();

  // Get the pointer to the User Interface manager
  G4UImanager* UImanager = G4UImanager::GetUIpointer();

  // Process macro or start UI session
  //
  if ( ! ui ) { 
    // batch mode
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    UImanager->ApplyCommand(command+fileName);
  }
  else { 
    // interactive mode
    UImanager->ApplyCommand("/control/execute init_vis.mac");
    ui->SessionStart();
    delete ui;
  }

  // Job termination
  // Free the store: user actions, physics_list and detector_description are
  // owned and deleted by the run manager, so they should not be deleted 
  // in the main() program !
  
  delete visManager;
  delete runManager;
  G4cout<<"Total time: "<<(clock()-t)/CLOCKS_PER_SEC<<"s"<<G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....
