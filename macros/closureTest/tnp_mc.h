#ifndef tnp_mc_h
#define tnp_mc_h

#include "TMath.h"
#include "TFile.h"
#include "TGraphAsymmErrors.h"

///////////////////////////////////////////////////
//                   T R K    P P                //
///////////////////////////////////////////////////
//Extracted with rt -b "../extractEffs.C('../../test/tnp_fitOutput_Trk_MC_pp_twoGaussPlusPol2.root','tnp_efficiencies_Trk_MC_pp_twoGaussPlusPol2.root')"

TFile* fTrk = new TFile("tnp_efficiencies_Trk_MC_pp_twoGaussPlusPol2.root");
TGraphAsymmErrors* g_Trk_00_12 = (TGraphAsymmErrors*)fTrk->Get("TM_abseta00_12"); 
TGraphAsymmErrors* g_Trk_12_18 = (TGraphAsymmErrors*)fTrk->Get("TM_abseta12_18");
TGraphAsymmErrors* g_Trk_18_24 = (TGraphAsymmErrors*)fTrk->Get("TM_abseta18_24");

double tnpEff_mc_trk_pp(double x, double eta) {
  double eff=1;
  if(fabs(eta)<1.2) eff = g_Trk_00_12->Eval(x);
  else if(fabs(eta)<1.8) eff = g_Trk_12_18->Eval(x);
  else if(fabs(eta)<2.4) eff = g_Trk_18_24->Eval(x);
  return eff;
}



///////////////////////////////////////////////////
//                   G L B    P P                //
///////////////////////////////////////////////////
//Extracted with rt -b "../extractEffs.C('../../test/tnp_fitOutput_Glb_MC_pp_twoGaussPlusPol2.root','tnp_efficiencies_Glb_MC_pp_twoGaussPlusPol2.root')"

TFile* fGlb = new TFile("tnp_efficiencies_Glb_MC_pp_twoGaussPlusPol2.root");
TGraphAsymmErrors* g_Glb_00_12 = (TGraphAsymmErrors*)fGlb->Get("Glb_abseta00_12"); 
TGraphAsymmErrors* g_Glb_12_18 = (TGraphAsymmErrors*)fGlb->Get("Glb_abseta12_18");
TGraphAsymmErrors* g_Glb_18_24 = (TGraphAsymmErrors*)fGlb->Get("Glb_abseta18_24");

double tnpEff_mc_glb_pp(double x, double eta) {
  double eff=1;
  if(fabs(eta)<1.2) eff = g_Glb_00_12->Eval(x);
  else if(fabs(eta)<1.8) eff = g_Glb_12_18->Eval(x);
  else if(fabs(eta)<2.4) eff = g_Glb_18_24->Eval(x);
  return eff;
}





///////////////////////////////////////////////////
//           M U I D    P P                      //
///////////////////////////////////////////////////
//Extracted with rt -b "../extractEffs.C(\"../../test/tnp_fitOutput_HybridSoftID_MC_pp_TightAcceptance_CBGPlusPol1.root\",\"tnp_efficiencies_HybridSoftID_MC_pp_CBGPlusPol1.root\")"

TFile* fMuId = new TFile("tnp_efficiencies_HybridSoftID_MC_pp_CBGPlusPol1.root");
TGraphAsymmErrors* g_MuId_00_12 = (TGraphAsymmErrors*)fMuId->Get("MuId_abseta00_12");
TGraphAsymmErrors* g_MuId_12_18 = (TGraphAsymmErrors*)fMuId->Get("MuId_abseta12_18");
TGraphAsymmErrors* g_MuId_18_21 = (TGraphAsymmErrors*)fMuId->Get("MuId_abseta18_21");
TGraphAsymmErrors* g_MuId_21_24 = (TGraphAsymmErrors*)fMuId->Get("MuId_abseta21_24");

double tnpEff_mc_MuId_pp(double x, double eta) {
  double eff=1;
  if(fabs(eta)<1.2) eff = g_MuId_00_12->Eval(x);
  else if(fabs(eta)<1.8) eff = g_MuId_12_18->Eval(x);
  else if(fabs(eta)<2.1) eff = g_MuId_18_21->Eval(x);
  else if(fabs(eta)<2.4) eff = g_MuId_21_24->Eval(x);
  return eff;
}





///////////////////////////////////////////////////
//           M U I D T R G    P P                //
///////////////////////////////////////////////////
//Extracted with rt -b "../extractEffs.C(\"../../test/tnp_fitOutput_HybridSoftIDTrigger_MC_pp_CBGPlusPol1.root\",\"tnp_efficiencies_HybridSoftIDTrigger_MC_pp_CBGPlusPol1.root\")"

TFile* fMuIdTrg = new TFile("tnp_efficiencies_HybridSoftIDTrigger_MC_pp_CBGPlusPol1.root");
TGraphAsymmErrors* g_MuIdTrg_00_12 = (TGraphAsymmErrors*)fMuIdTrg->Get("MuIdTrg_abseta00_12");
TGraphAsymmErrors* g_MuIdTrg_12_18 = (TGraphAsymmErrors*)fMuIdTrg->Get("MuIdTrg_abseta12_18");
TGraphAsymmErrors* g_MuIdTrg_18_21 = (TGraphAsymmErrors*)fMuIdTrg->Get("MuIdTrg_abseta18_21");
TGraphAsymmErrors* g_MuIdTrg_21_24 = (TGraphAsymmErrors*)fMuIdTrg->Get("MuIdTrg_abseta21_24");

double tnpEff_mc_MuIdTrg_pp(double x, double eta) {
  double eff=1;
  if(fabs(eta)<1.2) eff = g_MuIdTrg_00_12->Eval(x);
  else if(fabs(eta)<1.8) eff = g_MuIdTrg_12_18->Eval(x);
  else if(fabs(eta)<2.1) eff = g_MuIdTrg_18_21->Eval(x);
  else if(fabs(eta)<2.4) eff = g_MuIdTrg_21_24->Eval(x);
  return eff;
}

#endif //#ifndef tnp_mc_h
