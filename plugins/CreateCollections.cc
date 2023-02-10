#include "NanoAnalyzer.h"

std::vector<NanoObj::Jet> CreateJetCollectionForJEC (NanoAOD *InNano, unsigned int SystNam, unsigned int SystVar){

  std::vector<NanoObj::Jet> objColl;

  for(unsigned int io=0; io < InNano->jet_number; io++){
    NanoObj::Jet obj;

    obj.SetPtEtaPhiM(InNano->jet_pt_JEC[SystNam][SystVar][io],
  		     InNano->jet_eta[io],
  		     InNano->jet_phi[io],
  		     0.0);
    
    obj.DeepCSV   = InNano->jet_btagDeepCSV[io];
    obj.IDTight   = InNano->jet_IDTight[io]; 
    obj.IDLepVeto = InNano->jet_IDLepVeto[io];
    obj.Flavour   = InNano->jet_hadronFlavour[io];

    objColl.push_back(obj);
    
  }

  return objColl;
}

std::vector<NanoObj::Jet> CreateJetCollection (NanoAOD *InNano, unsigned int SystVar){

  std::vector<NanoObj::Jet> objColl;

  auto vJet_pt = InNano->jet_pt;

  // Systematic Uncertainties
  // JES and JER (Affecting the Jet pT)
  // Before, JER nominal SHOULD be applied as default. Based in the results it is not the case anymore. 
  // At reading level, I changed the jet_pt for jet_raw_pt for MC.
  if (SystVar == 1) vJet_pt = InNano->jet_systUncVar; 

  for(unsigned int io=0; io < InNano->jet_number; io++){
    NanoObj::Jet obj;
    
    obj.SetPtEtaPhiM(vJet_pt        [io],
  		     InNano->jet_eta[io],
  		     InNano->jet_phi[io],
  		     0.0);
    
    obj.DeepCSV   = InNano->jet_btagDeepCSV[io];
    obj.IDTight   = InNano->jet_IDTight[io]; 
    obj.IDLepVeto = InNano->jet_IDLepVeto[io];
    obj.Flavour   = InNano->jet_hadronFlavour[io];

    objColl.push_back(obj);
    
  }

  return objColl;
}

std::vector<NanoObj::Jet> CreateGenJetCollection (NanoAOD *InNano){

  std::vector<NanoObj::Jet> objColl;

  for(unsigned int io=0; io < InNano->nGenJet; io++){
    NanoObj::Jet obj;
    
    obj.SetPtEtaPhiM(InNano->genjet_pt [io],
  		     InNano->genjet_eta[io],
  		     InNano->genjet_phi[io],
  		     0.0);
    
    obj.Flavour   = InNano->genjet_flavour[io];

    objColl.push_back(obj);
    
  }

  return objColl;
}


std::vector<NanoObj::Muon> CreateMuonCollection (NanoAOD *InNano, float Iso){
  
  std::vector<NanoObj::Muon> objColl;

  // Note 22/09/21: This TEMPORAL fix is WRONG! It does not consider the pT/Iso cut!
  // After producing new samples, looks like few events have a problem with the muon collection size.
  // something like this mitigates the problem, but it must be fixed at NANO producer level.
  // if (InNano->muon_number != 1) return objColl;

  for(unsigned int io=0; io< InNano->muon_number; io++){
    
    NanoObj::Muon obj;
    
    obj.SetPtEtaPhiE(InNano->muon_pt [io],
  		     InNano->muon_eta[io],
  		     InNano->muon_phi[io],
  		     InNano->muon_E  [io]);
    
    obj.dXY      = InNano->muon_dxy[io];
    obj.dZ       = InNano->muon_dz[io];
    
    obj.Charge   = InNano->muon_charge[io];
    obj.Iso      = InNano->muon_iso_pflow[io];
    obj.IsTight  = InNano->muon_isTight[io];
    obj.IsLoose  = InNano->muon_isLoose[io];
    
    // Selection for veto object 
    if(obj.Pt() > 15 && obj.Iso < Iso) objColl.push_back(obj);
    
  }

  return objColl;
}


std::vector<NanoObj::Electron> CreateElectronCollection (NanoAOD *InNano){

  std::vector<NanoObj::Electron> objColl;

  // Note 22/09/21: This TEMPORAL fix is WRONG! It does not consider the pT cut!
  // After producing new samples, looks like few events have a problem with the electron collection size.
  // something like this mitigates the problem, but it must be fixed at NANO producer level.
  // if (InNano->electron_number != 1) return objColl;
  
  for(unsigned int io=0; io< InNano->electron_number; io++){

    NanoObj::Electron obj;
    
    obj.SetPtEtaPhiE(InNano->electron_pt   [io],
		     InNano->electron_etaSC[io],
		     InNano->electron_phi  [io],
		     InNano->electron_E    [io]);
    

    obj.EtaNoSC      = InNano->electron_eta[io];
    obj.dXY          = InNano->electron_dxy[io];
    obj.dZ           = InNano->electron_dz[io];
    obj.Charge       = InNano->electron_charge[io];
    obj.Iso          = InNano->electron_iso_pflow[io];
    obj.IsTightCBID  = InNano->electron_isTightCBID[io];
    obj.IsVetoCBID   = InNano->electron_isVetoCBID[io];
    obj.VID          = InNano->electron_VID[io];
    
    if(obj.Pt() > 15) objColl.push_back(obj);
    
  }

  return objColl;
}

