
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
  
  TString Ref     = "BDTTrainingJulyNoBDTCut-v0";
  TString RefCut  = "BDTTrainingJulyBDTCut004-v0";
  TString RefCut1 = "BDTTrainingJulyBDTCut005-v0";
  TString RefCut2 = "BDTTrainingJulyBDTCut006-v0";
  
  TString inputfile     = "../HistoResult/" + Ref + "/" + Ref + "_BDTValidation_FNano2016-v61_TTToSemiLeptonic_TuneCP5_PSweights_13TeV-powheg-pythia8.root";
  TString inputfileCut  = "../HistoResult/" + RefCut + "/" + RefCut + "_BDTValidation_FNano2016-v61_TTToSemiLeptonic_TuneCP5_PSweights_13TeV-powheg-pythia8.root";
  TString inputfileCut1 = "../HistoResult/" + RefCut + "/" + RefCut + "_BDTValidation_FNano2016-v61_TTToSemiLeptonic_TuneCP5_PSweights_13TeV-powheg-pythia8.root";
  TString inputfileCut2 = "../HistoResult/" + RefCut + "/" + RefCut + "_BDTValidation_FNano2016-v61_TTToSemiLeptonic_TuneCP5_PSweights_13TeV-powheg-pythia8.root";

  TFile *hfile     = TFile::Open(inputfile);
  TFile *hfileCut  = TFile::Open(inputfileCut);
  TFile *hfileCut1 = TFile::Open(inputfileCut1);
  TFile *hfileCut2 = TFile::Open(inputfileCut2);

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
  TH1D *hcut1_C, *hcut1_W, *hcut1_I;
  hcut1_C  = (TH1D*) hfileCut1->Get(callTH1(Channel,"C"+Cut,Histo))->Clone();
  hcut1_W  = (TH1D*) hfileCut1->Get(callTH1(Channel,"W"+Cut,Histo))->Clone();
  hcut1_I  = (TH1D*) hfileCut1->Get(callTH1(Channel,"I"+Cut,Histo))->Clone();
  TH1D *hcut1_P, *hcut1_Tot;
  hcut1_P  = (TH1D*) hcut1_C->Clone(); 
  hcut1_P->Add(hcut1_W);
  hcut1_Tot  = (TH1D*) hcut1_P->Clone();
  hcut1_Tot->Add(hcut1_I);
  // CUT 2
  TH1D *hcut2_C, *hcut2_W, *hcut2_I;
  hcut2_C  = (TH1D*) hfileCut2->Get(callTH1(Channel,"C"+Cut,Histo))->Clone();
  hcut2_W  = (TH1D*) hfileCut2->Get(callTH1(Channel,"W"+Cut,Histo))->Clone();
  hcut2_I  = (TH1D*) hfileCut2->Get(callTH1(Channel,"I"+Cut,Histo))->Clone();
  TH1D *hcut2_P, *hcut2_Tot;
  hcut2_P  = (TH1D*) hcut2_C->Clone(); 
  hcut2_P->Add(hcut2_W);
  hcut2_Tot  = (TH1D*) hcut2_P->Clone();
  hcut2_Tot->Add(hcut2_I);

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
  hcut1_C  ->Rebin(NewBin);
  hcut1_W  ->Rebin(NewBin);
  hcut1_I  ->Rebin(NewBin);
  hcut1_P  ->Rebin(NewBin);
  hcut1_Tot->Rebin(NewBin);
  hcut2_C  ->Rebin(NewBin);
  hcut2_W  ->Rebin(NewBin);
  hcut2_I  ->Rebin(NewBin);
  hcut2_P  ->Rebin(NewBin);
  hcut2_Tot->Rebin(NewBin);

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
  // // CUT1
  // TH1D *hgcut1_C, *hgcut1_W, *hgcut1_I;
  // hgcut1_C  = (TH1D*) hfileCut1->Get(callTH1(Channel,"C"+Cut,"h_lQb_DPhi"))->Clone();
  // hgcut1_W  = (TH1D*) hfileCut1->Get(callTH1(Channel,"W"+Cut,"h_lQb_DPhi"))->Clone();
  // hgcut1_I  = (TH1D*) hfileCut1->Get(callTH1(Channel,"I"+Cut,"h_lQb_DPhi"))->Clone();
  // TH1D *hgcut1_P, *hgcut1_Tot;  
  // hgcut1_P  = (TH1D*) hgcut1_C->Clone(); 
  // hgcut1_P->Add(hgcut1_W);
  // hgcut1_Tot = (TH1D*) hgcut1_P->Clone();
  // hgcut1_Tot->Add(hgcut1_I);
  // // CUT2
  // TH1D *hgcut2_C, *hgcut2_W, *hgcut2_I;
  // hgcut2_C  = (TH1D*) hfileCut2->Get(callTH1(Channel,"C"+Cut,"h_lQb_DPhi"))->Clone();
  // hgcut2_W  = (TH1D*) hfileCut2->Get(callTH1(Channel,"W"+Cut,"h_lQb_DPhi"))->Clone();
  // hgcut2_I  = (TH1D*) hfileCut2->Get(callTH1(Channel,"I"+Cut,"h_lQb_DPhi"))->Clone();
  // TH1D *hgcut2_P, *hgcut2_Tot;  
  // hgcut2_P  = (TH1D*) hgcut2_C->Clone(); 
  // hgcut2_P->Add(hgcut2_W);
  // hgcut2_Tot = (TH1D*) hgcut2_P->Clone();
  // hgcut2_Tot->Add(hgcut2_I);

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
  TH2D *h2Dcut1_C, *h2Dcut1_W, *h2Dcut1_I;
  h2Dcut1_C  = (TH2D*) hfileCut1->Get(callTH1(Channel,"C"+Cut,"h_LepJetVslQb_DPhi"))->Clone();
  h2Dcut1_W  = (TH2D*) hfileCut1->Get(callTH1(Channel,"W"+Cut,"h_LepJetVslQb_DPhi"))->Clone();
  h2Dcut1_I  = (TH2D*) hfileCut1->Get(callTH1(Channel,"I"+Cut,"h_LepJetVslQb_DPhi"))->Clone();
  TH2D *h2Dcut2_C, *h2Dcut2_W, *h2Dcut2_I;
  h2Dcut2_C  = (TH2D*) hfileCut2->Get(callTH1(Channel,"C"+Cut,"h_LepJetVslQb_DPhi"))->Clone();
  h2Dcut2_W  = (TH2D*) hfileCut2->Get(callTH1(Channel,"W"+Cut,"h_LepJetVslQb_DPhi"))->Clone();
  h2Dcut2_I  = (TH2D*) hfileCut2->Get(callTH1(Channel,"I"+Cut,"h_LepJetVslQb_DPhi"))->Clone();
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
  TH2D *h2Dcut1_P, *h2Dcut1_Tot;
  h2Dcut1_P  = (TH2D*) h2Dcut1_C->Clone();
  h2Dcut1_P->Add(h2Dcut1_W);
  h2Dcut1_Tot  = (TH2D*) h2Dcut1_P->Clone();
  h2Dcut1_Tot->Add(h2Dcut1_I);
  TH2D *h2Dcut2_P, *h2Dcut2_Tot;
  h2Dcut2_P  = (TH2D*) h2Dcut2_C->Clone();
  h2Dcut2_P->Add(h2Dcut2_W);
  h2Dcut2_Tot  = (TH2D*) h2Dcut2_P->Clone();
  h2Dcut2_Tot->Add(h2Dcut2_I);

  
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
  h2Dcut1_C  ->Rebin2D(NewBin,NewBin);
  h2Dcut1_W  ->Rebin2D(NewBin,NewBin);
  h2Dcut1_I  ->Rebin2D(NewBin,NewBin);
  h2Dcut1_P  ->Rebin2D(NewBin,NewBin);
  h2Dcut1_Tot->Rebin2D(NewBin,NewBin);
  h2Dcut2_C  ->Rebin2D(NewBin,NewBin);
  h2Dcut2_W  ->Rebin2D(NewBin,NewBin);
  h2Dcut2_I  ->Rebin2D(NewBin,NewBin);
  h2Dcut2_P  ->Rebin2D(NewBin,NewBin);
  h2Dcut2_Tot->Rebin2D(NewBin,NewBin);

  
  TH1D *hdcut_C, *hdcut_W, *hdcut_I;
  hdcut_C  = (TH1D*) h_C->Clone(); 
  hdcut_W  = (TH1D*) h_C->Clone(); 
  hdcut_I  = (TH1D*) h_C->Clone(); 
  TH1D *hdcut1_C, *hdcut1_W, *hdcut1_I;
  hdcut1_C  = (TH1D*) h_C->Clone(); 
  hdcut1_W  = (TH1D*) h_C->Clone(); 
  hdcut1_I  = (TH1D*) h_C->Clone(); 
  TH1D *hdcut2_C, *hdcut2_W, *hdcut2_I;
  hdcut2_C  = (TH1D*) h_C->Clone(); 
  hdcut2_W  = (TH1D*) h_C->Clone(); 
  hdcut2_I  = (TH1D*) h_C->Clone(); 

  cout << hdcut_C->GetNbinsX() << endl;
  for(int ib=1; ib <= hdcut_C->GetNbinsX(); ib++){

    hdcut_C->SetBinContent( ib, h2Dcut_C->GetBinContent(ib,ib));
    hdcut_C->SetBinError  ( ib, h2Dcut_C->GetBinErrorUp(ib,ib));
    hdcut_W->SetBinContent( ib, h2Dcut_W->GetBinContent(ib,ib));
    hdcut_W->SetBinError  ( ib, h2Dcut_W->GetBinErrorUp(ib,ib));
    hdcut_I->SetBinContent( ib, h2Dcut_I->GetBinContent(ib,ib));
    hdcut_I->SetBinError  ( ib, h2Dcut_I->GetBinErrorUp(ib,ib));

    hdcut1_C->SetBinContent( ib, h2Dcut1_C->GetBinContent(ib,ib));
    hdcut1_C->SetBinError  ( ib, h2Dcut1_C->GetBinErrorUp(ib,ib));
    hdcut1_W->SetBinContent( ib, h2Dcut1_W->GetBinContent(ib,ib));
    hdcut1_W->SetBinError  ( ib, h2Dcut1_W->GetBinErrorUp(ib,ib));
    hdcut1_I->SetBinContent( ib, h2Dcut1_I->GetBinContent(ib,ib));
    hdcut1_I->SetBinError  ( ib, h2Dcut1_I->GetBinErrorUp(ib,ib));

    hdcut2_C->SetBinContent( ib, h2Dcut2_C->GetBinContent(ib,ib));
    hdcut2_C->SetBinError  ( ib, h2Dcut2_C->GetBinErrorUp(ib,ib));
    hdcut2_W->SetBinContent( ib, h2Dcut2_W->GetBinContent(ib,ib));
    hdcut2_W->SetBinError  ( ib, h2Dcut2_W->GetBinErrorUp(ib,ib));
    hdcut2_I->SetBinContent( ib, h2Dcut2_I->GetBinContent(ib,ib));
    hdcut2_I->SetBinError  ( ib, h2Dcut2_I->GetBinErrorUp(ib,ib));

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

  TEfficiency *purcut1_C    = (TEfficiency *) purcut_C->Clone();
  TEfficiency *purcut1_CTot = (TEfficiency *) purcut_C->Clone();
  purcut1_C->   SetPassedHistogram(*hdcut1_C,   "f");
  purcut1_C->   SetTotalHistogram (*(hcut1_C),  "f");
  purcut1_CTot->SetPassedHistogram(*hdcut1_C,   "f");
  purcut1_CTot->SetTotalHistogram (*(hcut1_Tot),"f");
  float TotPurcut1 = hdcut1_C->Integral()/hcut1_Tot->Integral();

  TEfficiency *purcut2_C    = (TEfficiency *) purcut_C->Clone();
  TEfficiency *purcut2_CTot = (TEfficiency *) purcut_C->Clone();
  purcut2_C->   SetPassedHistogram(*hdcut2_C,   "f");
  purcut2_C->   SetTotalHistogram (*(hcut2_C),  "f");
  purcut2_CTot->SetPassedHistogram(*hdcut2_C,   "f");
  purcut2_CTot->SetTotalHistogram (*(hcut2_Tot),"f");
  float TotPurcut2 = hdcut2_C->Integral()/hcut2_Tot->Integral();

  
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
  e_C->Draw("SAMEC");

  e_W->SetLineColor(kRed);
  e_W->SetLineStyle(1);
  e_W->Draw("SAMEC");

  e_CTot->SetLineColor(kGreen+2);
  e_CTot->SetLineStyle(1);
  e_CTot->Draw("SAMEC");

  
  TLegend *leg1;
  leg1 = new TLegend(0.1,0.8,0.9,0.9);
  leg1->SetNColumns(3);
  leg1->SetLineColor(1);
  leg1->SetTextSize(0.032);

  // leg1->AddEntry((TObject*)0,"lep,jet assignment","");
  // leg1->AddEntry((TObject*)0,"","");
  leg1->AddEntry(e_CTot, "Correct",           "PLE");
  leg1->AddEntry(e_C,    "Correct (possible)","PLE");
  leg1->AddEntry(e_W,    "Wrong (possible)",  "PLE");
  leg1->AddEntry((TObject*)0,(TString)Form("Eff = %.0f",(100.*TotEff))+"%",  "");

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
  purcut_C->Draw("SAMEC");

  purcut_CTot->SetLineColor(kGreen+2);
  purcut_CTot->SetLineStyle(1);
  purcut_CTot->Draw("SAMEC");

  purcut1_C->SetLineColor(kBlue);
  purcut1_C->SetLineStyle(1);
  purcut1_C->Draw("SAMEC");

  purcut1_CTot->SetLineColor(kBlue+2);
  purcut1_CTot->SetLineStyle(1);
  purcut1_CTot->Draw("SAMEC");

  purcut2_C->SetLineColor(kRed);
  purcut2_C->SetLineStyle(1);
  purcut2_C->Draw("SAMEC");

  purcut2_CTot->SetLineColor(kRed+2);
  purcut2_CTot->SetLineStyle(1);
  purcut2_CTot->Draw("SAMEC");

  TLegend *leg2;
  leg2 = new TLegend(0.1,0.8,0.9,0.9);
  leg2->SetNColumns(2);
  leg2->SetLineColor(1);
  leg2->SetTextSize(0.032);

  leg2->AddEntry(purcut_CTot, "Correct","PLE");
  leg2->AddEntry((TObject*)0,(TString)Form("Pur = %.0f",(100.*TotPurcut))+"%",  "");

  leg2->Draw();

  c0->SaveAs("../Figures/BDTPlots/Eff_" + Ref + "_" + Histo + "_" + Channel + "_" + Cut +"AllCut.pdf");
}// Function




void BDTEfficienciesPerChannel(TString h_name){

  CreateBDTEfficiencyCurve("4j2b","all",h_name);
  CreateBDTEfficiencyCurve("3j1b","all",h_name);

}

void BDTEfficienciesCutsComparison(){

  // BDTEfficienciesPerChannel("h_bJet_pT");
  // BDTEfficienciesPerChannel("h_bJet_phi");
  // BDTEfficienciesPerChannel("h_bJet_csv");
  BDTEfficienciesPerChannel("h_LepJet_DPhi");
  // BDTEfficienciesPerChannel("h_LepJet_DR");
  // BDTEfficienciesPerChannel("h_LepJet_Mass");

}
