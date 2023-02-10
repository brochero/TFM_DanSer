#include<vector>
#include<iostream>
#include "TString.h"


/***************************
    SF: Normalization
***************************/
      
float SFLumi(TString filename,
	     float Lumi,
	     float NGenEvents){
  
  /************************
    Normalization Weights
  *************************/

  float NormWeight = 1.0;
  // NormWeight = Lumi*(1.0/N_Gen_events)*(Xsec)*(Br)


  //=======================================================  QCD  ==============================================================

  if     (filename.Contains("QCD_Pt-15to20_MuEnrichedPt5"))     NormWeight = Lumi * (1.0/NGenEvents) * (1273190000.0) * (0.003); // [pb] (cross section) * (Filter Eff) = 3.81957e+06
  else if(filename.Contains("QCD_Pt-20to30_MuEnrichedPt5"))     NormWeight = Lumi * (1.0/NGenEvents) * (558528000.0) * (0.0053); // [pb] (cross section) * (Filter Eff) = 2.96020e+06
  else if(filename.Contains("QCD_Pt-30to50_MuEnrichedPt5"))     NormWeight = Lumi * (1.0/NGenEvents) * (139803000.0) * (0.0118); // [pb] (cross section) * (Filter Eff) = 1.64968e+06
  else if(filename.Contains("QCD_Pt-50to80_MuEnrichedPt5"))     NormWeight = Lumi * (1.0/NGenEvents) * (19222500.0) * (0.02276); // [pb] (cross section) * (Filter Eff) = 437504.
  else if(filename.Contains("QCD_Pt-80to120_MuEnrichedPt5"))    NormWeight = Lumi * (1.0/NGenEvents) * (2758420.0) * (0.03844);  // [pb] (cross section) * (Filter Eff) = 106034.
  else if(filename.Contains("QCD_Pt-120to170_MuEnrichedPt5"))   NormWeight = Lumi * (1.0/NGenEvents) * (469797.0) * (0.05362);   // [pb] (cross section) * (Filter Eff) = 25190.5
  else if(filename.Contains("QCD_Pt-170to300_MuEnrichedPt5"))   NormWeight = Lumi * (1.0/NGenEvents) * (117989.0) * (0.07335);   // [pb] (cross section) * (Filter Eff) = 8654.49
  else if(filename.Contains("QCD_Pt-300to470_MuEnrichedPt5"))   NormWeight = Lumi * (1.0/NGenEvents) * (7820.25) * (0.10196);    // [pb] (cross section) * (Filter Eff) = 797.353
  else if(filename.Contains("QCD_Pt-470to600_MuEnrichedPt5"))   NormWeight = Lumi * (1.0/NGenEvents) * (645.528) * (0.12242);    // [pb] (cross section) * (Filter Eff) = 79.0255
  else if(filename.Contains("QCD_Pt-600to800_MuEnrichedPt5"))   NormWeight = Lumi * (1.0/NGenEvents) * (187.09) * (0.13412);     // [pb] (cross section) * (Filter Eff) = 25.0925
  else if(filename.Contains("QCD_Pt-800to1000_MuEnrichedPt5"))  NormWeight = Lumi * (1.0/NGenEvents) * (32.3486) * (0.14552);    // [pb] (cross section) * (Filter Eff) = 4.70737
  else if(filename.Contains("QCD_Pt-1000toInf_MuEnrichedPt5"))  NormWeight = Lumi * (1.0/NGenEvents) * (10.4305) * (0.15544);    // [pb] (cross section) * (Filter Eff) = 1.62132

  else if(filename.Contains("QCD_Pt-15to20_EMEnriched"))     NormWeight = Lumi * (1.0/NGenEvents) * (1279000000.0) * (0.0018); // [pb] (cross section) * (Filter Eff) = 2.30220e+06
  else if(filename.Contains("QCD_Pt-20to30_EMEnriched"))     NormWeight = Lumi * (1.0/NGenEvents) * (557600000.0) * (0.0096);  // [pb] (cross section) * (Filter Eff) = 5.35296e+06
  else if(filename.Contains("QCD_Pt-30to50_EMEnriched"))     NormWeight = Lumi * (1.0/NGenEvents) * (136000000.0) * (0.073);   // [pb] (cross section) * (Filter Eff) = 9.92800e+06
  else if(filename.Contains("QCD_Pt-50to80_EMEnriched"))     NormWeight = Lumi * (1.0/NGenEvents) * (19800000.0) * (0.146);    // [pb] (cross section) * (Filter Eff) = 2.89080e+06
  else if(filename.Contains("QCD_Pt-80to120_EMEnriched"))    NormWeight = Lumi * (1.0/NGenEvents) * (2800000.0) * (0.125);     // [pb] (cross section) * (Filter Eff) = 350000.
  else if(filename.Contains("QCD_Pt-120to170_EMEnriched"))   NormWeight = Lumi * (1.0/NGenEvents) * (477000.0) * (0.132);      // [pb] (cross section) * (Filter Eff) = 62964.0
  else if(filename.Contains("QCD_Pt-170to300_EMEnriched"))   NormWeight = Lumi * (1.0/NGenEvents) * (114000.0) * (0.165);      // [pb] (cross section) * (Filter Eff) = 18810.0
  else if(filename.Contains("QCD_Pt-300toInf_EMEnriched"))   NormWeight = Lumi * (1.0/NGenEvents) * (9000.0) * (0.15);         // [pb] (cross section) * (Filter Eff) = 1350.00

  else if(filename.Contains("QCD_Pt_15to20_bcToE"))     NormWeight = Lumi * (1.0/NGenEvents) * (231500.0);   // [pb] (cross section) * (Filter Eff)
  else if(filename.Contains("QCD_Pt_20to30_bcToE"))     NormWeight = Lumi * (1.0/NGenEvents) * (363600.0);   // [pb] (cross section) * (Filter Eff)
  else if(filename.Contains("QCD_Pt_30to80_bcToE"))     NormWeight = Lumi * (1.0/NGenEvents) * (416700.0);   // [pb] (cross section) * (Filter Eff)
  else if(filename.Contains("QCD_Pt_80to170_bcToE"))    NormWeight = Lumi * (1.0/NGenEvents) * (39950.0);    // [pb] (cross section) * (Filter Eff)
  else if(filename.Contains("QCD_Pt_170to250_bcToE"))   NormWeight = Lumi * (1.0/NGenEvents) * (2603.0);     // [pb] (cross section) * (Filter Eff)
  else if(filename.Contains("QCD_Pt_250toInf_bcToE"))   NormWeight = Lumi * (1.0/NGenEvents) * (722.6);      // [pb] (cross section) * (Filter Eff)


  //=======================================================  DY  ==============================================================

  //DYJetsToLL_0J_TuneCP5_13TeV-amcatnloFXFX-pythia8
  else if(filename.Contains("DYJetsToLL_0J_Tune"))  NormWeight = Lumi * (1.0/NGenEvents) * (4620.519036);  // [pb]
  //DYJetsToLL_1J_TuneCP5_13TeV-amcatnloFXFX-pythia8
  else if(filename.Contains("DYJetsToLL_1J_Tune"))  NormWeight = Lumi * (1.0/NGenEvents) * (859.589402);  // [pb]
  //DYJetsToLL_2J_TuneCP5_13TeV-amcatnloFXFX-pythia8
  else if(filename.Contains("DYJetsToLL_2J_Tune"))  NormWeight = Lumi * (1.0/NGenEvents) * (338.258531);  // [pb]
  //DYJetsToLL_M-10to50_TuneCP5_13TeV-madgraphMLM-pythia8
  //DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8
  else if(filename.Contains("DYJetsToLL_M-10to50_Tune"))  NormWeight = Lumi * (1.0/NGenEvents) * (22635.1);  // [pb] From CMS AN-16-327
  //DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8
  //DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8
  //DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8
  else if(filename.Contains("DYJetsToLL_M-50_Tune"))      NormWeight = Lumi * (1.0/NGenEvents) * (6025.2);   // [pb]
  //DYJetsToLL_M-5to50_TuneCP5_13TeV-madgraphMLM-pythia8
  else if(filename.Contains("DYJetsToLL_M-5to50_Tune"))  NormWeight = Lumi * (1.0/NGenEvents) * (81880.0);  // [pb]



  //=======================================================  VV  ==============================================================

  // for WW: using the nr in page 13 of https://indico.cern.ch/event/439995/contributions/1094416/attachments/1143460/1638648/diboson_final.pdf
  //WW_DoubleScattering_13TeV-pythia8_TuneCP5
  else if(filename.Contains("WW_DoubleScattering"))             NormWeight = Lumi * (1.0/NGenEvents) * (1.921);  // [pb]   from XDB !! check 
  //WW_TuneCP5_13TeV-pythia8
  else if(filename.Contains("WW_Tune"))             NormWeight = Lumi * (1.0/NGenEvents) * (118.7);  // [pb]  
 // For WZ and ZZ : https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns#Diboson
  //WZ_TuneCP5_13TeV-pythia8
  else if(filename.Contains("WZ_Tune"))             NormWeight = Lumi * (1.0/NGenEvents) * (47.13);  // [pb]
  //ZZ_TuneCP5_13TeV-pythia8
  else if(filename.Contains("ZZ_Tune"))             NormWeight = Lumi * (1.0/NGenEvents) * (16.523); // [pb]


  //=======================================================  ttV  ==============================================================

  //TTWJetsToLNu_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8
  //TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8
  else if(filename.Contains("TTWJetsToLNu_Tune"))           NormWeight = Lumi * (1.0/NGenEvents) * (0.2043); // [pb]
  //TTWJetsToQQ_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8
  //TTWJetsToQQ_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8
  else if(filename.Contains("TTWJetsToQQ_Tune"))          NormWeight = Lumi * (1.0/NGenEvents) * (0.4062); // [pb]
  //TTZJetsToQQ_Dilept_TuneCP5_PSweights_13TeV-amcatnlo-pythia8
  else if(filename.Contains("TTZJetsToQQ_Dilept_Tune"))          NormWeight = Lumi * (1.0/NGenEvents) * (0.0000); // [pb]    NOT AVAILABLE in XDB !! check
  //TTZToLLNuNu_M-10_TuneCP5_13TeV-amcatnlo-pythia8
  //TTZToLLNuNu_M-10_TuneCP5_PSweights_13TeV-amcatnlo-pythia8
  //TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8
  else if(filename.Contains("TTZToLLNuNu_M-10_Tune"))          NormWeight = Lumi * (1.0/NGenEvents) * (0.2529); // [pb]
  //TTZToLL_M-1to10_TuneCP5_13TeV-amcatnlo-pythia8
  else if(filename.Contains("TTZToLL_M-1to10_Tune"))          NormWeight = Lumi * (1.0/NGenEvents) * (0.05324); // [pb]
  //TTZToQQ_TuneCP5_13TeV-amcatnlo-pythia8
  //TTZToQQ_TuneCUETP8M1_13TeV-amcatnlo-pythia8
  else if(filename.Contains("TTZToQQ_Tune"))          NormWeight = Lumi * (1.0/NGenEvents) * (0.5297); // [pb]


  //=======================================================  W+Jets  ==============================================================

  //WJetsToLNu_0J_TuneCP5_13TeV-amcatnloFXFX-pythia8
  else if(filename.Contains("WJetsToLNu_0J_Tune"))       NormWeight = Lumi * (1.0/NGenEvents) * (50131.98259);  // [pb]
  //WJetsToLNu_1J_TuneCP5_13TeV-amcatnloFXFX-pythia8
  else if(filename.Contains("WJetsToLNu_1J_Tune"))       NormWeight = Lumi * (1.0/NGenEvents) * (8426.094336);  // [pb]
  //WJetsToLNu_2J_TuneCP5_13TeV-amcatnloFXFX-pythia8
  else if(filename.Contains("WJetsToLNu_2J_Tune"))       NormWeight = Lumi * (1.0/NGenEvents) * (3172.958208);  // [pb]
  //WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8
  //WJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8
  //WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8
  else if(filename.Contains("WJetsToLNu_Tune"))       NormWeight = Lumi * (1.0/NGenEvents) * (61526.7);  // [pb]
  //
  //        BE CAREFUL :     WJetsToLNu_Tune  is ALSO CONTAINED in TTWJetsToLNu_Tune so must be also searched AFTER the TTWJetsToLNu_Tune !!!
  //  


  //=======================================================  Single Top  ==============================================================

  // ......................... 	
  // ......  from XDB ........
  // ......................... 	
  //else if(filename.Contains("ST_s-channel_4f_hadronicDecays_TuneCP5_PSweights_13TeV-amcatnlo-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (0.0000000000000000000);    // [pb]
  //else if(filename.Contains("ST_s-channel_4f_leptonDecays_TuneCP5CR1_13TeV-amcatnlo-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (0.0000000000000000000);    // [pb]
  //else if(filename.Contains("ST_s-channel_4f_leptonDecays_TuneCP5CR2_13TeV-amcatnlo-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (0.0000000000000000000);    // [pb]
  //else if(filename.Contains("ST_s-channel_4f_leptonDecays_TuneCP5_13TeV-amcatnlo-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (3.74);    // [pb]
  //else if(filename.Contains("ST_s-channel_4f_leptonDecays_TuneCP5_PSweights_13TeV-amcatnlo-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (3.74);    // [pb]
  //else if(filename.Contains("ST_s-channel_4f_leptonDecays_TuneCP5down_13TeV-amcatnlo-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (0.0000000000000000000);    // [pb]
  //else if(filename.Contains("ST_s-channel_4f_leptonDecays_TuneCP5up_13TeV-amcatnlo-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (0.0000000000000000000);    // [pb]
  //else if(filename.Contains("ST_s-channel_4f_leptonDecays_mtop1695_TuneCP5_PSweights_13TeV-amcatnlo-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (3.991);    // [pb]
  //else if(filename.Contains("ST_s-channel_4f_leptonDecays_mtop1715_TuneCP5_PSweights_13TeV-amcatnlo-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (3.824);    // [pb]
  //else if(filename.Contains("ST_s-channel_4f_leptonDecays_mtop1735_TuneCP5_PSweights_13TeV-amcatnlo-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (3.653);    // [pb]
  //else if(filename.Contains("ST_s-channel_4f_leptonDecays_mtop1755_TuneCP5_PSweights_13TeV-amcatnlo-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (3.506);    // [pb]
  //else if(filename.Contains("ST_s-channel_antitop_leptonDecays_13TeV-PSweights_powheg-pythia"))  NormWeight = Lumi * (1.0/NGenEvents) * (0.0000000000000000000);    // [pb]
  //else if(filename.Contains("ST_s-channel_top_leptonDecays_13TeV-PSweights_powheg-pythia"))  NormWeight = Lumi * (1.0/NGenEvents) * (0.0000000000000000000);    // [pb]
  // ......................... 	
  // ......  from Reference for single top s-channel: https://twiki.cern.ch/twiki/bin/view/LHCPhysics/SingleTopRefXsec#Single_top_s_channel_cross_secti
  //                     MSTW2008nlo68cl
  //	        Mref	M= 	M= 	M= 	M= 	
  //	        172.5	169.5	171.5	173.5	175.5	
  //top	        6.35	6.76	6.48	6.22	5.97	
  //Anti-top	3.97	4.24	4.06	3.88	3.72	
  //sum	       10.32	11	10.54	10.1	9.69	
  // ......................... 	
  else if(filename.Contains("ST_s-channel_4f_hadronicDecays_TuneCP5_PSweights_13TeV-amcatnlo-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (6.6);    // [pb]
  else if(filename.Contains("ST_s-channel_4f_leptonDecays_TuneCP5CR1_13TeV-amcatnlo-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (3.7);    // [pb]
  else if(filename.Contains("ST_s-channel_4f_leptonDecays_TuneCP5CR2_13TeV-amcatnlo-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (3.7);    // [pb]
  else if(filename.Contains("ST_s-channel_4f_leptonDecays_TuneCP5_13TeV-amcatnlo-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (3.7);    // [pb]    <=======  What is the TOP mass here? for the moment I assume 172.5 GeV CHECK !!!
  else if(filename.Contains("ST_s-channel_4f_leptonDecays_TuneCP5_PSweights_13TeV-amcatnlo-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (3.7);    // [pb]
  else if(filename.Contains("ST_s-channel_4f_leptonDecays_TuneCP5down_13TeV-amcatnlo-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (0.0000000000000000000);    // [pb]
  else if(filename.Contains("ST_s-channel_4f_leptonDecays_TuneCP5up_13TeV-amcatnlo-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (0.0000000000000000000);    // [pb]
  else if(filename.Contains("ST_s-channel_4f_leptonDecays_mtop1695_TuneCP5_PSweights_13TeV-amcatnlo-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (4.24);    // [pb]
  else if(filename.Contains("ST_s-channel_4f_leptonDecays_mtop1715_TuneCP5_PSweights_13TeV-amcatnlo-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (4.06);    // [pb]
  else if(filename.Contains("ST_s-channel_4f_leptonDecays_mtop1735_TuneCP5_PSweights_13TeV-amcatnlo-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (3.88);    // [pb]
  else if(filename.Contains("ST_s-channel_4f_leptonDecays_mtop1755_TuneCP5_PSweights_13TeV-amcatnlo-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (3.72);    // [pb]
  // THIS VALUES ARE WRONG... THEY CORRESPOND TO THE INCLUSIVE DECAYS
  else if(filename.Contains("ST_s-channel_antitop_leptonDecays_13TeV-PSweights_powheg-pythia"))  NormWeight = Lumi * (1.0/NGenEvents) * (3.97);    // [pb]
  else if(filename.Contains("ST_s-channel_top_leptonDecays_13TeV-PSweights_powheg-pythia"))  NormWeight = Lumi * (1.0/NGenEvents) * (6.35);    // [pb]
  else if(filename.Contains("ST_s-channel_4f_InclusiveDecays_13TeV-amcatnlo-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (10.12);    // [pb]




  // ......................... 	
  // ......  from XDB ........
  // ......................... 	
  //else if(filename.Contains("ST_t-channel_antitop_4f_InclusiveDecays_TuneCP5_13TeV-powheg-madspin-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (0.00000000000000000);    // [pb]
  //else if(filename.Contains("ST_t-channel_antitop_4f_InclusiveDecays_TuneCP5_PSweights_13TeV-powheg-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (0.00000000000000000);    // [pb]
  //else if(filename.Contains("ST_t-channel_antitop_4f_InclusiveDecays_TuneCP5down_13TeV-powheg-madspin-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (0.00000000000000000);    // [pb]
  //else if(filename.Contains("ST_t-channel_antitop_4f_InclusiveDecays_TuneCP5down_PSweights_13TeV-powheg-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (0.00000000000000000);    // [pb]
  //else if(filename.Contains("ST_t-channel_antitop_4f_InclusiveDecays_TuneCP5up_13TeV-powheg-madspin-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (0.00000000000000000);    // [pb]
  //else if(filename.Contains("ST_t-channel_antitop_4f_InclusiveDecays_TuneCP5up_PSweights_13TeV-powheg-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (0.00000000000000000);    // [pb]
  //else if(filename.Contains("ST_t-channel_antitop_4f_inclusiveDecays_TuneCP5_13TeV-powhegV2-madspin-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (67.91);    // [pb]
  //else if(filename.Contains("ST_t-channel_antitop_5f_TuneCP5_13TeV-powheg-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (0.00000000000000000);    // [pb]
  //else if(filename.Contains("ST_t-channel_antitop_5f_TuneCP5_PSweights_13TeV-powheg-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (71.74);    // [pb]

  //else if(filename.Contains("ST_t-channel_top_4f_InclusiveDecays_TuneCP5_13TeV-powheg-madspin-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (0.00000000000000000);    // [pb]
  //else if(filename.Contains("ST_t-channel_top_4f_InclusiveDecays_TuneCP5_PSweights_13TeV-powheg-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (0.00000000000000000);    // [pb]
  //else if(filename.Contains("ST_t-channel_top_4f_InclusiveDecays_TuneCP5down_13TeV-powheg-madspin-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (0.00000000000000000);    // [pb]
  //else if(filename.Contains("ST_t-channel_top_4f_InclusiveDecays_TuneCP5down_PSweights_13TeV-powheg-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (0.00000000000000000);    // [pb]
  //else if(filename.Contains("ST_t-channel_top_4f_InclusiveDecays_TuneCP5up_13TeV-powheg-madspin-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (0.00000000000000000);    // [pb]
  //else if(filename.Contains("ST_t-channel_top_4f_InclusiveDecays_TuneCP5up_PSweights_13TeV-powheg-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (0.00000000000000000);    // [pb]
  //else if(filename.Contains("ST_t-channel_top_5f_TuneCP5_13TeV-powheg-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (119.7);    // [pb]
  // ......................... 	
  // Reference for single top t-channel: https://twiki.cern.ch/twiki/bin/view/LHCPhysics/SingleTopRefXsec#Single_top_t_channel_cross_secti  
  //                     MSTW2008nlo68cl
  //     	Mref	M= 	M= 	M= 	M= 
  //    	172.5	169.5	171.5	173.5	175.5
  //  top	137.6	140.91	138.69	136.52	134.4
  // Anti-top	82.67	84.79	83.37	81.98	80.62
  // sum	220.27	225.7	222.06	218.5	215.02
  // ......................... 	


  else if(filename.Contains("ST_t-channel_antitop_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (82.67);    // [pb]

  else if(filename.Contains("ST_t-channel_antitop_4f_InclusiveDecays_TuneCP5_13TeV-powheg-madspin-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (82.67);    // [pb]
  else if(filename.Contains("ST_t-channel_antitop_4f_InclusiveDecays_TuneCP5_PSweights_13TeV-powheg-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (82.67);    // [pb]
  else if(filename.Contains("ST_t-channel_antitop_4f_InclusiveDecays_TuneCP5down_13TeV-powheg-madspin-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (82.67);    // [pb]
  else if(filename.Contains("ST_t-channel_antitop_4f_InclusiveDecays_TuneCP5down_PSweights_13TeV-powheg-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (82.67);    // [pb]
  else if(filename.Contains("ST_t-channel_antitop_4f_InclusiveDecays_TuneCP5up_13TeV-powheg-madspin-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (82.67);    // [pb]
  else if(filename.Contains("ST_t-channel_antitop_4f_InclusiveDecays_TuneCP5up_PSweights_13TeV-powheg-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (82.67);    // [pb]
  else if(filename.Contains("ST_t-channel_antitop_4f_inclusiveDecays_TuneCP5_13TeV-powhegV2-madspin-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (82.67);    // [pb]
  
  else if(filename.Contains("ST_t-channel_antitop_4f_InclusiveDecays_TuneCP5CR1_13TeV-powheg-madspin-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (82.67);    // [pb]
  else if(filename.Contains("ST_t-channel_antitop_4f_InclusiveDecays_TuneCP5CR1_PSweights_13TeV-powheg-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (82.67);    // [pb]
  else if(filename.Contains("ST_t-channel_antitop_4f_InclusiveDecays_TuneCP5CR2_13TeV-powheg-madspin-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (82.67);    // [pb]
  else if(filename.Contains("ST_t-channel_antitop_4f_InclusiveDecays_TuneCP5CR2_PSweights_13TeV-powheg-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (82.67);    // [pb]
  else if(filename.Contains("ST_t-channel_antitop_4f_InclusiveDecays_TuneCP5_erdON_13TeV-powheg-madspin-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (82.67);    // [pb]
  else if(filename.Contains("ST_t-channel_antitop_4f_InclusiveDecays_TuneCP5_erdON_PSweights_13TeV-powheg-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (82.67);    // [pb]
  else if(filename.Contains("ST_t-channel_antitop_4f_hdampdown_InclusiveDecays_TuneCP5_13TeV-powheg-madspin-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (82.67);    // [pb]
  else if(filename.Contains("ST_t-channel_antitop_4f_hdampdown_InclusiveDecays_TuneCP5_PSweights_13TeV-powheg-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (82.67);    // [pb]
  else if(filename.Contains("ST_t-channel_antitop_4f_hdampup_InclusiveDecays_TuneCP5_13TeV-powheg-madspin-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (82.67);    // [pb]
  else if(filename.Contains("ST_t-channel_antitop_4f_hdampup_InclusiveDecays_TuneCP5_PSweights_13TeV-powheg-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (82.67);    // [pb]
   
  else if(filename.Contains("ST_t-channel_antitop_5f_TuneCP5_13TeV-powheg-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (82.67);    // [pb]
  else if(filename.Contains("ST_t-channel_antitop_5f_TuneCP5_PSweights_13TeV-powheg-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (82.67);    // [pb]

  else if(filename.Contains("ST_t-channel_top_4f_InclusiveDecays_TuneCP5_13TeV-powheg-madspin-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (137.6);    // [pb]
  else if(filename.Contains("ST_t-channel_top_4f_InclusiveDecays_TuneCP5_PSweights_13TeV-powheg-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (137.6);    // [pb]
  else if(filename.Contains("ST_t-channel_top_4f_InclusiveDecays_TuneCP5down_13TeV-powheg-madspin-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (137.6);    // [pb]
  else if(filename.Contains("ST_t-channel_top_4f_InclusiveDecays_TuneCP5down_PSweights_13TeV-powheg-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (137.6);    // [pb]
  else if(filename.Contains("ST_t-channel_top_4f_InclusiveDecays_TuneCP5up_13TeV-powheg-madspin-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (137.6);    // [pb]
  else if(filename.Contains("ST_t-channel_top_4f_InclusiveDecays_TuneCP5up_PSweights_13TeV-powheg-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (137.6);    // [pb]
  else if(filename.Contains("ST_t-channel_top_5f_TuneCP5_13TeV-powheg-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (137.6);    // [pb]

  else if(filename.Contains("ST_t-channel_top_4f_InclusiveDecays_TuneCP5CR1_13TeV-powheg-madspin-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (137.6);    // [pb]
  else if(filename.Contains("ST_t-channel_top_4f_InclusiveDecays_TuneCP5CR1_PSweights_13TeV-powheg-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (137.6);    // [pb]
  else if(filename.Contains("ST_t-channel_top_4f_InclusiveDecays_TuneCP5CR2_13TeV-powheg-madspin-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (137.6);    // [pb]
  else if(filename.Contains("ST_t-channel_top_4f_InclusiveDecays_TuneCP5CR2_PSweights_13TeV-powheg-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (137.6);    // [pb]
  else if(filename.Contains("ST_t-channel_top_4f_InclusiveDecays_TuneCP5_erdON_13TeV-powheg-madspin-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (137.6);    // [pb]
  else if(filename.Contains("ST_t-channel_top_4f_InclusiveDecays_TuneCP5_erdON_PSweights_13TeV-powheg-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (137.6);    // [pb]
  else if(filename.Contains("ST_t-channel_top_4f_hdampdown_InclusiveDecays_TuneCP5_13TeV-powheg-madspin-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (137.6);    // [pb]
  else if(filename.Contains("ST_t-channel_top_4f_hdampdown_InclusiveDecays_TuneCP5_PSweights_13TeV-powheg-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (137.6);    // [pb]
  else if(filename.Contains("ST_t-channel_top_4f_hdampup_InclusiveDecays_TuneCP5_13TeV-powheg-madspin-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (137.6);    // [pb]
  else if(filename.Contains("ST_t-channel_top_4f_hdampup_InclusiveDecays_TuneCP5_PSweights_13TeV-powheg-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (137.6);    // [pb]




  // ......................... 	
  // ......  from XDB ........
  // ......................... 	 
  //else if(filename.Contains("ST_tW_antitop_5f_DS_inclusiveDecays_TuneCP5_PSweights_13TeV-powheg-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (0.00000000000000000);    // [pb]
  //else if(filename.Contains("ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M2T4"))  NormWeight = Lumi * (1.0/NGenEvents) * (38.06);    // [pb]
  //else if(filename.Contains("ST_tW_antitop_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (34.97);    // [pb]
  //else if(filename.Contains("ST_tW_antitop_5f_inclusiveDecays_TuneCP5_PSweights_13TeV-powheg-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (34.97);    // [pb]
  //else if(filename.Contains("ST_tW_antitop_5f_inclusiveDecays_TuneCP5down_13TeV-powheg-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (0.00000000000000000);    // [pb]
  //else if(filename.Contains("ST_tW_antitop_5f_inclusiveDecays_TuneCP5down_PSweights_13TeV-powheg-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (0.00000000000000000);    // [pb]
  //else if(filename.Contains("ST_tW_antitop_5f_inclusiveDecays_TuneCP5up_13TeV-powheg-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (0.00000000000000000);    // [pb]
  //else if(filename.Contains("ST_tW_antitop_5f_inclusiveDecays_TuneCP5up_PSweights_13TeV-powheg-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (0.00000000000000000);    // [pb]
  //else if(filename.Contains("ST_tW_antitop_5f_inclusiveDecays_mtop1695_TuneCP5_PSweights_13TeV-powheg-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (36.65);    // [pb]
  //else if(filename.Contains("ST_tW_antitop_5f_inclusiveDecays_mtop1715_TuneCP5_PSweights_13TeV-powheg-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (35.52);    // [pb]
  //else if(filename.Contains("ST_tW_antitop_5f_inclusiveDecays_mtop1735_TuneCP5_PSweights_13TeV-powheg-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (34.44);    // [pb]
  //else if(filename.Contains("ST_tW_antitop_5f_inclusiveDecays_mtop1755_TuneCP5_PSweights_13TeV-powheg-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * ();    // [pb]

  //else if(filename.Contains("ST_tW_top_5f_DS_inclusiveDecays_TuneCP5_PSweights_13TeV-powheg-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (0.00000000000000000);    // [pb]
  //else if(filename.Contains("ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M2T4"))  NormWeight = Lumi * (1.0/NGenEvents) * (38.09);    // [pb]
  //else if(filename.Contains("ST_tW_top_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (34.91);    // [pb]
  //else if(filename.Contains("ST_tW_top_5f_inclusiveDecays_TuneCP5_PSweights_13TeV-powheg-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (34.91);    // [pb]
  //else if(filename.Contains("ST_tW_top_5f_inclusiveDecays_TuneCP5down_PSweights_13TeV-powheg-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (0.00000000000000000);    // [pb]
  //else if(filename.Contains("ST_tW_top_5f_inclusiveDecays_TuneCP5up_PSweights_13TeV-powheg-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (0.00000000000000000);    // [pb]
  //else if(filename.Contains("ST_tW_top_5f_inclusiveDecays_mtop1695_TuneCP5_PSweights_13TeV-powheg-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (36.58);    // [pb]
  //else if(filename.Contains("ST_tW_top_5f_inclusiveDecays_mtop1715_TuneCP5_PSweights_13TeV-powheg-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (35.46);    // [pb]
  //else if(filename.Contains("ST_tW_top_5f_inclusiveDecays_mtop1735_TuneCP5_PSweights_13TeV-powheg-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (0.00000000000000000);    // [pb]
  //else if(filename.Contains("ST_tW_top_5f_inclusiveDecays_mtop1755_TuneCP5_PSweights_13TeV-powheg-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (0.00000000000000000);    // [pb]
  // ......................... 	
  // Reference for single top tW: https://twiki.cern.ch/twiki/bin/view/LHCPhysics/SingleTopRefXsec#Single_top_Wt_channel_cross_sect 
  //                     MSTW2008nlo68cl
  //     	Mref	M= 	M= 	M= 	M= 
  //    	172.5	169.5	171.5	173.5	175.5
  //top+antitop	71.7	75.12	72.82	70.6	68.46
  // ......................... 	
  else if(filename.Contains("ST_tW_antitop_5f_DS_inclusiveDecays_TuneCP5_PSweights_13TeV-powheg-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (71.7/2.0);    // [pb]
  else if(filename.Contains("ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M2T4"))  NormWeight = Lumi * (1.0/NGenEvents) * (71.7/2.0);    // [pb]
  else if(filename.Contains("ST_tW_antitop_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (71.7/2.0);    // [pb]
  else if(filename.Contains("ST_tW_antitop_5f_inclusiveDecays_TuneCP5_MERGED_13TeV-powheg-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (71.7/2.0);    // [pb]
  else if(filename.Contains("ST_tW_antitop_5f_inclusiveDecays_TuneCP5_PSweights_13TeV-powheg-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (71.7/2.0);    // [pb]
  else if(filename.Contains("ST_tW_antitop_5f_inclusiveDecays_TuneCP5down_13TeV-powheg-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (0.00000000000000000);    // [pb]
  else if(filename.Contains("ST_tW_antitop_5f_inclusiveDecays_TuneCP5down_PSweights_13TeV-powheg-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (0.00000000000000000);    // [pb]
  else if(filename.Contains("ST_tW_antitop_5f_inclusiveDecays_TuneCP5up_13TeV-powheg-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (0.00000000000000000);    // [pb]
  else if(filename.Contains("ST_tW_antitop_5f_inclusiveDecays_TuneCP5up_PSweights_13TeV-powheg-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (0.00000000000000000);    // [pb]
  else if(filename.Contains("ST_tW_antitop_5f_inclusiveDecays_mtop1695_TuneCP5_PSweights_13TeV-powheg-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (75.12/2.0);    // [pb]
  else if(filename.Contains("ST_tW_antitop_5f_inclusiveDecays_mtop1715_TuneCP5_PSweights_13TeV-powheg-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (72.82/2.0);    // [pb]
  else if(filename.Contains("ST_tW_antitop_5f_inclusiveDecays_mtop1735_TuneCP5_PSweights_13TeV-powheg-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (70.6/2.0);    // [pb]
  else if(filename.Contains("ST_tW_antitop_5f_inclusiveDecays_mtop1755_TuneCP5_PSweights_13TeV-powheg-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (68.46/2.0);    // [pb]

  else if(filename.Contains("ST_tW_top_5f_DS_inclusiveDecays_TuneCP5_PSweights_13TeV-powheg-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (71.7/2.0);    // [pb]
  else if(filename.Contains("ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M2T4"))  NormWeight = Lumi * (1.0/NGenEvents) * (71.7/2.0);    // [pb]
  else if(filename.Contains("ST_tW_top_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (71.7/2.0);    // [pb]
  else if(filename.Contains("ST_tW_top_5f_inclusiveDecays_TuneCP5_PSweights_13TeV-powheg-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (71.7/2.0);    // [pb]
  else if(filename.Contains("ST_tW_top_5f_inclusiveDecays_TuneCP5down_PSweights_13TeV-powheg-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (0.00000000000000000);    // [pb]
  else if(filename.Contains("ST_tW_top_5f_inclusiveDecays_TuneCP5up_PSweights_13TeV-powheg-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (0.00000000000000000);    // [pb]
  else if(filename.Contains("ST_tW_top_5f_inclusiveDecays_mtop1695_TuneCP5_PSweights_13TeV-powheg-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (75.12/2.0);    // [pb]
  else if(filename.Contains("ST_tW_top_5f_inclusiveDecays_mtop1715_TuneCP5_PSweights_13TeV-powheg-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (72.82/2.0);    // [pb]
  else if(filename.Contains("ST_tW_top_5f_inclusiveDecays_mtop1735_TuneCP5_PSweights_13TeV-powheg-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (70.6/2.0);    // [pb]
  else if(filename.Contains("ST_tW_top_5f_inclusiveDecays_mtop1755_TuneCP5_PSweights_13TeV-powheg-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (68.46/2.0);    // [pb]





  //=======================================================  TT signal  ==============================================================

  // ......................... 	
  // ......  from XDB ........
  // ......................... 	 
  //else if(filename.Contains("TT_DiLept_TuneCP5_13TeV-amcatnlo-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (0.00000000000000000);    // [pb]
  //else if(filename.Contains("TT_TuneCUETP8M2T4_13TeV-powheg-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (730.6);    // [pb]
  //else if(filename.Contains("TTJets_DiLept_TuneCP5_13TeV-madgraphMLM-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (54.17);    // [pb]
  //else if(filename.Contains("TTJets_SingleLeptFromTbar_TuneCP5_13TeV-madgraphMLM-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (0.00000000000000000);    // [pb]
  //else if(filename.Contains("TTJets_TuneCP5_13TeV-amcatnloFXFX-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (831.76);    // [pb]
  //else if(filename.Contains("TTJets_TuneCP5_13TeV-madgraphMLM-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (496.1);    // [pb]
  //else if(filename.Contains("TTToSemiLeptonic_TuneCP2_PSweights_13TeV-powheg-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (0.00000000000000000);    // [pb]
  //else if(filename.Contains("TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (687.1);    // [pb]
  //else if(filename.Contains("TTToSemiLeptonic_TuneCP5_PSweights_13TeV-powheg-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (687.1);    // [pb]
  //else if(filename.Contains("TTToSemiLeptonic_TuneCP5_erdON_13TeV-powheg-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (0.00000000000000000);    // [pb]
  //else if(filename.Contains("TTToSemiLeptonic_TuneCP5down_13TeV-powheg-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (0.00000000000000000);    // [pb]
  //else if(filename.Contains("TTToSemiLeptonic_TuneCP5up_13TeV-powheg-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (0.00000000000000000);    // [pb]
  //else if(filename.Contains("TTToSemiLeptonic_hdampDOWN_TuneCP5_13TeV-powheg-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (0.00000000000000000);    // [pb]
  //else if(filename.Contains("TTToSemiLeptonic_hdampUP_TuneCP5_13TeV-powheg-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (0.00000000000000000);    // [pb]
  //else if(filename.Contains("TTToSemiLeptonic_mtop166p5_TuneCP5_13TeV-powheg-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (811.4);    // [pb]
  //else if(filename.Contains("TTToSemiLeptonic_mtop166p5_TuneCP5_PSweights_13TeV-powheg-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (811.4);    // [pb]
  //else if(filename.Contains("TTToSemiLeptonic_mtop169p5_TuneCP5_13TeV-powheg-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (0.00000000000000000);    // [pb]
  //else if(filename.Contains("TTToSemiLeptonic_mtop169p5_TuneCP5_PSweights_13TeV-powheg-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (746.2);    // [pb]
  //else if(filename.Contains("TTToSemiLeptonic_mtop171p5_TuneCP5_13TeV-powheg-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (0.00000000000000000);    // [pb]
  //else if(filename.Contains("TTToSemiLeptonic_mtop173p5_TuneCP5_13TeV-powheg-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (0.00000000000000000);    // [pb]
  //else if(filename.Contains("TTToSemiLeptonic_mtop173p5_TuneCP5_PSweights_13TeV-powheg-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (668.6);    // [pb]
  //else if(filename.Contains("TTToSemiLeptonic_mtop175p5_TuneCP5_13TeV-powheg-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (0.00000000000000000);    // [pb]
  //else if(filename.Contains("TTToSemiLeptonic_mtop175p5_TuneCP5_PSweights_13TeV-powheg-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (633.4);    // [pb]
  //else if(filename.Contains("TTToSemiLeptonic_mtop178p5_TuneCP5_13TeV-powheg-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (584.6);    // [pb]
  // ......................... 	
  // Reference from https://twiki.cern.ch/twiki/bin/view/LHCPhysics/TtbarNNLO
  //                     MSTW2008nlo68cl
  //     	Mref	M= 	M= 	M= 	M= 
  //    	172.5	169.5	171.5	173.5	175.5     166.5	  178.5
  //  top       831.76  903.37	854.87	809.38	766.71    982.34  707.54
  // semilept   365.52	396.99	375.67	355.68	336.93    431.69  310.93
  // ......................... 	
  else if(filename.Contains("TT_DiLept_TuneCP5_13TeV-amcatnlo-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (88.2);    // [pb] 831*(0.326^2)
  else if(filename.Contains("TT_TuneCUETP8M2T4_13TeV-powheg-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (831.76);    // [pb]
  else if(filename.Contains("TTJets_DiLept_TuneCP5_13TeV-madgraphMLM-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (88.2);    // [pb] 831*(0.326^2)
  else if(filename.Contains("TTJets_SingleLeptFromTbar_TuneCP5_13TeV-madgraphMLM-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (365.52);    // [pb] Xsec*Br(lep+Jets) = (831.76) * 2[(0.1086*3) * (0.67)] = 
  else if(filename.Contains("TTJets_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (831.76);    // [pb]
  else if(filename.Contains("TTJets_TuneCP5_13TeV-amcatnloFXFX-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (831.76);    // [pb]
  else if(filename.Contains("TTJets_TuneCP5_13TeV-madgraphMLM-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (831.76);    // [pb]
  else if(filename.Contains("TTToSemiLeptonic_TuneCP2_PSweights_13TeV-powheg-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (365.52);    // [pb]
  else if(filename.Contains("TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8")) NormWeight = Lumi * (1.0/NGenEvents) * (88.2);    // [pb]
  else if(filename.Contains("TTTo2L2Nu_TuneCP5_MERGED_13TeV-powheg-pythia8")) NormWeight = Lumi * (1.0/NGenEvents) * (88.2);    // [pb]
  else if(filename.Contains("TTTo2L2Nu_TuneCP5_PSweights_13TeV-powheg-pythia8")) NormWeight = Lumi * (1.0/NGenEvents) * (88.2);    // [pb]
  else if(filename.Contains("TTToHadronic_TuneCP5_13TeV-powheg-pythia8")) NormWeight = Lumi * (1.0/NGenEvents) * (380.2);    // [pb]
  else if(filename.Contains("TTToHadronic_TuneCP5_PSweights_13TeV-powheg-pythia8")) NormWeight = Lumi * (1.0/NGenEvents) * (380.2);    // [pb]
  else if(filename.Contains("TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8")) NormWeight = Lumi * (1.0/NGenEvents) * (365.52);    // [pb]
  else if(filename.Contains("TTToSemiLeptonic_TuneCP5_PSweights_13TeV-powheg-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (365.52);    // [pb]
  else if(filename.Contains("TTToSemiLeptonic_TuneCP5_MERGED_13TeV-powheg-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (365.52);    // [pb]
  else if(filename.Contains("TTToSemiLeptonic_TuneCP5_erdON_13TeV-powheg-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (365.52);    // [pb]
  else if(filename.Contains("TTToSemiLeptonic_TuneCP5_PSweights_erdON_13TeV-powheg-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (365.52);    // [pb]
  else if(filename.Contains("TTToSemiLeptonic_TuneCP5down_13TeV-powheg-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (365.52);    // [pb]
  else if(filename.Contains("TTToSemiLeptonic_TuneCP5down_PSweights_13TeV-powheg-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (365.52);    // [pb]
  else if(filename.Contains("TTToSemiLeptonic_TuneCP5up_13TeV-powheg-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (365.52);    // [pb]
  else if(filename.Contains("TTToSemiLeptonic_TuneCP5up_PSweights_13TeV-powheg-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (365.52);    // [pb]
  
  else if(filename.Contains("TTToSemiLeptonic_hdampDOWN_TuneCP5_13TeV-powheg-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (365.52);    // [pb]
  else if(filename.Contains("TTToSemiLeptonic_hdampDOWN_TuneCP5_PSweights_13TeV-powheg-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (365.52);    // [pb]
  else if(filename.Contains("TTToSemiLeptonic_hdampUP_TuneCP5_13TeV-powheg-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (365.52);    // [pb]
  else if(filename.Contains("TTToSemiLeptonic_hdampUP_TuneCP5_PSweights_13TeV-powheg-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (365.52);    // [pb]

  else if(filename.Contains("TTToSemiLeptonic_mtop166p5_TuneCP5_13TeV-powheg-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (431.69);    // [pb]
  else if(filename.Contains("TTToSemiLeptonic_mtop166p5_TuneCP5_PSweights_13TeV-powheg-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (431.69);    // [pb]
  else if(filename.Contains("TTToSemiLeptonic_mtop169p5_TuneCP5_13TeV-powheg-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (396.99);    // [pb]
  else if(filename.Contains("TTToSemiLeptonic_mtop169p5_TuneCP5_PSweights_13TeV-powheg-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (396.99);    // [pb]
  else if(filename.Contains("TTToSemiLeptonic_mtop171p5_TuneCP5_13TeV-powheg-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (375.67);    // [pb]
  else if(filename.Contains("TTToSemiLeptonic_mtop173p5_TuneCP5_13TeV-powheg-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (355.68);    // [pb]
  else if(filename.Contains("TTToSemiLeptonic_mtop173p5_TuneCP5_PSweights_13TeV-powheg-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (355.68);    // [pb]
  else if(filename.Contains("TTToSemiLeptonic_mtop175p5_TuneCP5_13TeV-powheg-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (336.93);    // [pb]
  else if(filename.Contains("TTToSemiLeptonic_mtop175p5_TuneCP5_PSweights_13TeV-powheg-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (336.93);    // [pb]
  else if(filename.Contains("TTToSemiLeptonic_mtop178p5_TuneCP5_13TeV-powheg-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (310.93);    // [pb]

  else if(filename.Contains("TTToSemiLeptonic_TuneCP5CR1_QCDbased_PSweights_13TeV-powheg-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (365.52);    // [pb]
  else if(filename.Contains("TTToSemiLeptonic_TuneCP5CR2_GluonMove_PSweights_13TeV-powheg-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (365.52);    // [pb]

  else if(filename.Contains("TTToSemiLeptonic_TuneCP5CR1_QCDbased_13TeV-powheg-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (365.52);    // [pb]
  else if(filename.Contains("TTToSemiLeptonic_TuneCP5CR2_GluonMove_13TeV-powheg-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (365.52);    // [pb]

  // Fake values for Higgs (can be corrected afterwards)
  else if(filename.Contains("ttH_M125_TuneCP5_13TeV_powheg-pythia8"))                  NormWeight = Lumi * (1.0/NGenEvents) * (0.527);  // [pb] (GEN value)
  else if(filename.Contains("ttHTobb_ttTo2L2Nu_M125_TuneCP5_13TeV_powheg-pythia8"))    NormWeight = Lumi * (1.0/NGenEvents) * (0.011);  // [pb]
  else if(filename.Contains("ttHTobb_ttToSemiLep_M125_TuneCP5_13TeV_powheg-pythia8"))  NormWeight = Lumi * (1.0/NGenEvents) * (0.011);  // [pb]
  else if(filename.Contains("ttHToNonbb_M125_TuneCP5_13TeV_powheg-pythia8"))           NormWeight = Lumi * (1.0/NGenEvents) * (0.212);  // [pb] ??
  else if(filename.Contains("VBFHToWWTo2L2Nu_TuneCP5_13TeV_powheg-pythia8"))           NormWeight = Lumi * (1.0/NGenEvents) * (10.);    // [pb]
  else if(filename.Contains("VBFHToWWToLNuQQ_TuneCP5_13TeV_powheg-pythia8"))           NormWeight = Lumi * (1.0/NGenEvents) * (10.);    // [pb]
  else if(filename.Contains("ggHToWWToLNuQQ_TuneCP5_13TeV_powheg-pythia8"))            NormWeight = Lumi * (1.0/NGenEvents) * (10.);    // [pb]

  else{
    std::cout << "Cross section for " << filename << " not found. Include it in plugins/SFLumi.cc" << std::endl;
    std::exit (EXIT_FAILURE);
  }


  return NormWeight;
}

