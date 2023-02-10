#ifndef __CINT__
#include "NanoAnalyzer.h"
#endif

#ifndef __CINT__
// MVA: BDT
#include "TMVA/MethodCategory.h"
#include "TMVA/Factory.h"
#include "TMVA/Tools.h"
#include "TMVA/TMVAGui.h"
// This include contains the info of the BDT. Added in the Makefile
#include "weights_TrFullStataMCatNLORegFrom2_WithDR-v6/TMVAClassification_BDT.class.C"

// Here to avoid additional headers affecting only the Analyzer code
bool JetCutConditions(std::vector<NanoObj::Jet> *jets);
// Progress
void print_progress(int TreeEntries, Long64_t ievt);
// Id for Systematics
int FindSysID(const std::vector<TString> Names, TString Name, TString BaseName);
// ttbar GEN channel
bool  IsGEN_ttbarLepJets(int top, int topbar);


void display_usage(){
  std::cout << "\033[1;37musage:\033[1;m Ntuple Analyzer for ttbar-Xsec and W-Helicity" << std::endl;
  std::cout << "" << std::endl;
  std::cout << "Options:" << std::endl;
  std::cout << "    -i        inputfile  Input file with list of samples (*.files)" << std::endl;
  std::cout << "    -d        input file directory. Default directory: SkimList" << std::endl;
  std::cout << "    -o        reference name for the output file " << std::endl;
  std::cout << "    -odir     output directory name " << std::endl;
  std::cout << "    -n        number of events" << std::endl;
  std::cout << "    -frac     W-Helicity fraction to be processed: FR, FL or F0" << std::endl;
  std::cout << "    -outside  code will run from outside (define \"cern\" or \"ciemat\"). You should do first  \"voms-proxy-init -voms cms\" " << std::endl;
  std::cout << "    -cmssw    full CMSSW_BASE path. Only needed for batch mode. " << std::endl;
  std::cout << "    -split    name of the .hist when jobs are submitted " << std::endl;
  std::cout << "    -h        displays this help message and exits " << std::endl;
  std::cout << "" << std::endl;
}


int main(int argc, const char* argv[]){

  // Time control
  TStopwatch sw;
  sw.Start(kTRUE);

  gErrorIgnoreLevel = kError;
  
  gSystem->Load("libTree");
  gROOT->ProcessLine("#include <vector>");

  double  _NUserEvt  = 0;
  const char * _output   = "Histos";
  const char * _input    = 0;
  const char * _dir      = "SkimList/";    // Default directory for the inputs
  const char * _odir     = "HistoResult/"; // Output directory
  const char * _fraction = "none";         // W-Helicity fraction for top samples
  const char * _cmssw    = "";             // CMSSW path 
  const char * _FromOutside = "";
  const char * _ghist    = "none";
  
  // Arguments used
  // Parsing input options
  if(argc == 1){
    display_usage();
    return -1;
  }
  else{
    //Argumet 1 must be a valid input fileName
    for (int i = 1; i < argc; i++){
      if( strcmp(argv[i],"-i") == 0 ){
	_input = argv[i+1];
	i++;
      }
      if( strcmp(argv[i],"-d") == 0 ){
	_dir = argv[i+1];
	i++;
      }
      if( strcmp(argv[i],"-o") == 0 ){
	_output = argv[i+1];
	i++;
      }
      if( strcmp(argv[i],"-odir") == 0 ){
	_odir = argv[i+1];
	i++;
      }
      if( strcmp(argv[i],"-frac") == 0 ){
	_fraction = argv[i+1];
	i++;
      }
      if( strcmp(argv[i],"-n") == 0 ){
	_NUserEvt = atoi(argv[i+1]);
	i++;
      }
      if( strcmp(argv[i],"-outside") == 0 ){
        _FromOutside = argv[i+1];
	i++;
      }
      if( strcmp(argv[i],"-cmssw") == 0 ){
	_cmssw = argv[i+1];
	i++;
      }
      if( strcmp(argv[i],"-split") == 0 ){
	_ghist = argv[i+1];
	i++;
      }
      if( strcmp(argv[i],"-h") == 0 ||
	  strcmp(argv[i],"--help") == 0 ){
	display_usage();
	return 0;
      }
    }
  }//else
  
  if( _input == 0 ){
    std::cerr << "\033[1;31mskimfile ERROR:\033[1;m The '-i' option is mandatory!"
	      << std::endl;
    display_usage();
    return -1;
  }
  
  // reassigning
  TString fname(_input);
  TString outfileRef(_output);
  TString fdir(_dir);
  TString SkimOutDir(_odir);
  TString FromOutside(_FromOutside);
  TString WFraction(_fraction);
  TString FullCMSSWPath(_cmssw);
  TString GlobalHistoName(_ghist);

  // Sample: Names based in the same structure than plugins/Lumi.cc
  bool Isttbar     = fname.Contains("TTToSemiLeptonic") || fname.Contains("TTJets");
  bool IsStbar     = fname.Contains("ST_") && fname.Contains("antitop_");
  bool IsSt        = fname.Contains("ST_") && fname.Contains("top_") && !IsStbar;
  bool IsWFraction = false;
  int nWFraction   = -1; 
  int wWF_o = 0, wWF_f = 0;

  if(WFraction != "none"){
    IsWFraction = true; 

    if      (WFraction == "F0") nWFraction = 0;
    else if (WFraction == "FL") nWFraction = 1;
    else if (WFraction == "FR") nWFraction = 2;
    // To select the correct top/tobar branch based in the sample:
    if     (Isttbar) { wWF_o = 0; wWF_f = 1; }
    else if(IsSt)    { wWF_o = 0; wWF_f = 0; }
    else if(IsStbar) { wWF_o = 1; wWF_f = 1; }
    else{
      std::cerr << "W-Helicity Fraction Weights are ONLY for TOP samples!" << std::endl;
      std::exit (EXIT_FAILURE);
    }

    TString WFracSamName = "ttbar";
    if (IsSt)    WFracSamName = "ST";
    if (IsStbar) WFracSamName = "STbar";
    std::cout << "Code set to run " << WFraction << " fraction in " << WFracSamName << std::endl; 

  }

  // Fractions from SM MC
  // [F_0],[F_L],[F_R]
  double WFraction_SMMC[3] = {0.6952,0.3030,1.8e-03}; 

  // ---------------------
  // b tag Scale Factors
  // ---------------------
  // Local b-tag SF From CSV file (BTV recommendation)
  TString btagCSVFile;
  TString measType = "iterativefit";
  TString sysType  = "central"; 
  BTagCalibrationReader *reader;
  BTagCalibration       *calib;

  // Lepton and trigger SF: Path to the files 
  TString LeptonSFPath;
  // Lepton pT/eta cuts (different per years)
  float pT_mu  = 30,  pT_el  = 35;
  float eta_mu = 2.4, eta_el = 2.1;
  // Jet pT/eta cuts
  float pT_jet = 30, eta_jet = 2.4;
  // DeepCSV working points
  double deepcsvWP_Loose;
  double deepcsvWP_Medium;
  double deepcsvWP_Tight;

  // ------------------------------------------
  // Luminosity and year depended parameters
  // ------------------------------------------
  double data_lumi;
  if      ( fname.Contains("2016") ) {
    data_lumi = 35900. ; // [pb-1] 2016
    LeptonSFPath = FullCMSSWPath + "includes/Corrections/SFIDISOTr/2016/";
    // btagCSVFile  = FullCMSSWPath + "includes/Corrections/btagSF/2016/DeepCSV_2016_LegacySF_V1.csv";
    btagCSVFile  = FullCMSSWPath + "includes/Corrections/btagSF/2016/ShortDeepCSV_2016_LegacySF_V1.csv";
    deepcsvWP_Loose  = 0.2217;
    deepcsvWP_Medium = 0.6321;
    deepcsvWP_Tight  = 0.8953;
  }
  else if ( fname.Contains("2017") ){
    data_lumi = 41500. ; // [pb-1] 2017
    LeptonSFPath = FullCMSSWPath + "includes/Corrections/SFIDISOTr/2017/";
    btagCSVFile  = FullCMSSWPath + "includes/Corrections/btagSF/2017/ShortDeepCSV_2017_94XSF_V5_B_F.csv";
    deepcsvWP_Loose  = 0.1522;
    deepcsvWP_Medium = 0.4941;
    deepcsvWP_Tight  = 0.8001;
  }  
  else if ( fname.Contains("2018") ){
    data_lumi = 59700. ; // [pb-1] 2018
    LeptonSFPath = FullCMSSWPath + "includes/Corrections/SFIDISOTr/2018/";
    // To check: Electron eta cut can be 2.4
    // eta_el = 2.4;
    btagCSVFile  = FullCMSSWPath + "includes/Corrections/btagSF/2018/ShortDeepCSV_2018_102XSF_V2.csv";
    deepcsvWP_Loose  = 0.1241;
    deepcsvWP_Medium = 0.4184;
    deepcsvWP_Tight  = 0.7527;
  }  
  else {
    std::cout << "Missing year tag in the file name." << std::endl;
    std::exit(0);
  }
  std::cout << "Luminosity set to " << data_lumi << " pb-1." << std::endl;

  // Local btag SF  
  std::cout << "Creating b-tag calibration (this can take a while)..." << std::endl;
  calib = new BTagCalibration("DeepCSV", (std::string)btagCSVFile);
  
  std::cout << "Creating b-tag Reader..." << std::endl;
  reader = new BTagCalibrationReader(BTagEntry::OP_RESHAPING, (std::string)sysType ) ;
  
  std::cout << "Loading b-tag Readers..." << std::endl;
  reader->load((*calib), BTagEntry::FLAV_B,    (std::string)measType);
  reader->load((*calib), BTagEntry::FLAV_C,    (std::string)measType);
  reader->load((*calib), BTagEntry::FLAV_UDSG, (std::string)measType);
  
  std::cout << "---------- Local b-tag SF  ---------- " << std::endl;
  std::cout << "Local scale factors loaded from: " <<std::endl;
  std::cout << btagCSVFile <<std::endl;
  std::cout << "----------------------------------\n " << std::endl;

  // Lepton SF: Load histograms
  TH2F *h2DLeptonSF[2][3];   
  ReadLeptonTriggerSF(LeptonSFPath, h2DLeptonSF);  
  
  // Inputs
  std::cout << "---------- Input Sample ---------- " << std::endl;
  bool isMC = true;
  std::vector<TString> InputNameFiles;
  std::cout << "Loading " << fdir + fname << " file...." << std::endl; 
  InputNameFiles = GetListOfFiles(fdir + fname, FromOutside);
  std::cout << "Number of samples to be read: " << InputNameFiles.size() << std::endl; 
  if ( fname.Contains("Data") ){
    isMC = false;    
    std::cout << "Sample identified as DATA." << std::endl;
  }  
  else std::cout << "Sample identified as MC." << std::endl;

  // For Data and QCD
  bool IsMu = true, IsEl = true;
  if( fname.Contains("DataSinleElectron") ||
      fname.Contains("EMEnriched")) IsMu = false;
  if( fname.Contains("DataSingleMuon") ||
      fname.Contains("MuEnriched")) IsEl = false;


  std::cout << "----------------------------------\n " << std::endl;
  
  // Output file
  SkimOutDir = SkimOutDir + outfileRef + "/";
  struct stat st;
  if(stat(SkimOutDir,&st) != 0) system("mkdir " + SkimOutDir);

  fname.Resize(fname.Sizeof()-7); // remove .files
  outfileRef = SkimOutDir + outfileRef + "_BDTTree_" + fname;
  TFile *OutputFile = new TFile( outfileRef + ".root","recreate");

  // ---------------------------------------------------------------
  // --- Defining Trees
  // ---------------------------------------------------------------

  TTree *tree_R, *tree_W;
  int recoregion, ch_evt;
  float j_pT, j_Deep, l_pT, DR_lj;
  float W_evt;

  // Right combination
  tree_R = new TTree("Tree_Right", "Tree with right assignment");

  tree_R->Branch("W_evt",  &W_evt,      "W_evt/F");
  tree_R->Branch("ch_evt", &ch_evt,     "channel/I");
  tree_R->Branch("region", &recoregion, "region/I");
  
  tree_R->Branch("j_pT",   &j_pT,       "j_pT/F");
  tree_R->Branch("j_Deep", &j_Deep,     "j_Deep/F");

  tree_R->Branch("l_pT",   &l_pT,       "l_pT/F");

  tree_R->Branch("DR_lj",  &DR_lj,      "DR_lj/F");

       
  // Wrong combination
  tree_W = new TTree("Tree_Wrong", "Tree with wrong assignment");

  tree_W->Branch("W_evt",   &W_evt,      "W_evt/F");
  tree_W->Branch("ch_evt",  &ch_evt,     "channel/I");
  tree_W->Branch("region",  &recoregion, "region/I");

  tree_W->Branch("j_pT",    &j_pT,       "j_pT/F");
  tree_W->Branch("j_Deep",  &j_Deep,     "j_Deep/F");
 
  tree_W->Branch("l_pT",    &l_pT,       "l_pT/F");
 
  tree_W->Branch("DR_lj",   &DR_lj,      "DR_lj/F");

  std::cout << "----------------------------------\n " << std::endl;
  std::cout << "----------------------------------\n " << std::endl;

  // WEIGHTS
  double weight_lumi = 1.0;
  
  // Total number of events
  // From histogram files
  int binForEvt = 2;
  double NTotalTreeEvt = 0, NTotalMCGENEvt = 0;
  for (int ifile = 0; ifile < InputNameFiles.size(); ifile++){
    TString HistoNormFileName;
    TFile *InputFile;
    if(GlobalHistoName == "none")
      HistoNormFileName = InputNameFiles.at(ifile) + ".hist";
    else
      HistoNormFileName = GlobalHistoName;
    
    std::cout<< "Number of events from: " << HistoNormFileName << std::endl;
    InputFile = TFile::Open(HistoNormFileName,"readonly");
    
    TH1F *h_LHEweights;
    if (InputFile != 0 && InputFile->GetListOfKeys()->Contains("LHEweights")){
      h_LHEweights = (TH1F*) InputFile->Get("LHEweights")->Clone();
    }
    else{
      std::cout << "File " << HistoNormFileName << " not found!" << std::endl; 
      std::exit(0);
    }

    NTotalMCGENEvt += h_LHEweights->GetBinContent(binForEvt); 
    NTotalTreeEvt  += h_LHEweights->GetBinContent(3); // Number of Skimmed Evts

    InputFile->Close() ;

    if (GlobalHistoName != "none") break;
    
  }
  
  double MaxEvt = NTotalTreeEvt;
  double NMCEvt_XsecNorm = NTotalMCGENEvt;
  if(_NUserEvt > 0){
    MaxEvt = std::min(NTotalTreeEvt, _NUserEvt);
    NMCEvt_XsecNorm = MaxEvt*(NTotalMCGENEvt/NTotalTreeEvt);
  }  

  if (isMC){    
    weight_lumi =  SFLumi(fname , data_lumi, NMCEvt_XsecNorm) ;

    std::cout << "-------- MC Normalization -------- " << std::endl;
    std::cout << "Normalizing to " << data_lumi << " pb-1 the " << NMCEvt_XsecNorm << " MC events (skimmed " << MaxEvt << ")" << std::endl;
    std::cout << "Weight per event = " << weight_lumi << std::endl;    
    std::cout << "----------------------------------\n " << std::endl;

  } // if(isMC)
  
  // Samples
  std::cout << "---------- Run Analysis ---------- " << std::endl;
  for (int ifile = 0; ifile < InputNameFiles.size(); ifile++){
    
    TFile *InputFile = TFile::Open(InputNameFiles.at(ifile),"readonly");
    std::cout << "Reading " + InputNameFiles.at(ifile) << std::endl;

    NanoAOD *SkimTree;
    SkimTree = new NanoAOD( (TTree*)InputFile->Get("Events"), "", true, true);
    
    Long64_t nEvtTree = SkimTree->fChain->GetEntriesFast() ;
    std::cout<< InputNameFiles.at(ifile) << " sample has "<< nEvtTree << " entries."<< std::endl;
    Long64_t NTreeEvtToRun;
    if(MaxEvt <= nEvtTree) {
      NTreeEvtToRun = MaxEvt; 
      MaxEvt = 0;
    }
    else {
      NTreeEvtToRun = nEvtTree;
      MaxEvt -= nEvtTree;
    }

    // MVA
    // Create a vector with the name of the variables used in the training
    // That is the way to identify all the variables involved.
    // std::vector<std::string> inputVariableNames;
    // inputVariableNames.push_back("j_Deep");
    // inputVariableNames.push_back("DpT_jmet");
    // inputVariableNames.push_back("Deta_lj");
    // inputVariableNames.push_back("DR_lj");
    // inputVariableNames.push_back("M_lj");
    // IClassifierReader *classReader = new ReadBDT(inputVariableNames);

    // Evt Loop
    for (Long64_t iEvt=0; iEvt<NTreeEvtToRun; iEvt++) {
      // Progress
      print_progress(NTreeEvtToRun, iEvt);
      
      // std::cout << "\n" << iEvt << std::endl;
      
      // Get Event
      SkimTree->fChain->GetEntry(iEvt);      

      // Trigger
      if ( !SkimTree->passHLT ) continue; 

      // WEIGHTS
      // -- Event weights
      double event_weight = 1. ;
      // -- ID/ISO/Trigger SF and b-tag weight       
      double weight_SFLep = 1.0, weight_btag = 1.0;
      // -- TOP weight
      double weight_Wfraction = 1.0;

      if(IsWFraction){
      // -- TOP weights[F0,FL,FR][t,tbar]
      double weight_frac[3][2] = {1.0,1.0,1.0,1.0,1.0,1.0,};
	weight_frac[0][0] = SkimTree->top_rwF0KF;
	weight_frac[0][1] = SkimTree->topbar_rwF0KF;

	weight_frac[1][0] = SkimTree->top_rwFLKF;
	weight_frac[1][1] = SkimTree->topbar_rwFLKF;

	weight_frac[2][0] = SkimTree->top_rwFRKF;
	weight_frac[2][1] = SkimTree->topbar_rwFRKF;

	for(int iwf = wWF_o; iwf <= wWF_f; iwf++){
	  weight_Wfraction *= weight_frac[nWFraction][iwf];	  
	}
	weight_Wfraction *= WFraction_SMMC[nWFraction];
      }

      // Only for inclusive samples
      // It distinguishes between lep+jets, dilepton and all jets decay modes  
      // if (IsGEN_ttbarLepJets( SkimTree->top_LepHad ,  SkimTree->topbar_LepHad ) ) continue;

      // Veto leptons
      std::vector<NanoObj::Muon>     VetoMuons     = CreateMuonCollection     (SkimTree);
      std::vector<NanoObj::Electron> VetoElectrons = CreateElectronCollection (SkimTree);
      // Only one lepton requirement
      if ((VetoMuons.size() + VetoElectrons.size()) > 1) continue; 

      // Selected leptons collection
      std::vector<NanoObj::Muon>     SeleMuons     ;
      std::vector<NanoObj::Electron> SeleElectrons ;
      TLorentzVector SeleLepton;
      int QSeleLepton; 
      SeleMuons     = GetTightMuons    (VetoMuons,     pT_mu, eta_mu, 0.15);
      SeleElectrons = GetTightElectrons(VetoElectrons, pT_el, eta_el);

      // Evt channel
      int ichannel = -1;
      if      (SeleMuons.size()==1 && IsMu){
      	ichannel = ch::mj;
      	SeleLepton = (TLorentzVector)SeleMuons.at(0);
	QSeleLepton = SeleMuons.at(0).Charge;
      }      
      else if (SeleElectrons.size()==1 && IsEl){
      	ichannel = ch::ej;  
      	SeleLepton = (TLorentzVector)SeleElectrons.at(0);
	QSeleLepton = SeleElectrons.at(0).Charge;
      }
      else{
	continue;
      }

      // Missing Transverse Energy
      TLorentzVector MET;
      MET.SetPtEtaPhiM(SkimTree->met_met,0.0,SkimTree->met_phi,0.0);    
      
      // Jets
      int NJets = 0, NLbJets = 0, NMbJets = 0, NTbJets = 0;

      // -- Jet Corrections and Systematic variations
      // - Coming directly from the Tree
      // - JER
      // - JES: 25 variations
      // - b-tagging: SF Modified accordingly
      std::vector<NanoObj::Jet> Jets = CreateJetCollection(SkimTree);

      // Select jets and clean from leptons (MC)
      SelectAndCleanJets(&Jets, SeleLepton, pT_jet, eta_jet);

      // b-tag weights
      weight_btag = GetbtagEvtWeightFromCSV(*reader, Jets);

      // PileUp
      double PUweight[3] = {SkimTree->puWeight,      // Nom
			    SkimTree->puWeightUp,    // Up
			    SkimTree->puWeightDown}; // Down

      // positive versus negative NLO
      double mcWeight = 1.;	
      if (SkimTree->genInfo_LHEWOrgXWGTUP != 0.) mcWeight = SkimTree->genInfo_LHEWOrgXWGTUP/std::abs(SkimTree->genInfo_LHEWOrgXWGTUP);
	
      // Lepton and trigger efficiency scale factors
      weight_SFLep = LeptonSF(h2DLeptonSF, ichannel, SeleLepton.Eta(), SeleLepton.Pt(), var::Nom);
  	
      // final Event Weight
      event_weight = weight_lumi*PUweight[var::Nom]*weight_SFLep*weight_btag*weight_Wfraction*mcWeight;

      // Jet pT conditions
      if (!JetCutConditions(&Jets)) continue;
      
      // Number of Jets
      NJets = Jets.size();
      // Selected jet-position
      unsigned int seljetpos = 99;
      float jBDT = -1.;
      
      for (int ij=0; ij<Jets.size(); ij++){
      	NanoObj::Jet ijet = Jets.at(ij);	
      	// Jet
      	float jetbtag =  ijet.DeepCSV;
      	NLbJets += jetbtag > deepcsvWP_Loose  ? 1:0; 
      	NMbJets += jetbtag > deepcsvWP_Medium ? 1:0; 
      	NTbJets += jetbtag > deepcsvWP_Tight  ? 1:0; 
			
      	// // BDT Variables
      	// float M_lj      = (ijet+SeleLepton).M();
      	// float Deta_lj   = ijet.Eta()-SeleLepton.Eta();
      	// float DR_lj     = ijet.DeltaR(SeleLepton);
      	// float DpT_METj  = ijet.Pt() - MET.Pt();
      	// float Dphi_METj = std::abs(ijet.Phi() - MET.Phi());
      	// if (Dphi_METj > ROOT::Math::Pi()) Dphi_METj = 2.*ROOT::Math::Pi()-Dphi_METj;

      	// // - Create a vector with the variables used in the BDT.
      	// // - The order must be the same that the one used in the classReader definition.
      	// // [0] "j_Deep",   [1] "DpT_jmet", 
      	// // [2] "Deta_lj",  [3] "DR_lj"     [5] "M_lj"

      	// std::vector<double> inputVariableValues;
      	// inputVariableValues.push_back(jetbtag);
      	// inputVariableValues.push_back(DpT_METj);
      	// inputVariableValues.push_back(Deta_lj);
      	// inputVariableValues.push_back(DR_lj);
      	// inputVariableValues.push_back(M_lj);
      	// double BDTResponse  = classReader->GetMvaValue(inputVariableValues);
	
      	// // Lepton-Jet with the highest BDT response
      	// if (BDTResponse > jBDT){
      	//   jBDT = BDTResponse;
      	//   seljetpos = ij;
      	// }
      	// // BDT Response for all jets
      	// h_Jet_BDT[ichannel][nreg-1]->Fill(BDTResponse, event_weight);
	
      } // for(jet)

      // ----------------------------
      // b and l at generation Level
      // ----------------------------
      TLorentzVector Gen_b, Gen_l;
      int LepID_top = 0, LepID_topbar = 0;
      int Genchannel = -1, GenID = 0;
      int Gencharge  = -1;
      // [0]=Top [1]=b [2]=W [3]=Up [4]=Down
      // Top leg
      if (std::abs( SkimTree->top_LepHad ) == 13 or std::abs(SkimTree->top_LepHad) == 11){
	Gen_b.SetPtEtaPhiE(SkimTree->topGenParticles_pt[1], SkimTree->topGenParticles_eta[1], SkimTree->topGenParticles_phi[1], SkimTree->topGenParticles_E[1]);
	Gen_l.SetPtEtaPhiE(SkimTree->topGenParticles_pt[4], SkimTree->topGenParticles_eta[4], SkimTree->topGenParticles_phi[4], SkimTree->topGenParticles_E[4]);
	LepID_top = SkimTree->top_LepHad;
      }
      // Anti-Top leg
      if (std::abs( SkimTree->topbar_LepHad ) == 13 or std::abs(SkimTree->topbar_LepHad) == 11){
	Gen_b.SetPtEtaPhiE(SkimTree->topbarGenParticles_pt[1], SkimTree->topbarGenParticles_eta[1], SkimTree->topbarGenParticles_phi[1], SkimTree->topbarGenParticles_E[1]);
	Gen_l.SetPtEtaPhiE(SkimTree->topbarGenParticles_pt[4], SkimTree->topbarGenParticles_eta[4], SkimTree->topbarGenParticles_phi[4], SkimTree->topbarGenParticles_E[4]);
	LepID_topbar = SkimTree->topbar_LepHad;
      }
      
      if ((LepID_top == 0 && LepID_topbar == 0) || (LepID_top != 0 && LepID_topbar != 0) ) continue;
      else{
	if (LepID_top != 0)    { Genchannel = std::abs(LepID_top)    == 11 ? ch::ej : ch::mj; GenID = -1*LepID_top/std::abs(LepID_top);       }
	if (LepID_topbar != 0) { Genchannel = std::abs(LepID_topbar) == 11 ? ch::ej : ch::mj; GenID = -1*LepID_topbar/std::abs(LepID_topbar); }
      }

      // Matching GenLepton and RecoLepton
      if (ichannel !=  Genchannel) continue;

      // Object matching
      int jetindex = -1;
      float DR_max = 0.4;
      // - Lepton
      if(QSeleLepton == GenID){
        // Jets
        for (int ij=0; ij<Jets.size(); ij++){
	  NanoObj::Jet ijet = Jets.at(ij);
          // Flavour
          if(std::abs(ijet.Flavour) != 5) continue;
          // pT
          float DpT = std::abs(ijet.Pt()-Gen_b.Pt());
          if (DpT/ijet.Pt() > 0.5 ) continue;
          // DeltaR
          float DR = ijet.DeltaR(Gen_b);
          if(DR < DR_max){
            DR_max = DR;
            jetindex = ij;
          }
        }
      }
      if (jetindex == -1) continue;


      int NbJets = NMbJets;      

      int sel = -1;
      // Event Selection
      if (NJets == 2 && NbJets == 1) sel = 0; 
      if (NJets == 2 && NbJets == 2) sel = 1; 
      if (NJets == 3 && NbJets == 1) sel = 2; 
      if (NJets == 3 && NbJets == 2) sel = 3; 
      if (NJets == 3 && NbJets == 3) sel = 4; 
      if (NJets == 4 && NbJets == 1) sel = 5; 
      if (NJets == 4 && NbJets == 2) sel = 6; 
      if (NJets == 4 && NbJets >= 3) sel = 7; 
      if (NJets >= 5)                sel = 8; 
      if (NJets >= 5 && NbJets >= 2) sel = 9; 
 

      if (sel == -1) continue;
      // Fill Trees
      for (int ij=0; ij<Jets.size(); ij++){
	NanoObj::Jet ijet = Jets.at(ij);
        // Tree variables
        W_evt      = event_weight;
	ch_evt     = ichannel;
        recoregion = sel;
        
	j_pT   = ijet.Pt();
        j_Deep = ijet.DeepCSV;
	
	l_pT   = SeleLepton.Pt();
        
	DR_lj  = ijet.DeltaR(SeleLepton);

        if(ij == jetindex){
          tree_R->Fill();
        }
        else {
          tree_W->Fill();
        }
      }
      
    } // for (iEvent)
    
    // delete classReader;
    
    InputFile->Close();
    delete InputFile;
 
    std::cout << "==================================================] 100% " << std::endl;
    std::cout << "--- End of event loop for sample " << ifile << ": "; sw.Print();
    std::cout << std::endl;
    sw.Continue();
      
    std::cout << "\nClosing " << InputNameFiles.at(ifile) << " file" << std::endl;
    std::cout << "Number of pending events: " << MaxEvt << std::endl;
    std::cout << "\n--------------------------------\n" << std::endl;
    
    // Exit from samples loop if all the requested events have been processed.
    if (MaxEvt == 0) break;
  } // for (InputFiles)
  
  // From local b-tagging SF
  delete reader, calib;

  std::cout << "-------- Saving Trees ------- " << std::endl;
  OutputFile->cd(); 

  tree_R->Write();
  tree_W->Write();

  OutputFile->Close();

  std::cout << "File " << OutputFile->GetName()  << " has been created. " << std::endl;
  sw.Stop();
  std::cout << "--- Total time running ==> "; sw.Print();
  std::cout << std::endl;  
  std::cout << "----------------------------------\n " << std::endl;
  std::cout << "!!!!!!!!!!!!! D o n e !!!!!!!!!!!!" << std::endl;

} // main

void print_progress(int TreeEntries, Long64_t ievt){
  int step = TreeEntries/50;
  if (ievt%(step) == 0){ 
    float progress=(ievt)/(TreeEntries*1.0);
    int barWidth = 50;
    
    std::cout << "[";
    int pos = barWidth * progress;
    
    for (int i = 0; i < barWidth; ++i) {
      if (i < pos) std::cout << "=";
      else if (i == pos) std::cout << ">";
      else std::cout << " ";
    }
    
    std::cout << "] " << int(progress * 100.0) << " %\r";
    std::cout.flush();
  }  
}

// Find Systematic Uncertainties
int FindSysID(const std::vector<TString> Names, TString Name, TString BaseName){
  for(int iName = 0; iName < Names.size(); iName++){
    if (Name == (BaseName + Names.at(iName))) return iName;
  }
  return -99;
}


bool JetCutConditions(std::vector<NanoObj::Jet> *jets){
  
  bool GoodEvt = false;
  int jet40=0, jet30=0;

  for (int ij = 0; ij < jets->size() ; ij++ ){
    NanoObj::Jet jet = (jets->at(ij));

    if(jet.Pt() > 40.) jet40++;  
    if(jet.Pt() > 30.) jet30++;  

  }

  GoodEvt = (jet40 >= 1 && jet30 >= 2);
  
  return GoodEvt;
  
}


bool  IsGEN_ttbarLepJets(int top, int topbar){
  
  // Dilepton
  if ( (std::abs( top )    == 13 || std::abs( top )    == 11 ) &&
       (std::abs( topbar ) == 13 || std::abs( topbar ) == 11 )
       ) return false;
  // All Jets
  else if ( (std::abs( top )    != 13 && std::abs( top )    != 11 ) &&
	    (std::abs( topbar ) != 13 && std::abs( topbar ) != 11 )
	    ) return false;
  // Lepton+Jets
  else{ return true; }

}


#endif
