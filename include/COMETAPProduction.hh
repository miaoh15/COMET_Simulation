#ifndef COMETAPProduction_h
#define COMETAPProduction_h 1

#include "G4VDiscreteProcess.hh"
#include "G4ParticleTable.hh"

#include "TF1.h"
#include "TRandom.h"
#include "TLorentzVector.h"

#include "COMETCHCrossSection.hh"

class COMETAPProduction : public G4VDiscreteProcess
{
    public:

    COMETAPProduction(const G4String& name = "AntiprotonProduction",
        G4ProcessType aType = fHadronic);
    
    ~COMETAPProduction();

    G4VParticleChange* PostStepDoIt(
        const G4Track&,
        const G4Step&
    );

    G4double GetMeanFreePath(const G4Track&, G4double, G4ForceCondition*);

    G4bool CheckCondition(const G4Step& aStep);

    void GetDatas(const G4Step* aStep);

    void PrepareSecondary(const G4Track&);

    G4double GetMaxDCS(G4double sqrt_S_now);

    G4double ComputeDCS(G4double p, G4double Theta, G4double sqrt_S);

    G4ParticleTable* particleTable;
    G4ParticleDefinition* proton, *anti_proton;
    G4VParticleChange fParticleChange;
    G4Track* Secondary1;
    G4String p_name;
    G4DynamicParticle* DP1;
    TRandom* random;
    
    private:

    COMETCHCrossSection* fCHCrossSection;
    TF1* FermiMomentum;
    TLorentzVector target;
    G4double fSqrt_S;
    const G4double Mx = 2.814, sqrt_St = 3.752, Et = 6.566, Tt = 5.628;
    vector<G4double> MaxDCSStore;
    vector<G4double> sqrt_S;
    TVector3 v_lab;

    bool tag;
    double upper;
    double lower;
};

#endif