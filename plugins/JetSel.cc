#include "NanoAnalyzer.h"

// Removes Jets overlapped with selected lepton (DeltaR 0.4) 
void SelectAndCleanJets(std::vector<NanoObj::Jet> *jets, TLorentzVector Lepton, float pT_min , float eta_max){

  auto seljets = (*jets);
  auto itorjet = jets->begin();

  for (auto itjet = seljets.begin(); itjet != seljets.end(); itjet++ ){
    NanoObj::Jet seljet = (*itjet);
    bool IsGoodJet = false;
    
    if(seljet.IDLepVeto  &&
       seljet.Pt() > pT_min &&
       std::abs(seljet.Eta()) < eta_max ){
      
      IsGoodJet = seljet.DeltaR(Lepton) > 0.4;

    } //if(GoodJet)                                                                           

    if(!IsGoodJet) jets->erase(itorjet);
    else itorjet++;    
 

  }//for(ijet)
}

// Removes GenJets overlapped with selected lepton (DeltaR 0.4) 
void SelectAndCleanGenJets(std::vector<NanoObj::Jet> *genjets, TLorentzVector Lepton){


  auto selgenjets = (*genjets);
  auto itorgenjet = genjets->begin();

  for (auto itgjet = selgenjets.begin(); itgjet != selgenjets.end(); itgjet++ ){
    NanoObj::Jet selgjet = (*itgjet);
    bool IsGoodGenJet = false;
    
    if(selgjet.Pt() > 15 &&
       std::abs(selgjet.Eta()) < 2.6 ){
      
      // Really needed here?
      IsGoodGenJet = selgjet.DeltaR(Lepton) > 0.4;

    } //if(GoodJet)                                                                           

    if(!IsGoodGenJet) genjets->erase(itorgenjet);
    else itorgenjet++;    
 

  }//for(ijet)
}
