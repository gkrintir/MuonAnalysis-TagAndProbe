#include "TTree.h"
#include "TFile.h"

#define DXYCUT 0.3
#define DZCUT 20

TTree* copyTree(TTree* told, int nentries=0) {
   TTree *tnew = told->CloneTree(0);
   tnew->SetAutoSave(0);
  // tnew->SetAutoFlush(10000000);
   int passedDXY,passedDZ, isNotMuonSeeded, SoftID, SoftHINoDxyz, tag_acceptance, probe_acceptance, probe_acceptance_new, probe_trg_acceptance;
  // int isMuonSeeded; //fix to naming in MC - the *Not* was omitted.
   float dzPV, dxyPV, dB, pt, eta, tag_pt, p, pair_dz, pair_deltaR;

  // told->SetBranchAddress("dzPV",&dzPV);
  // told->SetBranchAddress("dxyPV",&dxyPV);
  // //told->SetBranchAddress("isNotMuonSeeded", &isNotMuonSeeded);
  //// told->SetBranchAddress("isMuonSeeded", &isMuonSeeded);
  //// told->SetBranchAddress("dB", &dB);
  // told->SetBranchAddress("SoftHINoDxyz", &SoftHINoDxyz);
  // told->SetBranchAddress("p", &p);
   told->SetBranchAddress("pt", &pt);
   told->SetBranchAddress("eta", &eta);
  // told->SetBranchAddress("tag_pt", &tag_pt);
  // //told->SetBranchAddress("pair_dz", &pair_dz);

  // tnew->Branch("SoftID", &SoftID, "SoftID/I");
  // tnew->Branch("passedDXY", &passedDXY, "passedDXY/I");
  // tnew->Branch("passedDZ", &passedDZ, "passedDZ/I");
  // //tnew->Branch("isNotMuonSeeded", &isNotMuonSeeded);
  // tnew->Branch("tag_acceptance", &tag_acceptance, "tag_acceptance/I");
  // tnew->Branch("probe_acceptance", &probe_acceptance, "probe_acceptance/I");
   tnew->Branch("probe_acceptance_new", &probe_acceptance_new, "probe_acceptance_new/I");
  // tnew->Branch("probe_trg_acceptance", &probe_trg_acceptance, "probe_trg_acceptance/I");


   if (nentries == 0)
   {
	   nentries = told->GetEntries();
   }
   for (long i=0; i<nentries; i++) {
      told->GetEntry(i);

	  if (i % 1000000 == 0) { cout << "event: " << i << " done: " << 100 * i / nentries << "%" << endl; }

	  ////SoftMuonID
	  ////isNotMuonSeeded = isMuonSeeded;
	  //passedDXY = (fabs(dxyPV) < DXYCUT);
	  //passedDZ = (fabs(dzPV) < DZCUT);
	  //SoftID = (passedDXY && passedDZ && SoftHINoDxyz);

	  //// add acceptance conditions
	  //if (tag_pt > 3.5) { tag_acceptance = 1; }
	  //else tag_acceptance = 0;

	  ////if ((fabs(eta) < 1. && pt >= 3.3) || (fabs(eta) >= 1.0 && fabs(eta) < 2.2 && p >= 2.9) || (fabs(eta >= 2.2) && pt >= 0.8)) { probe_acceptance = 1; }  //old acceptance
	  //if (fabs(eta) < 2.4 && ((fabs(eta) < 0.8 && pt >= 3.3) || (0.8 <= fabs(eta) && fabs(eta) < 1.5 && pt >= 5.81 - 3.14*fabs(eta)) ||  (1.5 <= fabs(eta) && pt >= 0.8 && pt >= 1.89 - 0.526*fabs(eta)))) { probe_acceptance = 1; }
	  //else probe_acceptance = 0;

	  if (fabs(eta) < 2.4 && ((fabs(eta) < 1.0 && pt >= 3.3) || (1.0 <= fabs(eta) && fabs(eta) < 1.5 && pt >= 7.5 - 4.2*fabs(eta)) || (1.5 <= fabs(eta) && pt >= 0.8 && pt >= 2.4 - 0.8*fabs(eta)))) { probe_acceptance_new = 1; }
	  else probe_acceptance_new = 0;


	  //if (fabs(eta) < 2.4 && ((fabs(eta) < 1.2 && pt >= 3.3) ||  (1.2 <= fabs(eta) && fabs(eta) < 2.1 && pt >= 3.93 - 1.11*fabs(eta)) ||  (2.1 <= fabs(eta) && fabs(eta) < 2.4 && pt >= 1.3))) { probe_trg_acceptance = 1; }
	  //else probe_trg_acceptance = 0;

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
