#ifndef COMETHistoManager_h
#define COMETHistoManager_h 1

#include "Custom.hh"

#include "globals.hh"
#include "G4Track.hh"
#include "G4VProcess.hh"

#include "COMETParameters.hh"

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
    void OpenFile(std::string name);
    void CreateTree(std::string name);
    void Write();
    void Close();
    void SetValuePre(const G4Track* track);
    void SetSDHit(G4Step* step);

    template<typename ItemType>
    void SetBranch(std::string name, ItemType& item);
    inline bool IsBackward() const;

  private:

    static COMETHistoManager* fHistoManager;
    COMETParameters* fParameters;

    TFile* fTestRooFile;
    TTree*   fTestTree;

    vector<int> TrackID;
    vector<int> ParentID;
    vector<int> Pdg;

    vFV P;
    vFV Pos;
    vector<string> CreatorProcess;

    vFV detP;
    vFV detPos;

    bool backward;

};

template<typename ItemType>
void COMETHistoManager::SetBranch(std::string name, ItemType& item){
  fTestTree->Branch(name.c_str(), &item);
}

inline bool COMETHistoManager::IsBackward() const {
  return backward;
}

#endif
