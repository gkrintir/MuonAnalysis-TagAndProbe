#include "TTree.h"
#include "TFile.h"
#include <iostream>
#include <math.h>

TTree* skimTree(TTree* told, const std::string& type, const int& ps)
{
	//std::vector<std::string> varVec = { "pt", "eta", "abseta", "mass", "tag_nVertices", "tag_acceptance", "probe_acceptance", "probe_trg_acceptance", "isNotMuonSeeded", "tag_hiNtracks", "TM", "SoftID", "HLT_PAL1DoubleMuOpen", "Custom_track_cuts", "isHighPurity", "probe_acceptance_new", "tag_HLT_PAL3Mu3", "tag_HLT_PAL3Mu7"}; //with flags
	std::vector<std::string> varVec = { "pt", "eta", "abseta", "mass", "tag_nVertices", "probe_trg_acceptance", "tag_hiNtracks", "TM", "SoftID", "HLT_PAL1DoubleMuOpen", "tag_HLT_PAL3Mu3", "tag_HLT_PAL3Mu7", "weight" }; //for Muid from Trk

	std::string sel = "";
	if (type == "Trg") { sel = ("isNotMuonSeeded == 1 && TM==1 && SoftID==1 && tag_acceptance == 1 && probe_trg_acceptance==1 && (mass>=2.6 && mass<=3.6) && Custom_track_cuts==1 && (tag_HLT_PAL3Mu3==1||tag_HLT_PAL3Mu7==1)"); }
	else if (type == "MuID") { sel = ("isNotMuonSeeded == 1 && TM==1 && tag_acceptance == 1 && probe_acceptance_new==1 && (mass>=2.6 && mass<=3.6) && Custom_track_cuts==1 && (tag_HLT_PAL3Mu3==1||tag_HLT_PAL3Mu7==1)"); }
	else if (type == "MuID_Trk") { sel = ("TM==1"); } //going from Trk
	else if (type == "Trk") { sel = ("isNotMuonSeeded==1 && tag_acceptance == 1 && probe_acceptance_new==1 && (mass>=2.6 && mass<=3.6) && Custom_track_cuts==1 && (tag_HLT_PAL3Mu3==1||tag_HLT_PAL3Mu7==1)"); }

	told->SetBranchStatus("*", 0);
	for (auto& v : varVec) { if (told->GetBranch(v.c_str())) told->SetBranchStatus(v.c_str(), 1); }
	const Long64_t& entries = told->GetEntriesFast() / ps;

	const auto tnew = (sel != "" ? told->CopyTree(sel.c_str(), 0, entries) : told->CloneTree((ps > 1 ? entries : -1), "fast"));

	return tnew;
}

void cutThingsFromSkim(const char *filein, const char *fileout, const std::string& type = "Trk", const int& ps = 1) {
	TFile fin(filein);
	TFile fout(fileout, "RECREATE");

	fout.cd();
	const auto& tdir = fout.mkdir("tpTree");
	tdir->cd();
	const auto& tree = skimTree((TTree*)fin.Get("tpTree/fitter_tree"), type, ps);

	fout.Write();
	fout.Close();
}