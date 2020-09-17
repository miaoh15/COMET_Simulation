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

    void FillNtuple(G4int pdg, G4double momentumX, G4double momentumY, G4double momentumZ);

  private:
    TFile*   fRootFile;
    TTree*   fNtuple;
    int fPdg;
    double fMomentumX;
    double fMomentumY;
    double fMomentumZ;
};
