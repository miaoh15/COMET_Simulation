#ifndef COMETAntiprotonProduction_h
#define COMETAntiprotonProduction_h 1

#include "G4VDiscreteProcess.hh"
#include "G4ParticleTable.hh"

#include "TF1.h"
#include "TRandom.h"
#include "TLorentzVector.h"

#include "COMETCHCrossSection.hh"

class COMETAntiprotonProduction : public G4VDiscreteProcess
{
    public:

    COMETAntiprotonProduction(const G4String& name = "AntiprotonProduction",
        G4ProcessType aType = fHadronic);
    
    ~COMETAntiprotonProduction();

    G4VParticleChange* PostStepDoIt(
        const G4Track&,
        const G4Step&
    );

    G4double GetMeanFreePath(const G4Track&, G4double, G4ForceCondition*);

    G4bool CheckCondition(const G4Step& aStep);

    void GetDatas(const G4Step* aStep);

    void PrepareSecondary(const G4Track&);

    G4ParticleTable* particleTable;
    G4ParticleDefinition* proton, *anti_proton;
    G4VParticleChange fParticleChange;
    G4Track* Secondary1, *Secondary2, *Secondary3, *Secondary4;
    G4String p_name;
    G4DynamicParticle* DP1, *DP2, *DP3, *DP4;
    TRandom* random;
    
    private:

    COMETCHCrossSection* fCHCrossSection;
    TF1* FermiMomentum;
    TLorentzVector target;
    TVector3 v_lab;
};

#endif