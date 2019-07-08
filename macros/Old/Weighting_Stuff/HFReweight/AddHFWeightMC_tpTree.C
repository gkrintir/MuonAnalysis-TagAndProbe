

void AddHFWeightMC_tpTree(){

//  int filetype = 1; // 1 = pPb, 2 = Pbp, 3 = pPb=Pbp

//  if (filetype == 1) {
// pPb
//  TFile *inputData = TFile::Open("/afs/cern.ch/user/s/stuli/stuliWork/public/TnP_run2/Current/InputFiles/Data/PASingleMuon_PromptReco_pPb_merged_v1.root");
//  TFile *inputMC   = TFile::Open("./MC_PrunedTrees/TnP_DYtoMuMu_Embd_PU_pPb_pruned.root","update");
//  }

//  else if (filetype == 2) {
// Pbp
//  TFile *inputData = TFile::Open("/afs/cern.ch/user/s/stuli/stuliWork/public/TnP_run2/Current/InputFiles/Data/PASingleMuon_PromptReco_Pbp_merged_v1.root");
//  TFile *inputMC   = TFile::Open("./MC_PrunedTrees/TnP_DYtoMuMu_Embd_PU_Pbp_pruned.root","update");
//  }

//  else {
// pPb+Pbp
  TFile *inputData = TFile::Open("/afs/cern.ch/user/s/stuli/stuliWork/public/TnP_run2/Current/InputFiles/Data/PASingleMuon_PromptReco_pPb+Pbp.root");
  TFile *inputMC   = TFile::Open("./MC_PrunedTrees/TnP_DYtoMuMu_Embd_PU-merged.root","update");
//  }
// */

  Float_t DatahiHF;
  Float_t MChiHF;

  Float_t weight;

  TH1F* hDatahiHF_aux  = new TH1F("hDatahiHF_aux" ,"",50,0.,450.);
  TH1F* hDatahiHF2_aux  = new TH1F("hDatahiHF2_aux" ,"",50,0.,450.);
  TH1F* hMChiHF_aux     = new TH1F("hMChiHF_aux"  ,"",50,0.,450.);
  TH1F* hWeighthiHF_aux = new TH1F("hWeighthiHF_aux","",50,0.,450.);

  TH1F* hDatahiHF   = new TH1F("hDatahiHF"  ,"",50,0.,450.);
  TH1F* hDatahiHF2  = new TH1F("hDatahiHF2" ,"",50,0.,450.);

  TH1F* hMChiHF     = new TH1F("hMChiHF"    ,"",50,0.,450.);
  TH1F* hWeighthiHF = new TH1F("hWeighthiHF","",50,0.,450.);

  TH1F* hWeightedMC = new TH1F("hWeightedMC","",50,0.,450.);

  hDatahiHF->Sumw2();
  hMChiHF->Sumw2();

  hDatahiHF_aux->Sumw2();
  hDatahiHF2_aux->Sumw2();
  hMChiHF_aux->Sumw2();

  hWeightedMC->Sumw2();

  dataTree = (TTree*)inputData->Get("tpTree/fitter_tree");
  dataTree->SetBranchAddress("tag_hiHF",&DatahiHF);
  Int_t nData = dataTree->GetEntries();

  Double_t normData = 1.0/nData;

  for(size_t nEvent=0; nEvent<nData; ++nEvent){

    dataTree->GetEntry(nEvent);
    
    hDatahiHF->Fill(DatahiHF);
    hDatahiHF2->Fill(DatahiHF);

    hDatahiHF_aux->Fill(DatahiHF,normData);
    hDatahiHF2_aux->Fill(DatahiHF,normData);

  }

  MCTree = (TTree*)inputMC->Get("tpTree/fitter_tree");
  MCTree->SetBranchAddress("tag_hiHF",&MChiHF);
  Int_t nMC = MCTree->GetEntries();

  Double_t normMC = 1.0/nMC;

  for(size_t nEvent=0; nEvent<nMC; ++nEvent){
    MCTree->GetEntry(nEvent);

    hMChiHF->Fill(MChiHF);

    hMChiHF_aux->Fill(MChiHF,normMC);

  }


  hWeighthiHF = hDatahiHF;
  hWeighthiHF->Divide(hMChiHF);

  hWeighthiHF_aux = hDatahiHF_aux;
  hWeighthiHF_aux->Divide(hMChiHF_aux);

  hDatahiHF->SetMarkerStyle(20);
  hDatahiHF2->SetMarkerStyle(20);
  hMChiHF->SetLineColor(2);

  hDatahiHF_aux->SetMarkerStyle(20);
  hDatahiHF2_aux->SetMarkerStyle(20);
  hMChiHF_aux->SetLineColor(2);

  hDatahiHF->GetXaxis()->SetTitle("HF Energy");
  hDatahiHF2->GetXaxis()->SetTitle("HF Energy");
  hMChiHF->GetXaxis()->SetTitle("HF Energy");

  hDatahiHF->GetYaxis()->SetTitle("weight");
  hDatahiHF2->GetYaxis()->SetTitle("entries");
  hMChiHF->GetYaxis()->SetTitle("entries");

  TCanvas *c = new TCanvas();
  c->Divide(2,2);
  c->cd(1);
  hDatahiHF2->Draw("pe");
  c->cd(2);
  hMChiHF->Draw("");
  c->cd(3);
  hDatahiHF2->Draw("pe");
  hMChiHF->SetLineColor(2);
  hMChiHF->Draw("same");

  c->cd(4);
  hWeighthiHF->Draw("pe");
//  c->SaveAs("c.png");

  TCanvas *ca = new TCanvas();
  ca->Divide(2,2);
  ca->cd(1);
  hDatahiHF2_aux->Draw("pe");
  ca->cd(2);
  hMChiHF_aux->Draw("");
  ca->cd(3);
  hDatahiHF2_aux->Draw("pe");
  hMChiHF_aux->SetLineColor(2);
  hMChiHF_aux->Draw("same");

  ca->cd(4);
  hWeighthiHF_aux->Draw("pe");
//  ca->SaveAs("ca.png");

  TBranch *newBranch = MCTree->Branch("weight", &weight, "weight/F");

  for(size_t nEvent=0; nEvent<nMC; ++nEvent){

    MCTree->GetEntry(nEvent);

    weight = hWeighthiHF_aux->GetBinContent(hWeighthiHF_aux->FindBin(MChiHF));
    hWeightedMC->Fill(MChiHF,weight*normMC);
    newBranch->Fill();
  }

  TCanvas *cc = new TCanvas();
  cc->cd();
  hWeightedMC->SetLineColor(3);
  hWeightedMC->SetLineWidth(2);
  hWeightedMC->GetXaxis()->SetTitle("HF Energy");
  hWeightedMC->GetYaxis()->SetTitle("Weighted MC");
  hWeightedMC->Draw("");
//  hDatahiHF2_aux->Draw("pe same");
//  cc->SaveAs("cc.png");


  inputMC->Write("", TObject::kOverwrite);

}
