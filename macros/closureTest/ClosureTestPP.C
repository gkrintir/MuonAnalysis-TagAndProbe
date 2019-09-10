#define ClosureTestPP_cxx
#include "ClosureTestPP.h"
#include "TFile.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include "TLorentzVector.h"
#include "tnp_mc.h"

//#include <iostream>

using std::cout;
using std::endl;

const int trg_tag1 = pow(2,13);
const int trg_tag2 = pow(2,14);
const int trg_tag3 = pow(2,15);
const int trg_tag4 = pow(2,16);
const int trg_tag5 = pow(2,17);
const int trg_tag6 = pow(2,18);
const int trg_tag7 = pow(2,19);
const int trg_tag8 = pow(2,20);
const int trg_tag9 = pow(2,21);
const int trg_tag10 = pow(2,22);
const int trg_probe = pow(2,4);
//const double drmax = 0.1;
const double mumass = 105.6583715e-3;

// define the bins
double bins_00_12[14] = {3.5, 3.75, 4, 4.25, 4.5, 5, 5.5, 6, 7, 8, 10.5, 14, 18, 30};
double bins_12_18[15] = {2.06, 2.5, 2.75, 3, 3.25, 3.5, 4, 4.5, 5, 6, 7, 9, 14, 18, 30};
double bins_18_21[15] = {1.5, 2., 2.25, 2.5, 2.75, 3, 3.5, 4, 4.5, 5, 6, 7, 9, 13, 20};
double bins_21_24[14] = {1.5, 2., 2.25, 2.5, 2.75, 3, 3.5, 4, 4.5, 5, 6.5, 8.5, 12, 20};

void ClosureTestPP::Loop(const char* filename)
{
  //   In a ROOT session, you can do:
  //      root> .L ClosureTestPP.C
  //      root> ClosureTestPP t
  //      root> t.GetEntry(12); // Fill t data members with entry number 12
  //      root> t.Show();       // Show values of entry 12
  //      root> t.Show(16);     // Read and show values of entry 16
  //      root> t.Loop();       // Loop on all entries
  //

  //     This is the loop skeleton where:
  //    jentry is the global entry number in the chain
  //    ientry is the entry number in the current Tree
  //  Note that the argument to GetEntry must be:
  //    jentry for TChain::GetEntry
  //    ientry for TTree::GetEntry and TBranch::GetEntry
  //
  //       To read only selected branches, Insert statements like:
  // METHOD1:
  //    fChain->SetBranchStatus("*",0);  // disable all branches
  //    fChain->SetBranchStatus("branchname",1);  // activate branchname
  // METHOD2: replace line
  //    fChain->GetEntry(jentry);       //read all branches
  //by  b_branchname->GetEntry(ientry); //read only this branch
  if (fChain == 0) return;

  fChain->SetBranchStatus("*",1);
  // fChain->SetBranchStatus("Reco_trk*",0);
  fChain->SetBranchStatus("*vtx",0);
  //  fChain->SetBranchStatus("Gen_mu*",0);
  Long64_t nentries = fChain->GetEntriesFast();

  TFile *f = new TFile(filename,"RECREATE");
  f->cd();
  TH1D *hden_00_12 = new TH1D("hden_00_12","hden_00_12",13,bins_00_12);
  TH1D *hden_glbwtFromGlb_00_12 = new TH1D("hden_glbwtFromGlb_00_12","hden_glbwtFromGlb_00_12",13,bins_00_12);
  //  TH1D *hden_glbIDwt_00_12 = new TH1D("hden_glbIDwt_00_12","hden_glbIDwt_00_12",13,bins_00_12);
  TH1D *hden_glbIDtrgwtFromGlb_00_12 = new TH1D("hden_glbIDtrgwtFromGlb_00_12","hden_glbIDtrgwtFromGlb_00_12",13,bins_00_12);
  TH1D *hden_glbIDtrgwt_00_12 = new TH1D("hden_glbIDtrgwt_00_12","hden_glbIDtrgwt_00_12",13,bins_00_12);
  TH1D *hnumAcc_00_12 = new TH1D("hnumAcc_00_12","hnumAcc_00_12",13,bins_00_12);
  TH1D *hnumglb_00_12 = new TH1D("hnumglb_00_12","hnumglb_00_12",13,bins_00_12);
  //TH1D *hnumglbID_00_12 = new TH1D("hnumglbID_00_12","hnumglbID_00_12",13,bins_00_12);
  TH1D *hnumglbIDtrg_00_12 = new TH1D("hnumglbIDtrg_00_12","hnumglbIDtrg_00_12",13,bins_00_12);
   
  TH1D *hden_12_18 = new TH1D("hden_12_18","hden_12_18",14,bins_12_18);
  TH1D *hden_glbwtFromGlb_12_18 = new TH1D("hden_glbwtFromGlb_12_18","hden_glbwtFromGlb_12_18",14,bins_12_18);
  //TH1D *hden_glbIDwt_12_18 = new TH1D("hden_glbIDwt_12_18","hden_glbIDwt_12_18",14,bins_12_18);
  TH1D *hden_glbIDtrgwtFromGlb_12_18 = new TH1D("hden_glbIDtrgwtFromGlb_12_18","hden_glbIDtrgwtFromGlb_12_18",14,bins_12_18);
  TH1D *hden_glbIDtrgwt_12_18 = new TH1D("hden_glbIDtrgwt_12_18","hden_glbIDtrgwt_12_18",14,bins_12_18);
  TH1D *hnumAcc_12_18 = new TH1D("hnumAcc_12_18","hnumAcc_12_18",14,bins_12_18);
  TH1D *hnumglb_12_18 = new TH1D("hnumglb_12_18","hnumglb_12_18",14,bins_12_18);
  //TH1D *hnumglbID_12_18 = new TH1D("hnumglbID_12_18","hnumglbID_12_18",14,bins_12_18);
  TH1D *hnumglbIDtrg_12_18 = new TH1D("hnumglbIDtrg_12_18","hnumglbIDtrg_12_18",14,bins_12_18);
   
  TH1D *hden_18_21 = new TH1D("hden_18_21","hden_18_21",14,bins_18_21);
  TH1D *hden_glbwtFromGlb_18_21 = new TH1D("hden_glbwtFromGlb_18_21","hden_glbwtFromGlb_18_21",14,bins_18_21);
  //TH1D *hden_glbIDwt_18_21 = new TH1D("hden_glbIDwt_18_21","hden_glbIDwt_18_21",14,bins_18_21);
  TH1D *hden_glbIDtrgwtFromGlb_18_21 = new TH1D("hden_glbIDtrgwtFromGlb_18_21","hden_glbIDtrgwtFromGlb_18_21",14,bins_18_21);
  TH1D *hden_glbIDtrgwt_18_21 = new TH1D("hden_glbIDtrgwt_18_21","hden_glbIDtrgwt_18_21",14,bins_18_21);
  TH1D *hnumAcc_18_21 = new TH1D("hnumAcc_18_21","hnumAcc_18_21",14,bins_18_21);
  TH1D *hnumglb_18_21 = new TH1D("hnumglb_18_21","hnumglb_18_21",14,bins_18_21);
  //TH1D *hnumglbID_18_21 = new TH1D("hnumglbID_18_21","hnumglbID_18_21",14,bins_18_21);
  TH1D *hnumglbIDtrg_18_21 = new TH1D("hnumglbIDtrg_18_21","hnumglbIDtrg_18_21",14,bins_18_21);
   
  TH1D *hden_21_24 = new TH1D("hden_21_24","hden_21_24",13,bins_21_24);
  TH1D *hden_glbwtFromGlb_21_24 = new TH1D("hden_glbwtFromGlb_21_24","hden_glbwtFromGlb_21_24",13,bins_21_24);
  //TH1D *hden_glbIDwt_21_24 = new TH1D("hden_glbIDwt_21_24","hden_glbIDwt_21_24",13,bins_21_24);
  TH1D *hden_glbIDtrgwtFromGlb_21_24 = new TH1D("hden_glbIDtrgwtFromGlb_21_24","hden_glbIDtrgwtFromGlb_21_24",13,bins_21_24);
  TH1D *hden_glbIDtrgwt_21_24 = new TH1D("hden_glbIDtrgwt_21_24","hden_glbIDtrgwt_21_24",13,bins_21_24);
  TH1D *hnumAcc_21_24 = new TH1D("hnumAcc_21_24","hnumAcc_21_24",13,bins_21_24);
  TH1D *hnumglb_21_24 = new TH1D("hnumglb_21_24","hnumglb_21_24",13,bins_21_24);
  //TH1D *hnumglbID_21_24 = new TH1D("hnumglbID_21_24","hnumglbID_21_24",13,bins_21_24);
  TH1D *hnumglbIDtrg_21_24 = new TH1D("hnumglbIDtrg_21_24","hnumglbIDtrg_21_24",13,bins_21_24);


  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {//nentries
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    if (ientry%100000==0) cout << 100*ientry/(float)nentries<<"%" << endl;
    nb = fChain->GetEntry(jentry);   //nbytes += nb;
    // if (Cut(ientry) < 0) continue;

    // if there's no reco muon is that event, just skip it
    if (Reco_mu_size==0) continue;

    // cout << eventNb << " " << runNb << " " << LS << endl;

    // loop on the generated dimuons
    for (int igen=0; igen<Gen_QQ_size; igen++) {
      bool isgenpltag=false, isgenmitag=false;
      TLorentzVector tlvrecomatchtagpl, tlvrecomatchtagmi;
      TLorentzVector genpl = *((TLorentzVector*) Gen_mu_4mom->At(Gen_QQ_mupl_idx[igen]));
      TLorentzVector genmi = *((TLorentzVector*) Gen_mu_4mom->At(Gen_QQ_mumi_idx[igen]));

      int recmuplIdx = Gen_mu_whichRec[Gen_QQ_mupl_idx[igen]];
      int recmumiIdx = Gen_mu_whichRec[Gen_QQ_mumi_idx[igen]];

      // is the gen muon associated to a tag?
      if (recmuplIdx>-1){
	TLorentzVector recmu = *((TLorentzVector*) Reco_mu_4mom->At(recmuplIdx));
	// if((Reco_mu_trig[recmuplIdx]&trg_tag1)>0 ||
	//    (Reco_mu_trig[recmuplIdx]&trg_tag2)>0 ||
	//    (Reco_mu_trig[recmuplIdx]&trg_tag3)>0 ||
	//    (Reco_mu_trig[recmuplIdx]&trg_tag4)>0 ||
	//    (Reco_mu_trig[recmuplIdx]&trg_tag5)>0 ||
	//    (Reco_mu_trig[recmuplIdx]&trg_tag6)>0 ||
	//    (Reco_mu_trig[recmuplIdx]&trg_tag7)>0 ||
	//    (Reco_mu_trig[recmuplIdx]&trg_tag8)>0 ||
	//    (Reco_mu_trig[recmuplIdx]&trg_tag9)>0 ||
	//    (Reco_mu_trig[recmuplIdx]&trg_tag10)>0){
	// cout<<CutSgMuon(recmuplIdx)<<" "<<((Reco_mu_trig[recmuplIdx]&trg_tag1)>0 ||
	// 				   (Reco_mu_trig[recmuplIdx]&trg_tag2)>0 ||
	// 				   (Reco_mu_trig[recmuplIdx]&trg_tag3)>0 ||
	// 				   (Reco_mu_trig[recmuplIdx]&trg_tag4)>0 ||
	// 				   (Reco_mu_trig[recmuplIdx]&trg_tag5)>0 ||
	// 				   (Reco_mu_trig[recmuplIdx]&trg_tag6)>0 ||
	// 				   (Reco_mu_trig[recmuplIdx]&trg_tag7)>0 ||
	// 				   (Reco_mu_trig[recmuplIdx]&trg_tag8)>0 ||
	// 				   (Reco_mu_trig[recmuplIdx]&trg_tag9)>0 ||
	// 				   (Reco_mu_trig[recmuplIdx]&trg_tag10)>0)<<" "<<isGlobalMuonInAccept2015(&recmu)<<endl;}
	if(CutSgMuon(recmuplIdx) &&  
	   ((Reco_mu_trig[recmuplIdx]&trg_tag1)>0 ||
	     (Reco_mu_trig[recmuplIdx]&trg_tag2)>0 ||
	     (Reco_mu_trig[recmuplIdx]&trg_tag3)>0 ||
	     (Reco_mu_trig[recmuplIdx]&trg_tag4)>0 ||
	     (Reco_mu_trig[recmuplIdx]&trg_tag5)>0 ||
	     (Reco_mu_trig[recmuplIdx]&trg_tag6)>0 ||
	     (Reco_mu_trig[recmuplIdx]&trg_tag7)>0 ||
	     (Reco_mu_trig[recmuplIdx]&trg_tag8)>0 ||
	     (Reco_mu_trig[recmuplIdx]&trg_tag9)>0 ||
	     (Reco_mu_trig[recmuplIdx]&trg_tag10)>0)
	   && recmu.Pt()>4
	   //&& isGlobalMuonInAccept2015(&recmu)
	   ) {
	  isgenpltag = true; tlvrecomatchtagpl = recmu;	  
	}
      }
      if (recmumiIdx>-1){
	TLorentzVector recmu = *((TLorentzVector*) Reco_mu_4mom->At(recmumiIdx));
	if(CutSgMuon(recmumiIdx) &&  
	   ((Reco_mu_trig[recmumiIdx]&trg_tag1)>0 ||
	     (Reco_mu_trig[recmumiIdx]&trg_tag2)>0 ||
	     (Reco_mu_trig[recmumiIdx]&trg_tag3)>0 ||
	     (Reco_mu_trig[recmumiIdx]&trg_tag4)>0 ||
	     (Reco_mu_trig[recmumiIdx]&trg_tag5)>0 ||
	     (Reco_mu_trig[recmumiIdx]&trg_tag6)>0 ||
	     (Reco_mu_trig[recmumiIdx]&trg_tag7)>0 ||
	     (Reco_mu_trig[recmumiIdx]&trg_tag8)>0 ||
	     (Reco_mu_trig[recmumiIdx]&trg_tag9)>0 ||
	     (Reco_mu_trig[recmumiIdx]&trg_tag10)>0)
	   && recmu.Pt()>4
	   //&& isGlobalMuonInAccept2015(&recmu)
	   ) {
	  isgenmitag = true; tlvrecomatchtagmi = recmu;	  
	}
      }

      // // is the positive gen muon a tag, and the negative gen muon (actually, the associated reco muon) in 2018 tight acceptance?
      // if (isgenpltag && isGlobalMuonInTightAccept2018(&probeMi4mom)) {
      // 	double genpt = probeMi4mom.Pt(); double geneta = probeMi4mom.Eta(); 
      // 	double totweight = 1;
      // 	if (fabs(geneta)<1.2) {
      // 	  hden_00_12->Fill(genpt,totweight);
      // 	  totweight *= tnpEff_mc_glb_pp(genpt,geneta);
      // 	  hden_glbwt_00_12->Fill(genpt,totweight);
      // 	  // totweight *= tnpEff_mc_muid_pp(genpt,geneta);
      // 	  // hden_glbIDwt_00_12->Fill(genpt,totweight);
      // 	  totweight *= tnpEff_mc_MuIdTrg_pp(genpt,geneta);
      // 	  hden_glbIDtrgwt_00_12->Fill(genpt,totweight);
      // 	} else if (fabs(geneta)<1.8) {
      // 	  hden_12_18->Fill(genpt,totweight);
      // 	  totweight *= tnpEff_mc_glb_pp(genpt,geneta);
      // 	  hden_glbwt_12_18->Fill(genpt,totweight);
      // 	  // totweight *= tnpEff_mc_muid_pp(genpt,geneta);
      // 	  // hden_glbIDwt_12_18->Fill(genpt,totweight);
      // 	  totweight *= tnpEff_mc_MuIdTrg_pp(genpt,geneta);
      // 	  hden_glbIDtrgwt_12_18->Fill(genpt,totweight);
      // 	} else if (fabs(geneta)<2.1) {
      // 	  hden_18_21->Fill(genpt,totweight);
      // 	  totweight *= tnpEff_mc_glb_pp(genpt,geneta);
      // 	  hden_glbwt_18_21->Fill(genpt,totweight);
      // 	  // totweight *= tnpEff_mc_muid_pp(genpt,geneta);
      // 	  // hden_glbIDwt_18_21->Fill(genpt,totweight);
      // 	  totweight *= tnpEff_mc_MuIdTrg_pp(genpt,geneta);
      // 	  hden_glbIDtrgwt_18_21->Fill(genpt,totweight);
      // 	} else if (fabs(geneta)<2.4) {
      // 	  hden_21_24->Fill(genpt,totweight);
      // 	  totweight *= tnpEff_mc_glb_pp(genpt,geneta);
      // 	  hden_glbwt_21_24->Fill(genpt,totweight);
      // 	  // totweight *= tnpEff_mc_muid_pp(genpt,geneta);
      // 	  // hden_glbIDwt_21_24->Fill(genpt,totweight);
      // 	  totweight *= tnpEff_mc_MuIdTrg_pp(genpt,geneta);
      // 	  hden_glbIDtrgwt_21_24->Fill(genpt,totweight);
      // 	}
      // }
      // // is the negative gen muon a tag, and the positive gen muon in acceptance?
      // if (isgenmitag && isGlobalMuonInTightAccept2018(&probePl4mom)) {
      // 	double genpt = probePl4mom.Pt(); double geneta = probePl4mom.Eta(); 
      // 	double totweight = 1;
      // 	if (fabs(geneta)<1.2) {
      // 	  hden_00_12->Fill(genpt,totweight);
      // 	  totweight *= tnpEff_mc_glb_pp(genpt,geneta);
      // 	  hden_glbwt_00_12->Fill(genpt,totweight);
      // 	  // totweight *= tnpEff_mc_muid_pp(genpt,geneta);
      // 	  // hden_glbIDwt_00_12->Fill(genpt,totweight);
      // 	  totweight *= tnpEff_mc_MuIdTrg_pp(genpt,geneta);
      // 	  hden_glbIDtrgwt_00_12->Fill(genpt,totweight);
      // 	} else if (fabs(geneta)<1.8) {
      // 	  hden_12_18->Fill(genpt,totweight);
      // 	  totweight *= tnpEff_mc_glb_pp(genpt,geneta);
      // 	  hden_glbwt_12_18->Fill(genpt,totweight);
      // 	  // totweight *= tnpEff_mc_muid_pp(genpt,geneta);
      // 	  // hden_glbIDwt_12_18->Fill(genpt,totweight);
      // 	  totweight *= tnpEff_mc_MuIdTrg_pp(genpt,geneta);
      // 	  hden_glbIDtrgwt_12_18->Fill(genpt,totweight);
      // 	} else if (fabs(geneta)<2.1) {
      // 	  hden_18_21->Fill(genpt,totweight);
      // 	  totweight *= tnpEff_mc_glb_pp(genpt,geneta);
      // 	  hden_glbwt_18_21->Fill(genpt,totweight);
      // 	  // totweight *= tnpEff_mc_muid_pp(genpt,geneta);
      // 	  // hden_glbIDwt_18_21->Fill(genpt,totweight);
      // 	  totweight *= tnpEff_mc_MuIdTrg_pp(genpt,geneta);
      // 	  hden_glbIDtrgwt_18_21->Fill(genpt,totweight);
      // 	} else if (fabs(geneta)<2.4) {
      // 	  hden_21_24->Fill(genpt,totweight);
      // 	  totweight *= tnpEff_mc_glb_pp(genpt,geneta);
      // 	  hden_glbwt_21_24->Fill(genpt,totweight);
      // 	  // totweight *= tnpEff_mc_muid_pp(genpt,geneta);
      // 	  // hden_glbIDwt_21_24->Fill(genpt,totweight);
      // 	  totweight *= tnpEff_mc_MuIdTrg_pp(genpt,geneta);
      // 	  hden_glbIDtrgwt_21_24->Fill(genpt,totweight);
      // 	}
      // }

      //For the probe, take the 4mom of the reco muon if it exists, otherwise the gen 4mom if the muon is not reco'd
      TLorentzVector probePl4mom = *((TLorentzVector*) ((recmuplIdx>-1)?(Reco_mu_4mom->At(recmuplIdx)):(Gen_mu_4mom->At(Gen_QQ_mupl_idx[igen]))));
      TLorentzVector probeMi4mom = *((TLorentzVector*) ((recmumiIdx>-1)?(Reco_mu_4mom->At(recmumiIdx)):(Gen_mu_4mom->At(Gen_QQ_mumi_idx[igen]))));
      // TLorentzVector probePl4mom = *((TLorentzVector*) Gen_mu_4mom->At(Gen_QQ_mupl_idx[igen]));
      // TLorentzVector probeMi4mom = *((TLorentzVector*) Gen_mu_4mom->At(Gen_QQ_mumi_idx[igen]));

      // is the positive gen muon a tag, and the negative gen muon (actually, the associated reco muon) in 2018 tight acceptance?
      if (isgenpltag && isGlobalMuonInTightAccept2018(&probeMi4mom)) {
	double genpt = probeMi4mom.Pt(); double geneta = probeMi4mom.Eta(); 
	if (fabs(geneta)<1.2) {
	  hden_00_12->Fill(genpt,1);
	  double w_glb = tnpEff_mc_glb_pp(genpt,geneta);
	  double w_idtrg = tnpEff_mc_MuIdTrg_pp(genpt,geneta);
	  hden_glbIDtrgwt_00_12->Fill(genpt,w_glb*w_idtrg);
	  if(recmumiIdx>-1 && (Reco_mu_SelectionType[recmumiIdx]&2)>0){ //use only muons with kinematics of global muons for the muidtrg eff
	    hden_glbwtFromGlb_00_12->Fill(genpt,1);
	    hden_glbIDtrgwtFromGlb_00_12->Fill(genpt,w_idtrg);
	  }
	} else if (fabs(geneta)<1.8) {
	  hden_12_18->Fill(genpt,1);
	  double w_glb = tnpEff_mc_glb_pp(genpt,geneta);
	  double w_idtrg = tnpEff_mc_MuIdTrg_pp(genpt,geneta);
	  hden_glbIDtrgwt_12_18->Fill(genpt,w_glb*w_idtrg);
	  if(recmumiIdx>-1 && (Reco_mu_SelectionType[recmumiIdx]&2)>0){ //use only muons with kinematics of global muons for the muidtrg eff
	    hden_glbwtFromGlb_12_18->Fill(genpt,1);
	    hden_glbIDtrgwtFromGlb_12_18->Fill(genpt,w_idtrg);
	  }
	} else if (fabs(geneta)<2.1) {
	  hden_18_21->Fill(genpt,1);
	  double w_glb = tnpEff_mc_glb_pp(genpt,geneta);
	  double w_idtrg = tnpEff_mc_MuIdTrg_pp(genpt,geneta);
	  hden_glbIDtrgwt_18_21->Fill(genpt,w_glb*w_idtrg);
	  if(recmumiIdx>-1 && (Reco_mu_SelectionType[recmumiIdx]&2)>0){ //use only muons with kinematics of global muons for the muidtrg eff
	    hden_glbwtFromGlb_18_21->Fill(genpt,1);
	    hden_glbIDtrgwtFromGlb_18_21->Fill(genpt,w_idtrg);
	  }
	} else if (fabs(geneta)<2.4) {
	  hden_21_24->Fill(genpt,1);
	  double w_glb = tnpEff_mc_glb_pp(genpt,geneta);
	  double w_idtrg = tnpEff_mc_MuIdTrg_pp(genpt,geneta);
	  hden_glbIDtrgwt_21_24->Fill(genpt,w_glb*w_idtrg);
	  if(recmumiIdx>-1 && (Reco_mu_SelectionType[recmumiIdx]&2)>0){ //use only muons with kinematics of global muons for the muidtrg eff
	    hden_glbwtFromGlb_21_24->Fill(genpt,1);
	    hden_glbIDtrgwtFromGlb_21_24->Fill(genpt,w_idtrg);
	  }
	}
      }

      // is the negative gen muon a tag, and the positive gen muon in acceptance?
      if (isgenmitag && isGlobalMuonInTightAccept2018(&probePl4mom)) {
	double genpt = probePl4mom.Pt(); double geneta = probePl4mom.Eta(); 
	if (fabs(geneta)<1.2) {
	  hden_00_12->Fill(genpt,1);
	  double w_glb = tnpEff_mc_glb_pp(genpt,geneta);
	  double w_idtrg = tnpEff_mc_MuIdTrg_pp(genpt,geneta);
	  hden_glbIDtrgwt_00_12->Fill(genpt,w_glb*w_idtrg);
	  if(recmuplIdx>-1 && (Reco_mu_SelectionType[recmuplIdx]&2)>0){ //use only muons with kinematics of global muons for the muidtrg eff
	    hden_glbwtFromGlb_00_12->Fill(genpt,1);
	    hden_glbIDtrgwtFromGlb_00_12->Fill(genpt,w_idtrg);
	  }
	} else if (fabs(geneta)<1.8) {
	  hden_12_18->Fill(genpt,1);
	  double w_glb = tnpEff_mc_glb_pp(genpt,geneta);
	  double w_idtrg = tnpEff_mc_MuIdTrg_pp(genpt,geneta);
	  hden_glbIDtrgwt_12_18->Fill(genpt,w_glb*w_idtrg);
	  if(recmuplIdx>-1 && (Reco_mu_SelectionType[recmuplIdx]&2)>0){ //use only muons with kinematics of global muons for the muidtrg eff
	    hden_glbwtFromGlb_12_18->Fill(genpt,1);
	    hden_glbIDtrgwtFromGlb_12_18->Fill(genpt,w_idtrg);
	  }
	} else if (fabs(geneta)<2.1) {
	  hden_18_21->Fill(genpt,1);
	  double w_glb = tnpEff_mc_glb_pp(genpt,geneta);
	  double w_idtrg = tnpEff_mc_MuIdTrg_pp(genpt,geneta);
	  hden_glbIDtrgwt_18_21->Fill(genpt,w_glb*w_idtrg);
	  if(recmuplIdx>-1 && (Reco_mu_SelectionType[recmuplIdx]&2)>0){ //use only muons with kinematics of global muons for the muidtrg eff
	    hden_glbwtFromGlb_18_21->Fill(genpt,1);
	    hden_glbIDtrgwtFromGlb_18_21->Fill(genpt,w_idtrg);
	  }
	} else if (fabs(geneta)<2.4) {
	  hden_21_24->Fill(genpt,1);
	  double w_glb = tnpEff_mc_glb_pp(genpt,geneta);
	  double w_idtrg = tnpEff_mc_MuIdTrg_pp(genpt,geneta);
	  hden_glbIDtrgwt_21_24->Fill(genpt,w_glb*w_idtrg);
	  if(recmuplIdx>-1 && (Reco_mu_SelectionType[recmuplIdx]&2)>0){ //use only muons with kinematics of global muons for the muidtrg eff
	    hden_glbwtFromGlb_21_24->Fill(genpt,1);
	    hden_glbIDtrgwtFromGlb_21_24->Fill(genpt,w_idtrg);
	  }
	}
      }


      // does it match our tag(s)? and if yes, is the other leg in acceptance?
      //      if(recmuplIdx==-1 || recmumiIdx==-1) continue;
      // TLorentzVector *tlvrecomupl = (TLorentzVector*) Reco_mu_4mom->At(recmuplIdx);
      // TLorentzVector *tlvrecomumi = (TLorentzVector*) Reco_mu_4mom->At(recmumiIdx);
      // TLorentzVector *tlvrecoqq = (TLorentzVector*) Reco_QQ_4mom->At(ireco);

      // if (!((isgenpltag && tlvrecomupl->DeltaR(tlvrecomatchtagpl)<1e-1
      //             && isGlobalMuonInTightAccept2018(tlvrecomumi->Pt(),tlvrecomumi->Eta()) && fabs(tlvrecomumi->Eta())>absetamin && fabs(tlvrecomumi->Eta())<absetamax)
      //       || (isgenmitag && tlvrecomumi->DeltaR(tlvrecomatchtagmi)<1e-1 
      //          && isGlobalMuonInTightAccept2018(tlvrecomupl->Pt(),tlvrecomupl->Eta()) && fabs(tlvrecomupl->Eta())>absetamin && fabs(tlvrecomupl->Eta())<absetamax))) continue;

      // trigger
      //      bool okTrg = ((Reco_QQ_trig[ireco] & trg_probe)>0);
      // increment the counter
      if (isgenpltag && isGlobalMuonInTightAccept2018(&probeMi4mom)){
	//	  cout<<"isgenpltag && tlvrecomupl->DeltaR(tlvrecomatchtagpl)<1e-2 && Reco_mu_InTightAcc[recmumiIdx]"<<endl;
	if (fabs((&probeMi4mom)->Eta())<1.2) hnumAcc_00_12->Fill((&probeMi4mom)->Pt()); 
	else if (fabs((&probeMi4mom)->Eta())<1.8) hnumAcc_12_18->Fill((&probeMi4mom)->Pt()); 
	else if (fabs((&probeMi4mom)->Eta())<2.1) hnumAcc_18_21->Fill((&probeMi4mom)->Pt()); 
	else if (fabs((&probeMi4mom)->Eta())<2.4) hnumAcc_21_24->Fill((&probeMi4mom)->Pt()); 

	// GLB
	if(recmumiIdx>-1 && (Reco_mu_SelectionType[recmumiIdx]&2)>0){
	  if (fabs((&probeMi4mom)->Eta())<1.2) hnumglb_00_12->Fill((&probeMi4mom)->Pt());
	  else if (fabs((&probeMi4mom)->Eta())<1.8) hnumglb_12_18->Fill((&probeMi4mom)->Pt());
	  else if (fabs((&probeMi4mom)->Eta())<2.1) hnumglb_18_21->Fill((&probeMi4mom)->Pt());
	  else if (fabs((&probeMi4mom)->Eta())<2.4) hnumglb_21_24->Fill((&probeMi4mom)->Pt());

	  // ID
	  if (Cut_muplmi(recmumiIdx)) {
	    // if (fabs((&probeMi4mom)->Eta())<1.2) hnumglbID_00_12->Fill((&probeMi4mom)->Pt());
	    // else if (fabs((&probeMi4mom)->Eta())<1.8) hnumglbID_12_18->Fill((&probeMi4mom)->Pt());
	    // else if (fabs((&probeMi4mom)->Eta())<2.1) hnumglbID_18_21->Fill((&probeMi4mom)->Pt());
	    // else if (fabs((&probeMi4mom)->Eta())<2.4) hnumglbID_21_24->Fill((&probeMi4mom)->Pt());

	    // trigger: do it on the single muon
	    bool oktrig = (Reco_mu_trig[recmumiIdx]&trg_probe)>0 && (Reco_mu_trig[recmuplIdx]&trg_probe)>0 ;

	    if (oktrig){// && okTrg) {
	      if (fabs((&probeMi4mom)->Eta())<1.2) hnumglbIDtrg_00_12->Fill((&probeMi4mom)->Pt());
	      else if (fabs((&probeMi4mom)->Eta())<1.8) hnumglbIDtrg_12_18->Fill((&probeMi4mom)->Pt());
	      else if (fabs((&probeMi4mom)->Eta())<2.1) hnumglbIDtrg_18_21->Fill((&probeMi4mom)->Pt());
	      else if (fabs((&probeMi4mom)->Eta())<2.4) hnumglbIDtrg_21_24->Fill((&probeMi4mom)->Pt());
	    }
	  }
	}
      } // isgenpltag

      if (isgenmitag && isGlobalMuonInTightAccept2018(&probePl4mom)){
	if (fabs((&probePl4mom)->Eta())<1.2) hnumAcc_00_12->Fill((&probePl4mom)->Pt()); 
	else if (fabs((&probePl4mom)->Eta())<1.8) hnumAcc_12_18->Fill((&probePl4mom)->Pt());
	else if (fabs((&probePl4mom)->Eta())<2.1) hnumAcc_18_21->Fill((&probePl4mom)->Pt());
	else if (fabs((&probePl4mom)->Eta())<2.4) hnumAcc_21_24->Fill((&probePl4mom)->Pt());

	// GLB
	if(recmumiIdx>-1 && (Reco_mu_SelectionType[recmuplIdx]&2)>0){
	  if (fabs((&probePl4mom)->Eta())<1.2) hnumglb_00_12->Fill((&probePl4mom)->Pt());
	  else if (fabs((&probePl4mom)->Eta())<1.8) hnumglb_12_18->Fill((&probePl4mom)->Pt());
	  else if (fabs((&probePl4mom)->Eta())<2.1) hnumglb_18_21->Fill((&probePl4mom)->Pt());
	  else if (fabs((&probePl4mom)->Eta())<2.4) hnumglb_21_24->Fill((&probePl4mom)->Pt());

	  // ID
	  if (Cut_muplmi(recmuplIdx)) {
	    // if (fabs((&probePl4mom)->Eta())<1.2) hnumglbID_00_12->Fill((&probePl4mom)->Pt());
	    // else if (fabs((&probePl4mom)->Eta())<1.8) hnumglbID_12_18->Fill((&probePl4mom)->Pt());
	    // else if (fabs((&probePl4mom)->Eta())<2.1) hnumglbID_18_21->Fill((&probePl4mom)->Pt());
	    // else if (fabs((&probePl4mom)->Eta())<2.4) hnumglbID_21_24->Fill((&probePl4mom)->Pt());

	    // trigger: do it on the single muon
	    bool oktrig = (Reco_mu_trig[recmuplIdx]&trg_probe)>0 && (Reco_mu_trig[recmumiIdx]&trg_probe)>0;

	    if (oktrig){// && okTrg) {
	      if (fabs((&probePl4mom)->Eta())<1.2) hnumglbIDtrg_00_12->Fill((&probePl4mom)->Pt());
	      else if (fabs((&probePl4mom)->Eta())<1.8) hnumglbIDtrg_12_18->Fill((&probePl4mom)->Pt());
	      else if (fabs((&probePl4mom)->Eta())<2.1) hnumglbIDtrg_18_21->Fill((&probePl4mom)->Pt());
	      else if (fabs((&probePl4mom)->Eta())<2.4) hnumglbIDtrg_21_24->Fill((&probePl4mom)->Pt());
	    }
	  }
	}
      } // isgenmitag




      // // loop on QQ's: they should be 
      // // - opposite sign, 
      // // - one leg corresponding to the +/- tag muon found above, 
      // // - within [2.7,3.3], 
      // // - matched to the trigger, 
      // // - and the other leg than the tag should be in acceptance // and matched to a gen? To avoid checking the efficiency on fakes?
      // for (int ireco=0; ireco<Reco_QQ_size; ireco++) {
      // 	// does it match our tag(s)? and if yes, is the other leg in acceptance?
      // 	int recProbePlIdx = Reco_QQ_mupl_idx[ireco];
      // 	int recProbeMiIdx = Reco_QQ_mumi_idx[ireco];
      // 	if(recProbePlIdx==-1 || recProbeMiIdx==-1) continue;
      // 	TLorentzVector *tlvrecomupl = (TLorentzVector*) Reco_mu_4mom->At(recProbePlIdx);
      // 	TLorentzVector *tlvrecomumi = (TLorentzVector*) Reco_mu_4mom->At(recProbeMiIdx);
      // 	TLorentzVector *tlvrecoqq = (TLorentzVector*) Reco_QQ_4mom->At(ireco);
      // 	// if (!((isgenpltag && tlvrecomupl->DeltaR(tlvrecomatchtagpl)<1e-1
      // 	//             && isGlobalMuonInTightAccept2018(tlvrecomumi->Pt(),tlvrecomumi->Eta()) && fabs(tlvrecomumi->Eta())>absetamin && fabs(tlvrecomumi->Eta())<absetamax)
      // 	//       || (isgenmitag && tlvrecomumi->DeltaR(tlvrecomatchtagmi)<1e-1 
      // 	//          && isGlobalMuonInTightAccept2018(tlvrecomupl->Pt(),tlvrecomupl->Eta()) && fabs(tlvrecomupl->Eta())>absetamin && fabs(tlvrecomupl->Eta())<absetamax))) continue;

      // 	// dimuon cuts
      // 	if (tlvrecoqq->M()<2.7 || tlvrecoqq->M()>3.3) continue;
      // 	if (Reco_QQ_sign[ireco] != 0) continue;

      // 	// trigger
      // 	bool okTrg = ((Reco_QQ_trig[ireco] & trg_probe)>0);
      // 	// increment the counter
      // 	if (isgenpltag && tlvrecomupl->DeltaR(tlvrecomatchtagpl)<1e-2 && Reco_mu_InTightAcc[recProbeMiIdx] && Reco_mu_whichGen[recProbeMiIdx]>-1) {
      // 	  //	  cout<<"isgenpltag && tlvrecomupl->DeltaR(tlvrecomatchtagpl)<1e-2 && Reco_mu_InTightAcc[recProbeMiIdx]"<<endl;
      // 	  if (fabs(tlvrecomumi->Eta())<1.2) hnumAcc_00_12->Fill(tlvrecomumi->Pt()); 
      // 	  else if (fabs(tlvrecomumi->Eta())<1.8) hnumAcc_12_18->Fill(tlvrecomumi->Pt()); 
      // 	  else if (fabs(tlvrecomumi->Eta())<2.1) hnumAcc_18_21->Fill(tlvrecomumi->Pt()); 
      // 	  else if (fabs(tlvrecomumi->Eta())<2.4) hnumAcc_21_24->Fill(tlvrecomumi->Pt()); 

      // 	  // GLB
      // 	  if((Reco_mu_SelectionType[recProbeMiIdx]&2)>0){
      // 	    if (fabs(tlvrecomumi->Eta())<1.2) hnumglb_00_12->Fill(tlvrecomumi->Pt());
      // 	    else if (fabs(tlvrecomumi->Eta())<1.8) hnumglb_12_18->Fill(tlvrecomumi->Pt());
      // 	    else if (fabs(tlvrecomumi->Eta())<2.1) hnumglb_18_21->Fill(tlvrecomumi->Pt());
      // 	    else if (fabs(tlvrecomumi->Eta())<2.4) hnumglb_21_24->Fill(tlvrecomumi->Pt());

      // 	    // ID
      // 	    if (Cut_muplmi(recProbeMiIdx)) {
      // 	      // if (fabs(tlvrecomumi->Eta())<1.2) hnumglbID_00_12->Fill(tlvrecomumi->Pt());
      // 	      // else if (fabs(tlvrecomumi->Eta())<1.8) hnumglbID_12_18->Fill(tlvrecomumi->Pt());
      // 	      // else if (fabs(tlvrecomumi->Eta())<2.1) hnumglbID_18_21->Fill(tlvrecomumi->Pt());
      // 	      // else if (fabs(tlvrecomumi->Eta())<2.4) hnumglbID_21_24->Fill(tlvrecomumi->Pt());

      // 	      // trigger: do it on the single muon
      // 	      bool oktrig = (Reco_mu_trig[recProbeMiIdx]&trg_probe)>0 ;

      // 	      if (oktrig && okTrg) {
      // 		if (fabs(tlvrecomumi->Eta())<1.2) hnumglbIDtrg_00_12->Fill(tlvrecomumi->Pt());
      // 		else if (fabs(tlvrecomumi->Eta())<1.8) hnumglbIDtrg_12_18->Fill(tlvrecomumi->Pt());
      // 		else if (fabs(tlvrecomumi->Eta())<2.1) hnumglbIDtrg_18_21->Fill(tlvrecomumi->Pt());
      // 		else if (fabs(tlvrecomumi->Eta())<2.4) hnumglbIDtrg_21_24->Fill(tlvrecomumi->Pt());
      // 	      }
      // 	    }
      // 	  }
      // 	} // isgenpltag

      // 	if (isgenmitag && tlvrecomumi->DeltaR(tlvrecomatchtagmi)<1e-2 && Reco_mu_InTightAcc[recProbePlIdx] && Reco_mu_whichGen[recProbePlIdx]>-1) {
      // 	  if (fabs(tlvrecomupl->Eta())<1.2) hnumAcc_00_12->Fill(tlvrecomupl->Pt()); 
      // 	  else if (fabs(tlvrecomupl->Eta())<1.8) hnumAcc_12_18->Fill(tlvrecomupl->Pt());
      // 	  else if (fabs(tlvrecomupl->Eta())<2.1) hnumAcc_18_21->Fill(tlvrecomupl->Pt());
      // 	  else if (fabs(tlvrecomupl->Eta())<2.4) hnumAcc_21_24->Fill(tlvrecomupl->Pt());

      // 	  // GLB
      // 	  if((Reco_mu_SelectionType[recProbePlIdx]&2)>0){
      // 	    if (fabs(tlvrecomupl->Eta())<1.2) hnumglb_00_12->Fill(tlvrecomupl->Pt());
      // 	    else if (fabs(tlvrecomupl->Eta())<1.8) hnumglb_12_18->Fill(tlvrecomupl->Pt());
      // 	    else if (fabs(tlvrecomupl->Eta())<2.1) hnumglb_18_21->Fill(tlvrecomupl->Pt());
      // 	    else if (fabs(tlvrecomupl->Eta())<2.4) hnumglb_21_24->Fill(tlvrecomupl->Pt());

      // 	    // ID
      // 	    if (Cut_muplmi(recProbePlIdx)) {
      // 	      // if (fabs(tlvrecomupl->Eta())<1.2) hnumglbID_00_12->Fill(tlvrecomupl->Pt());
      // 	      // else if (fabs(tlvrecomupl->Eta())<1.8) hnumglbID_12_18->Fill(tlvrecomupl->Pt());
      // 	      // else if (fabs(tlvrecomupl->Eta())<2.1) hnumglbID_18_21->Fill(tlvrecomupl->Pt());
      // 	      // else if (fabs(tlvrecomupl->Eta())<2.4) hnumglbID_21_24->Fill(tlvrecomupl->Pt());

      // 	      // trigger: do it on the single muon
      // 	      bool oktrig = (Reco_mu_trig[recProbePlIdx]&trg_probe)>0 ;

      // 	      if (oktrig && okTrg) {
      // 		if (fabs(tlvrecomupl->Eta())<1.2) hnumglbIDtrg_00_12->Fill(tlvrecomupl->Pt());
      // 		else if (fabs(tlvrecomupl->Eta())<1.8) hnumglbIDtrg_12_18->Fill(tlvrecomupl->Pt());
      // 		else if (fabs(tlvrecomupl->Eta())<2.1) hnumglbIDtrg_18_21->Fill(tlvrecomupl->Pt());
      // 		else if (fabs(tlvrecomupl->Eta())<2.4) hnumglbIDtrg_21_24->Fill(tlvrecomupl->Pt());
      // 	      }
      // 	    }
      // 	  }
      // 	} // isgenmitag
      // } // recoQQsize (probe) loop



    } // genQQsize loop
  } // event loop


  f->Write();
  f->Close();
  delete f;
}
