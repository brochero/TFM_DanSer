//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Nov 11 19:21:03 2019 by ROOT version 6.12/07
// from TTree Events/Events
// found on file: TT_TuneCUETP8M2T4_13TeV-powheg-pythia8_6025F93B-D15B-0347-851C-EDA735AC040D_Skim.root
//////////////////////////////////////////////////////////

#ifndef NanoAODReader_h
#define NanoAODReader_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class NanoAOD {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.
   
   // Declaration of leaf types

   // Event 
   Int_t           event;
   Int_t           run;
   Int_t           lumiBlock;
   Float_t         rho;
   Int_t           nVertex;
   Int_t           passHLT;
   // PileUp
   Float_t         puWeight;
   Float_t         puWeightUp;
   Float_t         puWeightDown;

   // Jets
   UInt_t          jet_number;   
   Float_t         jet_raw_pt       [20];   //[nJet]
   Float_t         jet_pt           [20];   //[nJet]
   Float_t         jet_eta          [20];   //[nJet]
   Float_t         jet_phi          [20];   //[nJet]
   Float_t         jet_Et           [20];   //[nJet]
   Float_t         jet_E            [20];   //[nJet]
   Int_t           jet_IDTight      [20];   //[nJet]
   Int_t           jet_IDLepVeto    [20];   //[nJet]
   Float_t         jet_btagDeepCSV  [20];   //[nJet]
   Int_t           jet_partonFlavour[20];   //[nJet]
   Int_t           jet_hadronFlavour[20];   //[nJet]
   Float_t         jet_systUncVar   [20];   //[nJet]   
   // TEMPORAL:
   // For the new production from Anna (Nov/2021).
   Float_t         jet_genpt[20];   //[nJet]
   // SYSTEMATICS
   // SYS: JEC
   Float_t         jet_pt_JEC [27] [2] [20]; //[JES+JER] [Up,Dw] [nJet]
   

   // GenJets
   UInt_t  nGenJet;
   Float_t genjet_phi[20],genjet_E[20],genjet_pt[20],genjet_eta[20], genjet_flavour[20];

   // Muons
   UInt_t          muon_number;   
   Float_t         muon_pt       [3];   //[nMuon]
   Float_t         muon_eta      [3];   //[nMuon]
   Float_t         muon_phi      [3];   //[nMuon]
   Float_t         muon_E        [3];   //[nMuon]
   Int_t           muon_charge   [3];   //[nMuon]
   Float_t         muon_dxy      [3];   //[nMuon]
   Float_t         muon_dz       [3];   //[nMuon]
   Int_t           muon_isLoose  [3];   //[nMuon]
   Int_t           muon_isTight  [3];   //[nMuon]
   Float_t         muon_iso_pflow[3];   //[nMuon]

   // Electrons
   UInt_t          electron_number;   
   Float_t         electron_pt         [3];   //[nElectron] 
   Float_t         electron_etaSC      [3];   //[nElectron]
   Float_t         electron_eta        [3];   //[nElectron]
   Float_t         electron_phi        [3];   //[nElectron]
   Float_t         electron_E          [3];   //[nElectron]
   Int_t           electron_charge     [3];   //[nElectron]
   Float_t         electron_dxy        [3];   //[nElectron]
   Float_t         electron_dz         [3];   //[nElectron]
   Int_t           electron_isVetoCBID [3];   //[nElectron]
   Int_t           electron_isTightCBID[3];   //[nElectron]
   Int_t           electron_VID        [3];   //[nElectron]
   Float_t         electron_iso_pflow  [3];   //[nElectron]

   // MET
   Float_t         met_met;
   Float_t         met_metNoCorrFromJets;
   Float_t         met_phi;
   Float_t         met_sumEt;
   Float_t         met_px;
   Float_t         met_py;
   
   // MET Filters
   Float_t         metFilter_METFilters;
   Float_t         metFilter_HBHENoiseFilter;
   Float_t         metFilter_HBHENoiseIsoFilter;
   Float_t         metFilter_EcalDeadCellTriggerPrimitiveFilter;
   Float_t         metFilter_goodVertices;
   Float_t         metFilter_eeBadScFilter;
   Float_t         metFilter_globalSuperTightHalo2016Filter;
   Float_t         metFilter_BadPFMuonFilter;

   // GenWeights
   Float_t         genInfo_LHEWOrgXWGTUP;
   Float_t         genInfo_trueNumberOfInteractions;
   Float_t         genInfo_scalePDF;
   Float_t         genInfo_id2;
   Float_t         genInfo_id1;
   Float_t         genInfo_nLHEPart;
   Float_t         genInfo_x2;
   Float_t         genInfo_x1;
   Float_t         genInfo_MCWeight;
   Float_t         genInfo_ScaleWeights[9];
   UInt_t          nPSWeight;
   Float_t         genInfo_PSWeights[4];   //[nPSWeight]
   UInt_t          nLHEPdfWeight;
   Float_t         genInfo_PDFWeights[100];   //[nLHEPdfWeight]

   // GenLevel particles
   UInt_t          genParticles_number;   
   Int_t           genParticles_pdgId   [10];   //[nGenPart]
   Int_t           genParticles_status  [10];   //[nGenPart]
   Int_t           genParticles_motherId[10];   //[nGenPart]
   Float_t         genParticles_pt      [10];   //[nGenPart]
   Float_t         genParticles_eta     [10];   //[nGenPart]
   Float_t         genParticles_phi     [10];   //[nGenPart]
   Float_t         genParticles_E       [10];   //[nGenPart]
   // GenLevel top
   Int_t           topGenParticles_pdgId   [5];
   Int_t           topGenParticles_status  [5];
   Int_t           topGenParticles_motherId[5];
   Float_t         topGenParticles_pt      [5];
   Float_t         topGenParticles_eta     [5];
   Float_t         topGenParticles_phi     [5];
   Float_t         topGenParticles_E       [5];
   // GenLevel anti-top
   Int_t           topbarGenParticles_pdgId   [5];
   Int_t           topbarGenParticles_status  [5];
   Int_t           topbarGenParticles_motherId[5];
   Float_t         topbarGenParticles_pt      [5];
   Float_t         topbarGenParticles_eta     [5];
   Float_t         topbarGenParticles_phi     [5];
   Float_t         topbarGenParticles_E       [5];
   // Angles and weights for top
   Float_t         top_LepHad;
   Float_t         top_cosThKF;
   Float_t         top_rwF0KF;
   Float_t         top_rwFLKF;
   Float_t         top_rwFRKF;
   Float_t         top_cosThMlb;
   Float_t         top_rwF0Mlb;
   Float_t         top_rwFLMlb;
   Float_t         top_rwFRMlb;
   // Angles and weights for anti-top
   Float_t         topbar_LepHad;
   Float_t         topbar_cosThKF;
   Float_t         topbar_rwF0KF;
   Float_t         topbar_rwFLKF;
   Float_t         topbar_rwFRKF;
   Float_t         topbar_cosThMlb;
   Float_t         topbar_rwF0Mlb;
   Float_t         topbar_rwFLMlb;
   Float_t         topbar_rwFRMlb;

   // -------------------------------- //
   // -------------------------------- //
   // TList of branches
   // -------------------------------- //
   // -------------------------------- //
   // Event
   TBranch        *b_event;   
   TBranch        *b_run;   
   TBranch        *b_lumiBlock;   
   TBranch        *b_rho;   
   TBranch        *b_nVertex;   
   TBranch        *b_passHLT;   
   
   // PileUp
   TBranch        *b_puWeight;
   TBranch        *b_puWeightUp;
   TBranch        *b_puWeightDown;
   
   // Jets
   TBranch        *b_jet_number;   

   TBranch        *b_jet_raw_pt;   
   TBranch        *b_jet_pt;   
   TBranch        *b_jet_eta;   
   TBranch        *b_jet_phi;   
   TBranch        *b_jet_Et;   
   TBranch        *b_jet_E;   
   TBranch        *b_jet_IDTight;   
   TBranch        *b_jet_IDLepVeto;   
   TBranch        *b_jet_btagDeepCSV;   
   TBranch        *b_jet_partonFlavour;   
   TBranch        *b_jet_hadronFlavour;   
   TBranch        *b_jet_systUncVar;
   // TEMPORAL:
   // For the new production from Anna (Nov/2021).
   TBranch        *b_jet_genpt;
   // SYSTEMATICS
   // SYS: JEC
   TBranch        *b_jet_pt_JEC [27] [2]; //[JES+JER] [Up,Dw]

   // GenJets
   TBranch *b_nGenJet;
   TBranch *b_genjet_phi,*b_genjet_E,*b_genjet_pt,*b_genjet_eta;
   TBranch *b_genjet_flavour;

   // Muons
   TBranch        *b_muon_number;   
   TBranch        *b_muon_pt;   
   TBranch        *b_muon_eta;   
   TBranch        *b_muon_phi;   
   TBranch        *b_muon_E;   
   TBranch        *b_muon_charge;   
   TBranch        *b_muon_dxy;   
   TBranch        *b_muon_dz;   
   TBranch        *b_muon_isLoose;   
   TBranch        *b_muon_isTight;   
   TBranch        *b_muon_iso_pflow;   

   // Electrons
   TBranch        *b_electron_number;   
   TBranch        *b_electron_pt;   
   TBranch        *b_electron_etaSC;   
   TBranch        *b_electron_eta;   
   TBranch        *b_electron_phi;   
   TBranch        *b_electron_E;   
   TBranch        *b_electron_charge;   
   TBranch        *b_electron_dxy;   
   TBranch        *b_electron_dz;   
   TBranch        *b_electron_isVetoCBID;   
   TBranch        *b_electron_isTightCBID;   
   TBranch        *b_electron_VID;   
   TBranch        *b_electron_iso_pflow;   

   // MET
   TBranch        *b_met_met;   
   TBranch        *b_met_metNoCorrFromJets;   
   TBranch        *b_met_phi;   
   TBranch        *b_met_sumEt;   
   TBranch        *b_met_px;   
   TBranch        *b_met_py;   

   // MET Filters
   TBranch        *b_metFilter_METFilters;   
   TBranch        *b_metFilter_HBHENoiseFilter;   
   TBranch        *b_metFilter_HBHENoiseIsoFilter;   
   TBranch        *b_metFilter_EcalDeadCellTriggerPrimitiveFilter;   
   TBranch        *b_metFilter_goodVertices;   
   TBranch        *b_metFilter_eeBadScFilter;   
   TBranch        *b_metFilter_globalSuperTightHalo2016Filter;   
   TBranch        *b_metFilter_BadPFMuonFilter;   

   // GenWeights
   TBranch        *b_genInfo_LHEWOrgXWGTUP;   
   TBranch        *b_genInfo_trueNumberOfInteractions;   
   TBranch        *b_genInfo_scalePDF;   
   TBranch        *b_genInfo_id2;   
   TBranch        *b_genInfo_id1;   
   TBranch        *b_genInfo_nLHEPart;   
   TBranch        *b_genInfo_x2;   
   TBranch        *b_genInfo_x1;   
   TBranch        *b_genInfo_MCWeight;   
   TBranch        *b_genInfo_ScaleWeights;   
   TBranch        *b_nPSWeight;   
   TBranch        *b_genInfo_PSWeights;   
   TBranch        *b_nLHEPdfWeight;   
   TBranch        *b_genInfo_PDFWeights;   

   // GenLevel particles
   TBranch        *b_genParticles_number;   
   TBranch        *b_genParticles_pdgId;   
   TBranch        *b_genParticles_status;   
   TBranch        *b_genParticles_motherId;   
   TBranch        *b_genParticles_pt;   
   TBranch        *b_genParticles_eta;   
   TBranch        *b_genParticles_phi;   
   TBranch        *b_genParticles_E;   
   // GenLevel top
   TBranch        *b_topGenParticles_pdgId;   
   TBranch        *b_topGenParticles_status;   
   TBranch        *b_topGenParticles_motherId;   
   TBranch        *b_topGenParticles_pt;   
   TBranch        *b_topGenParticles_eta;   
   TBranch        *b_topGenParticles_phi;   
   TBranch        *b_topGenParticles_E;   
   // GenLevel anti-top
   TBranch        *b_topbarGenParticles_pdgId;   
   TBranch        *b_topbarGenParticles_status;   
   TBranch        *b_topbarGenParticles_motherId;   
   TBranch        *b_topbarGenParticles_pt;   
   TBranch        *b_topbarGenParticles_eta;   
   TBranch        *b_topbarGenParticles_phi;   
   TBranch        *b_topbarGenParticles_E;   
   // Angles and weights for top 
   TBranch        *b_top_LepHad;   
   TBranch        *b_top_cosThKF;   
   TBranch        *b_top_rwF0KF;   
   TBranch        *b_top_rwFLKF;   
   TBranch        *b_top_rwFRKF;   
   TBranch        *b_top_cosThMlb;   
   TBranch        *b_top_rwF0Mlb;   
   TBranch        *b_top_rwFLMlb;   
   TBranch        *b_top_rwFRMlb;   
   // Angles and weights for anti-top
   TBranch        *b_topbar_LepHad;   
   TBranch        *b_topbar_cosThKF;   
   TBranch        *b_topbar_rwF0KF;   
   TBranch        *b_topbar_rwFLKF;   
   TBranch        *b_topbar_rwFRKF;   
   TBranch        *b_topbar_cosThMlb;   
   TBranch        *b_topbar_rwF0Mlb;   
   TBranch        *b_topbar_rwFLMlb;   
   TBranch        *b_topbar_rwFRMlb;   

   TString JESVar;

   NanoAOD(TTree *tree=0, TString b_Syst="", bool IsMC = false, bool IsTop = false);
   virtual ~NanoAOD();
   virtual void     Init(TTree *tree, TString b_Syst, bool IsMC, bool IsTop);
   virtual Bool_t   Notify();
};

#endif
