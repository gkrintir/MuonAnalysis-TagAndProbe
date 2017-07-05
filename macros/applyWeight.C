#include "TTree.h"
#include "TFile.h"

#include "TH1.h"

#include <iostream>

using namespace std;

TTree* HFweighttoTree(TTree* told) {
   TTree *tnew = told->CloneTree(0);
   tnew->SetAutoSave(0);
   tnew->SetAutoFlush(0);

   float weight_HF;
   float old_tag_hiHF;
   float tag_hiHF;

   told->SetBranchAddress("tag_hiHF", &old_tag_hiHF);
   told->SetBranchAddress("weight_HF", &weight_HF);

   tnew->SetBranchAddress("tag_hiHF", &tag_hiHF);

//   tnew->Branch("weight_HF",&weight_HF,"weight_HF/I");

   int nentries = told->GetEntries();

   for (int i=0; i<nentries; i++) {
      told->GetEntry(i);
          // Applying  HF Weight
          tag_hiHF = old_tag_hiHF * weight_HF;

      tnew->Fill();
   }

   return tnew;
}


void applyWeight(const char *filein, const char *fileout){

   TFile *fin = new TFile(filein);
   TFile *fout = new TFile(fileout,"RECREATE");

   fout->cd();
   TDirectory *tdir_trk = fout->mkdir("tpTreeSta");
   tdir_trk->cd();
   TTree *tr_trk = HFweighttoTree((TTree*)fin->Get("tpTreeSta/fitter_tree"));

   fout->cd();
   TDirectory *tdir_muidtrg = fout->mkdir("tpTree");
   tdir_muidtrg->cd();
   TTree *tr_muidtrg = HFweighttoTree((TTree*) fin->Get("tpTree/fitter_tree"));

   fout->cd();
   TDirectory *tdir_trg = fout->mkdir("tpTreeTrk");
   tdir_trg->cd();
   TTree *tr_trg = HFweighttoTree((TTree*)fin->Get("tpTreeTrk/fitter_tree"));

   fout->Write();
   fout->Close();
}

