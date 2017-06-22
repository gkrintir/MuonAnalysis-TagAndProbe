#include "TTree.h"
#include "TFile.h"

#ifndef HFweight_h
#define HFweight_h

#include "TH1.h"

#include <iostream>

using namespace std;

class HFweight {
   public:
      HFweight(const char* weightfile = "/afs/cern.ch/work/e/echapon/public/DY_pA_2016/HFweight.root");
      ~HFweight();
      double weight(double hiHF);

   private:
      const char* weightfile = "/afs/cern.ch/work/e/echapon/public/DY_pA_2016/HFweight.root";
      TFile *f;
      TH1F* h_hiHF_ratio;
};

HFweight::HFweight(const char* weightfile) {
   f = new TFile(weightfile);
   if (!f || !f->IsOpen()) {
      cout << "Error! could not find HF weight file " << weightfile << endl;
      return;
   }

   h_hiHF_ratio = (TH1F*) f->Get("h_hiHF_ratio");
}

HFweight::~HFweight() {
   f->Close();
   if (f) {
      delete f;
      f=0;
   }
}

double HFweight::weight(double hiHF) {
   TH1F *hist;
   hist = h_hiHF_ratio;

   if (!hist) {
      cout << "Error, missing weight histo" << endl;
      return 1;
   }

   return hist->GetBinContent(hist->FindBin(hiHF));
}

#endif // #ifndef HFweight_h



TTree* copyTree(TTree* told) {
   TTree *tnew = told->CloneTree(0);
   tnew->SetAutoSave(0);
   tnew->SetAutoFlush(0);
   float weight_HF;
   float tag_hiHF;

   told->SetBranchAddress("tag_hiHF", &tag_hiHF);

   tnew->Branch("weight_HF",&weight_HF,"weight_HF/I");

   int nentries = told->GetEntries();
   for (int i=0; i<nentries; i++) {
      told->GetEntry(i);
	  // HF Weight
	  weight_HF = HFweight.weight(tag_hiHF);

      tnew->Fill();
   }

   return tnew;
}

TTree* justCopyTree(TTree* told) {
	TTree *tnew = told->CloneTree(0);
	tnew->SetAutoSave(0);
	tnew->SetAutoFlush(0);

	int nentries = told->GetEntries();
	for (int i = 0; i<nentries; i++) {
		told->GetEntry(i);
		tnew->Fill();
	}
	return tnew;
}

void addFlagsToFile(const char *filein, const char *fileout) {
   TFile *fin = new TFile(filein);
   TFile *fout = new TFile(fileout,"RECREATE");

   fout->cd();
   TDirectory *tdir_trk = fout->mkdir("tpTreeSta");
   tdir_trk->cd();
   TTree *tr_trk = justCopyTree((TTree*)fin->Get("tpTreeSta/fitter_tree"));

   fout->cd();
   TDirectory *tdir_muidtrg = fout->mkdir("tpTree");
   tdir_muidtrg->cd();
   TTree *tr_muidtrg = copyTree((TTree*) fin->Get("tpTree/fitter_tree"));

   fout->cd();
   TDirectory *tdir_trg = fout->mkdir("tpTreeTrk");
   tdir_trg->cd();
   TTree *tr_trg = justCopyTree((TTree*)fin->Get("tpTreeTrk/fitter_tree"));


   fout->Write();
   fout->Close();
}
