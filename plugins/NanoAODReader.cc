#include "NanoAODReader.h"
#include <iostream>

//#ifdef NanoAODReader_cxx
NanoAOD::NanoAOD(TTree *tree, TString b_Syst, bool IsMC, bool IsTop):fChain(0){

  // if parameter tree is not specified (or zero), connect the file
  // used to generate this class and read the Tree.
  if (tree == 0) {
    std::cout << "[ERROR]=Not tree available...." << std::endl;
    std::exit (0);
  }

  Init(tree, b_Syst, IsMC, IsTop);
}


NanoAOD::~NanoAOD(){
  delete fChain;
}

void NanoAOD::Init(TTree *tree, TString b_Syst, bool IsMC, bool IsTop){
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   // Event
   fChain->SetBranchAddress("event",     &event,     &b_event);
   fChain->SetBranchAddress("run",       &run,       &b_run);
   fChain->SetBranchAddress("lumiBlock", &lumiBlock, &b_lumiBlock);
   fChain->SetBranchAddress("rho",       &rho,       &b_rho);
   fChain->SetBranchAddress("nVertex",   &nVertex,   &b_nVertex);
   fChain->SetBranchAddress("passHLT",   &passHLT,   &b_passHLT);

   // PileUp
   fChain->SetBranchAddress("puWeight",     &puWeight,     &b_puWeight);
   fChain->SetBranchAddress("puWeightUp",   &puWeightUp,   &b_puWeightUp);
   fChain->SetBranchAddress("puWeightDown", &puWeightDown, &b_puWeightDown);

   // Jets
   fChain->SetBranchAddress("nJet", &jet_number, &b_jet_number);
   // -- Jets: Systematic uncertainties
   if(b_Syst != ""){
     if (b_Syst == "jet_JERNom")
       fChain->SetBranchAddress("jet_pt", jet_systUncVar, &b_jet_systUncVar);        
     else
       fChain->SetBranchAddress(b_Syst, jet_systUncVar, &b_jet_systUncVar);     
   }
   // -------------------------------------------------------------------------------------------
   // -------------------------------------------------------------------------------------------
   // -- Central pT jet value w/o JER_Nom
   // Modification in order to use the NO CORRECTED jet pT in MC
   // fChain->SetBranchAddress("jet_raw_pt", jet_raw_pt, &b_jet_raw_pt);
   // fChain->SetBranchAddress("jet_pt", jet_pt, &b_jet_pt);
   if(IsMC){
     // WARNING -> This configuration (pT_raw) will change for the next central production
     //            It must be "equivalent" to the one used in Real-DATA
     fChain->SetBranchAddress("jet_raw_pt", jet_pt, &b_jet_pt); 
     //fChain->SetBranchAddress("jet_pt", jet_pt, &b_jet_pt); 
     fChain->SetBranchAddress("met_metNoCorrFromJets", &met_met, &b_met_met);
   }
   else{
     fChain->SetBranchAddress("jet_pt", jet_pt, &b_jet_pt);
     fChain->SetBranchAddress("met_met", &met_met, &b_met_met);
   }
   // -------------------------------------------------------------------------------------------
   // -------------------------------------------------------------------------------------------
   fChain->SetBranchAddress("jet_eta",           jet_eta,           &b_jet_eta);
   fChain->SetBranchAddress("jet_phi",           jet_phi,           &b_jet_phi);
   fChain->SetBranchAddress("jet_Et",            jet_Et,            &b_jet_Et);
   fChain->SetBranchAddress("jet_E",             jet_E,             &b_jet_E);
   fChain->SetBranchAddress("jet_IDTight",       jet_IDTight,       &b_jet_IDTight);
   fChain->SetBranchAddress("jet_IDLepVeto",     jet_IDLepVeto,     &b_jet_IDLepVeto);
   fChain->SetBranchAddress("jet_btagDeepCSV",   jet_btagDeepCSV,   &b_jet_btagDeepCSV);
   fChain->SetBranchAddress("jet_partonFlavour", jet_partonFlavour, &b_jet_partonFlavour);
   fChain->SetBranchAddress("jet_hadronFlavour", jet_hadronFlavour, &b_jet_hadronFlavour);
   // TEMPORAL:
   // For the new production from Anna (Nov/2021). 
   // Jet object must be modified CreateCollections.cc
   // fChain->SetBranchAddress("jet_genjet_pt", jet_genpt, &b_jet_genpt);

   // Muons
   fChain->SetBranchAddress("nMuon",          &muon_number,   &b_muon_number);
   fChain->SetBranchAddress("muon_pt",        muon_pt,        &b_muon_pt);
   fChain->SetBranchAddress("muon_eta",       muon_eta,       &b_muon_eta);
   fChain->SetBranchAddress("muon_phi",       muon_phi,       &b_muon_phi);
   fChain->SetBranchAddress("muon_E",         muon_E,         &b_muon_E);
   fChain->SetBranchAddress("muon_charge",    muon_charge,    &b_muon_charge);
   fChain->SetBranchAddress("muon_dxy",       muon_dxy,       &b_muon_dxy);
   fChain->SetBranchAddress("muon_dz",        muon_dz,        &b_muon_dz);
   fChain->SetBranchAddress("muon_isLoose",   muon_isLoose,   &b_muon_isLoose);
   fChain->SetBranchAddress("muon_isTight",   muon_isTight,   &b_muon_isTight);
   fChain->SetBranchAddress("muon_iso_pflow", muon_iso_pflow, &b_muon_iso_pflow);

   // Electrons
   fChain->SetBranchAddress("nElectron",            &electron_number,     &b_electron_number);
   fChain->SetBranchAddress("electron_pt",          electron_pt,          &b_electron_pt);
   fChain->SetBranchAddress("electron_eta",         electron_eta,         &b_electron_eta);
   fChain->SetBranchAddress("electron_etaSC",       electron_etaSC,       &b_electron_etaSC);
   fChain->SetBranchAddress("electron_phi",         electron_phi,         &b_electron_phi);
   fChain->SetBranchAddress("electron_E",           electron_E,           &b_electron_E);
   fChain->SetBranchAddress("electron_charge",      electron_charge,      &b_electron_charge);
   fChain->SetBranchAddress("electron_dxy",         electron_dxy,         &b_electron_dxy);
   fChain->SetBranchAddress("electron_dz",          electron_dz,          &b_electron_dz);
   fChain->SetBranchAddress("electron_isVetoCBID",  electron_isVetoCBID,  &b_electron_isVetoCBID);
   fChain->SetBranchAddress("electron_isTightCBID", electron_isTightCBID, &b_electron_isTightCBID);
   fChain->SetBranchAddress("electron_VID",         electron_VID,         &b_electron_VID);
   fChain->SetBranchAddress("electron_iso_pflow",   electron_iso_pflow,   &b_electron_iso_pflow);

   // MET
   // MET selected at L70 and L74
   fChain->SetBranchAddress("met_phi",   &met_phi,   &b_met_phi);
   fChain->SetBranchAddress("met_sumEt", &met_sumEt, &b_met_sumEt);
   fChain->SetBranchAddress("met_px",    &met_px,    &b_met_px);
   fChain->SetBranchAddress("met_py",    &met_py,    &b_met_py);

   // MET Filters
   fChain->SetBranchAddress("metFilter_METFilters", &metFilter_METFilters, &b_metFilter_METFilters);
   fChain->SetBranchAddress("metFilter_HBHENoiseFilter", &metFilter_HBHENoiseFilter, &b_metFilter_HBHENoiseFilter);
   fChain->SetBranchAddress("metFilter_HBHENoiseIsoFilter", &metFilter_HBHENoiseIsoFilter, &b_metFilter_HBHENoiseIsoFilter);
   fChain->SetBranchAddress("metFilter_EcalDeadCellTriggerPrimitiveFilter", &metFilter_EcalDeadCellTriggerPrimitiveFilter, &b_metFilter_EcalDeadCellTriggerPrimitiveFilter);
   fChain->SetBranchAddress("metFilter_goodVertices", &metFilter_goodVertices, &b_metFilter_goodVertices);
   fChain->SetBranchAddress("metFilter_eeBadScFilter", &metFilter_eeBadScFilter, &b_metFilter_eeBadScFilter);
   fChain->SetBranchAddress("metFilter_globalSuperTightHalo2016Filter", &metFilter_globalSuperTightHalo2016Filter, &b_metFilter_globalSuperTightHalo2016Filter);
   fChain->SetBranchAddress("metFilter_BadPFMuonFilter", &metFilter_BadPFMuonFilter, &b_metFilter_BadPFMuonFilter);

   if (IsMC){
     // GenWeights
     std::cout << "Loading MC branches......" << std::endl; 
     fChain->SetBranchAddress("genInfo_LHEWOrgXWGTUP",            &genInfo_LHEWOrgXWGTUP, &b_genInfo_LHEWOrgXWGTUP);
     fChain->SetBranchAddress("genInfo_trueNumberOfInteractions", &genInfo_trueNumberOfInteractions, &b_genInfo_trueNumberOfInteractions);
     fChain->SetBranchAddress("genInfo_scalePDF",                 &genInfo_scalePDF, &b_genInfo_scalePDF);
     fChain->SetBranchAddress("genInfo_id2",                      &genInfo_id2, &b_genInfo_id2);
     fChain->SetBranchAddress("genInfo_id1",                      &genInfo_id1, &b_genInfo_id1);
     fChain->SetBranchAddress("genInfo_nLHEPart",                 &genInfo_nLHEPart, &b_genInfo_nLHEPart);
     fChain->SetBranchAddress("genInfo_x2",                       &genInfo_x2, &b_genInfo_x2);
     fChain->SetBranchAddress("genInfo_x1",                       &genInfo_x1, &b_genInfo_x1);
     fChain->SetBranchAddress("genInfo_MCWeight",                 &genInfo_MCWeight, &b_genInfo_MCWeight);
     fChain->SetBranchAddress("genInfo_ScaleWeights",             genInfo_ScaleWeights, &b_genInfo_ScaleWeights);
     fChain->SetBranchAddress("nPSWeight",                        &nPSWeight, &b_nPSWeight);
     fChain->SetBranchAddress("genInfo_PSWeights",                genInfo_PSWeights, &b_genInfo_PSWeights);
     fChain->SetBranchAddress("nLHEPdfWeight",                    &nLHEPdfWeight, &b_nLHEPdfWeight);
     fChain->SetBranchAddress("genInfo_PDFWeights",               genInfo_PDFWeights, &b_genInfo_PDFWeights);
   }

   if (IsTop){

     std::cout << "Loading TOP branches......" << std::endl; 
     // GenLevel particles
     fChain->SetBranchAddress("nGenPart",              &genParticles_number,  &b_genParticles_number);
     fChain->SetBranchAddress("genParticles_pdgId",    genParticles_pdgId,    &b_genParticles_pdgId);
     fChain->SetBranchAddress("genParticles_status",   genParticles_status,   &b_genParticles_status);
     fChain->SetBranchAddress("genParticles_motherId", genParticles_motherId, &b_genParticles_motherId);
     fChain->SetBranchAddress("genParticles_pt",       genParticles_pt,       &b_genParticles_pt);
     fChain->SetBranchAddress("genParticles_eta",      genParticles_eta,      &b_genParticles_eta);
     fChain->SetBranchAddress("genParticles_phi",      genParticles_phi,      &b_genParticles_phi);
     fChain->SetBranchAddress("genParticles_E",        genParticles_E,        &b_genParticles_E);
     // GenLevel top
     fChain->SetBranchAddress("topGenParticles_pdgId",    topGenParticles_pdgId,    &b_topGenParticles_pdgId);
     fChain->SetBranchAddress("topGenParticles_status",   topGenParticles_status,   &b_topGenParticles_status);
     fChain->SetBranchAddress("topGenParticles_motherId", topGenParticles_motherId, &b_topGenParticles_motherId);
     fChain->SetBranchAddress("topGenParticles_pt",       topGenParticles_pt,       &b_topGenParticles_pt);
     fChain->SetBranchAddress("topGenParticles_eta",      topGenParticles_eta,      &b_topGenParticles_eta);
     fChain->SetBranchAddress("topGenParticles_phi",      topGenParticles_phi,      &b_topGenParticles_phi);
     fChain->SetBranchAddress("topGenParticles_E",        topGenParticles_E,        &b_topGenParticles_E);
     // GenLevel anti-top
     fChain->SetBranchAddress("topbarGenParticles_pdgId",    topbarGenParticles_pdgId,    &b_topbarGenParticles_pdgId);
     fChain->SetBranchAddress("topbarGenParticles_status",   topbarGenParticles_status,   &b_topbarGenParticles_status);
     fChain->SetBranchAddress("topbarGenParticles_motherId", topbarGenParticles_motherId, &b_topbarGenParticles_motherId);
     fChain->SetBranchAddress("topbarGenParticles_pt",       topbarGenParticles_pt,       &b_topbarGenParticles_pt);
     fChain->SetBranchAddress("topbarGenParticles_eta",      topbarGenParticles_eta,      &b_topbarGenParticles_eta);
     fChain->SetBranchAddress("topbarGenParticles_phi",      topbarGenParticles_phi,      &b_topbarGenParticles_phi);
     fChain->SetBranchAddress("topbarGenParticles_E",        topbarGenParticles_E,        &b_topbarGenParticles_E);
     // Angles and weights for top
     fChain->SetBranchAddress("top_LepHad",   &top_LepHad,   &b_top_LepHad);
     fChain->SetBranchAddress("top_cosThKF",  &top_cosThKF,  &b_top_cosThKF);
     fChain->SetBranchAddress("top_rwF0KF",   &top_rwF0KF,   &b_top_rwF0KF);
     fChain->SetBranchAddress("top_rwFLKF",   &top_rwFLKF,   &b_top_rwFLKF);
     fChain->SetBranchAddress("top_rwFRKF",   &top_rwFRKF,   &b_top_rwFRKF);
     fChain->SetBranchAddress("top_cosThMlb", &top_cosThMlb, &b_top_cosThMlb);
     fChain->SetBranchAddress("top_rwF0Mlb",  &top_rwF0Mlb,  &b_top_rwF0Mlb);
     fChain->SetBranchAddress("top_rwFLMlb",  &top_rwFLMlb,  &b_top_rwFLMlb);
     fChain->SetBranchAddress("top_rwFRMlb",  &top_rwFRMlb,  &b_top_rwFRMlb);
     // Angles and weights for anti-top
     fChain->SetBranchAddress("topbar_LepHad",   &topbar_LepHad,   &b_topbar_LepHad);
     fChain->SetBranchAddress("topbar_cosThKF",  &topbar_cosThKF,  &b_topbar_cosThKF);
     fChain->SetBranchAddress("topbar_rwF0KF",   &topbar_rwF0KF,   &b_topbar_rwF0KF);
     fChain->SetBranchAddress("topbar_rwFLKF",   &topbar_rwFLKF,   &b_topbar_rwFLKF);
     fChain->SetBranchAddress("topbar_rwFRKF",   &topbar_rwFRKF,   &b_topbar_rwFRKF);
     fChain->SetBranchAddress("topbar_cosThMlb", &topbar_cosThMlb, &b_topbar_cosThMlb);
     fChain->SetBranchAddress("topbar_rwF0Mlb",  &topbar_rwF0Mlb,  &b_topbar_rwF0Mlb);
     fChain->SetBranchAddress("topbar_rwFLMlb",  &topbar_rwFLMlb,  &b_topbar_rwFLMlb);
     fChain->SetBranchAddress("topbar_rwFRMlb",  &topbar_rwFRMlb,  &b_topbar_rwFRMlb);

     // TEMPORAL:
     // For the new production from Anna (Nov/2021). 
     // GenJets
     // fChain->SetBranchAddress("nGenJet",              &nGenJet,        &b_nGenJet);
     // fChain->SetBranchAddress("genjet_pt",            &genjet_pt,      &b_genjet_pt);
     // fChain->SetBranchAddress("genjet_eta",           &genjet_eta,     &b_genjet_eta);
     // fChain->SetBranchAddress("genjet_phi",           &genjet_phi,     &b_genjet_phi);
     // fChain->SetBranchAddress("genjet_E",             &genjet_E,       &b_genjet_E);
     // fChain->SetBranchAddress("genjet_partonFlavour", &genjet_flavour, &b_genjet_flavour);
   
   }
   
   Notify();
}

Bool_t NanoAOD::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

//#endif // #ifdef NanoAOD_cxx
