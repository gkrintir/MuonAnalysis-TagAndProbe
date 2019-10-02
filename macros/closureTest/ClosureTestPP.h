//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Jan 17 15:39:08 2017 by ROOT version 6.08/04
// from TTree myTree/My TTree of dimuons
// found on file: root://xrootd.unl.edu//store/group/phys_heavyions/dileptons/MC2015/pp502TeV/TTrees/OniaTree_JpsiMM_5p02TeV_TuneCUETP8M1_HINppWinter16DR-75X_mcRun2_asymptotic_ppAt5TeV_v3-v1.root
//////////////////////////////////////////////////////////

#ifndef ClosureTestPP_h
#define ClosureTestPP_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <iostream>

// Header file for the classes stored in the TTree if any.
#include "TClonesArray.h"
#include "TLorentzVector.h"

class ClosureTestPP {
 public :
  TTree          *fChain;   //!pointer to the analyzed TTree or TChain
  Int_t           fCurrent; //!current Tree number in a TChain

  // Fixed size dimensions of array or collections stored in the TTree if any.

  // Declaration of leaf types
  UInt_t          eventNb;
  //  UInt_t          runNb;
  //UInt_t          LS;
  Float_t         zVtx;
  Short_t         nPV;
  //Int_t           Centrality;
  Int_t           nTrig;
  //Int_t           trigPrescale[15];   //[nTrig]
  ULong64_t       HLTriggers;
  /* Int_t           Npix; */
  /* Int_t           NpixelTracks; */
  /* Int_t           Ntracks; */
  Short_t         Reco_QQ_size;
  Short_t         Reco_QQ_type[20];   //[Reco_QQ_size]
  Short_t         Reco_QQ_sign[20];   //[Reco_QQ_size]
  Short_t         Reco_QQ_mumi_idx[20];   //[Reco_QQ_size]
  Short_t         Reco_QQ_mupl_idx[20];   //[Reco_QQ_size]
  Short_t         Reco_QQ_whichGen[20];   //[Reco_QQ_size]
  TClonesArray    *Reco_QQ_4mom;
  ULong64_t       Reco_QQ_trig[20];   //[Reco_QQ_size]
  Bool_t          Reco_QQ_isCowboy[20];   //[Reco_QQ_size]
  Float_t         Reco_QQ_ctau[20];   //[Reco_QQ_size]
  Float_t         Reco_QQ_ctauErr[20];   //[Reco_QQ_size]
  Float_t         Reco_QQ_ctau3D[20];   //[Reco_QQ_size]
  Float_t         Reco_QQ_ctauErr3D[20];   //[Reco_QQ_size]
  Float_t         Reco_QQ_ctauTrue[20];   //[Reco_QQ_size]
  Float_t         Reco_QQ_ctauTrue3D[20];   //[Reco_QQ_size]
  Float_t         Reco_QQ_VtxProb[20];   //[Reco_QQ_size]
  Float_t         Reco_QQ_dca[20];   //[Reco_QQ_size]
  Float_t         Reco_QQ_MassErr[20];   //[Reco_QQ_size]
  TClonesArray    *Reco_QQ_vtx;
  Short_t         Ntracks_fromQQ;   //[Reco_QQ_size]
  Short_t         Reco_mu_size;
  Short_t         Reco_mu_type[20];
  Short_t         Reco_mu_charge[20];
  Short_t         Reco_mu_whichGen[20];
  TClonesArray    *Reco_mu_4mom;
  ULong64_t       Reco_mu_trig[20];
  Bool_t          Reco_mu_highPurity[20];   //[Reco_mu_size]
  Bool_t          Reco_mu_InTightAcc[20];   //[Reco_mu_size]
  Int_t           Reco_mu_SelectionType[20];   //[Reco_mu_size]
  Float_t         Reco_mu_normChi2_inner[20];   //[Reco_mu_size]
  Float_t         Reco_mu_normChi2_global[20];   //[Reco_mu_size]
  Int_t           Reco_mu_nPixWMea[20];   //[Rec
  Int_t           Reco_mu_nTrkWMea[20];   //[Reco_mu_size]
  Int_t           Reco_mu_StationsMatched[20];   //[Reco_mu_size]
  Float_t         Reco_mu_dxy[20];   //[Reco_mu_size]
  Float_t         Reco_mu_dxyErr[20];   //[Reco_mu_size]
  Float_t         Reco_mu_dz[20];   //[Reco_mu_size]
  Float_t         Reco_mu_dzErr[20];   //[Reco_mu_size]
  /* Float_t         Reco_mu_pt_inner[20];   //[Reco_mu_size] */
  /* Float_t         Reco_mu_pt_global[20];   //[Reco_mu_size] */
  /* Float_t         Reco_mu_ptErr_inner[20];   //[Reco_mu_size] */
  /* Float_t         Reco_mu_ptErr_global[20];   //[Reco_mu_size]  Float_t         Reco_mu_dxy[10];   //[Reco_QQ_size] */
  TClonesArray    *Reco_trk_4mom;
  Short_t         Reco_trk_size;
  Short_t         Reco_trk_charge[20];
  Short_t         Reco_trk_whichGenmu[20];
  Float_t         Reco_trk_dxy[20];   //[Reco_mu_size]
  Float_t         Reco_trk_dz[20];   //[Reco_mu_size]
  int         Reco_trk_originalAlgo[20];   //[Reco_mu_size]
  int         Reco_trk_nPixWMea[20];   //[Reco_mu_size]
  int         Reco_trk_nTrkWMea[20];   //[Reco_mu_size]
  Short_t         Gen_QQ_size;
  Short_t         Gen_QQ_whichRec[4];
  Short_t         Gen_QQ_mupl_idx[4];
  Short_t         Gen_QQ_mumi_idx[4];
  TClonesArray    *Gen_QQ_4mom;
  Int_t           Gen_QQ_momId[4];   //[Gen_QQ_size]
  Float_t         Gen_QQ_ctau[4];   //[Gen_QQ_size]
  Float_t         Gen_QQ_ctau3D[4];   //[Gen_QQ_size]
  Short_t         Gen_mu_size;
  Short_t         Gen_mu_whichRec[20];
  Short_t         Gen_mu_charge[20];   //[Gen_mu_size]
  TClonesArray    *Gen_mu_4mom;

  // List of branches
  TBranch        *b_eventNb;   //!
  //  TBranch        *b_runNb;   //!
  //TBranch        *b_LS;   //!
  TBranch        *b_zVtx;   //!
  TBranch        *b_nPV;   //!
  TBranch        *b_Centrality;   //!
  TBranch        *b_nTrig;   //!
  TBranch        *b_trigPrescale;   //!
  TBranch        *b_HLTriggers;   //!
  TBranch        *b_Npix;   //!
  TBranch        *b_NpixelTracks;   //!
  TBranch        *b_Ntracks_fromQQ;   //!
  TBranch        *b_Reco_QQ_size;   //!
  TBranch        *b_Reco_QQ_type;   //!
  TBranch        *b_Reco_QQ_sign;   //!
  TBranch        *b_Reco_QQ_4mom;   //!
  TBranch        *b_Reco_QQ_mupl_idx;   //!
  TBranch        *b_Reco_QQ_mumi_idx;   //!
  TBranch        *b_Reco_QQ_trig;   //!
  TBranch        *b_Reco_QQ_mupl_trig;   //!
  TBranch        *b_Reco_QQ_mumi_trig;   //!
  TBranch        *b_Reco_QQ_isCowboy;   //!
  TBranch        *b_Reco_QQ_ctau;   //!
  TBranch        *b_Reco_QQ_ctauErr;   //!
  TBranch        *b_Reco_QQ_ctau3D;   //!
  TBranch        *b_Reco_QQ_ctauErr3D;   //!
  TBranch        *b_Reco_QQ_VtxProb;   //!
  TBranch        *b_Reco_QQ_dca;   //!
  TBranch        *b_Reco_QQ_MassErr;   //!
  TBranch        *b_Reco_QQ_vtx;   //!
  TBranch        *b_Reco_QQ_Ntrk;   //!
  TBranch        *b_Reco_QQ_whichGen;   //!
  TBranch        *b_Reco_mu_size;   //!
  TBranch        *b_Reco_mu_type;   //!
  TBranch        *b_Reco_mu_charge;   //!
  TBranch        *b_Reco_mu_whichGen;   //!
  TBranch        *b_Reco_mu_4mom;   //!
  TBranch        *b_Reco_mu_trig;   //!
  TBranch        *b_Reco_mu_SelectionType;   //!
  TBranch        *b_Reco_mu_InTightAcc;   //!
  TBranch        *b_Reco_mu_highPurity;   //!
  TBranch        *b_Reco_mu_normChi2_inner;   //!
  TBranch        *b_Reco_mu_normChi2_global;   //!
  TBranch        *b_Reco_mu_nPixWMea;   //!
  TBranch        *b_Reco_mu_nTrkWMea;   //!
  TBranch        *b_Reco_mu_StationsMatched;   //!
  TBranch        *b_Reco_mu_dxy;   //!
  TBranch        *b_Reco_mu_dxyErr;   //!
  TBranch        *b_Reco_mu_dz;   //!
  TBranch        *b_Reco_mu_dzErr;   //!
  /* TBranch        *b_Reco_mu_pt_inner;   //! */
  /* TBranch        *b_Reco_mu_pt_global;   //! */
  /* TBranch        *b_Reco_mu_ptErr_inner;   //! */
  /* TBranch        *b_Reco_mu_ptErr_global;   //! */
  TBranch        *b_Reco_trk_4mom;   //!
  TBranch        *b_Reco_trk_whichGenmu;   //!
  TBranch        *b_Reco_trk_charge;   //!
  TBranch        *b_Reco_trk_size;   //!
  TBranch        *b_Reco_trk_dxy;   //!
  TBranch        *b_Reco_trk_dz;   //!
  TBranch        *b_Reco_trk_originalAlgo;   //!
  TBranch        *b_Reco_trk_nPixWMea;   //!
  TBranch        *b_Reco_trk_nTrkWMea;   //!
  TBranch        *b_Gen_QQ_size;   //!
  TBranch        *b_Gen_QQ_mupl_idx;   //!
  TBranch        *b_Gen_QQ_mumi_idx;   //!
  TBranch        *b_Gen_QQ_4mom;   //!
  TBranch        *b_Gen_QQ_momId;   //!
  TBranch        *b_Gen_QQ_ctau;   //!
  TBranch        *b_Gen_QQ_ctau3D;   //!
  TBranch        *b_Gen_QQ_whichRec;   //[Reco_QQ_size]
  TBranch        *b_Gen_mu_size;   //!
  TBranch        *b_Gen_mu_charge;   //!
  TBranch        *b_Gen_mu_4mom;   //!
  TBranch        *b_Gen_mu_whichRec;   //!

  ClosureTestPP(TTree *tree=0);
  virtual ~ClosureTestPP();
  virtual Int_t    CutSgMuon(Long64_t entry);
  virtual Bool_t   isGlobalMuonInAccept2015 (TLorentzVector* Muon);
  virtual Bool_t   isGlobalMuonInTightAccept2018 (TLorentzVector* Muon);
  virtual Bool_t   areMuonsInAcceptance2015 (Int_t iRecoQQ);
  virtual Bool_t   passQualityCuts2015 (Int_t iRecoQQ);
  virtual Bool_t   Cut_muplmi (Int_t iRecoQQ);
  virtual Int_t    GetEntry(Long64_t entry);
  virtual Long64_t LoadTree(Long64_t entry);
  virtual void     Init(TTree *tree);
  virtual void     Loop(const char* filename);
  virtual Bool_t   Notify();
  virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef ClosureTestPP_cxx
ClosureTestPP::ClosureTestPP(TTree *tree) : fChain(0) 
{
  // if parameter tree is not specified (or zero), connect the file
  // used to generate this class and read the Tree.
  if (tree == 0) {
    TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("~/tuples/pp17/PromptJpsi/dimuons/Oniatree_MC_dimuons_PromptJpsi_ptHatMin2_26082019.root");
    if (!f || !f->IsOpen()) {
      f = new TFile("~/tuples/pp17/PromptJpsi/dimuons/Oniatree_MC_dimuons_PromptJpsi_ptHatMin2_26082019.root");
    }
    TDirectory * dir = (TDirectory*)f->Get("~/tuples/pp17/PromptJpsi/dimuons/Oniatree_MC_dimuons_PromptJpsi_ptHatMin2_26082019.root:/hionia");
    dir->GetObject("myTree",tree);

  }
  Init(tree);
}

ClosureTestPP::~ClosureTestPP()
{
  if (!fChain) return;
  delete fChain->GetCurrentFile();
}

Int_t ClosureTestPP::GetEntry(Long64_t entry)
{
  // Read contents of entry.
  if (!fChain) return 0;
  return fChain->GetEntry(entry);
}
Long64_t ClosureTestPP::LoadTree(Long64_t entry)
{
  // Set the environment to read one entry
  if (!fChain) return -5;
  Long64_t centry = fChain->LoadTree(entry);
  if (centry < 0) return centry;
  if (fChain->GetTreeNumber() != fCurrent) {
    fCurrent = fChain->GetTreeNumber();
    Notify();
  }
  return centry;
}

void ClosureTestPP::Init(TTree *tree)
{
  // The Init() function is called when the selector needs to initialize
  // a new tree or chain. Typically here the branch addresses and branch
  // pointers of the tree will be set.
  // It is normally not necessary to make changes to the generated
  // code, but the routine can be extended by the user if needed.
  // Init() will be called many times when running on PROOF
  // (once per file to be processed).

  // Set object pointer
  Reco_QQ_4mom = 0;
  Reco_QQ_vtx = 0;
  Reco_mu_4mom = 0;
  Reco_trk_4mom = 0;
  Gen_QQ_4mom = 0;
  Gen_mu_4mom = 0;
  // Set branch addresses and branch pointers
  if (!tree) return;
  fChain = tree;
  fCurrent = -1;
  fChain->SetMakeClass(1);

  fChain->SetBranchAddress("eventNb", &eventNb, &b_eventNb);
  //  fChain->SetBranchAddress("runNb", &runNb, &b_runNb);
  //fChain->SetBranchAddress("LS", &LS, &b_LS);
  fChain->SetBranchAddress("zVtx", &zVtx, &b_zVtx);
  fChain->SetBranchAddress("nPV", &nPV, &b_nPV);
  //  fChain->SetBranchAddress("Centrality", &Centrality, &b_Centrality);
  fChain->SetBranchAddress("nTrig", &nTrig, &b_nTrig);
  //fChain->SetBranchAddress("trigPrescale", trigPrescale, &b_trigPrescale);
  fChain->SetBranchAddress("HLTriggers", &HLTriggers, &b_HLTriggers);
  //fChain->SetBranchAddress("Npix", &Npix, &b_Npix);
  //fChain->SetBranchAddress("NpixelTracks", &NpixelTracks, &b_NpixelTracks);
  fChain->SetBranchAddress("Ntracks_fromQQ", &Ntracks_fromQQ, &b_Ntracks_fromQQ);
  fChain->SetBranchAddress("Reco_QQ_size", &Reco_QQ_size, &b_Reco_QQ_size);
  fChain->SetBranchAddress("Reco_QQ_sign", Reco_QQ_sign, &b_Reco_QQ_sign);
  fChain->SetBranchAddress("Reco_QQ_mupl_idx", &Reco_QQ_mupl_idx, &b_Reco_QQ_mupl_idx);
  fChain->SetBranchAddress("Reco_QQ_mumi_idx", &Reco_QQ_mumi_idx, &b_Reco_QQ_mumi_idx);
  fChain->SetBranchAddress("Reco_QQ_4mom", &Reco_QQ_4mom, &b_Reco_QQ_4mom);
  fChain->SetBranchAddress("Reco_QQ_trig", Reco_QQ_trig, &b_Reco_QQ_trig);
  fChain->SetBranchAddress("Reco_QQ_isCowboy", Reco_QQ_isCowboy, &b_Reco_QQ_isCowboy);
  fChain->SetBranchAddress("Reco_QQ_ctau", Reco_QQ_ctau, &b_Reco_QQ_ctau);
  fChain->SetBranchAddress("Reco_QQ_ctauErr", Reco_QQ_ctauErr, &b_Reco_QQ_ctauErr);
  fChain->SetBranchAddress("Reco_QQ_ctau3D", Reco_QQ_ctau3D, &b_Reco_QQ_ctau3D);
  fChain->SetBranchAddress("Reco_QQ_ctauErr3D", Reco_QQ_ctauErr3D, &b_Reco_QQ_ctauErr3D);
  fChain->SetBranchAddress("Reco_QQ_VtxProb", Reco_QQ_VtxProb, &b_Reco_QQ_VtxProb);
  fChain->SetBranchAddress("Reco_QQ_dca", Reco_QQ_dca, &b_Reco_QQ_dca);
  fChain->SetBranchAddress("Reco_QQ_MassErr", Reco_QQ_MassErr, &b_Reco_QQ_MassErr);
  fChain->SetBranchAddress("Reco_QQ_vtx", &Reco_QQ_vtx, &b_Reco_QQ_vtx);
  fChain->SetBranchAddress("Reco_QQ_whichGen", &Reco_QQ_whichGen, &b_Reco_QQ_whichGen);

  fChain->SetBranchAddress("Reco_mu_size", &Reco_mu_size, &b_Reco_mu_size);
  fChain->SetBranchAddress("Reco_mu_type", Reco_mu_type, &b_Reco_mu_type);
  fChain->SetBranchAddress("Reco_mu_charge", Reco_mu_charge, &b_Reco_mu_charge);
  fChain->SetBranchAddress("Reco_mu_whichGen", Reco_mu_whichGen, &b_Reco_mu_whichGen);
  fChain->SetBranchAddress("Reco_mu_InTightAcc", Reco_mu_InTightAcc, &b_Reco_mu_InTightAcc);
  fChain->SetBranchAddress("Reco_mu_4mom", &Reco_mu_4mom, &b_Reco_mu_4mom);
  fChain->SetBranchAddress("Reco_mu_trig", Reco_mu_trig, &b_Reco_mu_trig);
  fChain->SetBranchAddress("Reco_mu_SelectionType", Reco_mu_SelectionType, &b_Reco_mu_SelectionType);
  fChain->SetBranchAddress("Reco_mu_highPurity", Reco_mu_highPurity, &b_Reco_mu_highPurity);
  //  fChain->SetBranchAddress("Reco_mu_TrkMuArb", Reco_mu_TrkMuArb, &b_Reco_mu_TrkMuArb);
  //  fChain->SetBranchAddress("Reco_mu_TMOneStaTight", Reco_mu_TMOneStaTight, &b_Reco_mu_TMOneStaTight);
  fChain->SetBranchAddress("Reco_mu_normChi2_inner", Reco_mu_normChi2_inner, &b_Reco_mu_normChi2_inner);
  fChain->SetBranchAddress("Reco_mu_normChi2_global", Reco_mu_normChi2_global, &b_Reco_mu_normChi2_global);
  fChain->SetBranchAddress("Reco_mu_nPixWMea", Reco_mu_nPixWMea, &b_Reco_mu_nPixWMea);
  fChain->SetBranchAddress("Reco_mu_nTrkWMea", Reco_mu_nTrkWMea, &b_Reco_mu_nTrkWMea);
  fChain->SetBranchAddress("Reco_mu_StationsMatched", Reco_mu_StationsMatched, &b_Reco_mu_StationsMatched);
  fChain->SetBranchAddress("Reco_mu_dxy", Reco_mu_dxy, &b_Reco_mu_dxy);
  fChain->SetBranchAddress("Reco_mu_dxyErr", Reco_mu_dxyErr, &b_Reco_mu_dxyErr);
  fChain->SetBranchAddress("Reco_mu_dz", Reco_mu_dz, &b_Reco_mu_dz);
  fChain->SetBranchAddress("Reco_mu_dzErr", Reco_mu_dzErr, &b_Reco_mu_dzErr);
  /* fChain->SetBranchAddress("Reco_mu_pt_inner", Reco_mu_pt_inner, &b_Reco_mu_pt_inner); */
  /* fChain->SetBranchAddress("Reco_mu_pt_global", Reco_mu_pt_global, &b_Reco_mu_pt_global); */
  /* fChain->SetBranchAddress("Reco_mu_ptErr_inner", Reco_mu_ptErr_inner, &b_Reco_mu_ptErr_inner); */
  /* fChain->SetBranchAddress("Reco_mu_ptErr_global", Reco_mu_ptErr_global, &b_Reco_mu_ptErr_global); */
  fChain->SetBranchAddress("Reco_trk_4mom", &Reco_trk_4mom, &b_Reco_trk_4mom);
  fChain->SetBranchAddress("Reco_trk_whichGenmu", Reco_trk_whichGenmu, &b_Reco_trk_whichGenmu);
  fChain->SetBranchAddress("Reco_trk_size", &Reco_trk_size, &b_Reco_trk_size);
  fChain->SetBranchAddress("Reco_trk_charge", Reco_trk_charge, &b_Reco_trk_charge);
  fChain->SetBranchAddress("Reco_trk_dxy", Reco_trk_dxy, &b_Reco_trk_dxy);
  fChain->SetBranchAddress("Reco_trk_dz", Reco_trk_dz, &b_Reco_trk_dz);
  fChain->SetBranchAddress("Reco_trk_originalAlgo", Reco_trk_originalAlgo, &b_Reco_trk_originalAlgo);
  fChain->SetBranchAddress("Reco_trk_nPixWMea", Reco_trk_nPixWMea, &b_Reco_trk_nPixWMea);
  fChain->SetBranchAddress("Reco_trk_nTrkWMea", Reco_trk_nTrkWMea, &b_Reco_trk_nTrkWMea);

  fChain->SetBranchAddress("Gen_QQ_size", &Gen_QQ_size, &b_Gen_QQ_size);
  fChain->SetBranchAddress("Gen_QQ_4mom", &Gen_QQ_4mom, &b_Gen_QQ_4mom);
  fChain->SetBranchAddress("Gen_QQ_mupl_idx", &Gen_QQ_mupl_idx, &b_Gen_QQ_mupl_idx);
  fChain->SetBranchAddress("Gen_QQ_mumi_idx", &Gen_QQ_mumi_idx, &b_Gen_QQ_mumi_idx);
  fChain->SetBranchAddress("Gen_QQ_momId", Gen_QQ_momId, &b_Gen_QQ_momId);
  fChain->SetBranchAddress("Gen_QQ_ctau", Gen_QQ_ctau, &b_Gen_QQ_ctau);
  fChain->SetBranchAddress("Gen_QQ_ctau3D", Gen_QQ_ctau3D, &b_Gen_QQ_ctau3D);
  fChain->SetBranchAddress("Gen_QQ_whichRec", Gen_QQ_whichRec, &b_Gen_QQ_whichRec);
  fChain->SetBranchAddress("Gen_mu_size", &Gen_mu_size, &b_Gen_mu_size);
  fChain->SetBranchAddress("Gen_mu_whichRec", &Gen_mu_whichRec, &b_Gen_mu_whichRec);
  fChain->SetBranchAddress("Gen_mu_charge", Gen_mu_charge, &b_Gen_mu_charge);
  fChain->SetBranchAddress("Gen_mu_4mom", &Gen_mu_4mom, &b_Gen_mu_4mom);
  Notify();
}

Bool_t ClosureTestPP::Notify()
{
  // The Notify() function is called when a new file is opened. This
  // can be either for a new TTree in a TChain or when when a new TTree
  // is started when using PROOF. It is normally not necessary to make changes
  // to the generated code, but the routine can be extended by the
  // user if needed. The return value is currently not used.

  return kTRUE;
}

void ClosureTestPP::Show(Long64_t entry)
{
  // Print contents of entry.
  // If entry is not specified, print current entry
  if (!fChain) return;
  fChain->Show(entry);
}

Int_t ClosureTestPP::CutSgMuon(Long64_t irec)
{
  // This function may be called from Loop.
  // returns  1 if entry is accepted.
  // returns -1 otherwise.
  // return 1;
  //  cout<<"CutSgMuon: "<<(Reco_mu_nTrkWMea[irec] > 5 )<<" "<<(Reco_mu_nPixWMea[irec]>0)<<" "<<(Reco_mu_normChi2_inner[irec]<4.0)<<" "<<(fabs(Reco_mu_dxy[irec])<0.2)<<" "<<(fabs(Reco_mu_dz[irec])<0.5)<<" "<<(Reco_mu_normChi2_global[irec]<10.0)<<" "<<(Reco_mu_StationsMatched[irec]>0)<<" "<<((Reco_mu_SelectionType[irec]&2)>0)<<" "<<((Reco_mu_SelectionType[irec]&8)>0)<<endl;
  if (Reco_mu_nTrkWMea[irec] > 5 &&   //Reco_mu_nTrkHits[irec]>10 &&
      Reco_mu_nPixWMea[irec]>0 &&
      //Reco_mu_normChi2_inner[irec]<4.0 &&
      /* fabs(Reco_mu_dxy[irec])<0.3 && */
      /* fabs(Reco_mu_dz[irec])<20 && */
      //Reco_mu_normChi2_global[irec]<10.0 &&
      //Reco_mu_nMuValHits[irec]>0 &&
      //Reco_mu_StationsMatched[irec]>0 &&
      //(Reco_mu_SelectionType[irec]&2)>0 && //isGlobal
      (Reco_mu_SelectionType[irec]&4096)>0 //isTracker //TMOneStaTight:4096
      )
    return 1;
  else
    return 0;
}

Bool_t ClosureTestPP::isGlobalMuonInAccept2015 (TLorentzVector* Muon) 
{
  return (fabs(Muon->Eta()) < 2.4 &&
	  ((fabs(Muon->Eta()) < 1.2 && Muon->Pt() >= 3.5) ||
	   (1.2 <= fabs(Muon->Eta()) && fabs(Muon->Eta()) < 2.1 && Muon->Pt() >= 5.77-1.89*fabs(Muon->Eta())) ||
	   (2.1 <= fabs(Muon->Eta()) && Muon->Pt() >= 1.8)));
};

Bool_t ClosureTestPP::isGlobalMuonInTightAccept2018 (TLorentzVector* Muon) 
{
  double pt = Muon->Pt(), eta = Muon->Eta();
  return (fabs(eta) < 2.4 && 
	  ((fabs(eta) < 1.2 && pt >= 3.5 ) || 
	   (1.2 <= fabs(eta) && fabs(eta) < 2.1 && pt >= 5.47-1.89*fabs(eta)) || 
  	   (2.1 <= fabs(eta) && pt >= 1.5)));
};

Bool_t ClosureTestPP::areMuonsInAcceptance2015 (Int_t iRecoQQ)
{
  int recmumi = Reco_QQ_mumi_idx[iRecoQQ];
  int recmupl = Reco_QQ_mupl_idx[iRecoQQ];
  TLorentzVector *RecoQQmupl = (TLorentzVector*) Reco_mu_4mom->At(recmupl);
  TLorentzVector *RecoQQmumi = (TLorentzVector*) Reco_mu_4mom->At(recmumi);
  return ( isGlobalMuonInAccept2015(RecoQQmupl) && isGlobalMuonInAccept2015(RecoQQmumi) );
};  

Bool_t ClosureTestPP::passQualityCuts2015 (Int_t iRecoQQ) 
{
  Bool_t cond = true;
  
  int recmumi = Reco_QQ_mumi_idx[iRecoQQ];
  int recmupl = Reco_QQ_mupl_idx[iRecoQQ];
  cond = cond && Cut_muplmi(recmumi) && Cut_muplmi(recmupl) ;

  cond = cond && (Reco_QQ_VtxProb[iRecoQQ] > 0.01);

  return cond;
}; 

Bool_t ClosureTestPP::Cut_muplmi (Int_t irec) 
{
  Bool_t cond = true;

  // cond = cond && (Reco_QQ_mupl_highPurity[irec]);
  cond = cond && (Reco_mu_SelectionType[irec]&2)>0; //isGlobal
  cond = cond && (Reco_mu_SelectionType[irec]&8)>0; //isTracker
  //  cond = cond && (Reco_QQ_mupl_isGoodMuon[irec]==1);
  cond = cond && (Reco_mu_nTrkWMea[irec] > 5);
  cond = cond && (Reco_mu_nPixWMea[irec] > 0);
  cond = cond && (fabs(Reco_mu_dxy[irec]) < 0.3);
  cond = cond && (fabs(Reco_mu_dz[irec]) < 20.);

  return cond;
}; 

#endif // #ifdef ClosureTestPP_cxx
