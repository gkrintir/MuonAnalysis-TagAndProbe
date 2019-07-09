#include "TTree.h"
#include "TFile.h"
#include <iostream>
#include <math.h>

TTree* skimTree(TTree* told, const std::string& type, const int& ps)
{
	//std::vector<std::string> varVec = {"pt", "eta", "abseta", "mass", "dzPV", "dxyPV", "tag_hiNtracks","isNotMuonSeeded", "TM", "SoftHINoDxyz", "HLT_PAL1DoubleMuOpen"}; //without flags
	std::vector<std::string> varVec = { "pt", "eta", "abseta", "mass", "tag_hiNtracks","isNotMuonSeeded", "TM", "SoftID", "HLT_PAL1DoubleMuOpen" }; //with flags

	std::string sel = "";
	if (type == "Trg") { sel = ("isNotMuonSeeded == 1 && TM==1 && SoftID==1 && (mass>=2.6 && mass<=3.6)"); }
	else if (type == "MuID") { sel = ("isNotMuonSeeded == 1 && TM==1 && (mass>=2.6 && mass<=3.6)"); }
	else if (type == "Trk") { sel = ("isNotMuonSeeded==1 && (mass>=2.6 && mass<=3.6)"); }

	told->SetBranchStatus("*", 0);
	for (auto& v : varVec) { if (told->GetBranch(v.c_str())) told->SetBranchStatus(v.c_str(), 1); }
	const Long64_t& entries = told->GetEntriesFast() / ps;

	const auto tnew = (sel != "" ? told->CopyTree(sel.c_str(), 0, entries) : told->CloneTree((ps > 1 ? entries : -1), "fast"));

	return tnew;
}

void cutThingsFromSkim(const char *filein, const char *fileout, const std::string& type = "", const int& ps = 1) {
	TFile fin(filein);
	TFile fout(fileout, "RECREATE");

	fout.cd();
	const auto& tdir = fout.mkdir("tpTree");
	tdir->cd();
	const auto& tree = skimTree((TTree*)fin.Get("tpTree/fitter_tree"), type, ps);

	fout.Write();
	fout.Close();
}