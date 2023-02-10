#include "NanoAnalyzer.h"

std::vector<NanoObj::Electron> GetTightElectrons(std::vector<NanoObj::Electron> electrons, float pT_min , float eta_max){

  std::vector<NanoObj::Electron> GoodElectrons;

  for (auto ite = electrons.begin() ; ite != electrons.end(); ite++ ){

    NanoObj::Electron sele = *ite;

    // Identification (Tight)
    if(sele.IsTightCBID &&
       sele.Pt() > pT_min &&
       std::abs(sele.Eta()) < eta_max){ 

      // Forbidden regions 
      if (std::abs(sele.Eta()) > 1.4442 && std::abs(sele.Eta())< 1.566) continue; 

      // IP cuts: Barrel
      if (std::abs(sele.Eta()) <= 1.479){
	if (std::abs(sele.dXY) > 0.05 || std::abs(sele.dZ) > 0.10) continue;
      }
      // IP cuts: Encaps
      if (std::abs(sele.Eta()) > 1.479){
	if (std::abs(sele.dXY) > 0.10 || std::abs(sele.dZ) > 0.20) continue;
      }

      GoodElectrons.push_back(sele);

    }

  }

  return GoodElectrons;
}

std::vector<NanoObj::Electron> GetVetoElectrons(std::vector<NanoObj::Electron> electrons, float pT_min , float eta_max){

  std::vector<NanoObj::Electron> GoodElectrons;

  for (unsigned int iel = 0; iel < electrons.size(); iel++ ){
    NanoObj::Electron selelctron = electrons.at(iel);
    
    // Identification (Veto)
    if(!selelctron.IsVetoCBID ||
       selelctron.Pt() < pT_min  ||
       // eta Super-Cluster
       (std::abs(selelctron.Eta()) > 1.4442 && 
        std::abs(selelctron.Eta()) < 1.566) ||
       std::abs(selelctron.Eta()) > eta_max ) continue;
    
    // Isolation already included for electrons in the ID
    
    GoodElectrons.push_back(selelctron);
  
  }

  return GoodElectrons;
}

std::vector<NanoObj::Electron> GetElectronsForQCD(std::vector<NanoObj::Electron> electrons, float pT_min , float eta_max, bool IsIso){

  std::vector<NanoObj::Electron> GoodElectrons;

  for (unsigned int iel = 0; iel < electrons.size(); iel++ ){
    NanoObj::Electron selelctron = electrons.at(iel);
    
    // ONLY pT - eta
    if(selelctron.Pt() < pT_min  ||
       // eta Super-Cluster
       (std::abs(selelctron.Eta()) > 1.4442 && 
        std::abs(selelctron.Eta()) < 1.566) ||
       std::abs(selelctron.Eta()) > eta_max ) continue;
    
    // Explanation (3 bits per cut):
    // 100 100 100 100 100 100 100 100 100 100 = 613566756
    // What I need:
    // 100 100 0** 100 100 100 100 100 100 100
    //         011                             = 611469604
    //         010                             = 609372452
    //         001                             = 607275300
    //         000                             = 605178148
    
    // This means TIGHT electrons w/o isolation cut 
    int eIso = 0;
    if(selelctron.VID == 613566756)    // Tight ISOLATED
      eIso = 1; 
    if(selelctron.VID == 611469604 ||  // Tight ANTI-ISOLATED
       selelctron.VID == 609372452 ||  // Tight ANTI-ISOLATED
       selelctron.VID == 607275300 ||  // Tight ANTI-ISOLATED
       selelctron.VID == 605178148     // Tight ANTI-ISOLATED
       ) eIso = 2;

    if ((eIso == 1 &&  IsIso) ||
	(eIso == 2 && !IsIso))
      GoodElectrons.push_back(selelctron);
  
  }

  return GoodElectrons;
}
