#ifndef COMETRandomSvc_h
#define COMETRandomSvc_h 1

#include "TRandom.h"

class COMETRandomSvc{

    public:
    COMETRandomSvc();

    static COMETRandomSvc* GetRandomSvc();
    void SetRandomSeedROOT(int seed);
    void SetRandomSeedG4(int seed);
    static TRandom* GetRandomROOT();

    private:
    static COMETRandomSvc* fRandomSvc;
    static TRandom* fRandomROOT;

};

#endif