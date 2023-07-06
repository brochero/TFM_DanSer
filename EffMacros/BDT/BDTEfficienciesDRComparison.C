
TString callTH1 (TString ch, TString cut, TString histo){
  return "central/" + ch + "/" + cut + "/" + histo + "_" + ch + "_" + cut + "_central";
}


void CreateBDTEfficiencyCurve(TString Cut,
			      TString Channel,
			      TString Histo){

  unsigned int NewBin = 2;

  gStyle->SetOptStat("emruo");
  gStyle->SetOptStat(kFALSE);
  TH1::SetDefaultSumw2(kTRUE);  
  
  float MarkerSize = 0.7;
  int LineStyle  = 2;
  
  TString Ref      = "BDTTrainingJulyNoBDTCut-v0";
  TString RefCut   = "BDTTrainingJulyBDTCut005-v0";
  TString RefDR    = "BDTTrainingJulyNoBDTCut-v0";
  TString RefDRCut = "BDTTrainingJulyBDTCut005-v0";
  
  TString inputfile     = "../HistoResult/" + Ref + "/" + Ref + "_BDTValidation_FNano2016-v61_TTToSemiLeptonic_TuneCP5_PSweights_13TeV-powheg-pythia8.root";
  TString inputfileCut  = "../HistoResult/" + RefCut + "/" + RefCut + "_BDTValidation_FNano2016-v61_TTToSemiLeptonic_TuneCP5_PSweights_13TeV-powheg-pythia8.root";
  TString inputfileDR = "../HistoResult/" + RefCut + "/" + RefCut + "_BDTValidation_DRFNano2016-v61_TTToSemiLeptonic_TuneCP5_PSweights_13TeV-powheg-pythia8.root";
  TString inputfileDRCut = "../HistoResult/" + RefCut + "/" + RefCut + "_BDTValidation_DRFNano2016-v61_TTToSemiLeptonic_TuneCP5_PSweights_13TeV-powheg-pythia8.root";

  TFile *hfile     = TFile::Open(inputfile);
  TFile *hfileCut  = TFile::Open(inputfileCut);
  TFile *hfileDR = TFile::Open(inputfileDR);
  TFile *hfileDRCut = TFile::Open(inputfileDRCut);

  TH1D *h_C, *h_W, *h_I;
  h_C  = (TH1D*) hfile->Get(callTH1(Channel,"C"+Cut,Histo))->Clone();
  h_W  = (TH1D*) hfile->Get(callTH1(Channel,"W"+Cut,Histo))->Clone();
  h_I  = (TH1D*) hfile->Get(callTH1(Channel,"I"+Cut,Histo))->Clone();
  TH1D *h_P, *h_Tot;
  h_P  = (TH1D*) h_C->Clone(); 
  h_P->Add(h_W);
  h_Tot  = (TH1D*) h_P->Clone();
  h_Tot->Add(h_I);

 // CUT 0
  TH1D *hcut_C, *hcut_W, *hcut_I;
  hcut_C  = (TH1D*) hfileCut->Get(callTH1(Channel,"C"+Cut,Histo))->Clone();
  hcut_W  = (TH1D*) hfileCut->Get(callTH1(Channel,"W"+Cut,Histo))->Clone();
  hcut_I  = (TH1D*) hfileCut->Get(callTH1(Channel,"I"+Cut,Histo))->Clone();
  TH1D *hcut_P, *hcut_Tot;
  hcut_P  = (TH1D*) hcut_C->Clone(); 
  hcut_P->Add(hcut_W);
  hcut_Tot  = (TH1D*) hcut_P->Clone();
  hcut_Tot->Add(hcut_I);
  // CUT 1
  TH1D *hDR_C, *hDR_W, *hDR_I;
  hDR_C  = (TH1D*) hfileDR->Get(callTH1(Channel,"C"+Cut,Histo))->Clone();
  hDR_W  = (TH1D*) hfileDR->Get(callTH1(Channel,"W"+Cut,Histo))->Clone();
  hDR_I  = (TH1D*) hfileDR->Get(callTH1(Channel,"I"+Cut,Histo))->Clone();
  TH1D *hDR_P, *hDR_Tot;
  hDR_P  = (TH1D*) hDR_C->Clone(); 
  hDR_P->Add(hDR_W);
  hDR_Tot  = (TH1D*) hDR_P->Clone();
  hDR_Tot->Add(hDR_I);
  // CUT 2
  TH1D *hDRcut_C, *hDRcut_W, *hDRcut_I;
  hDRcut_C  = (TH1D*) hfileDRCut->Get(callTH1(Channel,"C"+Cut,Histo))->Clone();
  hDRcut_W  = (TH1D*) hfileDRCut->Get(callTH1(Channel,"W"+Cut,Histo))->Clone();
  hDRcut_I  = (TH1D*) hfileDRCut->Get(callTH1(Channel,"I"+Cut,Histo))->Clone();
  TH1D *hDRcut_P, *hDRcut_Tot;
  hDRcut_P  = (TH1D*) hDRcut_C->Clone(); 
  hDRcut_P->Add(hDRcut_W);
  hDRcut_Tot  = (TH1D*) hDRcut_P->Clone();
  hDRcut_Tot->Add(hDRcut_I);

      // Number of events
  double n_CTot = h_C->Integral();   
  double n_WTot = h_W->Integral();   
  double n_ITot = h_I->Integral();   

  double n_Tot = n_CTot + n_WTot + n_ITot;
  double n_PTot = n_CTot + n_WTot;
  
  h_C      ->Rebin(NewBin);
  h_W      ->Rebin(NewBin);
  h_I      ->Rebin(NewBin);
  h_P      ->Rebin(NewBin);
  h_Tot    ->Rebin(NewBin);
  hcut_C   ->Rebin(NewBin);
  hcut_W   ->Rebin(NewBin);
  hcut_I   ->Rebin(NewBin);
  hcut_P   ->Rebin(NewBin);
  hcut_Tot ->Rebin(NewBin);
  hDR_C  ->Rebin(NewBin);
  hDR_W  ->Rebin(NewBin);
  hDR_I  ->Rebin(NewBin);
  hDR_P  ->Rebin(NewBin);
  hDR_Tot->Rebin(NewBin);
  hDRcut_C  ->Rebin(NewBin);
  hDRcut_W  ->Rebin(NewBin);
  hDRcut_I  ->Rebin(NewBin);
  hDRcut_P  ->Rebin(NewBin);
  hDRcut_Tot->Rebin(NewBin);

  TEfficiency *e_C = new TEfficiency("Eff_" + ((TString)h_C->GetName()),
				     "Efficiency; BDT Cut; Efficiency",
				     h_C->GetNbinsX(),
				     h_C->GetXaxis()->GetBinLowEdge(0),
				     h_C->GetXaxis()->GetBinLowEdge(h_C->GetNbinsX()+1));

  TEfficiency *e_W    = (TEfficiency *)e_C->Clone();
  TEfficiency *e_CTot = (TEfficiency *)e_C->Clone();
  e_C->   SetPassedHistogram(*hcut_C,"f");
  e_C->   SetTotalHistogram (*h_P,   "f");
  e_W->   SetPassedHistogram(*hcut_W,"f");
  e_W->   SetTotalHistogram (*h_P,   "f");
  e_CTot->SetPassedHistogram(*hcut_C,"f");
  e_CTot->SetTotalHistogram (*h_Tot, "f");
  float TotEff = hcut_C->Integral()/h_Tot->Integral();

  TEfficiency *eDR_CTot = (TEfficiency *)e_C->Clone();
  eDR_CTot->SetPassedHistogram(*hDRcut_C,"f");
  eDR_CTot->SetTotalHistogram (*hDR_Tot, "f");
  float TotEffDR = hDRcut_C->Integral()/hDR_Tot->Integral();

  // // --------------------
  // // GEN level
  // // --------------------
  // TH1D *hg_C, *hg_W, *hg_I;
  // hg_C  = (TH1D*) hfile->Get(callTH1(Channel,"C"+Cut,"h_lQb_DPhi"))->Clone();
  // hg_W  = (TH1D*) hfile->Get(callTH1(Channel,"W"+Cut,"h_lQb_DPhi"))->Clone();
  // hg_I  = (TH1D*) hfile->Get(callTH1(Channel,"I"+Cut,"h_lQb_DPhi"))->Clone();
  // TH1D *hg_P, *hg_Tot;
  // hg_P  = (TH1D*) hg_C->Clone(); 
  // hg_P->Add(hg_W);
  // hg_Tot  = (TH1D*) hg_P->Clone();
  // hg_Tot->Add(hg_I);
  // // CUT
  // TH1D *hgcut_C, *hgcut_W, *hgcut_I;
  // hgcut_C  = (TH1D*) hfileCut->Get(callTH1(Channel,"C"+Cut,"h_lQb_DPhi"))->Clone();
  // hgcut_W  = (TH1D*) hfileCut->Get(callTH1(Channel,"W"+Cut,"h_lQb_DPhi"))->Clone();
  // hgcut_I  = (TH1D*) hfileCut->Get(callTH1(Channel,"I"+Cut,"h_lQb_DPhi"))->Clone();
  // TH1D *hgcut_P, *hgcut_Tot;  
  // hgcut_P  = (TH1D*) hgcut_C->Clone(); 
  // hgcut_P->Add(hgcut_W);
  // hgcut_Tot  = (TH1D*) hgcut_P->Clone();
  // hgcut_Tot->Add(hgcut_I);
  // // DR
  // TH1D *hgDR_C, *hgDR_W, *hgDR_I;
  // hgDR_C  = (TH1D*) hfileDR->Get(callTH1(Channel,"C"+Cut,"h_lQb_DPhi"))->Clone();
  // hgDR_W  = (TH1D*) hfileDR->Get(callTH1(Channel,"W"+Cut,"h_lQb_DPhi"))->Clone();
  // hgDR_I  = (TH1D*) hfileDR->Get(callTH1(Channel,"I"+Cut,"h_lQb_DPhi"))->Clone();
  // TH1D *hgDR_P, *hgDR_Tot;  
  // hgDR_P  = (TH1D*) hgDR_C->Clone(); 
  // hgDR_P->Add(hgDR_W);
  // hgDR_Tot = (TH1D*) hgDR_P->Clone();
  // hgDR_Tot->Add(hgDR_I);
  // // DRCUT
  // TH1D *hgDRcut_C, *hgDRcut_W, *hgDRcut_I;
  // hgDRcut_C  = (TH1D*) hfileDRCut->Get(callTH1(Channel,"C"+Cut,"h_lQb_DPhi"))->Clone();
  // hgDRcut_W  = (TH1D*) hfileDRCut->Get(callTH1(Channel,"W"+Cut,"h_lQb_DPhi"))->Clone();
  // hgDRcut_I  = (TH1D*) hfileDRCut->Get(callTH1(Channel,"I"+Cut,"h_lQb_DPhi"))->Clone();
  // TH1D *hgDRcut_P, *hgDRcut_Tot;  
  // hgDRcut_P  = (TH1D*) hgDRcut_C->Clone(); 
  // hgDRcut_P->Add(hgDRcut_W);
  // hgDRcut_Tot = (TH1D*) hgDRcut_P->Clone();
  // hgDRcut_Tot->Add(hgDRcut_I);

  // // Purity
  // TEfficiency *p_C = new TEfficiency("PurC_" + ((TString)hg_C->GetName()),
  // 				     "Purity; BDT Cut; Purity",
  // 				     hg_C->GetNbinsX(),
  // 				     hg_C->GetXaxis()->GetBinLowEdge(0),
  // 				     hg_C->GetXaxis()->GetBinLowEdge(hg_C->GetNbinsX()+1));
  // hg_C->Rebin(NewBin);
  // hg_W->Rebin(NewBin);  
  // p_C->SetPassedHistogram(*hg_C,   "f");
  // p_C->SetTotalHistogram (*hcut_C, "f");
  
  // Diagonal purity
  TH2D *h2D_C, *h2D_W, *h2D_I;
  h2D_C  = (TH2D*) hfile->Get(callTH1(Channel,"C"+Cut,"h_LepJetVslQb_DPhi"))->Clone();
  h2D_W  = (TH2D*) hfile->Get(callTH1(Channel,"W"+Cut,"h_LepJetVslQb_DPhi"))->Clone();
  h2D_I  = (TH2D*) hfile->Get(callTH1(Channel,"I"+Cut,"h_LepJetVslQb_DPhi"))->Clone();
  TH2D *h2Dcut_C, *h2Dcut_W, *h2Dcut_I;
  h2Dcut_C  = (TH2D*) hfileCut->Get(callTH1(Channel,"C"+Cut,"h_LepJetVslQb_DPhi"))->Clone();
  h2Dcut_W  = (TH2D*) hfileCut->Get(callTH1(Channel,"W"+Cut,"h_LepJetVslQb_DPhi"))->Clone();
  h2Dcut_I  = (TH2D*) hfileCut->Get(callTH1(Channel,"I"+Cut,"h_LepJetVslQb_DPhi"))->Clone();
  TH2D *h2DDR_C, *h2DDR_W, *h2DDR_I;
  h2DDR_C  = (TH2D*) hfileDR->Get(callTH1(Channel,"C"+Cut,"h_LepJetVslQb_DPhi"))->Clone();
  h2DDR_W  = (TH2D*) hfileDR->Get(callTH1(Channel,"W"+Cut,"h_LepJetVslQb_DPhi"))->Clone();
  h2DDR_I  = (TH2D*) hfileDR->Get(callTH1(Channel,"I"+Cut,"h_LepJetVslQb_DPhi"))->Clone();
  TH2D *h2DDRcut_C, *h2DDRcut_W, *h2DDRcut_I;
  h2DDRcut_C  = (TH2D*) hfileDRCut->Get(callTH1(Channel,"C"+Cut,"h_LepJetVslQb_DPhi"))->Clone();
  h2DDRcut_W  = (TH2D*) hfileDRCut->Get(callTH1(Channel,"W"+Cut,"h_LepJetVslQb_DPhi"))->Clone();
  h2DDRcut_I  = (TH2D*) hfileDRCut->Get(callTH1(Channel,"I"+Cut,"h_LepJetVslQb_DPhi"))->Clone();
  TH2D *h2D_P, *h2D_Tot;
  h2D_P  = (TH2D*) h2D_C->Clone();
  h2D_P->Add(h2D_W);
  h2D_Tot  = (TH2D*) h2D_P->Clone();
  h2D_Tot->Add(h2D_I);
  TH2D *h2Dcut_P, *h2Dcut_Tot;
  h2Dcut_P  = (TH2D*) h2Dcut_C->Clone();
  h2Dcut_P->Add(h2Dcut_W);
  h2Dcut_Tot  = (TH2D*) h2Dcut_P->Clone();
  h2Dcut_Tot->Add(h2Dcut_I);
  TH2D *h2DDR_P, *h2DDR_Tot;
  h2DDR_P  = (TH2D*) h2DDR_C->Clone();
  h2DDR_P->Add(h2DDR_W);
  h2DDR_Tot  = (TH2D*) h2DDR_P->Clone();
  h2DDR_Tot->Add(h2DDR_I);
  TH2D *h2DDRcut_P, *h2DDRcut_Tot;
  h2DDRcut_P  = (TH2D*) h2DDRcut_C->Clone();
  h2DDRcut_P->Add(h2DDRcut_W);
  h2DDRcut_Tot  = (TH2D*) h2DDRcut_P->Clone();
  h2DDRcut_Tot->Add(h2DDRcut_I);

  
  h2D_C      ->Rebin2D(NewBin,NewBin);
  h2D_W      ->Rebin2D(NewBin,NewBin);
  h2D_I      ->Rebin2D(NewBin,NewBin);
  h2D_P      ->Rebin2D(NewBin,NewBin);
  h2D_Tot    ->Rebin2D(NewBin,NewBin);
  h2Dcut_C   ->Rebin2D(NewBin,NewBin);
  h2Dcut_W   ->Rebin2D(NewBin,NewBin);
  h2Dcut_I   ->Rebin2D(NewBin,NewBin);
  h2Dcut_P   ->Rebin2D(NewBin,NewBin);
  h2Dcut_Tot ->Rebin2D(NewBin,NewBin);
  h2DDR_C  ->Rebin2D(NewBin,NewBin);
  h2DDR_W  ->Rebin2D(NewBin,NewBin);
  h2DDR_I  ->Rebin2D(NewBin,NewBin);
  h2DDR_P  ->Rebin2D(NewBin,NewBin);
  h2DDR_Tot->Rebin2D(NewBin,NewBin);
  h2DDRcut_C  ->Rebin2D(NewBin,NewBin);
  h2DDRcut_W  ->Rebin2D(NewBin,NewBin);
  h2DDRcut_I  ->Rebin2D(NewBin,NewBin);
  h2DDRcut_P  ->Rebin2D(NewBin,NewBin);
  h2DDRcut_Tot->Rebin2D(NewBin,NewBin);

  
  TH1D *hdcut_C, *hdcut_W, *hdcut_I;
  hdcut_C  = (TH1D*) h_C->Clone(); 
  hdcut_W  = (TH1D*) h_C->Clone(); 
  hdcut_I  = (TH1D*) h_C->Clone(); 
  TH1D *hdDR_C, *hdDR_W, *hdDR_I;
  hdDR_C  = (TH1D*) h_C->Clone(); 
  hdDR_W  = (TH1D*) h_C->Clone(); 
  hdDR_I  = (TH1D*) h_C->Clone(); 
  TH1D *hdDRcut_C, *hdDRcut_W, *hdDRcut_I;
  hdDRcut_C  = (TH1D*) h_C->Clone(); 
  hdDRcut_W  = (TH1D*) h_C->Clone(); 
  hdDRcut_I  = (TH1D*) h_C->Clone(); 

  cout << hdcut_C->GetNbinsX() << endl;
  for(int ib=1; ib <= hdcut_C->GetNbinsX(); ib++){

    hdcut_C->SetBinContent( ib, h2Dcut_C->GetBinContent(ib,ib));
    hdcut_C->SetBinError  ( ib, h2Dcut_C->GetBinErrorUp(ib,ib));
    hdcut_W->SetBinContent( ib, h2Dcut_W->GetBinContent(ib,ib));
    hdcut_W->SetBinError  ( ib, h2Dcut_W->GetBinErrorUp(ib,ib));
    hdcut_I->SetBinContent( ib, h2Dcut_I->GetBinContent(ib,ib));
    hdcut_I->SetBinError  ( ib, h2Dcut_I->GetBinErrorUp(ib,ib));

    hdDR_C->SetBinContent( ib, h2DDR_C->GetBinContent(ib,ib));
    hdDR_C->SetBinError  ( ib, h2DDR_C->GetBinErrorUp(ib,ib));
    hdDR_W->SetBinContent( ib, h2DDR_W->GetBinContent(ib,ib));
    hdDR_W->SetBinError  ( ib, h2DDR_W->GetBinErrorUp(ib,ib));
    hdDR_I->SetBinContent( ib, h2DDR_I->GetBinContent(ib,ib));
    hdDR_I->SetBinError  ( ib, h2DDR_I->GetBinErrorUp(ib,ib));

    hdDRcut_C->SetBinContent( ib, h2DDRcut_C->GetBinContent(ib,ib));
    hdDRcut_C->SetBinError  ( ib, h2DDRcut_C->GetBinErrorUp(ib,ib));
    hdDRcut_W->SetBinContent( ib, h2DDRcut_W->GetBinContent(ib,ib));
    hdDRcut_W->SetBinError  ( ib, h2DDRcut_W->GetBinErrorUp(ib,ib));
    hdDRcut_I->SetBinContent( ib, h2DDRcut_I->GetBinContent(ib,ib));
    hdDRcut_I->SetBinError  ( ib, h2DDRcut_I->GetBinErrorUp(ib,ib));

  }
   
  TEfficiency *purcut_C = new TEfficiency("pur_C" + ((TString)hdcut_C->GetName()),
				       "Purity; ; Efficiency",
				       hdcut_C->GetNbinsX(),
				       hdcut_C->GetXaxis()->GetBinLowEdge(0),
				       hdcut_C->GetXaxis()->GetBinLowEdge(hdcut_C->GetNbinsX()+1));
  TEfficiency *purcut_W    = (TEfficiency *) purcut_C->Clone();
  TEfficiency *purcut_CTot = (TEfficiency *) purcut_C->Clone();
  purcut_C->   SetPassedHistogram(*hdcut_C,   "f");
  purcut_C->   SetTotalHistogram (*(hcut_C),  "f");
  purcut_W->   SetPassedHistogram(*hdcut_W,   "f");
  purcut_W->   SetTotalHistogram (*(hcut_Tot),"f");
  purcut_CTot->SetPassedHistogram(*hdcut_C,   "f");
  purcut_CTot->SetTotalHistogram (*(hcut_Tot),"f");
  float TotPurcut = hdcut_C->Integral()/hcut_Tot->Integral();

  TEfficiency *purDR_C    = (TEfficiency *) purcut_C->Clone();
  TEfficiency *purDR_CTot = (TEfficiency *) purcut_C->Clone();
  purDR_C->   SetPassedHistogram(*hdDR_C,   "f");
  purDR_C->   SetTotalHistogram (*(hDR_C),  "f");
  purDR_CTot->SetPassedHistogram(*hdDR_C,   "f");
  purDR_CTot->SetTotalHistogram (*(hDR_Tot),"f");
  float TotPurDR = hdDR_C->Integral()/hDR_Tot->Integral();

  TEfficiency *purDRcut_C    = (TEfficiency *) purcut_C->Clone();
  TEfficiency *purDRcut_CTot = (TEfficiency *) purcut_C->Clone();
  purDRcut_C->   SetPassedHistogram(*hdDRcut_C,   "f");
  purDRcut_C->   SetTotalHistogram (*(hDRcut_C),  "f");
  purDRcut_CTot->SetPassedHistogram(*hdDRcut_C,   "f");
  purDRcut_CTot->SetTotalHistogram (*(hDRcut_Tot),"f");
  float TotPurDRcut = hdDRcut_C->Integral()/hDRcut_Tot->Integral();

  
  // ------------------------
  // Drawing
  // ------------------------
  TCanvas *c0;
  c0 = new TCanvas("Efficiency");
  c0->Divide(2,1);
  c0->cd(1);
  c0->cd(1)->SetGrid();
  
  TH1 *h_Style = (TH1*)h_C->Clone();  
  h_Style->SetTitle("Efficiency in the " + (TString)h_C->GetTitle() + " for " + Cut);
  h_Style->GetXaxis()->SetTitle((TString)h_C->GetXaxis()->GetTitle());
  h_Style->GetYaxis()->SetTitle("Efficiency");

  h_Style->GetYaxis()->SetTitleOffset(1.1);
  //h_Style->GetXaxis()->SetRangeUser(-0.2,0.5);
  h_Style->GetYaxis()->SetRangeUser(0.,1.2);
  h_Style->Reset();
  h_Style->Draw();

  e_C->SetLineColor(kGreen);
  e_C->SetLineStyle(1);
  //e_C->Draw("SAMEC");

  e_W->SetLineColor(kRed);
  e_W->SetLineStyle(1);
  //e_W->Draw("SAMEC");

  e_CTot->SetLineColor(kGreen+2);
  e_CTot->SetLineStyle(1);
  e_CTot->Draw("SAMEC");

  eDR_CTot->SetLineColor(kBlue+2);
  eDR_CTot->SetLineStyle(1);
  eDR_CTot->Draw("SAMEC");

  
  TLegend *leg1;
  leg1 = new TLegend(0.1,0.8,0.9,0.9);
  leg1->SetNColumns(2);
  leg1->SetLineColor(1);
  leg1->SetTextSize(0.032);

  // leg1->AddEntry((TObject*)0,"lep,jet assignment","");
  // leg1->AddEntry((TObject*)0,"","");
  leg1->AddEntry(e_CTot,  "BDT",           "PLE");
  leg1->AddEntry(eDR_CTot,"BDT with DR",           "PLE");
  leg1->AddEntry((TObject*)0,(TString)Form("Eff = %.0f",(100.*TotEff))+"%",  "");
  leg1->AddEntry((TObject*)0,(TString)Form("Eff with DR = %.0f",(100.*TotEffDR))+"%",  "");

  leg1->Draw();


  c0->cd(2);
  c0->cd(2)->SetGrid();

  TH1 *p_Style = (TH1*)h_C->Clone();  
  p_Style->SetTitle("Purity in the " + (TString)h_C->GetTitle() + " for " + Cut);
  p_Style->GetXaxis()->SetTitle((TString)h_C->GetXaxis()->GetTitle());
  p_Style->GetYaxis()->SetTitle("Purity");

  p_Style->GetYaxis()->SetTitleOffset(1.2);
  p_Style->GetYaxis()->SetRangeUser(0.,1.2);
  p_Style->Reset();
  p_Style->Draw();
  
  purcut_C->SetLineColor(kGreen);
  purcut_C->SetLineStyle(1);
  // purcut_C->Draw("SAMEC");

  purcut_CTot->SetLineColor(kGreen+2);
  purcut_CTot->SetLineStyle(1);
  purcut_CTot->Draw("SAMEC");

  purDRcut_CTot->SetLineColor(kBlue);
  purDRcut_CTot->SetLineStyle(1);
  purDRcut_CTot->Draw("SAMEC");


  TLegend *leg2;
  leg2 = new TLegend(0.1,0.8,0.9,0.9);
  leg2->SetNColumns(2);
  leg2->SetLineColor(1);
  leg2->SetTextSize(0.032);

  leg2->AddEntry(purcut_CTot, "BDT","PLE");
  leg2->AddEntry(purDRcut_CTot, "BDT with DR","PLE");
  leg2->AddEntry((TObject*)0,(TString)Form("Pur = %.0f",(100.*TotPurcut))+"%",  "");
  leg2->AddEntry((TObject*)0,(TString)Form("Pur with DR = %.0f",(100.*TotPurDRcut))+"%",  "");

  leg2->Draw();

  c0->SaveAs("../Figures/BDTPlots/Eff_" + Ref + "_" + Histo + "_" + Channel + "_" + Cut +"DR.pdf");
}// Function




void BDTEfficienciesPerChannel(TString h_name){

  CreateBDTEfficiencyCurve("4j2b","all",h_name);
  CreateBDTEfficiencyCurve("3j1b","all",h_name);

}

void BDTEfficienciesDRComparison(){

  // BDTEfficienciesPerChannel("h_bJet_pT");
  // BDTEfficienciesPerChannel("h_bJet_phi");
  // BDTEfficienciesPerChannel("h_bJet_csv");
  BDTEfficienciesPerChannel("h_LepJet_DPhi");
  // BDTEfficienciesPerChannel("h_LepJet_DR");
  // BDTEfficienciesPerChannel("h_LepJet_Mass");

}
