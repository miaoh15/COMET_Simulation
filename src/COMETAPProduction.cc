#include "COMETAPProduction.hh"
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

COMETAPProduction::COMETAPProduction( const G4String& name, G4ProcessType aType)
    : G4VDiscreteProcess(name,aType){
    particleTable = G4ParticleTable::GetParticleTable();
    proton = particleTable->FindParticle("proton");
    anti_proton = particleTable->FindParticle("anti_proton");

    fCHCrossSection = new COMETCHCrossSection(anti_proton);

    FermiMomentum = new TF1("fermi_momentum","(x<[1])*[0]+(x>[1])*[3]*pow([4]/[3],(x-[1])/([2]-[1]))",0.,1.);
    FermiMomentum->SetParameters(1,0.24,0.8,2e-2,4.5e-4);

    random = new TRandom();
    random->SetSeed(clock());

    ifstream MDCS("/home/miaomiao/work/COMET-alpha/data/APPMaxDCS.txt");
    string line;
    vector<string> MaxDCSStore_str;

    if(MDCS){
        while(getline(MDCS, line)){
            MaxDCSStore_str.push_back(line);
        }
    }

    string::size_type size;

    for(G4int i=0; i<MaxDCSStore_str.size(); i++){
        string temp = MaxDCSStore_str.at(i);
        string::size_type temp_pos = temp.find("    ");
        string sqrt_S_str = temp.substr(0, temp_pos);
        G4double sqrt_S_d = stod(sqrt_S_str, &size);
        string temp_MCS_str = temp.substr(temp_pos);
        temp_MCS_str.erase(remove(temp_MCS_str.begin(),temp_MCS_str.end(),' '), temp_MCS_str.end());
        G4double MCS = stod(temp_MCS_str, &size);
        MaxDCSStore.push_back(MCS);
        sqrt_S.push_back(sqrt_S_d);
    }

    upper = 112.*TMath::Pi()/180.;
    lower = 92.*TMath::Pi()/180.;
}

COMETAPProduction::~COMETAPProduction(){
}

G4VParticleChange* COMETAPProduction::PostStepDoIt(const G4Track& trackData,
    const G4Step& aStep){
        fParticleChange.Initialize(trackData);

        if(CheckCondition(aStep)){
            GetDatas(&aStep);
            if(tag == true){
                PrepareSecondary(trackData);

                fParticleChange.AddSecondary(Secondary1);
                fParticleChange.ProposeTrackStatus(fStopAndKill);
                //G4cout<<"Antiproton has been created !!!"<<G4endl;
            }
            else{
                fParticleChange.ProposeTrackStatus(trackData.GetTrackStatus());
            }
        }
        else{
            fParticleChange.ProposeTrackStatus(trackData.GetTrackStatus());
        }
        return &fParticleChange;
    }

G4bool COMETAPProduction::CheckCondition(const G4Step& aStep){
    G4bool condition = false;
    if(aStep.GetTrack()->GetParticleDefinition()->GetPDGEncoding()==2212){
        condition = true;
    }
    return condition;
}

G4double COMETAPProduction::GetMeanFreePath(const G4Track& track, G4double, G4ForceCondition* /*condition*/){
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

    fSqrt_S = W_cms.E();

    G4double MicroCrossSection = 1e7*fCHCrossSection->GetMicroCrossSection(fSqrt_S);
    //G4cout<<"MicroCrossSection: "<<MicroCrossSection<<G4endl;

    G4Material* mat = track.GetMaterial();
    G4double NofProton = (mat->GetDensity()/(g/cm3))*Avogadro*(mat->GetZ()/(mat->GetA()/(g/mole)));
    //std::cout<<"Z: "<<mat->GetZ()<<"A: "<<mat->GetA()<<std::endl;
    G4double MacroCrossSection = NofProton*MicroCrossSection*1e-27;
    //G4cout<<"MacroCrossSection: "<<MacroCrossSection<<G4endl;

    G4double MeanFreePath = 10/MacroCrossSection;
    //G4cout<<"MeanFreePath: "<<MeanFreePath/mm<<G4endl;

    return MeanFreePath;
}

void COMETAPProduction::PrepareSecondary(const G4Track& track){
    Secondary1 = new G4Track(DP1,track.GetGlobalTime(),track.GetPosition());
}

void COMETAPProduction::GetDatas(const G4Step* aStep){

    G4Track* track = aStep->GetTrack();
    const G4DynamicParticle* DynamicParticle = track->GetDynamicParticle();

    G4LorentzVector beam_G4 = DynamicParticle->Get4Momentum();
    TLorentzVector beam(beam_G4.px()/GeV, beam_G4.py()/GeV, beam_G4.pz()/GeV, beam_G4.e()/GeV);

    G4double Mproton = proton->GetPDGMass()/GeV;
    G4double Emax = (fSqrt_S*fSqrt_S-Mx*Mx+Mproton*Mproton)/(2*fSqrt_S);
    G4double pmax = sqrt(Emax*Emax-Mproton*Mproton);
    G4double p = random->Uniform(0., pmax);
    G4double theta = random->Uniform(0., pi);
    G4double MaxDCS = GetMaxDCS(fSqrt_S);
    G4double DifferentialCrossSection = random->Uniform(0.,MaxDCS);
    //G4cout<<"DCS: "<<ComputeDCS(p, theta, fSqrt_S)*p*p*sin(theta)*2*pi<<G4endl;

    while(DifferentialCrossSection>=ComputeDCS(p, theta, fSqrt_S)*p*p*sin(theta)*2*pi){
        p = random->Uniform(0., pmax);
        theta = random->Uniform(0., pi);
        DifferentialCrossSection = random->Uniform(0.,MaxDCS);
    }

    G4double phi = random->Uniform(0., 2*pi);

    TLorentzVector pAntiproton(p*sin(theta)*cos(phi),p*sin(theta)*sin(phi), p*cos(theta), sqrt(p*p+Mproton*Mproton));

    //////////////////////////////////
    /*G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
    analysisManager->FillNtupleDColumn(0, pAntiproton.Px());
    analysisManager->FillNtupleDColumn(1, pAntiproton.Py());
    analysisManager->FillNtupleDColumn(2, pAntiproton.Pz());
    analysisManager->FillNtupleDColumn(6, pAntiproton.P());
    analysisManager->AddNtupleRow();*/
    //////////////////////////////////

    pAntiproton.Boost(v_lab);

    if(!(pAntiproton.Theta()>lower&&pAntiproton.Theta()<upper)) {
        tag = false;
        return;
    }
    else tag = true;

    G4LorentzVector Antiproton(pAntiproton.Px()*GeV,pAntiproton.Py()*GeV,pAntiproton.Pz()*GeV,pAntiproton.E()*GeV);

    DP1 = new G4DynamicParticle(anti_proton,Antiproton);
}

G4double COMETAPProduction::GetMaxDCS(G4double sqrt_S_now){
    if(sqrt_S_now<3.7525) return 0.;

    G4double upper_limit = 0., lower_limit = 0., upper_MCS = 0., lower_MCS = 0.;
    G4double MicroCrossSection = 0.;

    string::size_type size;

    for(G4int i=0; i<sqrt_S.size(); i++){
        lower_limit = sqrt_S.at(i);
        upper_limit = sqrt_S.at(i+1);
        if(!(lower_limit<sqrt_S_now && upper_limit>sqrt_S_now)) continue;
        else{
            lower_MCS = MaxDCSStore.at(i);
            upper_MCS = MaxDCSStore.at(i+1);

            break;
        }
    }

    MicroCrossSection = exp(log(lower_MCS)+(log(upper_MCS)-log(lower_MCS))*((sqrt_S_now-lower_limit)/(upper_limit-lower_limit)));

    return MicroCrossSection;
}

G4double COMETAPProduction::ComputeDCS(G4double p, G4double Theta, G4double Ecms){

    //Fundamental parameters
    G4double pt = p*sin(Theta);
    G4double Mproton = 0.938;
    G4double Emax = (Ecms*Ecms-Mx*Mx+Mproton*Mproton)/(2*Ecms);

    G4double E = sqrt(Mproton*Mproton+p*p);
    G4double X_r = E/Emax;
    G4double X_m = Mproton/Emax;
    G4double X_t = (X_r-X_m)/(1.-X_m);
    G4double Q = Ecms-sqrt_St;

    //Compute Differential Cross Section
    const G4double a[13] = {3.15,  1.05e-4,    10.1,   0.5,    7.90,   0.465,   3.7e-2, 2.31,   1.4e-2, 3.02e-2,    3.19,   0.399,  8.39};
    const G4double b[10] = {0.,   0.306, 0.120,      0.0552, 2.72,   0.758,  -0.680, 1.54,   0.594,  2.87};
    G4double ICS_RS, f, A, B, theta;
    G4double P_t = pt;
    if ((a[3]-X_r)<0) theta = 0.;
    else theta = 1;
    f = a[1]*exp(-a[2]*X_r)*theta+(a[0]-a[1])*pow((1-X_r),a[4]);
    A = a[5]*exp(-a[6]*X_r)+a[7]*exp(a[8]*X_r);
    B = a[9]*exp(-a[10]*(X_r+a[11]))*pow((X_r+a[11]),a[12]);
    ICS_RS = f*exp(-(A*P_t+B*P_t*P_t));

    if(Ecms>10.) return ICS_RS/E;

    else{
        G4double ICS_LE, R_reciprocal, A_R, B_R, C_R, D_R;
        A_R = b[1]*exp(-b[2]*X_t);
        B_R = b[3]*exp(b[4]*X_t);
        C_R = b[5]+b[6]*X_t+b[7]*X_t*X_t;
        D_R = b[8]*exp(b[9]*X_t);
        R_reciprocal = 1-exp(-(1-exp(-A_R*pow(Q,B_R)))*exp(C_R*Q-D_R));
        ICS_LE = ICS_RS*(1/R_reciprocal);

        return ICS_LE/E;
    }
}
