#ifndef helper_h
#define helper_h

#include "TGraphAsymmErrors.h"
#include "RooDataSet.h"
#include "RooRealVar.h"
#include "TAxis.h"
#include "TRandom3.h"

TGraphAsymmErrors *plotEff(RooDataSet *a, int aa, const char* varx){
  const RooArgSet *set = a->get();
  RooRealVar *xAx = (RooRealVar*)set->find(varx);
  RooRealVar *eff = (RooRealVar*)set->find("efficiency");

  const int nbins = xAx->getBinning().numBins();

  double tx[nbins], txhi[nbins], txlo[nbins];
  double ty[nbins], tyhi[nbins], tylo[nbins];

  for (int i=0; i<nbins; i++) {
    a->get(i);
    ty[i] = eff->getVal();
    tx[i] = xAx->getVal();
    txhi[i] = fabs(xAx->getErrorHi());
    txlo[i] = fabs(xAx->getErrorLo());
    tyhi[i] = fabs(eff->getErrorHi());
    tylo[i] = fabs(eff->getErrorLo());
  }

  cout<<"NBins : "<<nbins<<endl;

  const double *x = tx;
  const double *xhi = txhi;
  const double *xlo = txlo;
  const double *y = ty;
  const double *yhi = tyhi;
  const double *ylo = tylo;


  TGraphAsymmErrors *b = new TGraphAsymmErrors();
  if(aa == 1) {*b = TGraphAsymmErrors(nbins,x,y,xlo,xhi,ylo,yhi);}
  if(aa == 0) {*b = TGraphAsymmErrors(nbins,x,y,0,0,ylo,yhi);}

  b->SetMaximum(1.1);
  b->SetMinimum(0.0);
  b->SetMarkerStyle(20);
  b->SetMarkerColor(kRed+2);
  b->SetMarkerSize(1.0);
  b->SetTitle("");
  b->GetXaxis()->SetTitleSize(0.1);
  b->GetYaxis()->SetTitleSize(0.1);
  b->GetXaxis()->SetTitle("#eta");
  b->GetYaxis()->SetTitle("Efficiency");
  b->GetXaxis()->CenterTitle();

  for (int i=0; i<nbins; i++) {
    cout << x[i] << " " << y[i] << " " << yhi[i] << " " << ylo[i] << endl;
  }

  return b;

};

bool IsAccept(Double_t pt, Double_t eta)
{

  //return(1);
  //return (TMath::Abs(eta) < 2.4); 

  return (TMath::Abs(eta) < 2.4 &&
	  (    ( TMath::Abs(eta) < 1.0 && pt >= 3.4 ) ||
	       (  1.0 <= TMath::Abs(eta) && TMath::Abs(eta) < 1.5 && pt >= 5.8-2.4*TMath::Abs(eta) ) ||
	       (  1.5 <= TMath::Abs(eta) && pt >= 3.3667 - 7.0/9.0*TMath::Abs(eta)) ));
};

TH1F *g2h(TGraphAsymmErrors *g, double def=1e-3) {
  int n = g->GetN();
  double *x = g->GetX();
  double *y = g->GetY();
  double *exl = g->GetEXlow();
  double *exh = g->GetEXhigh();
  double *eyl = g->GetEYlow();
  double *eyh = g->GetEYhigh();
  double *bins = new double[n+2];
  bins[0] = 0;
  for (int i=0; i<n; i++) bins[i+1] = x[i]-exl[i];
  bins[n+1] = x[n-1]+exh[n-1];
  //  for (int i=0; i<n+2; i++) cout<<"Bin Limit #"<<i<<" = "<<bins[i]<<endl;
  TH1F *ans = new TH1F(Form("tmp%i",gRandom->Integer(1e9)),"tmp",n+1,bins);
  ans->SetBinContent(1,def);
  ans->SetBinError(1,def/5.);
  for (int i=0; i<n; i++) {
    ans->SetBinContent(i+2,y[i]);
    ans->SetBinError(i+2,(eyl[i]+eyh[i])/2);
  }
  ans->SetLineColor(g->GetLineColor());
  ans->SetMarkerColor(g->GetMarkerColor());
  ans->SetMarkerStyle(g->GetMarkerStyle());
  ans->GetYaxis()->SetTitle("Efficiency");
  ans->GetXaxis()->SetTitle("p_{T} [GeV/c]");
  delete[] bins;
  return ans;
};

void setTRatioPlotStyle(TRatioPlot *tr) {
  tr->SetH1DrawOpt("");
  tr->SetH2DrawOpt("");
  tr->Draw();
  tr->GetLowerRefXaxis()->SetTitleOffset(0.9);
  tr->SetLowBottomMargin(0.4);
  tr->SetRightMargin(0.05);
  tr->GetUpperRefYaxis()->SetRangeUser(0,1.1);
  //  tr->GetUpperRefXaxis()->SetRangeUser(0,30);
  tr->GetLowerRefYaxis()->SetRangeUser(0.89,1.11);
  //  tr->GetLowerRefXaxis()->SetRangeUser(0,30);
  tr->GetLowerRefYaxis()->SetNdivisions(503,kFALSE);
  tr->GetUpperRefYaxis()->SetTitle("Efficiency");
  tr->GetLowerRefYaxis()->SetTitle("trd / tnp");
  tr->GetUpperRefYaxis()->SetTitleOffset(0.9);
  tr->GetLowerRefYaxis()->SetTitleOffset(0.9);
  tr->RangeAxisChanged();
};

float GetError(double binlow, double binwidth, TGraphAsymmErrors *g, std::string add=""){
  float res = 0, numpts = 0;
  double *gx = g->GetX();
  double *gy = g->GetY();
  double *gyerr = g->GetEYlow();
  //  cout<<"Filling error for x in ["<<binlow<<","<<binlow+binwidth<<"]"<<endl;
  for (int i=0;i<g->GetN();i++){
    double e = gyerr[i];
    if (fabs(e)>0.02 || isnan(e) || isnan(-e)) e = 0.02;
    if (gx[i]>binlow && gx[i]<=binlow+binwidth){
      /* cout<<"adding error "<<e<<endl; */
      cout<<"FYI: the (X,Y) value in g_original"<<add<<" is ("<<gx[i]<<","<<gy[i]<<")"<<endl;
      res += pow(e,2);
      numpts+=1;
    }
    if(numpts==0 && gx[i]>binlow+binwidth) { //if these bins limits do not contain a point from input graph
      res += pow(e,2);
      numpts+=1;
    }
  }
  if(numpts==0) { //if no errors were found, take the error of the last point of the graph (highest Pt)
    res += pow(gyerr[g->GetN()-1],2);
    numpts+=1;
  }

  return sqrt(res/numpts);
}

void SetGoodTnpError(TGraphAsymmErrors *gfin, TGraphAsymmErrors *gorig, TH1D* h_forBins, TGraphAsymmErrors *gorig2 = NULL){

  for(int i=1;i<=h_forBins->GetNbinsX();i++){
    float e = GetError(h_forBins->GetBinLowEdge(i), h_forBins->GetBinWidth(i), gorig); 
    float e2=0;
    if(gorig2!=NULL) e2 = GetError(h_forBins->GetBinLowEdge(i), h_forBins->GetBinWidth(i), gorig2, "_Glb");
    cout<<"Setting error "<<sqrt(e*e+e2*e2)<<" for point x = "<<gfin->GetX()[i-1]<<endl;
    gfin->SetPointEYlow(i-1,sqrt(e*e+e2*e2));
    gfin->SetPointEYhigh(i-1,sqrt(e*e+e2*e2));
    //    cout<<"Final graphs's (X,Y) value is ("<<gfin->GetX()[i-1]<<","<<gfin->GetY()[i-1]<<")"<<endl; 
  }

  return;
}
#endif // #ifndef helper_h
