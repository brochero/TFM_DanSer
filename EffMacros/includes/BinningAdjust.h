void BinningAdjust(TH1D *Histo);

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

void NewHistoRange(TH1D *Input, float InitRange, float FinalRange){
  
  for (unsigned int ibin=1; ibin <= Input->GetNbinsX(); ibin ++){
    float LowBin = Input->GetBinLowEdge(ibin);

    if(LowBin < InitRange || LowBin >= FinalRange){
      Input->SetBinContent(ibin, 0.0);
      Input->SetBinError  (ibin, 0.0);
    }
  }

  Input->SetAxisRange(InitRange, FinalRange);
  Input->SetCanExtend(false);
  
}

