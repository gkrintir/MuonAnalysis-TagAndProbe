#include "TTree.h"
#include "TFile.h"
#include <iostream>
#include <math.h>

TTree* trimTree(TTree* told)
{
  std::vector<std::string> varVec = {"pt", "eta", "mass", "tag_hiNtracks", "isTrkM", "isMuonID", "isTrg"};

  told->SetBranchStatus("*",0);
  for (auto& v : varVec) {
    if (told->GetBranch(v.c_str())) told->SetBranchStatus(v.c_str(), 1);
  }
  const auto& tnew = told->CloneTree(-1,"fast");

  return tnew;
}

void skimFile(const char *filein, const char *fileout) {
   TFile fin(filein);
   TFile fout(fileout,"RECREATE");

   fout.cd();
   const auto& tdir_muidtrg = fout.mkdir("tpTree");
   tdir_muidtrg->cd();
   const auto& tr_muidtrg = trimTree((TTree*)fin.Get("tpTree/fitter_tree"));

   fout.Write();
   fout.Close();
}
