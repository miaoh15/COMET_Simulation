#include "COMETCHCrossSection.hh"
#include "COMETDetectorConstruction.hh"

using namespace std;

COMETCHCrossSection::COMETCHCrossSection(G4ParticleDefinition* particle)
{
    fParameters = COMETParameters::GetParameters();
    if(particle->GetParticleName()=="anti_proton"){
        ifstream CS;

        if(fParameters->restrict_phase_space == false) CS = ifstream(fParameters->MCS);
        else CS = ifstream(fParameters->MCS_RPS);

        G4double tmp;

        if(CS){
            int i=0;
            while(!CS.eof()){
                CS >> tmp;
                if(i%2 == 0) sqrt_S.push_back(tmp);
                else if(i%2 == 1) CrossSectionStore.push_back(tmp);
                else cout<<"Error in read micro cross section !!!"<<endl;
                i++;
            }
        }
    }
}

COMETCHCrossSection::~COMETCHCrossSection(){}

G4double COMETCHCrossSection::GetMicroCrossSection(G4double sqrt_S_now){

    if(sqrt_S_now<=3.7525) return 1e-40;

    G4double upper_limit = 0., lower_limit = 0., upper_MCS = 0., lower_MCS = 0.;
    G4double MicroCrossSection = 0.;

    for(long unsigned int i=0; i<sqrt_S.size(); i++){
        lower_limit = sqrt_S.at(i);
        upper_limit = sqrt_S.at(i+1);
        if(!(lower_limit<sqrt_S_now && upper_limit>sqrt_S_now)) continue;
        else{
            lower_MCS = CrossSectionStore.at(i);
            upper_MCS = CrossSectionStore.at(i+1);

            break;
        }
    }

    if(lower_MCS == 0 && upper_MCS == 0) return 1e-40;

    MicroCrossSection = exp(log(lower_MCS)+(log(upper_MCS)-log(lower_MCS))*((sqrt_S_now-lower_limit)/(upper_limit-lower_limit)));

    return MicroCrossSection;
}
