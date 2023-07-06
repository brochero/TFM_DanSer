#include "TFile.h"
#include "TH1.h"
#include "TString.h"
#include "HistoModifier.h"

const std::vector<TString> ChName  = {"mujets","ejets"};

const std::vector<TString> RegName = {"2j2b"
				      ,"3j2b","3j3b"
				      ,"4j2b","4jge3b"
				      ,"ge5ge2b"
				      ,"3j3bplus4jge3b"
				      ,"3j2bplus3j3b"
				      ,"4j2bplus4jge3b"
				      ,"4j2bplus4jge3bplusge5ge2b"
				      ,"4j2bplusge5ge2b"
				      ,"3j2bplus3j3bplus4j2bplus4jge3bplusge5ge2b"
                                     };


const std::vector<TString> Samples = {
  "ttbarSgn-F0_LepJets",
  "ttbarSgn-FL_LepJets",
  "ttbarSgn-FR_LepJets",
  "ttbarBkg",
  "WJetsaMCatNLO",
  "stSgn-F0_tch",
  "stSgn-FL_tch",
  "stSgn-FR_tch",
  "stSgn-F0_tW",
  "stSgn-FL_tW",
  "stSgn-FR_tW",
  "ttbarSgn_LepJets_SYS",
  "stSgn_tch",
  "stSgn_tW",
  "st_sch",
  //"QCDDD",
  "ZJets",
  "VV",
  "ttV",
  "ttH",
  "DataSingleLepton"};

const std::vector<TString> SysVar  = {"Up","Down"};
const std::vector<TString> SysName = {
  "PileUp"
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
  ,"jet_JER"
  ,"ScPS_ISR","ScPS_FSR"
  ,"ScME"
};


void FileReader (TString BaseName, TString OutVersion, TString Sample, TString Histo, bool IsSyst=true, float SF_ttbar=1.,TString Year = "2016", bool DoToppT = false);

void DataModifier (TString BaseName, TString OutVersion, TString Histo, bool IsRandom, float SF_ttbar=1., float SF_ST=1., TString Scenario="");

/* void AddJESQuadrature (TH1D *Inp, TH1D*Nom, TH1D *Var){ */
/*   // Function based on the SYMMETRIZATION of JES */
/*   for (int ib=1;ib<=Inp->GetNbinsX();ib++){ */

/*     Inp->SetBinContent(ib, */
/* 		       sqrt((Inp->GetBinContent(ib)*Inp->GetBinContent(ib)) + */
/* 			    (Var->GetBinContent(ib)*Var->GetBinContent(ib))));     */

/*   }   */
/* } */


