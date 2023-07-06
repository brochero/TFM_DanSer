
TString callTH1 (TString ch, TString cut, TString histo){
  return "central/" + ch + "/" + cut + "/" + histo + "_" + ch + "_" + cut + "_central";
}


void CreateBDTEfficiencyCurve(TString Cut,
			      TString Channel,
			      TString Histo,
			      unsigned int newbin = 2){
  

  gStyle->SetOptStat("emruo");
  gStyle->SetOptStat(kFALSE);
  
  float MarkerSize = 0.7;
  int LineStyle  = 2;

  TString Ref    = "MultiRegions_Std-r9-v0";
  TString RefCut = "MultiRegions_std-r9-BDTCut004-v0";

  TString inputfile = "../HistoResult/" + Ref + "/" + Ref + "_BDTValidation_FNano2016-v61_TTToSemiLeptonic_TuneCP5_PSweights_13TeV-powheg-pythia8.root";
  TFile *hfile = NULL;
  hfile = TFile::Open(inputfile);
  cout << "file loaded: " << inputfile << endl;

  TString inputfileCut = "../HistoResult/" + RefCut + "/" + RefCut + "_BDTValidation_FNano2016-v61_TTToSemiLeptonic_TuneCP5_PSweights_13TeV-powheg-pythia8.root";
  TFile *hfileCut = NULL;
  hfileCut = TFile::Open(inputfileCut);
  cout << "file loaded: " << inputfileCut << endl;


  TString Refr    = "MultiRegions_Std-r9-QGL-NoDR-v0";
  TString RefCutr = "MultiRegions_std-r9-NoDR-BDTCut004-v0";
    
  TString inputfiler = "../HistoResult/" + Refr + "/" + Refr + "_BDTValidation_FNano2016-v61_TTToSemiLeptonic_TuneCP5_PSweights_13TeV-powheg-pythia8.root";
  TFile *hfiler = NULL;
  hfiler = TFile::Open(inputfiler);
  cout << "file loaded: " << inputfiler << endl;

  TString inputfileCutr = "../HistoResult/" + RefCutr + "/" + RefCutr + "_BDTValidation_FNano2016-v61_TTToSemiLeptonic_TuneCP5_PSweights_13TeV-powheg-pythia8.root";
  TFile *hfileCutr = NULL;
  hfileCutr = TFile::Open(inputfileCutr);
  cout << "file loaded: " << inputfileCutr << endl;



  
  TH1::SetDefaultSumw2(kTRUE);  

  TH1D *h_C, *h_W, *h_I;
  cout << "Loading histograms... " << endl;
  h_C  = (TH1D*) hfile->Get(callTH1(Channel,"C"+Cut,Histo))->Clone();
  h_W  = (TH1D*) hfile->Get(callTH1(Channel,"W"+Cut,Histo))->Clone();
  h_I  = (TH1D*) hfile->Get(callTH1(Channel,"I"+Cut,Histo))->Clone();

  TH1D *h_P, *h_Tot;
  h_P  = (TH1D*) h_C->Clone(); 
  h_P->Add(h_W);
  h_Tot  = (TH1D*) h_P->Clone();
  h_Tot->Add(h_I);

  TH1D *hcut_C, *hcut_W, *hcut_I;
  cout << "Loading histograms (with BDT cut)... " << endl;
  hcut_C  = (TH1D*) hfileCut->Get(callTH1(Channel,"C"+Cut,Histo))->Clone();
  hcut_W  = (TH1D*) hfileCut->Get(callTH1(Channel,"W"+Cut,Histo))->Clone();
  hcut_I  = (TH1D*) hfileCut->Get(callTH1(Channel,"I"+Cut,Histo))->Clone();

  TH1D *hcut_P, *hcut_Tot;
  hcut_P  = (TH1D*) hcut_C->Clone(); 
  hcut_P->Add(hcut_W);
  hcut_Tot  = (TH1D*) hcut_P->Clone();
  hcut_Tot->Add(hcut_I);

  // rebinning
  h_C  ->Rebin(newbin);
  h_W  ->Rebin(newbin);
  h_P  ->Rebin(newbin);
  h_Tot->Rebin(newbin);

  hcut_C  ->Rebin(newbin);
  hcut_W  ->Rebin(newbin);
  hcut_P  ->Rebin(newbin);
  hcut_Tot->Rebin(newbin);

  TH1D *hr_C, *hr_W, *hr_I;
  cout << "Loading histograms... " << endl;
  hr_C  = (TH1D*) hfiler->Get(callTH1(Channel,"C"+Cut,Histo))->Clone();
  hr_W  = (TH1D*) hfiler->Get(callTH1(Channel,"W"+Cut,Histo))->Clone();
  hr_I  = (TH1D*) hfiler->Get(callTH1(Channel,"I"+Cut,Histo))->Clone();

  TH1D *hr_P, *hr_Tot;
  hr_P  = (TH1D*) hr_C->Clone(); 
  hr_P->Add(hr_W);
  hr_Tot  = (TH1D*) hr_P->Clone();
  hr_Tot->Add(hr_I);

  TH1D *hrcut_C, *hrcut_W, *hrcut_I;
  cout << "Loading histograms (with BDT cut)... " << endl;
  hrcut_C  = (TH1D*) hfileCutr->Get(callTH1(Channel,"C"+Cut,Histo))->Clone();
  hrcut_W  = (TH1D*) hfileCutr->Get(callTH1(Channel,"W"+Cut,Histo))->Clone();
  hrcut_I  = (TH1D*) hfileCutr->Get(callTH1(Channel,"I"+Cut,Histo))->Clone();

  TH1D *hrcut_P, *hrcut_Tot;
  hrcut_P  = (TH1D*) hrcut_C->Clone(); 
  hrcut_P->Add(hrcut_W);
  hrcut_Tot  = (TH1D*) hrcut_P->Clone();
  hrcut_Tot->Add(hrcut_I);

  // rebinning
  hr_C  ->Rebin(newbin);
  hr_W  ->Rebin(newbin);
  hr_P  ->Rebin(newbin);
  hr_Tot->Rebin(newbin);

  hrcut_C  ->Rebin(newbin);
  hrcut_W  ->Rebin(newbin);
  hrcut_P  ->Rebin(newbin);
  hrcut_Tot->Rebin(newbin);

  // // Number of events
  // double n_CTot = h_C->Integral();   
  // double n_WTot = h_W->Integral();   
  // double n_ITot = h_I->Integral();   
  // double n_Tot  = n_CTot + n_WTot + n_ITot;
  // double n_PTot = n_CTot + n_WTot;

  // // Efficiencies
  TEfficiency *e_C = new TEfficiency("Eff_" + ((TString)h_C->GetName()),
				     "Efficiency; BDT Cut; Efficiency",
				     h_C->GetNbinsX(),
				     h_C->GetXaxis()->GetBinLowEdge(0),
				     h_C->GetXaxis()->GetBinLowEdge(h_C->GetNbinsX()+1));

  TEfficiency *e_W    = (TEfficiency *)e_C->Clone();
  TEfficiency *e_CTot = (TEfficiency *)e_C->Clone();

  TEfficiency *er_C    = (TEfficiency *)e_C->Clone();
  TEfficiency *er_W    = (TEfficiency *)e_C->Clone();
  TEfficiency *er_CTot = (TEfficiency *)e_C->Clone();

  e_C   ->SetPassedHistogram(*hcut_C,"f");
  e_C   ->SetTotalHistogram (*h_P,   "f");
  e_W   ->SetPassedHistogram(*hcut_W,"f");
  e_W   ->SetTotalHistogram (*h_P,   "f");
  e_CTot->SetPassedHistogram(*hcut_C,"f");
  e_CTot->SetTotalHistogram (*h_Tot, "f");

  er_C   ->SetPassedHistogram(*hrcut_C,"f");
  er_C   ->SetTotalHistogram (*hr_P,   "f");
  er_W   ->SetPassedHistogram(*hrcut_W,"f");
  er_W   ->SetTotalHistogram (*hr_P,   "f");
  er_CTot->SetPassedHistogram(*hrcut_C,"f");
  er_CTot->SetTotalHistogram (*hr_Tot, "f");

  // Total numerical effifiency (after BDT cut)
  float TotEff = hcut_C->Integral()/h_Tot->Integral();
  float TotEffr = hrcut_C->Integral()/hr_Tot->Integral();

  // Distribution at GEN level
  TH1D *hg_C, *hg_W, *hg_I;
  cout << "Loading histograms... " << endl;
  hg_C  = (TH1D*) hfile->Get(callTH1(Channel,"C"+Cut,"h_lQb_DPhi"))->Clone();
  hg_W  = (TH1D*) hfile->Get(callTH1(Channel,"W"+Cut,"h_lQb_DPhi"))->Clone();
  hg_I  = (TH1D*) hfile->Get(callTH1(Channel,"I"+Cut,"h_lQb_DPhi"))->Clone();

  TH1D *hg_P, *hg_Tot;
  hg_P  = (TH1D*) hg_C->Clone(); 
  hg_P->Add(hg_W);
  hg_Tot  = (TH1D*) hg_P->Clone();
  hg_Tot->Add(hg_I);

  TH1D *hgcut_C, *hgcut_W, *hgcut_I;
  cout << "Loading histograms... " << endl;
  hgcut_C  = (TH1D*) hfileCut->Get(callTH1(Channel,"C"+Cut,"h_lQb_DPhi"))->Clone();
  hgcut_W  = (TH1D*) hfileCut->Get(callTH1(Channel,"W"+Cut,"h_lQb_DPhi"))->Clone();
  hgcut_I  = (TH1D*) hfileCut->Get(callTH1(Channel,"I"+Cut,"h_lQb_DPhi"))->Clone();

  TH1D *hgcut_P, *hgcut_Tot;
  hgcut_P  = (TH1D*) hgcut_C->Clone(); 
  hgcut_P->Add(hgcut_W);
  hgcut_Tot  = (TH1D*) hgcut_P->Clone();
  hgcut_Tot->Add(hgcut_I);

  // Rebinning
  hg_C  ->Rebin(newbin);
  hg_W  ->Rebin(newbin);
  hg_I  ->Rebin(newbin);
  hg_P  ->Rebin(newbin);
  hg_Tot->Rebin(newbin);
  
  // Purity
  TEfficiency *p_C = new TEfficiency("PurC_" + ((TString)hg_C->GetName()),
				     "Purity; BDT Cut; Purity",
				     hg_C->GetNbinsX(),
				     hg_C->GetXaxis()->GetBinLowEdge(0),
				     hg_C->GetXaxis()->GetBinLowEdge(hg_C->GetNbinsX()+1));

  
  p_C->SetPassedHistogram(*hcut_C,   "f");
  p_C->SetTotalHistogram (*h_C, "f");

  
  // 2D histograms: Match GEN-RECO DeltaPhi  
  TH2D *h2D_C, *h2D_W, *h2D_I;
  h2D_C  = (TH2D*) hfile->Get(callTH1(Channel,"C"+Cut,"h_LepJetVslQb_DPhi"))->Clone();
  h2D_W  = (TH2D*) hfile->Get(callTH1(Channel,"W"+Cut,"h_LepJetVslQb_DPhi"))->Clone();
  h2D_I  = (TH2D*) hfile->Get(callTH1(Channel,"I"+Cut,"h_LepJetVslQb_DPhi"))->Clone();

  TH2D *h2Dcut_C, *h2Dcut_W, *h2Dcut_I;
  cout << callTH1(Channel,"C"+Cut,"h_LepJetVslQb_DPhi") << endl;
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

  // H2D Diagonal 
  TH1D *hd_C, *hd_W, *hd_I;
  TH1D *hd_P, *hd_Tot;
  hd_C  = (TH1D*) hfileCut->Get(callTH1(Channel,"C"+Cut,Histo))->Clone(); 
  // Rebinning
  hd_C->Rebin(newbin);
  hd_C->Reset();
  hd_W  = (TH1D*) hd_C->Clone(); 
  hd_I  = (TH1D*) hd_C->Clone(); 

  // Rebin for the 2D histograms: Should be done BEFORE extract the diagonal!
  h2Dcut_C->Rebin2D(newbin);
  h2Dcut_W->Rebin2D(newbin);
  h2Dcut_I->Rebin2D(newbin);
  
  // Diagonal extraction
  for(int ib=1; ib <= hd_C->GetNbinsX(); ib++){

    hd_C->SetBinContent( ib, h2Dcut_C->GetBinContent(ib,ib));
    hd_C->SetBinError  ( ib, h2Dcut_C->GetBinErrorUp(ib,ib));

    hd_W->SetBinContent( ib, h2Dcut_W->GetBinContent(ib,ib));
    hd_W->SetBinError  ( ib, h2Dcut_W->GetBinErrorUp(ib,ib));

    hd_I->SetBinContent( ib, h2Dcut_I->GetBinContent(ib,ib));
    hd_I->SetBinError  ( ib, h2Dcut_I->GetBinErrorUp(ib,ib));

  }
    
  TEfficiency *pur_C = new TEfficiency("pur_C" + ((TString)hd_C->GetName()),
				       "Purity; ; Efficiency",
				       hd_C->GetNbinsX(),
				       hd_C->GetXaxis()->GetBinLowEdge(0),
				       hd_C->GetXaxis()->GetBinLowEdge(hd_C->GetNbinsX()+1));

  TEfficiency *pur_W    = (TEfficiency *) pur_C->Clone();
  TEfficiency *pur_CTot = (TEfficiency *) pur_C->Clone();

  pur_C->SetPassedHistogram(*hd_C,"f");
  pur_C->SetTotalHistogram (*(hcut_C), "f");
  
  hd_W->Rebin();
  pur_W->SetPassedHistogram(*hd_I,"f");
  // pur_W->SetPassedHistogram(*hd_W,"f");
  pur_W->SetTotalHistogram (*(hcut_Tot), "f");

  pur_CTot->SetPassedHistogram(*hd_C, "f");
  pur_CTot->SetTotalHistogram (*(hcut_Tot),"f");

  float TotPurBDTCut = hcut_C->Integral()/h_C->Integral();
  float TotPur       = hd_C->Integral()/hcut_Tot->Integral();
  
  // Drawing

  TCanvas *c0;
  c0 = new TCanvas("Efficiency","",350,500);
  //c0->Divide(2,1);
  c0->cd();
  c0->cd()->SetGrid();
  
  TH1 *h_Style = (TH1*)h_C->Clone();  
  h_Style->SetTitle("Efficiency in the " + (TString)h_C->GetTitle() + " for " + Cut);
  h_Style->GetXaxis()->SetTitle((TString)h_C->GetXaxis()->GetTitle());
  h_Style->GetYaxis()->SetTitle("Efficiency");

  h_Style->GetYaxis()->SetTitleOffset(1.1);
  //h_Style->GetXaxis()->SetRangeUser(-0.2,0.5);
  h_Style->GetYaxis()->SetRangeUser(0.3,1.);
  h_Style->Reset();
  h_Style->Draw();

  e_C->SetLineColor(kGreen);
  e_C->SetLineStyle(1);
  e_C->Draw("SAMEC");

  er_C->SetLineColor(kBlue);
  er_C->SetLineStyle(1);
  er_C->Draw("SAMEC");

  e_W->SetLineColor(kRed);
  e_W->SetLineStyle(1);
  //e_W->Draw("SAMEC");

  e_CTot->SetLineColor(kGreen+2);
  e_CTot->SetLineStyle(1);
  e_CTot->Draw("SAMEC");

  er_CTot->SetLineColor(kBlue-9);
  er_CTot->SetLineStyle(1);
  er_CTot->Draw("SAMEC");

  
  TLegend *leg1;
  leg1 = new TLegend(0.1,0.8,0.9,0.9);
  leg1->SetNColumns(2);
  leg1->SetLineColor(1);
  leg1->SetTextSize(0.032);

  // leg1->AddEntry((TObject*)0,"lep,jet assignment","");
  // leg1->AddEntry((TObject*)0,"","");
  leg1->AddEntry(e_CTot, "Correct",           "PLE");
  leg1->AddEntry(er_CTot, "Correct No DR",           "PLE");
  leg1->AddEntry(e_C,    "Correct (possible)","PLE");
  leg1->AddEntry(er_C,    "Correct No DR(possible)","PLE");
  leg1->AddEntry((TObject*)0,(TString)Form("Eff = %.0f",(100.*TotEff))+"%",  "");
  leg1->AddEntry((TObject*)0,(TString)Form("Eff_{No DR} = %.0f",(100.*TotEffr))+"%",  "");

  leg1->Draw();


  // c0->cd(2);
  // c0->cd(2)->SetGrid();

  // TH1 *p_Style = (TH1*)h_C->Clone();  
  // p_Style->SetTitle("Purity in the " + (TString)h_C->GetTitle() + " for " + Cut);
  // p_Style->GetXaxis()->SetTitle((TString)h_C->GetXaxis()->GetTitle());
  // p_Style->GetYaxis()->SetTitle("Purity");

  // p_Style->GetYaxis()->SetTitleOffset(1.2);
  // p_Style->GetYaxis()->SetRangeUser(0.,1.2);
  // p_Style->Reset();
  // p_Style->Draw();
  
  // pur_C->SetLineColor(kGreen);
  // pur_C->SetLineStyle(1);
  // // pur_C->Draw("SAMEC");

  // p_C->SetLineColor(kBlue);
  // p_C->SetLineStyle(1);
  // p_C->Draw("SAMEL");

  // pur_W->SetLineColor(kRed);
  // pur_W->SetLineStyle(1);
  // pur_W->Draw("SAMEC");

  // pur_CTot->SetLineColor(kGreen+2);
  // pur_CTot->SetLineStyle(1);
  // pur_CTot->Draw("SAMEC");

  // TLegend *leg2;
  // leg2 = new TLegend(0.1,0.8,0.9,0.9);
  // leg2->SetNColumns(3);
  // leg2->SetLineColor(1);
  // leg2->SetTextSize(0.032);

  // // leg2->AddEntry((TObject*)0,"lep,jet assignment","");
  // // leg2->AddEntry((TObject*)0,"","");
  // leg2->AddEntry(p_C,      "Correct (pass)","PLE");
  // leg2->AddEntry(pur_CTot, "Correct (GEN match)","PLE");
  // leg2->AddEntry(e_W,      "Wrong",  "PLE");
  // leg2->AddEntry((TObject*)0,(TString)Form("Pur_{cut} = %.0f",(100.*TotPurBDTCut))+"%",  "");
  // leg2->AddEntry((TObject*)0,(TString)Form("Pur_{gen} = %.0f",(100.*TotPur))+"%",  "");

  // leg2->Draw();
  // ---------------------------------------------------

  // TPad *GPad = new TPad("GPad", "",0,0,1,1);
  // GPad = (TPad*)c0->GetPad(2);
    
  // GPad->Divide(2,1);

  // TPad *G1Pad = new TPad("G1Pad", "",0,0,1,1);
  // G1Pad = (TPad*)GPad->GetPad(1);
  // G1Pad->SetPad(0.0, 0.0, 1., 1.);

  // G1Pad->cd();
  // h_Style->Draw();

  // TEfficiency *e1_C = (TEfficiency*)e_C->Clone();
  // e1_C->SetLineColor(kBlack);
  // e1_C->SetLineStyle(1);
  // e1_C->Draw("SAMEL");

  // // Draw the axis of the 2nd TMultiGraph
  // TAxis *p_Ya = (TAxis *)h_Style->GetYaxis()->Clone();
  // Double_t a_ymin = p_Ya->GetXmin();
  // Double_t a_ymax = p_Ya->GetXmax()+0.05;
  // p_Ya->SetLabelSize(0);
  // p_Ya->SetTickLength(0);
  // p_Ya->SetLabelSize(0);
  // p_Ya->SetTickLength(0);
  // TGaxis *newyaxis = new TGaxis(0.505,a_ymin,0.505,a_ymax,a_ymin,a_ymax,510,"+L");     
  // newyaxis->SetLabelColor(kBlue);
  // newyaxis->SetLineColor(kBlue);
  // newyaxis->SetTitleColor(kBlue);
  // newyaxis->SetTitle("Purity");
  // newyaxis->Draw();


  // TPad *TinyPad = new TPad("TinyPad", "TinyPad",0,0,1,1);
  // TinyPad = (TPad*)GPad->GetPad(2);
  // TinyPad->SetPad(0.2, 0.12, 0.8, 0.5);

  // TinyPad->SetTopMargin(0.1);
  // TinyPad->SetBottomMargin(0.2);
  // TinyPad->SetRightMargin(0.18);
  // TinyPad->SetLeftMargin(0.18);
  // TinyPad->SetFillStyle(4000);
  // TinyPad->Draw();

  // TinyPad->cd();
  
  // TH1D *h_TinyStyle = (TH1D*)h_Style->Clone();

  // h_TinyStyle->SetTitle("");
  // h_TinyStyle->GetYaxis()->SetTitleOffset(0.6);
  // h_TinyStyle->GetXaxis()->SetRangeUser(0.05,0.11); 
  // h_TinyStyle->GetYaxis()->SetRangeUser(0.6,0.7); 

  // h_TinyStyle->GetYaxis()->SetTitle("");
  // h_TinyStyle->GetXaxis()->SetTitle(""); 

  // // h_TinyStyle->GetYaxis()->SetTitleSize(0.06);
  // // h_TinyStyle->GetXaxis()->SetTitleSize(0.06); 
  // h_TinyStyle->GetYaxis()->SetLabelSize(0.06);
  // h_TinyStyle->GetYaxis()->SetNdivisions(604);
  // h_TinyStyle->GetXaxis()->SetLabelSize(0.06); 
  // h_TinyStyle->GetXaxis()->SetNdivisions(604);

  // h_TinyStyle->Draw();
  // e1_C->Draw("SAMEL");
  // p_C->Draw("SAMEL");

  // TGaxis *newTinyyaxis = new TGaxis(0.12,0.6,0.12,0.7,0.6,0.7,604,"+L");     
  // newTinyyaxis->SetLabelColor(kBlue);
  // newTinyyaxis->SetLineColor(kBlue);
  // newTinyyaxis->SetTitleColor(kBlue);
  // newTinyyaxis->SetLabelSize(0.06); 
  // newTinyyaxis->Draw();


  c0->SaveAs("../Figures/BDTPlots/Eff_" + Ref + "_" + Histo + "_" + Channel + "_" + Cut +"DREffect.pdf");
}// Function




void BDTEfficienciesPerChannel(TString h_name){

  CreateBDTEfficiencyCurve("ge4","all",h_name);
  CreateBDTEfficiencyCurve("4jge3b","all",h_name);
  CreateBDTEfficiencyCurve("4j2b","all",h_name);
  CreateBDTEfficiencyCurve("3j2b","all",h_name);
  CreateBDTEfficiencyCurve("3j3b","all",h_name);
  CreateBDTEfficiencyCurve("3j1b","all",h_name);

}

void BDTEfficiencies_WithOut_DR(){

  // BDTEfficienciesPerChannel("h_bJet_pT");
  // BDTEfficienciesPerChannel("h_bJet_phi");
  // BDTEfficienciesPerChannel("h_bJet_csv");
  BDTEfficienciesPerChannel("h_LepJet_DPhi");
  // BDTEfficienciesPerChannel("h_LepJet_DR");
  // BDTEfficienciesPerChannel("h_LepJet_Mass");

}
