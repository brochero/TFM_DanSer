#include "../HistoModifier.h" 

TString callTH1 (TString ch, TString cut, TString histo){
  return "central/" + ch + "/" + cut + "/" + histo + "_" + ch + "_" + cut + "_central";
}


void CreateBDTEfficiencyCurve(TString Cut,
			      TString Channel,
			      TString Histo){

  unsigned int NewBin = 6;

  gStyle->SetOptStat("emruo");
  gStyle->SetOptStat(kFALSE);
  TH1::SetDefaultSumw2(kTRUE);  
  
  float MarkerSize = 0.7;
  int LineStyle  = 2;
  
  TString Ref     = "ValGenJetNovNoBDTCut-v0";
  TString RefCut  = "ValGenJetNov-v0";  
  TString inputfile     = "../../HistoResult/" + Ref    + "/" + Ref    + "_BDTValidation_GenJetsFNano2017-v7_TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8.root";
  TString inputfileCut  = "../../HistoResult/" + RefCut + "/" + RefCut + "_BDTValidation_GenJetsFNano2017-v7_TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8.root";

  TString CutValName = "008";
  //TString hDiagName = "lQb_Mass";
  TString hDiagName = "lgjb_Mass";
  
  TFile *hfile     = TFile::Open(inputfile);
  TFile *hfileCut  = TFile::Open(inputfileCut);

  TH1D *ho_C, *ho_W, *ho_I;
  ho_C  = (TH1D*) hfile->Get(callTH1(Channel,"C"+Cut,Histo))->Clone();
  ho_W  = (TH1D*) hfile->Get(callTH1(Channel,"W"+Cut,Histo))->Clone();
  ho_I  = (TH1D*) hfile->Get(callTH1(Channel,"I"+Cut,Histo))->Clone();
  TH1D *ho_P, *ho_Tot;
  ho_P  = (TH1D*) ho_C->Clone(); 
  ho_P->Add(ho_W);
  ho_Tot  = (TH1D*) ho_P->Clone();
  ho_Tot->Add(ho_I);

 // CUT
  TH1D *hocut_C, *hocut_W, *hocut_I;
  hocut_C  = (TH1D*) hfileCut->Get(callTH1(Channel,"C"+Cut,Histo))->Clone();
  hocut_W  = (TH1D*) hfileCut->Get(callTH1(Channel,"W"+Cut,Histo))->Clone();
  hocut_I  = (TH1D*) hfileCut->Get(callTH1(Channel,"I"+Cut,Histo))->Clone();
  TH1D *hocut_P, *hocut_Tot;
  hocut_P  = (TH1D*) hocut_C->Clone(); 
  hocut_P->Add(hocut_W);
  hocut_Tot  = (TH1D*) hocut_P->Clone();
  hocut_Tot->Add(hocut_I);
    
  TH1D *h_C      = HistoModifier(ho_C,      Cut);
  TH1D *h_W      = HistoModifier(ho_W,      Cut);
  TH1D *h_I      = HistoModifier(ho_I,      Cut);
  TH1D *h_P      = HistoModifier(ho_P,      Cut);
  TH1D *h_Tot    = HistoModifier(ho_Tot,    Cut);
  TH1D *hcut_C   = HistoModifier(hocut_C,   Cut);
  TH1D *hcut_W   = HistoModifier(hocut_W,   Cut);
  TH1D *hcut_I   = HistoModifier(hocut_I,   Cut);
  TH1D *hcut_P   = HistoModifier(hocut_P,   Cut);
  TH1D *hcut_Tot = HistoModifier(hocut_Tot, Cut);

  // Number of events
  double n_CTot = h_C->Integral();   
  double n_WTot = h_W->Integral();   
  double n_ITot = h_I->Integral();   

  double n_Tot = n_CTot + n_WTot + n_ITot;
  double n_PTot = n_CTot + n_WTot;

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
  TH2D *ho2D_C, *ho2D_W, *ho2D_I;
  ho2D_C  = (TH2D*) hfile->Get(callTH1(Channel,"C"+Cut,"h_LepJetVs" + hDiagName))->Clone();
  ho2D_W  = (TH2D*) hfile->Get(callTH1(Channel,"W"+Cut,"h_LepJetVs" + hDiagName))->Clone();
  ho2D_I  = (TH2D*) hfile->Get(callTH1(Channel,"I"+Cut,"h_LepJetVs" + hDiagName))->Clone();
  TH2D *ho2Dcut_C, *ho2Dcut_W, *ho2Dcut_I;
  ho2Dcut_C  = (TH2D*) hfileCut->Get(callTH1(Channel,"C"+Cut,"h_LepJetVs" + hDiagName))->Clone();
  ho2Dcut_W  = (TH2D*) hfileCut->Get(callTH1(Channel,"W"+Cut,"h_LepJetVs" + hDiagName))->Clone();
  ho2Dcut_I  = (TH2D*) hfileCut->Get(callTH1(Channel,"I"+Cut,"h_LepJetVs" + hDiagName))->Clone();
  TH2D *ho2D_P, *ho2D_Tot;
  ho2D_P  = (TH2D*) ho2D_C->Clone();
  ho2D_P->Add(ho2D_W);
  ho2D_Tot  = (TH2D*) ho2D_P->Clone();
  ho2D_Tot->Add(ho2D_I);
  TH2D *ho2Dcut_P, *ho2Dcut_Tot;
  ho2Dcut_P  = (TH2D*) ho2Dcut_C->Clone();
  ho2Dcut_P->Add(ho2Dcut_W);
  ho2Dcut_Tot  = (TH2D*) ho2Dcut_P->Clone();
  ho2Dcut_Tot->Add(ho2Dcut_I);
  
  TH2D *h2D_C      = HistoModifier2D(ho2D_C,     Cut);
  TH2D *h2D_W      = HistoModifier2D(ho2D_W,     Cut);
  TH2D *h2D_I      = HistoModifier2D(ho2D_I,     Cut);
  TH2D *h2D_P      = HistoModifier2D(ho2D_P,     Cut);
  TH2D *h2D_Tot    = HistoModifier2D(ho2D_Tot,   Cut);
  TH2D *h2Dcut_C   = HistoModifier2D(ho2Dcut_C,  Cut);
  TH2D *h2Dcut_W   = HistoModifier2D(ho2Dcut_W,  Cut);
  TH2D *h2Dcut_I   = HistoModifier2D(ho2Dcut_I,  Cut);
  TH2D *h2Dcut_P   = HistoModifier2D(ho2Dcut_P,  Cut);
  TH2D *h2Dcut_Tot = HistoModifier2D(ho2Dcut_Tot,Cut);

  TH1D *hdcut_C, *hdcut_W, *hdcut_I;
  hdcut_C  = (TH1D*) h_C->Clone(); 
  hdcut_W  = (TH1D*) h_C->Clone(); 
  hdcut_I  = (TH1D*) h_C->Clone(); 

  cout << hdcut_C->GetNbinsX() << endl;
  for(int ib=1; ib <= hdcut_C->GetNbinsX(); ib++){

    hdcut_C->SetBinContent( ib, h2Dcut_C->GetBinContent(ib,ib));
    hdcut_C->SetBinError  ( ib, h2Dcut_C->GetBinErrorUp(ib,ib));
    hdcut_W->SetBinContent( ib, h2Dcut_W->GetBinContent(ib,ib));
    hdcut_W->SetBinError  ( ib, h2Dcut_W->GetBinErrorUp(ib,ib));
    hdcut_I->SetBinContent( ib, h2Dcut_I->GetBinContent(ib,ib));
    hdcut_I->SetBinError  ( ib, h2Dcut_I->GetBinErrorUp(ib,ib));

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

  
  // ------------------------
  // Drawing
  // ------------------------
  TCanvas *c0;
  c0 = new TCanvas("c0","Efficiency",1000,500);
  c0->Divide(2,1);
  c0->cd(1);
  c0->cd(1)->SetGrid();
  
  TH1 *h_Style = (TH1*)h_C->Clone();  
  h_Style->SetTitle("BDT Efficiency (" + Cut + ")");
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

  TLegend *leg2;
  leg2 = new TLegend(0.1,0.8,0.9,0.9);
  leg2->SetNColumns(2);
  leg2->SetLineColor(1);
  leg2->SetTextSize(0.032);

  leg2->AddEntry(purcut_CTot, "Correct",           "PLE");
  leg2->AddEntry(purcut_C,    "Correct (possible)","PLE");
  leg2->AddEntry((TObject*)0,(TString)Form("Pur = %.0f",(100.*TotPurcut))+"%",  "");

  leg2->Draw();

  TString BDTDir = "../../Figures/BDTPlots-" + Ref + "/EffDiffFractions/";
  gSystem->mkdir(BDTDir,kTRUE);
  c0->SaveAs(BDTDir + Histo + "_" + Channel + "_" + Cut + "_" + CutValName + ".png");

  c0->cd(2)->Clear();

  c0->cd(2);
  TProfile *p2Dcut_C = h2Dcut_C->ProfileY("CutpY",1,-1,"s");
  p2Dcut_C->SetTitle((TString)ho2D_C->GetTitle() + " (" +Cut + ")");
  p2Dcut_C->GetXaxis()->SetTitle((TString)ho2D_C->GetXaxis()->GetTitle());
  p2Dcut_C->GetYaxis()->SetTitle((TString)ho2D_C->GetYaxis()->GetTitle());
  p2Dcut_C->GetYaxis()->SetRangeUser(0,250);
  p2Dcut_C->SetLineColor(kAzure);  
  p2Dcut_C->Draw();

  TLine *Diag;
  Diag = new TLine(0,0,250,250);
  Diag->SetLineWidth(1);
  Diag->SetLineStyle(2);
  Diag->SetLineColor(kViolet); 
  Diag->Draw();
  
  c0->SaveAs(BDTDir + "p_" + Histo + "_" + Channel + "_" + Cut + "_" + CutValName + ".png");

  
  
}// Function




void BDTEfficienciesPerChannel(TString h_name){

  CreateBDTEfficiencyCurve("2j2b",    "all" ,h_name);
  CreateBDTEfficiencyCurve("3j2b",    "all" ,h_name);
  CreateBDTEfficiencyCurve("3j3b",    "all" ,h_name);
  CreateBDTEfficiencyCurve("4j2b",    "all" ,h_name);
  CreateBDTEfficiencyCurve("4jge3b",  "all" ,h_name);
  CreateBDTEfficiencyCurve("ge5",     "all" ,h_name);

}

void BDTEfficiencies(){

  // BDTEfficienciesPerChannel("h_bJet_pT");
  // BDTEfficienciesPerChannel("h_bJet_phi");
  // BDTEfficienciesPerChannel("h_bJet_csv");
  // BDTEfficienciesPerChannel("h_LepJet_DPhi");
  // BDTEfficienciesPerChannel("h_LepJet_DR");
  BDTEfficienciesPerChannel("h_LepJet_Mass");

}
