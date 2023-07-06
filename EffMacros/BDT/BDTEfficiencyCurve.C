
TString callTH1 (TString ch, TString cut){
  return "central/" + ch + "/" + cut + "/c_Jet_BDT_" + ch + "_" + cut + "_central";
}


void CreateBDTEfficiencyCurve(TString Cut      = "4j2b",
			      TString Channel  = "all"){
  

  gStyle->SetOptStat("emruo");
  gStyle->SetOptStat(kFALSE);
  
  float MarkerSize = 0.7;
  int LineStyle  = 2;
  
  // TString Ref = "TrFullStataMCatNLORegFrom2_WithDR-v6";
  // TString inputfile = "../HistoResult/"+Ref+"/"+Ref+"_BDTValidation_SmallFNano2017-v7_TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8.root";

  TString Ref = "ValGenJetNovNoBDTCut-v0";
  TString inputfile = "../HistoResult/"+Ref+"/"+Ref+"_BDTValidation_GenJetsFNano2017-v7_TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8.root";
  
  TFile *hfile = NULL;
  hfile = TFile::Open(inputfile);
  cout << "file loaded: " << inputfile << endl;
  

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

  
  TEfficiency *e_C = new TEfficiency("Eff_" + ((TString)h_C->GetName()),
				     "Efficiency; BDT Cut; Efficiency",
				     h_C->GetNbinsX(),
				     h_C->GetXaxis()->GetBinLowEdge(0),
				     h_C->GetXaxis()->GetBinLowEdge(h_C->GetNbinsX()+1));

  TEfficiency *e_W = new TEfficiency("Eff_" + ((TString)h_W->GetName()),
				     "Efficiency; BDT Cut; Efficiency",
				     h_W->GetNbinsX(),
				     h_W->GetXaxis()->GetBinLowEdge(0),
				     h_W->GetXaxis()->GetBinLowEdge(h_W->GetNbinsX()+1));

  TEfficiency *e_CTot = new TEfficiency("EffTot_" + ((TString)h_C->GetName()),
					"Efficiency; BDT Cut; Efficiency",
					h_C->GetNbinsX(),
					h_C->GetXaxis()->GetBinLowEdge(0),
					h_C->GetXaxis()->GetBinLowEdge(h_C->GetNbinsX()+1));
  
  TEfficiency *e_WTot = new TEfficiency("EffTot_" + ((TString)h_W->GetName()),
					"Efficiency; BDT Cut; Efficiency",
					h_W->GetNbinsX(),
					h_W->GetXaxis()->GetBinLowEdge(0),
					h_W->GetXaxis()->GetBinLowEdge(h_W->GetNbinsX()+1));
  

  TEfficiency *p_C = new TEfficiency("Pur_" + ((TString)h_C->GetName()),
				     "Purity; BDT Cut; Purity",
				     h_C->GetNbinsX(),
				     h_C->GetXaxis()->GetBinLowEdge(0),
				     h_C->GetXaxis()->GetBinLowEdge(h_C->GetNbinsX()+1));

  TEfficiency *p_W = new TEfficiency("Pur_" + ((TString)h_W->GetName()),
				     "Purity; BDT Cut; Purity",
				     h_W->GetNbinsX(),
				     h_W->GetXaxis()->GetBinLowEdge(0),
				     h_W->GetXaxis()->GetBinLowEdge(h_W->GetNbinsX()+1));

  
  for(int nbin = 1; nbin<= h_C->GetNbinsX(); nbin++){

    e_C->SetTotalEvents (nbin, (n_CTot+n_WTot));
    e_C->SetPassedEvents(nbin, h_C->GetBinContent(nbin)); 

    e_W->SetTotalEvents (nbin, (n_CTot+n_WTot));
    e_W->SetPassedEvents(nbin, h_W->GetBinContent(nbin)); 
    
    e_CTot->SetTotalEvents (nbin, n_Tot);
    e_CTot->SetPassedEvents(nbin, h_C->GetBinContent(nbin)); 
    
    e_WTot->SetTotalEvents (nbin, n_Tot);
    e_WTot->SetPassedEvents(nbin, h_W->GetBinContent(nbin)); 


    Long64_t n_BinTot = h_C->GetBinContent(nbin) + h_W->GetBinContent(nbin) + h_I->GetBinContent(nbin); 
    
    p_C->SetTotalEvents (nbin, n_BinTot);
    p_C->SetPassedEvents(nbin, h_C->GetBinContent(nbin)); 

    p_W->SetTotalEvents (nbin, n_BinTot);
    p_W->SetPassedEvents(nbin, h_W->GetBinContent(nbin)); 
    

  }

  float XaxisRange_o = -0.2, XaxisRange_f = 0.5;
  
  TCanvas *c0;
  c0 = new TCanvas("Efficiency");
  c0->Divide(2,1);
  c0->cd(1);

  TH1 *h_Style = (TH1*)h_C->Clone();  
  h_Style->SetTitle("Efficiency ROC curves for " + Cut);
  h_Style->GetXaxis()->SetTitle("BDT Cut");
  h_Style->GetYaxis()->SetTitle("Efficiency");

  h_Style->GetYaxis()->SetTitleOffset(0.6);
  h_Style->GetXaxis()->SetRangeUser(XaxisRange_o,XaxisRange_f);
  h_Style->Reset();
  h_Style->Draw();

  e_C->SetLineColor(kGreen);
  e_C->SetLineStyle(1);
  e_C->Draw("SAMEL");

  e_W->SetLineColor(kRed);
  e_W->SetLineStyle(1);
  e_W->Draw("SAMEL");

  e_CTot->SetLineColor(kGreen+2);
  e_CTot->SetLineStyle(1);
  e_CTot->Draw("SAMEL");

  e_WTot->SetLineColor(kRed+2);
  e_WTot->SetLineStyle(1);
  e_WTot->Draw("SAMEL");

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
  leg1->SetTextSize(0.032);

  leg1->AddEntry((TObject*)0,"lep,jet assignment","");
  leg1->AddEntry((TObject*)0,Cut,"");
  leg1->AddEntry(e_CTot, "Correct (total)",   "PLE");
  leg1->AddEntry(e_WTot, "Wrong (total)",     "PLE");
  leg1->AddEntry(e_C,    "Correct (possible)","PLE");
  leg1->AddEntry(e_W,    "Wrong (possible)",  "PLE");

  leg1->Draw();

  
  
  // ---------------------------------------------------

  TPad *GPad = new TPad("GPad", "",0,0,1,1);
  GPad = (TPad*)c0->GetPad(2);
    
  GPad->Divide(2,1);

  TPad *G1Pad = new TPad("G1Pad", "",0,0,1,1);
  G1Pad = (TPad*)GPad->GetPad(1);
  G1Pad->SetPad(0.0, 0.0, 1., 1.);

  G1Pad->cd();
  h_Style->Draw();

  TEfficiency *e1_C = (TEfficiency*)e_C->Clone();
  e1_C->SetLineColor(kBlack);
  e1_C->SetLineStyle(1);
  e1_C->Draw("SAMEL");

  p_C->SetLineColor(kBlue);
  p_C->SetLineStyle(1);
  p_C->Draw("SAMEL");

  titleCh->Draw();

  // Draw the axis of the 2nd TMultiGraph
  c0->Update();
  auto newyaxis = new TGaxis(gPad->GetUxmax(),gPad->GetUymin(),
			     gPad->GetUxmax(),gPad->GetUymax(),
			     0,1.05,510,"+L");
  newyaxis->SetLabelColor(kBlue);
  newyaxis->SetLineColor (kBlue);
  newyaxis->SetTitleColor(kBlue);
  newyaxis->SetTitle("Purity");
  newyaxis->Draw();

  TPad *TinyPad = new TPad("TinyPad", "TinyPad",0,0,1,1);
  TinyPad = (TPad*)GPad->GetPad(2);
  TinyPad->SetPad(0.2, 0.12, 0.8, 0.5);

  TinyPad->SetTopMargin(0.1);
  TinyPad->SetBottomMargin(0.2);
  TinyPad->SetRightMargin(0.18);
  TinyPad->SetLeftMargin(0.18);
  TinyPad->SetFillStyle(4000);
  TinyPad->Draw();

  TinyPad->cd();

  // Check intersection
  float xo=0.06,xf=0.10,yo=0.6,yf=0.8;
  float tDiff = 1.;    
  int bDiff;    

  for (int ib=1;ib<h_C->GetNbinsX();ib++){
    
    float effVal = e1_C->GetEfficiency (ib);
    float purVal = p_C->GetEfficiency (ib);
    float Diff = effVal - purVal;    
    if(Diff > 0.0 && Diff < tDiff){tDiff = Diff; bDiff = ib;}
  }
  // Get Ranges
  xo = (p_C->GetCopyTotalHisto())->GetBinCenter(bDiff)-0.02;
  xf = (p_C->GetCopyTotalHisto())->GetBinCenter(bDiff)+0.02;
  yo = e1_C->GetEfficiency (bDiff) - 0.1;
  yf = e1_C->GetEfficiency (bDiff) + 0.1;
      

  TH1D *h_TinyStyle = (TH1D*)h_Style->Clone();

  h_TinyStyle->SetTitle("");
  h_TinyStyle->GetYaxis()->SetTitleOffset(0.6);
  h_TinyStyle->GetXaxis()->SetRangeUser(xo,xf); 
  h_TinyStyle->GetYaxis()->SetRangeUser(yo,yf); 

  h_TinyStyle->GetYaxis()->SetTitle("");
  h_TinyStyle->GetXaxis()->SetTitle(""); 

  // h_TinyStyle->GetYaxis()->SetTitleSize(0.06);
  // h_TinyStyle->GetXaxis()->SetTitleSize(0.06); 
  h_TinyStyle->GetYaxis()->SetLabelSize(0.06);
  h_TinyStyle->GetYaxis()->SetNdivisions(604);
  h_TinyStyle->GetXaxis()->SetLabelSize(0.06); 
  h_TinyStyle->GetXaxis()->SetNdivisions(604);

  h_TinyStyle->Draw();
  e1_C->Draw("SAMEL");
  p_C->Draw("SAMEL");

  c0->Update();
  TGaxis *newTinyyaxis = new TGaxis(gPad->GetUxmax(),gPad->GetUymin(),
				    gPad->GetUxmax(),gPad->GetUymax(),
				    yo,yf,604,"+L");     
  newTinyyaxis->SetLabelColor(kBlue);
  newTinyyaxis->SetLineColor(kBlue);
  newTinyyaxis->SetTitleColor(kBlue);
  newTinyyaxis->SetLabelSize(0.06); 
  newTinyyaxis->Draw();

  TString BDTDir = "../Figures/BDTPlots-" + Ref + "/EffiPur/";
  gSystem->mkdir(BDTDir,kTRUE);
  c0->SaveAs(BDTDir + "EffPur_" + Channel + "_" + Cut +".png");
}// Function




void BDTEfficiencyCurve(){

  CreateBDTEfficiencyCurve("2j2b",  "all");
  CreateBDTEfficiencyCurve("3j2b",  "all");
  CreateBDTEfficiencyCurve("3j3b",  "all");
  CreateBDTEfficiencyCurve("4j2b",  "all");
  CreateBDTEfficiencyCurve("4jge3b","all");
  CreateBDTEfficiencyCurve("ge5",   "all");

}
