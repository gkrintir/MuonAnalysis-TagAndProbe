#include "TTree.h"
#include "TFile.h"

#define DXYCUT 0.3
#define DZCUT 20

TTree* copyTree(TTree* told, int nentries=0) {
   TTree *tnew = told->CloneTree(0);
   tnew->SetAutoSave(0);
  // tnew->SetAutoFlush(10000000);
   //int passedDXY,passedDZ, isNotMuonSeeded, SoftID, SoftHINoDxyz;
  // int isMuonSeeded; //fix to naming in MC - the *Not* was omitted.
   float eta, abseta;

   told->SetBranchAddress("eta",&eta);

   tnew->Branch("abseta", &abseta, "abseta/F");
 
 
   if (nentries == 0)
   {
	   nentries = told->GetEntries();
   }
   cout << nentries;
   for (long i=0; i<nentries; i++) {
      told->GetEntry(i);

	  if (i % 100000 == 0) { cout << "event: " << i << " done: " << 100 * i / nentries << "%" << endl; }


	  abseta = fabs(eta);
      tnew->Fill();
   }

   return tnew;
}

TTree* justCopyTree(TTree* told, int nentries=0) {
	TTree *tnew = told->CloneTree(0);
	tnew->SetAutoSave(0);
	tnew->SetAutoFlush(0);

	if (nentries == 0)
	{
		nentries = told->GetEntries();
	}
	for (long i = 0; i<nentries; i++) {
		told->GetEntry(i);
		tnew->Fill();
	}
	return tnew;
}

void CutThingsFromSkim(const char *filein, const char *fileout) {
   TFile *fin = new TFile(filein);
   TFile *fout = new TFile(fileout,"RECREATE");

   //fout->cd();
   //TDirectory *tdir_trk = fout->mkdir("tpTreeSta");
   //tdir_trk->cd();
   //TTree *tr_trk = justCopyTree((TTree*)fin->Get("tpTreeSta/fitter_tree"),0);

   fout->cd();
   TDirectory *tdir_muidtrg = fout->mkdir("tpTree");
   tdir_muidtrg->cd();
   TTree *tr_muidtrg = copyTree((TTree*) fin->Get("tpTree/fitter_tree"),0);

   //fout->cd();
   //TDirectory *tdir_trg = fout->mkdir("tpTreeTrk");
   //tdir_trg->cd();
   //TTree *tr_trg = justCopyTree((TTree*)fin->Get("tpTreeTrk/fitter_tree"),0);


   fout->Write();
   fout->Close();
}
