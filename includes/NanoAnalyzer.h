#ifndef __NTUPLE__
#define __NTUPLE__

#include "TROOT.h"
#include "TSystem.h"
#include "TRint.h"
#include "TStyle.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TF1.h"
#include "TH1F.h"
#include "TH2F.h"
#include "THStack.h"
#include "TLatex.h"
#include "TTree.h"
#include "TNtuple.h"
#include "TLegend.h"
#include "TLine.h"
#include "TMath.h"
#include "iostream"
#include <X11/Xlib.h>
#include "TLorentzVector.h"
#include "Math/Vector4D.h"
#include "Math/Vector3D.h"
#include <Math/VectorUtil.h>
#include "Math/GenVector/LorentzVector.h"
#include "Math/GenVector/Boost.h"
#include <sys/stat.h>
#include "TStopwatch.h"

#include <vector>
#include <fstream>
#include <string>
#include <sstream>

#include <iostream>
#include <cmath>
#include <map>

#include <fstream>
#include <string>
#include <sstream>

#include <iostream>
#include <cmath>
#include <map>

#include "NanoAODReader.h"

#include "ObjectsDef.h"

#include "Corrections/btagSF/BTagCalibrationStandalone.h"


// Functions
// - Create collections
std::vector<NanoObj::Jet>      CreateJetCollection      (NanoAOD *InNano, unsigned int SystVar=0);
std::vector<NanoObj::Jet>      CreateJetCollectionForJEC(NanoAOD *InNano, unsigned int SystNam=0, unsigned int SysVar=0);
std::vector<NanoObj::Muon>     CreateMuonCollection     (NanoAOD *InNano, float Iso=0.25);
std::vector<NanoObj::Electron> CreateElectronCollection (NanoAOD *InNano);

// -- GenJets
std::vector<NanoObj::Jet>      CreateGenJetCollection      (NanoAOD *InNano);
void SelectAndCleanGenJets(std::vector<NanoObj::Jet> *jets, TLorentzVector Lepton);

// - Selectors
// -- Muons
std::vector<NanoObj::Muon> GetVetoMuons  (std::vector<NanoObj::Muon>  muons, float pT_min , float eta_max, float iso_wp);
std::vector<NanoObj::Muon> GetSelMuons   (std::vector<NanoObj::Muon> *muons, float pT_min , float eta_max, float iso_wp);
std::vector<NanoObj::Muon> GetTightMuons (std::vector<NanoObj::Muon>  muons, float pT_min , float eta_max, float iso_wp);
std::vector<NanoObj::Muon> GetMuonsForQCD(std::vector<NanoObj::Muon>  muons, float pT_min , float eta_max, bool IsIso);
// -- Electrons
std::vector<NanoObj::Electron> GetVetoElectrons   (std::vector<NanoObj::Electron>  electrons, float pT_min , float eta_max);
std::vector<NanoObj::Electron> GetSelElectrons    (std::vector<NanoObj::Electron> *electrons, float pT_min , float eta_max);
std::vector<NanoObj::Electron> GetTightElectrons  (std::vector<NanoObj::Electron>  electrons, float pT_min , float eta_max);
std::vector<NanoObj::Electron> GetElectronsForQCD (std::vector<NanoObj::Electron>  electrons, float pT_min , float eta_max, bool IsIso);
// -- Jets
void SelectAndCleanJets(std::vector<NanoObj::Jet> *jets, TLorentzVector Lepton, float pT_min , float eta_max);
// -- b-tagging
// --- From Nano
float GetbtagEvtWeightFromNanoAOD(std::vector<NanoObj::Jet> jets);
// --- From CSV files
float GetbtagEvtWeightFromCSV(BTagCalibrationReader Reader, std::vector<NanoObj::Jet> jets,
			      std::string SysbF = "central",
			      std::string SyscF = "central",
			      std::string SyslF = "central");

// - Scale Factors
// -- Lepton SF (ID, ISO and Trigger)
void ReadLeptonTriggerSF(TString fSFdir,    TH2F *hLepSF[2][3]);
void  GetSF             (TH2F *Histo,       int channel, float eta, float pT, float *SF, float *SF_err);
float LeptonSF          (TH2F *Histo[2][3], int channel, float eta, float pT, int SystVar); // SystVar[0=None, +1/-1=ID/ISO, +2/-2=Trigger]
// -- Luminosity
float SFLumi(TString filename, float Lumi, float NGenEvents);

// Tools
std::vector<TString> GetListOfFiles(TString FileName, TString FromOutside);

unsigned int GetGenChannel(int TopDecay, int TopBarDecay);


double computeThetaStar( ROOT::Math::PtEtaPhiEVector & lepP4,
                         ROOT::Math::PtEtaPhiEVector & topP4,
                         ROOT::Math::PtEtaPhiEVector & wP4,
                         ROOT::Math::PtEtaPhiEVector & bP4,
                         bool ThetaLepb = true);

inline double squareDouble( const double & val ){
  return val*val;
}

// ------------------------------------------------------
// Parameters
// ------------------------------------------------------ 

//Reference helicity fractions in the SM
const double F0_KF = 0.6952; // old choice was 0.6671
const double FL_KF = 0.3030; // old choice was 0.3325
const double FR_KF = 1. - F0_KF - FL_KF;
//Reference helicity fractions in the SM
const double F0_Mlb = 0.7010; //
const double FL_Mlb = 0.2984; //
const double FR_Mlb = 1. - F0_Mlb - FL_Mlb;

// Channels
struct ch {
  enum:unsigned int{mj=0,ej,all};
};

// Variation
struct var {
  enum:unsigned int{Nom=0,Up,Down};
};
const std::vector<TString> vVarNames = {"Nominal","Up","Down"};

// b-tag
// btag SF definition
typedef struct hbtag{
  TF1     *HF[5];    // 5 pT bins
  TF1     *LF[4][3]; // 4 pT 3 eta bins
  TF1     *CF[5];    // 5 pT bins
} hbtag;

typedef struct btagCollection{
  hbtag Central;
  hbtag SystJES[25][3]; // 25 JES Variations + Nominal(Empty) Up/Down
  hbtag Syst[8][3];     // 3 Nominal (LF) - 5 HF Variations + Nominal(Empty)  Up/Down
                        // 3 LF Variations - 5 Nominal (HF CF) + Nominal(Empty) Up/Down
}btagCollection;

// btag names (SAME ORDER THAN Jetbtag.cc vectors)
const std::vector<TString> vbtgNames = {"hf","hfstats1","hfstats2",
					"lf","lfstats1","lfstats2","cferr1","cferr2"};

// b-tag histo structure
const int dummypTHF_bin = 5, dummypTLF_bin = 4, dummyeta_bin = 3;
const double dummypTHF_binsize [dummypTHF_bin+1] = {20., 30., 50., 70., 100., 10000.};
const double dummypTLF_binsize [dummypTLF_bin+1] = {20., 30., 40., 60., 10000.};
const double dummyeta_binsize  [dummyeta_bin+1]  = {0., 0.8, 1.6, 2.4};

// Total number of JEC
const unsigned int nJEC   = 26; //JES 25 + JER 1 Up/Down(nominal is added later) 
const unsigned int nJECVar= 53; //JES 25 + JER 2 Up/Down(nominal is added as 1 variation ONLY Up) 
// JES names ordered as they were recorded in jes object
const std::vector<TString> vJESNames = {"AbsoluteStat","AbsoluteScale","AbsoluteMPFBias",
					"Fragmentation",
					"SinglePionECAL","SinglePionHCAL",
					"FlavorQCD",
					"TimePtEta",
					"RelativeJEREC1","RelativeJEREC2","RelativeJERHF",
					"RelativePtBB","RelativePtEC1","RelativePtEC2","RelativePtHF",
					"RelativeBal",
					"RelativeFSR",
					"RelativeStatFSR","RelativeStatEC","RelativeStatHF",
					"PileUpDataMC",
					"PileUpPtRef","PileUpPtBB","PileUpPtEC1","PileUpPtHF"};

// The order respects the index in weights vector FROM NANOAOD
// LHE scale variation weights (w_var / w_nominal)
// [0] is renscfact=0.5d0 facscfact=0.5d0
// [1] is renscfact=0.5d0 facscfact=1d0
// [2] is renscfact=0.5d0 facscfact=2d0
// [3] is renscfact=1d0 facscfact=0.5d0
// [4] is renscfact=1d0 facscfact=1d0
// [5] is renscfact=1d0 facscfact=2d0
// [6] is renscfact=2d0 facscfact=0.5d0
// [7] is renscfact=2d0 facscfact=1d0
// [8] is renscfact=2d0 facscfact=2d0
// 2 and 6 are unphysical anti-correlated variations = "RUpFDown" and "RDownFUp"
const std::vector<TString> vScMENames = {"RDownFDown","RDownFNom","RDownFUp",
					 "RNomFDown", "RNomFNom", "RNomFUp",
					 "RUpFDown",  "RUpFNom",  "RUpFUp"};


#endif

