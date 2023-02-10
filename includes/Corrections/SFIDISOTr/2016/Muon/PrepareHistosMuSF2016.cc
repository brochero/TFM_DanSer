// Code designed to:
// 1. Merge the different periods of the SF (BCDEF and GH)
// 2. Create negative side of the trigger SF to avoid additional conditions in the analyzer.
// 3. Standardize the maximum pT for mmuons and electrons to 500 GeV (as it is in e SF) 
  
#include "TH2.h" 

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


TH2F* TriggerHistoMirror (TH2F *Histo){
  
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

void MergeHistos(TString File1, TString File2, TString File3, TString Histo){

  gStyle->SetOptStat(kFALSE);


  TH1::SetDefaultSumw2(kTRUE);

  TFile *MuSF_1  = TFile::Open(File1);
  TFile *MuSF_2  = TFile::Open(File2);  

  TFile *MuSFTot  = new TFile(File3,"RECREATE");
  
  if( !MuSF_1 || !MuSF_2 ){
    std::cerr << "ERROR [SF]: Could not open SF files!!!"  << std::endl;
    std::exit(0);
  }

  // - File_1
  TH2F *H_1  = (TH2F*) MuSF_1 ->Get(Histo)->Clone();
  // - File_2
  TH2F *H_2  = (TH2F*) MuSF_2 ->Get(Histo)->Clone();

  // Lumi fractions
  float LumFrac_1 = 19.8/35.9; // (5.8 + 2.6 + 4.2 + 4.1 + 3.1)
  float LumFrac_2 = 16.1/35.9; // (7.5 + 8.4 + 0.2)
  
  // - Total
  TH2F *HTot = (TH2F*) H_1->Clone();
  HTot->Reset();
  
  
  int Nbineta = H_1->GetNbinsX(); // X-axis (eta)
  int NbinpT  =  H_1->GetNbinsY(); // Y-axis (pT)

  for(int nbx=1; nbx <= Nbineta; nbx++){
    for(int nby=1; nby <= NbinpT; nby++){

      int global_bin = H_1->GetBin(nbx,nby);

      float Val_1    = H_1->GetBinContent(global_bin);
      float ValErr_1 = H_1->GetBinError(global_bin);
      float Val_2    = H_2->GetBinContent(global_bin);
      float ValErr_2 = H_2->GetBinError(global_bin);

      float Val    = LumFrac_1*Val_1 + LumFrac_2*Val_2; 
      float ValErr = sqrt( ( (LumFrac_1*Val_1)*(LumFrac_1*Val_1) )*( ValErr_1*ValErr_1 ) +
			   ( (LumFrac_2*Val_2)*(LumFrac_2*Val_2) )*( ValErr_2*ValErr_2 ) );      
      
      HTot->SetBinContent(global_bin,Val);
      HTot->SetBinError  (global_bin,ValErr);            
    }
  }
  

  MuSFTot->cd();

  if(File3.Contains("TriggerSF")){    

    TH2F *HTotFullEtaRange =  TriggerHistoMirror(HTot);
    TH2F *HTotMaxYAxisTr = SetYMaximum(HTotFullEtaRange,500/*GeV*/); 
    HTotMaxYAxisTr->SetName("Muon_SF2D");
    HTotMaxYAxisTr->Write();
  }

  else{
    TH2F *HTotMaxYAxis = SetYMaximum(HTot,500/*GeV*/); 
    HTotMaxYAxis->SetName("Muon_SF2D");
    HTotMaxYAxis->Write();
  }

  MuSFTot->Close();
  MuSF_1->Close();
  MuSF_2->Close();
  
}

void PrepareHistosMuSF2016(){

  // For ID
  MergeHistos("Mu_RunBtoFIDSF_2016.root","Mu_RunGtoHIDSF_2016.root","Mu_TightIDSF.root",
	      "NUM_TightID_DEN_genTracks_eta_pt_syst");

  // For ISO
  MergeHistos("Mu_RunBtoFISOSF_2016.root","Mu_RunGtoHISOSF_2016.root","Mu_TightISOSF.root",
	      "NUM_TightRelIso_DEN_TightIDandIPCut_eta_pt_syst");

  // For Trigger
  MergeHistos("Mu_RunBtoFTriggerSF_2016.root","Mu_RunGtoHTriggerSF_2016.root","Mu_TriggerSF.root",
	      "IsoMu24_OR_IsoTkMu24_PtEtaBins/abseta_pt_ratio");


}
