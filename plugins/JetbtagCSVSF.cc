// New b-tag method (includes JES correlations in the BTagCalibrationReader construction)
#include "NanoAnalyzer.h"


// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
//      FROM CSV
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------

// ---------
// Event SF
// ---------
float GetbtagEvtWeightFromCSV(BTagCalibrationReader Reader, std::vector<NanoObj::Jet> jets,
			      std::string SysbF, std::string SyscF,std::string SyslF){
  
  double EvtWeightHF = 1., EvtWeightcF = 1., EvtWeightLF = 1.;  
  
  for (auto itjet = jets.begin(); itjet != jets.end(); itjet++ ){

    NanoObj::Jet jet = (*itjet);

    if ( std::abs(jet.Flavour) == 5 ){      //HF  
      double iCSVWgtHF = Reader.eval_auto_bounds(SysbF, BTagEntry::FLAV_B, 
						 std::abs(jet.Eta()), jet.Pt(), jet.DeepCSV);  
      if( iCSVWgtHF!=0 ) EvtWeightHF *= iCSVWgtHF;
    }
    else if( std::abs(jet.Flavour) == 4 ){  //cF
      double iCSVWgtcF = Reader.eval_auto_bounds(SyscF, BTagEntry::FLAV_C, 
						 std::abs(jet.Eta()), jet.Pt(), jet.DeepCSV);  
      if( iCSVWgtcF!=0 ) EvtWeightcF *= iCSVWgtcF;   
    }
    else {                                  //LF
      double iCSVWgtLF = Reader.eval_auto_bounds(SyslF, BTagEntry::FLAV_UDSG, 
						 std::abs(jet.Eta()), jet.Pt(), jet.DeepCSV);  
      if( iCSVWgtLF!=0 ) EvtWeightLF *= iCSVWgtLF;
    }
    
  }

  //std::cout << "SF_HF = "<< EvtWeightHF << "\tSF_LF = " << EvtWeightLF << "\tSF_cF = " << EvtWeightcF << std::endl; 

  return ( EvtWeightHF * EvtWeightcF * EvtWeightLF );
  
}
