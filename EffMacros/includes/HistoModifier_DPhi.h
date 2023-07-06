// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// ------------------------------ WARNING ------------------------------ 
// HistoModifier.h for DeltaPhi Different bin size
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


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

  Double_t binX[65];
  for (unsigned int ibin=1; ibin <= Input->GetNbinsX(); ibin ++){
    binX[ibin-1] = Input->GetBinLowEdge(ibin);
  }
  binX[64] = Input->GetBinLowEdge(65);

  // -- All bins
  int nbins = 64;
  Double_t newbin[] = {binX[0],
                       binX[1], binX[2], binX[3], binX[4], binX[5], binX[6], binX[7], binX[8], binX[9], binX[10], // 10
                       binX[11],binX[12],binX[13],binX[14],binX[15],binX[16],binX[17],binX[18],binX[19],binX[20], // 10
                       binX[21],binX[22],binX[23],binX[24],binX[25],binX[26],binX[27],binX[28],binX[29],binX[30], // 10
                       binX[31],binX[32],binX[33],binX[34],binX[35],binX[36],binX[37],binX[38],binX[39],binX[40], // 10
                       binX[41],binX[42],binX[43],binX[44],binX[45],binX[46],binX[47],binX[48],binX[49],binX[50], // 10
                       binX[51],binX[52],binX[53],binX[54],binX[55],binX[56],binX[57],binX[58],binX[59],binX[60], // 10
		       binX[61],binX[62],binX[63],binX[64]};                                                      // 10

     
  // -- 1 bin
  int nbins1 = 1;
  Double_t newbin1[] = {binX[0],  // 0.0
			binX[64]  // 3.2
  };

  // -- 8 bins
  int nbins8 = 8;
  Double_t newbin8[] = {binX[0],  // 0.0
			binX[8],  // 0.4
			binX[16], // 0.8
			binX[24], // 1.2
			binX[32], // 1.6
			binX[40], // 2.0
			binX[48], // 2.4
			binX[56], // 2.8
			binX[64]  // 3.2
  };


  // -- 16 bins
  int nbins16 = 16;
  Double_t newbin16[] = {binX[0],  // 0.0
			 binX[4],  // 0.2
			 binX[8],  // 0.4
			 binX[12], // 0.6
			 binX[16], // 0.8
			 binX[20], // 1.0
			 binX[24], // 1.2
			 binX[28], // 1.4
			 binX[32], // 1.6
			 binX[36], // 1.8
			 binX[40], // 2.0
			 binX[44], // 2.2
			 binX[48], // 2.4
			 binX[52], // 2.6
			 binX[56], // 2.8
			 binX[60], // 3.0
			 binX[64]  // 3.2
  };

  // -- 44 bins
  int nbins44 = 43;
  Double_t newbin44[] = {binX[0],  // 0.0
			 binX[4],  // 0.2
			 binX[8],  // 0.4
			 binX[10], // 0.5
			 binX[12], // 0.6
			 binX[16], // 0.8
			 binX[17], // 
			 binX[18], // 0.9
			 binX[19], // 
			 binX[20], // 1.0
			 binX[21], // 
			 binX[22], // 1.1
			 binX[23], // 
			 binX[24], // 1.2
			 binX[25], // 
			 binX[26], // 1.3
			 binX[27], // 
			 binX[28], // 1.4
			 binX[29], // 
			 binX[30], // 1.5
			 binX[31], // 
			 binX[32], // 1.6
			 binX[33], // 
			 binX[34], // 1.7
			 binX[35], // 
			 binX[36], // 1.8
			 binX[37], // 
			 binX[38], // 1.9
			 binX[39], // 
			 binX[40], // 2.0
			 binX[41], // 
			 binX[42], // 2.1
			 binX[43], // 
			 binX[44], // 2.2
			 binX[45], // 
			 binX[46], // 2.3
			 binX[47], // 
			 binX[48], // 2.4
			 binX[50], // 2.5
			 binX[52], // 2.6
			 binX[54], // 2.7
			 binX[56], // 2.8
			 binX[60], // 3.0
			 binX[64]  // 3.2
  };

  TH1D *HistoNewBin;
  if      (region == "4j2b" || region == "4j2bplus4jge3b" || region == "ge5ge2b")
    HistoNewBin = (TH1D*) Input->Rebin(nbins44,"Fixed_"+(TString)Input->GetName(),newbin44);
  // HistoNewBin = (TH1D*) Input->Rebin(nbins16,"Fixed_"+(TString)Input->GetName(),newbin16);
  else if (region == "2j2b" || region == "3j2b" || region == "3j2bplus3j3b")
    HistoNewBin = (TH1D*) Input->Rebin(nbins1,"Fixed_"+(TString)Input->GetName(),newbin1);
  else{
    HistoNewBin = (TH1D*) Input->Rebin(nbins8,"Fixed_"+(TString)Input->GetName(),newbin8);
  }
  
  return HistoNewBin;

}

TH2D *HistoModifier2D(TH2D *Input, TString region){

  // Only x-axis because it is symmetric for y-axis
  int nbinX=Input->GetNbinsX();
  // Dummy histograms to locate each of the bins
  TH1D *DumX = Input->ProjectionX();
  TH1D *DumY = Input->ProjectionY();
  
  Double_t binX[65];
  for (unsigned int ibin=1; ibin <= DumX->GetNbinsX(); ibin ++){
    binX[ibin-1] = DumX->GetBinLowEdge(ibin);
  }
  binX[64] = DumX->GetBinLowEdge(65);

  // -- All bins
  int nbins = 64;
  Double_t newbin[] = {binX[0],
                       binX[1], binX[2], binX[3], binX[4], binX[5], binX[6], binX[7], binX[8], binX[9],           // 10
                       binX[10],binX[11],binX[12],binX[13],binX[14],binX[15],binX[16],binX[17],binX[18],binX[19], // 10
                       binX[20],binX[21],binX[22],binX[23],binX[24],binX[25],binX[26],binX[27],binX[28],binX[29], // 10
                       binX[30],binX[31],binX[32],binX[33],binX[34],binX[35],binX[36],binX[37],binX[38],binX[39], // 10
                       binX[40],binX[41],binX[42],binX[43],binX[44],binX[45],binX[46],binX[47],binX[48],binX[49], // 10
                       binX[50],binX[51],binX[52],binX[53],binX[54],binX[55],binX[56],binX[57],binX[58],binX[59], // 10
                       binX[60],binX[61],binX[62],binX[63],binX[64]};
  
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
  
  // -- 1 bin
  int nbins1 = 1;
  Double_t newbin1[] = {binX[0],  // 0.0
			binX[64]  // 3.2
  };

  // -- 8 bins
  int nbins8 = 8;
  Double_t newbin8[] = {binX[0],  // 0.0
			binX[8],  // 0.4
			binX[16], // 0.8
			binX[24], // 1.2
			binX[32], // 1.6
			binX[40], // 2.0
			binX[48], // 2.4
			binX[56], // 2.8
			binX[64]  // 3.2
  };


    // -- 16 bins
  int nbins16 = 16;
  Double_t newbin16[] = {binX[0],  // 0.0
			 binX[4],  // 0.2
			 binX[8],  // 0.4
			 binX[12], // 0.6
			 binX[16], // 0.8
			 binX[20], // 1.0
			 binX[24], // 1.2
			 binX[28], // 1.4
			 binX[32], // 1.6
			 binX[36], // 1.8
			 binX[40], // 2.0
			 binX[44], // 2.2
			 binX[48], // 2.4
			 binX[52], // 2.6
			 binX[56], // 2.8
			 binX[60], // 3.0
			 binX[64]  // 3.2
  };
  
  // -- 44 bins
  int nbins44 = 43;
  Double_t newbin44[] = {binX[0],  // 0.0
			 binX[4],  // 0.2
			 binX[8],  // 0.4
			 binX[10], // 0.5
			 binX[12], // 0.6
			 binX[16], // 0.8
			 binX[17], // 
			 binX[18], // 0.9
			 binX[19], // 
			 binX[20], // 1.0
			 binX[21], // 
			 binX[22], // 1.1
			 binX[23], // 
			 binX[24], // 1.2
			 binX[25], // 
			 binX[26], // 1.3
			 binX[27], // 
			 binX[28], // 1.4
			 binX[29], // 
			 binX[30], // 1.5
			 binX[31], // 
			 binX[32], // 1.6
			 binX[33], // 
			 binX[34], // 1.7
			 binX[35], // 
			 binX[36], // 1.8
			 binX[37], // 
			 binX[38], // 1.9
			 binX[39], // 
			 binX[40], // 2.0
			 binX[41], // 
			 binX[42], // 2.1
			 binX[43], // 
			 binX[44], // 2.2
			 binX[45], // 
			 binX[46], // 2.3
			 binX[47], // 
			 binX[48], // 2.4
			 binX[50], // 2.5
			 binX[52], // 2.6
			 binX[54], // 2.7
			 binX[56], // 2.8
			 binX[60], // 3.0
			 binX[64]  // 3.2
  };
  
  
  // Creates a new TH2D  
  TH2D *Histo2DNewBin;
  TH1D *HistoNewBin; 

  if (region == "4j2b" || region == "ge5ge2b" || region == "ge5" ||
      region == "4j2bplus4jge3b"){
    Histo2DNewBin = new TH2D("Fixed_"+(TString)Input->GetName(), Input->GetTitle(), nbins44, newbin44, nbins44, newbin44);
    HistoNewBin   = (TH1D*) DumX->Rebin(nbins44,"Fixed_"+(TString)Input->GetName(),newbin44);
    /* Histo2DNewBin = new TH2D("Fixed_"+(TString)Input->GetName(), Input->GetTitle(), nbins16, newbin16, nbins16, newbin16); */
    /* HistoNewBin   = (TH1D*) DumX->Rebin(nbins16,"Fixed_"+(TString)Input->GetName(),newbin16); */
  }
  else if (region == "2j2b" || region == "3j2b" || region == "3j2bplus3j3b"){
    Histo2DNewBin = new TH2D("Fixed_"+(TString)Input->GetName(), Input->GetTitle(), nbins1, newbin1, nbins1, newbin1);
    HistoNewBin   = (TH1D*) DumX->Rebin(nbins1,"Fixed_"+(TString)Input->GetName(),newbin1);
  }
  else{
    Histo2DNewBin = new TH2D("Fixed_"+(TString)Input->GetName(), Input->GetTitle(), nbins8, newbin8, nbins8, newbin8);
    HistoNewBin   = (TH1D*) DumX->Rebin(nbins8,"Fixed_"+(TString)Input->GetName(),newbin8);
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

// For PLOTTING purpose ONLY
// Divides over bin width
void BinningAdjust(TH1D *Histo){
  for(int ib=1; ib<= Histo->GetNbinsX(); ib++){
    double Val  = Histo->GetBinContent(ib);
    double Err  = Histo->GetBinError(ib);
    double BinW = Histo->GetXaxis()->GetBinWidth(ib);
    Histo->SetBinContent(ib,(Val/BinW));
    Histo->SetBinError(ib,(Err/BinW));
  }  
  
}

// 1. SymmetricSystematicCreator:
//    Creates the opposite symmetric variation
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

// 2. ExtrapolateSymmetricSystematicCreator: 
//    Modifies ONLY the normalization parameter of the Up/Down variations.
//    Founds the separation between Up/Down templates and scale those templates w.r.t the Nominal.
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

// 3. BinnedSymmetricSystematicCreator:
//    Same as ExtrapolateSymmetricSystematicCreator but the process is done bin by bin
//    It DOES CHANGE the shape of the initial Up/Down templates
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

// 4. SmoothEmptyBins:
//    Replaces the empty bins with the content obtained from a Smooth(2)
//    It is done in order to AVOID bins w/o events due to the lack of statistics
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

// 5. ExtrapolateSystematicCreator:
//    Extrapolates a systematic variation calculated w.r.t a NOMINAL template to another NOMINAL'.
//    It modifies the Up/Down templates.
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
