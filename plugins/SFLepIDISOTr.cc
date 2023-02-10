#include "NanoAnalyzer.h"

void ReadLeptonTriggerSF(TString fSFdir, TH2F *hLepSF[2][3]){

  TString MuFileBase = fSFdir + "/Muon/Mu";
  TString ElFileBase = fSFdir + "/Electron/El";

  // Lepton SFs: ID, ISO and trigger with stat. + syst. Errors
  TString FileNames[2][3] = {  {MuFileBase + "_TightIDSF",
				MuFileBase + "_TightISOSF",
				MuFileBase + "_TriggerSF"},
			       {ElFileBase + "_RECOSF",
				ElFileBase + "_CBFall17V2TightSF",
				ElFileBase + "_TriggerSF"} };  

  TString HistoNames[2][3] = {{"Muon_SF2D",  "Muon_SF2D",  "Muon_SF2D"  },
			      {"EGamma_SF2D","EGamma_SF2D","EGamma_SF2D"} };

  for (int ich=0; ich<2; ich++){
    for (int ih=0; ih<3; ih++){
      
      std::cout << "Reading " << FileNames[ich][ih] + ".root" << std::endl;
      TFile *fSF = TFile::Open(FileNames[ich][ih] + ".root");  
      
      if( !fSF ){
	std::cerr << "ERROR [SF]: Could not open SF files for electrons!!!"  << std::endl;
	std::exit(0);
      }
      
      hLepSF[ich][ih] = (TH2F*)fSF->Get(HistoNames[ich][ih])->Clone();
      hLepSF[ich][ih]->SetDirectory(0);
      
      fSF->TFile::Close();
      delete fSF;
    }
    
  }

}

void GetSF(TH2F *Histo, float eta, float pT, float *SF, float *SF_err){
  
  int global_bin = Histo->GetBin(Histo->GetXaxis()->FindBin(eta),
				 Histo->GetYaxis()->FindBin(pT));
  
  (*SF)     = Histo->GetBinContent(global_bin);
  (*SF_err) = Histo->GetBinError  (global_bin);
  
  // std::cout << "GlobalBin (" << Histo->GetXaxis()->FindBin(eta) << "," << Histo->GetYaxis()->FindBin(pT) << ") = " << global_bin << " SF = " << (*SF) << " +/- " << (*SF_err) << std::endl;
}


float LeptonSF(TH2F *Histo[2][3], int channel, float eta, float pT, int SystVar = var::Nom){

  if (pT > 500.) pT = 499.; // Maximum pT for electrons and muons

  float SF0, SF0_err;
  GetSF(Histo[channel][0], eta, pT, &SF0, &SF0_err);
  float SF1, SF1_err;
  GetSF(Histo[channel][1], eta, pT, &SF1, &SF1_err);
  float SFTr, SFTr_err;
  GetSF(Histo[channel][2], eta, pT, &SFTr, &SFTr_err);
  
  // SystVar[0=None, 1/-1=ID/ISO, 2/-2=Trigger]
  if      (SystVar == var::Nom    ) return (SF0*SF1*SFTr);
  else if (SystVar == var::Up     ) return ((SF0+SF0_err)*(SF1+SF1_err)*SFTr);
  else if (SystVar == var::Down   ) return ((SF0-SF0_err)*(SF1-SF1_err)*SFTr);
  else if (SystVar == var::Up+10  ) return (SF0*SF1*(SFTr+SFTr_err));
  else if (SystVar == var::Down+10) return (SF0*SF1*(SFTr-SFTr_err));
  else return 1.;
}
