#include "TTree.h"
#include "TFile.h"

#define DXYCUT 0.3
#define DZCUT 20

TTree* copyTree(TTree* told, int nentries=0) {
   TTree *tnew = told->CloneTree(0);
   tnew->SetAutoSave(0);
   tnew->SetAutoFlush(0);
   int passedDXY,passedDZ, isNotMuonSeeded, SoftID, SoftHINoDxyz;
   int isMuonSeeded; //fix to naming in MC - the *Not* was omitted.
   float dzPV, dxyPV, dB;

   told->SetBranchAddress("dzPV",&dzPV);
   told->SetBranchAddress("dxyPV",&dxyPV);
  // told->SetBranchAddress("isNotMuonSeeded", &isNotMuonSeeded);
   told->SetBranchAddress("isMuonSeeded", &isMuonSeeded);
   told->SetBranchAddress("dB", &dB);
   told->SetBranchAddress("SoftHINoDxyz", &SoftHINoDxyz);


   tnew->Branch("SoftID", &SoftID, "SoftID/I");
   tnew->Branch("passedDXY", &passedDXY, "passedDXY/I");
   tnew->Branch("passedDZ", &passedDZ, "passedDZ/I");
   tnew->Branch("isNotMuonSeeded", &isNotMuonSeeded);
 
   if (nentries == 0)
   {
	   nentries = told->GetEntries();
   }
   for (int i=0; i<nentries; i++) {
      told->GetEntry(i);


	  //SoftMuonID
	  isNotMuonSeeded = isMuonSeeded;
	  passedDXY = (fabs(dxyPV) < DXYCUT);
	  passedDZ = (fabs(dzPV) < DZCUT);
	  SoftID = (passedDXY && passedDZ && SoftHINoDxyz);
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
	for (int i = 0; i<nentries; i++) {
		told->GetEntry(i);
		tnew->Fill();
	}
	return tnew;
}

void addFlagsToFile_lowpT(const char *filein, const char *fileout) {
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
