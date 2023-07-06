#include <TLatex.h>

float TotalError(float Syst, float Stat){
  float Total = Syst*Syst + Stat*Stat;
  return sqrt(Total);
}

void SetupGraph(TGraphErrors *Gr, int Color = 2, int Mark = 20, int Line = 3 ){

  Gr->SetTitle("");
  Gr->GetYaxis()->SetTitleSize(0.0);
  Gr->GetYaxis()->SetLabelSize(0.0);
  Gr->GetYaxis()->SetNdivisions(0);

  Gr->SetLineColor(1);
  Gr->SetLineWidth(Line);
  Gr->SetMarkerColor(Color);
  Gr->SetMarkerStyle(Mark);
  Gr->SetMarkerSize(1.2);

}

void redrawBorder()
{
   // this little macro redraws the axis tick marks and the pad border lines.
   gPad->Update();
   gPad->RedrawAxis();
   TLine l;
   l.DrawLine(gPad->GetUxmin(), gPad->GetUymax(), gPad->GetUxmax(), gPad->GetUymax());
   l.DrawLine(gPad->GetUxmax(), gPad->GetUymin(), gPad->GetUxmax(), gPad->GetUymax());
}

void CreateSummaryPlots(RooArgList FitPar, TString OutDir){

  int npar=4, nmeas=5, npoints=1;
  // Parameters
  enum {xsec=0, F0, FL, FR};
  // Meas
  enum {Theory=0, meas, CMS, LHC, ATLAS13TeV};
  
  Int_t cerror = 1757;
  TColor *colerror = new TColor(cerror, 0.7, 0., 0., "", 0.3); // alpha

  int markcolor [nmeas];
  for(int i=0; i<nmeas;i++) markcolor[i]=1;
  int markpoint [nmeas];
  markpoint[Theory]     =  0;
  markpoint[CMS]        = 22;
  markpoint[LHC]        = 21;
  markpoint[ATLAS13TeV] = 33;
  markpoint[meas]       = 20;

  float xsec_o =  720,  xsec_f = 920;
  float F0_o   =  0.60, F0_f   = 0.75;
  float FL_o   =  0.28, FL_f   = 0.36;
  float FR_o   = -0.05, FR_f   = 0.05;
  // __________________________________________________________________________________________
  // __________________________________________________________________________________________
  // [Par][Meas][Point]
  float Central [npar][nmeas][npoints];
  float ErrorSta[npar][nmeas][npoints];
  float ErrorSys[npar][nmeas][npoints];
  float Error   [npar][nmeas][npoints];

  // __________________________________________________________________________________________
  // From TOP++ v2.0
  Central [xsec][Theory][0] = 832;
  ErrorSys[xsec][Theory][0] = 46.;
  ErrorSta[xsec][Theory][0] =  0.;
  Error   [xsec][Theory][0] = TotalError(ErrorSys[xsec][Theory][0],ErrorSta[xsec][Theory][0]);
  // -------------------------------------
  // From https://arxiv.org/pdf/1005.2625.pdf
  Central [F0][Theory][0] = 0.687;
  ErrorSta[F0][Theory][0] = 0.000;
  ErrorSys[F0][Theory][0] = 0.005;
  Error   [F0][Theory][0] = TotalError(ErrorSys[F0][Theory][0],ErrorSta[F0][Theory][0]);

  Central [FL][Theory][0] = 0.311;
  ErrorSta[FL][Theory][0] = 0.000;
  ErrorSys[FL][Theory][0] = 0.005;
  Error   [FL][Theory][0] = TotalError(ErrorSys[FL][Theory][0],ErrorSta[FL][Theory][0]);

  Central [FR][Theory][0] = 0.0017;
  ErrorSta[FR][Theory][0] = 0.0000;
  ErrorSys[FR][Theory][0] = 0.0001*15;
  Error   [FR][Theory][0] = TotalError(ErrorSys[FR][Theory][0],ErrorSta[FR][Theory][0]);
  // __________________________________________________________________________________________
  // From https://twiki.cern.ch/twiki/pub/CMSPublic/PhysicsResultsTOPSummaryFigures/tt_xsec_cms_13TeV.pdf (Jun 21)
  Central [xsec][CMS][0] = 791;
  ErrorSta[xsec][CMS][0] = 01.;
  ErrorSys[xsec][CMS][0] = 25.;
  Error   [xsec][CMS][0] = TotalError(ErrorSys[xsec][CMS][0],ErrorSta[xsec][CMS][0]);
  // -------------------------------------
  // From https://arxiv.org/abs/1605.09047
  Central [F0][CMS][0] = 0.681;
  ErrorSta[F0][CMS][0] = 0.012;
  ErrorSys[F0][CMS][0] = 0.023;
  Error   [F0][CMS][0] = TotalError(ErrorSys[F0][CMS][0],ErrorSta[F0][CMS][0]);

  Central [FL][CMS][0] = 0.323;
  ErrorSta[FL][CMS][0] = 0.008;
  ErrorSys[FL][CMS][0] = 0.014;
  Error   [FL][CMS][0] = TotalError(ErrorSys[FL][CMS][0],ErrorSta[FL][CMS][0]);

  Central [FR][CMS][0] = -0.004;
  ErrorSta[FR][CMS][0] =  0.005;
  ErrorSys[FR][CMS][0] =  0.014;
  Error   [FR][CMS][0] = TotalError(ErrorSys[FR][CMS][0],ErrorSta[FR][CMS][0]);
  // __________________________________________________________________________________________
  // From https://twiki.cern.ch/twiki/pub/CMSPublic/PhysicsResultsTOPSummaryFigures/tt_xsec_cms_13TeV.pdf (Jun 21)
  Central [xsec][LHC][0] = 791;
  ErrorSta[xsec][LHC][0] = 01.;
  ErrorSys[xsec][LHC][0] = 25.;
  Error   [xsec][LHC][0] = TotalError(ErrorSys[xsec][LHC][0],ErrorSta[xsec][LHC][0]);
  // -------------------------------------
  // From https://link.springer.com/content/pdf/10.1007/JHEP08(2020)051.pdf
  Central [F0][LHC][0] = 0.693;
  ErrorSta[F0][LHC][0] = 0.009;
  ErrorSys[F0][LHC][0] = 0.011;
  Error   [F0][LHC][0] = TotalError(ErrorSys[F0][LHC][0],ErrorSta[F0][LHC][0]);

  Central [FL][LHC][0] = 0.315;
  ErrorSta[FL][LHC][0] = 0.006;
  ErrorSys[FL][LHC][0] = 0.009;
  Error   [FL][LHC][0] = TotalError(ErrorSys[FL][LHC][0],ErrorSta[FL][LHC][0]);

  Central [FR][LHC][0] = -0.008;
  ErrorSta[FR][LHC][0] =  0.005;
  ErrorSys[FR][LHC][0] =  0.006;
  Error   [FR][LHC][0] = TotalError(ErrorSys[FR][LHC][0],ErrorSta[FR][LHC][0]);
  // __________________________________________________________________________________________
  // From https://twiki.cern.ch/twiki/pub/CMSPublic/PhysicsResultsTOPSummaryFigures/tt_xsec_cms_13TeV.pdf (Jun 21)
  Central [xsec][ATLAS13TeV][0] = 791;
  ErrorSta[xsec][ATLAS13TeV][0] = 01.;
  ErrorSys[xsec][ATLAS13TeV][0] = 25.;
  Error   [xsec][ATLAS13TeV][0] = TotalError(ErrorSys[xsec][ATLAS13TeV][0],ErrorSta[xsec][ATLAS13TeV][0]);
  // -------------------------------------
  // From https://atlas.web.cern.ch/Atlas/GROUPS/PHYSICS/CONFNOTES/ATLAS-CONF-2022-063/
  Central [F0][ATLAS13TeV][0] = 0.684;
  ErrorSta[F0][ATLAS13TeV][0] = 0.005;
  ErrorSys[F0][ATLAS13TeV][0] = 0.014;
  Error   [F0][ATLAS13TeV][0] = TotalError(ErrorSys[F0][ATLAS13TeV][0],ErrorSta[F0][ATLAS13TeV][0]);

  Central [FL][ATLAS13TeV][0] = 0.316;
  ErrorSta[FL][ATLAS13TeV][0] = 0.003;
  ErrorSys[FL][ATLAS13TeV][0] = 0.008;
  Error   [FL][ATLAS13TeV][0] = TotalError(ErrorSys[FL][ATLAS13TeV][0],ErrorSta[FL][ATLAS13TeV][0]);

  Central [FR][ATLAS13TeV][0] = -0.002;
  ErrorSta[FR][ATLAS13TeV][0] =  0.002;
  ErrorSys[FR][ATLAS13TeV][0] =  0.014;
  Error   [FR][ATLAS13TeV][0] = TotalError(ErrorSys[FR][ATLAS13TeV][0],ErrorSta[FR][ATLAS13TeV][0]);
  // __________________________________________________________________________________________
  RooRealVar *xsec_var, *F0_var, *FL_var;
  xsec_var = (RooRealVar*)FitPar.find("Xsectt_Fit"); // Cross Section
  F0_var   = (RooRealVar*)FitPar.find("F0_Fit");     // F0
  FL_var   = (RooRealVar*)FitPar.find("FL_Fit");     // FL
  // -------------------------------------  
  // From COMBINE
  Central [xsec][meas][0] = xsec_var->getVal();
  ErrorSta[xsec][meas][0] = 0.;
  ErrorSys[xsec][meas][0] = xsec_var->getError();
  Error   [xsec][meas][0] = TotalError(ErrorSys[xsec][meas][0],ErrorSta[xsec][meas][0]);
  // -------------------------------------
  // From COMBINE
  Central [F0][meas][0] = F0_var->getVal();
  ErrorSta[F0][meas][0] = 0.0;
  ErrorSys[F0][meas][0] = F0_var->getError();
  Error   [F0][meas][0] = TotalError(ErrorSys[F0][meas][0],ErrorSta[F0][meas][0]);

  Central [FL][meas][0] = FL_var->getVal();
  ErrorSta[FL][meas][0] = 0.0;
  ErrorSys[FL][meas][0] = FL_var->getError();
  Error   [FL][meas][0] = TotalError(ErrorSys[FL][meas][0],ErrorSta[FL][meas][0]);

  Central [FR][meas][0] = 1. - (Central [F0][meas][0] + Central [FL][meas][0]);
  ErrorSta[FR][meas][0] =  0.01;
  ErrorSys[FR][meas][0] =  0.01;
  Error   [FR][meas][0] = TotalError(ErrorSys[FR][meas][0],ErrorSta[FR][meas][0]);
  // __________________________________________________________________________________________
  // __________________________________________________________________________________________
  /* Error[xsec][meas][0] = 49.4; */
  /* Error[F0][meas][0] = 0.01; */
  /* Error[FL][meas][0] = 0.007; */
  
  float y [nmeas][npoints]; 
  float ye[nmeas][npoints];  

  for(int i=0; i<nmeas;i++) { y[i][0]=nmeas-i; ye[i][0]=0.0;}
  
  // __________________________________________________________________________________________
  // Cross Section
  //__________________________________________________________________________________________

  // Measurement
  TGraphErrors *g_xsec_sta[nmeas];
  TGraphErrors *g_xsec_tot[nmeas];
  g_xsec_sta[meas] = new TGraphErrors(1,Central[xsec][meas],y[meas],ErrorSta[xsec][meas], ye[meas]);
  g_xsec_tot[meas] = new TGraphErrors(1,Central[xsec][meas],y[meas],Error   [xsec][meas], ye[meas]);
  SetupGraph(g_xsec_sta[meas], markcolor [meas], markpoint [meas] );
  SetupGraph(g_xsec_tot[meas], markcolor [meas], markpoint [meas], 1 );
  g_xsec_sta[meas]->GetXaxis()->SetLimits(xsec_o,xsec_f);
  g_xsec_sta[meas]->GetXaxis()->SetLabelOffset(-0.03);
  g_xsec_sta[meas]->GetXaxis()->SetLabelSize(0.08);
  g_xsec_sta[meas]->GetXaxis()->SetLabelFont(42);
  g_xsec_sta[meas]->GetXaxis()->SetNdivisions(406);
  g_xsec_sta[meas]->GetXaxis()->SetTitle("#sigma_{t#kern[0.4]{#bar{t}}} [pb]");
  g_xsec_sta[meas]->GetXaxis()->SetTitleSize(0.12);
  g_xsec_sta[meas]->GetXaxis()->SetTitleOffset(0.45);
  g_xsec_sta[meas]->GetXaxis()->SetTitleFont(42);

  g_xsec_sta[meas]->GetYaxis()->SetRangeUser(0,nmeas);
  // -------------------------------------

  // -------------------------------------
  // Theory -> Band
  TLine *l_xsec = new TLine(Central[xsec][Theory][0], 0, Central[xsec][Theory][0], nmeas);  
  l_xsec->SetLineColor(0);
  l_xsec->SetLineWidth(2);
  l_xsec->SetLineStyle(8);  
  TBox *g_xsec_error = new TBox(Central[xsec][Theory][0] - Error[xsec][Theory][0], 0, Central[xsec][Theory][0] + Error[xsec][Theory][0], nmeas);  
  g_xsec_error->SetFillColor(cerror);
  // -------------------------------------
  
  // -------------------------------------
  // CMS
  g_xsec_sta[CMS] = new TGraphErrors(1,Central[xsec][CMS],y[CMS],ErrorSta[xsec][CMS], ye[CMS]);
  g_xsec_tot[CMS] = new TGraphErrors(1,Central[xsec][CMS],y[CMS],Error   [xsec][CMS], ye[CMS]);
  SetupGraph(g_xsec_sta[CMS], markcolor [CMS+1], markpoint [CMS] );
  SetupGraph(g_xsec_tot[CMS], markcolor [CMS+1], markpoint [CMS], 1 );
  // -------------------------------------

  // __________________________________________________________________________________________
  // F0
  // __________________________________________________________________________________________

  // Measurement
  TGraphErrors *g_F0_sta[nmeas];
  TGraphErrors *g_F0_tot[nmeas];
  g_F0_sta[meas] = new TGraphErrors(1,Central[F0][meas],y[meas],ErrorSta[F0][meas], ye[meas]);
  g_F0_tot[meas] = new TGraphErrors(1,Central[F0][meas],y[meas],Error   [F0][meas], ye[meas]);
  SetupGraph(g_F0_sta[meas], markcolor [meas], markpoint [meas] );
  SetupGraph(g_F0_tot[meas], markcolor [meas], markpoint [meas], 1 );
  g_F0_sta[meas]->GetXaxis()->SetLimits(F0_o, F0_f);
  g_F0_sta[meas]->GetXaxis()->SetLabelOffset(-0.03);
  g_F0_sta[meas]->GetXaxis()->SetLabelSize(0.08);
  g_F0_sta[meas]->GetXaxis()->SetLabelFont(42);
  g_F0_sta[meas]->GetXaxis()->SetNdivisions(505);
  g_F0_sta[meas]->GetXaxis()->SetTitle("F_{0}");
  g_F0_sta[meas]->GetXaxis()->SetTitleSize(0.12);
  g_F0_sta[meas]->GetXaxis()->SetTitleOffset(0.45);
  g_F0_sta[meas]->GetXaxis()->SetTitleFont(42);

  g_F0_sta[meas]->GetYaxis()->SetRangeUser(0,nmeas);
  // -------------------------------------

  // -------------------------------------
  // Theory -> Band
  TLine *l_F0 = new TLine(Central[F0][Theory][0], 0, Central[F0][Theory][0], nmeas);  
  l_F0->SetLineColor(0);
  l_F0->SetLineWidth(2);
  l_F0->SetLineStyle(8);  
  TBox *g_F0_error = new TBox(Central[F0][Theory][0] - Error[F0][Theory][0], 0, Central[F0][Theory][0] + Error[F0][Theory][0], nmeas);  
  g_F0_error->SetFillColor(cerror);
  // -------------------------------------
  
  // -------------------------------------
  // CMS
  g_F0_sta[CMS] = new TGraphErrors(1,Central[F0][CMS],y[CMS],ErrorSta[F0][CMS], ye[CMS]);
  g_F0_tot[CMS] = new TGraphErrors(1,Central[F0][CMS],y[CMS],Error   [F0][CMS], ye[CMS]);
  SetupGraph(g_F0_sta[CMS], markcolor [CMS], markpoint [CMS] );
  SetupGraph(g_F0_tot[CMS], markcolor [CMS], markpoint [CMS], 1 );
  // -------------------------------------

  // -------------------------------------
  // LHC
  g_F0_sta[LHC] = new TGraphErrors(1,Central[F0][LHC],y[LHC],ErrorSta[F0][LHC], ye[LHC]);
  g_F0_tot[LHC] = new TGraphErrors(1,Central[F0][LHC],y[LHC],Error   [F0][LHC], ye[LHC]);
  SetupGraph(g_F0_sta[LHC], markcolor [LHC], markpoint [LHC] );
  SetupGraph(g_F0_tot[LHC], markcolor [LHC], markpoint [LHC], 1 );
  // -------------------------------------

  // -------------------------------------
  // ATLAS13TeV
  g_F0_sta[ATLAS13TeV] = new TGraphErrors(1,Central[F0][ATLAS13TeV],y[ATLAS13TeV],ErrorSta[F0][ATLAS13TeV], ye[ATLAS13TeV]);
  g_F0_tot[ATLAS13TeV] = new TGraphErrors(1,Central[F0][ATLAS13TeV],y[ATLAS13TeV],Error   [F0][ATLAS13TeV], ye[ATLAS13TeV]);
  SetupGraph(g_F0_sta[ATLAS13TeV], markcolor [ATLAS13TeV], markpoint [ATLAS13TeV] );
  SetupGraph(g_F0_tot[ATLAS13TeV], markcolor [ATLAS13TeV], markpoint [ATLAS13TeV], 1 );
  // -------------------------------------

  // __________________________________________________________________________________________
  // FL
  // __________________________________________________________________________________________

  // Measurement
  TGraphErrors *g_FL_sta[nmeas];
  TGraphErrors *g_FL_tot[nmeas];
  g_FL_sta[meas] = new TGraphErrors(1,Central[FL][meas],y[meas],ErrorSta[FL][meas], ye[meas]);
  g_FL_tot[meas] = new TGraphErrors(1,Central[FL][meas],y[meas],Error   [FL][meas], ye[meas]);
  SetupGraph(g_FL_sta[meas], markcolor [meas], markpoint [meas] );
  SetupGraph(g_FL_tot[meas], markcolor [meas], markpoint [meas], 1 );
  g_FL_sta[meas]->GetXaxis()->SetLimits(FL_o, FL_f);
  g_FL_sta[meas]->GetXaxis()->SetLabelOffset(-0.03);
  g_FL_sta[meas]->GetXaxis()->SetLabelSize(0.08);
  g_FL_sta[meas]->GetXaxis()->SetLabelFont(42);
  g_FL_sta[meas]->GetXaxis()->SetNdivisions(406);
  g_FL_sta[meas]->GetXaxis()->SetTitle("F_{L}");
  g_FL_sta[meas]->GetXaxis()->SetTitleSize(0.12);
  g_FL_sta[meas]->GetXaxis()->SetTitleOffset(0.45);
  g_FL_sta[meas]->GetXaxis()->SetTitleFont(42);

  g_FL_sta[meas]->GetYaxis()->SetRangeUser(0,nmeas);
  // -------------------------------------

  // -------------------------------------
  // Theory -> Band
  TLine *l_FL = new TLine(Central[FL][Theory][0], 0, Central[FL][Theory][0], nmeas);  
  l_FL->SetLineColor(0);
  l_FL->SetLineWidth(2);
  l_FL->SetLineStyle(8);  
  TBox *g_FL_error = new TBox(Central[FL][Theory][0] - Error[FL][Theory][0], 0, Central[FL][Theory][0] + Error[FL][Theory][0], nmeas);  
  g_FL_error->SetFillColor(cerror);
  // -------------------------------------
  
  // -------------------------------------
  // CMS
  g_FL_sta[CMS] = new TGraphErrors(1,Central[FL][CMS],y[CMS],ErrorSta[FL][CMS], ye[CMS]);
  g_FL_tot[CMS] = new TGraphErrors(1,Central[FL][CMS],y[CMS],Error   [FL][CMS], ye[CMS]);
  SetupGraph(g_FL_sta[CMS], markcolor [CMS], markpoint [CMS] );
  SetupGraph(g_FL_tot[CMS], markcolor [CMS], markpoint [CMS], 1 );
  // -------------------------------------

  // -------------------------------------
  // LHC
  g_FL_sta[LHC] = new TGraphErrors(1,Central[FL][LHC],y[LHC],ErrorSta[FL][LHC], ye[LHC]);
  g_FL_tot[LHC] = new TGraphErrors(1,Central[FL][LHC],y[LHC],Error   [FL][LHC], ye[LHC]);
  SetupGraph(g_FL_sta[LHC], markcolor [LHC], markpoint [LHC] );
  SetupGraph(g_FL_tot[LHC], markcolor [LHC], markpoint [LHC], 1 );
  // -------------------------------------
  
  // -------------------------------------
  // ATLAS13TeV
  g_FL_sta[ATLAS13TeV] = new TGraphErrors(1,Central[FL][ATLAS13TeV],y[ATLAS13TeV],ErrorSta[FL][ATLAS13TeV], ye[ATLAS13TeV]);
  g_FL_tot[ATLAS13TeV] = new TGraphErrors(1,Central[FL][ATLAS13TeV],y[ATLAS13TeV],Error   [FL][ATLAS13TeV], ye[ATLAS13TeV]);
  SetupGraph(g_FL_sta[ATLAS13TeV], markcolor [ATLAS13TeV], markpoint [ATLAS13TeV] );
  SetupGraph(g_FL_tot[ATLAS13TeV], markcolor [ATLAS13TeV], markpoint [ATLAS13TeV], 1 );
  // -------------------------------------
  
  // __________________________________________________________________________________________
  // FR
  // __________________________________________________________________________________________

  // Measurement
  TGraphErrors *g_FR_sta[nmeas];
  TGraphErrors *g_FR_tot[nmeas];
  g_FR_sta[meas] = new TGraphErrors(1,Central[FR][meas],y[meas],ErrorSta[FR][meas], ye[meas]);
  g_FR_tot[meas] = new TGraphErrors(1,Central[FR][meas],y[meas],Error   [FR][meas], ye[meas]);
  SetupGraph(g_FR_sta[meas], markcolor [meas], markpoint [meas] );
  SetupGraph(g_FR_tot[meas], markcolor [meas], markpoint [meas], 1 );
  g_FR_sta[meas]->GetXaxis()->SetLimits(FR_o, FR_f);
  g_FR_sta[meas]->GetXaxis()->SetLabelOffset(-0.03);
  g_FR_sta[meas]->GetXaxis()->SetLabelSize(0.08);
  g_FR_sta[meas]->GetXaxis()->SetLabelFont(42);
  g_FR_sta[meas]->GetXaxis()->SetNdivisions(504);
  g_FR_sta[meas]->GetXaxis()->SetTitle("F_{R}");
  g_FR_sta[meas]->GetXaxis()->SetTitleSize(0.12);
  g_FR_sta[meas]->GetXaxis()->SetTitleOffset(0.45);
  g_FR_sta[meas]->GetXaxis()->SetTitleFont(42);

  g_FR_sta[meas]->GetYaxis()->SetRangeUser(0,nmeas);
  // -------------------------------------

  // -------------------------------------
  // Theory -> Band
  TLine *l_FR = new TLine(Central[FR][Theory][0], 0, Central[FR][Theory][0], nmeas);  
  l_FR->SetLineColor(0);
  l_FR->SetLineWidth(2);
  l_FR->SetLineStyle(8);  
  TBox *g_FR_error = new TBox(Central[FR][Theory][0] - Error[FR][Theory][0], 0, Central[FR][Theory][0] + Error[FR][Theory][0], nmeas);  
  g_FR_error->SetFillColor(cerror);
  // -------------------------------------
  
  // -------------------------------------
  // CMS
  g_FR_sta[CMS] = new TGraphErrors(1,Central[FR][CMS],y[CMS],ErrorSta[FR][CMS], ye[CMS]);
  g_FR_tot[CMS] = new TGraphErrors(1,Central[FR][CMS],y[CMS],Error   [FR][CMS], ye[CMS]);
  SetupGraph(g_FR_sta[CMS], markcolor [CMS], markpoint [CMS] );
  SetupGraph(g_FR_tot[CMS], markcolor [CMS], markpoint [CMS], 1 );
  // -------------------------------------

  // -------------------------------------
  // LHC
  g_FR_sta[LHC] = new TGraphErrors(1,Central[FR][LHC],y[LHC],ErrorSta[FR][LHC], ye[LHC]);
  g_FR_tot[LHC] = new TGraphErrors(1,Central[FR][LHC],y[LHC],Error   [FR][LHC], ye[LHC]);
  SetupGraph(g_FR_sta[LHC], markcolor [LHC], markpoint [LHC] );
  SetupGraph(g_FR_tot[LHC], markcolor [LHC], markpoint [LHC], 1 );
  // -------------------------------------

  // -------------------------------------
  // ATLAS13TeV
  g_FR_sta[ATLAS13TeV] = new TGraphErrors(1,Central[FR][ATLAS13TeV],y[ATLAS13TeV],ErrorSta[FR][ATLAS13TeV], ye[ATLAS13TeV]);
  g_FR_tot[ATLAS13TeV] = new TGraphErrors(1,Central[FR][ATLAS13TeV],y[ATLAS13TeV],Error   [FR][ATLAS13TeV], ye[ATLAS13TeV]);
  SetupGraph(g_FR_sta[ATLAS13TeV], markcolor [ATLAS13TeV], markpoint [ATLAS13TeV] );
  SetupGraph(g_FR_tot[ATLAS13TeV], markcolor [ATLAS13TeV], markpoint [ATLAS13TeV], 1 );
  // -------------------------------------
// __________________________________________________________________________________________
  // __________________________________________________________________________________________
  

  TLatex *tl_cms;
  tl_cms  = new TLatex(-20.,50.,"CMS");
  tl_cms->SetNDC();
  tl_cms->SetTextAlign(12);
  tl_cms->SetX(0.0);
  tl_cms->SetY(0.94);
  tl_cms->SetTextFont(62);
  tl_cms->SetTextSize(0.12);
  tl_cms->SetTextSizePixels(24);
  TLatex *tl_lum;
  tl_lum  = new TLatex(-20.,50.,"139 fb^{-1} (13 TeV)");
  tl_lum->SetNDC();
  tl_lum->SetTextAlign(12);
  tl_lum->SetX(0.30);
  tl_lum->SetY(0.935);
  tl_lum->SetTextFont(42);
  tl_lum->SetTextSize(0.07);
  tl_lum->SetTextSizePixels(24);
  
  TLatex *tl_ch;
  tl_ch  = new TLatex(-20.,50.,"Lepton+jets");
  tl_ch->SetNDC();
  tl_ch->SetTextAlign(12);
  tl_ch->SetX(0.02);
  tl_ch->SetY(0.84);
  tl_ch->SetTextFont(42);
  tl_ch->SetTextSize(0.07);
  tl_ch->SetTextSizePixels(24);

  TLine *ll_th = new TLine(0.05,0.59, 0.05,0.64);
  ll_th->SetLineColor(0);
  ll_th->SetLineWidth(2);
  ll_th->SetLineStyle(8);
  TBox *bl_th = new TBox(0.,0.59,0.1,0.64);
  bl_th->SetFillColor(cerror);
  TLatex *ul_th;
  ul_th  = new TLatex(-20.,50.,"SM NNLO");
  ul_th->SetNDC();
  ul_th->SetTextAlign(12);
  ul_th->SetX(0.12);
  ul_th->SetY(0.615);
  ul_th->SetTextFont(42);
  ul_th->SetTextSize(0.07);
  ul_th->SetTextSizePixels(24);

  
  float legy[nmeas];
  legy[meas]       =0.55;
  legy[CMS]        =0.35;
  legy[LHC]        =0.25;
  legy[ATLAS13TeV] =0.15;

  TMarker *tm_entry[nmeas];
  TLine   *tl_entry[nmeas];
  TLatex  *tt_entry[nmeas];

  // CMS
  tm_entry[CMS] = new TMarker(0.05,legy[CMS],markpoint [CMS]);
  tm_entry[CMS]->SetMarkerColor(markcolor [CMS]);
  tm_entry[CMS]->SetMarkerSize(1.2);
  tl_entry[CMS] = new TLine(0.0,legy[CMS], 0.1,legy[CMS]);
  tl_entry[CMS]->SetLineWidth(1);
  tl_entry[CMS]->SetLineStyle(1);
  tt_entry[CMS]  = new TLatex(-20.,50.,"CMS (F_{i}/#sigma_{tt} at 8/13 TeV)");
  tt_entry[CMS]->SetNDC();
  tt_entry[CMS]->SetTextAlign(12);
  tt_entry[CMS]->SetX(0.15);
  tt_entry[CMS]->SetY(legy[CMS]);
  tt_entry[CMS]->SetTextFont(42);
  tt_entry[CMS]->SetTextSize(0.07);
  tt_entry[CMS]->SetTextSizePixels(24);

  // LHC
  tm_entry[LHC] = new TMarker(0.05,legy[LHC],markpoint [LHC]);
  tm_entry[LHC]->SetMarkerColor(markcolor [LHC]);
  tm_entry[LHC]->SetMarkerSize(1.2);
  tl_entry[LHC] = new TLine(0.0,legy[LHC], 0.1,legy[LHC]);
  tl_entry[LHC]->SetLineWidth(1);
  tl_entry[LHC]->SetLineStyle(1);
  tt_entry[LHC]  = new TLatex(-20.,50.,"LHC combination (8 TeV)");
  tt_entry[LHC]->SetNDC();
  tt_entry[LHC]->SetTextAlign(12);
  tt_entry[LHC]->SetX(0.15);
  tt_entry[LHC]->SetY(legy[LHC]);
  tt_entry[LHC]->SetTextFont(42);
  tt_entry[LHC]->SetTextSize(0.07);
  tt_entry[LHC]->SetTextSizePixels(24);

  // ATLAS13TeV
  tm_entry[ATLAS13TeV] = new TMarker(0.05,legy[ATLAS13TeV],markpoint [ATLAS13TeV]);
  tm_entry[ATLAS13TeV]->SetMarkerColor(markcolor [ATLAS13TeV]);
  tm_entry[ATLAS13TeV]->SetMarkerSize(1.2);
  tl_entry[ATLAS13TeV] = new TLine(0.0,legy[ATLAS13TeV], 0.1,legy[ATLAS13TeV]);
  tl_entry[ATLAS13TeV]->SetLineWidth(1);
  tl_entry[ATLAS13TeV]->SetLineStyle(1);
  tt_entry[ATLAS13TeV]  = new TLatex(-20.,50.,"ATLAS (13TeV)");
  tt_entry[ATLAS13TeV]->SetNDC();
  tt_entry[ATLAS13TeV]->SetTextAlign(12);
  tt_entry[ATLAS13TeV]->SetX(0.15);
  tt_entry[ATLAS13TeV]->SetY(legy[ATLAS13TeV]);
  tt_entry[ATLAS13TeV]->SetTextFont(42);
  tt_entry[ATLAS13TeV]->SetTextSize(0.07);
  tt_entry[ATLAS13TeV]->SetTextSizePixels(24);

  // Measurement
  tm_entry[meas] = new TMarker(0.05,legy[meas],markpoint [meas]);
  tm_entry[meas]->SetMarkerColor(markcolor [meas]);
  tm_entry[meas]->SetMarkerSize(1.2);
  tl_entry[meas] = new TLine(0.0,legy[meas], 0.1,legy[meas]);
  tl_entry[meas]->SetLineWidth(1);
  tl_entry[meas]->SetLineStyle(1);
  tt_entry[meas]  = new TLatex(-20.,50.,"Measurement (13 TeV)");
  tt_entry[meas]->SetNDC();
  tt_entry[meas]->SetTextAlign(12);
  tt_entry[meas]->SetX(0.15);
  tt_entry[meas]->SetY(legy[meas]);
  tt_entry[meas]->SetTextFont(62);
  tt_entry[meas]->SetTextSize(0.07);
  tt_entry[meas]->SetTextSizePixels(24);

  
  
  // ------------------------------------------
  TCanvas *histocanvas;
  histocanvas = new TCanvas("plots", "TOP-21-002",1000,500);
  histocanvas->Divide(5,1);

  histocanvas->cd(1)->SetBottomMargin(.14);
  histocanvas->cd(2)->SetBottomMargin(.14);
  histocanvas->cd(3)->SetBottomMargin(.14);
  histocanvas->cd(4)->SetBottomMargin(.14);
  histocanvas-> Range( 1., -1., 10., 1. );

  histocanvas-> cd(4); 
  g_xsec_sta[meas] ->Draw("AP");
  g_xsec_error     ->Draw();
  l_xsec           ->Draw();
  g_xsec_sta[meas] ->Draw("P");
  g_xsec_tot[meas] ->Draw("P");
  g_xsec_sta[CMS]  ->Draw("P");
  g_xsec_tot[CMS]  ->Draw("P");
  redrawBorder();
  // ------------------------------------------
  histocanvas-> cd(1); 
  g_F0_sta[meas]       ->Draw("AP");
  g_F0_error           ->Draw();
  l_F0                 ->Draw();
  g_F0_sta[meas]       ->Draw("P");
  g_F0_tot[meas]       ->Draw("P");
  g_F0_sta[CMS]        ->Draw("P");
  g_F0_tot[CMS]        ->Draw("P");
  g_F0_sta[LHC]        ->Draw("P");
  g_F0_tot[LHC]        ->Draw("P");
  g_F0_sta[ATLAS13TeV] ->Draw("P");
  g_F0_tot[ATLAS13TeV] ->Draw("P");
  redrawBorder();
  // ------------------------------------------
  histocanvas-> cd(2); 
  g_FL_sta[meas]       ->Draw("AP");
  g_FL_error           ->Draw();
  l_FL                 ->Draw();
  g_FL_sta[meas]       ->Draw("P");
  g_FL_tot[meas]       ->Draw("P");
  g_FL_sta[CMS]        ->Draw("P");
  g_FL_tot[CMS]        ->Draw("P");
  g_FL_sta[LHC]        ->Draw("P");
  g_FL_tot[LHC]        ->Draw("P");
  g_FL_sta[ATLAS13TeV] ->Draw("P");
  g_FL_tot[ATLAS13TeV] ->Draw("P");
  redrawBorder();
    // ------------------------------------------
  histocanvas-> cd(3); 
  g_FR_sta[meas]       ->Draw("AP");
  g_FR_error           ->Draw();
  l_FR                 ->Draw();
  g_FR_sta[meas]       ->Draw("P");
  g_FR_tot[meas]       ->Draw("P");
  g_FR_sta[CMS]        ->Draw("P");
  g_FR_tot[CMS]        ->Draw("P");
  g_FR_sta[LHC]        ->Draw("P");
  g_FR_tot[LHC]        ->Draw("P");
  g_FR_sta[ATLAS13TeV] ->Draw("P");
  g_FR_tot[ATLAS13TeV] ->Draw("P");
  redrawBorder();
  // ------------------------------------------
  histocanvas-> cd(5); 

  tl_cms->Draw();
  tl_lum->Draw("SAME");
  tl_ch ->Draw("SAME");

  bl_th ->Draw("SAME");
  ll_th ->Draw("SAME");
  ul_th ->Draw("SAME");

  tm_entry[CMS] ->Draw("SAME");
  tl_entry[CMS] ->Draw("SAME");
  tt_entry[CMS] ->Draw("SAME");

  tm_entry[LHC] ->Draw("SAME");
  tl_entry[LHC] ->Draw("SAME");
  tt_entry[LHC] ->Draw("SAME");

  tm_entry[ATLAS13TeV] ->Draw("SAME");
  tl_entry[ATLAS13TeV] ->Draw("SAME");
  tt_entry[ATLAS13TeV] ->Draw("SAME");

  tm_entry[meas] ->Draw("SAME");
  tl_entry[meas] ->Draw("SAME");
  tt_entry[meas] ->Draw("SAME");
  
  // ------------------------------------------
  // ------------------------------------------

  
  histocanvas->SaveAs(OutDir + "SummaryPlots.pdf");
  // __________________________________________________________________________________________


}
