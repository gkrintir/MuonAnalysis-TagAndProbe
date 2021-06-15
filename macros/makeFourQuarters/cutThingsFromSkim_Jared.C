#include "TTree.h"
#include "TFile.h"
#include <iostream>
#include <math.h>

TTree* skimTree(TTree* told, const std::string& type, const int& ps, int whichQuarter)
{
	std::vector<std::string> varVec = { "pt", "eta", "abseta", "mass", "tag_nVertices", /*"tag_acceptance", "probe_acceptance", "probe_trg_acceptance", "isNotMuonSeeded",*/ "tag_hiNtracks", "TM", "SoftID", "pair_dz", "tag_pt", "pair_probeMultiplicity"/*"HLT_PAL1DoubleMuOpen", "pair_dz", "Custom_track_cuts"*/ }; //with flags
	//std::vector<std::string> varVec = { "pt", "eta", "abseta", "mass", "tag_nVertices", "probe_trg_acceptance", "tag_hiNtracks", "TM", "SoftID", "HLT_PAL1DoubleMuOpen" }; //for Muid from Trk
	string probe_muid_newacceptance = "( (abseta<0.3 && pt>3.4) || (abseta>0.3 && abseta<1.1 && pt>3.3) || (abseta>1.1 && abseta<1.5 && pt>(9.075-5.25*abseta)) || (abseta>1.5 && abseta<2.4 && pt>(2.4-0.8*abseta) && pt>0.8) )";

	std::string sel = "";
	if (type == "Trg") { sel = ("isNotMuonSeeded == 1 && TM==1 && SoftID==1 && tag_acceptance == 1 && probe_trg_acceptance==1 && (mass>=2.6 && mass<=3.6)"); }
	else if (type == "MuID") { sel = (probe_muid_newacceptance + " && (mass>=2.6 && mass<=3.6) && pair_dz<=0.1 && tag_pt>=3.0"); }
	else if (type == "MuID_Trk") { sel = ("TM==1"); } //going from Trk
	else if (type == "Trk") { sel = ("")/*"isNotMuonSeeded==1 && tag_acceptance == 1 && probe_acceptance==1 && (mass>=2.7 && mass<=3.5) && (pair_dz>-2 && pair_dz<2) && Custom_track_cuts==1")*/; }

	told->SetBranchStatus("*", 0);
	for (auto& v : varVec) { if (told->GetBranch(v.c_str())) told->SetBranchStatus(v.c_str(), 1); }
	const Long64_t& entries = told->GetEntriesFast() / ps;

        cout << "entries = " << entries << endl;
        const Long64_t& nentries = entries/4;
        const Long64_t& firstentry = (whichQuarter-1)*nentries;
        cout << "nentries = " << nentries << endl;
        cout << "firstentry = " << firstentry << endl;
        const auto tnew = (whichQuarter>0 ? told->CopyTree(sel.c_str(), 0, nentries, firstentry) : told->CloneTree(-1,"fast"));
        
  /*      const Long64_t& firstentry = whichQuarter-1;
        cout << "firstentry = " << firstentry << endl;
	const auto tnew = (sel != "" ? told->CopyTree(sel.c_str(), 0, entries, firstentry) : told->CloneTree((ps > 1 ? entries : -1), "fast"));
*/
	return tnew;
}

void cutThingsFromSkim_Jared(const char *filein, const char *fileout, const std::string& type = "MuID", const int& ps = 1, const int whichTenth = 1) {
	TFile fin(filein);
	TFile fout(fileout, "RECREATE");

	fout.cd();
	const auto& tdir = fout.mkdir("tpTree");
	tdir->cd();
	const auto& tree = skimTree((TTree*)fin.Get("tpTree/fitter_tree"), type, ps, whichTenth);

	fout.Write();
	fout.Close();
}
