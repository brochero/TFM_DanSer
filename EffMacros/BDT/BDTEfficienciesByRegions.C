
// std::vector<TString> RegNames = {"2j","2j1b","2j2b","3j","3j1b","3j2b","3j3b","4j","4j1b","4j2b","4jge3b","ge5"};
std::vector<TString> RegNames = {"2j","2j1b","2j2b","3j","3j1b","3j2b","3j3b","4j","4j1b","4j2b","4jge3b"};
std::vector<int> RegCol       = {TColor::GetColor("#ff0000"),TColor::GetColor("#a2bf52"),TColor::GetColor("#994000"),
				 TColor::GetColor("#0008ff"),TColor::GetColor("#628ccc"),TColor::GetColor("#222663"),TColor::GetColor("#a600ff"),
				 TColor::GetColor("#ffbf00"),TColor::GetColor("#ff5e00"),TColor::GetColor("#e0d100"),TColor::GetColor("#00a396")};

TString callTH1 (TString ch, TString cut, TString histo){
  return "central/" + ch + "/" + cut + "/" + histo + "_" + ch + "_" + cut + "_central";
}


void CreateBDTEfficiencyCurve(TString Channel,
			      TString Histo){

  unsigned int NewBin = 2;

  gStyle->SetOptStat("emruo");
  gStyle->SetOptStat(kFALSE);
  TH1::SetDefaultSumw2(kTRUE);  
  
  float MarkerSize = 0.7;
  int LineStyle  = 2;
  
  TString Ref     = "BDTTrainingJulyNoBDTCut-v0";
  TString RefCut  = "BDTTrainingJulyBDTCut005-v0";
  
  TString inputfile     = "../HistoResult/" + Ref    + "/" + Ref    + "_BDTValidation_FNano2016-v61_TTToSemiLeptonic_TuneCP5_PSweights_13TeV-powheg-pythia8.root";
  TString inputfileCut  = "../HistoResult/" + RefCut + "/" + RefCut + "_BDTValidation_FNano2016-v61_TTToSemiLeptonic_TuneCP5_PSweights_13TeV-powheg-pythia8.root";

  TFile *hfile     = TFile::Open(inputfile);
  TFile *hfileCut  = TFile::Open(inputfileCut);


  std::vector<TEfficiency*> eff_C, eff_Tot, eff_W;
  std::vector<TEfficiency*> pur_C, pur_Tot;
  TH1D *Or;
  std::vector<float> TotalEff,TotalPur;

    
  for(int ireg=0; ireg<RegNames.size(); ireg++){

    TString Cut = RegNames.at(ireg);
    
    TH1D *h_C, *h_W, *h_I;
    h_C  = (TH1D*) hfile->Get(callTH1(Channel,"C"+Cut,Histo))->Clone();
    h_W  = (TH1D*) hfile->Get(callTH1(Channel,"W"+Cut,Histo))->Clone();
    h_I  = (TH1D*) hfile->Get(callTH1(Channel,"I"+Cut,Histo))->Clone();
    TH1D *h_P, *h_Tot;
    h_P  = (TH1D*) h_C->Clone(); 
    h_P->Add(h_W);
    h_Tot  = (TH1D*) h_P->Clone();
    h_Tot->Add(h_I);

    // CUT
    TH1D *hcut_C, *hcut_W, *hcut_I;
    hcut_C  = (TH1D*) hfileCut->Get(callTH1(Channel,"C"+Cut,Histo))->Clone();
    hcut_W  = (TH1D*) hfileCut->Get(callTH1(Channel,"W"+Cut,Histo))->Clone();
    hcut_I  = (TH1D*) hfileCut->Get(callTH1(Channel,"I"+Cut,Histo))->Clone();
    TH1D *hcut_P, *hcut_Tot;
    hcut_P  = (TH1D*) hcut_C->Clone(); 
    hcut_P->Add(hcut_W);
    hcut_Tot  = (TH1D*) hcut_P->Clone();
    hcut_Tot->Add(hcut_I);

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
  
    // Diagonal purity
    TH2D *h2D_C, *h2D_W, *h2D_I;
    h2D_C  = (TH2D*) hfile->Get(callTH1(Channel,"C"+Cut,"h_LepJetVslQb_DPhi"))->Clone();
    h2D_W  = (TH2D*) hfile->Get(callTH1(Channel,"W"+Cut,"h_LepJetVslQb_DPhi"))->Clone();
    h2D_I  = (TH2D*) hfile->Get(callTH1(Channel,"I"+Cut,"h_LepJetVslQb_DPhi"))->Clone();
    TH2D *h2Dcut_C, *h2Dcut_W, *h2Dcut_I;
    h2Dcut_C  = (TH2D*) hfileCut->Get(callTH1(Channel,"C"+Cut,"h_LepJetVslQb_DPhi"))->Clone();
    h2Dcut_W  = (TH2D*) hfileCut->Get(callTH1(Channel,"W"+Cut,"h_LepJetVslQb_DPhi"))->Clone();
    h2Dcut_I  = (TH2D*) hfileCut->Get(callTH1(Channel,"I"+Cut,"h_LepJetVslQb_DPhi"))->Clone();
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
  
    TH1D *hdcut_C, *hdcut_W, *hdcut_I;
    hdcut_C  = (TH1D*) h_C->Clone(); 
    hdcut_W  = (TH1D*) h_C->Clone(); 
    hdcut_I  = (TH1D*) h_C->Clone(); 

    // cout << hdcut_C->GetNbinsX() << endl;
    for(int ib=1; ib <= hdcut_C->GetNbinsX(); ib++){

      hdcut_C->SetBinContent( ib, h2Dcut_C->GetBinContent(ib,ib));
      hdcut_C->SetBinError  ( ib, h2Dcut_C->GetBinErrorUp(ib,ib));
      hdcut_W->SetBinContent( ib, h2Dcut_W->GetBinContent(ib,ib));
      hdcut_W->SetBinError  ( ib, h2Dcut_W->GetBinErrorUp(ib,ib));
      hdcut_I->SetBinContent( ib, h2Dcut_I->GetBinContent(ib,ib));
      hdcut_I->SetBinError  ( ib, h2Dcut_I->GetBinErrorUp(ib,ib));

    }
   
    TEfficiency *purcut_C = new TEfficiency("purity_C" + ((TString)hdcut_C->GetName()),
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


    eff_C  .push_back(e_C);
    eff_Tot.push_back(e_CTot);
    eff_W  .push_back(e_W);
    pur_C  .push_back(purcut_C);
    pur_Tot.push_back(purcut_CTot);


    Or = (TH1D*)h_C->Clone("Original");
    TotalEff.push_back(TotEff);
    TotalPur.push_back(TotPurcut);
    
  }
  
  // ------------------------
  // Drawing
  // ------------------------
  TCanvas *c0;
  c0 = new TCanvas("Efficiency");
  c0->Divide(2,1);
  c0->cd(1);
  c0->cd(1)->SetGrid();
  
  TH1 *h_Style = (TH1*)Or->Clone();  
  h_Style->SetTitle("Efficiency in the " + (TString)Or->GetTitle() + " for all regions");
  h_Style->GetXaxis()->SetTitle((TString)Or->GetXaxis()->GetTitle());
  h_Style->GetYaxis()->SetTitle("Efficiency");

  h_Style->GetYaxis()->SetTitleOffset(1.1);
  // h_Style->GetXaxis()->SetRangeUser(-0.2,0.5);
  h_Style->GetYaxis()->SetRangeUser(0.,1.2);
  h_Style->Reset();
  h_Style->Draw();

  TLegend *leg1;
  leg1 = new TLegend(0.1,0.8,0.9,0.9);
  leg1->SetNColumns(4);
  leg1->SetLineColor(1);
  leg1->SetTextSize(0.032);

  for(int ireg=0; ireg<RegNames.size(); ireg++){

    eff_C.at(ireg)->SetLineColor(RegCol.at(ireg));
    eff_C.at(ireg)->SetLineStyle(1);
    eff_C.at(ireg)->SetLineWidth(2);
    eff_C.at(ireg)->SetMarkerSize(0);
    // eff_C.at(ireg)->Draw("SAMECX0");

    eff_Tot.at(ireg)->SetLineColor(RegCol.at(ireg));
    eff_Tot.at(ireg)->SetLineStyle(1);
    eff_Tot.at(ireg)->SetLineWidth(2);
    eff_Tot.at(ireg)->SetMarkerSize(0);
    eff_Tot.at(ireg)->Draw("SAMECX0");

    if(ireg == 3) leg1->AddEntry((TObject*)0,"","");
    leg1->AddEntry(eff_C.at(ireg), RegNames.at(ireg), "L");
  }    
  
  leg1->Draw();


  c0->cd(2);
  c0->cd(2)->SetGrid();

  TH1 *p_Style = (TH1*)Or->Clone();  
  p_Style->SetTitle("Purity in the " + (TString)Or->GetTitle() + " for all regions");
  p_Style->GetXaxis()->SetTitle((TString)Or->GetXaxis()->GetTitle());
  p_Style->GetYaxis()->SetTitle("Purity");

  p_Style->GetYaxis()->SetTitleOffset(1.2);
  p_Style->GetYaxis()->SetRangeUser(0.,1.2);
  p_Style->Reset();
  p_Style->Draw();
  

  TLegend *leg2;
  leg2 = new TLegend(0.1,0.8,0.9,0.9);
  leg2->SetNColumns(4);
  leg2->SetLineColor(1);
  leg2->SetTextSize(0.032);

  for(int ireg=0; ireg<RegNames.size(); ireg++){

    pur_C.at(ireg)->SetLineColor(RegCol.at(ireg));
    pur_C.at(ireg)->SetLineStyle(1);
    pur_C.at(ireg)->SetLineWidth(2);
    pur_C.at(ireg)->SetMarkerSize(0.);
    // pur_C.at(ireg)->Draw("SAMECX0");

    pur_Tot.at(ireg)->SetLineColor(RegCol.at(ireg));
    pur_Tot.at(ireg)->SetLineStyle(1);
    pur_Tot.at(ireg)->SetMarkerSize(0.);
    pur_Tot.at(ireg)->Draw("SAMECX0");

    if(ireg == 3) leg2->AddEntry((TObject*)0,"","");
    leg2->AddEntry(pur_C.at(ireg), RegNames.at(ireg), "L");
    // leg2->AddEntry(pur_Tot.at(ireg), RegNames.at(ireg), "L");

  }
  
  // leg2->AddEntry(pur_Tot.at(0), "Correct",           "PLE");
  // leg2->AddEntry(pur_C.at(0),    "Correct (possible)","PLE");
  // leg2->AddEntry((TObject*)0,(TString)Form("Pur = %.0f",(100.*TotalPur.at(0)))+"%",  "");

  leg2->Draw();

  c0->SaveAs("../Figures/BDTPlots/Eff_" + Ref + "_" + Histo + "_" + Channel + "_ByRegions_wrt_Total.pdf");

}// Function




void BDTEfficienciesPerChannel(TString h_name){

  CreateBDTEfficiencyCurve("all",h_name);

}

void BDTEfficienciesByRegions(){

  // BDTEfficienciesPerChannel("h_bJet_pT");
  // BDTEfficienciesPerChannel("h_bJet_phi");
  // BDTEfficienciesPerChannel("h_bJet_csv");
  BDTEfficienciesPerChannel("h_LepJet_DPhi");
  // BDTEfficienciesPerChannel("h_LepJet_DR");
  // BDTEfficienciesPerChannel("h_LepJet_Mass");

}
