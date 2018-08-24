#include "TTree.h"
#include "TFile.h"

#define DXYCUT 0.2
#define DZCUT 0.5

TTree* copyTree(TTree* told, int nentries=0) {
   TTree *tnew = told->CloneTree(0);
   tnew->SetAutoSave(0);
   tnew->SetAutoFlush(0);
   int iso1p00, iso1p25, iso1p50,iso1p75,iso2p00;
   int tkiso2p5, tkiso3, tkiso4, tkiso5, tkiso6, tkiso7;
   int reltkiso0p2, reltkiso0p3, reltkiso0p4;
   int dxycut, dzcut;
   float combRelIsoPF03, tkIso;
   float dB,dzPV,pt;

   told->SetBranchAddress("combRelIsoPF03", &combRelIsoPF03);
   told->SetBranchAddress("tkIso", &tkIso);
   told->SetBranchAddress("dB",&dB);
   told->SetBranchAddress("dzPV",&dzPV);
   told->SetBranchAddress("pt",&pt);

   tnew->Branch("iso1p00", &iso1p00, "iso1p00/I");
   tnew->Branch("iso1p25", &iso1p25, "iso1p25/I");
   tnew->Branch("iso1p50", &iso1p50, "iso1p50/I");
   tnew->Branch("iso1p75", &iso1p75, "iso1p75/I");
   tnew->Branch("iso2p00", &iso2p00, "iso2p00/I");
   tnew->Branch("tkiso2p5", &tkiso2p5, "tkiso2p5/I");
   tnew->Branch("tkiso3", &tkiso3, "tkiso3/I");
   tnew->Branch("tkiso4", &tkiso4, "tkiso4/I");
   tnew->Branch("tkiso5", &tkiso5, "tkiso5/I");
   tnew->Branch("tkiso6", &tkiso6, "tkiso6/I");
   tnew->Branch("tkiso7", &tkiso7, "tkiso7/I");
   tnew->Branch("reltkiso0p2", &reltkiso0p2, "reltkiso0p2/I");
   tnew->Branch("reltkiso0p3", &reltkiso0p3, "reltkiso0p3/I");
   tnew->Branch("reltkiso0p4", &reltkiso0p4, "reltkiso0p4/I");
   tnew->Branch("dxycut", &dxycut, "dxycut/I");
   tnew->Branch("dzcut", &dzcut, "dzcut/I");

 
   if (nentries == 0)
   {
	   nentries = told->GetEntries();
   }
   for (int i=0; i<nentries; i++) {
      told->GetEntry(i);
	  // Isolations
	  iso1p00 = ((combRelIsoPF03)<1.00);
	  iso1p25 = ((combRelIsoPF03)<1.25);
	  iso1p50 = ((combRelIsoPF03)<1.50);
	  iso1p75 = ((combRelIsoPF03)<1.75);
	  iso2p00 = ((combRelIsoPF03)<2.00);
     tkiso2p5 = (tkIso<2.5);
     tkiso3 = (tkIso<3);
     tkiso4 = (tkIso<4);
     tkiso5 = (tkIso<5);
     tkiso6 = (tkIso<6);
     tkiso7 = (tkIso<7);
     reltkiso0p2 = (tkIso/pt<0.2);
     reltkiso0p3 = (tkIso/pt<0.3);
     reltkiso0p4 = (tkIso/pt<0.4);

	  dxycut = (fabs(dB)<0.01);
	  dzcut = (fabs(dzPV)<0.1);

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

void addFlagsToFile2(const char *filein, const char *fileout) {
   TFile *fin = new TFile(filein);
   TFile *fout = new TFile(fileout,"RECREATE");

   fout->cd();
   TDirectory *tdir_trk = fout->mkdir("tpTreeSta");
   tdir_trk->cd();
   TTree *tr_trk = justCopyTree((TTree*)fin->Get("tpTreeSta/fitter_tree"),0);

   fout->cd();
   TDirectory *tdir_muidtrg = fout->mkdir("tpTree");
   tdir_muidtrg->cd();
   TTree *tr_muidtrg = copyTree((TTree*) fin->Get("tpTree/fitter_tree"),0);

   fout->cd();
   TDirectory *tdir_trg = fout->mkdir("tpTreeTrk");
   tdir_trg->cd();
   TTree *tr_trg = justCopyTree((TTree*)fin->Get("tpTreeTrk/fitter_tree"),0);


   fout->Write();
   fout->Close();
}
