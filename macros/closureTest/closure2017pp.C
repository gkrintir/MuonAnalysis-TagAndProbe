#include "TFile.h"
//#include "tnp_weight.h"
#include "tnp_mc.h"
#include "helper.h"
#include "TEfficiency.h"
#include "TGraphAsymmErrors.h"
#include "TRatioPlot.h"

Double_t tnp_mc_muidtrg_pp_wrapper(Double_t *x, Double_t *par) {
  return tnpEff_mc_MuIdTrg_pp(x[0],par[0]);
}
// Double_t tnp_mc_muid_pp_wrapper(Double_t *x, Double_t *par) {
//   return tnpEff_mc_muid_pp(x[0],par[0]);
// }
Double_t tnp_mc_glb_pp_wrapper(Double_t *x, Double_t *par) {
  return tnpEff_mc_glb_pp(x[0],par[0]);
}
Double_t tnp_mc_full_pp_wrapper(Double_t *x, Double_t *par) {
  return tnpEff_mc_glb_pp(x[0],par[0])
    //    * tnpEff_mc_muid_pp(x[0],par[0])
    * tnpEff_mc_MuIdTrg_pp(x[0],par[0]);
}

float ptmin(float etamax) {
  float ans=0;
  if (etamax<1.2) ans = 3.5;
  else if (etamax<2.1) ans = 5.47-1.89*fabs(etamax);
  else ans = 1.5;
  // ans = (int) (ans*10.);
  // ans = ans/10.;
  return ans;
}

void closure2017pp() {
  TFile *f = new TFile("histos_trd_pp.root");

  TH1D *haxes20 = new TH1D("haxes20","haxes20",1,0,20);
  TH1D *haxes30 = new TH1D("haxes30","haxes30",1,0,30);
  haxes20->GetYaxis()->SetRangeUser(0,1.1);
  haxes30->GetYaxis()->SetRangeUser(0,1.1);
  haxes20->GetXaxis()->SetTitle("p_{T} [GeV/c]");
  haxes30->GetXaxis()->SetTitle("p_{T} [GeV/c]");
  haxes20->GetYaxis()->SetTitle("Efficiency");
  haxes30->GetYaxis()->SetTitle("Efficiency");

  // Muidtrg eff comparison: Trd vs Tnp (binned)
  TCanvas *c1 = new TCanvas();
  TFile *ftnp_muidtrg = new TFile("../../test/tnp_fitOutput_HybridSoftIDTrigger_MC_pp_CBGPlusPol1.root");
  RooDataSet *da_muidtrg=NULL;
  TGraphAsymmErrors *gmuidtrg=new TGraphAsymmErrors();
  TH1D *hnum=NULL, *hden=NULL;
  TH1D *htnp_num=NULL, *htnp_den=NULL;
  TH1D *hnum2=NULL, *hden2=NULL;
  TGraphAsymmErrors *eff=new TGraphAsymmErrors();
  TGraphAsymmErrors *eff2=new TGraphAsymmErrors();
  TRatioPlot *tr = NULL;
  TLegend *tleg = new TLegend(0.6,0.2,0.9,0.5);
  tleg->SetBorderSize(0); tleg->SetFillColor(0);

  // 0<|y|<1.2
  c1->cd(); c1->Clear();
  //  da_muidtrg = (RooDataSet*)ftnp_muidtrg->Get("tpTree/MuIdTrg_abseta00_12/fit_eff");
  htnp_num = (TH1D*) f->Get("hden_glbIDtrgwtFromGlb_00_12");//plotEff(da_muidtrg,1,"pt");
  htnp_den = (TH1D*) f->Get("hden_glbwtFromGlb_00_12");
  gmuidtrg->Divide(htnp_num,htnp_den,"pois");
  SetGoodTnpError(gmuidtrg, g_MuIdTrg_00_12, htnp_num);
  gmuidtrg->SetLineColor(kRed);
  gmuidtrg->SetMarkerColor(kRed);
  hnum = (TH1D*) f->Get("hnumglbIDtrg_00_12");
  hden = (TH1D*) f->Get("hnumglb_00_12");
  eff->Divide(hnum,hden,"pois");
  eff->SetLineColor(kBlack);
  eff->SetMarkerColor(kBlack);
  tleg->AddEntry(gmuidtrg,"Tag and probe","lp");
  tleg->AddEntry(eff,"Traditional","lp");
  tleg->SetHeader("pp, MuId+trigger, 0<|y|<1.2");
  tr = new TRatioPlot(g2h(eff,20),g2h(gmuidtrg,2));
  tr->Draw();
  setTRatioPlotStyle(tr);
  c1->Update();
  tr->GetUpperPad()->cd();
  tleg->Draw();
  g_MuIdTrg_00_12->Draw("P");
  c1->SaveAs("pp_muidtrg_binned_00_12.pdf");

  // 1.2<|y|<1.8
  c1->cd(); c1->Clear();
  //  da_muidtrg = (RooDataSet*)ftnp_muidtrg->Get("tpTree/MuIdTrg_abseta12_18/fit_eff");
  htnp_num = (TH1D*) f->Get("hden_glbIDtrgwtFromGlb_12_18");//plotEff(da_muidtrg,1,"pt");
  htnp_den = (TH1D*) f->Get("hden_glbwtFromGlb_12_18");
  gmuidtrg->Divide(htnp_num,htnp_den,"pois");
  SetGoodTnpError(gmuidtrg, g_MuIdTrg_12_18, htnp_num);
  gmuidtrg->SetLineColor(kRed);
  gmuidtrg->SetMarkerColor(kRed);
  hnum = (TH1D*) f->Get("hnumglbIDtrg_12_18");
  hden = (TH1D*) f->Get("hnumglb_12_18");
  eff->Divide(hnum,hden,"pois");
  eff->SetLineColor(kBlack);
  eff->SetMarkerColor(kBlack);
  tleg->SetHeader("pp, MuId+trigger, 1.2<|y|<1.8");
  tr = new TRatioPlot(g2h(eff,20),g2h(gmuidtrg,2));
  tr->Draw();
  setTRatioPlotStyle(tr);
  c1->Update();
  tr->GetUpperPad()->cd();
  tleg->Draw();
  g_MuIdTrg_12_18->Draw("P");
  c1->SaveAs("pp_muidtrg_binned_12_18.pdf");

  // 1.8<|y|<2.1
  c1->cd(); c1->Clear();
  //  da_muidtrg = (RooDataSet*)ftnp_muidtrg->Get("tpTree/MuIdTrg_abseta18_21/fit_eff");
  htnp_num = (TH1D*) f->Get("hden_glbIDtrgwtFromGlb_18_21");//plotEff(da_muidtrg,1,"pt");
  htnp_den = (TH1D*) f->Get("hden_glbwtFromGlb_18_21");
  gmuidtrg->Divide(htnp_num,htnp_den,"pois");
  SetGoodTnpError(gmuidtrg, g_MuIdTrg_18_21, htnp_num);
  gmuidtrg->SetLineColor(kRed);
  gmuidtrg->SetMarkerColor(kRed);
  hnum = (TH1D*) f->Get("hnumglbIDtrg_18_21");
  hden = (TH1D*) f->Get("hnumglb_18_21");
  eff->Divide(hnum,hden,"pois");
  eff->SetLineColor(kBlack);
  eff->SetMarkerColor(kBlack);
  tleg->SetHeader("pp, MuId+trigger, 1.8<|y|<2.1");
  tr = new TRatioPlot(g2h(eff,20),g2h(gmuidtrg,2));
  tr->Draw();
  setTRatioPlotStyle(tr);
  c1->Update();
  tr->GetUpperPad()->cd();
  tleg->Draw();
  g_MuIdTrg_18_21->Draw("P");
  c1->SaveAs("pp_muidtrg_binned_18_21.pdf");

  // 2.1<|y|<2.4
  c1->cd(); c1->Clear();
  //  da_muidtrg = (RooDataSet*)ftnp_muidtrg->Get("tpTree/MuIdTrg_abseta18_21/fit_eff");
  htnp_num = (TH1D*) f->Get("hden_glbIDtrgwtFromGlb_21_24");//plotEff(da_muidtrg,1,"pt");
  htnp_den = (TH1D*) f->Get("hden_glbwtFromGlb_21_24");
  //  cout<<htnp_num->GetNbinsX()<<endl;
  // for(int i=0;i<=htnp_num->GetNbinsX()+1;i++){
  //   cout<<"bin #"<<i<<" lowedge, width = "<<htnp_num->GetBinLowEdge(i)<<" "<<htnp_num->GetBinWidth(i)<<endl;
  //   cout<<"hnum y = "<<htnp_num->GetBinContent(i)<<endl;
  //   cout<<"hden y = "<<htnp_den->GetBinContent(i)<<endl;
  // }
  gmuidtrg->Divide(htnp_num,htnp_den,"pois");
  // for(int i=0;i<gmuidtrg->GetN();i++){
  //   cout<<"TnP method graph, pt #"<<i<<"<< X,Y = "<<gmuidtrg->GetX()[i]<<","<<gmuidtrg->GetY()[i]<<endl;
  // }
  SetGoodTnpError(gmuidtrg, g_MuIdTrg_21_24, htnp_num);
  gmuidtrg->SetLineColor(kRed);
  gmuidtrg->SetMarkerColor(kRed);
  hnum = (TH1D*) f->Get("hnumglbIDtrg_21_24");
  hden = (TH1D*) f->Get("hnumglb_21_24");
  // cout<<endl;
  // for(int i=0;i<=hnum->GetNbinsX()+1;i++){
  //   cout<<"bin #"<<i<<" lowedge, width = "<<hnum->GetBinLowEdge(i)<<" "<<hnum->GetBinWidth(i)<<endl;
  //   cout<<"hnum y = "<<hnum->GetBinContent(i)<<endl;
  //   cout<<"hden y = "<<hden->GetBinContent(i)<<endl;
  // }
  eff->Divide(hnum,hden,"pois");
  // for(int i=0;i<eff->GetN();i++){
  //   cout<<"Trad method graph, pt #"<<i<<"<< X,Y = "<<eff->GetX()[i]<<","<<eff->GetY()[i]<<endl;
  // }
  eff->SetLineColor(kBlack);
  eff->SetMarkerColor(kBlack);
  tleg->SetHeader("pp, MuId+trigger, 2.1<|y|<2.4");
  TH1F* heff = g2h(eff,20); TH1F* hmuidtrg = g2h(gmuidtrg,2);
  tr = new TRatioPlot(heff,hmuidtrg);
  // cout<<endl;
  // cout<<"final hist sizes for num, den = "<<heff->GetNbinsX()<<" "<<hmuidtrg->GetNbinsX()<<endl;
  // for(int i=0;i<=heff->GetNbinsX()+1;i++){
  //   cout<<"bin #"<<i<<" lowedge, width = "<<heff->GetBinLowEdge(i)<<" "<<heff->GetBinWidth(i)<<endl;
  //   cout<<"hTrad y = "<<heff->GetBinContent(i)<<endl;
  //   cout<<"hTnP y = "<<hmuidtrg->GetBinContent(i)<<endl;
  // }
  tr->Draw();
  setTRatioPlotStyle(tr);
  c1->Update();
  tr->GetUpperPad()->cd();
  tleg->Draw();
  g_MuIdTrg_21_24->Draw("P");
  c1->SaveAs("pp_muidtrg_binned_21_24.pdf");




  // Full eff comparison: Trd vs Tnp (functions)

  // 0<|y|<1.2
  c1->cd(); c1->Clear();
  htnp_num = (TH1D*) f->Get("hden_glbIDtrgwt_00_12");
  htnp_den = (TH1D*) f->Get("hden_00_12");
  gmuidtrg->Divide(htnp_num,htnp_den,"pois");
  SetGoodTnpError(gmuidtrg, g_MuIdTrg_00_12, htnp_num, g_Glb_00_12);
  gmuidtrg->SetLineColor(kRed);
  gmuidtrg->SetMarkerColor(kRed);
  hnum = (TH1D*) f->Get("hnumglbIDtrg_00_12");
  hden = (TH1D*) f->Get("hnumAcc_00_12");
  eff->Divide(hnum,hden,"pois");
  eff->SetLineColor(kBlack);
  eff->SetMarkerColor(kBlack);
  tleg->SetHeader("pp, full eff, 0<|y|<1.2");
  tr = new TRatioPlot(g2h(eff,20),g2h(gmuidtrg,2));
  tr->Draw();
  setTRatioPlotStyle(tr);
  c1->Update();
  tr->GetUpperPad()->cd();
  tleg->Draw();
  c1->SaveAs("pp_full_binned_00_12.pdf");

  // 1.2<|y|<1.8
  c1->cd(); c1->Clear();
  htnp_num = (TH1D*) f->Get("hden_glbIDtrgwt_12_18");
  htnp_den = (TH1D*) f->Get("hden_12_18");
  gmuidtrg->Divide(htnp_num,htnp_den,"pois");
  SetGoodTnpError(gmuidtrg, g_MuIdTrg_12_18, htnp_num, g_Glb_12_18);
  gmuidtrg->SetLineColor(kRed);
  gmuidtrg->SetMarkerColor(kRed);
  hnum = (TH1D*) f->Get("hnumglbIDtrg_12_18");
  hden = (TH1D*) f->Get("hnumAcc_12_18");
  eff->Divide(hnum,hden,"pois");
  eff->SetLineColor(kBlack);
  eff->SetMarkerColor(kBlack);
  tleg->SetHeader("pp, full eff, 1.2<|y|<1.8");
  tr = new TRatioPlot(g2h(eff,20),g2h(gmuidtrg,2));
  tr->Draw();
  setTRatioPlotStyle(tr);
  c1->Update();
  tr->GetUpperPad()->cd();
  tleg->Draw();
  c1->SaveAs("pp_full_binned_12_18.pdf");

  // 1.8<|y|<2.1
  c1->cd(); c1->Clear();
  htnp_num = (TH1D*) f->Get("hden_glbIDtrgwt_18_21");
  htnp_den = (TH1D*) f->Get("hden_18_21");
  gmuidtrg->Divide(htnp_num,htnp_den,"pois");
  SetGoodTnpError(gmuidtrg, g_MuIdTrg_18_21, htnp_num, g_Glb_18_24);
  gmuidtrg->SetLineColor(kRed);
  gmuidtrg->SetMarkerColor(kRed);
  hnum = (TH1D*) f->Get("hnumglbIDtrg_18_21");
  hden = (TH1D*) f->Get("hnumAcc_18_21");
  eff->Divide(hnum,hden,"pois");
  eff->SetLineColor(kBlack);
  eff->SetMarkerColor(kBlack);
  tleg->SetHeader("pp, full eff, 1.8<|y|<2.1");
  tr = new TRatioPlot(g2h(eff,20),g2h(gmuidtrg,2));
  tr->Draw();
  setTRatioPlotStyle(tr);
  c1->Update();
  tr->GetUpperPad()->cd();
  tleg->Draw();
  c1->SaveAs("pp_full_binned_18_21.pdf");

  // 2.1<|y|<2.4
  c1->cd(); c1->Clear();
  htnp_num = (TH1D*) f->Get("hden_glbIDtrgwt_21_24");
  htnp_den = (TH1D*) f->Get("hden_21_24");
  gmuidtrg->Divide(htnp_num,htnp_den,"pois");
  SetGoodTnpError(gmuidtrg, g_MuIdTrg_21_24, htnp_num, g_Glb_18_24);
  gmuidtrg->SetLineColor(kRed);
  gmuidtrg->SetMarkerColor(kRed);
  hnum = (TH1D*) f->Get("hnumglbIDtrg_21_24");
  hden = (TH1D*) f->Get("hnumAcc_21_24");
  eff->Divide(hnum,hden,"pois");
  eff->SetLineColor(kBlack);
  eff->SetMarkerColor(kBlack);
  tleg->SetHeader("pp, full eff, 2.1<|y|<2.4");
  tr = new TRatioPlot(g2h(eff,20),g2h(gmuidtrg,2));
  tr->Draw();
  setTRatioPlotStyle(tr);
  c1->Update();
  tr->GetUpperPad()->cd();
  tleg->Draw();
  c1->SaveAs("pp_full_binned_21_24.pdf");









  // // 0<|y|<1.2
  // c1->cd(); c1->Clear();
  // da_muidtrg = (RooDataSet*)ftnp_muidtrg->Get("tpTree/MuIdTrg_abseta00_12/fit_eff");
  // gmuidtrg = plotEff(da_muidtrg,1,"pt");
  // gmuidtrg->SetLineColor(kRed);
  // gmuidtrg->SetMarkerColor(kRed);
  // hnum = (TH1D*) f->Get("hnumglbIDtrg_00_12");
  // hden = (TH1D*) f->Get("hnumglb_00_12");
  // eff->Divide(hnum,hden,"pois");
  // eff->SetLineColor(kBlack);
  // eff->SetMarkerColor(kBlack);
  // tleg->AddEntry(gmuidtrg,"Tag and probe","lp");
  // tleg->AddEntry(eff,"Traditional","lp");
  // tleg->SetHeader("pp, trigger, 0<|y|<1.2");
  // tr = new TRatioPlot(g2h(eff,20),g2h(gmuidtrg,2));
  // tr->Draw();
  // setTRatioPlotStyle(tr);
  // c1->Update();
  // tr->GetUpperPad()->cd();
  // tleg->Draw();
  // c1->SaveAs("pp_muidtrg_binned_00_12.pdf");

  // // 1.2<|y|<1.8
  // c1->cd(); c1->Clear();
  // da_muidtrg = (RooDataSet*)ftnp_muidtrg->Get("tpTree/MuIdTrg_abseta12_18/fit_eff");
  // gmuidtrg = plotEff(da_muidtrg,1,"pt");
  // gmuidtrg->SetLineColor(kRed);
  // gmuidtrg->SetMarkerColor(kRed);
  // hnum = (TH1D*) f->Get("hnumglbIDtrg_12_18");
  // hden = (TH1D*) f->Get("hnumglb_12_18");
  // eff->Divide(hnum,hden,"pois");
  // eff->SetLineColor(kBlack);
  // eff->SetMarkerColor(kBlack);
  // eff->SetMarkerStyle(kFullSquare);
  // tleg->SetHeader("pp, trigger, 1.2<|y|<1.8");
  // tr = new TRatioPlot(g2h(eff,20),g2h(gmuidtrg,2));
  // setTRatioPlotStyle(tr);
  // c1->Update();
  // tr->GetUpperPad()->cd();
  // tleg->Draw();
  // c1->SaveAs("pp_muidtrg_binned_12_18.pdf");

  // // 1.8<|y|<2.1
  // c1->cd(); c1->Clear();
  // da_muidtrg = (RooDataSet*)ftnp_muidtrg->Get("tpTree/MuIdTrg_abseta18_21/fit_eff");
  // gmuidtrg = plotEff(da_muidtrg,1,"pt");
  // gmuidtrg->SetLineColor(kRed);
  // gmuidtrg->SetMarkerColor(kRed);
  // hnum = (TH1D*) f->Get("hnumglbIDtrg_18_21");
  // hden = (TH1D*) f->Get("hnumglb_18_21");
  // eff->Divide(hnum,hden,"pois");
  // eff->SetLineColor(kBlack);
  // eff->SetMarkerColor(kBlack);
  // eff->SetMarkerStyle(kFullSquare);
  // tleg->SetHeader("pp, trigger, 1.8<|y|<2.1");
  // tr = new TRatioPlot(g2h(eff,20),g2h(gmuidtrg,2));
  // setTRatioPlotStyle(tr);
  // c1->Update();
  // tr->GetUpperPad()->cd();
  // tleg->Draw();
  // c1->SaveAs("pp_muidtrg_binned_18_21.pdf");

  // // 2.1<|y|<2.4
  // c1->cd(); c1->Clear();
  // da_muidtrg = (RooDataSet*)ftnp_muidtrg->Get("tpTree/MuIdTrg_abseta21_24/fit_eff");
  // gmuidtrg = plotEff(da_muidtrg,1,"pt");
  // gmuidtrg->SetLineColor(kRed);
  // gmuidtrg->SetMarkerColor(kRed);
  // hnum = (TH1D*) f->Get("hnumglbIDtrg_21_24");
  // hden = (TH1D*) f->Get("hnumglb_21_24");
  // eff->Divide(hnum,hden,"pois");
  // eff->SetLineColor(kBlack);
  // eff->SetMarkerColor(kBlack);
  // eff->SetMarkerStyle(kFullSquare);
  // tleg->SetHeader("pp, trigger, 2.1<|y|<2.4");
  // tr = new TRatioPlot(g2h(eff,20),g2h(gmuidtrg,2));
  // setTRatioPlotStyle(tr);
  // c1->Update();
  // tr->GetUpperPad()->cd();
  // tleg->Draw();
  // c1->SaveAs("pp_muidtrg_binned_21_24.pdf");







//   // Full eff comparison: Trd vs Tnp (functions)
//   // 0<|y|<1.2
//   c1->cd(); c1->Clear();
//   double y=1.2-1e-4; double ptminval = ptmin(y);
//   TF1 *fpp_full = new TF1("fpp_full_00_12",tnp_mc_full_pp_wrapper,ptminval,30,2);
//   fpp_full->SetLineColor(kRed);
//   fpp_full->SetParameter(0,y);
//   hnum = (TH1D*) f->Get("hnumglbIDtrg_00_12");
//   hden = (TH1D*) f->Get("hden_00_12");
//   eff->Divide(hnum,hden,"pois");
//   eff->SetLineColor(kBlack);
//   eff->SetMarkerColor(kBlack);
//   eff->SetMarkerStyle(kFullSquare);
//   hnum2 = (TH1D*) f->Get("hden_staIDtrgwt_00_12");
//   hden2 = (TH1D*) f->Get("hden_00_12");
//   eff2->Divide(hnum2,hden2,"pois");
//   eff2->SetLineColor(kMagenta);
//   eff2->SetMarkerColor(kMagenta);
//   tleg->SetHeader("pp, full eff, 0<|y|<1.2");
//   tr = new TRatioPlot(g2h(eff,20),g2h(eff2,2));
//   setTRatioPlotStyle(tr);
//   c1->Update();
//   tr->GetUpperPad()->cd();
//   fpp_full->Draw("same");
//   tleg->Draw();
//   c1->SaveAs("pp_full_00_12.pdf");

//   // 1.2<|y|<1.8
//   c1->cd(); c1->Clear();
//   y=1.8-1e-4; ptminval = ptmin(y);
//   fpp_full = new TF1("fpp_full_12_18",tnp_mc_full_pp_wrapper,ptminval,30,2);
//   fpp_full->SetLineColor(kRed);
//   fpp_full->SetParameter(0,y);
//   hnum = (TH1D*) f->Get("hnumglbIDtrg_12_18");
//   hden = (TH1D*) f->Get("hden_12_18");
//   eff->Divide(hnum,hden,"pois");
//   eff->SetLineColor(kBlack);
//   eff->SetMarkerColor(kBlack);
//   eff->SetMarkerStyle(kFullSquare);
//   hnum2 = (TH1D*) f->Get("hden_staIDtrgwt_12_18");
//   hden2 = (TH1D*) f->Get("hden_12_18");
//   eff2->Divide(hnum2,hden2,"pois");
//   eff2->SetLineColor(kMagenta);
//   eff2->SetMarkerColor(kMagenta);
//   tleg->SetHeader("pp, full eff, 1.2<|y|<1.8");
//   tr = new TRatioPlot(g2h(eff,20),g2h(eff2,2));
//   setTRatioPlotStyle(tr);
//   c1->Update();
//   tr->GetUpperPad()->cd();
//   fpp_full->Draw("same");
//   tleg->Draw();
//   c1->SaveAs("pp_full_12_18.pdf");

//   // 1.8<|y|<2.1
//   c1->cd(); c1->Clear();
//   y=2.1-1e-4; ptminval = ptmin(y);
//   fpp_full = new TF1("fpp_full_18_21",tnp_mc_full_pp_wrapper,ptminval,20,2);
//   fpp_full->SetLineColor(kRed);
//   fpp_full->SetParameter(0,y);
//   hnum = (TH1D*) f->Get("hnumglbIDtrg_18_21");
//   hden = (TH1D*) f->Get("hden_18_21");
//   eff->Divide(hnum,hden,"pois");
//   eff->SetLineColor(kBlack);
//   eff->SetMarkerColor(kBlack);
//   eff->SetMarkerStyle(kFullSquare);
//   hnum2 = (TH1D*) f->Get("hden_staIDtrgwt_18_21");
//   hden2 = (TH1D*) f->Get("hden_18_21");
//   eff2->Divide(hnum2,hden2,"pois");
//   eff2->SetLineColor(kMagenta);
//   eff2->SetMarkerColor(kMagenta);
//   tleg->SetHeader("pp, full eff, 1.8<|y|<2.1");
//   tr = new TRatioPlot(g2h(eff,20),g2h(eff2,2));
//   setTRatioPlotStyle(tr);
//   c1->Update();
//   tr->GetUpperPad()->cd();
//   fpp_full->Draw("same");
//   tleg->Draw();
//   c1->SaveAs("pp_full_18_21.pdf");

//   // 2.1<|y|<2.4
//   c1->cd(); c1->Clear();
//   y=2.4-1e-4; ptminval = ptmin(y);
//   fpp_full = new TF1("fpp_full_21_24",tnp_mc_full_pp_wrapper,ptminval,20,2);
//   fpp_full->SetLineColor(kRed);
//   fpp_full->SetParameter(0,y);
//   hnum = (TH1D*) f->Get("hnumglbIDtrg_21_24");
//   hden = (TH1D*) f->Get("hden_21_24");
//   eff->Divide(hnum,hden,"pois");
//   eff->SetLineColor(kBlack);
//   eff->SetMarkerColor(kBlack);
//   eff->SetMarkerStyle(kFullSquare);
//   hnum2 = (TH1D*) f->Get("hden_staIDtrgwt_21_24");
//   hden2 = (TH1D*) f->Get("hden_21_24");
//   eff2->Divide(hnum2,hden2,"pois");
//   eff2->SetLineColor(kMagenta);
//   eff2->SetMarkerColor(kMagenta);
//   tleg->SetHeader("pp, full eff, 2.1<|y|<2.4");
//   tr = new TRatioPlot(g2h(eff,20),g2h(eff2,2));
//   setTRatioPlotStyle(tr);
//   c1->Update();
//   tr->GetUpperPad()->cd();
//   fpp_full->Draw("same");
//   tleg->Draw();
//   c1->SaveAs("pp_full_21_24.pdf");
}
