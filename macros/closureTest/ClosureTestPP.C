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

const ULong64_t trg_tag14 = pow(2,12);
const ULong64_t trg_tag1 = pow(2,13);
const ULong64_t trg_tag2 = pow(2,14);
const ULong64_t trg_tag3 = pow(2,15);
const ULong64_t trg_tag4 = pow(2,16);
const ULong64_t trg_tag5 = pow(2,17);
const ULong64_t trg_tag6 = pow(2,18);
const ULong64_t trg_tag7 = pow(2,19);
const ULong64_t trg_tag8 = pow(2,20);
const ULong64_t trg_tag9 = pow(2,21);
const ULong64_t trg_tag10 = pow(2,22);
const ULong64_t trg_tag11 = pow(2,23);
const ULong64_t trg_tag12 = pow(2,24);
const ULong64_t trg_tag13 = pow(2,25);
const ULong64_t trg_probe = pow(2,3);
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
  TH1D *hden_glbIDtrgwtFromTrk_00_12 = new TH1D("hden_glbIDtrgwtFromTrk_00_12","hden_glbIDtrgwtFromTrk_00_12",13,bins_00_12);
  TH1D *hden_glbwt_00_12 = new TH1D("hden_glbwt_00_12","hden_glbwt_00_12",13,bins_00_12);
  //  TH1D *hden_glbIDwt_00_12 = new TH1D("hden_glbIDwt_00_12","hden_glbIDwt_00_12",13,bins_00_12);
  TH1D *hden_glbIDwtFromGlb_00_12 = new TH1D("hden_glbIDwtFromGlb_00_12","hden_glbIDwtFromGlb_00_12",13,bins_00_12);
  TH1D *hden_glbIDtrgwtFromGlb_00_12 = new TH1D("hden_glbIDtrgwtFromGlb_00_12","hden_glbIDtrgwtFromGlb_00_12",13,bins_00_12);
  TH1D *hden_glbIDtrgwt_00_12 = new TH1D("hden_glbIDtrgwt_00_12","hden_glbIDtrgwt_00_12",13,bins_00_12);
  TH1D *hnumAcc_00_12 = new TH1D("hnumAcc_00_12","hnumAcc_00_12",13,bins_00_12);
  TH1D *hnumglb_00_12 = new TH1D("hnumglb_00_12","hnumglb_00_12",13,bins_00_12);
  TH1D *hnumglbFromGen_00_12 = new TH1D("hnumglbFromGen_00_12","hnumglbFromGen_00_12",13,bins_00_12);
  TH1D *hnumglbID_00_12 = new TH1D("hnumglbID_00_12","hnumglbID_00_12",13,bins_00_12);
  TH1D *hnumglbIDtrg_00_12 = new TH1D("hnumglbIDtrg_00_12","hnumglbIDtrg_00_12",13,bins_00_12);
  TH1D *hnumPt_Acc_00_12 = new TH1D("hnumPt_Acc_00_12","hnumPt_Acc_00_12",80,3.5,30);
  TH1D *hnumPt_Glb_00_12 = new TH1D("hnumPt_Glb_00_12","hnumPt_Glb_00_12",80,3.5,30);
  TH1D *hnumPt_GlbFromGen_00_12 = new TH1D("hnumPt_GlbFromGen_00_12","hnumPt_GlbFromGen_00_12",80,3.5,30);
  TH1D *hnumPt_ID_00_12 = new TH1D("hnumPt_ID_00_12","hnumPt_ID_00_12",80,3.5,30);
  TH1D *hnumPt_IDtrg_00_12 = new TH1D("hnumPt_IDtrg_00_12","hnumPt_IDtrg_00_12",80,3.5,30);
  TH1D *hnumPt_IDtrgFail_00_12 = new TH1D("hnumPt_IDtrgFail_00_12","hnumPt_IDtrgFail_00_12",80,3.5,30);
  TH1D *hnumAbseta_Acc_00_12 = new TH1D("hnumAbseta_Acc_00_12","hnumAbseta_Acc_00_12",80,0,2.4);
  TH1D *hnumAbseta_Glb_00_12 = new TH1D("hnumAbseta_Glb_00_12","hnumAbseta_Glb_00_12",80,0,2.4);
  TH1D *hnumAbseta_GlbFromGen_00_12 = new TH1D("hnumAbseta_GlbFromGen_00_12","hnumAbseta_GlbFromGen_00_12",80,0,2.4);
  TH1D *hnumAbseta_IDtrg_00_12 = new TH1D("hnumAbseta_IDtrg_00_12","hnumAbseta_IDtrg_00_12",80,0,2.4);

  TH1D *hden_12_18 = new TH1D("hden_12_18","hden_12_18",14,bins_12_18);
  TH1D *hden_glbwtFromGlb_12_18 = new TH1D("hden_glbwtFromGlb_12_18","hden_glbwtFromGlb_12_18",14,bins_12_18);
  TH1D *hden_glbIDtrgwtFromTrk_12_18 = new TH1D("hden_glbIDtrgwtFromTrk_12_18","hden_glbIDtrgwtFromTrk_12_18",14,bins_12_18);
  TH1D *hden_glbwt_12_18 = new TH1D("hden_glbwt_12_18","hden_glbwt_12_18",14,bins_12_18);
  //  TH1D *hden_glbIDwt_12_18 = new TH1D("hden_glbIDwt_12_18","hden_glbIDwt_12_18",14,bins_12_18);
  TH1D *hden_glbIDwtFromGlb_12_18 = new TH1D("hden_glbIDwtFromGlb_12_18","hden_glbIDwtFromGlb_12_18",14,bins_12_18);
  TH1D *hden_glbIDtrgwtFromGlb_12_18 = new TH1D("hden_glbIDtrgwtFromGlb_12_18","hden_glbIDtrgwtFromGlb_12_18",14,bins_12_18);
  TH1D *hden_glbIDtrgwt_12_18 = new TH1D("hden_glbIDtrgwt_12_18","hden_glbIDtrgwt_12_18",14,bins_12_18);
  TH1D *hnumAcc_12_18 = new TH1D("hnumAcc_12_18","hnumAcc_12_18",14,bins_12_18);
  TH1D *hnumglb_12_18 = new TH1D("hnumglb_12_18","hnumglb_12_18",14,bins_12_18);
  TH1D *hnumglbFromGen_12_18 = new TH1D("hnumglbFromGen_12_18","hnumglbFromGen_12_18",14,bins_12_18);
  TH1D *hnumglbID_12_18 = new TH1D("hnumglbID_12_18","hnumglbID_12_18",14,bins_12_18);
  TH1D *hnumglbIDtrg_12_18 = new TH1D("hnumglbIDtrg_12_18","hnumglbIDtrg_12_18",14,bins_12_18);
  TH1D *hnumPt_Acc_12_18 = new TH1D("hnumPt_Acc_12_18","hnumPt_Acc_12_18",80,3.5,30);
  TH1D *hnumPt_Glb_12_18 = new TH1D("hnumPt_Glb_12_18","hnumPt_Glb_12_18",80,3.5,30);
  TH1D *hnumPt_GlbFromGen_12_18 = new TH1D("hnumPt_GlbFromGen_12_18","hnumPt_GlbFromGen_12_18",80,3.5,30);
  TH1D *hnumPt_ID_12_18 = new TH1D("hnumPt_ID_12_18","hnumPt_ID_12_18",80,3.5,30);
  TH1D *hnumPt_IDtrg_12_18 = new TH1D("hnumPt_IDtrg_12_18","hnumPt_IDtrg_12_18",80,3.5,30);
  TH1D *hnumPt_IDtrgFail_12_18 = new TH1D("hnumPt_IDtrgFail_12_18","hnumPt_IDtrgFail_12_18",80,3.5,30);
  TH1D *hnumAbseta_Acc_12_18 = new TH1D("hnumAbseta_Acc_12_18","hnumAbseta_Acc_12_18",80,0,2.4);
  TH1D *hnumAbseta_Glb_12_18 = new TH1D("hnumAbseta_Glb_12_18","hnumAbseta_Glb_12_18",80,0,2.4);
  TH1D *hnumAbseta_GlbFromGen_12_18 = new TH1D("hnumAbseta_GlbFromGen_12_18","hnumAbseta_GlbFromGen_12_18",80,0,2.4);
  TH1D *hnumAbseta_IDtrg_12_18 = new TH1D("hnumAbseta_IDtrg_12_18","hnumAbseta_IDtrg_12_18",80,0,2.4);

  TH1D *hden_18_21 = new TH1D("hden_18_21","hden_18_21",14,bins_18_21);
  TH1D *hden_glbwtFromGlb_18_21 = new TH1D("hden_glbwtFromGlb_18_21","hden_glbwtFromGlb_18_21",14,bins_18_21);
  TH1D *hden_glbIDtrgwtFromTrk_18_21 = new TH1D("hden_glbIDtrgwtFromTrk_18_21","hden_glbIDtrgwtFromTrk_18_21",14,bins_18_21);
  TH1D *hden_glbwt_18_21 = new TH1D("hden_glbwt_18_21","hden_glbwt_18_21",14,bins_18_21);
  //  TH1D *hden_glbIDwt_18_21 = new TH1D("hden_glbIDwt_18_21","hden_glbIDwt_18_21",14,bins_18_21);
  TH1D *hden_glbIDwtFromGlb_18_21 = new TH1D("hden_glbIDwtFromGlb_18_21","hden_glbIDwtFromGlb_18_21",14,bins_18_21);
  TH1D *hden_glbIDtrgwtFromGlb_18_21 = new TH1D("hden_glbIDtrgwtFromGlb_18_21","hden_glbIDtrgwtFromGlb_18_21",14,bins_18_21);
  TH1D *hden_glbIDtrgwt_18_21 = new TH1D("hden_glbIDtrgwt_18_21","hden_glbIDtrgwt_18_21",14,bins_18_21);
  TH1D *hnumAcc_18_21 = new TH1D("hnumAcc_18_21","hnumAcc_18_21",14,bins_18_21);
  TH1D *hnumglb_18_21 = new TH1D("hnumglb_18_21","hnumglb_18_21",14,bins_18_21);
  TH1D *hnumglbFromGen_18_21 = new TH1D("hnumglbFromGen_18_21","hnumglbFromGen_18_21",14,bins_18_21);
  TH1D *hnumglbID_18_21 = new TH1D("hnumglbID_18_21","hnumglbID_18_21",14,bins_18_21);
  TH1D *hnumglbIDtrg_18_21 = new TH1D("hnumglbIDtrg_18_21","hnumglbIDtrg_18_21",14,bins_18_21);
  TH1D *hnumPt_Acc_18_21 = new TH1D("hnumPt_Acc_18_21","hnumPt_Acc_18_21",80,3.5,30);
  TH1D *hnumPt_Glb_18_21 = new TH1D("hnumPt_Glb_18_21","hnumPt_Glb_18_21",80,3.5,30);
  TH1D *hnumPt_GlbFromGen_18_21 = new TH1D("hnumPt_GlbFromGen_18_21","hnumPt_GlbFromGen_18_21",80,3.5,30);
  TH1D *hnumPt_ID_18_21 = new TH1D("hnumPt_ID_18_21","hnumPt_ID_18_21",80,3.5,30);
  TH1D *hnumPt_IDtrg_18_21 = new TH1D("hnumPt_IDtrg_18_21","hnumPt_IDtrg_18_21",80,3.5,30);
  TH1D *hnumPt_IDtrgFail_18_21 = new TH1D("hnumPt_IDtrgFail_18_21","hnumPt_IDtrgFail_18_21",80,3.5,30);
  TH1D *hnumAbseta_Acc_18_21 = new TH1D("hnumAbseta_Acc_18_21","hnumAbseta_Acc_18_21",80,0,2.4);
  TH1D *hnumAbseta_Glb_18_21 = new TH1D("hnumAbseta_Glb_18_21","hnumAbseta_Glb_18_21",80,0,2.4);
  TH1D *hnumAbseta_GlbFromGen_18_21 = new TH1D("hnumAbseta_GlbFromGen_18_21","hnumAbseta_GlbFromGen_18_21",80,0,2.4);
  TH1D *hnumAbseta_IDtrg_18_21 = new TH1D("hnumAbseta_IDtrg_18_21","hnumAbseta_IDtrg_18_21",80,0,2.4);

  TH1D *hden_21_24 = new TH1D("hden_21_24","hden_21_24",13,bins_21_24);
  TH1D *hden_glbwtFromGlb_21_24 = new TH1D("hden_glbwtFromGlb_21_24","hden_glbwtFromGlb_21_24",13,bins_21_24);
  TH1D *hden_glbIDtrgwtFromTrk_21_24 = new TH1D("hden_glbIDtrgwtFromTrk_21_24","hden_glbIDtrgwtFromTrk_21_24",13,bins_21_24);
  TH1D *hden_glbwt_21_24 = new TH1D("hden_glbwt_21_24","hden_glbwt_21_24",13,bins_21_24);
  //  TH1D *hden_glbIDwt_21_24 = new TH1D("hden_glbIDwt_21_24","hden_glbIDwt_21_24",13,bins_21_24);
  TH1D *hden_glbIDwtFromGlb_21_24 = new TH1D("hden_glbIDwtFromGlb_21_24","hden_glbIDwtFromGlb_21_24",13,bins_21_24);
  TH1D *hden_glbIDtrgwtFromGlb_21_24 = new TH1D("hden_glbIDtrgwtFromGlb_21_24","hden_glbIDtrgwtFromGlb_21_24",13,bins_21_24);
  TH1D *hden_glbIDtrgwt_21_24 = new TH1D("hden_glbIDtrgwt_21_24","hden_glbIDtrgwt_21_24",13,bins_21_24);
  TH1D *hnumAcc_21_24 = new TH1D("hnumAcc_21_24","hnumAcc_21_24",13,bins_21_24);
  TH1D *hnumglb_21_24 = new TH1D("hnumglb_21_24","hnumglb_21_24",13,bins_21_24);
  TH1D *hnumglbFromGen_21_24 = new TH1D("hnumglbFromGen_21_24","hnumglbFromGen_21_24",13,bins_21_24);
  TH1D *hnumglbID_21_24 = new TH1D("hnumglbID_21_24","hnumglbID_21_24",13,bins_21_24);
  TH1D *hnumglbIDtrg_21_24 = new TH1D("hnumglbIDtrg_21_24","hnumglbIDtrg_21_24",13,bins_21_24);
  TH1D *hnumPt_Acc_21_24 = new TH1D("hnumPt_Acc_21_24","hnumPt_Acc_21_24",80,3.5,30);
  TH1D *hnumPt_Glb_21_24 = new TH1D("hnumPt_Glb_21_24","hnumPt_Glb_21_24",80,3.5,30);
  TH1D *hnumPt_GlbFromGen_21_24 = new TH1D("hnumPt_GlbFromGen_21_24","hnumPt_GlbFromGen_21_24",80,3.5,30);
  TH1D *hnumPt_ID_21_24 = new TH1D("hnumPt_ID_21_24","hnumPt_ID_21_24",80,3.5,30);
  TH1D *hnumPt_IDtrg_21_24 = new TH1D("hnumPt_IDtrg_21_24","hnumPt_IDtrg_21_24",80,3.5,30);
  TH1D *hnumPt_IDtrgFail_21_24 = new TH1D("hnumPt_IDtrgFail_21_24","hnumPt_IDtrgFail_21_24",80,3.5,30);
  TH1D *hnumAbseta_Acc_21_24 = new TH1D("hnumAbseta_Acc_21_24","hnumAbseta_Acc_21_24",80,0,2.4);
  TH1D *hnumAbseta_Glb_21_24 = new TH1D("hnumAbseta_Glb_21_24","hnumAbseta_Glb_21_24",80,0,2.4);
  TH1D *hnumAbseta_GlbFromGen_21_24 = new TH1D("hnumAbseta_GlbFromGen_21_24","hnumAbseta_GlbFromGen_21_24",80,0,2.4);
  TH1D *hnumAbseta_IDtrg_21_24 = new TH1D("hnumAbseta_IDtrg_21_24","hnumAbseta_IDtrg_21_24",80,0,2.4);

   
  int n2Tags = 0;
  int n2TagsNoDM0 = 0;
  int n2TagsNoDbMu0 = 0;
  int n2TagsPassAllCuts = 0;
  int nInAcc = 0;  
  int nTrkNotAcc = 0;
  int nisGlb = 0;
  int nisTrkOrGlb = 0;
  int nTagNotGen = 0;
  int nTnpPairNotGen = 0;

  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<100000;jentry++){//nentries
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    if (ientry%100000==0) cout << 100*ientry/(float)nentries<<"%" << endl;
    nb = fChain->GetEntry(jentry);   //nbytes += nb;
    // if (Cut(ientry) < 0) continue;

    // if there's no reco muon is that event, just skip it
    if (Reco_mu_size==0) continue;

    // loop on the generated dimuons
    for (int igen=0; igen<Gen_QQ_size; igen++) {
      bool isgenpltag=false, isgenmitag=false;
      TLorentzVector tlvrecomatchtagpl, tlvrecomatchtagmi;
      TLorentzVector genpl = *((TLorentzVector*) Gen_mu_4mom->At(Gen_QQ_mupl_idx[igen]));
      TLorentzVector genmi = *((TLorentzVector*) Gen_mu_4mom->At(Gen_QQ_mumi_idx[igen]));

      int ireco = Gen_QQ_whichRec[igen];
      int recmuplIdx = Gen_mu_whichRec[Gen_QQ_mupl_idx[igen]];
      int recmumiIdx = Gen_mu_whichRec[Gen_QQ_mumi_idx[igen]];

      // is the gen muon associated to a tag?
      if (recmuplIdx>-1){
	TLorentzVector recmu = *((TLorentzVector*) Reco_mu_4mom->At(recmuplIdx));
	
	if(CutSgMuon(recmuplIdx) &&  
	   (
	    ((HLTriggers&trg_tag1)>0 && (Reco_mu_trig[recmuplIdx]&trg_tag1)>0) ||
	    ((HLTriggers&trg_tag2)>0 && (Reco_mu_trig[recmuplIdx]&trg_tag2)>0) ||
	    ((HLTriggers&trg_tag3)>0 && (Reco_mu_trig[recmuplIdx]&trg_tag3)>0) ||
	    ((HLTriggers&trg_tag4)>0 && (Reco_mu_trig[recmuplIdx]&trg_tag4)>0) ||
	    ((HLTriggers&trg_tag5)>0 && (Reco_mu_trig[recmuplIdx]&trg_tag5)>0) ||
	    ((HLTriggers&trg_tag6)>0 && (Reco_mu_trig[recmuplIdx]&trg_tag6)>0) ||
	    ((HLTriggers&trg_tag7)>0 && (Reco_mu_trig[recmuplIdx]&trg_tag7)>0) ||
	    ((HLTriggers&trg_tag8)>0 && (Reco_mu_trig[recmuplIdx]&trg_tag8)>0) ||
	    ((HLTriggers&trg_tag9)>0 && (Reco_mu_trig[recmuplIdx]&trg_tag9)>0) ||
	    ((HLTriggers&trg_tag10)>0 && (Reco_mu_trig[recmuplIdx]&trg_tag10)>0) ||
	    ((HLTriggers&trg_tag11)>0 && (Reco_mu_trig[recmuplIdx]&trg_tag11)>0) ||
	    ((HLTriggers&trg_tag12)>0 && (Reco_mu_trig[recmuplIdx]&trg_tag12)>0) ||
	    ((HLTriggers&trg_tag13)>0 && (Reco_mu_trig[recmuplIdx]&trg_tag13)>0) ||
	    ((HLTriggers&trg_tag14)>0 && (Reco_mu_trig[recmuplIdx]&trg_tag14)>0))
	   && isGlobalMuonInTightAccept2018(&recmu)
	   ) {
	  isgenpltag = true; tlvrecomatchtagpl = recmu;	  
	}
      }
      if (recmumiIdx>-1){
	TLorentzVector recmu = *((TLorentzVector*) Reco_mu_4mom->At(recmumiIdx));
	if(CutSgMuon(recmumiIdx) &&  
	   (
	    ((HLTriggers&trg_tag1)>0 && (Reco_mu_trig[recmumiIdx]&trg_tag1)>0) ||
	    ((HLTriggers&trg_tag2)>0 && (Reco_mu_trig[recmumiIdx]&trg_tag2)>0) ||
	    ((HLTriggers&trg_tag3)>0 && (Reco_mu_trig[recmumiIdx]&trg_tag3)>0) ||
	    ((HLTriggers&trg_tag4)>0 && (Reco_mu_trig[recmumiIdx]&trg_tag4)>0) ||
	    ((HLTriggers&trg_tag5)>0 && (Reco_mu_trig[recmumiIdx]&trg_tag5)>0) ||
	    ((HLTriggers&trg_tag6)>0 && (Reco_mu_trig[recmumiIdx]&trg_tag6)>0) ||
	    ((HLTriggers&trg_tag7)>0 && (Reco_mu_trig[recmumiIdx]&trg_tag7)>0) ||
	    ((HLTriggers&trg_tag8)>0 && (Reco_mu_trig[recmumiIdx]&trg_tag8)>0) ||
	    ((HLTriggers&trg_tag9)>0 && (Reco_mu_trig[recmumiIdx]&trg_tag9)>0) ||
	    ((HLTriggers&trg_tag10)>0 && (Reco_mu_trig[recmumiIdx]&trg_tag10)>0) ||
	    ((HLTriggers&trg_tag11)>0 && (Reco_mu_trig[recmumiIdx]&trg_tag11)>0) ||
	    ((HLTriggers&trg_tag12)>0 && (Reco_mu_trig[recmumiIdx]&trg_tag12)>0) ||
	    ((HLTriggers&trg_tag13)>0 && (Reco_mu_trig[recmumiIdx]&trg_tag13)>0) ||
	    ((HLTriggers&trg_tag14)>0 && (Reco_mu_trig[recmumiIdx]&trg_tag14)>0))
	   && isGlobalMuonInTightAccept2018(&recmu)
	   ) {
	  isgenmitag = true; tlvrecomatchtagmi = recmu;	  
	}
      }

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
	  double w_trk = tnpEff_mc_trk_pp(genpt,geneta);
	  double w_glb = tnpEff_mc_glb_pp(genpt,geneta);
	  double w_id = tnpEff_mc_MuId_pp(genpt,geneta);
	  double w_idtrg = tnpEff_mc_MuIdTrg_pp(genpt,geneta);
	  hden_glbIDtrgwtFromTrk_00_12->Fill(genpt,w_glb*w_idtrg/w_trk);
	  hden_glbwt_00_12->Fill(genpt,w_glb);
	  hden_glbIDtrgwt_00_12->Fill(genpt,w_glb*w_idtrg);
	  if(recmumiIdx>-1 && (Reco_mu_SelectionType[recmumiIdx]&2)>0){ //use only muons with kinematics of global muons for the muidtrg eff
	    hden_glbwtFromGlb_00_12->Fill(genpt,1);
	    hden_glbIDwtFromGlb_00_12->Fill(genpt,w_id);
	    hden_glbIDtrgwtFromGlb_00_12->Fill(genpt,w_idtrg);
	  }
	} else if (fabs(geneta)<1.8) {
	  hden_12_18->Fill(genpt,1);
	  double w_trk = tnpEff_mc_trk_pp(genpt,geneta);
	  double w_glb = tnpEff_mc_glb_pp(genpt,geneta);
	  double w_id = tnpEff_mc_MuId_pp(genpt,geneta);
	  double w_idtrg = tnpEff_mc_MuIdTrg_pp(genpt,geneta);
	  hden_glbIDtrgwtFromTrk_12_18->Fill(genpt,w_glb*w_idtrg/w_trk);
	  hden_glbwt_12_18->Fill(genpt,w_glb);
	  hden_glbIDtrgwt_12_18->Fill(genpt,w_glb*w_idtrg);
	  if(recmumiIdx>-1 && (Reco_mu_SelectionType[recmumiIdx]&2)>0){ //use only muons with kinematics of global muons for the muidtrg eff
	    hden_glbwtFromGlb_12_18->Fill(genpt,1);
	    hden_glbIDwtFromGlb_12_18->Fill(genpt,w_id);
	    hden_glbIDtrgwtFromGlb_12_18->Fill(genpt,w_idtrg);
	  }
	} else if (fabs(geneta)<2.1) {
	  hden_18_21->Fill(genpt,1);
	  double w_trk = tnpEff_mc_trk_pp(genpt,geneta);
	  double w_glb = tnpEff_mc_glb_pp(genpt,geneta);
	  double w_id = tnpEff_mc_MuId_pp(genpt,geneta);
	  double w_idtrg = tnpEff_mc_MuIdTrg_pp(genpt,geneta);
	  hden_glbIDtrgwtFromTrk_18_21->Fill(genpt,w_glb*w_idtrg/w_trk);
	  hden_glbwt_18_21->Fill(genpt,w_glb);
	  hden_glbIDtrgwt_18_21->Fill(genpt,w_glb*w_idtrg);
	  if(recmumiIdx>-1 && (Reco_mu_SelectionType[recmumiIdx]&2)>0){ //use only muons with kinematics of global muons for the muidtrg eff
	    hden_glbwtFromGlb_18_21->Fill(genpt,1);
	    hden_glbIDwtFromGlb_18_21->Fill(genpt,w_id);
	    hden_glbIDtrgwtFromGlb_18_21->Fill(genpt,w_idtrg);
	  }
	} else if (fabs(geneta)<2.4) {
	  hden_21_24->Fill(genpt,1);
	  double w_trk = tnpEff_mc_trk_pp(genpt,geneta);
	  double w_glb = tnpEff_mc_glb_pp(genpt,geneta);
	  double w_id = tnpEff_mc_MuId_pp(genpt,geneta);
	  double w_idtrg = tnpEff_mc_MuIdTrg_pp(genpt,geneta);
	  hden_glbIDtrgwtFromTrk_21_24->Fill(genpt,w_glb*w_idtrg/w_trk);
	  hden_glbwt_21_24->Fill(genpt,w_glb);
	  hden_glbIDtrgwt_21_24->Fill(genpt,w_glb*w_idtrg);
	  if(recmumiIdx>-1 && (Reco_mu_SelectionType[recmumiIdx]&2)>0){ //use only muons with kinematics of global muons for the muidtrg eff
	    hden_glbwtFromGlb_21_24->Fill(genpt,1);
	    hden_glbIDwtFromGlb_21_24->Fill(genpt,w_id);
	    hden_glbIDtrgwtFromGlb_21_24->Fill(genpt,w_idtrg);
	  }
	}
      }

      // is the negative gen muon a tag, and the positive gen muon (actually, the associated reco muon) in 2018 tight acceptance?
      if (isgenmitag && isGlobalMuonInTightAccept2018(&probePl4mom)) {
	double genpt = probePl4mom.Pt(); double geneta = probePl4mom.Eta(); 
	if (fabs(geneta)<1.2) {
	  hden_00_12->Fill(genpt,1);
	  double w_trk = tnpEff_mc_trk_pp(genpt,geneta);
	  double w_glb = tnpEff_mc_glb_pp(genpt,geneta);
	  double w_id = tnpEff_mc_MuId_pp(genpt,geneta);
	  double w_idtrg = tnpEff_mc_MuIdTrg_pp(genpt,geneta);
	  hden_glbIDtrgwtFromTrk_00_12->Fill(genpt,w_glb*w_idtrg/w_trk);
	  hden_glbwt_00_12->Fill(genpt,w_glb);
	  hden_glbIDtrgwt_00_12->Fill(genpt,w_glb*w_idtrg);
	  if(recmuplIdx>-1 && (Reco_mu_SelectionType[recmuplIdx]&2)>0){ //use only muons with kinematics of global muons for the muidtrg eff
	    hden_glbwtFromGlb_00_12->Fill(genpt,1);
	    hden_glbIDwtFromGlb_00_12->Fill(genpt,w_id);
	    hden_glbIDtrgwtFromGlb_00_12->Fill(genpt,w_idtrg);
	  }
	} else if (fabs(geneta)<1.8) {
	  hden_12_18->Fill(genpt,1);
	  double w_trk = tnpEff_mc_trk_pp(genpt,geneta);
	  double w_glb = tnpEff_mc_glb_pp(genpt,geneta);
	  double w_id = tnpEff_mc_MuId_pp(genpt,geneta);
	  double w_idtrg = tnpEff_mc_MuIdTrg_pp(genpt,geneta);
	  hden_glbIDtrgwtFromTrk_12_18->Fill(genpt,w_glb*w_idtrg/w_trk);
	  hden_glbwt_12_18->Fill(genpt,w_glb);
	  hden_glbIDtrgwt_12_18->Fill(genpt,w_glb*w_idtrg);
	  if(recmuplIdx>-1 && (Reco_mu_SelectionType[recmuplIdx]&2)>0){ //use only muons with kinematics of global muons for the muidtrg eff
	    hden_glbwtFromGlb_12_18->Fill(genpt,1);
	    hden_glbIDwtFromGlb_12_18->Fill(genpt,w_id);
	    hden_glbIDtrgwtFromGlb_12_18->Fill(genpt,w_idtrg);
	  }
	} else if (fabs(geneta)<2.1) {
	  hden_18_21->Fill(genpt,1);
	  double w_trk = tnpEff_mc_trk_pp(genpt,geneta);
	  double w_glb = tnpEff_mc_glb_pp(genpt,geneta);
	  double w_id = tnpEff_mc_MuId_pp(genpt,geneta);
	  double w_idtrg = tnpEff_mc_MuIdTrg_pp(genpt,geneta);
	  hden_glbIDtrgwtFromTrk_18_21->Fill(genpt,w_glb*w_idtrg/w_trk);
	  hden_glbwt_18_21->Fill(genpt,w_glb);
	  hden_glbIDtrgwt_18_21->Fill(genpt,w_glb*w_idtrg);
	  if(recmuplIdx>-1 && (Reco_mu_SelectionType[recmuplIdx]&2)>0){ //use only muons with kinematics of global muons for the muidtrg eff
	    hden_glbwtFromGlb_18_21->Fill(genpt,1);
	    hden_glbIDwtFromGlb_18_21->Fill(genpt,w_id);
	    hden_glbIDtrgwtFromGlb_18_21->Fill(genpt,w_idtrg);
	  }
	} else if (fabs(geneta)<2.4) {
	  hden_21_24->Fill(genpt,1);
	  double w_trk = tnpEff_mc_trk_pp(genpt,geneta);
	  double w_glb = tnpEff_mc_glb_pp(genpt,geneta);
	  double w_id = tnpEff_mc_MuId_pp(genpt,geneta);
	  double w_idtrg = tnpEff_mc_MuIdTrg_pp(genpt,geneta);
	  hden_glbIDtrgwtFromTrk_21_24->Fill(genpt,w_glb*w_idtrg/w_trk);
	  hden_glbwt_21_24->Fill(genpt,w_glb);
	  hden_glbIDtrgwt_21_24->Fill(genpt,w_glb*w_idtrg);
	  if(recmuplIdx>-1 && (Reco_mu_SelectionType[recmuplIdx]&2)>0){ //use only muons with kinematics of global muons for the muidtrg eff
	    hden_glbwtFromGlb_21_24->Fill(genpt,1);
	    hden_glbIDwtFromGlb_21_24->Fill(genpt,w_id);
	    hden_glbIDtrgwtFromGlb_21_24->Fill(genpt,w_idtrg);
	  }
	}
      }
    } // genQQsize loop


    for (int irecTag=0; irecTag<Reco_mu_size; irecTag++) {
      //Consider all reco muons as potential tags (as in TnP method), even they are fake (not matched to gen)

      //Is this recmu a tag ?
      TLorentzVector tagRecMu = *((TLorentzVector*) Reco_mu_4mom->At(irecTag));

      bool isATag = false;
      if(CutSgMuon(irecTag) &&  
	 (
	  ((HLTriggers&trg_tag1)>0 && (Reco_mu_trig[irecTag]&trg_tag1)>0) ||
	  ((HLTriggers&trg_tag2)>0 && (Reco_mu_trig[irecTag]&trg_tag2)>0) ||
	  ((HLTriggers&trg_tag3)>0 && (Reco_mu_trig[irecTag]&trg_tag3)>0) ||
	  ((HLTriggers&trg_tag4)>0 && (Reco_mu_trig[irecTag]&trg_tag4)>0) ||
	  ((HLTriggers&trg_tag5)>0 && (Reco_mu_trig[irecTag]&trg_tag5)>0) ||
	  ((HLTriggers&trg_tag6)>0 && (Reco_mu_trig[irecTag]&trg_tag6)>0) ||
	  ((HLTriggers&trg_tag7)>0 && (Reco_mu_trig[irecTag]&trg_tag7)>0) ||
	  ((HLTriggers&trg_tag8)>0 && (Reco_mu_trig[irecTag]&trg_tag8)>0) ||
	  ((HLTriggers&trg_tag9)>0 && (Reco_mu_trig[irecTag]&trg_tag9)>0) ||
	  ((HLTriggers&trg_tag10)>0 && (Reco_mu_trig[irecTag]&trg_tag10)>0) ||
	  ((HLTriggers&trg_tag11)>0 && (Reco_mu_trig[irecTag]&trg_tag11)>0) ||
	  ((HLTriggers&trg_tag12)>0 && (Reco_mu_trig[irecTag]&trg_tag12)>0) ||
	  ((HLTriggers&trg_tag13)>0 && (Reco_mu_trig[irecTag]&trg_tag13)>0) ||
	  ((HLTriggers&trg_tag14)>0 && (Reco_mu_trig[irecTag]&trg_tag14)>0))
	 && isGlobalMuonInAccept2015(&tagRecMu)
	 ) {
	isATag = true;// tlvrecomatchtagpl = recmu;	  
      }
   

      Short_t tagGenIdx = Reco_mu_whichGen[irecTag];	  
      if(isATag){

   	//For the GlobalMuon efficiency, start from gen muons, which are assumed to have 100% tracking efficiency (=generalTracks probes in TnP)
	vector<float> seenPt;
	for (Short_t itrkProbe=0; itrkProbe<Reco_trk_size; itrkProbe++) {
	  int igenProbe = Reco_trk_whichGenmu[itrkProbe];
	  if(igenProbe==-1) continue;
	  TLorentzVector trkGenMu = *((TLorentzVector*) Gen_mu_4mom->At(igenProbe));

	  Short_t probRecIdx = Gen_mu_whichRec[igenProbe];
	  TLorentzVector probeMu = *((TLorentzVector*) Reco_trk_4mom->At(itrkProbe));
	  
	  //Keep this tag-probe pair if the dimuon is in Jpsi mass range, and has charge 0
	  if(probRecIdx>-1 && irecTag==probRecIdx) continue; //drop the pair if it is a duplicate muon
	  TLorentzVector recQQ = probeMu + tagRecMu;
	  if(recQQ.M()<2.7 || recQQ.M()>3.3) continue;
	  if(Reco_mu_charge[irecTag] + ((probRecIdx>-1)?(Reco_mu_charge[probRecIdx]):(Reco_trk_charge[itrkProbe])) != 0) continue;
	  //	  if(tagGenIdx==igenProbe) continue; //drop the pair if it is a duplicate muon	  




	  // bool foundGenJpsi = false;
	  // if(tagGenIdx==-1){ //If the tag is not matched to a gen (from PV), then make harder Jpsi cuts
	  //   nTagNotGen+=1; 
	  //   continue;
	  //   //if(recQQ.M()<2.95 || recQQ.M()>3.21) continue;
	  //   //if(Reco_mu_dz[irecTag]>0.5 && Reco_mu_dxy[irecTag]>0.2) continue;
	  // }
	  // else{
	  //   for (int iQQ=0;iQQ<Gen_QQ_size;iQQ++){
	  //     if((tagGenIdx==Gen_QQ_mumi_idx[iQQ] && igenProbe==Gen_QQ_mupl_idx[iQQ]) || (tagGenIdx==Gen_QQ_mupl_idx[iQQ] && igenProbe==Gen_QQ_mumi_idx[iQQ])){ foundGenJpsi=true; break;}
	  //   }
	  //   // if(!foundGenJpsi){
	  //   //   for (int iQQ=0;iQQ<Gen_QQ_size;iQQ++){
	  //   //     if((tagGenIdx==Gen_QQ_mumi_idx[iQQ] && igenProbe==Gen_QQ_mupl_idx[iQQ]) || (tagGenIdx==Gen_QQ_mupl_idx[iQQ] && igenProbe==Gen_QQ_mumi_idx[iQQ])){ foundGenJpsi=true; break;}
	  //   //     else{
	  //   // 	cout<<"Muons do not fit this gen Jpsi#"<<iQQ<<" , genmiidx, genplidx = "<<Gen_QQ_mumi_idx[iQQ]<<" "<<Gen_QQ_mupl_idx[iQQ]<<endl;
	  //   // 	cout<<"tag recoIdx, genIdx = "<<irecTag<<" "<<tagGenIdx<<endl;
	  //   // 	cout<<"probe recoIdx, genIdx = "<<probRecIdx<<" "<<igenProbe<<endl;
	  //   //     }
	  //   //   }
	  //   // }
	  //   if(!foundGenJpsi) {nTnpPairNotGen+=1; continue;}
	  // }

	  //is probe in acceptance?
	  if(isGlobalMuonInTightAccept2018(&probeMu)){
	    if(Reco_trk_originalAlgo[itrkProbe]!=13 && Reco_trk_originalAlgo[itrkProbe]!=14){//Reco_trk_nPixWMea[itrkProbe]>0 && Reco_trk_nTrkWMea[itrkProbe]>5 && Reco_trk_originalAlgo[itrkProbe]!=13 && Reco_trk_originalAlgo[itrkProbe]!=14){// && probRecIdx>-1){

	      //temporary fix to bug in the oniatree Gen_mu branches. Has a completely negligible effect anyway. 
	      bool bad=false;
	      for(int l=0;l<seenPt.size();l++){
		if(fabs(trkGenMu.Pt()-seenPt[l])/trkGenMu.Pt() < 0.001) {cout<<"Already seen a gen muon with this pt !!!"<<endl; bad=true;}
	      }
	      seenPt.push_back(trkGenMu.Pt());
	      //	  if(bad) continue;



	      if (fabs((&probeMu)->Eta())<1.2){ hnumAcc_00_12->Fill((&probeMu)->Pt());
		hnumPt_Acc_00_12->Fill((&probeMu)->Pt());
		hnumAbseta_Acc_00_12->Fill(fabs((&probeMu)->Eta()));}
	      else if (fabs((&probeMu)->Eta())<1.8){ hnumAcc_12_18->Fill((&probeMu)->Pt()); 
		hnumPt_Acc_12_18->Fill((&probeMu)->Pt());
		hnumAbseta_Acc_12_18->Fill(fabs((&probeMu)->Eta()));}
	      else if (fabs((&probeMu)->Eta())<2.1){ hnumAcc_18_21->Fill((&probeMu)->Pt()); 
		hnumPt_Acc_18_21->Fill((&probeMu)->Pt());
		hnumAbseta_Acc_18_21->Fill(fabs((&probeMu)->Eta()));}
	      else if (fabs((&probeMu)->Eta())<2.4){ hnumAcc_21_24->Fill((&probeMu)->Pt()); 
		hnumPt_Acc_21_24->Fill((&probeMu)->Pt());
		hnumAbseta_Acc_21_24->Fill(fabs((&probeMu)->Eta()));}
	      
	      if(probRecIdx==-1){
		float drmin = 0.05;
		bool foundit = false;
		for (Short_t irecmu=0; irecmu<Reco_mu_size; irecmu++) {
		  TLorentzVector recmuMom = *((TLorentzVector*) Reco_mu_4mom->At(irecmu));
		  if(recmuMom.DeltaR(trkGenMu)<drmin && fabs(recmuMom.Pt()-trkGenMu.Pt())/trkGenMu.Pt()<0.1 && Reco_mu_charge[irecmu]==Reco_trk_charge[itrkProbe]){
		    drmin = recmuMom.DeltaR(trkGenMu); foundit = true;
		    probRecIdx=irecmu;
		  }
		}
		//if(foundit && drmin>0.01) cout<<"dR of genmatching = "<<drmin<<endl;
	      }
	    
	      nInAcc+=1;
	      if (probRecIdx>-1) nisTrkOrGlb+=1;
	      // is probe GLB?
	      if(probRecIdx>-1 && (Reco_mu_SelectionType[probRecIdx]&2)>0){
		if (fabs((&probeMu)->Eta())<1.2){ hnumglbFromGen_00_12->Fill((&probeMu)->Pt());
		  hnumPt_GlbFromGen_00_12->Fill((&probeMu)->Pt());
		  hnumAbseta_GlbFromGen_00_12->Fill(fabs((&probeMu)->Eta()));}
		else if (fabs((&probeMu)->Eta())<1.8){ hnumglbFromGen_12_18->Fill((&probeMu)->Pt());
		  hnumPt_GlbFromGen_12_18->Fill((&probeMu)->Pt());
		  hnumAbseta_GlbFromGen_12_18->Fill(fabs((&probeMu)->Eta()));}
		else if (fabs((&probeMu)->Eta())<2.1){ hnumglbFromGen_18_21->Fill((&probeMu)->Pt());
		  hnumPt_GlbFromGen_18_21->Fill((&probeMu)->Pt());
		  hnumAbseta_GlbFromGen_18_21->Fill(fabs((&probeMu)->Eta()));}
		else if (fabs((&probeMu)->Eta())<2.4){ hnumglbFromGen_21_24->Fill((&probeMu)->Pt());
		  hnumPt_GlbFromGen_21_24->Fill((&probeMu)->Pt());
		  hnumAbseta_GlbFromGen_21_24->Fill(fabs((&probeMu)->Eta()));}
		nisGlb+=1;
	      }// probe mu isGlobal
	    } //probe mu in acceptance
	    else{
	      nTrkNotAcc+=1;
	    }
	  }

	} //loop on gen muon probes



	// //For the GlobalMuon efficiency, start from gen muons, which are assumed to have 100% tracking efficiency (=generalTracks probes in TnP)
	// for (Short_t igenProbe=0; igenProbe<Gen_mu_size; igenProbe++) {
	//   TLorentzVector probeGenMu = *((TLorentzVector*) Gen_mu_4mom->At(igenProbe));
	//   Short_t probRecIdx = Gen_mu_whichRec[igenProbe];
	//   TLorentzVector probeMu = (probRecIdx>-1)?( *((TLorentzVector*) Reco_mu_4mom->At(probRecIdx)) ):probeGenMu;

	//   //Keep this tag-probe pair if the dimuon is in Jpsi mass range, and has charge 0
	//   if(probRecIdx>-1 && irecTag==probRecIdx) continue; //drop the pair if it is a duplicate muon
	//   TLorentzVector recQQ = probeMu + tagRecMu;
	//   if(recQQ.M()<2.7 || recQQ.M()>3.3) continue;
	//   if(Reco_mu_charge[irecTag] + ((probRecIdx>-1)?(Reco_mu_charge[probRecIdx]):(Gen_mu_charge[igenProbe])) != 0) continue;
	//   //	  if(tagGenIdx==igenProbe) continue; //drop the pair if it is a duplicate muon	  

	//   bool foundGenJpsi = false;
	//   if(tagGenIdx==-1){ //If the tag is not matched to a gen (from PV), then make harder Jpsi cuts
	//     nTagNotGen+=1; 
	//     continue;
	//     // if(recQQ.M()<2.95 || recQQ.M()>3.21) continue;
	//     // if(Reco_mu_dz[irecTag]>0.5 && Reco_mu_dxy[irecTag]>0.2) continue;
	//   }
	//   else{
	//     for (int iQQ=0;iQQ<Gen_QQ_size;iQQ++){
	//       if((tagGenIdx==Gen_QQ_mumi_idx[iQQ] && igenProbe==Gen_QQ_mupl_idx[iQQ]) || (tagGenIdx==Gen_QQ_mupl_idx[iQQ] && igenProbe==Gen_QQ_mumi_idx[iQQ])){ foundGenJpsi=true; break;}
	//     }
	//     // if(!foundGenJpsi){
	//     //   for (int iQQ=0;iQQ<Gen_QQ_size;iQQ++){
	//     //     if((tagGenIdx==Gen_QQ_mumi_idx[iQQ] && igenProbe==Gen_QQ_mupl_idx[iQQ]) || (tagGenIdx==Gen_QQ_mupl_idx[iQQ] && igenProbe==Gen_QQ_mumi_idx[iQQ])){ foundGenJpsi=true; break;}
	//     //     else{
	//     // 	cout<<"Muons do not fit this gen Jpsi#"<<iQQ<<" , genmiidx, genplidx = "<<Gen_QQ_mumi_idx[iQQ]<<" "<<Gen_QQ_mupl_idx[iQQ]<<endl;
	//     // 	cout<<"tag recoIdx, genIdx = "<<irecTag<<" "<<tagGenIdx<<endl;
	//     // 	cout<<"probe recoIdx, genIdx = "<<probRecIdx<<" "<<igenProbe<<endl;
	//     //     }
	//     //   }
	//     // }
	//     if(!foundGenJpsi) {nTnpPairNotGen+=1; continue;}
	//   }

	//   //is probe in acceptance?
	//   if(isGlobalMuonInTightAccept2018(&probeMu) && probRecIdx>-1){
	//     if (fabs((&probeMu)->Eta())<1.2){ hnumAcc_00_12->Fill((&probeMu)->Pt()); 
	//       hnumPt_Acc_00_12->Fill((&probeMu)->Pt());
	//       hnumAbseta_Acc_00_12->Fill(fabs((&probeMu)->Eta()));}
	//     else if (fabs((&probeMu)->Eta())<1.8){ hnumAcc_12_18->Fill((&probeMu)->Pt()); 
	//       hnumPt_Acc_12_18->Fill((&probeMu)->Pt());
	//       hnumAbseta_Acc_12_18->Fill(fabs((&probeMu)->Eta()));}
	//     else if (fabs((&probeMu)->Eta())<2.1){ hnumAcc_18_21->Fill((&probeMu)->Pt()); 
	//       hnumPt_Acc_18_21->Fill((&probeMu)->Pt());
	//       hnumAbseta_Acc_18_21->Fill(fabs((&probeMu)->Eta()));}
	//     else if (fabs((&probeMu)->Eta())<2.4){ hnumAcc_21_24->Fill((&probeMu)->Pt()); 
	//       hnumPt_Acc_21_24->Fill((&probeMu)->Pt());
	//       hnumAbseta_Acc_21_24->Fill(fabs((&probeMu)->Eta()));}
	    
	//     nInAcc+=1;
	//     // is probe GLB?
	//     if(probRecIdx>-1 && (Reco_mu_SelectionType[probRecIdx]&2)>0){
	//       if (fabs((&probeMu)->Eta())<1.2){ hnumglbFromGen_00_12->Fill((&probeMu)->Pt());
	// 	hnumPt_GlbFromGen_00_12->Fill((&probeMu)->Pt());
	// 	hnumAbseta_GlbFromGen_00_12->Fill(fabs((&probeMu)->Eta()));}
	//       else if (fabs((&probeMu)->Eta())<1.8){ hnumglbFromGen_12_18->Fill((&probeMu)->Pt());
	// 	hnumPt_GlbFromGen_12_18->Fill((&probeMu)->Pt());
	// 	hnumAbseta_GlbFromGen_12_18->Fill(fabs((&probeMu)->Eta()));}
	//       else if (fabs((&probeMu)->Eta())<2.1){ hnumglbFromGen_18_21->Fill((&probeMu)->Pt());
	// 	hnumPt_GlbFromGen_18_21->Fill((&probeMu)->Pt());
	// 	hnumAbseta_GlbFromGen_18_21->Fill(fabs((&probeMu)->Eta()));}
	//       else if (fabs((&probeMu)->Eta())<2.4){ hnumglbFromGen_21_24->Fill((&probeMu)->Pt());
	// 	hnumPt_GlbFromGen_21_24->Fill((&probeMu)->Pt());
	// 	hnumAbseta_GlbFromGen_21_24->Fill(fabs((&probeMu)->Eta()));}
	//       nisGlb+=1;
	//     }// probe mu isGlobal
	//   } //probe mu in acceptance

	// } //loop on gen muon probes









	//Consider the reco muons as potential Glb probes, for MuIdTrg efficiency
	for (Short_t irecProbe=0; irecProbe<Reco_mu_size; irecProbe++) {
	  if(irecTag==irecProbe) continue; //drop the pair if it is a duplicate muon

	  TLorentzVector probeRecMu = *((TLorentzVector*) Reco_mu_4mom->At(irecProbe));

	  //Keep this tag-probe pair if the dimuon is in Jpsi mass range, and has charge 0
	  TLorentzVector recQQ = probeRecMu + tagRecMu;
	  if(recQQ.M()<2.7 || recQQ.M()>3.3) continue;
	  if(Reco_mu_charge[irecTag] + Reco_mu_charge[irecProbe] != 0) continue;

	  //is probe in acceptance + reco as trk or glb? This assumes that the efficiency to reconstruct a gen muon as a tracker or global is close to 100% (in tight acceptance)
	  if(isGlobalMuonInTightAccept2018(&probeRecMu) && irecProbe>-1){
	    // if (fabs((&probeRecMu)->Eta())<1.2){ hnumAcc_00_12->Fill((&probeRecMu)->Pt()); 
	    //   hnumPt_Acc_00_12->Fill((&probeRecMu)->Pt());
	    //   hnumAbseta_Acc_00_12->Fill(fabs((&probeRecMu)->Eta()));}
	    // else if (fabs((&probeRecMu)->Eta())<1.8){ hnumAcc_12_18->Fill((&probeRecMu)->Pt()); 
	    //   hnumPt_Acc_12_18->Fill((&probeRecMu)->Pt());
	    //   hnumAbseta_Acc_12_18->Fill(fabs((&probeRecMu)->Eta()));}
	    // else if (fabs((&probeRecMu)->Eta())<2.1){ hnumAcc_18_21->Fill((&probeRecMu)->Pt()); 
	    //   hnumPt_Acc_18_21->Fill((&probeRecMu)->Pt());
	    //   hnumAbseta_Acc_18_21->Fill(fabs((&probeRecMu)->Eta()));}
	    // else if (fabs((&probeRecMu)->Eta())<2.4){ hnumAcc_21_24->Fill((&probeRecMu)->Pt()); 
	    //   hnumPt_Acc_21_24->Fill((&probeRecMu)->Pt());
	    //   hnumAbseta_Acc_21_24->Fill(fabs((&probeRecMu)->Eta()));}
	    
	    //	    nInAcc+=1;

	    // bool isProbeATag=false;
	    // if(CutSgMuon(irecProbe) &&  
	    //    (
	    //     ((HLTriggers&trg_tag1)>0 && (Reco_mu_trig[irecProbe]&trg_tag1)>0) ||
	    //     ((HLTriggers&trg_tag2)>0 && (Reco_mu_trig[irecProbe]&trg_tag2)>0) ||
	    //     ((HLTriggers&trg_tag3)>0 && (Reco_mu_trig[irecProbe]&trg_tag3)>0) ||
	    //     ((HLTriggers&trg_tag4)>0 && (Reco_mu_trig[irecProbe]&trg_tag4)>0) ||
	    //     ((HLTriggers&trg_tag5)>0 && (Reco_mu_trig[irecProbe]&trg_tag5)>0) ||
	    //     ((HLTriggers&trg_tag6)>0 && (Reco_mu_trig[irecProbe]&trg_tag6)>0) ||
	    //     ((HLTriggers&trg_tag7)>0 && (Reco_mu_trig[irecProbe]&trg_tag7)>0) ||
	    //     ((HLTriggers&trg_tag8)>0 && (Reco_mu_trig[irecProbe]&trg_tag8)>0) ||
	    //     ((HLTriggers&trg_tag9)>0 && (Reco_mu_trig[irecProbe]&trg_tag9)>0) ||
	    //     ((HLTriggers&trg_tag10)>0 && (Reco_mu_trig[irecProbe]&trg_tag10)>0) ||
	    //     ((HLTriggers&trg_tag11)>0 && (Reco_mu_trig[irecProbe]&trg_tag11)>0) ||
	    //     ((HLTriggers&trg_tag12)>0 && (Reco_mu_trig[irecProbe]&trg_tag12)>0) ||
	    //     ((HLTriggers&trg_tag13)>0 && (Reco_mu_trig[irecProbe]&trg_tag13)>0) ||
	    //     ((HLTriggers&trg_tag14)>0 && (Reco_mu_trig[irecProbe]&trg_tag14)>0))
	    //    && isGlobalMuonInTightAccept2018(&probeRecMu)
	    //    ) {
	    //   isProbeATag = true;// tlvrecomatchtagpl = recmu;	  
	    //   n2Tags +=1;
	    
	    //   if((HLTriggers&trg_probe)<=0) {
	    //     n2TagsNoDbMu0 +=1;
	    //     cout<<"WTF! We have two tags, but the event does not fire L1DoubleMu0!"<<endl;
	    //     cout<<"pt, eta, charge, L1DoubleMu0 of tag muon "<<tagRecMu.Pt()<<" "<<tagRecMu.Eta()<<" "<<Reco_mu_charge[irecTag]<<" "<<((Reco_mu_trig[irecTag]&trg_probe)>0)<<endl;
	    //     cout<<"pt, eta, charge, L1DoubleMu0 of probe-tag 2nd muon "<<probeRecMu.Pt()<<" "<<probeRecMu.Eta()<<" "<<Reco_mu_charge[irecProbe]<<" "<<((Reco_mu_trig[irecProbe]&trg_probe)>0)<<endl;
	    //     cout<<"dimuon mass = "<<recQQ.M()<<endl;
	    //     cout<<"FiresSingleMuTriggers(tag1) = "<<	((HLTriggers&trg_tag1)>0 && (Reco_mu_trig[irecTag]&trg_tag1)>0) <<" "<<
	    // 	((HLTriggers&trg_tag2)>0 && (Reco_mu_trig[irecTag]&trg_tag2)>0) <<" "<<
	    // 	((HLTriggers&trg_tag3)>0 && (Reco_mu_trig[irecTag]&trg_tag3)>0) <<" "<<
	    // 	((HLTriggers&trg_tag4)>0 && (Reco_mu_trig[irecTag]&trg_tag4)>0) <<" "<<
	    // 	((HLTriggers&trg_tag5)>0 && (Reco_mu_trig[irecTag]&trg_tag5)>0) <<" "<<
	    // 	((HLTriggers&trg_tag6)>0 && (Reco_mu_trig[irecTag]&trg_tag6)>0) <<" "<<
	    // 	((HLTriggers&trg_tag7)>0 && (Reco_mu_trig[irecTag]&trg_tag7)>0) <<" "<<
	    // 	((HLTriggers&trg_tag8)>0 && (Reco_mu_trig[irecTag]&trg_tag8)>0) <<" "<<
	    // 	((HLTriggers&trg_tag9)>0 && (Reco_mu_trig[irecTag]&trg_tag9)>0) <<" "<<
	    // 	((HLTriggers&trg_tag10)>0 && (Reco_mu_trig[irecTag]&trg_tag10)>0) <<" "<<
	    // 	((HLTriggers&trg_tag11)>0 && (Reco_mu_trig[irecTag]&trg_tag11)>0) <<" "<<
	    // 	((HLTriggers&trg_tag12)>0 && (Reco_mu_trig[irecTag]&trg_tag12)>0) <<" "<<
	    // 	((HLTriggers&trg_tag13)>0 && (Reco_mu_trig[irecTag]&trg_tag13)>0) <<" "<<
	    // 	((HLTriggers&trg_tag14)>0 && (Reco_mu_trig[irecTag]&trg_tag14)>0)<<" "<<endl;
	    //     cout<<"FiresSingleMuTriggers(tag2) = "<<	((HLTriggers&trg_tag1)>0 && (Reco_mu_trig[irecProbe]&trg_tag1)>0) <<" "<<
	    // 	((HLTriggers&trg_tag2)>0 && (Reco_mu_trig[irecProbe]&trg_tag2)>0) <<" "<<
	    // 	((HLTriggers&trg_tag3)>0 && (Reco_mu_trig[irecProbe]&trg_tag3)>0) <<" "<<
	    // 	((HLTriggers&trg_tag4)>0 && (Reco_mu_trig[irecProbe]&trg_tag4)>0) <<" "<<
	    // 	((HLTriggers&trg_tag5)>0 && (Reco_mu_trig[irecProbe]&trg_tag5)>0) <<" "<<
	    // 	((HLTriggers&trg_tag6)>0 && (Reco_mu_trig[irecProbe]&trg_tag6)>0) <<" "<<
	    // 	((HLTriggers&trg_tag7)>0 && (Reco_mu_trig[irecProbe]&trg_tag7)>0) <<" "<<
	    // 	((HLTriggers&trg_tag8)>0 && (Reco_mu_trig[irecProbe]&trg_tag8)>0) <<" "<<
	    // 	((HLTriggers&trg_tag9)>0 && (Reco_mu_trig[irecProbe]&trg_tag9)>0) <<" "<<
	    // 	((HLTriggers&trg_tag10)>0 && (Reco_mu_trig[irecProbe]&trg_tag10)>0) <<" "<<
	    // 	((HLTriggers&trg_tag11)>0 && (Reco_mu_trig[irecProbe]&trg_tag11)>0) <<" "<<
	    // 	((HLTriggers&trg_tag12)>0 && (Reco_mu_trig[irecProbe]&trg_tag12)>0) <<" "<<
	    // 	((HLTriggers&trg_tag13)>0 && (Reco_mu_trig[irecProbe]&trg_tag13)>0) <<" "<<
	    // 	((HLTriggers&trg_tag14)>0 && (Reco_mu_trig[irecProbe]&trg_tag14)>0)<<" "<<endl;
	    //   }

	    //}
	  

	    //Fill denominator of MuIdTrg efficiency
	    //Keep only the probes that are Global & in acceptance
	    if((Reco_mu_SelectionType[irecProbe]&2)>0) {
	      //	      nisGlb+=1;
	      if (fabs((&probeRecMu)->Eta())<1.2){ hnumglb_00_12->Fill((&probeRecMu)->Pt());
		hnumPt_Glb_00_12->Fill((&probeRecMu)->Pt());
		hnumAbseta_Glb_00_12->Fill(fabs((&probeRecMu)->Eta()));}
	      else if (fabs((&probeRecMu)->Eta())<1.8){ hnumglb_12_18->Fill((&probeRecMu)->Pt());
		hnumPt_Glb_12_18->Fill((&probeRecMu)->Pt());
		hnumAbseta_Glb_12_18->Fill(fabs((&probeRecMu)->Eta()));}
	      else if (fabs((&probeRecMu)->Eta())<2.1){ hnumglb_18_21->Fill((&probeRecMu)->Pt());
		hnumPt_Glb_18_21->Fill((&probeRecMu)->Pt());
		hnumAbseta_Glb_18_21->Fill(fabs((&probeRecMu)->Eta()));}
	      else if (fabs((&probeRecMu)->Eta())<2.4){ hnumglb_21_24->Fill((&probeRecMu)->Pt());
		hnumPt_Glb_21_24->Fill((&probeRecMu)->Pt());
		hnumAbseta_Glb_21_24->Fill(fabs((&probeRecMu)->Eta()));}

	      // ID
	      if (Cut_muplmi(irecProbe)) {
		if (fabs((&probeRecMu)->Eta())<1.2){ hnumglbID_00_12->Fill((&probeRecMu)->Pt());
		  hnumPt_ID_00_12->Fill((&probeRecMu)->Pt());}
		else if (fabs((&probeRecMu)->Eta())<1.8){ hnumglbID_12_18->Fill((&probeRecMu)->Pt());
		  hnumPt_ID_12_18->Fill((&probeRecMu)->Pt());}
		else if (fabs((&probeRecMu)->Eta())<2.1){ hnumglbID_18_21->Fill((&probeRecMu)->Pt());
		  hnumPt_ID_18_21->Fill((&probeRecMu)->Pt());}
		else if (fabs((&probeRecMu)->Eta())<2.4){ hnumglbID_21_24->Fill((&probeRecMu)->Pt());
		  hnumPt_ID_21_24->Fill((&probeRecMu)->Pt());}

		bool oktrig = (Reco_mu_trig[irecProbe]&trg_probe)>0;
		bool okTrg = (HLTriggers&trg_probe)>0;

		if (oktrig && okTrg) {
		  if (fabs((&probeRecMu)->Eta())<1.2){ hnumglbIDtrg_00_12->Fill((&probeRecMu)->Pt());
		    hnumPt_IDtrg_00_12->Fill((&probeRecMu)->Pt());
		    hnumAbseta_IDtrg_00_12->Fill(fabs((&probeRecMu)->Eta()));}
		  else if (fabs((&probeRecMu)->Eta())<1.8){ hnumglbIDtrg_12_18->Fill((&probeRecMu)->Pt());
		    hnumPt_IDtrg_12_18->Fill((&probeRecMu)->Pt());
		    hnumAbseta_IDtrg_12_18->Fill(fabs((&probeRecMu)->Eta()));}
		  else if (fabs((&probeRecMu)->Eta())<2.1){ hnumglbIDtrg_18_21->Fill((&probeRecMu)->Pt());
		    hnumPt_IDtrg_18_21->Fill((&probeRecMu)->Pt());
		    hnumAbseta_IDtrg_18_21->Fill(fabs((&probeRecMu)->Eta()));}
		  else if (fabs((&probeRecMu)->Eta())<2.4){ hnumglbIDtrg_21_24->Fill((&probeRecMu)->Pt());
		    hnumPt_IDtrg_21_24->Fill((&probeRecMu)->Pt());
		    hnumAbseta_IDtrg_21_24->Fill(fabs((&probeRecMu)->Eta()));}
		}
		else{
		  if (fabs((&probeRecMu)->Eta())<1.2){ 
		    hnumPt_IDtrgFail_00_12->Fill((&probeRecMu)->Pt());}
		  else if (fabs((&probeRecMu)->Eta())<1.8){ 
		    hnumPt_IDtrgFail_12_18->Fill((&probeRecMu)->Pt());}
		  else if (fabs((&probeRecMu)->Eta())<2.1){ 
		    hnumPt_IDtrgFail_18_21->Fill((&probeRecMu)->Pt());}
		  else if (fabs((&probeRecMu)->Eta())<2.4){ 
		    hnumPt_IDtrgFail_21_24->Fill((&probeRecMu)->Pt());}
		}//trigger
	      }//ID
	    }//GLB
	  } //probe mu in acceptance + isTracker || isGlobal
       	    
	}//loop on reco muon probes

	  
      } //isATag	
    }//loop on reco muon tags



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



  } // event loop


  cout<<"# of gen muons in acceptance = "<<nInAcc<<endl;
  cout<<"# of gen muons in acceptance & TrkOrGlb = "<<nisTrkOrGlb<<endl;
  cout<<"# of gen muons in acceptance & Glb = "<<nisGlb<<endl;
  cout<<"# of tacks matched to gen muons but not in track acceptance = "<<nTrkNotAcc<<endl;

  f->Write();
  f->Close();
  delete f;
}
