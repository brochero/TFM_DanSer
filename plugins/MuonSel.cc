 #include "NanoAnalyzer.h"

std::vector<NanoObj::Muon> GetTightMuons(std::vector<NanoObj::Muon> muons, float pT_min , float eta_max, float iso_wp){

  std::vector<NanoObj::Muon> GoodMuons;
  
  for (auto itmuon = muons.begin() ; itmuon != muons.end(); itmuon++ ){
    
    NanoObj::Muon selmuon = *itmuon;
    
    // Identification (Tight)    
    if(selmuon.IsTight &&
       selmuon.Pt() > pT_min  &&
       std::abs(selmuon.Eta()) < eta_max && 
       selmuon.Iso < iso_wp){

      GoodMuons.push_back(selmuon); 
          
    }

  }

  return GoodMuons;
}

std::vector<NanoObj::Muon> GetVetoMuons(std::vector<NanoObj::Muon> muons, float pT_min , float eta_max, float iso_wp){

  std::vector<NanoObj::Muon> VetoMuons;

  for (unsigned int imuon = 0; imuon < muons.size(); imuon++ ){
    NanoObj::Muon selmuon = muons.at(imuon);
    
    // Identification (LOOSE)
    if(!selmuon.IsLoose ||
       selmuon.Pt() < pT_min  ||
       std::abs(selmuon.Eta()) > eta_max ) continue;
    
    // Isolation
    if(selmuon.Iso > iso_wp) continue;
    
    VetoMuons.push_back(selmuon);
  
  }

  return VetoMuons;
}


std::vector<NanoObj::Muon> GetMuonsForQCD(std::vector<NanoObj::Muon> muons, float pT_min , float eta_max, bool IsIso){

  std::vector<NanoObj::Muon> QCDMuons;

  for (unsigned int imuon = 0; imuon < muons.size(); imuon++ ){
    NanoObj::Muon selmuon = muons.at(imuon);
    
    // Identification: Same selection criteria BUT no ISOLATION
    if(selmuon.IsTight &&
       selmuon.Pt() > pT_min  &&
       std::abs(selmuon.Eta()) < eta_max ){

      if((selmuon.Iso > 0.15 &&  IsIso) ||
	 (selmuon.Iso < 0.15 && !IsIso)) continue;
      
      QCDMuons.push_back(selmuon);

    }
  }

  return QCDMuons;
}
