#include "G4SystemOfUnits.hh"

#include "COMETParameters.hh"

COMETParameters* COMETParameters::fParameters = 0;

COMETParameters::COMETParameters(){

    fParameters = this;

    // for detector construction
    target_length = 150*CLHEP::um;
    target_radius = 2*CLHEP::cm;
    world_length = 4*CLHEP::m;
    world_radius = 4*CLHEP::m;
    detector_radius = 1*CLHEP::m;
    detector_thickness = 0.01*CLHEP::m;
    detector_theta_down = 0.;
    detector_theta_up = 179.5;
    target_material = "Be";

    // for cut in laboratory coordinate
    cut_in_lab = true;
    lower_bound = 90.;
    upper_bound = 180.;

    // for restrict phase space
    restrict_phase_space = true;
    p_min = 1.4;
    theta_min = 2.6;

    // for multiply cross section
    multi = 1e14;

    // for simplify simulation
    kill_secondary = true;
    collect_only_AP = true;
    only_target_AP = true;

    // for cross section data
    MCS = "/home/miaomiao/work/COMET-alpha/data/AntiprotonMicroCrossSection.txt";
    MCS_RPS = "/home/miaomiao/work/COMET-alpha/data/MCSRestrictPhaseSpace.txt";
    APPMaxDCS = "/home/miaomiao/work/COMET-alpha/data/APPMaxDCS.txt";
    APPMaxDCS_RPS = "/home/miaomiao/work/COMET-alpha/data/APPMaxDCS_RPS.txt";

    // for output file
    outputName = "/media/miaomiao/data/Analysis/COMET-alpha-analysis/results/output_test.root";
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