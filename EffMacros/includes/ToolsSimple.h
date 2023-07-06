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
    
  std::vector<TString> histoname;
  std::vector<TString> histounits;
  
  // Histograms
  /* histoname.push_back("h2D_LepISOVsMET"); */
  /* histounits.push_back("LepISO"); */
  histoname.push_back("h2D_LepISOVsBDT");
  histounits.push_back("LepISO");
  /* histoname.push_back("h2D_LepISOVsSumBDT"); */
  /* histounits.push_back("LepISO"); */
  /* histoname.push_back("h2D_LepISOVsSumQGL"); */
  /* histounits.push_back("LepISO"); */
  
  for(unsigned int h=0; h<histoname.size(); h++){
    for(unsigned int ch=0; ch<channel.size(); ch++){
      
      // Standard input
      TString FullName = "central/" + channel[ch] + "/" + region + "/" +  histoname[h] + "_" + channel[ch] + "_" + region + "_central";
      
      std::cout << "Name: " << FullName << std::endl;
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
std::vector<histos> loadhistograms(TString region, TString namefile, bool Combine = false, TString namesys="central"){

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
    histoname.push_back("h_LepJet_DPhi");
    //histoname.push_back("Norm_h_LepJet_DPhi");
    histounits.push_back("#Delta#phi(lep,jet) [rad]");
    
    histoname.push_back("Fixed_h_LepJet_DPhi");
    //histoname.push_back("Norm_Fixed_h_LepJet_DPhi");
    histounits.push_back("#Delta#phi(lep,jet) [rad]");

    /* histoname.push_back("h_Jet_pT"); */
    /* histounits.push_back("jet pT [GeV]"); */
    
    /* histoname.push_back("Fixed_h_Jet_pT"); */
    /* histounits.push_back("jet pT [GeV]"); */
  }
  else{
    histoname.push_back("LepJet_DPhi");
    histounits.push_back("#Delta#phi(lep,jet) [rad]");

    /* histoname.push_back("LepJet_DR"); */
    /* histounits.push_back("#Delta R(lep,jet)"); */

    /* histoname.push_back("LepJet_DEta"); */
    /* histounits.push_back("#Delta#eta(lep,jet)"); */

    /* histoname.push_back("LepJet_Mass"); */
    /* histounits.push_back("Mass(lep,jet) [GeV]"); */

    /* histoname.push_back("BDTSel"); */
    /* histounits.push_back("BDT Response"); */

    /* histoname.push_back("PrimVertex"); */
    /* histounits.push_back("Number of vertices"); */

    /* histoname.push_back("MET"); */
    /* histounits.push_back("MET [GeV]"); */

    /* histoname.push_back("Lep_pT"); */
    /* histounits.push_back("Lepton pT [GeV]"); */

    /* histoname.push_back("Lep_eta"); */
    /* histounits.push_back("Lepton #eta"); */

    /* histoname.push_back("Lep_phi"); */
    /* histounits.push_back("Lepton #phi"); */

    /* histoname.push_back("NJets"); */
    /* histounits.push_back("Number of jets"); */

    /* histoname.push_back("NMbJets"); */
    /* histounits.push_back("Number of b-jets (medium)"); */

    /* histoname.push_back("NLbJets"); */
    /* histounits.push_back("Number of b-jets (loose)"); */

    /* histoname.push_back("NTbJets"); */
    /* histounits.push_back("Number of b-jets (tight)"); */

    /* histoname.push_back("Jet_pT"); */
    /* histounits.push_back("Leading jet p_{T} [GeV]"); */

    /* histoname.push_back("Jet_eta"); */
    /* histounits.push_back("Leading jet #eta "); */

    /* histoname.push_back("Jet_phi"); */
    /* histounits.push_back("Leading jet #phi "); */

    /* histoname.push_back("SecJet_pT"); */
    /* histounits.push_back("Second jet p_{T} [GeV]"); */

    /* histoname.push_back("SecJet_eta"); */
    /* histounits.push_back("Second jet #eta "); */

    /* histoname.push_back("SecJet_phi"); */
    /* histounits.push_back("Second jet #phi "); */

    /* histoname.push_back("Jet_QGL"); */
    /* histounits.push_back("Leading jet QGL "); */

    /* histoname.push_back("Jet_DeepCSV"); */
    /* histounits.push_back("Leading jet DeepCSV "); */

    // ONLY FOR DD
    /* histoname.push_back("LepMET_MT"); */
    /* histounits.push_back("Transverse mass [GeV] "); */

    /* histoname.push_back("LepMET_DPhi"); */
    /* histounits.push_back(" Phi(Lep,MET) "); */

    /* histoname.push_back("MET_phi"); */
    /* histounits.push_back("MET Phi [rad]"); */
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
      inpHis->SetDirectory(0);

      std::cout << "Name: " << FullName << " Nevt = " << inpHis->Integral() << std::endl;

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


// Read files from COMBINE OUTPUT
std::vector<histos> loadcombine(TString path[2], TString namefile){
  
  TFile *file=NULL; // new TFile(namefile);
  file = TFile::Open(namefile + ".root");
  std::cout << "Loading " << namefile << ".root file..." << endl;
  
  if(!file){
    std::cerr << "ERROR: Could not open " <<  namefile  << " files!!!"  << std::endl;
    std::exit(0);
  }

  std::vector<TString> hNamefile;
  
  hNamefile.push_back("AllBackground_COMBINE"); // 0
  hNamefile.push_back("CP5_ttbarBkg_COMBINE");  // 1
  hNamefile.push_back("CP5_ttbarSgn-F0_LepJets_SYS_COMBINE"); // 2
  hNamefile.push_back("CP5_ttbarSgn-FL_LepJets_SYS_COMBINE"); // 3
  hNamefile.push_back("CP5_ttbarSgn-FR_LepJets_SYS_COMBINE"); // 4
  hNamefile.push_back("total"); // 5
  hNamefile.push_back("total_signal"); // 6
  hNamefile.push_back("total_background"); // 7
  // Data (below)                          // 8
  
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
    //cout << "Reading data " << NamHisto << endl;
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
    for(unsigned int ch=0; ch<channel.size(); ch++){  
      
      histos.hist[ch] = (TH1D*)histos_0[h].hist[ch]->Clone();
      histos.hist[ch]->Add(histos_0[h].hist[ch], histos_1[h].hist[ch]);
      
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
	htbm->GetXaxis()->SetRangeUser(-0.7,0.5); 
      }

      if(((TString)htbm->GetName()).Contains("_MET_")) {
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
      }

      if(((TString)htbm->GetName()).Contains("LepJet_Mass")) {
	htbm->Rebin(rebin);
	htbm->GetXaxis()->SetRangeUser(0,200);
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
      htbm->SetBinContent(htbm->GetNbinsX(),
      					(htbm->GetBinContent(htbm->GetNbinsX()+1) + 
      					 htbm->GetBinContent(htbm->GetNbinsX())
      					 )
      					);
      htbm->GetXaxis()->SetCanExtend(kFALSE);
      htbm->SetBinContent(htbm->GetNbinsX()+1, 0.0);

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
    htbm->SetBinContent(htbm->GetNbinsX(),
			(htbm->GetBinContent(htbm->GetNbinsX()+1) + 
			 htbm->GetBinContent(htbm->GetNbinsX())
			 )
			);
    htbm->GetXaxis()->SetCanExtend(kFALSE);
    htbm->SetBinContent(htbm->GetNbinsX()+1, 0.0);

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
