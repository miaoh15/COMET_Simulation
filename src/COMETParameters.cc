#include "G4SystemOfUnits.hh"

#include "COMETParameters.hh"

#include <unistd.h>

COMETParameters* COMETParameters::fParameters = 0;

COMETParameters::COMETParameters(){

    fParameters = this;

    // for detector construction
    target_length = 100*CLHEP::um;
    target_radius = 2*CLHEP::cm;
    world_length = 4*CLHEP::m;
    world_radius = 4*CLHEP::m;
    detector_radius = 1*CLHEP::m;
    detector_thickness = 0.01*CLHEP::m;
    detector_theta_down = 0.;
    detector_theta_up = 179.5;
    target_material = "Be";

    // for cut in laboratory coordinate
    cut_in_lab = false; // Only collect particles fly in a certain range of direction.
    lower_bound = 90.;
    upper_bound = 180.;

    // for restrict phase space
    restrict_phase_space = false; // Restrict the phase space P [1.4, inf] theta [2.6, pi].
    p_min = 1.4;
    theta_min = 2.6;

    // for multiply cross section
    multi = 1e7;

    // for generator
    particle = "proton";
    Nparticle = 1;
    energy = 10.14*GeV; // GeV
    PDirection = G4ThreeVector(0.,0.,1.);
    Position = G4ThreeVector(0.,0.,-2.*m);
    Smearing = false;
    MaxSmearing = 2.5*mm;

    // for simplify simulation
    kill_secondary = true; // To kill secondary particles and primary particles, only anti-proton will be reserved and be killed after being detected.
    collect_only_AP = true; // Only information of an-riprotons will be write in ROOT file.
    only_target_AP = true; // Only anti-protons created within target will be reserved, in other word, AP created in detector will be killed.
    fill_only_AP = true; // Only events where anti-protons are created will be filled.

    // for cross section data
    char current_path[255];
    if(!getcwd(current_path, 255)) cout<<"Fatal: Current path cannot access properly !!!"<<endl;
    string path = current_path;
    path = path+"/";

    MCS = path+"data/AntiprotonMicroCrossSection.txt";
    MCS_RPS = path+"data/MCSRestrictPhaseSpace.txt";
    APPMaxDCS = path+"data/APPMaxDCS.txt";
    APPMaxDCS_RPS = path+"data/APPMaxDCS_RPS.txt";

    // for output file
    //outputName = "/media/miaomiao/data/Analysis/COMET-alpha-analysis/results/output_Boyarinov/output3.root";
    outputName = "output.root";
}

COMETParameters::~COMETParameters(){
    delete fParameters;
}

COMETParameters* COMETParameters::GetParameters(){
    if(!fParameters){
        fParameters = new COMETParameters();
    }

    return fParameters;
}
