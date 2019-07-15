#include "TTree.h"
#include "TFile.h"
#include <iostream>
#include <math.h>

TTree* trimTree(TTree* told)
{
	std::vector<std::string> varVec = { "p","pt", "eta", "abseta", "mass", "dzPV", "dxyPV", "tag_nVertices", "tag_hiNtracks", "tag_pt", "isNotMuonSeeded", "TM", "SoftHINoDxyz", "HLT_PAL1DoubleMuOpen" }; //without flags
	//std::vector<std::string> varVec = { "pt", "eta","abseta", "mass", "tag_nVertices", "tag_acceptance", "probe_acceptance", "tag_hiNtracks","isNotMuonSeeded", "TM", "SoftID", "HLT_PAL1DoubleMuOpen" }; //with flags


	told->SetBranchStatus("*", 0);
	for (auto& v : varVec) {
		if (told->GetBranch(v.c_str())) told->SetBranchStatus(v.c_str(), 1);
	}
	const auto& tnew = told->CloneTree(-1, "fast");

	return tnew;
}

void skimFile(const char *filein, const char *fileout) {
	TFile fin(filein);
	TFile fout(fileout, "RECREATE");

	fout.cd();
	const auto& tdir_muidtrg = fout.mkdir("tpTree");
	tdir_muidtrg->cd();
	const auto& tr_muidtrg = trimTree((TTree*)fin.Get("tpTree/fitter_tree"));

	fout.Write();
	fout.Close();
}
