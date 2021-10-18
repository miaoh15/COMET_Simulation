#include "COMETRandomSvc.hh"
#include "G4RandomTools.hh"

using namespace std;

COMETRandomSvc* COMETRandomSvc::fRandomSvc = 0;
TRandom* COMETRandomSvc::fRandomROOT = 0;

COMETRandomSvc::COMETRandomSvc(){
    fRandomSvc = this;

    fRandomROOT = new TRandom();
    fRandomROOT->SetSeed(clock());

    G4Random::setTheSeed(clock());
}

COMETRandomSvc* COMETRandomSvc::GetRandomSvc(){
    if(!fRandomSvc){
        fRandomSvc = new COMETRandomSvc();
    }
    return fRandomSvc;
}

TRandom* COMETRandomSvc::GetRandomROOT(){
    if(!fRandomROOT){
        fRandomROOT = new TRandom();
        fRandomROOT->SetSeed(clock());
    }
    return fRandomROOT;
}

void COMETRandomSvc::SetRandomSeedG4(int seed){
    G4Random::setTheSeed(seed);
}

void COMETRandomSvc::SetRandomSeedROOT(int seed){
    fRandomROOT->SetSeed(seed);
}