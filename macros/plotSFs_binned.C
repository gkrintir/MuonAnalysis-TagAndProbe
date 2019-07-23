#include "tnp_weight_lowPt.h"
#include "TF1.h"
#include "TLegend.h"
#include "TH1.h"
#include "TCanvas.h"

Double_t tnp_weight_ppb_wrapper(Double_t *x, Double_t *par) {
	if (par[2] < 0.5) return tnp_weight_trkM_ppb(x[0], par[1]);
	else if (par[2] < 1.5) return tnp_weight_muid_ppb(x[0], par[0], par[1]);
	else return tnp_weight_trg_ppb(x[0], par[0], par[1]);
}

float ptmin(float etamax) {
	float ans = 0.8;
	if (etamax<=0.81) ans = 3.3;
	else if (etamax <= 1.5) ans = 5.81 - 3.14*fabs(etamax);
	else if (etamax <= 2.1) ans = max(1.89 - 0.526*fabs(etamax),0.8); 
	else ans = 0.8;
	ans = (int) (ans*10.);
	ans = ans/10.;
	return ans;
}

void plotSFs_binned() {
	TCanvas *c1 = new TCanvas();
	TH1F *haxes = new TH1F("haxes", ";p_{T} [GeV/c];Scale factor", 1, 0, 25);
	TH1F *haxeseta = new TH1F("haxes20", ";#eta;Scale factor", 1, -2.4, 2.4);
	gStyle->SetOptStat(0);

	float *etamin = NULL, *etamax = NULL;
	float eta, ptminval, ptmaxval;

	etamin = new float[4]; etamin[0] = 0.0; etamin[1] = 0.8; etamin[2] = 1.5; etamin[3] = 2.1;
	etamax = new float[4]; etamax[0] = 0.8; etamax[1] = 1.5; etamax[2] = 2.1; etamax[3] = 2.4;

	const char* tags[3] = { "trkM_","muid_","trg_" };
	const char* names[3] = { "Trk M","MuID","Trigger" };
	const double range[3] = { 0.1,0.03,0.1 };

	for (int j = 1; j < 2; j++)
	{
		// ppb
	   // int ietamax = (j==0) ? 0 : 2; // for trigger, only 1 plot (eta dependence)
		int ietamax = 3;
		for (int ieta = 0; ieta <= ietamax; ieta++) {
			if (j > 0) {
				haxes->GetYaxis()->SetRangeUser(1 - 2.*range[j], 1 + range[j]);
				haxes->Draw();
			}
			else
			{
				haxeseta->GetYaxis()->SetRangeUser(0.85, 1.1);
				haxeseta->Draw();
			}

			TLegend *tleg = new TLegend(0.50, 0.16, 0.88, 0.47);
			tleg->SetTextSize(0.04);
			tleg->SetBorderSize(0);

			eta = (etamax[ieta] + etamin[ieta]) / 2.;
			ptminval = ptmin(etamax[ieta]);
			ptmaxval = 25;

				//for (int i = 1; i <= 100; i++) {
				//	TF1 *fnom = new TF1(Form("f%i", i), tnp_weight_ppb_wrapper, ptminval, ptmaxval, 3);
				//	fnom->SetParameters(eta, i, j);
				//	fnom->SetLineColor(kBlack);
				//	fnom->Draw("same");
				//}

			//TF1 *fbinned = new TF1("fbinned", tnp_weight_ppb_wrapper, ptminval, ptmaxval, 3);
			//fbinned->SetParameters(eta, -10, j);
			//fbinned->SetLineColor(kRed);
			//fbinned->Draw("same"); 
			TF1 *fbinnedp = new TF1("fbinnedp", tnp_weight_ppb_wrapper, ptminval, ptmaxval, 3);
			fbinnedp->SetParameters(eta, -11, j);
			fbinnedp->SetLineColor(kCyan);
			fbinnedp->Draw("same");
			TF1 *fbinnedm = new TF1("fbinnedm", tnp_weight_ppb_wrapper, ptminval, ptmaxval, 3);
			fbinnedm->SetParameters(eta, -12, j);
			fbinnedm->SetLineColor(kCyan);
			fbinnedm->Draw("same");
			TF1 *fsystp = new TF1("fsystp", tnp_weight_ppb_wrapper, ptminval, ptmaxval, 3);
			fsystp->SetParameters(eta, -13, j);
			fsystp->SetLineColor(kGreen + 2);
			fsystp->Draw("same");
			TF1 *fsystm = new TF1("fsystm", tnp_weight_ppb_wrapper, ptminval, ptmaxval, 3);
			fsystm->SetParameters(eta, -14, j);
			fsystm->SetLineColor(kGreen + 2);
			fsystm->Draw("same");
			TF1 *fbinned = new TF1("fbinned", tnp_weight_ppb_wrapper, ptminval, ptmaxval, 3);
			fbinned->SetParameters(eta, -10, j);
			fbinned->SetLineColor(kRed);
			fbinned->Draw("same");

			if (j == 0) tleg->SetHeader(Form("#splitline{pPb, %s}{#eta #in [-2.4,2.4], p_{T}>15 GeV/c}", names[j]));
			else tleg->SetHeader(Form("#splitline{pPb, %s}{#eta #in [%.1f,%.1f], p_{T}>%.1f GeV/c}", names[j], etamin[ieta], etamax[ieta], ptminval));

			tleg->AddEntry(fbinned, "Nominal binned", "l");
			if (j > 0) tleg->AddEntry("fbinnedp", "stat (+/1#sigma)", "l");
			//if (j == 0) tleg->AddEntry(fp, "syst (+/1#sigma)", "l");
			if (j > 0) tleg->AddEntry(fsystp, "syst (+/1#sigma)", "l");
			tleg->Draw();
			c1->SaveAs(Form("tnp_ppb_%seta%.1f-%.1f.pdf", tags[j], etamin[ieta], etamax[ieta]));
			c1->SaveAs(Form("tnp_ppb_%seta%.1f-%.1f.png", tags[j], etamin[ieta], etamax[ieta]));
		} // eta loop
	} // eff type loop
}
