
TH1D *HistoModifier(TH1D *Input, TString region="all");
void GetStatVar    (TH1D *Nom, TH1D *StatDown, TH1D *StatUp, TString SamName);
TH1D *ReadRegionHisto(TFile *InpFile, TString InpHis, TString InpCh, TString InpReg, TString InpVar, bool ForQCDDD=false);

TH1D *SymmetricSystematicCreator(TH1D*Nom, TH1D *Var);

void ExtrapolateSymmetricSystematicCreator(TH1D *Nom, TH1D *Up, TH1D *Dw);
void BinnedSymmetricSystematicCreator(TH1D *Nom, TH1D *Up, TH1D *Dw);

void ExtrapolateSystematicCreator(TH1D *NomNew, TH1D *NomOr, TH1D *SysVar);

void SmoothEmptyBins(TH1D*Nom, TString SampleName = "");


TH1D *ReadRegionHisto(TFile *InpFile, TString InpHis, TString InpCh, TString InpReg, TString InpVar, bool ForQCDDD){

  TString HistoName;
  TString BaseHName;
  
  TH1D *histo;
  bool fh = true;
  
  TString tokReg;
  Ssiz_t from = 0;

  if (ForQCDDD){
    HistoName = InpHis + "_" + InpCh + "_" + InpReg + "_" + InpVar;
    BaseHName = InpVar + "/" + InpCh + "/" + InpReg + "/" + HistoName;
    histo = (TH1D*)(InpFile->Get(BaseHName))->Clone(InpHis + "_" + InpCh + "_" + InpReg + "_" + InpVar);
  }

  else{
    while (InpReg.Tokenize(tokReg,from,"plus")) {
    
      HistoName = InpHis + "_" + InpCh + "_" + tokReg + "_" + InpVar;
      BaseHName = InpVar + "/" + InpCh + "/" + tokReg + "/" + HistoName;
      TH1D *histofile= (TH1D*)(InpFile->Get(BaseHName))->Clone(InpHis + "_" + InpCh + "_" + InpReg + "_" + InpVar);

      if (fh) { histo = histofile; fh = false; }
      else    { histo->Add(histofile); }    

    } // while
  }// Not QCDDD

  return histo;
}




void GetStatVar(TH1D *Nom, TH1D *StatDown, TH1D *StatUp, TString StatSysName){

  StatUp  ->SetName((TString)StatUp  ->GetName() + "_" + StatSysName + "StatUp");
  StatDown->SetName((TString)StatDown->GetName() + "_" + StatSysName + "StatDown");

  for(int nb=1; nb<=StatUp->GetNbinsX(); nb++){
    double bcStatUp   = StatUp  ->GetBinContent(nb) + StatUp->GetBinError(nb);
    double bcStatDown = StatDown->GetBinContent(nb) - StatDown->GetBinError(nb);

    StatUp  ->SetBinContent(nb,bcStatUp);
    StatDown->SetBinContent(nb,bcStatDown);
  }

}

TH1D *HistoModifier(TH1D *Input, TString region){

  float EntriesPerEvt;
  if(Input->Integral()!= 0.0) EntriesPerEvt = Input->GetEntries()/Input->Integral();
  else EntriesPerEvt=1.;

  Double_t binX[51];
  for (unsigned int ibin=1; ibin <= Input->GetNbinsX(); ibin ++){
    binX[ibin-1] = Input->GetBinLowEdge(ibin);
  }
  binX[50] = Input->GetBinLowEdge(51);

  // -- All bins
  int nbins = 50;
  Double_t newbin[] = {binX[0],
                       binX[1], binX[2], binX[3], binX[4], binX[5], binX[6], binX[7], binX[8], binX[9],           // 10
                       binX[10],binX[11],binX[12],binX[13],binX[14],binX[15],binX[16],binX[17],binX[18],binX[19], // 10
                       binX[20],binX[21],binX[22],binX[23],binX[24],binX[25],binX[26],binX[27],binX[28],binX[29], // 10
                       binX[30],binX[31],binX[32],binX[33],binX[34],binX[35],binX[36],binX[37],binX[38],binX[39], // 10
                       binX[40],binX[41],binX[42],binX[43],binX[44],binX[45],binX[46],binX[47],binX[48],binX[49], // 10
                       binX[50]};
  
  // Create Mass Range
  /* float Lower = 50, Upper=150; */
  /* for (unsigned int ibin=1; ibin <= Input->GetNbinsX(); ibin ++){ */
  /*   float ilow = Input->GetBinLowEdge(ibin); */
  /*   if (ilow <  Lower) {Input->SetBinContent(ibin,0.);  Input->SetBinError(ibin,0.);} */
  /*   if (ilow >= Upper) {Input->SetBinContent(ibin,0.);  Input->SetBinError(ibin,0.);} */
  /* } */
  
  // -- 1 bin
  int nbins1 = 1;
  Double_t newbin1[] = {binX[0],  // 0
			binX[50]  // 250
  };

  // -- 4 bins
  int nbins4 = 4;
  Double_t newbin4[] = {binX[0],  // 0
			binX[10], // 50
			binX[20], // 100
			binX[33], // 160
			binX[50]  // 250
  };

  // -- 5 bins
  int nbins5 = 5;
  Double_t newbin5[] = {binX[0],  // 0
			binX[10], // 50
			binX[20], // 100
			binX[25], // 125
			binX[30], // 150
			binX[50]  // 250
  };

    // -- 8 bins
  int nbins8 = 8;
  Double_t newbin8[] = {binX[0],  // 0
			binX[10], // 50
			binX[14], // 70
			binX[17], // 85
			binX[20], // 100
			binX[23], // 115
			binX[26], // 130
			binX[30], // 150
			binX[50]  // 250
  };

  // -- 12 bins
  int nbins12 = 12;
  Double_t newbin12[] = {binX[0],  // 0
			 binX[10], // 50
			 binX[12], // 60
			 binX[14], // 70
			 binX[16], // 80
			 binX[18], // 90
			 binX[20], // 100
			 binX[22], // 110
			 binX[24], // 120
			 binX[26], // 130
			 binX[28], // 140
			 binX[30], // 150
			 // binX[32], // 160
			 binX[50]  // 250
  };

  // -- 20 bins
  int nbins20 = 20;
  Double_t newbin20[] = {binX[0],  // 0
			 binX[10], // 50
			 binX[11], // 55
			 binX[12], // 60
			 binX[13], // 65
			 binX[14], // 70
			 binX[15], // 75
			 binX[16], // 80
			 binX[17], // 85
			 binX[18], // 90
			 binX[19], // 85
			 binX[20], // 100
			 binX[21], // 105
			 binX[22], // 110
			 binX[23], // 115
			 binX[24], // 120
			 binX[25], // 125
			 binX[26], // 130
			 binX[27], // 135
			 binX[30], // 150
			 binX[50]  // 250
  };

  // -- 21 bins
  int nbins21 = 21;
  Double_t newbin21[] = {binX[0],  // 0
			 binX[10], // 50
			 binX[11], // 55
			 binX[12], // 60
			 binX[13], // 65
			 binX[14], // 70
			 binX[15], // 75
			 binX[16], // 80
			 binX[17], // 85
			 binX[18], // 90
			 binX[19], // 85
			 binX[20], // 100
			 binX[21], // 105
			 binX[22], // 110
			 binX[23], // 115
			 binX[24], // 120
			 binX[25], // 125
			 binX[26], // 130
			 binX[27], // 135
			 binX[28], // 140
			 binX[29], // 145
			 binX[50]  // 250
  };
  
  // -- 24 bins
  int nbins24 = 24;
  Double_t newbin24[] = {binX[0],  // 0
			 /* binX[5],  // 25 */
			 binX[7],  // 35
			 binX[8],  // 40
			 binX[9],  // 45
			 binX[10], // 50
			 binX[11], // 55
			 binX[12], // 60
			 binX[13], // 65
			 binX[14], // 70
			 binX[15], // 75
			 binX[16], // 80
			 binX[17], // 85
			 binX[18], // 90
			 binX[19], // 85
			 binX[20], // 100
			 binX[21], // 105
			 binX[22], // 110
			 binX[23], // 115
			 binX[24], // 120
			 binX[25], // 125
			 binX[26], // 130
			 binX[27], // 135
			 binX[28], // 140
			 binX[29], // 145
			 /* binX[30], // 150 */
			 /* binX[32], // 160 */
			 /* binX[36], // 180 */
			 /* binX[40], // 200 */
			 binX[50]  // 250
  };

  // -- 26 bins
  int nbins26 = 26;
  Double_t newbin26[] = {binX[0],  // 0
			 binX[7],  // 35
			 binX[8],  // 40
			 binX[9],  // 45
			 binX[10], // 50
			 binX[11], // 55
			 binX[12], // 60
			 binX[13], // 65
			 binX[14], // 70
			 binX[15], // 75
			 binX[16], // 80
			 binX[17], // 85
			 binX[18], // 90
			 binX[19], // 85
			 binX[20], // 100
			 binX[21], // 105
			 binX[22], // 110
			 binX[23], // 115
			 binX[24], // 120
			 binX[25], // 125
			 binX[26], // 130
			 binX[27], // 135
			 binX[28], // 140
			 binX[29], // 145
			 /* binX[30], // 150 */
			 binX[32], // 160
			 binX[35], // 175
			 /* binX[36], // 180 */
			 /* binX[40], // 200 */
			 binX[50]  // 250
  };

  // -- 29 bins
  int nbins29 = 29;
  Double_t newbin29[] = {binX[0],  // 0
			 binX[5],  // 25
			 binX[7],  // 35
			 binX[8],  // 40
			 binX[9],  // 45
			 binX[10], // 50
			 binX[11], // 55
			 binX[12], // 60
			 binX[13], // 65
			 binX[14], // 70
			 binX[15], // 75
			 binX[16], // 80
			 binX[17], // 85
			 binX[18], // 90
			 binX[19], // 85
			 binX[20], // 100
			 binX[21], // 105
			 binX[22], // 110
			 binX[23], // 115
			 binX[24], // 120
			 binX[25], // 125
			 binX[26], // 130
			 binX[27], // 135
			 binX[28], // 140
			 binX[29], // 145
			 binX[30], // 150
			 binX[32], // 160
			 binX[36], // 180
			 binX[40], // 200
			 binX[50]  // 250
  };

  // --  bins
  int nbins29B = 29;
  Double_t newbin29B[] = {binX[0],  // 0
			  binX[7],  // 35
			  binX[8],  // 40
			  binX[9],  // 45
			  binX[10], // 50
			  binX[11], // 55
			  binX[12], // 60
			  binX[13], // 65
			  binX[14], // 70
			  binX[15], // 75
			  binX[16], // 80
			  binX[17], // 85
			  binX[18], // 90
			  binX[19], // 85
			  binX[20], // 100
			  binX[21], // 105
			  binX[22], // 110
			  binX[23], // 115
			  binX[24], // 120
			  binX[25], // 125
			  binX[26], // 130
			  binX[27], // 135
			  binX[28], // 140
			  binX[29], // 145
			  binX[30], // 150
			  binX[31], // 155
			  binX[33], // 165
			  binX[36], // 180
			  binX[40], // 200
			  binX[50]  // 250
  };
  
 

  TH1D *HistoNewBin;
  /* if      (region == "3j2b" || region == "4j2b" || region == "ge5ge2b" || region == "ge5" || region == "3j2bplus3j3b" || region == "4j2bplus4jge3b") */
  /*   HistoNewBin = (TH1D*) Input->Rebin(nbins20,"Fixed_"+(TString)Input->GetName(),newbin20); */
  if      (region == "4j2b" || region == "ge5ge2b")
    HistoNewBin = (TH1D*) Input->Rebin(nbins20,"Fixed_"+(TString)Input->GetName(),newbin20);
  else if (region == "3j2b" || region == "2j2b")
    HistoNewBin = (TH1D*) Input->Rebin(nbins1,"Fixed_"+(TString)Input->GetName(),newbin1);
  else if (region == "3j3b" || region == "4jge3b" )
    HistoNewBin = (TH1D*) Input->Rebin(nbins5,"Fixed_"+(TString)Input->GetName(),newbin5);
  else if (region == "3j3bplus4jge3b" )
    HistoNewBin = (TH1D*) Input->Rebin(nbins8,"Fixed_"+(TString)Input->GetName(),newbin8);
  else{
    HistoNewBin = (TH1D*) Input->Rebin(nbins12,"Fixed_"+(TString)Input->GetName(),newbin12);
  }
  
  return HistoNewBin;

}

TH2D *HistoModifier2D(TH2D *Input, TString region){

  // Only x-axis because it is symmetric for y-axis
  int nbinX=Input->GetNbinsX();
  // Dummy histograms to locate each of the bins
  TH1D *DumX = Input->ProjectionX();
  TH1D *DumY = Input->ProjectionY();
  
  Double_t binX[51];
  for (unsigned int ibin=1; ibin <= DumX->GetNbinsX(); ibin ++){
    binX[ibin-1] = DumX->GetBinLowEdge(ibin);
  }
  binX[50] = DumX->GetBinLowEdge(51);

  // -- All bins
  int nbins = 50;
  Double_t newbin[] = {binX[0],
                       binX[1], binX[2], binX[3], binX[4], binX[5], binX[6], binX[7], binX[8], binX[9],           // 10
                       binX[10],binX[11],binX[12],binX[13],binX[14],binX[15],binX[16],binX[17],binX[18],binX[19], // 10
                       binX[20],binX[21],binX[22],binX[23],binX[24],binX[25],binX[26],binX[27],binX[28],binX[29], // 10
                       binX[30],binX[31],binX[32],binX[33],binX[34],binX[35],binX[36],binX[37],binX[38],binX[39], // 10
                       binX[40],binX[41],binX[42],binX[43],binX[44],binX[45],binX[46],binX[47],binX[48],binX[49], // 10
                       binX[50]};
  
  // Read all the bin content
  std::vector< std::vector<double> > binVal;
  for (unsigned int ixbin=1; ixbin <= DumX->GetNbinsX(); ixbin ++){
    std::vector<double> binYVal;
    for (unsigned int iybin=1; iybin <= DumY->GetNbinsX(); iybin ++){
      binYVal.push_back( Input->GetBinContent(ixbin,iybin) );
    }
    binVal.push_back( binYVal );
  }  

  // ----------------------------------------------------------------------------
  // ----------------------------------------------------------------------------
  // WARNING: Until I find another way, this definitions must be the same than
  //          the ones at HistoModifier
  // ----------------------------------------------------------------------------
  // ----------------------------------------------------------------------------
  
  // -- 1 bins
  int nbins1 = 1;
  Double_t newbin1[] = {binX[0],  // 0
			binX[50]  // 250
  };

  // -- 5 bins
  int nbins5 = 5;
  Double_t newbin5[] = {binX[0],  // 0
			binX[10], // 50
			binX[20], // 100
			binX[25], // 125
			binX[30], // 150
			binX[50]  // 250
  };

    // -- 8 bins
  int nbins8 = 8;
  Double_t newbin8[] = {binX[0],  // 0
			binX[10], // 50
			binX[14], // 70
			binX[17], // 85
			binX[20], // 100
			binX[23], // 115
			binX[26], // 130
			binX[30], // 150
			binX[50]  // 250
  };

  // -- 12 bins
  int nbins12 = 12;
  Double_t newbin12[] = {binX[0],  // 0
			 binX[10], // 50
			 binX[12], // 60
			 binX[14], // 70
			 binX[16], // 80
			 binX[18], // 90
			 binX[20], // 100
			 binX[22], // 110
			 binX[24], // 120
			 binX[26], // 130
			 binX[28], // 140
			 binX[30], // 150
			 binX[50]  // 250
  };

  // -- 20 bins
  int nbins20 = 20;
  Double_t newbin20[] = {binX[0],  // 0
			 binX[10], // 50
			 binX[11], // 55
			 binX[12], // 60
			 binX[13], // 65
			 binX[14], // 70
			 binX[15], // 75
			 binX[16], // 80
			 binX[17], // 85
			 binX[18], // 90
			 binX[19], // 85
			 binX[20], // 100
			 binX[21], // 105
			 binX[22], // 110
			 binX[23], // 115
			 binX[24], // 120
			 binX[25], // 125
			 binX[26], // 130
			 binX[27], // 135
			 binX[30], // 150
			 binX[50]  // 250
  };

  
  // Creates a new TH2D  
  TH2D *Histo2DNewBin;
  TH1D *HistoNewBin; 

  if (region == "4j2b" || region == "ge5ge2b" || region == "ge5" ||
      region == "3j2bplus3j3b" || region == "4j2bplus4jge3b"){
    Histo2DNewBin = new TH2D("Fixed_"+(TString)Input->GetName(), Input->GetTitle(), nbins20, newbin20, nbins20, newbin20);
    HistoNewBin   = (TH1D*) DumX->Rebin(nbins20,"Fixed_"+(TString)Input->GetName(),newbin20);
  }
  else if (region == "3j2b" || region == "2j2b"){
    Histo2DNewBin = new TH2D("Fixed_"+(TString)Input->GetName(), Input->GetTitle(), nbins1, newbin1, nbins1, newbin1);
    HistoNewBin   = (TH1D*) DumX->Rebin(nbins1,"Fixed_"+(TString)Input->GetName(),newbin1);
  }
  else if (region == "3j3b" || region == "4jge3b" ){
    Histo2DNewBin = new TH2D("Fixed_"+(TString)Input->GetName(), Input->GetTitle(), nbins5, newbin5, nbins5, newbin5);
    HistoNewBin   = (TH1D*) DumX->Rebin(nbins5,"Fixed_"+(TString)Input->GetName(),newbin5);
  }
  else if (region == "3j3bplus4jge3b" ){
    Histo2DNewBin = new TH2D("Fixed_"+(TString)Input->GetName(), Input->GetTitle(), nbins8, newbin8, nbins8, newbin8);
    HistoNewBin   = (TH1D*) DumX->Rebin(nbins8,"Fixed_"+(TString)Input->GetName(),newbin8);
  }
  else{
    Histo2DNewBin = new TH2D("Fixed_"+(TString)Input->GetName(), Input->GetTitle(), nbins12, newbin12, nbins12, newbin12);
    HistoNewBin   = (TH1D*) DumX->Rebin(nbins12,"Fixed_"+(TString)Input->GetName(),newbin12);
  }

  // New binning loop
   for (unsigned int inewxbin=1; inewxbin <= Histo2DNewBin->GetNbinsX(); inewxbin ++){
     int newBx_o = DumX->FindBin(HistoNewBin->GetBinLowEdge(inewxbin)); 
     int newBx_f = DumX->FindBin(HistoNewBin->GetBinLowEdge(inewxbin)+HistoNewBin->GetBinWidth(inewxbin)); 
     // cout << "For X: " << newBx_o << "," << newBx_f << " = " << HistoNewBin->GetBinLowEdge(inewxbin) << "," << HistoNewBin->GetBinLowEdge(inewxbin)+HistoNewBin->GetBinWidth(inewxbin) << endl;
     
     for (unsigned int inewybin=1; inewybin <= Histo2DNewBin->GetNbinsY(); inewybin ++){
      int newBy_o = DumX->FindBin(HistoNewBin->GetBinLowEdge(inewybin)); 
      int newBy_f = DumX->FindBin(HistoNewBin->GetBinLowEdge(inewybin)+HistoNewBin->GetBinWidth(inewybin)); 
      // cout << "For Y: " << newBy_o << "," << newBy_f << " = " << HistoNewBin->GetBinLowEdge(inewybin) << "," << HistoNewBin->GetBinLowEdge(inewybin)+HistoNewBin->GetBinWidth(inewybin) << endl;

      double BinBlockVal = 0.;

      // Old binning: To add the corresponding bins
      for (unsigned int ixbin=newBx_o; ixbin < newBx_f; ixbin ++){
	for (unsigned int iybin=newBy_o; iybin < newBy_f; iybin ++){
	  double ValXY = Input->GetBinContent(ixbin,iybin);
	  BinBlockVal += ValXY ;
	  // cout << "SUM " << ixbin << "," << iybin << " -> " <<  ValXY << " = " << BinBlockVal << endl;
	}
      }

      Histo2DNewBin->SetBinContent( inewxbin, inewybin, BinBlockVal ) ;
            
     } // newBinY
   } // newBinX
   
   
   cout << "Tot = " << Input->Integral() << " NewTot = " << Histo2DNewBin->Integral() << endl;   

   // Set number of entries
   Histo2DNewBin->SetEntries(Input->GetEntries());
   
   return Histo2DNewBin;
   
}


void BinningAdjust(TH1D *Histo){
  // Divide over bin width
  for(int ib=1; ib<= Histo->GetNbinsX(); ib++){
    double Val  = Histo->GetBinContent(ib);
    double Err  = Histo->GetBinError(ib);
    double BinW = Histo->GetXaxis()->GetBinWidth(ib);
    Histo->SetBinContent(ib,(Val/BinW));
    Histo->SetBinError(ib,(Err/BinW));
  }  
  
}


TH1D *SymmetricSystematicCreator(TH1D*Nom, TH1D *Var, TString NameVar){
  TH1D *OutVar = (TH1D*) Nom->Clone(NameVar);
  OutVar->Reset();
  for(int ib=1; ib<= Nom->GetNbinsX(); ib++){
    float Frac = 0.;
    if(Nom->GetBinContent(ib) != 0.) {
      Frac = Var->GetBinContent(ib)/Nom->GetBinContent(ib);
      Frac = 1. + (1. - Frac);
    }
    OutVar->SetBinContent( ib, ( Frac*Nom->GetBinContent(ib) ) );    
    OutVar->SetBinError  ( ib, (      Nom->GetBinError(ib)   ) );    
  }
  return OutVar;
}

// Extrapolate and symmetry Up/Down var
// Same shape/symmetric normalization
void ExtrapolateSymmetricSystematicCreator(TH1D *Nom, TH1D *Up, TH1D *Dw){

  float yNom = Nom->Integral();
  float yUp  = Up ->Integral();
  float yDw  = Dw ->Integral();

  float AvVar = (yUp + yDw)/2.;

  float UpFrac = 1. + (yUp  - AvVar)/AvVar;
  float DwFrac = 1. - (AvVar- yDw)/AvVar;
  
  Up->Scale((1./yUp)*(yNom*UpFrac));
  Dw->Scale((1./yDw)*(yNom*DwFrac));

}

// Extrapolate and symmetry Up/Down var bin by bin
void BinnedSymmetricSystematicCreator(TH1D *Nom, TH1D *Up, TH1D *Dw){
  
  for(int ib=1; ib<= Nom->GetNbinsX(); ib++){
    float yNom = Nom->GetBinContent(ib);
    float yUp  = Up ->GetBinContent(ib);
    float yDw  = Dw ->GetBinContent(ib);

    float AvVar = (yUp - yDw)/2.;
      
    Up ->SetBinContent(ib,yNom+AvVar);
    Dw ->SetBinContent(ib,yNom-AvVar);
      
  }

}


void SmoothEmptyBins(TH1D*Nom, TString SampleName){

  TH1D *NomSm = (TH1D*) Nom->Clone("SmoothedHisto");
  NomSm->Smooth(2);
  
  for(unsigned int nb = 1; nb <= Nom->GetNbinsX(); nb++){
    
    float value = Nom->GetBinContent(nb);
    float error = Nom->GetBinError(nb);
    
    float valueSm = NomSm->GetBinContent(nb);
    float errorSm = NomSm->GetBinError(nb);

    bool BinChange = false;
    
    if (value < 0) {
      cout << "WARNING! -- Negative bin content in " << (TString) Nom->GetName() << " " << SampleName << " " << nb << ", setting it to " << valueSm << " +- " << errorSm << " (from " << value << " +- " << error << ")" << endl;
      value = valueSm;
      error = errorSm;
      BinChange = true;
    }

    if((value-error) < 0.0 ){
      cout << "WARNING! -- Negative content due to the error in "  << (TString) Nom->GetName() << " " << SampleName << " " << nb << ", setting it to " << valueSm << " +- " << errorSm << " (from " << value << " +- " << error << ")" << endl;
      value = valueSm;
      error = errorSm;
      BinChange = true;
    }

    if(BinChange){
      Nom->SetBinContent(nb,value);
      Nom->SetBinError  (nb,error);
    }
      
  }//for(ib)
}

void ExtrapolateSystematicCreator(TH1D *NomNew, TH1D *NomOr, TH1D *SysVar){

  TH1D *histoFracVar = (TH1D*)SysVar->Clone("FracVar");
  histoFracVar->Divide(NomOr);
  
  for(int ib=1; ib<= SysVar->GetNbinsX(); ib++){
    float Frac = histoFracVar->GetBinContent(ib);
    // Extrapolates the SYS variations to the NOMINAL distribution
    SysVar->SetBinContent(ib,Frac*NomNew->GetBinContent(ib));
    SysVar->SetBinError  (ib,     NomNew->GetBinError  (ib));
  }
  
  
}
