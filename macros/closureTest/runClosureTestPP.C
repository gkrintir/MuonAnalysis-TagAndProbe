#include "ClosureTestPP.C"

void runClosureTestPP() {
  TFile *f = TFile::Open("/home/llr/cms/falmagne/tuples/pp17/PromptJpsi/dimuons/Oniatree_MC_dimuons_PromptJpsi_ptHatMin2_18092019.root");
  TTree *tr = (TTree*) f->Get("hionia/myTree");
  ClosureTestPP toto(tr);
  toto.Loop("histos_trd_pp.root");
}
