#include <TFile.h>
#include <TTree.h>
#include <TVector3.h>
#include <CLHEP/Units/SystemOfUnits.h>

#include "COMETHistoManager.hh"
#include "G4UnitsTable.hh"

COMETHistoManager::COMETHistoManager()
:fRootFile(0), 
 fNtuple(0),
 fPdg(0),
 fMomentum(NULL)
 {
 }

COMETHistoManager::~COMETHistoManager()
{
  if (fRootFile) delete fRootFile;
}

void COMETHistoManager::Book()
{ 
  // Creating a tree container to handle histograms and ntuples.
  // This tree is associated to an output file.
  //
  G4String fileName = "data.root";
  fRootFile = new TFile(fileName,"RECREATE");
  if (! fRootFile) {
    G4cout << " COMETHistoManager::Book :" 
           << " problem creating the ROOT TFile "
           << G4endl;
    return;
  }

  // create 1st ntuple
  fNtuple = new TTree("Ntuple", "release");
  fNtuple->Branch("Pdg", &fPdg, "Pdg");
  fNtuple->Branch("Momentum", &fMomentum, "Momentum");
 
  G4cout << "\n----> Output file is open in " << fileName << G4endl;
}

void COMETHistoManager::Save()
{ 
  if (! fRootFile) return;
  
  fRootFile->Write();       // Writing the histograms to the file
  fRootFile->Close();       // and closing the tree (and the file)
  
  G4cout << "\n----> Histograms and ntuples are saved\n" << G4endl;
}

void COMETHistoManager::FillNtuple(G4int pdg, TVector3* momentum)
{
  fPdg = pdg;
  fMomentum = momentum;

  if (fNtuple) fNtuple->Fill();
}