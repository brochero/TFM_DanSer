#ifndef __CINT__
#include "NanoAnalyzer.h"
#endif

#ifndef __CINT__

//#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
//#include <numpy/arrayobject.h>

// MVA: BDT

#include "TMVA/MethodCategory.h"
#include "TMVA/Factory.h"
#include "TMVA/Tools.h"
#include "TMVA/TMVAGui.h"
#include "TMVA/Reader.h"

#include "TEfficiency.h"
#include "TProfile.h" 

//PyKeras
#include "TMVA/PyMethodBase.h"

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
  std::cout << "    -i    inputfile  Input file with list of samples (*.files)" << std::endl;
  std::cout << "    -d    Input file directory. Default directory: SkimList" << std::endl;
  std::cout << "    -o    reference name for the output file " << std::endl;
  std::cout << "    -odir output directory name " << std::endl;
  std::cout << "    -n    number of events" << std::endl;
  std::cout << "    -BDT  BDT cut" << std::endl;
  std::cout << "    -frac W-Helicity fraction to be processed: FR, FL or F0" << std::endl;
  std::cout << "    -outside  Code will run from outside (define \"cern\" or \"ciemat\"). You should do first  \"voms-proxy-init -voms cms\" " << std::endl;
  std::cout << "    -cmssw    Full CMSSW_BASE path. Only needed for batch mode. " << std::endl;
  std::cout << "    -split    Name of the .hist when jobs are submitted " << std::endl;
  std::cout << "    -h    displays this help message and exits " << std::endl;
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
  const char * _ghist    = "/gpfs/users/sernad/TFM_DanSer/CMSSW_12_0_0/src/TFM_DanSer/inputs/tree_64.root.hist";
  float BDTcut = -10.;
  
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
      if( strcmp(argv[i],"-BDT") == 0 ){
	BDTcut = atof(argv[i+1]);
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

  TString dirhistosname = "central";

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
    btagCSVFile  = FullCMSSWPath + "includes/Corrections/btagSF/2017/DeepCSV_2017_94XSF_V5_B_F.csv";
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
  //TH2F *h2DLeptonSF[2][3];   
  //ReadLeptonTriggerSF(LeptonSFPath, h2DLeptonSF);  
  
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
  if( fname.Contains("DataSingleElectron") ||
      fname.Contains("EMEnriched")) IsMu = false;
  if( fname.Contains("DataSingleMuon") ||
      fname.Contains("MuEnriched")) IsEl = false;


  std::cout << "----------------------------------\n " << std::endl;
  
  // Output file
  SkimOutDir = SkimOutDir + outfileRef + "/";
  struct stat st;
  if(stat(SkimOutDir,&st) != 0) system("mkdir " + SkimOutDir);

  fname.Resize(fname.Sizeof()-7); // remove .files
  outfileRef = SkimOutDir + outfileRef + "_BDTValidation_" + fname;
  TFile *OutputFile = new TFile( outfileRef + ".root","recreate");

  // --- Defining histograms
  std::cout << "------ Creating Histograms ------- " << std::endl;
  int nch = ch::all+1, nreg = (9*3);

  TH1::SetDefaultSumw2(kTRUE); 
  TH1D *h_PrimVertex[nch][nreg];
  
  TH1D *h_Lep_pT[nch][nreg],*h_Lep_eta[nch][nreg],*h_Lep_phi[nch][nreg];

  TH1D *h_MET[nch][nreg], *h_MET_phi[nch][nreg];

  TH1D *h_Jet_pT[nch][nreg], *h_Jet_eta[nch][nreg], *h_Jet_phi[nch][nreg];  
  TH1D *h_bJet_pT[nch][nreg], *h_bJet_eta[nch][nreg], *h_bJet_phi[nch][nreg], *h_bJet_csv[nch][nreg];//, *h_bJet_QGL[nch][nreg];  
  
  TH1D *h_Jet_BDT[nch][nreg], *h_CJet_BDT[nch][nreg];
  TH1D *c_Jet_BDT[nch][nreg];  

  TH1D *h_LepJet_DR[nch][nreg],    *h_LepJet_DEta[nch][nreg],    *h_LepJet_DPhi[nch][nreg],    *h_LepJet_Mass[nch][nreg];

  TH1D *h_lQb_DPhi[nch][nreg],*h_Corr_DPhi[nch][nreg];
  TH2D *h2D_LepJetVslQb_DPhi[nch][nreg],*h2D_LepJetVsCorr_DPhi[nch][nreg]; 
  TProfile *p_LepJetVslQb_DPhi[nch][nreg],*p_LepJetVsCorr_DPhi[nch][nreg]; 

  TH1D *h_lQb_Mass[nch][nreg],*h_Corr_Mass[nch][nreg];
  TH2D *h2D_LepJetVslQb_Mass[nch][nreg],*h2D_LepJetVsCorr_Mass[nch][nreg]; 
  TProfile *p_LepJetVslQb_Mass[nch][nreg],*p_LepJetVsCorr_Mass[nch][nreg]; 

  TH1D *h_METJet_DpT[nch][nreg],    *h_METJet_DPhi[nch][nreg];

  TString chname[nch]   = {"mujets","ejets","all"};
  TString regname[nreg] = {
    "C2j1b","C2j2b","C3j1b","C3j2b","C3j3b","C4j1b","C4j2b","C4jge3b","Cge5",
    "I2j1b","I2j2b","I3j1b","I3j2b","I3j3b","I4j1b","I4j2b","I4jge3b","Ige5",
    "W2j1b","W2j2b","W3j1b","W3j2b","W3j3b","W4j1b","W4j2b","W4jge3b","Wge5"
  }; 
 
  for (unsigned int ih = 0; ih<nch; ih++){
    for (unsigned int ir = 0; ir<nreg; ir++){
      std::cout << "Creating histos for " << chname[ih] << " and " << regname[ir] << std::endl;
      
      // Event variables
      h_PrimVertex[ih][ir] = new TH1D("h_PrimVertex_" + chname[ih] + "_" + regname[ir] + "_" + dirhistosname, "Primary Vertex",             86, 0., 85.);

      // Lepton variables
      h_Lep_pT [ih][ir] = new TH1D("h_Lep_pT_"     + chname[ih] + "_" + regname[ir] + "_" + dirhistosname, "Lepton pT;pT[GeV]",        46, 8., 100.);

      h_Lep_eta[ih][ir] = new TH1D("h_Lep_eta_"    + chname[ih] + "_" + regname[ir] + "_" + dirhistosname, "Lepton #eta; #eta",        24, -2.4, 2.4);
      h_Lep_phi[ih][ir] = new TH1D("h_Lep_phi_"    + chname[ih] + "_" + regname[ir] + "_" + dirhistosname, "Lepton Phi; Phi",          64, -3.2, 3.2);

      // Missing Transverse Energy
      h_MET    [ih][ir] = new TH1D("h_MET_"       + chname[ih] + "_" + regname[ir] + "_" + dirhistosname, "MET",40,0.,120.);
      h_MET_phi[ih][ir] = new TH1D("h_MET_phi_"   + chname[ih] + "_" + regname[ir] + "_" + dirhistosname, "MET Phi",64, -3.2, 3.2);

      // Jets variables
      h_Jet_pT [ih][ir] = new TH1D("h_Jet_pT_"  + chname[ih] + "_" + regname[ir] + "_" + dirhistosname,    "pT of leading jet;pT[GeV]",  60,0.,300.);
      h_Jet_eta[ih][ir] = new TH1D("h_Jet_eta_" + chname[ih] + "_" + regname[ir] + "_" + dirhistosname,    "#eta of leading jet; #eta",  27,-2.7,2.7);
      h_Jet_phi[ih][ir] = new TH1D("h_Jet_phi_" + chname[ih] + "_" + regname[ir] + "_" + dirhistosname, "Phi of leading jet; Phi",       64, -3.2, 3.2);
      
      // BDT
      h_Jet_BDT [ih][ir] = new TH1D("h_Jet_BDT_"    + chname[ih] + "_" + regname[ir] + "_" + dirhistosname, "BDT; BDT Sel Jet",  100,-1.,1.);
      h_CJet_BDT[ih][ir] = new TH1D("h_CJet_BDT_"   + chname[ih] + "_" + regname[ir] + "_" + dirhistosname, "BDT; BDT Corr Jet", 100,-1.,1.);
      c_Jet_BDT [ih][ir] = new TH1D("c_Jet_BDT_"    + chname[ih] + "_" + regname[ir] + "_" + dirhistosname, "BDT Cut; BDT Sel Jet",  100,-.6,.6);

      // b jet (selected by the BDT)
      h_bJet_pT [ih][ir] = new TH1D("h_bJet_pT_"  + chname[ih] + "_" + regname[ir] + "_" + dirhistosname, "pT of b-jet;pT[GeV]",      60,0.,300.);
      h_bJet_eta[ih][ir] = new TH1D("h_bJet_eta_" + chname[ih] + "_" + regname[ir] + "_" + dirhistosname, "#eta of b-jet; #eta",      27,-2.7,2.7);
      h_bJet_phi[ih][ir] = new TH1D("h_bJet_phi_" + chname[ih] + "_" + regname[ir] + "_" + dirhistosname, "Phi of b-jet; Phi",        64,-3.2, 3.2);
      h_bJet_csv[ih][ir] = new TH1D("h_bJet_csv_" + chname[ih] + "_" + regname[ir] + "_" + dirhistosname, "DeepCSV of b-jet; DeepCSV",50, 0., 1.);
      //h_bJet_QGL[ih][ir] = new TH1D("h_bJet_qgl_" + chname[ih] + "_" + regname[ir] + "_" + dirhistosname, "QGL of b-jet; QGL",        50, 0., 1.);

      // -- DPhi
      // GEN Vs RECO
      h_LepJet_DPhi       [ih][ir] = new TH1D    ("h_LepJet_DPhi_"      + chname[ih] + "_" + regname[ir] + "_" + dirhistosname, "DPhi (RECO); #Delta Phi(lep,jet) " ,64,0.,3.2);
      h_lQb_DPhi          [ih][ir] = new TH1D    ("h_lQb_DPhi_"         + chname[ih] + "_" + regname[ir] + "_" + dirhistosname, "DPhi (GEN); #Delta Phi(l,b quark) " ,64,0.,3.2);
      h2D_LepJetVslQb_DPhi[ih][ir] = new TH2D    ("h_LepJetVslQb_DPhi_" + chname[ih] + "_" + regname[ir] + "_" + dirhistosname, "DPhi (RECO Vs GEN); #Delta Phi(lep,jet); #Delta Phi(l,b quark) " ,64,0.,3.2,64,0.,3.2);
      p_LepJetVslQb_DPhi  [ih][ir] = new TProfile("p_LepJetVslQb_DPhi_" + chname[ih] + "_" + regname[ir] + "_" + dirhistosname, "DPhi (RECO Vs GEN); #Delta Phi(lep,jet); #Delta Phi(l,b quark) " ,64,0.,3.2,0.,3.2);
      // RECO: Correct Vs Selected
      h_Corr_DPhi          [ih][ir] = new TH1D    ("h_Corr_DPhi_"         + chname[ih] + "_" + regname[ir] + "_" + dirhistosname, "DPhi (Correct); #Delta Phi(l,jet) " ,64,0.,3.2);
      h2D_LepJetVsCorr_DPhi[ih][ir] = new TH2D    ("h_LepJetVsCorr_DPhi_" + chname[ih] + "_" + regname[ir] + "_" + dirhistosname, "DPhi (RECO Vs Correct); #Delta Phi(lep,jet); #Delta Phi(l,jet) " ,64,0.,3.2,64,0.,3.2);
      p_LepJetVsCorr_DPhi  [ih][ir] = new TProfile("p_LepJetVsCorr_DPhi_" + chname[ih] + "_" + regname[ir] + "_" + dirhistosname, "DPhi (RECO Vs Correct); #Delta Phi(lep,jet); #Delta Phi(l,jet) " ,64,0.,3.2,0.,3.2);

      // -- Mass
      // GEN Vs RECO
      h_LepJet_Mass       [ih][ir] = new TH1D    ("h_LepJet_Mass_"      + chname[ih] + "_" + regname[ir] + "_" + dirhistosname, "Mass; Mass(lep,jet) [GeV]"  ,50,0.,250.);
      h_lQb_Mass          [ih][ir] = new TH1D    ("h_lQb_Mass_"         + chname[ih] + "_" + regname[ir] + "_" + dirhistosname, "Mass (GEN); Mass(l,b quark)[GeV]" ,50,0.,250.);
      h2D_LepJetVslQb_Mass[ih][ir] = new TH2D    ("h_LepJetVslQb_Mass_" + chname[ih] + "_" + regname[ir] + "_" + dirhistosname, "Mass (RECO Vs GEN); Mass(lep,jet)[GeV]; Mass(l,b quark)[GeV]" ,50,0.,250.,50,0.,250.);
      p_LepJetVslQb_Mass  [ih][ir] = new TProfile("p_LepJetVslQb_Mass_" + chname[ih] + "_" + regname[ir] + "_" + dirhistosname, "Mass (RECO Vs GEN); Mass(lep,jet)[GeV]; Mass(l,b quark)[GeV]" ,50,0.,250.,0.,250.);
      // RECO: Correct Vs Selected
      h_Corr_Mass          [ih][ir] = new TH1D    ("h_Corr_Mass_"         + chname[ih] + "_" + regname[ir] + "_" + dirhistosname, "Mass (Correct); Mass(l,jet)[GeV]" ,50,0.,250.);
      h2D_LepJetVsCorr_Mass[ih][ir] = new TH2D    ("h_LepJetVsCorr_Mass_" + chname[ih] + "_" + regname[ir] + "_" + dirhistosname, "Mass (RECO Vs Correct); Mass(lep,jet)[GeV]; Mass(l,jet)[GeV]" ,50,0.,250.,50,0.,250.);
      p_LepJetVsCorr_Mass  [ih][ir] = new TProfile("p_LepJetVsCorr_Mass_" + chname[ih] + "_" + regname[ir] + "_" + dirhistosname, "Mass (RECO Vs Correct); Mass(lep,jet)[GeV]; Mass(l,jet)[GeV]" ,50,0.,250.,0.,250.);

      // -- Other BDT input variables
      // (lep,jet)
      h_LepJet_DR  [ih][ir] = new TH1D("h_LepJet_DR_"   + chname[ih] + "_" + regname[ir] + "_" + dirhistosname, "DR;   #Delta R(lep,jet) "   ,60,0.4,5.);
      h_LepJet_DEta[ih][ir] = new TH1D("h_LepJet_DEta_" + chname[ih] + "_" + regname[ir] + "_" + dirhistosname, "DEta; #Delta #eta(lep,jet) ",50,-5.,5.);
      // (MET,jet)
      h_METJet_DpT [ih][ir] = new TH1D("h_METJet_DpT_"   + chname[ih] + "_" + regname[ir] + "_" + dirhistosname, "DpT; #Delta pT (jet,MET) [GeV]", 100,-200.,300.);
      h_METJet_DPhi[ih][ir] = new TH1D("h_METJet_DPhi_"  + chname[ih] + "_" + regname[ir] + "_" + dirhistosname, "DPhi; #Delta Phi (jet,MET)", 32,0.,3.2);
    
    }
  }


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
    
    TFile *InputFile = TFile::Open("/gpfs/users/sernad/TFM_DanSer/CMSSW_12_0_0/src/TFM_DanSer/inputs/tree_64.root","readonly");
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
    float var1, var2, var3, var4, var5, var6, var7, var8, var9;
    int spec1; float spec2;
    TMVA::Tools::Instance();

    std::cout << "Setup TMVA..." << std::endl;

    //PyKeras
    //We call PyKeras in TMVA, needed to have PyKeras available as a method in TMVA
    TMVA::PyMethodBase::PyInitialize();
  
    // Method to calculate the BDT response
    TMVA::Reader *Reader = new TMVA::Reader( "!Color:!Silent" );

    Reader->AddVariable ( "j_Deep",    &var1 );
    Reader->AddVariable ( "DR_lj",     &var2 );
    Reader->AddVariable ( "Deta_lj",   &var3 );
    Reader->AddVariable ( "DpT_metj",  &var4 );
    Reader->AddVariable ( "DPhi_lj",   &var5 );

    //Reader->AddVariable ( "Deta_lmet", &var6 );
    //Reader->AddVariable ( "DpT_lj",    &var7 );
    //Reader->AddVariable ( "DR_metj",   &var8 );
    Reader->AddVariable ( "DPhi_metj", &var9 );
    Reader->AddSpectator( "region",    &spec1 );
    Reader->AddSpectator( "M_lj",      &spec2 );
    
    Reader->BookMVA("PyKeras", TString("dataset/weights/TMVAClassification_PyKeras.weights.xml"));
    //Reader->BookMVA("BDT",  "TMVAClassification_BDT.weights.xml");
    //Reader->BookMVA("BDT",  "includes/weights_TrFullStataMCatNLORegFrom2_WithDR-v6/TMVAClassification_BDT.weights.xml");
    
    // Evt Loop
    for (Long64_t iEvt=0; iEvt<NTreeEvtToRun; iEvt++) {
      // Progress
      print_progress(NTreeEvtToRun, iEvt);

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

      // GenJets
      std::vector<NanoObj::Jet> GenJets = CreateGenJetCollection(SkimTree);
      // Select genjets and clean from leptons (MC)
      SelectAndCleanGenJets(&GenJets, SeleLepton);


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
      //weight_SFLep = LeptonSF(h2DLeptonSF, ichannel, SeleLepton.Eta(), SeleLepton.Pt(), var::Nom);
      weight_SFLep = 1.;
  	
      // final Event Weight
      weight_lumi = 1.;
      event_weight = weight_lumi*PUweight[var::Nom]*weight_SFLep*weight_btag*weight_Wfraction*mcWeight;

      // Jet pT conditions
      if (!JetCutConditions(&Jets)) continue;
      
      // Number of Jets
      NJets = Jets.size();
      // Selected jet-position
      unsigned int seljetpos = 99;
      float jBDT = -1.;
      float jDR  = -1.;
      std::vector<float> BDTs;            

      for (int ij=0; ij<Jets.size(); ij++){
      	NanoObj::Jet ijet = Jets.at(ij);	
      	// Jet
      	float jetbtag =  ijet.DeepCSV;
      	NLbJets += jetbtag > deepcsvWP_Loose  ? 1:0; 
      	NMbJets += jetbtag > deepcsvWP_Medium ? 1:0; 
      	NTbJets += jetbtag > deepcsvWP_Tight  ? 1:0;

        int NbJets = NMbJets;  
        // QGL
	      //float jQGL = ijet.QGL >= 0. ? ijet.QGL:0.; 
			
      	// -- BDT Variables
      	float Deta_lj   = ijet.Eta()-SeleLepton.Eta();
      	float DR_lj     = ijet.DeltaR(SeleLepton);
      	float DpT_METj  = ijet.Pt() - MET.Pt();
      	float Dphi_METj = std::abs(ijet.Phi() - MET.Phi());
        float Deta_lmet = SeleLepton.Eta()-MET.Eta();
        float DpT_lj    = ijet.Pt() - SeleLepton.Pt();
        float DR_metj   = ijet.DeltaR(MET);
      	if (Dphi_METj > ROOT::Math::Pi()) Dphi_METj = 2.*ROOT::Math::Pi()-Dphi_METj;
	      // DeltaPhi(lep,bjet)
	      double DPhi_lj = std::abs(SeleLepton.Phi()-ijet.Phi());
	      if (DPhi_lj > ROOT::Math::Pi()) DPhi_lj = 2.*ROOT::Math::Pi() - DPhi_lj;
	      // Mass
      	float M_lj = (ijet+SeleLepton).M();


        var1 = jetbtag;
        var2 = DR_lj;
        var3 = Deta_lj;
        var4 = DpT_METj;
        var5 = DPhi_lj;
        var6 = Deta_lmet;
        var7 = DpT_lj;
        var8 = DR_metj;
        var9 = Dphi_METj;

        spec2 = M_lj;

        int sel;
             // Event Selection
        if (NJets == 2 && NbJets == 1)
          sel = 0;
        if (NJets == 2 && NbJets == 2)
          sel = 1;
        if (NJets == 3 && NbJets == 1)
          sel = 2;
        if (NJets == 3 && NbJets == 2)
          sel = 3;
        if (NJets == 3 && NbJets == 3)
          sel = 4;
        if (NJets == 4 && NbJets == 1)
          sel = 5;
        if (NJets == 4 && NbJets == 2)
          sel = 6;
        if (NJets == 4 && NbJets >= 3)
          sel = 7;
        if (NJets >= 5)
          sel = 8;
        if (NJets >= 5 && NbJets >= 2)
          sel = 9;

        spec1 = sel;

      	double BDTResponse  = Reader->EvaluateMVA("PyKeras");
        //double BDTResponse  = Reader->EvaluateMVA("BDT");
	
	      BDTs.push_back(BDTResponse);

        //TMVA::PyMethodBase::PyFinalize();

      	// Lepton-Jet with the highest BDT response
      	if (BDTResponse > jBDT){
      	  jBDT = BDTResponse;
      	  seljetpos = ij;
      	}

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
      int genjetindex = -1;
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
          if (DpT/ijet.Pt() > 0.8 ) continue;
          // DeltaR
          float DR = ijet.DeltaR(Gen_b);
          if(DR < DR_max){
            DR_max = DR;
            jetindex = ij;
          }
        }

	// GenJet object
	DR_max = 0.4;
	for (int igj=0; igj<GenJets.size(); igj++){
	  NanoObj::Jet igjet = GenJets.at(igj);
	  // Flavour
	  if(std::abs(igjet.Flavour) != 5) continue;
	  // pT
	  float DpT = std::abs(igjet.Pt()-Gen_b.Pt());
	  if (DpT/igjet.Pt() > 0.8 ) continue;
	  // DeltaR
	  float DR = igjet.DeltaR(Gen_b);
	  if(DR < DR_max){
	    DR_max = DR;
	    genjetindex = igj;
	  }
	}
	
	
      } // if(lepChargeMatch)


      // using bQuark-RECOJet match
      bool GEvt = (jetindex == seljetpos); // Correct (GEN,BDT) matching
      bool IEvt = (jetindex == -1);        // Impossible matching (No GEN jet associated to the b-quark)


      // -- Event selection
      // -------------------------------------------------
      // To be checked in the new region setup! 
      // -------------------------------------------------
      if (jBDT < BDTcut) continue; 

      int NbJets = NMbJets;      

      bool sel [nreg];
      for (unsigned int irb=0;irb<nreg;irb++) sel [irb] = false;

      float cjBDT = 0.;
      unsigned int ic;
      if      (GEvt) { ic=0;  cjBDT = jBDT; }
      else if (IEvt) { ic=9; }
      else           { ic=18; cjBDT = BDTs.at(jetindex); }

      sel[ic+0]  =  (NJets == 2 && NbJets == 1) ; 
      sel[ic+1]  =  (NJets == 2 && NbJets == 2) ; 
      sel[ic+2]  =  (NJets == 3 && NbJets == 1) ; 
      sel[ic+3]  =  (NJets == 3 && NbJets == 2) ; 
      sel[ic+4]  =  (NJets == 3 && NbJets == 3) ; 
      sel[ic+5]  =  (NJets == 4 && NbJets == 1) ; 
      sel[ic+6]  =  (NJets == 4 && NbJets == 2) ; 
      sel[ic+7]  =  (NJets == 4 && NbJets >= 3) ; 
      sel[ic+8]  =  (NJets >= 5 && NbJets >= 2) ; 

      // Fill histograms
      for(int ir = 0; ir<nreg; ir++){
        if( !sel[ir] ) continue;
	
	      // first channel by channel
        h_PrimVertex[ichannel][ir]->Fill(SkimTree->nVertex, event_weight);	
        // Leptons
        h_Lep_pT [ichannel][ir]->Fill(SeleLepton.Pt(), event_weight);
        h_Lep_eta[ichannel][ir]->Fill(SeleLepton.Eta(), event_weight);
        h_Lep_phi[ichannel][ir]->Fill(SeleLepton.Phi(), event_weight);;

        // Missing Transverse Energy
        h_MET      [ichannel][ir]->Fill(MET.E(), event_weight);
        h_MET_phi  [ichannel][ir]->Fill(MET.Phi(), event_weight);
        // Jet variables
        h_Jet_pT [ichannel][ir]->Fill(Jets.at(0).Pt(),  event_weight);
        h_Jet_eta[ichannel][ir]->Fill(Jets.at(0).Eta(), event_weight);
        h_Jet_phi[ichannel][ir]->Fill(Jets.at(0).Phi(), event_weight);

        // -- BDT
        // BDT values
        h_Jet_BDT[ichannel][ir]->Fill(jBDT,event_weight);
        if (!IEvt) h_CJet_BDT[ichannel][ir]->Fill(cjBDT,event_weight);
        // BDT Cut
        int vBDTCut = c_Jet_BDT[ichannel][ir]->FindBin(jBDT);
        for (int ibin=1; ibin<=vBDTCut; ibin++) c_Jet_BDT[ichannel][ir]->AddBinContent(ibin, event_weight);
        c_Jet_BDT[ichannel][ir]->AddBinContent(101, event_weight); // Total Number of Events 
        
        // -- Lepton,Jet (BDT)
        TLorentzVector SelJet = (TLorentzVector) Jets.at(seljetpos);
        // - b-Jet variables
        h_bJet_pT [ichannel][ir]->Fill(SelJet.Pt(),   event_weight);
        h_bJet_eta[ichannel][ir]->Fill(SelJet.Eta(),  event_weight);
        h_bJet_phi[ichannel][ir]->Fill(SelJet.Phi(),  event_weight);
        h_bJet_csv[ichannel][ir]->Fill(Jets.at(seljetpos).DeepCSV,event_weight);
        //h_bJet_QGL[ichannel][ir]->Fill(Jets.at(seljetpos).QGL,    event_weight); //jQGL
        
        // DeltaR(lep,bjet)
        float DR_lb = SeleLepton.DeltaR(SelJet);
        // DeltaPhi(lep,bjet)
        double DPhi_lb = std::abs(SeleLepton.Phi()-SelJet.Phi());
        if (DPhi_lb > ROOT::Math::Pi()) DPhi_lb = 2.*ROOT::Math::Pi() - DPhi_lb;
        // DetaEta(lep,bjet)
        double DEta_lb = SelJet.Eta()-SeleLepton.Eta();
        // Mass
        float M_lb = (SelJet+SeleLepton).M();
          
        h_LepJet_DR  [ichannel][ir]->Fill(DR_lb,   event_weight);
        h_LepJet_DPhi[ichannel][ir]->Fill(DPhi_lb, event_weight);
        h_LepJet_DEta[ichannel][ir]->Fill(DEta_lb, event_weight);
        h_LepJet_Mass[ichannel][ir]->Fill(M_lb,    event_weight);

        // RECO level: RECO-jet matched to GEN b-quark
        if (!IEvt){
          TLorentzVector CorrJet = (TLorentzVector) Jets.at(jetindex);

          double CorrDPhi_lb = std::abs(SeleLepton.Phi()-CorrJet.Phi());
          if (CorrDPhi_lb > ROOT::Math::Pi()) CorrDPhi_lb = 2.*ROOT::Math::Pi() - CorrDPhi_lb;	  
          h_Corr_DPhi          [ichannel][ir]->Fill(CorrDPhi_lb,         event_weight);
          h2D_LepJetVsCorr_DPhi[ichannel][ir]->Fill(DPhi_lb,CorrDPhi_lb, event_weight);
          p_LepJetVsCorr_DPhi  [ichannel][ir]->Fill(DPhi_lb,CorrDPhi_lb, event_weight);	  

          float CorrM_lb = (CorrJet+SeleLepton).M();
          h_Corr_Mass          [ichannel][ir]->Fill(CorrM_lb,      event_weight);
          h2D_LepJetVsCorr_Mass[ichannel][ir]->Fill(M_lb,CorrM_lb, event_weight);
          p_LepJetVsCorr_Mass  [ichannel][ir]->Fill(M_lb,CorrM_lb, event_weight);	

	      }// if(!IEvt)

        if(genjetindex > -1){
          // -- GEN level: Lep,b-GenJet
          TLorentzVector GenJet_Obj = (TLorentzVector) GenJets.at(genjetindex);
          // DPhi
          double GenDPhi_lgjb = std::abs(Gen_l.Phi()-GenJet_Obj.Phi());
        }

        // -- GEN level: Lep,b-quark
        // DPhi
        double GenDPhi_lb = std::abs(Gen_l.Phi()-Gen_b.Phi());
        if (GenDPhi_lb > ROOT::Math::Pi()) GenDPhi_lb = 2.*ROOT::Math::Pi() - GenDPhi_lb;
        h_lQb_DPhi          [ichannel][ir]->Fill(GenDPhi_lb,         event_weight);
        h2D_LepJetVslQb_DPhi[ichannel][ir]->Fill(DPhi_lb,GenDPhi_lb, event_weight);
        p_LepJetVslQb_DPhi  [ichannel][ir]->Fill(DPhi_lb,GenDPhi_lb, event_weight);
        // Mass
        float GenM_lb = (Gen_l+Gen_b).M();
        h_lQb_Mass          [ichannel][ir]->Fill(GenM_lb,          event_weight);
        h2D_LepJetVslQb_Mass[ichannel][ir]->Fill(M_lb,GenM_lb, event_weight);
        p_LepJetVslQb_Mass  [ichannel][ir]->Fill(M_lb,GenM_lb, event_weight);

        // BDT: MET Inputs
        float DpT_METb  = SelJet.Pt()  - MET.Pt();
        float Dphi_METb = std::abs(SelJet.Phi() - MET.Phi());
        if (Dphi_METb > ROOT::Math::Pi()) Dphi_METb = 2.*ROOT::Math::Pi()-Dphi_METb;	
        h_METJet_DpT   [ichannel][ir]->Fill(DpT_METb,  event_weight);
        h_METJet_DPhi  [ichannel][ir]->Fill(Dphi_METb, event_weight);


        // -- GEN level: Lep,b-quark
        //TLorentzVector Gen_Obj = (TLorentzVector) Gen_b;
        // DPhi
        //double GenDPhi_lb = std::abs(Gen_l.Phi()-Gen_Obj.Phi());

      }
	
    } // for (iEvent)
    
    delete Reader;
    
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

  // ---------------------------------
  // Create histograms for all channel 
  // ---------------------------------
  std::cout << "-- Creating ALL channels histograms --\n " << std::endl;

  for (unsigned int ih = 0; ih<ch::all; ih++){
    for (unsigned int ir = 0; ir<nreg; ir++){
      // Event variables
      h_PrimVertex[ch::all][ir]->Add(h_PrimVertex[ih][ir]);
      // Lepton variables
      h_Lep_pT [ch::all][ir]->Add(h_Lep_pT[ih][ir]);
      h_Lep_eta[ch::all][ir]->Add(h_Lep_eta[ih][ir]);
      h_Lep_phi[ch::all][ir]->Add(h_Lep_phi[ih][ir]);
      // BDT
      h_Jet_BDT [ch::all][ir]->Add(h_Jet_BDT[ih][ir]);
      h_CJet_BDT[ch::all][ir]->Add(h_CJet_BDT[ih][ir]);
      c_Jet_BDT [ch::all][ir]->Add(c_Jet_BDT[ih][ir]);
      // Jet variables
      h_Jet_pT    [ch::all][ir]->Add(h_Jet_pT[ih][ir]);
      h_Jet_eta   [ch::all][ir]->Add(h_Jet_eta[ih][ir]);
      h_Jet_phi   [ch::all][ir]->Add(h_Jet_phi[ih][ir]);
      // MET
      h_MET      [ch::all][ir]->Add(h_MET[ih][ir]);
      h_MET_phi  [ch::all][ir]->Add(h_MET_phi[ih][ir]);
      // b-jet
      h_bJet_pT    [ch::all][ir]->Add(h_bJet_pT[ih][ir]);
      h_bJet_eta   [ch::all][ir]->Add(h_bJet_eta[ih][ir]);
      h_bJet_phi   [ch::all][ir]->Add(h_bJet_phi[ih][ir]);
      h_bJet_csv   [ch::all][ir]->Add(h_bJet_csv[ih][ir]);
      //h_bJet_QGL   [ch::all][ir]->Add(h_bJet_QGL[ih][ir]);
      // Lepton,b jet
      h_LepJet_DR    [ch::all][ir]->Add(h_LepJet_DR[ih][ir]);
      h_LepJet_DEta  [ch::all][ir]->Add(h_LepJet_DEta[ih][ir]);
      h_LepJet_DPhi  [ch::all][ir]->Add(h_LepJet_DPhi[ih][ir]);
      h_LepJet_Mass  [ch::all][ir]->Add(h_LepJet_Mass[ih][ir]);
      // Additional DPhi plots
      h_lQb_DPhi           [ch::all][ir]->Add(h_lQb_DPhi           [ih][ir]);
      h2D_LepJetVslQb_DPhi [ch::all][ir]->Add(h2D_LepJetVslQb_DPhi [ih][ir]);
      p_LepJetVslQb_DPhi   [ch::all][ir]->Add(p_LepJetVslQb_DPhi   [ih][ir]);
      h_Corr_DPhi          [ch::all][ir]->Add(h_Corr_DPhi          [ih][ir]);
      h2D_LepJetVsCorr_DPhi[ch::all][ir]->Add(h2D_LepJetVsCorr_DPhi[ih][ir]);
      p_LepJetVsCorr_DPhi  [ch::all][ir]->Add(p_LepJetVsCorr_DPhi  [ih][ir]);
      // Additional Mass plots
      h_lQb_Mass           [ch::all][ir]->Add(h_lQb_Mass           [ih][ir]);
      h2D_LepJetVslQb_Mass [ch::all][ir]->Add(h2D_LepJetVslQb_Mass [ih][ir]);
      p_LepJetVslQb_Mass   [ch::all][ir]->Add(p_LepJetVslQb_Mass   [ih][ir]);
      h_Corr_Mass          [ch::all][ir]->Add(h_Corr_Mass          [ih][ir]);
      h2D_LepJetVsCorr_Mass[ch::all][ir]->Add(h2D_LepJetVsCorr_Mass[ih][ir]);
      p_LepJetVsCorr_Mass  [ch::all][ir]->Add(p_LepJetVsCorr_Mass  [ih][ir]);
      // BDT: MET variables
      h_METJet_DpT   [ch::all][ir]->Add(h_METJet_DpT[ih][ir]);
      h_METJet_DPhi  [ch::all][ir]->Add(h_METJet_DPhi[ih][ir]);
 
    }// for(ir)
  } //for(ich)

  std::cout << "-------- Saving histograms ------- " << std::endl;
  OutputFile->cd();
  OutputFile->mkdir(dirhistosname);

  for (unsigned int ih = 0; ih<ch::all+1; ih++){
    OutputFile->mkdir(dirhistosname + "/" + chname[ih]);
    OutputFile->cd(dirhistosname + "/" + chname[ih]);
    for (unsigned int ir = 0; ir<nreg; ir++){
      OutputFile->mkdir(dirhistosname + "/" + chname[ih] + "/" + regname[ir]);
      OutputFile->cd(dirhistosname + "/" + chname[ih] + "/" + regname[ir]);
     
      // Event variables
      h_PrimVertex[ih][ir]->Write();
      // Lepton variables
      h_Lep_pT [ih][ir]->Write();
      h_Lep_eta[ih][ir]->Write();
      h_Lep_phi[ih][ir]->Write();
      // BDT
      h_Jet_BDT[ih][ir]->Write();
      h_CJet_BDT[ih][ir]->Write();
      c_Jet_BDT[ih][ir]->Write();
      // Jet variables
      h_Jet_pT    [ih][ir]->Write();
      h_Jet_eta   [ih][ir]->Write();
      h_Jet_phi   [ih][ir]->Write();
      // MET
      h_MET      [ih][ir]->Write();
      h_MET_phi  [ih][ir]->Write();
      // b-jet
      h_bJet_pT    [ih][ir]->Write();
      h_bJet_eta   [ih][ir]->Write();
      h_bJet_phi   [ih][ir]->Write();
      h_bJet_csv   [ih][ir]->Write();
      //h_bJet_QGL   [ih][ir]->Write();
      // Lepton,b jet
      h_LepJet_DR    [ih][ir]->Write();
      h_LepJet_DEta  [ih][ir]->Write();
      h_LepJet_DPhi  [ih][ir]->Write();
      h_LepJet_Mass  [ih][ir]->Write();
      // Additional DPhi plots
      h_lQb_DPhi           [ih][ir]->Write();
      h2D_LepJetVslQb_DPhi [ih][ir]->Write();
      p_LepJetVslQb_DPhi   [ih][ir]->Write();
      h_Corr_DPhi          [ih][ir]->Write();
      h2D_LepJetVsCorr_DPhi[ih][ir]->Write();
      p_LepJetVsCorr_DPhi  [ih][ir]->Write();
      // Additional Mass plots
      h_lQb_Mass           [ih][ir]->Write();
      h2D_LepJetVslQb_Mass [ih][ir]->Write();
      p_LepJetVslQb_Mass   [ih][ir]->Write();
      h_Corr_Mass          [ih][ir]->Write();
      h2D_LepJetVsCorr_Mass[ih][ir]->Write();
      p_LepJetVsCorr_Mass  [ih][ir]->Write();
      // BDT: MET variables
      h_METJet_DpT   [ih][ir]->Write();
      h_METJet_DPhi  [ih][ir]->Write();

    }// for(ir)
  } //for(ich)

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