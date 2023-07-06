// Ratio Max and Min 
void RatioGetMaxMin(TH1D *his,float &val){

  float maxr = 0;
  float minr = 99;

  for(int ibin=1;ibin<=his->GetNbinsX();ibin++) {
    double cbin = his->GetBinContent(ibin);
    if (cbin > maxr && cbin < 2.0) maxr = cbin; 
    if (cbin < minr && cbin > 0.5) minr = cbin; 
  }

  minr = 2.0-(minr);
  minr = ceil(minr*100.);

  maxr = ceil(maxr*100.);

  val = std::max (maxr,minr);
  val = val/100.;
}

// Ratio Creator
TH1D *HistoRatio (TH1D *hisNum, TH1D *hisDen, TString xtitle=""){
  
  //Graph Ratio Clone
  TH1D *Ratio;
  Ratio = (TH1D*)hisNum->Clone("Ratio" + (TString)hisNum->GetName());
  Ratio->Divide(hisDen);

  for(int ibin=1;ibin<=Ratio->GetNbinsX();ibin++) {
    if (Ratio->GetBinContent(ibin) == 0.0 ) {
      Ratio->SetBinContent(ibin, 1.0);
      Ratio->SetBinError(ibin, 0.0);
    }
  }

  Ratio->SetFillColor(0);
  Ratio->SetLineWidth(1);
  Ratio->SetTitle("");

  Ratio->GetYaxis()->SetTitle("Data/MC");
  Ratio->GetYaxis()->CenterTitle();
  Ratio->GetYaxis()->SetTitleOffset(0.45);
  Ratio->GetYaxis()->SetTitleSize(0.09);
  Ratio->GetYaxis()->SetLabelSize(0.10);
  Ratio->GetYaxis()->SetNdivisions(402);
  //Ratio->GetXaxis()->SetTitleFont(41);
  Ratio->GetXaxis()->SetTitle(xtitle);
  Ratio->GetXaxis()->SetNdivisions(509); //(402)
  Ratio->GetXaxis()->SetTitleOffset(1.1);
  Ratio->GetXaxis()->SetLabelSize(0.10);
  Ratio->GetXaxis()->SetTitleSize(0.16);

  return Ratio;

}

// Ratio Max and Min

void FractionGetMaxMin(TH1D *his,float &valmax,float &valmin){

  float maxf = 0., minf = 100.;

  double avr = 0.0;
  for(int ibin=1;ibin<=his->GetNbinsX();ibin++) {
    double cbin = his->GetBinContent(ibin);
    avr += cbin;
    if (cbin > maxf) maxf = cbin;    
    if (cbin < minf) minf = cbin;    
  }
  avr = avr/(1.0*his->GetNbinsX());

  valmax = ceil( (avr + maxf)/2.0 );
  valmin = floor( minf );
}



// Fraction creator
TH1D *HistoFraction (TH1D *hisNom, TH1D *hisVar, TString Units = ""){

  //Graph Fraction
  TH1D *Fraction  = (TH1D*)hisNom->Clone("Fraction" + (TString)hisVar->GetName());
  Fraction->Reset();

  for(int ibin=1;ibin<=Fraction->GetNbinsX();ibin++) {

    double newbin = 0.0 ;
    double maxbin = 0.0 ;
    double nombin = hisNom->GetBinContent(ibin);
    double varbin = hisVar->GetBinContent(ibin);

    if (nombin != 0.0){
      newbin = std::abs((varbin - nombin)/nombin);
    }

    Fraction->SetBinContent(ibin, 100.*newbin); 
    Fraction->SetBinError(ibin, 0.0); 
  }

  Fraction->SetFillColor(0);
  Fraction->SetLineWidth(1);
  Fraction->SetTitle("");

  Fraction->GetYaxis()->SetTitle("Var[%]");
  Fraction->GetYaxis()->CenterTitle();
  Fraction->GetYaxis()->SetTitleOffset(0.40);
  Fraction->GetYaxis()->SetTitleSize(0.09);
  Fraction->GetYaxis()->SetLabelSize(0.10);
  Fraction->GetYaxis()->SetNdivisions(402);
  if(Units != "") Fraction->GetXaxis()->SetTitle(Units);
  Fraction->GetXaxis()->SetNdivisions(509); //(402)
  Fraction->GetXaxis()->SetTitleOffset(1.1);
  Fraction->GetXaxis()->SetLabelSize(0.10);
  Fraction->GetXaxis()->SetTitleSize(0.16);

  return Fraction;

}

// Fraction creator
std::vector<TH1D*> HistoRealFraction (TH1D *hisNom, TH1D *hisVarUp, TH1D *hisVarDw, TString Units = ""){

  //Graph Fraction
  TH1D *FractionVar[2];
  FractionVar[0] = (TH1D*)hisNom->Clone((TString)hisVarUp->GetName());
  FractionVar[0]->SetFillColor(0);
  FractionVar[0]->SetLineWidth(1);
  FractionVar[0]->SetTitle("");
  FractionVar[0]->GetYaxis()->SetTitle("Var[%]");
  FractionVar[0]->GetYaxis()->CenterTitle();
  FractionVar[0]->GetYaxis()->SetTitleOffset(0.40);
  FractionVar[0]->GetYaxis()->SetTitleSize(0.09);
  FractionVar[0]->GetYaxis()->SetLabelSize(0.10);
  FractionVar[0]->GetYaxis()->SetNdivisions(402);
  if(Units != "") FractionVar[0]->GetXaxis()->SetTitle(Units);
  FractionVar[0]->GetXaxis()->SetNdivisions(509); //(402)
  FractionVar[0]->GetXaxis()->SetTitleOffset(1.1);
  FractionVar[0]->GetXaxis()->SetLabelSize(0.10);
  FractionVar[0]->GetXaxis()->SetTitleSize(0.16);

  FractionVar[1] = (TH1D*)FractionVar[0]->Clone((TString)hisVarDw->GetName());
  
  FractionVar[0]->Reset();
  FractionVar[1]->Reset();

  for(int ibin=1;ibin<=FractionVar[0]->GetNbinsX();ibin++) {

    double vCe = hisNom  ->GetBinContent(ibin);
    double vUp = hisVarUp->GetBinContent(ibin);
    double vDw = hisVarDw->GetBinContent(ibin);
    
    double eDw = (vCe-vDw);
    double eUp = (vUp-vCe);
    
    if(vCe != 0.) { eDw = 100.*eDw/vCe; eUp = 100.*eUp/vCe; }
    else { eDw = 0.; eUp = 0.; }
    
    FractionVar[0]->SetBinContent(ibin,eUp);
    FractionVar[1]->SetBinContent(ibin,eDw);
        
    FractionVar[0]->SetBinError(ibin, 0.0); 
    FractionVar[1]->SetBinError(ibin, 0.0); 

  }

  std::vector<TH1D*> vFraction;
  vFraction.push_back(FractionVar[0]);
  vFraction.push_back(FractionVar[1]);
  return vFraction;

}



void SetUpTitles(TLatex *titlePr,
		 TLatex *title,
		 TLatex *chtitle,
		 int     year=2016){
  // Preliminary
  titlePr->SetTitle("Preliminary");
  titlePr->SetNDC();
  titlePr->SetTextAlign(12);
  titlePr->SetX(0.24);
  titlePr->SetY(0.93);
  // titlePr->SetTextColor(2);
  titlePr->SetTextFont(42);
  titlePr->SetTextSize(0.05);
  titlePr->SetTextSizePixels(24);

  // CMS Energy
  if(year == 2016)   title->SetTitle("2016, 36.5 fb^{-1} (13 TeV)");
  if(year == 2017)   title->SetTitle("2017, 41.5 fb^{-1} (13 TeV)");
  if(year == 2018)   title->SetTitle("2018, 59.7 fb^{-1} (13 TeV)");
  if(year == 201678) title->SetTitle("Run II, 138 fb^{-1} (13 TeV)");
  title->SetNDC();
  title->SetTextAlign(12);
  title->SetX(0.67);
  title->SetY(0.93);
  title->SetTextFont(42);
  title->SetTextSize(0.04);
  title->SetTextSizePixels(24);

  // Channel Title
  chtitle->SetNDC();
  chtitle->SetTextAlign(12);
  chtitle->SetX(0.2);
  chtitle->SetY(0.8);
  chtitle->SetTextFont(42);
  chtitle->SetTextSize(0.06);
  chtitle->SetTextSizePixels(24);

}

void SetUpFractionTitles(TLatex *titlePr,
			 TLatex *title,
			 TLatex *chtitle){
  // Preliminary
  titlePr->SetTextSize(0.05);
  titlePr->SetTextSizePixels(24);

  // CMS Energy
  title->SetTextSize(0.05);
  title->SetTextSizePixels(24);

  // Title
  chtitle->SetTextSize(0.05);
  chtitle->SetTextSizePixels(24);

}
