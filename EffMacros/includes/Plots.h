#ifndef __PLOTTER__
#define __PLOTTER__

#include "TH1.h"
#include "TH2.h"
#include "THStack.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TDirectory.h"
#include "TStyle.h"
#include "TSystem.h"
#include "TString.h"
#include "TDirectory.h"
#include "TROOT.h"
#include "TObject.h"
#include "TLegend.h"

#include "tdrstyle.C"

// ------------------------------------------------------------------
// Run tags
// ------------------------------------------------------------------

// QCD For systematics
/* TString Ref     = "BDTCutIsoMu25OctToppTNewRange3D-v0"; */
/* TString TreeRef = "QCDDDBDTwithDR-v0"; */
/* TString Ref     = "BDTCutIsoMu25LegacyQCDDD-v1"; */
/* TString TreeRef = "FitJanQCDDD-v1"; */
// Std
TString Ref     = "Legacy-v1";
TString TreeRef = "FitJan-v1";

int     DataYear = 2017;
TString fl       = Ref+"_"+TreeRef+"_FullSelStep_FNano" + TString::Format("%i",DataYear) + "-v7";
// TString fl       = Ref+"_"+TreeRef+"_FullSelStepQCD_FNano" + TString::Format("%i",DataYear) + "-v7";
// QCD For systematics
// TString fl       = Ref+"_FNano" + TString::Format("%i",DataYear) + "-v7";
// ------------------------------------------------------------------
// ------------------------------------------------------------------

// ------------------------------------------------------------------
// BDT Cut
// ------------------------------------------------------------------
float BDTCut = 0.08;
// ------------------------------------------------------------------

TString dirnameIn = "../HistoResult/"+Ref+"/";
TString files     = dirnameIn + fl;

typedef struct histos{
  TH1D     *hist[3]  ={0,0,0}; 
  TH1D     *Up[3]    ={0,0,0}; 
  TH1D     *Dw[3]    ={0,0,0}; 
  THStack  *mc[3]    ={0,0,0};
  TH2D     *hist2D[3]={0,0,0}; 
  TString units;
} histos;

// Channels
/* std::vector<TString> channel  = {"mujets",  "ejets", "all"}; */
/* std::vector<TString> Label_ch = {"#mu+jets","e+jets","l+jets"}; */
// For QCD-DD
std::vector<TString> channel  = {"mujets",  "ejets"};
std::vector<TString> Label_ch = {"#mu+jets","e+jets"};

// Alpha color
Int_t chatch  = 1756;
TColor *color = new TColor(chatch, 0.3, 0.5, 0.7, "", 0.55); // alpha = 0.45
// Alpha color
Int_t chatchTot  = 2000;
TColor *colorTot = new TColor(chatchTot, 0.0, 0.6, 0.1, "", 0.25); // alpha = 0.45

// Colors
int col_ttbar    = TColor::GetColor("#ff0000");
//int col_ttbarFR  = TColor::GetColor("#ff7a7a");
int col_ttbarFR  = TColor::GetColor("#230fff");
int col_ttbarFL  = TColor::GetColor("#ff9000");
int col_ttbarF0  = TColor::GetColor("#fc0000");

int col_ST_tch   = TColor::GetColor("#ff00ff");
int col_ST_tchFL = TColor::GetColor("#ff00ff");
int col_ST_tchF0 = TColor::GetColor("#ff00ff");
int col_ST_tchFR = TColor::GetColor("#ff00ff");

int col_ST_sch   = TColor::GetColor("#00ff5e");

int col_ST_tW    = TColor::GetColor("#9500ff");
int col_ST_tWFL  = TColor::GetColor("#9500ff");
int col_ST_tWF0  = TColor::GetColor("#9500ff");
int col_ST_tWFR  = TColor::GetColor("#9500ff");

int col_ttBkg  = TColor::GetColor("#00e5ff");
int col_WJets  = TColor::GetColor("#33cc33");
int col_ZJets  = TColor::GetColor("#3366ff");
int col_QCD    = TColor::GetColor("#ffff00");
int col_VV     = TColor::GetColor("#ffffff");
int col_ttV    = TColor::GetColor("#e75c8d");
int col_ttH    = TColor::GetColor("#e5c4f4");

// Systematic uncertainties names
std::vector<TString> SysNames = {"PileUp"
				 ,"LepSF","TrgSF"
				 ,"jet_btaghf","jet_btaghfstats1","jet_btaghfstats2"
				 ,"jet_btaglf","jet_btaglfstats1","jet_btaglfstats2"
				 ,"jet_btagcferr1","jet_btagcferr2"
				 ,"jet_JESAbsoluteStat","jet_JESAbsoluteScale","jet_JESAbsoluteMPFBias"
				 ,"jet_JESFragmentation"
				 ,"jet_JESSinglePionECAL","jet_JESSinglePionHCAL"
				 ,"jet_JESFlavorQCD"
				 ,"jet_JESTimePtEta"
				 ,"jet_JESRelativeJEREC1","jet_JESRelativeJEREC2","jet_JESRelativeJERHF"
				 ,"jet_JESRelativePtBB","jet_JESRelativePtEC1","jet_JESRelativePtEC2","jet_JESRelativePtHF"
				 ,"jet_JESRelativeBal"
				 ,"jet_JESRelativeFSR"
				 ,"jet_JESRelativeStatFSR","jet_JESRelativeStatEC","jet_JESRelativeStatHF"
				 ,"jet_JESPileUpDataMC"
				 ,"jet_JESPileUpPtRef","jet_JESPileUpPtBB","jet_JESPileUpPtEC1","jet_JESPileUpPtHF"
				 ,"ScPS_ISR","ScPS_FSR"
				 ,"jet_JER"
				 ,"ScME"
};

std::vector<TString> ScMENames = {"ScME_RDownFDown","ScME_RDownFNom"
				 ,"ScME_RNomFDown", "ScME_RNomFUp"
				 ,"ScME_RUpFNom",   "ScME_RUpFUp"};

// Colors
int col_PileUp = TColor::GetColor("#00e5ff");
int col_LepSF  = TColor::GetColor("#2200ff");
int col_TrgSF  = TColor::GetColor("#0fd62a");
int col_btaghf = TColor::GetColor("#ff8c00");
int col_btaglf = TColor::GetColor("#d60f1c");
int col_btagcf = TColor::GetColor("#ba9568");
int col_JER    = TColor::GetColor("#a8b800");
int col_JES    = TColor::GetColor("#a7b041");
int col_ISR    = TColor::GetColor("#9000ff");
int col_FSR    = TColor::GetColor("#c06eff");
int col_ME     = TColor::GetColor("#ff6ebb");
int col_Tune   = TColor::GetColor("#00ff48");
int col_hdamp  = TColor::GetColor("#ff0084");

#endif
