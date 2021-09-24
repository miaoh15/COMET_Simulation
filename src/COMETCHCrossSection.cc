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

        string line;

        vector<string> CrossSectionStore_str;

        if(CS){
            while(getline(CS, line)){
                CrossSectionStore_str.push_back(line);
            }
        }

        string::size_type size;

        for(G4int i=0; i<CrossSectionStore_str.size(); i++){
            string temp = CrossSectionStore_str.at(i);
            string::size_type temp_pos = temp.find("    ");
            string sqrt_S_str = temp.substr(0, temp_pos);
            G4double sqrt_S_d = stod(sqrt_S_str, &size);
            string temp_MCS_str = temp.substr(temp_pos);
            temp_MCS_str.erase(remove(temp_MCS_str.begin(),temp_MCS_str.end(),' '), temp_MCS_str.end());
            G4double MCS = stod(temp_MCS_str, &size);
            CrossSectionStore.push_back(MCS);
            sqrt_S.push_back(sqrt_S_d);
        }
    }
}

COMETCHCrossSection::~COMETCHCrossSection(){}

G4double COMETCHCrossSection::GetMicroCrossSection(G4double sqrt_S_now){

    if(sqrt_S_now<=4.8325) return 1e-40;

    G4double upper_limit = 0., lower_limit = 0., upper_MCS = 0., lower_MCS = 0.;
    G4double MicroCrossSection = 0.;

    string::size_type size;

    for(G4int i=0; i<sqrt_S.size(); i++){
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