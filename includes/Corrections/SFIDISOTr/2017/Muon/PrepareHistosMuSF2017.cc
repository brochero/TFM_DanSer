// Code designed to:
// 1. Create negative side of the trigger SF to avoid additional conditions in the analyzer.
// 2. Standardize the maximum pT for mmuons and electrons to 500 GeV (as it is in e SF) 
// 3. Invert axis in SF TH2

#include "TH2.h" 

TH2F* SwitchXYAxis (TH2F *Histo){
  
  int NbinpT  = Histo->GetNbinsX(); // X-axis (pT)
  int Nbineta = Histo->GetNbinsY(); // Y-axis (eta)
  
  float Vbineta[40]; // eta values
  float VbinpT [40]; // pT  values
    
  // X-axis (pT)
  for(int nbx=1; nbx <= NbinpT; nbx++) VbinpT[nbx-1] = ( Histo->GetXaxis()->GetBinLowEdge(nbx) ); 
  VbinpT[NbinpT] = ( Histo->GetXaxis()->GetBinLowEdge(NbinpT + 1) ); // Add upper edge of the last bin
  
  // Y-axis (eta)
  for(int nby=1; nby <= Nbineta; nby++)  Vbineta[nby-1] = ( Histo->GetYaxis()->GetBinLowEdge(nby) );
  Vbineta[Nbineta] = ( Histo->GetYaxis()->GetBinLowEdge(Nbineta + 1) ); // Add upper edge of the last bin

  TH2F *New2DInv = new TH2F((TString)Histo->GetName()+"Inv",Histo->GetTitle(), Nbineta,Vbineta,NbinpT,VbinpT);

  // std::cout << Nbineta << " bins for eta." << std::endl;
  // for (int iv=0; iv <= Nbineta; iv++) std::cout << Vbineta[iv] << ", ";
  // std::cout << std::endl;
  
  // std::cout << NumberYbins << " bins for pT." << std::endl;
  // for (int iv=0; iv <= NumberYbins; iv++) std::cout << VbinpT[iv] << ", ";
  // std::cout << std::endl;

  for(int nbx=1; nbx <= NbinpT; nbx++){

    int newYbin = New2DInv->GetYaxis()->FindBin(   Histo->GetXaxis()->GetBinCenter(nbx) );

    for(int nby=1; nby <= NbinpT; nby++){

      int newXbin = New2DInv->GetXaxis()->FindBin(   Histo->GetYaxis()->GetBinCenter(nby) );

      int gbin    = Histo   ->GetBin(nbx,     nby);
      int newgbin = New2DInv->GetBin(newXbin, newYbin);

      float OrVal    = Histo->GetBinContent(gbin);
      float OrValErr = Histo->GetBinError  (gbin);

 
      New2DInv->SetBinContent(newgbin,OrVal);
      New2DInv->SetBinError  (newgbin,OrValErr);
      
    }
  }

  
  return New2DInv;
  
}



TH2F* SetYMaximum (TH2F *Histo, float MaxYValue = 500){
  
  int Nbineta = Histo->GetNbinsX(); // X-axis (eta)
  int NbinpT  = Histo->GetNbinsY(); // Y-axis (pT)
  
  float Vbineta[40]; // eta values
  float VbinpT [40]; // pT  values
  
  // X-axis (eta)
  for(int nbx=1; nbx <= Nbineta; nbx++)  Vbineta[nbx-1] = ( Histo->GetXaxis()->GetBinLowEdge(nbx) );
  Vbineta[Nbineta] = ( Histo->GetXaxis()->GetBinLowEdge(Nbineta + 1) ); // Add upper edge of the last bin
  
  // Y-axis (pT)
  int NumberYbins = 0;  
  for(int nby=1; nby <= NbinpT; nby++){
    if ( Histo->GetYaxis()->GetBinLowEdge(nby) < MaxYValue){
      VbinpT[nby-1] = ( Histo->GetYaxis()->GetBinLowEdge(nby) ); 
      NumberYbins ++;
    }
  }

  VbinpT[NumberYbins] = MaxYValue;

  TH2F *New2DRange = new TH2F((TString)Histo->GetName()+"YMax",Histo->GetTitle(), Nbineta,Vbineta,NumberYbins,VbinpT);

  // std::cout << Nbineta << " bins for eta." << std::endl;
  // for (int iv=0; iv <= Nbineta; iv++) std::cout << Vbineta[iv] << ", ";
  // std::cout << std::endl;
  
  // std::cout << NumberYbins << " bins for pT." << std::endl;
  // for (int iv=0; iv <= NumberYbins; iv++) std::cout << VbinpT[iv] << ", ";
  // std::cout << std::endl;

  for(int nbx=1; nbx <= Nbineta; nbx++){

    int newXbin = New2DRange->GetXaxis()->FindBin(   Histo->GetXaxis()->GetBinCenter(nbx) );

    for(int nby=1; nby <= NbinpT; nby++){

      if ( Histo->GetYaxis()->GetBinLowEdge(nby) >=  VbinpT[NumberYbins]) break;

      int newYbin;
      if (Histo->GetYaxis()->GetBinCenter(nby) < MaxYValue) newYbin = New2DRange->GetYaxis()->FindBin(   Histo->GetYaxis()->GetBinCenter(nby) );
      else {
	newYbin = NumberYbins;
      }

      int gbin    = Histo     ->GetBin(nbx,     nby);
      int newgbin = New2DRange->GetBin(newXbin, newYbin);

      float OrVal    = Histo->GetBinContent(gbin);
      float OrValErr = Histo->GetBinError  (gbin);

 
      New2DRange->SetBinContent(newgbin,OrVal);
      New2DRange->SetBinError  (newgbin,OrValErr);
      
    }
  }

  
  return New2DRange;
  
}


TH2F* HistoMirror (TH2F *Histo){
  
  int Nbineta = Histo->GetNbinsX(); // X-axis (eta)
  int NbinpT  = Histo->GetNbinsY(); // Y-axis (pT)
  
  float Vbineta[40]; // eta values
  float VbinpT [40]; // pT  values
  
  // X-axis (eta)
  // NEGATIVE side
  Vbineta[0] = ( -1*Histo->GetXaxis()->GetBinLowEdge(Nbineta + 1) ); // Add upper edge of the last bin (as first bin)
  for(int nbx=Nbineta; nbx >= 2; nbx--)  Vbineta[(Nbineta-nbx)+1] = ( -1*Histo->GetXaxis()->GetBinLowEdge(nbx) );

  for(int nbx=1; nbx <= Nbineta; nbx++)  Vbineta[Nbineta+(nbx-1)] = ( Histo->GetXaxis()->GetBinLowEdge(nbx) );
  Vbineta[2*Nbineta] = ( Histo->GetXaxis()->GetBinLowEdge(Nbineta + 1) ); // Add upper edge of the last bin

  
  // Y-axis (pT)
  for(int nby=1; nby <= NbinpT; nby++)  VbinpT[nby-1] = ( Histo->GetYaxis()->GetBinLowEdge(nby) );
  VbinpT[NbinpT] = Histo->GetYaxis()->GetBinLowEdge(NbinpT+1);


  TH2F *New2DTr = new TH2F((TString)Histo->GetName()+"FullEtaRange",Histo->GetTitle(), Nbineta*2,Vbineta,NbinpT,VbinpT);

  // std::cout << Nbineta*2 << " bins for eta." << std::endl;
  // for (int iv=0; iv <= 2*Nbineta; iv++) std::cout << Vbineta[iv] << ", ";
  // std::cout << std::endl;
  
  // std::cout << NbinpT << " bins for pT." << std::endl;
  // for (int iv=0; iv <= NbinpT; iv++) std::cout << VbinpT[iv] << ", ";
  // std::cout << std::endl;


  for(int nbx=1; nbx <= Nbineta; nbx++){

    int newXbin      = New2DTr->GetXaxis()->FindBin(   Histo->GetXaxis()->GetBinCenter(nbx));
    int minusnewXbin = New2DTr->GetXaxis()->FindBin(-1*Histo->GetXaxis()->GetBinCenter(nbx));

    // cout << nbx << " newXBin = " << newXbin <<  " minusnewXBin = " << minusnewXbin << " value = " << Histo->GetXaxis()->GetBinCenter(nbx) << endl;

    for(int nby=1; nby <= NbinpT; nby++){

      int gbin = Histo->GetBin(nbx,nby);

      int newgbin      = New2DTr->GetBin(newXbin,     nby);
      int minusnewgbin = New2DTr->GetBin(minusnewXbin,nby);

      float OrVal    = Histo->GetBinContent(gbin);
      float OrValErr = Histo->GetBinError  (gbin);

      // cout << nby << " gbin = " << gbin <<  " newgbin = " << newgbin <<  " minusnewgbin = " << minusnewgbin << " value = " << New2DTr->GetXaxis()->GetBinCenter(newXbin) << "/" << New2DTr->GetXaxis()->GetBinCenter(minusnewXbin) << " Vs " << New2DTr->GetYaxis()->GetBinCenter(nby) << "  -- (" << OrVal << " +/- " << OrValErr << ")" << endl;
 
      New2DTr->SetBinContent(newgbin,     OrVal);
      New2DTr->SetBinContent(minusnewgbin,OrVal);

      New2DTr->SetBinError(newgbin,     OrValErr);
      New2DTr->SetBinError(minusnewgbin,OrValErr);

    }

  }

  return New2DTr;
  
} 

void MergeHistos(TString File1, TString File3, TString Histo){

  gStyle->SetOptStat(kFALSE);


  TH1::SetDefaultSumw2(kTRUE);

  TFile *MuSF_1  = TFile::Open(File1);

  TFile *MuSFTot  = new TFile(File3,"RECREATE");
  
  if( !MuSF_1){
    std::cerr << "ERROR [SF]: Could not open SF files!!!"  << std::endl;
    std::exit(0);
  }

  // - File_1
  TH2F *H_1  = (TH2F*) MuSF_1 ->Get(Histo)->Clone();
    
  MuSFTot->cd();

  if(File3.Contains("TriggerSF")){    

    TH2F *HTotFullEtaRange =  HistoMirror(H_1);
    TH2F *HTotMaxYAxisTr = SetYMaximum(HTotFullEtaRange,500/*GeV*/); 
    HTotMaxYAxisTr->SetName("Muon_SF2D");
    HTotMaxYAxisTr->Write();

  }

  else{

    TH2F *HTotInv             = SwitchXYAxis(H_1); 
    TH2F *HTotInvFullEtaRange = HistoMirror(HTotInv);    
    TH2F *HTotMaxYAxis        = SetYMaximum(HTotInvFullEtaRange,500/*GeV*/); 
    

    HTotMaxYAxis->SetName("Muon_SF2D");
    HTotMaxYAxis->Write();

  }

  MuSFTot->Close();
  MuSF_1->Close();
  
}

void PrepareHistosMuSF2017(){

  // For ID
  MergeHistos("Mu_IDSF_2017.root","Mu_TightIDSF.root",
	      "NUM_TightID_DEN_genTracks_pt_abseta_syst");

  // For ISO
  MergeHistos("Mu_ISOSF_2017.root","Mu_TightISOSF.root",
	      "NUM_TightRelIso_DEN_TightIDandIPCut_pt_abseta_syst");

  // For Trigger
  MergeHistos("Mu_TriggerAllSF_2017.root","Mu_TriggerSF.root",
	      "IsoMu27_PtEtaBins/abseta_pt_ratio");

}
