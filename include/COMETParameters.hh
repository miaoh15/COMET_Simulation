#ifndef COMETParameters_h
#define COMETParameters_h 1

#include "G4ThreeVector.hh"

#include <string>
#include "globals.hh"

using namespace std;

class COMETParameters{
    public:

    COMETParameters();
    ~COMETParameters();

    static COMETParameters* GetParameters();

    // for detector construction
    G4double target_length;
    G4double target_radius;
    G4double world_length;
    G4double world_radius;
    G4double detector_radius;
    G4double detector_thickness;
    G4double detector_theta_down;
    G4double detector_theta_up;
    G4String target_material;

    // for cut in laboratory coordinate
    bool cut_in_lab;
    double lower_bound;
    double upper_bound;

    // for restrict phase space
    bool restrict_phase_space;
    double p_min;
    double theta_min;

    // for multiply cross section
    double multi;

    // for simplify simulation
    bool kill_secondary;
    bool collect_only_AP;
    bool only_target_AP;
    bool fill_only_AP;

    // for generator
    G4String particle;
    int Nparticle;
    double energy; // GeV
    G4ThreeVector PDirection;
    G4ThreeVector Position;
    bool Smearing;
    G4double MaxSmearing;

    // for cross section data
    string MCS;
    string MCS_RPS;
    string APPMaxDCS;
    string APPMaxDCS_RPS;

    // for output file
    string outputName;

    private:

    static COMETParameters* fParameters;
};

#endif