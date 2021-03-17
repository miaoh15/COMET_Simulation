#ifndef COMETHistoManager_h
#define COMETHistoManager_h 1

#include "globals.hh"
#include "G4Track.hh"
#include "G4VProcess.hh"

#include <vector>
#include <string>

using namespace std;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class TFile;
class TTree;
class TVector3;

class COMETHistoManager{
    public:
    COMETHistoManager();
   ~COMETHistoManager();

    static COMETHistoManager* GetHistoManager();
    void ClearVector();
    void SetBranch();
    void Fill();
    void SetBranch(std::string name, std::vector<double>* pVecD);
    void SetBranch(std::string name, std::vector<int>* pVecI);
    void SetBranch(std::string name, std::vector<string>* pVecS);
    void OpenFile(std::string name);
    void CreateTree(std::string name);
    void Write();
    void Close();
    void SetValuePre(const G4Track* track);

  private:

    static COMETHistoManager* fHistoManager;

    TFile* fTestRooFile;
    TTree*   fTestTree;

    vector<int> TrackID;
    vector<int> ParentID;
    vector<int> Pdg;
    vector<double> Px;
    vector<double> Py;
    vector<double> Pz;
    vector<double> Posx;
    vector<double> Posy;
    vector<double> Posz;
    vector<string> CreatorProcess;
};

#endif
