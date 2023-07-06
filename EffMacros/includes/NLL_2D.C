#include "../Plots.h"
#include "PlottingFunctions.C"


void NLL_2D(){

  // Output 
  TString dirfigname_pdf;
  dirfigname_pdf = "../CombineResults/";
  // make a dir if it does not exist!!
  gSystem->mkdir(dirfigname_pdf,       kTRUE);


  /****************
        Style
  ****************/
  setTDRStyle();
  gROOT->SetStyle("Plain");
  gStyle->SetOptFit(1000);
  gStyle->SetOptStat("emruo");
  gStyle->SetOptStat(kFALSE);
  gStyle->SetPadTickY(1);
  gStyle->SetPadTickX(1);
  
  // Plots
  TH2F *h2D_RatioVsXsec, *h2D_RatioVsXsec4, *h2D_Base;
  h2D_RatioVsXsec = new TH2F("h2D_RatioVsXsec", "NLL Distribution; R^{VPS}_{ t#bar{t}b#bar{b} / t#bar{t}jj }; #sigma^{VPS}_{t#bar{t}jj}",
			     200, 0.017, 0.024, 200, 24, 40);
  h2D_RatioVsXsec4 = new TH2F("h2D_RatioVsXsec4", "NLL Distribution; R^{VPS}_{ t#bar{t}b#bar{b} / t#bar{t}jj }; #sigma^{VPS}_{t#bar{t}jj}",
			      200, 0.017, 0.024, 200, 24, 40);
  
  h2D_Base = new TH2F("h2D_Base", "; R^{VPS}_{ t#bar{t}b#bar{b} / t#bar{t}jj }; #sigma^{VPS}_{t#bar{t}jj} [pb]",
		      //317, 0.017, 0.024, 317, 24, 44);
		      //317, 0.014, 0.0245, 317, 24, 44); // sigmas
		      317, 0.014, 0.025, 317, 22, 48); // CL

  TGraph *g2D_RatioVsXsec;

  // Result
  float rRatio[2], rXsec[2];

  // Tree
  float Ratio, Xsec, NLL, qE;

  TChain theTree("limit"); 
  theTree.Add("../CombineResults/higgsCombine2DScan.MultiDimFit.mH0.root");
  //theTree.Add("../CombineResults/higgsCombine2DScan10k.MultiDimFit.mH0.root");

  theTree.SetBranchAddress( "r_VisPhSp",         &Ratio);
  theTree.SetBranchAddress( "xsec_VisPhSp_ttjj", &Xsec );
  theTree.SetBranchAddress( "deltaNLL",          &NLL  );
  theTree.SetBranchAddress( "quantileExpected",  &qE   );


  float iratio[300], ixsec[300];


  // int MaxEvt = 100000;
  int MaxEvt = theTree.GetEntries();

  for (Long64_t ievt=0; ievt<MaxEvt; ievt++) {
    theTree.GetEntry(ievt);  

    // if(NLL > 0.97 && NLL < 1.03){
    //   iratio[ievt] = Ratio;
    //   ixsec [ievt] = Xsec;
    // }
    
    // std::cout << Ratio << "\t" << Xsec << "\t" << NLL << std::endl; 
    // if(2*NLL<4.) // 2 sigma
    if(2*NLL<6.18)  // 95% CL
      h2D_RatioVsXsec4->Fill(Ratio,Xsec,2*NLL);

    //if(2*NLL<1.) // 1 sigma
    if(2*NLL<2.28) // 68% CL
      h2D_RatioVsXsec->Fill(Ratio,Xsec,2*NLL);

    if(qE==-1){
      rRatio[0] = Ratio;
      rXsec[0]  = Xsec;
    } 
    
  }
  
  // Contours
  Double_t contours[3];
  contours[0] = 1.00;
  contours[1] = 0.0001;

  h2D_RatioVsXsec->SetContour(2, contours);
 

  /****************
     Draw Histos
  ****************/ 
  TCanvas *histocanvas;
  histocanvas = new TCanvas("plots", "Plots",1000,500);
  histocanvas->Divide(2,1);
  TPad    *padLog[2];  
  //Plot Pad
  padLog[0] = (TPad*)histocanvas->cd(1);
  padLog[0]->SetPad(0.01, 0.01, 0.45, 0.99);
  padLog[0]->SetTopMargin(0.1);
  padLog[0]->SetRightMargin(0.04);

  padLog[1] = (TPad*)histocanvas->cd(2);
  padLog[1]->SetPad(0.55, 0.01, 0.99, 0.99);
  padLog[1]->SetTopMargin(0.1);
  padLog[1]->SetRightMargin(0.04);
  
  padLog[0]->cd();
  //h2D_RatioVsXsec->Draw("PROF COLZ");
  //h2D_RatioVsXsec->Draw("CONT Z LIST");
  h2D_RatioVsXsec->Draw("CONT0 LIST");
  padLog[0]->Update();        

  TCanvas *contcanvas;
  contcanvas = new TCanvas("Contours", "Contours",500,500);

  TPad    *padCont;  
  //Plot Pad
  padCont = (TPad*)contcanvas->cd();
  padCont->SetPad(0.01, 0.01, 0.99, 0.99);
  padCont->SetTopMargin(0.1);
  padCont->SetRightMargin(0.06);
  padCont->SetLeftMargin(0.15);
  padCont->SetBottomMargin(0.15);

  //-----------------------------------------
  //-----------------------------------------

  padCont->cd();

  // padCont->SetGridx();
  // padCont->SetGridy();
  h2D_Base->GetYaxis()->SetTitleFont(42);
  h2D_Base->GetYaxis()->SetTitleOffset(0.95);
  h2D_Base->GetYaxis()->SetTitleSize(0.055);
  h2D_Base->GetYaxis()->SetLabelFont(42);
  h2D_Base->GetYaxis()->SetLabelSize(0.04);
  h2D_Base->GetYaxis()->SetNdivisions(607); 

  h2D_Base->GetXaxis()->SetNdivisions(509); //(402)
  h2D_Base->GetXaxis()->SetLabelFont(42);
  h2D_Base->GetXaxis()->SetLabelSize(0.04);
  h2D_Base->GetXaxis()->SetTitleFont(42);
  h2D_Base->GetXaxis()->SetTitleSize(0.055);
  h2D_Base->GetXaxis()->SetTitleOffset(1.);

  h2D_Base->Draw();

  //-----------------------------------------
  //-----------------------------------------

  //TEllipse * el = new TEllipse(rRatio[0], rXsec[0]+0.05, 0.00128, 2.99, 0, 360, -0.0031);
  TEllipse * el = new TEllipse(rRatio[0], rXsec[0]+0.19, 0.0019, 4.59, 0, 360, -0.0031);
  el->SetFillColor(0);
  el->SetLineColor(4);
  el->SetLineStyle(1);
  el->SetLineWidth(3);

  //TEllipse * el2 = new TEllipse(rRatio[0]+0.00003, rXsec[0]+0.4, 0.00255, 5.9, 0, 360, -0.0031);
  TEllipse * el2 = new TEllipse(rRatio[0]+0.00003, rXsec[0]+0.65, 0.00315, 7.4, 0, 360, -0.0031);
  el2->SetFillColor(0);
  el2->SetLineColor(2);
  el2->SetLineStyle(2);
  el2->SetLineWidth(3);

  el2->Draw("SAME");
  el->Draw("SAME");


  // Get Contours
  TObjArray *conts = (TObjArray*)gROOT->GetListOfSpecials()->FindObject("contours");
  TList* contLevel = NULL;
  TGraph* curv     = NULL;
  TGraph* gc       = NULL;
  Int_t nGraphs    = 0;
  Int_t TotalConts = 0;
  
  if (conts == NULL){
    printf("*** No Contours Were Extracted!\n");
    TotalConts = 0;
    std::exit(0);
  } 
  else {
    TotalConts = conts->GetSize();
  }
  printf("TotalConts = %d\n", TotalConts);
  for(int i = 0; i < TotalConts; i++){
    contLevel = (TList*)conts->At(i);
    printf("Contour %d has %d Graphs\n", i, contLevel->GetSize());
    nGraphs += contLevel->GetSize();
  }
  nGraphs = 0;
  char val[20];

  Double_t xval0, yval0, zval0;

  for(int i = 0; i < TotalConts; i++){
    contLevel = (TList*)conts->At(i);
    zval0 = contours[i];
    printf("Z-Level Passed in as:  Z = %f\n", zval0);
    
    // Get first graph from list on curves on this level
    curv = (TGraph*)contLevel->First();
    // for(int j = 0; j < contLevel->GetSize(); j++){
    for(int j = 0; j < 1; j++){
      curv->GetPoint(0, xval0, yval0);
      curv->SetLineColor(4);
      nGraphs ++;
      printf("\tGraph: %d  -- %d Elements\n", nGraphs,curv->GetN());
      // Draw clones of the graphs to avoid deletions in case the 1st
      // pad is redrawn.
      gc = (TGraph*)curv->Clone();
      //gc->Draw("C");
      sprintf(val,"%g",zval0);
      curv = (TGraph*)contLevel->After(curv); // Get Next graph
    }
  }



  Double_t contours4[3];
  contours4[0] = 4.00;
  contours4[1] = 0.0001;

  h2D_RatioVsXsec4->SetContour(2, contours4);
  padLog[1]->cd();
  //h2D_RatioVsXsec->Draw("PROF COLZ");
  //h2D_RatioVsXsec->Draw("CONT Z LIST");
  h2D_RatioVsXsec4->Draw("CONT0 LIST");
  padLog[1]->Update();        

  padCont->cd();

  // Get Contours
  TObjArray *conts4 = (TObjArray*)gROOT->GetListOfSpecials()->FindObject("contours");
  TList* contLevel4 = NULL;
  TGraph* curv4     = NULL;
  TGraph* gc4       = NULL;
  Int_t nGraphs4    = 0;
  Int_t TotalConts4 = 0;
  
  if (conts4 == NULL){
    printf("*** No Contours Were Extracted!\n");
    TotalConts4 = 0;
    std::exit(0);
  } 
  else {
    TotalConts4 = conts4->GetSize();
  }
  printf("TotalConts = %d\n", TotalConts4);
  for(int i = 0; i < TotalConts4; i++){
    contLevel4 = (TList*)conts4->At(i);
    printf("Contour %d has %d Graphs\n", i, contLevel4->GetSize());
    nGraphs4 += contLevel4->GetSize();
  }
  nGraphs4 = 0;
  char val4[20];

  Double_t xval40, yval40, zval40;

  for(int i = 0; i < TotalConts4; i++){
    contLevel4 = (TList*)conts4->At(i);
    zval40 = contours4[i];
    printf("Z-Level Passed in as:  Z = %f\n", zval40);
    
    // Get first graph from list on curves on this level
    curv4 = (TGraph*)contLevel4->First();
    //for(int j = 0; j < contLevel4->GetSize(); j++){
    for(int j = 0; j < 1; j++){
      curv4->GetPoint(0, xval40, yval40);
      curv4->SetLineColor(2);
      nGraphs4 ++;
      printf("\tGraph: %d  -- %d Elements\n", nGraphs4,curv4->GetN());
      // Draw clones of the graphs to avoid deletions in case the 1st
      // pad is redrawn.
      gc4 = (TGraph*)curv4->Clone();
      //gc4->Draw("C");
      sprintf(val4,"%g",zval40);
      curv4 = (TGraph*)contLevel4->After(curv4); // Get Next graph
    }
  }

  // TLatex l,l4;
  // l.SetTextSize(0.08);
  // l4.SetTextSize(0.08);
  // l.DrawLatex(0.0205,34.5,"#sigma");
  // l4.DrawLatex(0.021,37.5,"2#sigma");

  TGraph *best_fit = new TGraph(1, rRatio, rXsec);
  best_fit->SetMarkerSize(2); 
  best_fit->SetMarkerStyle(34); 
  best_fit->Draw("p same");

  // Powheg
  float pRatio[1]={0.017},pXsec[1]={30.5};
  float pErrRatio[1]={0.002},pErrXsec[1]={3.};
  TGraphErrors *powheg = new TGraphErrors(1,pRatio,pXsec,pErrRatio,pErrXsec);
  powheg->SetMarkerSize(2); 
  powheg->SetMarkerStyle(20); 
  powheg->Draw("pe same");



  /***********************
           Legends
  ***********************/
  TLegend *leg;
  //leg = new TLegend(0.55,0.70,0.93,0.89);
  leg = new TLegend(0.45,0.70,0.93,0.89);
  leg->SetFillColor(0);
  leg->SetLineColor(0);
  leg->SetLineWidth(0.0);
  leg->SetTextFont(42);
  leg->SetTextSize(0.035);
  //leg->AddEntry((TObject*)0,"","");
  leg->AddEntry(best_fit, "Best fit","P");
  leg->AddEntry(el, " 68% CL contour","L");
  leg->AddEntry(el2," 95% CL contour","L");
  // leg->AddEntry(el, " 1#sigma error ellipse","L");
  // leg->AddEntry(el2," 2#sigma error ellipse","L");
  leg->AddEntry(powheg," POWHEG + PYTHIA8","PEL");

  leg->Draw("SAME");
    
  //-------------------------------------------------------
  // CMS Legend
  //-------------------------------------------------------
      TLatex *titlePr;      
      titlePr  = new TLatex(-20.,50.,"Preliminary");
      titlePr->SetNDC();
      titlePr->SetTextAlign(12);
      titlePr->SetX(0.15);
      titlePr->SetY(0.93);
      titlePr->SetTextFont(52);
      titlePr->SetTextSize(0.05);
      titlePr->SetTextSizePixels(24);
      //titlePr->Draw("SAME");
      
      TLatex *titleCMS;
      titleCMS  = new TLatex(-20.,50.,"CMS");
      titleCMS->SetNDC();
      titleCMS->SetTextAlign(12);
      // titleCMS->SetX(0.18);
      // titleCMS->SetY(0.84);
      titleCMS->SetX(0.15);
      titleCMS->SetY(0.93);
      titleCMS->SetTextFont(61);
      titleCMS->SetTextSize(0.05);
      titleCMS->SetTextSizePixels(24);
      titleCMS->Draw("SAME");

      TLatex *title;
      title  = new TLatex(-20.,50.,"35.9 fb^{-1} (13 TeV)");
      title->SetNDC();
      title->SetTextAlign(12);
      title->SetX(0.70);
      title->SetY(0.923);
      title->SetTextFont(42);
      title->SetTextSize(0.035);
      title->SetTextSizePixels(24);
      title->Draw("SAME");

      TLatex *chtitle;
      chtitle  = new TLatex(-20.,50.,"Lepton+jets");
      chtitle->SetNDC();
      chtitle->SetTextAlign(12);
      chtitle->SetX(0.19);
      chtitle->SetY(0.8);
      chtitle->SetTextFont(42);
      chtitle->SetTextSize(0.04);
      chtitle->SetTextSizePixels(24);
      chtitle->Draw("SAME");

      TLatex *phtitle;
      phtitle  = new TLatex(-20.,50.,"VPS");
      phtitle->SetNDC();
      phtitle->SetTextAlign(12);
      phtitle->SetX(0.19);
      phtitle->SetY(0.75);
      phtitle->SetTextFont(42);
      phtitle->SetTextSize(0.04);
      phtitle->SetTextSizePixels(24);
      phtitle->Draw("SAME");



  histocanvas->SaveAs(dirfigname_pdf + "h2D_RatioVsXsec.pdf");         
  contcanvas->SaveAs(dirfigname_pdf + "cont_RatioVsXsec.pdf");        
       

} //end Plots.C
