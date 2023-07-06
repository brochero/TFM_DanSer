#include "BinSizeOriginal.h"
// #include "BinSizeTest.h"
//#include "BinSizeNov_1pc.h"

void NewHistoRange(TH1D *Input, float InitRange, float FinalRange);

TH1D *HistoModifier  (TH1D *Input, TString region="all", int channel=0, int year=2017);
TH2D *HistoModifier2D(TH2D *Input, TString region="all", int channel=0, int year=2017);
void GetStatVar      (TH1D *Nom, TH1D *StatDown, TH1D *StatUp, TString SamName);
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


TH1D *HistoModifier(TH1D *Input, TString region, int channel, int year){


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
                       binX[1], binX[2], binX[3], binX[4], binX[5], binX[6], binX[7], binX[8], binX[9], binX[10], // 10
                       binX[11],binX[12],binX[13],binX[14],binX[15],binX[16],binX[17],binX[18],binX[19],binX[20], // 10
                       binX[21],binX[22],binX[23],binX[24],binX[25],binX[26],binX[27],binX[28],binX[29],binX[30], // 10
                       binX[31],binX[32],binX[33],binX[34],binX[35],binX[36],binX[37],binX[38],binX[39],binX[40], // 10
                       binX[41],binX[42],binX[43],binX[44],binX[45],binX[46],binX[47],binX[48],binX[49],binX[50]};// 10
                          

  TH1D *HistoNewBin;
  if      (region == "2j2b")
    //HistoNewBin = (TH1D*) Input->Rebin(nbins1,"Fixed_"+(TString)Input->GetName(),newbin1);
    HistoNewBin = (TH1D*) Input->Rebin(nbins2j2b_mujets_2017,"Fixed_"+(TString)Input->GetName(),newbin2j2b_mujets_2017);
  
  else if (region == "3j2b" || region == "3j2bplus3j3b")
    //HistoNewBin = (TH1D*) Input->Rebin(nbins1,"Fixed_"+(TString)Input->GetName(),newbin1);
    HistoNewBin = (TH1D*) Input->Rebin(nbins3j2bplus3j3b_mujets_2017,"Fixed_"+(TString)Input->GetName(),newbin3j2bplus3j3b_mujets_2017);
  
  //else if (region == "4j2b" && year == 2017)
  else if (region == "4j2b")
    HistoNewBin = (TH1D*) Input->Rebin(nbins4j2b_mujets_2017,"Fixed_"+(TString)Input->GetName(),newbin4j2b_mujets_2017);
  //HistoNewBin = (TH1D*) Input->Rebin(nbins4j2b_ejets_2017,"Fixed_"+(TString)Input->GetName(),newbin4j2b_ejets_2017);

  //else if (region == "4j2bplus4jge3b" &&  year == 2017)
  else if (region == "4j2bplus4jge3b")
    HistoNewBin = (TH1D*) Input->Rebin(nbins4j2bplus4jge3b_mujets_2017,"Fixed_"+(TString)Input->GetName(),newbin4j2bplus4jge3b_mujets_2017);
  // HistoNewBin = (TH1D*) Input->Rebin(nbins4j2bplus4jge3b_ejets_2017,"Fixed_"+(TString)Input->GetName(),newbin4j2bplus4jge3b_ejets_2017);

  //else if (region == "4j2bplus4jge3bplusge5ge2b" && year == 2017)
  else if (region == "4j2bplusge5ge2b" || region == "4j2bplus4jge3bplusge5ge2b" || region == "3j2bplus3j3bplus4j2bplus4jge3bplusge5ge2b")
    HistoNewBin = (TH1D*) Input->Rebin(nbins4j2bplus4jge3bplusge5ge2b_mujets_2017,"Fixed_"+(TString)Input->GetName(),newbin4j2bplus4jge3bplusge5ge2b_mujets_2017);
  // HistoNewBin = (TH1D*) Input->Rebin(nbins4j2bplus4jge3bplusge5ge2b_ejets_2017,"Fixed_"+(TString)Input->GetName(),newbin4j2bplus4jge3bplusge5ge2b_ejets_2017);

  //else if (region == "ge5ge2b" && year == 2017)
  else if (region == "ge5ge2b")
    HistoNewBin = (TH1D*) Input->Rebin(nbinsge5ge2b_mujets_2017,"Fixed_"+(TString)Input->GetName(),newbinge5ge2b_mujets_2017);
  // HistoNewBin = (TH1D*) Input->Rebin(nbinsge5ge2b_ejets_2017,"Fixed_"+(TString)Input->GetName(),newbinge5ge2b_ejets_2017);

  else{
    HistoNewBin = (TH1D*) Input->Rebin(nbins1,"Fixed_"+(TString)Input->GetName(),newbin1);
  }

  // TEMPORAL to avoid rebinning!!!
  HistoNewBin = (TH1D*) Input->Rebin(nbins,"Fixed_"+(TString)Input->GetName(),newbin);

  return HistoNewBin;

}

TH2D *HistoModifier2D(TH2D *Input, TString region, int channel, int year){

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

  // Creates a new TH2D  
  TH2D *Histo2DNewBin;
  TH1D *HistoNewBin; 

  if      (region == "2j2b"){
    /* Histo2DNewBin = new TH2D("Fixed_"+(TString)Input->GetName(), Input->GetTitle(), nbins1, newbin1, nbins1, newbin1); */
    /* HistoNewBin   = (TH1D*) DumX->Rebin(nbins1,"Fixed_"+(TString)Input->GetName(),newbin1); */
    Histo2DNewBin = new TH2D("Fixed_"+(TString)Input->GetName(), Input->GetTitle(),
			     nbins2j2b_mujets_2017, newbin2j2b_mujets_2017,
			     nbins2j2b_mujets_2017, newbin2j2b_mujets_2017);
    HistoNewBin   = (TH1D*) DumX->Rebin(nbins2j2b_mujets_2017,"Fixed_"+(TString)Input->GetName(),newbin2j2b_mujets_2017);
  }

  else if (region == "3j2b" || region == "3j2bplus3j3b"){
    /* Histo2DNewBin = new TH2D("Fixed_"+(TString)Input->GetName(), Input->GetTitle(), nbins1, newbin1, nbins1, newbin1); */
    /* HistoNewBin   = (TH1D*) DumX->Rebin(nbins1,"Fixed_"+(TString)Input->GetName(),newbin1); */
    Histo2DNewBin = new TH2D("Fixed_"+(TString)Input->GetName(), Input->GetTitle(),
			     nbins3j2bplus3j3b_mujets_2017, newbin3j2bplus3j3b_mujets_2017,
			     nbins3j2bplus3j3b_mujets_2017, newbin3j2bplus3j3b_mujets_2017);
    HistoNewBin   = (TH1D*) DumX->Rebin(nbins3j2bplus3j3b_mujets_2017,"Fixed_"+(TString)Input->GetName(),newbin3j2bplus3j3b_mujets_2017);
  }

  //else if (region == "4j2b" && year == 2017){
  else if (region == "4j2b"){
    Histo2DNewBin = new TH2D("Fixed_"+(TString)Input->GetName(), Input->GetTitle(),
			     nbins4j2b_mujets_2017, newbin4j2b_mujets_2017,
			     nbins4j2b_mujets_2017, newbin4j2b_mujets_2017);
    HistoNewBin   = (TH1D*) DumX->Rebin(nbins4j2b_mujets_2017,"Fixed_"+(TString)Input->GetName(),newbin4j2b_mujets_2017);

    /* Histo2DNewBin = new TH2D("Fixed_"+(TString)Input->GetName(), Input->GetTitle(), */
    /* 			     nbins4j2b_ejets_2017, newbin4j2b_ejets_2017, */
    /* 			     nbins4j2b_ejets_2017, newbin4j2b_ejets_2017); */
    /* HistoNewBin   = (TH1D*) DumX->Rebin(nbins4j2b_ejets_2017,"Fixed_"+(TString)Input->GetName(),newbin4j2b_ejets_2017); */
  }

  //else if (region == "4j2bplus4jge3b" && year == 2017){
  else if (region == "4j2bplus4jge3b"){
    Histo2DNewBin = new TH2D("Fixed_"+(TString)Input->GetName(), Input->GetTitle(),
			     nbins4j2bplus4jge3b_mujets_2017, newbin4j2bplus4jge3b_mujets_2017,
			     nbins4j2bplus4jge3b_mujets_2017, newbin4j2bplus4jge3b_mujets_2017);
    HistoNewBin   = (TH1D*) DumX->Rebin(nbins4j2bplus4jge3b_mujets_2017,"Fixed_"+(TString)Input->GetName(),newbin4j2bplus4jge3b_mujets_2017);

    /* Histo2DNewBin = new TH2D("Fixed_"+(TString)Input->GetName(), Input->GetTitle(), */
    /* 			     nbins4j2bplus4jge3b_ejets_2017, newbin4j2bplus4jge3b_ejets_2017, */
    /* 			     nbins4j2bplus4jge3b_ejets_2017, newbin4j2bplus4jge3b_ejets_2017); */
    /* HistoNewBin   = (TH1D*) DumX->Rebin(nbins4j2bplus4jge3b_ejets_2017,"Fixed_"+(TString)Input->GetName(),newbin4j2bplus4jge3b_ejets_2017); */
  }

  //else if (region == "4j2bplus4jge3bplusge5ge2b" && year == 2017){
  else if (region == "4j2bplusge5ge2b" || region == "4j2bplus4jge3bplusge5ge2b" || region == "3j2bplus3j3bplus4j2bplus4jge3bplusge5ge2b"){
    Histo2DNewBin = new TH2D("Fixed_"+(TString)Input->GetName(), Input->GetTitle(),
			     nbins4j2bplus4jge3bplusge5ge2b_mujets_2017, newbin4j2bplus4jge3bplusge5ge2b_mujets_2017,
			     nbins4j2bplus4jge3bplusge5ge2b_mujets_2017, newbin4j2bplus4jge3bplusge5ge2b_mujets_2017);
    HistoNewBin   = (TH1D*) DumX->Rebin(nbins4j2bplus4jge3bplusge5ge2b_mujets_2017,"Fixed_"+(TString)Input->GetName(),newbin4j2bplus4jge3bplusge5ge2b_mujets_2017);

    /* Histo2DNewBin = new TH2D("Fixed_"+(TString)Input->GetName(), Input->GetTitle(), */
    /* 			     nbins4j2bplus4jge3bplusge5ge2b_ejets_2017, newbin4j2bplus4jge3bplusge5ge2b_ejets_2017, */
    /* 			     nbins4j2bplus4jge3bplusge5ge2b_ejets_2017, newbin4j2bplus4jge3bplusge5ge2b_ejets_2017); */
    /* HistoNewBin   = (TH1D*) DumX->Rebin(nbins4j2bplus4jge3bplusge5ge2b_ejets_2017,"Fixed_"+(TString)Input->GetName(),newbin4j2bplus4jge3bplusge5ge2b_ejets_2017); */
  }

    //else if (region == "ge5ge2b" && year == 2017){
    else if (region == "ge5ge2b"){
    Histo2DNewBin = new TH2D("Fixed_"+(TString)Input->GetName(), Input->GetTitle(),
			     nbinsge5ge2b_mujets_2017, newbinge5ge2b_mujets_2017,
			     nbinsge5ge2b_mujets_2017, newbinge5ge2b_mujets_2017);
    HistoNewBin   = (TH1D*) DumX->Rebin(nbinsge5ge2b_mujets_2017,"Fixed_"+(TString)Input->GetName(),newbinge5ge2b_mujets_2017);

    /* Histo2DNewBin = new TH2D("Fixed_"+(TString)Input->GetName(), Input->GetTitle(), */
    /* 			     nbinsge5ge2b_ejets_2017, newbinge5ge2b_ejets_2017, */
    /* 			     nbinsge5ge2b_ejets_2017, newbinge5ge2b_ejets_2017); */
    /* HistoNewBin   = (TH1D*) DumX->Rebin(nbinsge5ge2b_ejets_2017,"Fixed_"+(TString)Input->GetName(),newbinge5ge2b_ejets_2017); */
  }

  else{
    HistoNewBin = (TH1D*) DumX->Rebin(nbins1,"Fixed_"+(TString)Input->GetName(),newbin1);
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
   
   // TEMPORAL to avoid rebinning!!!
   return Input;

   //return Histo2DNewBin;
   
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
//    18/10/22: Optimization after still finding negative bins.
void SmoothEmptyBins(TH1D*Nom, TString SampleName){

  unsigned int NxBins = Nom->GetNbinsX();
  
  // Remove UnderFlows
  Nom->SetBinContent(0,0.);
  Nom->SetBinError  (0,0.);
  // Remove OverFlows
  Nom->SetBinContent(NxBins+1,0.);
  Nom->SetBinError  (NxBins+1,0.);
  
  
  if (NxBins < 3) {
    cout << "Histogram cannot be smoothed..." << endl;
    return;
  }
  float Nevt = Nom->Integral();
  TH1D *NomSm = (TH1D*) Nom->Clone("SmoothedHisto");
  NomSm->Smooth(2);
  
  for(unsigned int nb = 1; nb <= NxBins; nb++){
    
    float value = Nom->GetBinContent(nb);
    float error = Nom->GetBinError(nb);
    
    float valueSm = NomSm->GetBinContent(nb);
    float errorSm = NomSm->GetBinError(nb);

    bool BinChange = false;
    
    if (value < 0 || (value-error) < 0.0) {
      cout << "WARNING! -- Negative bin content in " << (TString) Nom->GetName() << " " << SampleName << " " << nb << ", setting it to " << valueSm << " +- " << errorSm << " (from " << value << " +- " << error << ")" << endl;
      if(valueSm > 0){
	value = valueSm;
	error =  valueSm; // 100% error
      }
      else if(nb > 1 && nb < NxBins) {
	value = (Nom->GetBinContent(nb-1)+Nom->GetBinContent(nb+1))/2.;
	error = value; // 100% error
      }

      else {
	value = 1;
	error = 1;
      }
      
      BinChange = true;
      
    }

    /* if((value-error) < 0.0 ){ */
    /*   cout << "WARNING! -- Negative content due to the error in "  << (TString) Nom->GetName() << " " << SampleName << " " << nb << ", setting it to " << valueSm << " +- " << errorSm << " (from " << value << " +- " << error << ")" << endl; */
    /*   value = valueSm; */
    /*   error = errorSm; */
    /*   BinChange = true; */
    /* } */

    if(BinChange){
      Nom->SetBinContent(nb,value);
      Nom->SetBinError  (nb,error);
    }
      
  }//for(ib)

  // Renormalization->Total number of events
  // Make no sense when there are HUGE negative entries...
  // cout << "Re-normalazing histograms to the initial integral after remove the negative bins:" << Nom->Integral() << " to " << Nevt << endl;
  // Nom->Scale(Nevt/Nom->Integral());
  
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
