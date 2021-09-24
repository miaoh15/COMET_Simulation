#ifndef COMETCHCrossSection_h
#define COMETCHCrossSection_h 1

#include "globals.hh"
#include "G4Material.hh"
#include "G4ParticleDefinition.hh"

#include "COMETParameters.hh"

using namespace std;

class COMETCHCrossSection
{
    public:

    COMETCHCrossSection(G4ParticleDefinition* particle);
    ~COMETCHCrossSection();

    G4double GetMicroCrossSection(G4double sqrt_S);

    private:
    vector<G4double> CrossSectionStore;
    vector<G4double> sqrt_S;

    COMETParameters* fParameters;
};

#endif