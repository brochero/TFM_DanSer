#include "TLorentzVector.h"

namespace NanoObj {

  // Jet Class
  class Jet: public TLorentzVector{
  public:
    float DeepCSV = -99.;
    bool IDTight = 0, IDLepVeto = 0;
    int Flavour = -99 ;    
  };

  // Muon Class
  class Muon:public TLorentzVector{
  public:
    int Charge = 0;
    float Iso = -99., dXY = -99., dZ = -99.;
    bool IsTight = 0, IsLoose = 0;
  };
  
  // Electron Class
  class Electron:public TLorentzVector{
  public:
    int Charge = 0;
    float EtaNoSC = -99., Iso =-99., dXY = -99., dZ = -99.;
    int VID =-99;
    bool IsTightCBID = 0, IsVetoCBID = 0;
  };  

}
