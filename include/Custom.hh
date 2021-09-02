#ifndef Custom_h
#define Custom_h
#pragma once

// ROOT
#include "Math/Vector4D.h"
#include "TVector3.h"
#include "TFile.h"
#include "TMath.h"
#include "TTree.h"
#include "TVectorT.h"

typedef ROOT::Math::XYZTVector FV;
typedef std::vector<FV> vFV;

typedef std::vector<Int_t> vInt;
typedef TVectorT<Double_t> vDbl;
typedef std::vector<int> vint;
typedef std::vector<double> vdbl;

typedef std::vector<bool> vbool;
typedef std::vector<vbool> vvbool;
typedef unsigned int nint;
typedef std::vector<nint> vnint;
typedef std::vector<vint> vvint;
typedef std::vector<vdbl> vvdbl;

typedef std::string str;
typedef std::vector<std::string> vstr;

// CLHEP
#include "CLHEP/Vector/LorentzVector.h"
#include "CLHEP/Vector/ThreeVector.h"

typedef CLHEP::HepLorentzVector HepLV;
typedef std::vector<HepLV> vHepLV;

typedef CLHEP::Hep3Vector Hep3V;
typedef std::vector<Hep3V> vHep3V;

#endif /* OMEGAXIK_UTIL_CUSTOM_HPP */
