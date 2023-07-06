
// Add systematic histograms in quadrature 
/* void addsystematic(std::vector<histos> hisInit, std::vector<histos> his, TString SysName = "All"){ */

/*   bool sysmatch = false; */
/*   if (SysName != "All") sysmatch = true; */
  
/*   for(unsigned int h = 0; h < his.size(); h++){ */
/*     for(unsigned int ch=0; ch<channel.size(); ch++){   */

/*       TString hname = (TString)his[h].Up[ch]->GetName(); */
/*       if (sysmatch){ */
/* 	if (!hname.Contains(SysName)) continue; */
/*       } */

/*       for (int ib=1;ib<=his[h].hist[ch]->GetNbinsX();ib++){ */
	
/* 	double vCe = his[h].hist[ch]->GetBinContent(ib); */
/* 	double vUp = his[h].Up[ch]  ->GetBinContent(ib); */
/* 	double vDw = his[h].Dw[ch]  ->GetBinContent(ib); */

/* 	double eDw = (vCe-vDw); */
/* 	double eUp = (vUp-vCe); */

/* 	if(vCe != 0.) { eDw = 100.*eDw/vCe; eUp = 100.*eUp/vCe; } */
/* 	else { eDw = 0.; eUp = 0.; } */
	
/* 	if(eUp > 0.) */
/* 	  hisInit[h].Up[ch]->SetBinContent(ib, */
/* 					   sqrt((hisInit[h].Up[ch]->GetBinContent(ib)*hisInit[h].Up[ch]->GetBinContent(ib)) + (eUp*eUp))); */
/* 	else{ */
/* 	  hisInit[h].Dw[ch]->SetBinContent(ib, */
/* 					   sqrt((hisInit[h].Dw[ch]->GetBinContent(ib)*hisInit[h].Dw[ch]->GetBinContent(ib)) + (eUp*eUp))); */
/* 	} */
	
/* 	if(eDw > 0.) */
/* 	  hisInit[h].Dw[ch]->SetBinContent(ib, */
/* 					   sqrt((hisInit[h].Dw[ch]->GetBinContent(ib)*hisInit[h].Dw[ch]->GetBinContent(ib)) + (eDw*eDw))); */
/* 	else { */
/* 	  hisInit[h].Up[ch]->SetBinContent(ib, */
/* 					   sqrt((hisInit[h].Up[ch]->GetBinContent(ib)*hisInit[h].Up[ch]->GetBinContent(ib)) + (eDw*eDw))); */
/* 	} */

/*       }// for(ib) */

/*     }// for(ch) */
    
/*   }// for(histo) */

/* } */



void addTH1systematic(TH1D *InitUp, TH1D *InitDw, TH1D *Nom, TH1D *VarUp, TH1D *VarDw){

  for (int ib = 1;ib <= Nom->GetNbinsX(); ib++){
    
    double vCe = Nom  ->GetBinContent(ib);
    double vUp = VarUp->GetBinContent(ib);
    double vDw = VarDw->GetBinContent(ib);
    
    /* double eDw = std::abs(vCe-vDw); */
    /* double eUp = std::abs(vUp-vCe); */
    double eDw = (vCe-vDw);
    double eUp = (vUp-vCe);
    
    if(vCe != 0.) { eDw = 100.*eDw/vCe; eUp = 100.*eUp/vCe; }
    else { eDw = 0.; eUp = 0.; }
    
    if(eUp > 0.)
      InitUp->SetBinContent(ib,
			   sqrt((InitUp->GetBinContent(ib)*InitUp->GetBinContent(ib)) + (eUp*eUp)));
    else{
      InitDw->SetBinContent(ib,
			   sqrt((InitDw->GetBinContent(ib)*InitDw->GetBinContent(ib)) + (eUp*eUp)));
    }
    
    if(eDw > 0.)
      InitDw->SetBinContent(ib,
			   sqrt((InitDw->GetBinContent(ib)*InitDw->GetBinContent(ib)) + (eDw*eDw)));
    else {
      InitUp->SetBinContent(ib,
			   sqrt((InitUp->GetBinContent(ib)*InitUp->GetBinContent(ib)) + (eDw*eDw)));
    }
    
  }// for(ib)
}
