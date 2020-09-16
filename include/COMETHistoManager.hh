#ifndef COMETHistoManager_h
#define COMETHistoManager_h 1
#endif

#include "globals.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class TFile;
class TTree;
class TVector3;

class COMETHistoManager{
    public:
    COMETHistoManager();
   ~COMETHistoManager();

    void Book();
    void Save();

    void FillNtuple(G4int pdg, TVector3* momentum);

  private:
    TFile*   fRootFile;
    TTree*   fNtuple;
    G4int fPdg;
    TVector3* fMomentum;
};
