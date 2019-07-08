

void AddHFWeightMC_Trk(){

//  Int_t filetype = 1; // 1 = pPb, 2 = Pbp, 3 = pPb=Pbp

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

  Float_t DatahiHF;
  Float_t MChiHF;

  Float_t weight;

  TH1F* hDatahiHF_aux_Trk  = new TH1F("hDatahiHF_aux_Trk" ,"",50,0.,450.);
  TH1F* hDatahiHF2_aux_Trk  = new TH1F("hDatahiHF2_aux_Trk" ,"",50,0.,450.);
  TH1F* hMChiHF_aux_Trk     = new TH1F("hMChiHF_aux_Trk"  ,"",50,0.,450.);
  TH1F* hWeighthiHF_aux_Trk = new TH1F("hWeighthiHF_aux_Trk","",50,0.,450.);

  TH1F* hDatahiHF_Trk   = new TH1F("hDatahiHF_Trk"  ,"",50,0.,450.);
  TH1F* hDatahiHF2_Trk  = new TH1F("hDatahiHF2_Trk" ,"",50,0.,450.);

  TH1F* hMChiHF_Trk     = new TH1F("hMChiHF_Trk"    ,"",50,0.,450.);
  TH1F* hWeighthiHF_Trk = new TH1F("hWeighthiHF_Trk","",50,0.,450.);

  TH1F* hWeightedMC_Trk = new TH1F("hWeightedMC_Trk","",50,0.,450.);

  hDatahiHF_Trk->Sumw2();
  hMChiHF_Trk->Sumw2();

  hDatahiHF_aux_Trk->Sumw2();
  hDatahiHF2_aux_Trk->Sumw2();
  hMChiHF_aux_Trk->Sumw2();

  hWeightedMC_Trk->Sumw2();

  dataTree = (TTree*)inputData->Get("tpTreeTrk/fitter_tree");
  dataTree->SetBranchAddress("tag_hiHF",&DatahiHF);
  Int_t nData = dataTree->GetEntries();

  Double_t normData = 1.0/nData;

  for(size_t nEvent=0; nEvent<nData; ++nEvent){

    dataTree->GetEntry(nEvent);
    
    hDatahiHF_Trk->Fill(DatahiHF);
    hDatahiHF2_Trk->Fill(DatahiHF);

    hDatahiHF_aux_Trk->Fill(DatahiHF,normData);
    hDatahiHF2_aux_Trk->Fill(DatahiHF,normData);

  }

  MCTree = (TTree*)inputMC->Get("tpTreeTrk/fitter_tree");
  MCTree->SetBranchAddress("tag_hiHF",&MChiHF);
  Int_t nMC = MCTree->GetEntries();

  Double_t normMC = 1.0/nMC;

  for(size_t nEvent=0; nEvent<nMC; ++nEvent){
    MCTree->GetEntry(nEvent);

    hMChiHF_Trk->Fill(MChiHF);

    hMChiHF_aux_Trk->Fill(MChiHF,normMC);

  }


  hWeighthiHF_Trk = hDatahiHF_Trk;
  hWeighthiHF_Trk->Divide(hMChiHF_Trk);

  hWeighthiHF_aux_Trk = hDatahiHF_aux_Trk;
  hWeighthiHF_aux_Trk->Divide(hMChiHF_aux_Trk);

  hDatahiHF_Trk->SetMarkerStyle(20);
  hDatahiHF2_Trk->SetMarkerStyle(20);
  hMChiHF_Trk->SetLineColor(2);

  hDatahiHF_aux_Trk->SetMarkerStyle(20);
  hDatahiHF2_aux_Trk->SetMarkerStyle(20);
  hMChiHF_aux_Trk->SetLineColor(2);

  hDatahiHF_Trk->GetXaxis()->SetTitle("HF Energy");
  hDatahiHF2_Trk->GetXaxis()->SetTitle("HF Energy");
  hMChiHF_Trk->GetXaxis()->SetTitle("HF Energy");

  hDatahiHF_Trk->GetYaxis()->SetTitle("weight");
  hDatahiHF2_Trk->GetYaxis()->SetTitle("entries");
  hMChiHF_Trk->GetYaxis()->SetTitle("entries");

  TCanvas *c = new TCanvas();
  c->Divide(2,2);
  c->cd(1);
  hDatahiHF2_Trk->Draw("pe");
  c->cd(2);
  hMChiHF_Trk->Draw("");
  c->cd(3);
  hDatahiHF2_Trk->Draw("pe");
  hMChiHF_Trk->SetLineColor(2);
  hMChiHF_Trk->Draw("same");

  c->cd(4);
  hWeighthiHF_Trk->Draw("pe");
//  c->SaveAs("c.png");

  TCanvas *ca = new TCanvas();
  ca->Divide(2,2);
  ca->cd(1);
  hDatahiHF2_aux_Trk->Draw("pe");
  ca->cd(2);
  hMChiHF_aux_Trk->Draw("");
  ca->cd(3);
  hDatahiHF2_aux_Trk->Draw("pe");
  hMChiHF_aux_Trk->SetLineColor(2);
  hMChiHF_aux_Trk->Draw("same");

  ca->cd(4);
  hWeighthiHF_aux_Trk->Draw("pe");
//  ca->SaveAs("ca.png");

  TBranch *newBranch = MCTree->Branch("weight", &weight, "weight/F");

  for(size_t nEvent=0; nEvent<nMC; ++nEvent){

    MCTree->GetEntry(nEvent);

    weight = hWeighthiHF_aux_Trk->GetBinContent(hWeighthiHF_aux_Trk->FindBin(MChiHF));
    hWeightedMC_Trk->Fill(MChiHF,weight*normMC);
    newBranch->Fill();
  }

  TCanvas *cc = new TCanvas();
  cc->cd();
  hWeightedMC_Trk->SetLineColor(3);
  hWeightedMC_Trk->SetLineWidth(2);
  hWeightedMC_Trk->GetXaxis()->SetTitle("HF Energy");
  hWeightedMC_Trk->GetYaxis()->SetTitle("Weighted MC");
  hWeightedMC_Trk->Draw("");
//  hDatahiHF2_aux_Trk->Draw("pe same");
//  cc->SaveAs("cc.png");


  inputMC->Write("", TObject::kOverwrite);

}
