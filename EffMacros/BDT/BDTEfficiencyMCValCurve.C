
TString callTH1 (TString ch, TString cut){
  return "central/" + ch + "/" + cut + "/c_Jet_BDT_" + ch + "_" + cut + "_central";
}


void CreateBDTEfficiencyCurve(TString Cut      = "Reg2",
			      TString Channel  = "all",
			      TString MCTr = ""){
  

  gStyle->SetOptStat("emruo");
  gStyle->SetOptStat(kFALSE);
  
  float MarkerSize = 0.7;
  int LineStyle  = 2;

  //   MCTr = "CP5";
  // TString inputfile = "/home/brochero/CMS/ttbar/CIEMAT-Demokritos/HistoResult/BDTCP5-v0/BDTCP5-v0_BDTValidation_FNano2016-v61_BDTVal_CP5_ttbarSignal_LepJetsPowhegPythia.root";
  // TString inputfile1 = "/home/brochero/CMS/ttbar/CIEMAT-Demokritos/HistoResult/BDTM2T4-v0/BDTM2T4-v0_BDTValidation_FNano2016-v61_BDTVal_CP5_ttbarSignal_LepJetsPowhegPythia.root";
  // TString inputfile2 = "/home/brochero/CMS/ttbar/CIEMAT-Demokritos/HistoResult/BDTMCatNLO-v0/BDTMCatNLO-v0_BDTValidation_FNano2016-v61_BDTVal_CP5_ttbarSignal_LepJetsPowhegPythia.root";
  
  MCTr = "M2T4";
  TString inputfile = "/home/brochero/CMS/ttbar/CIEMAT-Demokritos/HistoResult/BDTCP5-v0/BDTCP5-v0_BDTValidation_FNano2016-v61_BDTVal_CUETP8M2T4_ttbarSignal_PowhegPythia.root";
  TString inputfile1 = "/home/brochero/CMS/ttbar/CIEMAT-Demokritos/HistoResult/BDTM2T4-v0/BDTM2T4-v0_BDTValidation_FNano2016-v61_BDTVal_CUETP8M2T4_ttbarSignal_PowhegPythia.root";
  TString inputfile2 = "/home/brochero/CMS/ttbar/CIEMAT-Demokritos/HistoResult/BDTMCatNLO-v0/BDTMCatNLO-v0_BDTValidation_FNano2016-v61_BDTVal_CUETP8M2T4_ttbarSignal_PowhegPythia.root";

  // MCTr = "MCatNLO";
  // TString inputfile = "/home/brochero/CMS/ttbar/CIEMAT-Demokritos/HistoResult/BDTCP5-v0/BDTCP5-v0_BDTValidation_FNano2016-v61_BDTVal_CUETP8M2T4_ttbarSignal_aMCatNLOPythia.root";
  // TString inputfile1 = "/home/brochero/CMS/ttbar/CIEMAT-Demokritos/HistoResult/BDTM2T4-v0/BDTM2T4-v0_BDTValidation_FNano2016-v61_BDTVal_CUETP8M2T4_ttbarSignal_aMCatNLOPythia.root";
  // TString inputfile2 = "/home/brochero/CMS/ttbar/CIEMAT-Demokritos/HistoResult/BDTMCatNLO-v0/BDTMCatNLO-v0_BDTValidation_FNano2016-v61_BDTVal_CUETP8M2T4_ttbarSignal_aMCatNLOPythia.root";

    TFile *hfile = NULL;
  hfile = TFile::Open(inputfile);
  cout << "file loaded: " << inputfile << endl;
  TFile *hfile1 = NULL;
  hfile1 = TFile::Open(inputfile1);
  cout << "file loaded: " << inputfile1 << endl;
  TFile *hfile2 = NULL;
  hfile2 = TFile::Open(inputfile2);
  cout << "file loaded: " << inputfile2 << endl;


  TH1::SetDefaultSumw2(kTRUE);  

  TH1D *h_C, *h_W, *h_I;
  cout << "Loading histograms... " << endl;
  h_C  = (TH1D*) hfile->Get(callTH1(Channel,"C"+Cut))->Clone();
  h_W  = (TH1D*) hfile->Get(callTH1(Channel,"W"+Cut))->Clone();
  h_I  = (TH1D*) hfile->Get(callTH1(Channel,"I"+Cut))->Clone();
  // First bin contains all the events
  Long64_t n_CTot = h_C->GetBinContent(1);   
  Long64_t n_WTot = h_W->GetBinContent(1);   
  Long64_t n_ITot = h_I->GetBinContent(1);   

  Long64_t n_Tot = n_CTot + n_WTot + n_ITot;

  TH1D *h_C1, *h_W1, *h_I1;
  cout << "Loading histograms... " << endl;
  h_C1  = (TH1D*) hfile1->Get(callTH1(Channel,"C"+Cut))->Clone();
  h_W1  = (TH1D*) hfile1->Get(callTH1(Channel,"W"+Cut))->Clone();
  h_I1  = (TH1D*) hfile1->Get(callTH1(Channel,"I"+Cut))->Clone();
  // First bin contains all the events
  Long64_t n_CTot1 = h_C1->GetBinContent(1);   
  Long64_t n_WTot1 = h_W1->GetBinContent(1);   
  Long64_t n_ITot1 = h_I1->GetBinContent(1);   

  Long64_t n_Tot1 = n_CTot1 + n_WTot1 + n_ITot1;

  TH1D *h_C2, *h_W2, *h_I2;
  cout << "Loading histograms... " << endl;
  h_C2  = (TH1D*) hfile2->Get(callTH1(Channel,"C"+Cut))->Clone();
  h_W2  = (TH1D*) hfile2->Get(callTH1(Channel,"W"+Cut))->Clone();
  h_I2  = (TH1D*) hfile2->Get(callTH1(Channel,"I"+Cut))->Clone();
  // First bin contains all the events
  Long64_t n_CTot2 = h_C2->GetBinContent(1);   
  Long64_t n_WTot2 = h_W2->GetBinContent(1);   
  Long64_t n_ITot2 = h_I2->GetBinContent(1);   

  Long64_t n_Tot2 = n_CTot2 + n_WTot2 + n_ITot2;


  
  TEfficiency *e_C = new TEfficiency("Eff_" + ((TString)h_C->GetName()),
				     "Efficiency; BDT Cut; Efficiency",
				     h_C->GetNbinsX(),
				     h_C->GetXaxis()->GetBinLowEdge(0),
				     h_C->GetXaxis()->GetBinLowEdge(h_C->GetNbinsX()+1));

  TEfficiency *e_CTot = new TEfficiency("EffTot_" + ((TString)h_C->GetName()),
					"Efficiency; BDT Cut; Efficiency",
					h_C->GetNbinsX(),
					h_C->GetXaxis()->GetBinLowEdge(0),
					h_C->GetXaxis()->GetBinLowEdge(h_C->GetNbinsX()+1));

  TEfficiency *e_C1 = new TEfficiency("Eff1_" + ((TString)h_C->GetName()),
				     "Efficiency; BDT Cut; Efficiency",
				     h_C->GetNbinsX(),
				     h_C->GetXaxis()->GetBinLowEdge(0),
				     h_C->GetXaxis()->GetBinLowEdge(h_C->GetNbinsX()+1));

  TEfficiency *e_CTot1 = new TEfficiency("EffTot_" + ((TString)h_C->GetName()),
					"Efficiency; BDT Cut; Efficiency",
					h_C->GetNbinsX(),
					h_C->GetXaxis()->GetBinLowEdge(0),
					h_C->GetXaxis()->GetBinLowEdge(h_C->GetNbinsX()+1));

  TEfficiency *e_C2 = new TEfficiency("Eff2_" + ((TString)h_C->GetName()),
				     "Efficiency; BDT Cut; Efficiency",
				     h_C->GetNbinsX(),
				     h_C->GetXaxis()->GetBinLowEdge(0),
				     h_C->GetXaxis()->GetBinLowEdge(h_C->GetNbinsX()+1));

  TEfficiency *e_CTot2 = new TEfficiency("EffTot2_" + ((TString)h_C->GetName()),
					"Efficiency; BDT Cut; Efficiency",
					h_C->GetNbinsX(),
					h_C->GetXaxis()->GetBinLowEdge(0),
					h_C->GetXaxis()->GetBinLowEdge(h_C->GetNbinsX()+1));

  TEfficiency *p_C = new TEfficiency("Pur_" + ((TString)h_C->GetName()),
				     "Purity; BDT Cut; Purity",
				     h_C->GetNbinsX(),
				     h_C->GetXaxis()->GetBinLowEdge(0),
				     h_C->GetXaxis()->GetBinLowEdge(h_C->GetNbinsX()+1));

  TEfficiency *p_C1 = new TEfficiency("Pur1_" + ((TString)h_C->GetName()),
				     "Purity; BDT Cut; Purity",
				     h_C->GetNbinsX(),
				     h_C->GetXaxis()->GetBinLowEdge(0),
				     h_C->GetXaxis()->GetBinLowEdge(h_C->GetNbinsX()+1));

  TEfficiency *p_C2 = new TEfficiency("Pur2_" + ((TString)h_C->GetName()),
				     "Purity; BDT Cut; Purity",
				     h_C->GetNbinsX(),
				     h_C->GetXaxis()->GetBinLowEdge(0),
				     h_C->GetXaxis()->GetBinLowEdge(h_C->GetNbinsX()+1));


  
  for(int nbin = 1; nbin<= h_C->GetNbinsX(); nbin++){

    e_C->SetTotalEvents (nbin, (n_CTot+n_WTot));
    e_C->SetPassedEvents(nbin, h_C->GetBinContent(nbin)); 
    e_CTot->SetTotalEvents (nbin, n_Tot);
    e_CTot->SetPassedEvents(nbin, h_C->GetBinContent(nbin)); 

    e_C1->SetTotalEvents (nbin, (n_CTot1+n_WTot1));
    e_C1->SetPassedEvents(nbin, h_C1->GetBinContent(nbin)); 
    e_CTot1->SetTotalEvents (nbin, n_Tot1);
    e_CTot1->SetPassedEvents(nbin, h_C1->GetBinContent(nbin)); 

    e_C2->SetTotalEvents (nbin, (n_CTot2+n_WTot2));
    e_C2->SetPassedEvents(nbin, h_C2->GetBinContent(nbin)); 
    e_CTot2->SetTotalEvents (nbin, n_Tot2);
    e_CTot2->SetPassedEvents(nbin, h_C2->GetBinContent(nbin)); 


    Long64_t n_BinTot = h_C->GetBinContent(nbin) + h_W->GetBinContent(nbin) + h_I->GetBinContent(nbin);     
    p_C->SetTotalEvents (nbin, n_BinTot);
    p_C->SetPassedEvents(nbin, h_C->GetBinContent(nbin)); 

    Long64_t n_BinTot1 = h_C1->GetBinContent(nbin) + h_W1->GetBinContent(nbin) + h_I1->GetBinContent(nbin);     
    p_C1->SetTotalEvents (nbin, n_BinTot1);
    p_C1->SetPassedEvents(nbin, h_C1->GetBinContent(nbin)); 

    Long64_t n_BinTot2 = h_C2->GetBinContent(nbin) + h_W2->GetBinContent(nbin) + h_I2->GetBinContent(nbin);     
    p_C2->SetTotalEvents (nbin, n_BinTot2);
    p_C2->SetPassedEvents(nbin, h_C2->GetBinContent(nbin)); 

  }

  TCanvas *c0;
  c0 = new TCanvas("Efficiency");
  // c0->Divide(2,1);
  c0->cd();

  TH1 *h_Style = (TH1*)h_C->Clone();  
  h_Style->SetTitle("Efficiency ROC curves for " + Cut);
  h_Style->GetXaxis()->SetTitle("BDT Cut");
  h_Style->GetYaxis()->SetTitle("Efficiency");

  h_Style->GetYaxis()->SetTitleOffset(0.6);
  h_Style->GetXaxis()->SetRangeUser(-0.2,0.5);
  h_Style->Reset();
  h_Style->Draw();

  e_C->SetLineColor(kGreen);
  e_C->SetLineStyle(1);
  e_C->Draw("SAMEL");

  e_CTot->SetLineColor(kGreen+2);
  e_CTot->SetLineStyle(1);
  e_CTot->Draw("SAMEL");

  e_C1->SetLineColor(kOrange);
  e_C1->SetLineStyle(1);
  e_C1->Draw("SAMEL");

  e_CTot1->SetLineColor(kOrange+2);
  e_CTot1->SetLineStyle(1);
  e_CTot1->Draw("SAMEL");

  e_C2->SetLineColor(kRed);
  e_C2->SetLineStyle(1);
  e_C2->Draw("SAMEL");

  e_CTot2->SetLineColor(kRed+2);
  e_CTot2->SetLineStyle(1);
  e_CTot2->Draw("SAMEL");

  TLatex *titleCh = new TLatex();
  if(Channel == "all")    titleCh->SetTitle("lep+jets");
  if(Channel == "mujets") titleCh->SetTitle("#mu+jets");
  if(Channel == "ejets")  titleCh->SetTitle("e+jets");
  titleCh->SetNDC();
  titleCh->SetTextAlign(12);
  titleCh->SetX(0.14);
  titleCh->SetY(0.83);
  //titleCh->SetTextColor(2);                                                                                                                                                                                                                                
  titleCh->SetTextFont(42);
  titleCh->SetTextSize(0.05);
  titleCh->SetTextSizePixels(24);

  titleCh->Draw();

  TLegend *leg1;
  leg1 = new TLegend(0.5,0.60,0.89,0.85);
  leg1->SetLineColor(1);
  leg1->SetTextSize(0.025);

  //leg1->AddEntry((TObject*)0,"lep,jet assignment: CP5 MC","");
  //leg1->AddEntry((TObject*)0,"lep,jet assignment: CUETP8M2T4 MC","");
  leg1->AddEntry((TObject*)0,"lep,jet assignment: aMC@NLO MC","");
  leg1->AddEntry(e_CTot, "Tr. CP5",           "PLE");
  leg1->AddEntry(e_C,    "Tr. CP5 (possible)","PLE");

  leg1->AddEntry(e_CTot1, "Tr. CUETP8M2T4",           "PLE");
  leg1->AddEntry(e_C1,    "Tr. CUETP8M2T4 (possible)","PLE");
  
  leg1->AddEntry(e_CTot2, "Tr. aMC@NLO",           "PLE");
  leg1->AddEntry(e_C2,    "Tr. aMC@NLO (possible)","PLE");

  leg1->Draw();

  // ---------------------------------------------------



  c0->SaveAs("../Figures/BDTPlots/EffiMC/EffPurMCVal_" + MCTr + "_" + Channel + "_" + Cut +".pdf");
}// Function




void BDTEfficiencyMCValCurve(){

  CreateBDTEfficiencyCurve("Reg0","all");
  CreateBDTEfficiencyCurve("Reg1","all");
  CreateBDTEfficiencyCurve("Reg2","all");

  CreateBDTEfficiencyCurve("Reg0","mujets");
  CreateBDTEfficiencyCurve("Reg1","mujets");
  CreateBDTEfficiencyCurve("Reg2","mujets");

  CreateBDTEfficiencyCurve("Reg0","ejets");
  CreateBDTEfficiencyCurve("Reg1","ejets");
  CreateBDTEfficiencyCurve("Reg2","ejets");
}
