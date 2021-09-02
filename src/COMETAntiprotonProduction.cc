#include "COMETAntiprotonProduction.hh"
#include "COMETDetectorConstruction.hh"
#include "COMETCHCrossSection.hh"
#include "COMETAnalysis.hh"

#include "G4LorentzConvertor.hh"

#include "TLorentzVector.h"
#include "TRandom.h"
#include "TF1.h"
#include "TGenPhaseSpace.h"

using namespace std;
using namespace CLHEP;

COMETAntiprotonProduction::COMETAntiprotonProduction( const G4String& name, G4ProcessType aType)
    : G4VDiscreteProcess(name,aType){
    particleTable = G4ParticleTable::GetParticleTable();
    proton = particleTable->FindParticle("proton");
    anti_proton = particleTable->FindParticle("anti_proton");

    fCHCrossSection = new COMETCHCrossSection(anti_proton);

    FermiMomentum = new TF1("fermi_momentum","(x<[1])*[0]+(x>[1])*[3]*pow([4]/[3],(x-[1])/([2]-[1]))",0.,1.);
    FermiMomentum->SetParameters(1,0.24,0.8,2e-2,4.5e-4);

    random = new TRandom();
    random->SetSeed(clock());
}

COMETAntiprotonProduction::~COMETAntiprotonProduction(){
    /*delete Secondary1;
    delete Secondary2;
    delete Secondary3;
    delete Secondary4;
    delete DP1;
    delete DP2;
    delete DP3;
    delete DP4;
    delete FermiMomentum;
    delete fCHCrossSection;*/
}

G4VParticleChange* COMETAntiprotonProduction::PostStepDoIt(const G4Track& trackData,
    const G4Step& aStep){
        fParticleChange.Initialize(trackData);

        if(CheckCondition(aStep)){
            GetDatas(&aStep);
            PrepareSecondary(trackData);

            fParticleChange.AddSecondary(Secondary1);
            fParticleChange.AddSecondary(Secondary2);
            fParticleChange.AddSecondary(Secondary3);
            fParticleChange.AddSecondary(Secondary4);
            fParticleChange.ProposeTrackStatus(fStopAndKill);
            //G4cout<<"Antiproton has been created !!!"<<G4endl;
        }
        else{
            fParticleChange.ProposeTrackStatus(trackData.GetTrackStatus());
        }

        return &fParticleChange;
    }

G4bool COMETAntiprotonProduction::CheckCondition(const G4Step& aStep){
    G4bool condition = false;
    if(aStep.GetTrack()->GetParticleDefinition()->GetPDGEncoding()==2212){
        condition = true;
    }
    return condition;
}

G4double COMETAntiprotonProduction::GetMeanFreePath(const G4Track& track, G4double, G4ForceCondition* /*condition*/){
    //*condition = Forced;
    
    Double_t Mproton = proton->GetPDGMass()/GeV;

    const G4DynamicParticle* DynamicParticle = track.GetDynamicParticle();
    G4LorentzVector beam_G4 = DynamicParticle->Get4Momentum();
    TLorentzVector beam(beam_G4.px()/GeV, beam_G4.py()/GeV, beam_G4.pz()/GeV, beam_G4.e()/GeV);

    Double_t TargetMomentum = FermiMomentum->GetRandom(0.,1.);
    //Double_t TargetMomentum = 0.;

    Double_t x,y,z;
    random->Sphere(x,y,z,TargetMomentum);
    G4LorentzVector target_G4 = G4LorentzVector(x*1000, x*1000, y*1000, sqrt(TargetMomentum*TargetMomentum+Mproton*Mproton)*1000);

    target = TLorentzVector(x,y,z,sqrt(TargetMomentum*TargetMomentum+Mproton*Mproton));

    TLorentzVector W = beam+target;
    v_lab = W.Vect();
    Double_t ratio = v_lab.Mag()/W.Beta();
    v_lab.SetX(W.Px()/ratio);
    v_lab.SetY(W.Py()/ratio);
    v_lab.SetZ(W.Pz()/ratio);
    TLorentzVector W_cms = W;
    W_cms.Boost(-v_lab);

    G4double sqrt_S = W_cms.E();
    //G4cout<<"sqrt_S: "<<sqrt_S<<G4endl;

    G4double MicroCrossSection = 1e10*fCHCrossSection->GetMicroCrossSection(sqrt_S);
    //G4cout<<"MicroCrossSection: "<<MicroCrossSection<<G4endl;

    G4Material* mat = track.GetMaterial();
    G4double NofProton = (mat->GetDensity()/(g/cm3))*Avogadro*(mat->GetZ()/(mat->GetA()/(g/mole)));
    G4double MacroCrossSection = NofProton*MicroCrossSection*1e-27;
    //G4cout<<"MacroCrossSection: "<<MacroCrossSection<<G4endl;

    G4double MeanFreePath = 10/MacroCrossSection;

    return MeanFreePath;
}

void COMETAntiprotonProduction::PrepareSecondary(const G4Track& track){
    Secondary1 = new G4Track(DP1,track.GetGlobalTime(),track.GetPosition());
    Secondary2 = new G4Track(DP2,track.GetGlobalTime(),track.GetPosition());
    Secondary3 = new G4Track(DP3,track.GetGlobalTime(),track.GetPosition());
    Secondary4 = new G4Track(DP4,track.GetGlobalTime(),track.GetPosition());
}

void COMETAntiprotonProduction::GetDatas(const G4Step* aStep){

    G4Track* track = aStep->GetTrack();
    const G4DynamicParticle* DynamicParticle = track->GetDynamicParticle();

    G4LorentzVector beam_G4 = DynamicParticle->Get4Momentum();
    TLorentzVector beam(beam_G4.px()/GeV, beam_G4.py()/GeV, beam_G4.pz()/GeV, beam_G4.e()/GeV);

    Double_t mass[4] = {0.938,0.938,0.938,0.938};
    TLorentzVector W = beam+target;
    TGenPhaseSpace event;
    event.SetDecay(W, 4, mass);
    Double_t weight = event.Generate();
    TLorentzVector* pProton1 = event.GetDecay(0);
    TLorentzVector* pProton2 = event.GetDecay(1);
    TLorentzVector* pProton3 = event.GetDecay(2);
    TLorentzVector* pAntiproton = event.GetDecay(3);

    //////////////////////////////////
    TLorentzVector pAntiproton_cms = *pAntiproton;
    pAntiproton_cms.Boost(-v_lab);
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
    analysisManager->FillNtupleDColumn(0, pAntiproton_cms.Px());
    analysisManager->FillNtupleDColumn(1, pAntiproton_cms.Py());
    analysisManager->FillNtupleDColumn(2, pAntiproton_cms.Pz());
    analysisManager->FillNtupleDColumn(6, pAntiproton_cms.P());
    analysisManager->AddNtupleRow();
    //////////////////////////////////

    G4LorentzVector Proton1(pProton1->Px()*GeV,pProton1->Py()*GeV,pProton1->Pz()*GeV,pProton1->E()*GeV);
    G4LorentzVector Proton2(pProton2->Px()*GeV,pProton2->Py()*GeV,pProton2->Pz()*GeV,pProton2->E()*GeV);
    G4LorentzVector Proton3(pProton3->Px()*GeV,pProton3->Py()*GeV,pProton3->Pz()*GeV,pProton3->E()*GeV);
    G4LorentzVector Antiproton(pAntiproton->Px()*GeV,pAntiproton->Py()*GeV,pAntiproton->Pz()*GeV,pAntiproton->E()*GeV);

    DP1 = new G4DynamicParticle(proton,Proton1);
    DP2 = new G4DynamicParticle(proton,Proton1);
    DP3 = new G4DynamicParticle(proton,Proton1);
    DP4 = new G4DynamicParticle(anti_proton,Antiproton);
}

