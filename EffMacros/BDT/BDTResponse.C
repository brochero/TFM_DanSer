//const TString HistoName = "Jet_BDT";
const TString HistoName = "LepJet_Mass";

TString callTH1 (TString ch, TString cut){
  return "central/" + ch + "/" + cut + "/h_" + HistoName + "_" + ch + "_" + cut + "_central";
}


void CreateBDT(TString Cut      = "4j2b",
	       TString Channel  = "all"){
  

  gStyle->SetOptStat("emruo");
  gStyle->SetOptStat(kFALSE);
  
  float MarkerSize = 0.7;
  int LineStyle  = 2;
  
  //TString Ref = "TrFullStataMCatNLORegFrom2_WithDR-v6";
  //TString inputfile = "../HistoResult/"+Ref+"/"+Ref+"_BDTValidation_SmallFNano2016-v7_TTToSemiLeptonic_TuneCP5_PSweights_13TeV-powheg-pythia8.root";

  TString Ref = "ValGenJetNovNoBDTCut-v0";
  TString inputfile = "../../HistoResult/"+Ref+"/"+Ref+"_BDTValidation_GenJetsFNano2017-v7_TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8.root";

  // Range
  float XaxisRange_o = -0.2, XaxisRange_f = 0.6;

  if(HistoName == "LepJet_Mass")
   XaxisRange_o = 0.0, XaxisRange_f = 250;
  
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
  Long64_t n_CTot = h_C->Integral(h_C->FindBin(XaxisRange_o),h_C->FindBin(XaxisRange_f));   
  Long64_t n_WTot = h_W->Integral(h_C->FindBin(XaxisRange_o),h_C->FindBin(XaxisRange_f));   
  Long64_t n_ITot = h_I->Integral(h_C->FindBin(XaxisRange_o),h_C->FindBin(XaxisRange_f));   

  Long64_t n_Tot = n_CTot + n_WTot + n_ITot;

  // Set Colors
  h_C->Scale(100./n_Tot);
  h_C->SetLineColor(1);
  h_C->SetFillColor(kGreen+1);
  h_C->SetLineWidth(1);
  // h_C->SetFillStyle(3001);

  h_W->Scale(100./n_Tot);
  h_W->SetLineColor(1);
  h_W->SetFillColor(kRed);
  h_W->SetLineWidth(1);
  // h_W->SetFillStyle(3001);

  h_I->Scale(100./n_Tot);
  h_I->SetLineColor(1);
  h_I->SetFillColor(kBlue);
  h_I->SetLineWidth(1);
  // h_I->SetFillStyle(3001);

  // Stack
  THStack *AllComb = new THStack ("AllComb", "");  
  AllComb->SetHistogram(h_C);
  AllComb->Add(h_I);
  AllComb->Add(h_W);
  AllComb->Add(h_C);

    
  TCanvas *c0;
  c0 = new TCanvas("Efficiency");
  c0->Divide(2,1);
  c0->cd(1);

  TH1 *h_Style = (TH1*)h_C->Clone();  
  if(HistoName == "Jet_BDT"){
    h_Style->SetTitle("BDT response for " + Cut);
    h_Style->GetXaxis()->SetTitle("BDT response");
  }
  if(HistoName == "LepJet_Mass"){
    h_Style->SetTitle("Invariant mass for " + Cut);
    h_Style->GetXaxis()->SetTitle("M(l,j)[GeV]");
  }
  h_Style->GetYaxis()->SetTitle("");

  TH1D *hl_C = (TH1D*)h_C->Clone("Line");  
  if(hl_C->Integral()!=0.0) hl_C->Scale(1./hl_C->Integral());
  hl_C->SetLineColor(kGreen+1);
  hl_C->SetFillColor(0);
  hl_C->SetLineWidth(1);
  // h_C->SetFillStyle(3001);

  TH1D *hl_W = (TH1D*)h_W->Clone("Line");  
  if(hl_W->Integral()!=0.0) hl_W->Scale(1./hl_W->Integral());
  hl_W->SetLineColor(kRed);
  hl_W->SetFillColor(0);
  hl_W->SetLineWidth(1);
  // h_W->SetFillStyle(3001);

  TH1D *hl_I = (TH1D*)h_I->Clone("Line");  
  if(hl_I->Integral()!=0.0) hl_I->Scale(1./hl_I->Integral());
  hl_I->SetLineColor(kBlue);
  hl_I->SetFillColor(0);
  hl_I->SetLineWidth(1);
  
  h_Style->GetYaxis()->SetTitleOffset(0.6);
  h_Style->GetXaxis()->SetRangeUser(XaxisRange_o,XaxisRange_f);
  double MaxY = std::max(hl_C->GetMaximum(),hl_W->GetMaximum());
  MaxY = std::max(MaxY,hl_I->GetMaximum());
  h_Style->SetMaximum(1.4*MaxY);
  h_Style->Reset();
  h_Style->Draw();

  hl_C->Draw("HISTSAME");
  hl_W->Draw("HISTSAME");
  hl_I->Draw("HISTSAME");
  
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
  leg1 = new TLegend(0.55,0.65,0.9,0.9);
  leg1->SetLineColor(1);
  leg1->SetTextSize(0.032);

  leg1->AddEntry((TObject*)0,"lep,jet assignment","");
  leg1->AddEntry((TObject*)0,Cut,"");
  leg1->AddEntry(hl_C, "Correct",     "L");
  leg1->AddEntry(hl_W, "Wrong",       "L");
  leg1->AddEntry(hl_I, "w/o solution","L");

  leg1->Draw();
  
  // ---------------------------------------------------

  c0->cd(2);
  TH1D *h_Style2 = (TH1D*)h_Style->Clone("Style2");
  h_Style2->SetMaximum(1.4*AllComb->GetMaximum());
  h_Style2->GetYaxis()->SetTitle("Fraction [\%]");
  h_Style2->GetYaxis()->SetTitleOffset(1.5);

  h_Style2->Draw();
  
  AllComb->Draw("HISTSAME");
  
  titleCh->Draw();

  TLegend *leg2;
  leg2 = new TLegend(0.55,0.65,0.90,0.90);
  leg2->SetLineColor(1);
  leg2->SetTextSize(0.032);

  leg2->AddEntry((TObject*)0,"lep,jet assignment","");
  leg2->AddEntry((TObject*)0,Cut,"");
  leg2->AddEntry(h_C, (TString)Form("Correct %.0f",(100.*n_CTot/n_Tot))+"\%",     "F");
  leg2->AddEntry(h_W, (TString)Form("Wrong %.0f",(100.*n_WTot/n_Tot))+"\%",       "F");
  leg2->AddEntry(h_I, (TString)Form("w/o solution %.0f",(100.*n_ITot/n_Tot))+"\%","F");

  leg2->Draw();

  
  TString BDTDir = "../../Figures/BDTPlots-" + Ref + "/EffFractions/";
  gSystem->mkdir(BDTDir,kTRUE);
  c0->SaveAs(BDTDir + HistoName + "_" + Channel + "_" + Cut +".png");
}// Function




void BDTResponse(){

  CreateBDT("2j2b",  "all");
  CreateBDT("3j2b",  "all");
  CreateBDT("4j2b",  "all");
  CreateBDT("4jge3b","all");
  CreateBDT("ge5",   "all");

  CreateBDT("2j2b",  "mujets");
  CreateBDT("3j2b",  "mujets");
  CreateBDT("4j2b",  "mujets");
  CreateBDT("4jge3b","mujets");
  CreateBDT("ge5",   "mujets");
  
  CreateBDT("2j2b",  "ejets");
  CreateBDT("3j2b",  "ejets");
  CreateBDT("4j2b",  "ejets");
  CreateBDT("4jge3b","ejets");
  CreateBDT("ge5",   "ejets");

}
