// Read 3D histograms
std::vector<histos> load3Dhistograms(TString region, TString namefile){
  
  /* TFile *file=NULL; // new TFile(namefile); */
  /* file = TFile::Open(namefile + ".root"); */
  /* std::cout << "Loading " << namefile << ".root file..." << endl; */
  
  /* if(!file){ */
  /*   std::cerr << "ERROR: Could not open " <<  namefile  << " files!!!"  << std::endl; */
  /*   std::exit(0); */
  /* } */
  
  std::vector<histos> sample;
  histos histofile;  

  return sample;
  
}

// Read 2D histograms
std::vector<histos> load2Dhistograms(TString region, TString namefile){

  TFile *file=NULL; // new TFile(namefile);
  file = TFile::Open(namefile + ".root");
  std::cout << "Loading " << namefile << ".root file..." << endl;
  
  if(!file){
    std::cerr << "ERROR: Could not open " <<  namefile  << " files!!!"  << std::endl;
    std::exit(0);
  }
  
  std::vector<histos> sample;
  histos histofile;
  histofile.units = "LepISO";
    
  std::vector<TString> histoname;
  std::vector<TString> histounits;
  // ----------------------------------------------------
  // -- New bin 0: (0,25,50)
  for(unsigned int ch=0; ch<channel.size(); ch++){  
    // Standard input
    TString Bin0 = "central/" + channel[ch] + "/" + region + "/h2D_LepISOVsBDT_0_25_"  + channel[ch] + "_" + region + "_central";
    TString Bin1 = "central/" + channel[ch] + "/" + region + "/h2D_LepISOVsBDT_25_50_" + channel[ch] + "_" + region + "_central";
    TH2D *inpHis;
    inpHis   =  (TH2D*)(file->Get(Bin0))->Clone();
    inpHis->Add((TH2D*)(file->Get(Bin1))->Clone());

    inpHis->SetDirectory(0);
    inpHis->SetName("h2D_LepISOVsBDT_0_50_" + channel[ch] + "_" + region + "_central");
    histofile.hist2D[ch] = inpHis;
  }
  sample.push_back(histofile);
  // ----------------------------------------------------
  // -- New bin 1: (50,75,100)
  for(unsigned int ch=0; ch<channel.size(); ch++){  
    // Standard input
    TString Bin0 = "central/" + channel[ch] + "/" + region + "/h2D_LepISOVsBDT_50_75_"  + channel[ch] + "_" + region + "_central";
    TString Bin1 = "central/" + channel[ch] + "/" + region + "/h2D_LepISOVsBDT_75_100_" + channel[ch] + "_" + region + "_central";
    TH2D *inpHis;
    inpHis   =  (TH2D*)(file->Get(Bin0))->Clone();
    inpHis->Add((TH2D*)(file->Get(Bin1))->Clone());

    inpHis->SetDirectory(0);
    inpHis->SetName("h2D_LepISOVsBDT_50_100_" + channel[ch] + "_" + region + "_central");
    histofile.hist2D[ch] = inpHis;
  }  
  sample.push_back(histofile);
  // ----------------------------------------------------
  // -- New bin 2: (100,125,150)
  for(unsigned int ch=0; ch<channel.size(); ch++){  
    // Standard input
    TString Bin0 = "central/" + channel[ch] + "/" + region + "/h2D_LepISOVsBDT_100_125_"  + channel[ch] + "_" + region + "_central";
    TString Bin1 = "central/" + channel[ch] + "/" + region + "/h2D_LepISOVsBDT_125_150_" + channel[ch] + "_" + region + "_central";
    TH2D *inpHis;
    inpHis   =  (TH2D*)(file->Get(Bin0))->Clone();
    inpHis->Add((TH2D*)(file->Get(Bin1))->Clone());

    inpHis->SetDirectory(0);
    inpHis->SetName("h2D_LepISOVsBDT_100_150_" + channel[ch] + "_" + region + "_central");
    histofile.hist2D[ch] = inpHis;
  }  
  sample.push_back(histofile);
  // ----------------------------------------------------


  // Histograms
  /* histoname.push_back("h2D_LepISOVsBDT_0_25"); */
  /* histounits.push_back("LepISO"); */
  /* histoname.push_back("h2D_LepISOVsBDT_25_50"); */
  /* histounits.push_back("LepISO"); */
  /* histoname.push_back("h2D_LepISOVsBDT_50_75"); */
  /* histounits.push_back("LepISO"); */
  /* histoname.push_back("h2D_LepISOVsBDT_75_100"); */
  /* histounits.push_back("LepISO"); */
  /* histoname.push_back("h2D_LepISOVsBDT_100_125"); */
  /* histounits.push_back("LepISO"); */

  // ----------------------------------------------------
  // -- New bin 3: (150,250)
  histoname.push_back("h2D_LepISOVsBDT_150_250");
  histounits.push_back("LepISO");
  // ----------------------------------------------------
  // -- Total
  histoname.push_back("h2D_LepISOVsBDT");
  histounits.push_back("LepISO");
  // ----------------------------------------------------
  
  for(unsigned int h=0; h<histoname.size(); h++){
    for(unsigned int ch=0; ch<channel.size(); ch++){
      
      // Standard input
      TString FullName = "central/" + channel[ch] + "/" + region + "/" +  histoname[h] + "_" + channel[ch] + "_" + region + "_central";
      
      // std::cout << "Name: " << FullName << std::endl;
      TH2D *inpHis;
      inpHis = (TH2D*)(file->Get(FullName))->Clone();
      inpHis->SetDirectory(0);

      histofile.hist2D[ch] = inpHis;
    }

    histofile.units = histounits.at(h);
    sample.push_back(histofile);
  }  

  file->Close();
  delete file;
  
  cout << "All the 2D histograms from " << namefile << ".root have been loaded successfully with " << sample.size() << " histograms..." << endl;
  
  return sample;
}
    

// Read histograms
std::vector<histos> loadhistograms(TString region, TString namefile, bool Combine = false, TString namesys="central", bool IsQCDDD=false, bool DivBinWidth=false){

  if (Combine) namefile = namefile + "_COMBINE";
  
  TFile *file=NULL; // new TFile(namefile);
  file = TFile::Open(namefile + ".root");
  std::cout << "Loading " << namefile << ".root file..." << endl;
  
  if(!file){
    std::cerr << "ERROR: Could not open " <<  namefile  << " files!!!"  << std::endl;
    std::exit(0);
  }
  
  std::vector<histos> sample;
  histos histofile;
    
  std::vector<TString> histoname;
  std::vector<TString> histounits;

  // Histograms

  if (Combine){    
    histoname.push_back("Fixed_h_LepJet_Mass");
    histounits.push_back("Mass(lep,jet) [GeV]");
    /* histoname.push_back("Fixed_h_LepJet_DPhi"); */
    /* histounits.push_back("DPhi(lep,jet)"); */
  }
  else{
    if(IsQCDDD){
      histoname.push_back("LepJet_Mass");
      histounits.push_back("Mass(lep,jet) [GeV]");

      /* histoname.push_back("LepJet_DPhi"); */
      /* histounits.push_back("DPhi(lep,jet)"); */

      /* histoname.push_back("LepJet_DR"); */
      /* histounits.push_back("DR(lep,jet)"); */

      /* histoname.push_back("BDTSel"); */
      /* histounits.push_back("BDT Response"); */
      
      /* histoname.push_back("Lep_pT"); */
      /* histounits.push_back("Lepton pT [GeV]"); */

      /* histoname.push_back("Lep_eta"); */
      /* histounits.push_back("Lepton #eta"); */

      /* histoname.push_back("Lep_phi"); */
      /* histounits.push_back("Lepton #phi"); */

      /* histoname.push_back("Jet_pT"); */
      /* histounits.push_back("Leading jet p_{T} [GeV]"); */

      /* histoname.push_back("Jet_eta"); */
      /* histounits.push_back("Leading jet #eta"); */

      /* histoname.push_back("Jet_phi"); */
      /* histounits.push_back("Leading jet #phi"); */

      /* histoname.push_back("SecJet_pT"); */
      /* histounits.push_back("Second leading jet p_{T} [GeV]"); */

      /* histoname.push_back("SecJet_eta"); */
      /* histounits.push_back("Second leading jet #eta"); */

    }
    else{
      histoname.push_back("LepJet_DPhi");
      histounits.push_back("#Delta#phi(lep,jet) [rad]");
      
      histoname.push_back("LepJet_Mass");
      histounits.push_back("Mass(lep,jet) [GeV]");
      
      /* histoname.push_back("LepJet_DPhiFullRange"); */
      /* histounits.push_back("#Delta#phi(lep,jet) [rad]"); */
      
      histoname.push_back("LepJet_DR");
      histounits.push_back("#Delta R(lep,jet)");

      histoname.push_back("LepJet_DEta");
      histounits.push_back("#Delta#eta(lep,jet)");

      histoname.push_back("BDTSel");
      histounits.push_back("BDT Response");

      histoname.push_back("PrimVertex");
      histounits.push_back("Number of vertices");

      histoname.push_back("MET");
      histounits.push_back("MET [GeV]");

      histoname.push_back("MET_phi");
      histounits.push_back("#phi_{MET}");

      /* histoname.push_back("METCorr"); */
      /* histounits.push_back("MET [GeV]"); */

      /* histoname.push_back("METCorr_phi"); */
      /* histounits.push_back("#phi_{MET}"); */

      histoname.push_back("Lep_pT");
      histounits.push_back("Lepton pT [GeV]");

      histoname.push_back("Lep_eta");
      histounits.push_back("Lepton #eta");

      histoname.push_back("Lep_phi");
      histounits.push_back("Lepton #phi");

      histoname.push_back("NJets");
      histounits.push_back("Number of jets");

      histoname.push_back("NMbJets");
      histounits.push_back("Number of b-jets (medium)");

      /* histoname.push_back("NLbJets"); */
      /* histounits.push_back("Number of b-jets (loose)"); */

      /* histoname.push_back("NTbJets"); */
      /* histounits.push_back("Number of b-jets (tight)"); */

      histoname.push_back("Jet_pT");
      histounits.push_back("Leading jet p_{T} [GeV]");

      histoname.push_back("Jet_eta");
      histounits.push_back("Leading jet #eta ");

      histoname.push_back("Jet_phi");
      histounits.push_back("Leading jet #phi ");

      histoname.push_back("SecJet_pT");
      histounits.push_back("Second jet p_{T} [GeV]");

      histoname.push_back("SecJet_eta");
      histounits.push_back("Second jet #eta ");

      histoname.push_back("SecJet_phi");
      histounits.push_back("Second jet #phi ");

      /* histoname.push_back("Jet_QGL"); */
      /* histounits.push_back("Leading jet QGL "); */

      /* histoname.push_back("Jet_DeepCSV"); */
      /* histounits.push_back("Leading jet DeepCSV "); */

    }
  }


  if(namefile.Contains("LepJets_SYS")){
    //namesys = "jet_JERNom";
  }
  
  for(unsigned int h=0; h<histoname.size(); h++){
    for(unsigned int ch=0; ch<channel.size(); ch++){

      // Standard input
      TString FullName = namesys + "/" + channel[ch] + "/" + region + "/h_" +  histoname[h] + "_" + channel[ch] + "_" + region + "_" + namesys;
      // Combine input
      if (Combine) {
	FullName = histoname[h] + "_" + channel[ch] + "_" + region + "_" + namesys;
	// Compare wrt the normalized samples.
	// if(namesys !="central") FullName = "Norm_" + FullName;
      }
      TH1D *inpHis;
      inpHis = (TH1D*)(file->Get(FullName))->Clone();
      inpHis->Rebin(1);
      inpHis->SetDirectory(0);

      // To draw distributions with Evt/Bin width
      //if(DivBinWidth) BinningAdjust(inpHis);
      
      // std::cout << "Name: " << FullName << " Bins = " << inpHis->GetNbinsX()  << " Nevt = " << inpHis->Integral() << std::endl;

      if(namesys == "central" || namesys.Contains("ScME_R") || namesys.Contains("JERNom"))
	 histofile.hist[ch] = inpHis;
      else if (namesys.EndsWith("Up"))
	histofile.Up[ch] = inpHis;
      else if (namesys.EndsWith("Down"))
	histofile.Dw[ch] = inpHis;
    }

    histofile.units = histounits.at(h);
      
    sample.push_back(histofile);
  }  

  file->Close();
  delete file;
  
  cout << "All the histograms from " << namefile << ".root have been loaded successfully with " << sample.size() << " histograms..." << endl;
  
  return sample;
}

// Read files from TEMPLATES
std::vector<histos> loadtemplates(TString namefile, std::vector<TString> hNamefile, TString HistoName, TString Region){
  
  std::vector<histos> CombHistos;

  for(int ih=0;ih<hNamefile.size();ih++){      

    if(hNamefile.at(ih) == "total" ||
       hNamefile.at(ih) == "total_signal" || hNamefile.at(ih) == "total_background" )
      continue;

    
    TFile *file=NULL; // new TFile(namefile);
    file = TFile::Open(namefile + "/" + hNamefile.at(ih) + ".root");
    std::cout << "Loading " << namefile + "/" + hNamefile.at(ih) << ".root file..." << endl;
    
    if(!file){
      std::cerr << "ERROR: Could not open " <<  namefile  << " files!!!"  << std::endl;
      std::exit(0);
    }
    
    histos CombHisto;

    for(unsigned int ch=0; ch<2; ch++){
      // Standard input
      TString NamHisto = HistoName + "_" + channel.at(ch) + "_" + Region + "_central";
      std::cout << "Reading " << NamHisto << std::endl; 
      CombHisto.hist[ch] = (TH1D*)(file->Get(NamHisto))->Clone(hNamefile.at(ih));
      CombHisto.hist[ch]->SetDirectory(0);
    }
    
    CombHisto.hist[2] = (TH1D*)CombHisto.hist[0]->Clone();
    CombHisto.hist[2]->SetDirectory(0);    
    CombHisto.hist[2]->Add(CombHisto.hist[1]);

    
    CombHistos.push_back(CombHisto);

    file->Close();
    delete file;
    
  }

  // Same COMBINE categories
  histos CombHistoTotal;
  histos CombHistoTotalSgn;
  histos CombHistoTotalBkg;

  for(unsigned int ch=0; ch<3; ch++){
    CombHistoTotal.hist[ch]    = (TH1D*)CombHistos.at(0).hist[ch]->Clone("total");
    CombHistoTotalSgn.hist[ch] = (TH1D*)CombHistos.at(2).hist[ch]->Clone("total_signal");
    CombHistoTotalBkg.hist[ch] = (TH1D*)CombHistos.at(0).hist[ch]->Clone("total_background");
  }
  
  for(int ih=0;ih<hNamefile.size();ih++){
    for(unsigned int ch=0; ch<3; ch++){

      if (ih <= 4)        CombHistoTotal.hist[ch]   ->Add (CombHistos.at(ih).hist[ch]);
      if (ih > 1 && ih <= 4) CombHistoTotalSgn.hist[ch]->Add (CombHistos.at(ih).hist[ch]);
      
    }
  }

  CombHistos.push_back(CombHistoTotal);
  CombHistos.push_back(CombHistoTotalSgn);
  CombHistos.push_back(CombHistoTotalBkg);

  
  // DATA
  TFile *file=NULL; // new TFile(namefile);
  file = TFile::Open(namefile + "/DataSingleLepton_COMBINE.root");
  std::cout << "Loading " << namefile + "/DataSingleLepton_COMBINE.root file..." << endl;  
  if(!file){
    std::cerr << "ERROR: Could not open DataSingleLepton_COMBINE.root files!!!"  << std::endl;
    std::exit(0);
  }
  
  histos CombHistoData;
  for(unsigned int ch=0; ch<2; ch++){
    // Standard input
    TString NamHisto = HistoName + "_" + channel.at(ch) + "_" + Region + "_central";
    CombHistoData.hist[ch] = (TH1D*)(file->Get(NamHisto))->Clone("Data_COMBINE");
    CombHistoData.hist[ch]->SetDirectory(0);
  }
    
  CombHistoData.hist[2] = (TH1D*)CombHistoData.hist[0]->Clone("Data_COMBINE");
  CombHistoData.hist[2]->SetDirectory(0);    
  CombHistoData.hist[2]->Add(CombHistoData.hist[1]);
  
  CombHistos.push_back(CombHistoData);
  
  file->Close();
  delete file;

  
  return CombHistos;
}



// Read files from COMBINE OUTPUT
std::vector<histos> loadcombine(TString path[2], TString namefile, std::vector<TString> hNamefile){
  
  TFile *file=NULL; // new TFile(namefile);
  file = TFile::Open(namefile + ".root");
  std::cout << "Loading " << namefile << ".root file..." << endl;
  
  if(!file){
    std::cerr << "ERROR: Could not open " <<  namefile  << " files!!!"  << std::endl;
    std::exit(0);
  }

  std::vector<histos> CombHistos;
  
  for(int ih=0;ih<hNamefile.size();ih++){      
    histos CombHisto;
    for(unsigned int ch=0; ch<2; ch++){
      // Standard input
      TString NamHisto = path[ch] + hNamefile.at(ih);
      cout << "Reading " << NamHisto << endl;
      CombHisto.hist[ch] = (TH1D*)(file->Get(NamHisto))->Clone();
      CombHisto.hist[ch]->SetDirectory(0);
    }

    CombHisto.hist[2] = (TH1D*)CombHisto.hist[0]->Clone();
    CombHisto.hist[2]->SetDirectory(0);

    CombHisto.hist[2]->Add(CombHisto.hist[1]);
    CombHistos.push_back(CombHisto);
  }  

  // Data TGraph
  cout << "Loading DATA histograms..." << endl;

  histos CombData;
  for(unsigned int ch=0; ch<2; ch++){

    CombData.hist[ch] = (TH1D*)CombHistos.at(0).hist[ch]->Clone("Data_COMBINE");
    CombData.hist[ch]->SetDirectory(0);
    CombData.hist[ch]->Reset();

    // Standard input
    TString NamHisto = path[ch] + "data";
    cout << "Reading data " << NamHisto << " -> " << CombData.hist[ch]->GetNbinsX() << endl;
    TGraphAsymmErrors *DataFull = (TGraphAsymmErrors *) file->Get(NamHisto)->Clone();

    for(int ibin=1;ibin<=CombData.hist[ch]->GetNbinsX();ibin++){ 

      double igb, EvtBinData, EvtErrBinData;
      DataFull->GetPoint((ibin-1),igb,EvtBinData); 
      CombData.hist[ch]->SetBinContent(ibin,EvtBinData);
      EvtErrBinData = DataFull->GetErrorY((ibin-1));
      CombData.hist[ch]->SetBinError(ibin,EvtErrBinData);

    }
  }

  CombData.hist[2] = (TH1D*)CombData.hist[0]->Clone();
  CombData.hist[2]->SetDirectory(0);
  CombData.hist[2]->Add(CombData.hist[1]);
  

  file->Close();
  delete file;

  CombHistos.push_back(CombData);
  return CombHistos;
}



// Add histograms
std::vector<histos> addhistograms(std::vector<histos> histos_0, std::vector<histos> histos_1){

  std::vector<histos> sum;
  histos histos;

  for(unsigned int h = 0; h < histos_0.size(); h++){
    histos.units = histos_0[h].units;
    for(unsigned int ch=0; ch<channel.size(); ch++){  
      // 1D
      if(histos_0[h].hist[ch]){
	cout << "Adding 1D histograms..." << endl;
	histos.hist[ch] = (TH1D*)histos_0[h].hist[ch]->Clone();
	histos.hist[ch]->Add(histos_0[h].hist[ch], histos_1[h].hist[ch]);
      }
      // Up
      if(histos_0[h].Up[ch]){
	cout << "Adding Up histograms..." << endl;
	histos.Up[ch] = (TH1D*)histos_0[h].Up[ch]->Clone();
	histos.Up[ch]->Add(histos_0[h].Up[ch], histos_1[h].Up[ch]);
      }
      // Down
      if(histos_0[h].Dw[ch]){
	cout << "Adding Down histograms..." << endl;
	histos.Dw[ch] = (TH1D*)histos_0[h].Dw[ch]->Clone();
	histos.Dw[ch]->Add(histos_0[h].Dw[ch], histos_1[h].Dw[ch]);
      }
      // 2D
      if(histos_0[h].hist2D[ch]){
	cout << "Adding 2D histograms..." << endl;
	histos.hist2D[ch] = (TH2D*)histos_0[h].hist2D[ch]->Clone();
	histos.hist2D[ch]->Add(histos_0[h].hist2D[ch], histos_1[h].hist2D[ch]);
      }
    }
    sum.push_back(histos);
  }

  return sum;
}

// Add channels
std::vector<histos> addchannels(std::vector<histos> histos_0, std::vector<histos> histos_1){

  std::vector<histos> sum;

  for(unsigned int h = 0; h < histos_0.size(); h++){

    histos histo;
      
    histo.hist[0] = (TH1D*)histos_0[h].hist[0]->Clone();
    histo.hist[1] = (TH1D*)histos_1[h].hist[1]->Clone();
    
    histo.hist[2] = (TH1D*)histo.hist[0]->Clone();
    histo.hist[2]->Add(histos_0[h].hist[0], histos_1[h].hist[1]);
    
    sum.push_back(histo);

  }

  return sum;
}


std::vector<histos> initsystematic(std::vector<histos> hisCe,  std::vector<histos> hisUp, std::vector<histos> hisDw, bool resethisto = false){

  std::vector<histos> unc;
  
  for(unsigned int h = 0; h < hisCe.size(); h++){
    histos histo;
    for(unsigned int ch=0; ch<channel.size(); ch++){

      histo.hist[ch] = (TH1D*)hisCe[h].hist[ch]->Clone();
      
      if(resethisto){

	histo.Up[ch] = (TH1D*)hisCe[h].hist[ch]->Clone();
	histo.Dw[ch] = (TH1D*)hisCe[h].hist[ch]->Clone();
	
	histo.hist[ch]->Reset();
	histo.Up[ch]  ->Reset();
	histo.Dw[ch]  ->Reset();
      }
      else{
	histo.Up[ch] = (TH1D*)hisUp[h].Up[ch]->Clone();
	histo.Dw[ch] = (TH1D*)hisDw[h].Dw[ch]->Clone();
      }
      
    }

    histo.units = hisCe[h].units;
    unc.push_back(histo);
    
  }  

  return unc;

}

void ExtrapolateSysVar(std::vector<histos> hisCen,
		       std::vector<histos> hisVar){
  
  for(unsigned int h = 0; h < hisVar.size(); h++){
    for(unsigned int ch=0; ch<channel.size(); ch++){  
      for (int ib=1;ib<=hisCen[h].hist[ch]->GetNbinsX();ib++){
	
	double vCe = hisVar[h].hist[ch]->GetBinContent(ib);
	double vUp = hisVar[h].Up[ch]  ->GetBinContent(ib);
	double vDw = hisVar[h].Dw[ch]  ->GetBinContent(ib);
	
	double eDw = (vCe-vDw);
	double eUp = (vUp-vCe);
	
	if(vCe != 0.) { eDw = eDw/vCe; eUp = eUp/vCe; }
	else { eDw = 0.; eUp = 0.; }
	
	double Up = eUp*hisCen[h].hist[ch]->GetBinContent(ib);
	double Dw = eDw*hisCen[h].hist[ch]->GetBinContent(ib);	
	
	hisVar[h].hist[ch]->SetBinContent(ib,    hisCen[h].hist[ch]->GetBinContent(ib));
	hisVar[h].Up[ch]  ->SetBinContent(ib,eUp*hisCen[h].hist[ch]->GetBinContent(ib));
	hisVar[h].Dw[ch]  ->SetBinContent(ib,eDw*hisCen[h].hist[ch]->GetBinContent(ib));

      }// for(ib)
      
    }// for(ch)
    
  }// for(histo)
  
}

// Add systematic histograms in quadrature 
void addsystematic(std::vector<histos> hisInit, std::vector<histos> his, TString SysName = "All"){

  bool sysmatch = false;
  if (SysName != "All") sysmatch = true;
  
  for(unsigned int h = 0; h < his.size(); h++){
    for(unsigned int ch=0; ch<channel.size(); ch++){  

      TString hname = (TString)his[h].Up[ch]->GetName();
      if (sysmatch){
	if (!hname.Contains(SysName)) continue;
      }

      for (int ib=1;ib<=his[h].hist[ch]->GetNbinsX();ib++){
	
	double vCe = his[h].hist[ch]->GetBinContent(ib);
	double vUp = his[h].Up[ch]  ->GetBinContent(ib);
	double vDw = his[h].Dw[ch]  ->GetBinContent(ib);

	double eDw = (vCe-vDw);
	double eUp = (vUp-vCe);

	if(vCe != 0.) { eDw = 100.*eDw/vCe; eUp = 100.*eUp/vCe; }
	else { eDw = 0.; eUp = 0.; }
	
	if(eUp > 0.)
	  hisInit[h].Up[ch]->SetBinContent(ib,
					   sqrt((hisInit[h].Up[ch]->GetBinContent(ib)*hisInit[h].Up[ch]->GetBinContent(ib)) + (eUp*eUp)));
	else{
	  hisInit[h].Dw[ch]->SetBinContent(ib,
					   sqrt((hisInit[h].Dw[ch]->GetBinContent(ib)*hisInit[h].Dw[ch]->GetBinContent(ib)) + (eUp*eUp)));
	}
	
	if(eDw > 0.)
	  hisInit[h].Dw[ch]->SetBinContent(ib,
					   sqrt((hisInit[h].Dw[ch]->GetBinContent(ib)*hisInit[h].Dw[ch]->GetBinContent(ib)) + (eDw*eDw)));
	else {
	  hisInit[h].Up[ch]->SetBinContent(ib,
					   sqrt((hisInit[h].Up[ch]->GetBinContent(ib)*hisInit[h].Up[ch]->GetBinContent(ib)) + (eDw*eDw)));
	}

      }// for(ib)

    }// for(ch)
    
  }// for(histo)

}

// For Scale variations at ME
std::vector<histos> FindMaxVariation(std::vector<histos> hisNom, std::vector< std::vector<histos> > hisScME){

  std::vector<histos> TotScME;
  
  for(unsigned int isc = 0; isc < hisScME.size(); isc++){

    std::vector<histos> iScME = hisScME.at(isc);  

    for(unsigned int h = 0; h < iScME.size(); h++){

      histos ScME = iScME.at(h);
      
      if (isc == 0){
	histos InitScME;	
	for(unsigned int ch=0; ch<channel.size(); ch++){  
	  TString hname = (TString)ScME.hist[ch]->GetName();
	  hname.Resize(hname.Index("ScME_R"));
	  InitScME.Up[ch]   = (TH1D*)ScME.hist[ch]->Clone(hname + "ScMEUp");
	  InitScME.Dw[ch]   = (TH1D*)ScME.hist[ch]->Clone(hname + "ScMEDown");	  
	  InitScME.hist[ch] = (TH1D*)hisNom.at(h).hist[ch]->Clone();
	}
	TotScME.push_back(InitScME);
      }

      for(unsigned int ch=0; ch<channel.size(); ch++){  
	for (int ib=1; ib<=ScME.hist[ch]->GetNbinsX(); ib++){
	  
	  double viUp  = TotScME.at(h).Up[ch]->GetBinContent(ib);
	  double viDw  = TotScME.at(h).Dw[ch]->GetBinContent(ib);	  
	  double viNew = ScME.hist[ch]->GetBinContent(ib);
	  
	  if (viNew > viUp) viUp = viNew; 
	  if (viNew < viDw) viDw = viNew; 

	  TotScME.at(h).Up[ch]->SetBinContent(ib,viUp);
	  TotScME.at(h).Dw[ch]->SetBinContent(ib,viDw);

	}// for(ib)
      }// for(ch)
    }// for(histo)    
  }// for(scale variation)

  return TotScME;

}

// Add histograms to the stack
std::vector<histos> addstack(std::vector<histos> stack_0, std::vector<histos> histos_0){

  for(unsigned int h = 0; h < histos_0.size(); h++){
    for(unsigned int ch=0; ch<channel.size(); ch++){
      stack_0[h].mc[ch]->Add(histos_0[h].hist[ch]); // add histo to stack
      stack_0[h].hist[ch] = (TH1D*) stack_0[h].mc[ch]->GetStack()->Last()->Clone(); // create histo with the final stack
    }
  }
  
  return stack_0;
}

// Setup histograms
void setuphistograms(std::vector<histos> histos, int color, int style=1001, int lcolor=1, bool smooth = false, int rebin = 1, TString histovar="central"){

  for(unsigned int h = 0; h < histos.size(); h++){
    for(unsigned int ch=0; ch<channel.size(); ch++){  

      TH1D *htbm;
      if     (histovar == "central") htbm = histos[h].hist[ch];
      else if(histovar == "Up")      htbm = histos[h].Up[ch];
      else if(histovar == "Down")    htbm = histos[h].Dw[ch];
      else break;
      
      htbm->SetLineColor(lcolor); 
      htbm->SetFillColor(color);
      htbm->SetFillStyle(style);

      if(smooth) htbm->Smooth ();
      
      if(((TString)htbm->GetName()).Contains("PrimVertex")) {
	htbm->Rebin(rebin);
	htbm->Rebin(2);
	htbm->GetXaxis()->SetRangeUser(0,60); 
      }

      if(((TString)htbm->GetName()).Contains("BDTSel")) {
	htbm->Rebin(rebin);
	htbm->Rebin(2);
	htbm->GetXaxis()->SetRangeUser(-0.4,0.7); 
      }

      if(((TString)htbm->GetName()).Contains("_MET_") && !((TString)htbm->GetName()).Contains("phi")) {
	htbm->Rebin(rebin);
	htbm->Rebin(2);
      }

      if(((TString)htbm->GetName()).Contains("Jet_pT")) {
	htbm->Rebin(rebin);
	htbm->GetXaxis()->SetRangeUser(30,200);
      }

      if(((TString)htbm->GetName()).Contains("_phi")) {
	htbm->Rebin(3);
      }

      if(((TString)htbm->GetName()).Contains("Lep_pT")) {
	htbm->Rebin(rebin);	
	htbm->GetXaxis()->SetRangeUser(30,150);
      }
      
      if(((TString)htbm->GetName()).Contains("LepJet_DPhi")) {
	htbm->Rebin(rebin);
	//htbm->Rebin(2);
      }
      if(((TString)htbm->GetName()).Contains("LepJet_DR")) {
	htbm->Rebin(2);
	htbm->GetXaxis()->SetRangeUser(0,3.5);
      }
      if(((TString)htbm->GetName()).Contains("LepJet_DEta")) {
	//htbm->Rebin(2);
	htbm->GetXaxis()->SetRangeUser(-2.4,2.4);
      }      
      if(((TString)htbm->GetName()).Contains("LepJet_Mass")) {
	htbm->Rebin(rebin);
	//htbm->GetXaxis()->SetRangeUser(0,200);
      }

      /* if(((TString)htbm->GetName()).Contains("bJets")) { */
      /* 	if(((TString)htbm->GetName()).Contains("Reg0")) */
      /* 	  htbm->GetXaxis()->SetRangeUser(1,4); */
      /* 	if(((TString)htbm->GetName()).Contains("Reg1")) */
      /* 	  htbm->GetXaxis()->SetRangeUser(1,4); */
      /* 	if(((TString)htbm->GetName()).Contains("Reg2")) */
      /* 	  htbm->GetXaxis()->SetRangeUser(4,8); */
      /* 	if(((TString)htbm->GetName()).Contains("RegAll")) */
      /* 	  htbm->GetXaxis()->SetRangeUser(0,5); */
      /* } */

      /* if(((TString)htbm->GetName()).Contains("NJets")) { */
      /* 	if(((TString)htbm->GetName()).Contains("Reg0")) */
      /* 	  htbm->GetXaxis()->SetRangeUser(1,4); */
      /* 	if(((TString)htbm->GetName()).Contains("Reg1")) */
      /* 	  htbm->GetXaxis()->SetRangeUser(1,4); */
      /* 	if(((TString)htbm->GetName()).Contains("Reg2")) */
      /* 	  htbm->GetXaxis()->SetRangeUser(4,8); */
      /* 	if(((TString)htbm->GetName()).Contains("RegAll")) */
      /* 	  htbm->GetXaxis()->SetRangeUser(1,8); */
      /* } */

      // Overflows in the last bin
      /* htbm->SetBinContent(htbm->GetNbinsX(), */
      /* 					(htbm->GetBinContent(htbm->GetNbinsX()+1) +  */
      /* 					 htbm->GetBinContent(htbm->GetNbinsX()) */
      /* 					 ) */
      /* 					); */
      /* htbm->GetXaxis()->SetCanExtend(kFALSE); */
      /* htbm->SetBinContent(htbm->GetNbinsX()+1, 0.0); */

    }    
  }    
}

// Setup histogram for COMBINE
void setuphistogram(histos histos, int color, int style=1001, int lcolor=1, bool smooth = false, int rebin = 1, TString histovar="central"){

  for(unsigned int ch=0; ch<channel.size(); ch++){  

    TH1D *htbm;
    if     (histovar == "central") htbm = histos.hist[ch];
    else if(histovar == "Up")      htbm = histos.Up[ch];
    else if(histovar == "Down")    htbm = histos.Dw[ch];
    else break;
      
    htbm->SetLineColor(lcolor); 
    htbm->SetFillColor(color);
    htbm->SetFillStyle(style);

    if(smooth) htbm->Smooth ();
    
    htbm->Rebin(rebin);
    
    // Overflows in the last bin
    /* htbm->SetBinContent(htbm->GetNbinsX(), */
    /* 			(htbm->GetBinContent(htbm->GetNbinsX()+1) +  */
    /* 			 htbm->GetBinContent(htbm->GetNbinsX()) */
    /* 			 ) */
    /* 			); */
    /* htbm->GetXaxis()->SetCanExtend(kFALSE); */
    /* htbm->SetBinContent(htbm->GetNbinsX()+1, 0.0); */

  }    
}


// Scale histograms
std::vector<histos> ScaleHistos(std::vector<histos> histos_0, float Val){

  std::vector<histos> out;

  for(unsigned int h = 0; h < histos_0.size(); h++){

    histos histo;

    for(unsigned int ch=0; ch<channel.size(); ch++){
      
    histo.hist[ch] = (TH1D*)histos_0[h].hist[ch]->Clone();
    if(Val != 0.0) histo.hist[ch]-> Scale(Val);

    }
    
    out.push_back(histo);

  }

  return out;
}

// Normalize histograms
std::vector<histos> NormHistos(std::vector<histos> histos_0){

  std::vector<histos> out;

  for(unsigned int h = 0; h < histos_0.size(); h++){
    histos histo;

    for(unsigned int ch=0; ch<channel.size(); ch++){
      
      histo.hist[ch] = (TH1D*)histos_0[h].hist[ch]->Clone();
      float Norm = histo.hist[ch]->Integral();
      if (Norm != 0.0) Norm = 1.0/Norm;
      else Norm = 0.0;
      histo.hist[ch]->Scale(Norm);

    }
    
    out.push_back(histo);

  }

  return out;
}

// Function created for load2Dhistogramsregions and loadhistogramsregions
void SetNames(histos histo,TString NewRegName, TString OldRegName){
  for(unsigned int ch=0; ch<channel.size(); ch++){    

    if(histo.hist[ch]){
      TString NewName = (TString)histo.hist[ch]->GetName();
      NewName.ReplaceAll(OldRegName,NewRegName);
      histo.hist[ch]->SetName(NewName);
    }

    if(histo.hist2D[ch]){
      TString NewName = (TString)histo.hist2D[ch]->GetName();
      NewName.ReplaceAll(OldRegName,NewRegName);
      histo.hist2D[ch]->SetName(NewName);
    }
    
  }
}

// 2D => Modification to read various regions at once using the available functions
std::vector<histos> load2Dhistogramsregions(TString region, TString namefile){
  std::vector<histos> sample;
  
  TString IsoReg = "";
  if(region.Contains("ISO")){
    IsoReg = region.Contains("AntiISO")?"AntiISO":"ISO";
  }

  bool fh = true;  
  TString tokregion;
  Ssiz_t from = 0;
  while (region.Tokenize(tokregion,from,"plus")) {
    
    if(!fh) tokregion = IsoReg+tokregion;
    std::vector<histos> Reg = load2Dhistograms(tokregion,namefile);
    
    if (fh) { sample = Reg; fh = false;
      // Set Correct name
      for(unsigned int h = 0; h < sample.size(); h++)
	SetNames(sample.at(h),region,tokregion);
    }
    else    { sample = addhistograms(sample, Reg); }      
  }
  
  return sample;
  
}

// 1D => Modification to read various regions at once using the available functions
std::vector<histos> loadhistogramsregions(TString region, TString namefile, bool Combine = false, TString namesys="central", bool IsQCDDD=false){
  std::vector<histos> sample;

  TString IsoReg = "";
  if(region.Contains("ISO")){
    IsoReg = region.Contains("AntiISO")?"AntiISO":"ISO";
  }
  
  bool fh = true;  
  TString tokregion;
  Ssiz_t from = 0;
  while (region.Tokenize(tokregion,from,"plus")) {

    if(!fh) tokregion = IsoReg+tokregion;
    std::vector<histos> Reg = loadhistograms(tokregion,namefile,Combine,namesys,IsQCDDD);
    
    if (fh) { sample = Reg; fh = false;
      // Set Correct name
      for(unsigned int h = 0; h < sample.size(); h++)
	SetNames(sample.at(h),region,tokregion);
    }
    else    { sample = addhistograms(sample, Reg); }      
  }
  
  return sample;
  
}


// -----------------------------------------------------------------------------------------------------------

TString BinSizeCreator(THStack *InSt, std::vector<TString> InNa, float BinLimit){
  
  int Nh     = InSt -> GetNhists();
  TH1D *Base = (TH1D*)InSt -> GetHistogram(); 
  int MaxBin = Base-> GetNbinsX()+1;

  std::vector<float> BinWidthRange;
  BinWidthRange.push_back(Base->GetBinLowEdge(1));
    
  bool FixingTail = false;
  int NewBin = 0;
  for(int ibo=1; ibo <= Base->GetNbinsX(); ibo++){
    
    if(ibo <= NewBin) continue;

    std::vector<int> nBinSample;
    for(unsigned int in=0; in<Nh; in++){	
      TH1D *ih = (TH1D*) (InSt->GetHists()->At(in))->Clone();    
      float Den = ih->Integral();
      if(Den == 0.0) {
	std::cerr<< "Empty histogram cannot be re-binned!" << endl;
	std::exit(0);
      }
      // These lines are included in order to reduce the limit for F0 and FL to other value (e.g. 0.01)
      float BinLimitSample = BinLimit;
      if (InNa.at(in).Contains("F0") || InNa.at(in).Contains("FL")) BinLimitSample = BinLimit;
	
      float TbC = 0.;
      for(int ibf=ibo; ibf <= Base->GetNbinsX(); ibf++){
		
	TbC += ih->GetBinContent(ibf)/Den;
	// std::cout << "ib = (" << ibo << "," << ibf << ") = " << TbC << endl;
    
	if (TbC >= BinLimitSample){	
	  nBinSample.push_back(ibf);
	  break;	  
	}
	else if(ibf == Base->GetNbinsX()){
	  nBinSample.push_back(ibf);
	  FixingTail = true;
	} 	
      }// for(ibf)
    }//for(ihisto)

    for(int ihb=0;ihb<nBinSample.size();ihb++){
      if(nBinSample.at(ihb) > NewBin) NewBin = nBinSample.at(ihb);
    }

    if (FixingTail) BinWidthRange.at(BinWidthRange.size()-1) = Base->GetBinLowEdge(NewBin+1); 
    else BinWidthRange.push_back(Base->GetBinLowEdge(NewBin+1));

  }//for(ibo)

  TString Output = "";
  for(int ihb=0;ihb<BinWidthRange.size();ihb++)
    Output += Form("%.1f,", BinWidthRange.at(ihb));

  Output.Remove(Output.Length()-1);
  Output += "};";
  
  return Output;
  
}

// -----------------------------------------------------------------------------------------------------------

TH2D *GetFractionsForSgnBkg(THStack *InSt, std::vector<TString> InNa){
  
  int Nh     = InSt -> GetNhists();
  TH1D *Base = (TH1D*)InSt -> GetHistogram(); 
  int MaxBin = Base-> GetNbinsX()+1;

  // Get binning
  Double_t binX[MaxBin];
  for(int ibx=0;ibx<MaxBin;ibx++){
    binX[ibx] = Base->GetBinLowEdge(ibx+1);
  }
  
  TH2D *h2DFractions = new TH2D("","",
				Base->GetNbinsX(),
				binX,
				Nh+1,0,Nh+1);
  
  gStyle->SetPaintTextFormat("1.0f");
  h2DFractions->SetMarkerSize(1.); 
  h2DFractions->SetOption("COL"); 

  TH1D *hTotal;
  hTotal = (TH1D*)InSt->GetStack()->Last()->Clone();
  
  for(unsigned int in=0; in<InNa.size();in++)
    h2DFractions->GetYaxis()->SetBinLabel(in+1, InNa.at(in));
  
  h2DFractions->GetYaxis()->SetBinLabel(Nh+1, "Total");
    
  float yTotal = hTotal->Integral(0,MaxBin);
  
  for(unsigned int in=0; in<InNa.size();in++){
    
    TH1D *ih = (TH1D*) (InSt->GetHists()->At(in))->Clone();
    
    for(int ib=1; ib <= Base->GetNbinsX(); ib++){
      float Den = ih->Integral();
      float bc =0.;
      if(Den != 0.0) bc = 100.*ih->GetBinContent(ib)/Den;
      h2DFractions->SetBinContent(ib,in+1,bc); 
    }
  }

  for(int ib=1; ib <= Base->GetNbinsX(); ib++){
      float Den = hTotal->Integral();
      float bc =0.;
      if(Den != 0.0) bc = 100.*hTotal->GetBinContent(ib)/Den;
    h2DFractions->SetBinContent(ib,Nh+1,bc); 
  }

  return h2DFractions;

}


