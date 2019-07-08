

void AddHFWeightMC_Sta(){

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

  TH1F* hDatahiHF_aux_Sta  = new TH1F("hDatahiHF_aux_Sta" ,"",50,0.,450.);
  TH1F* hDatahiHF2_aux_Sta  = new TH1F("hDatahiHF2_aux_Sta" ,"",50,0.,450.);
  TH1F* hMChiHF_aux_Sta     = new TH1F("hMChiHF_aux_Sta"  ,"",50,0.,450.);
  TH1F* hWeighthiHF_aux_Sta = new TH1F("hWeighthiHF_aux_Sta","",50,0.,450.);

  TH1F* hDatahiHF_Sta   = new TH1F("hDatahiHF_Sta"  ,"",50,0.,450.);
  TH1F* hDatahiHF2_Sta  = new TH1F("hDatahiHF2_Sta" ,"",50,0.,450.);

  TH1F* hMChiHF_Sta     = new TH1F("hMChiHF_Sta"    ,"",50,0.,450.);
  TH1F* hWeighthiHF_Sta = new TH1F("hWeighthiHF_Sta","",50,0.,450.);

  TH1F* hWeightedMC_Sta = new TH1F("hWeightedMC_Sta","",50,0.,450.);

  hDatahiHF_Sta->Sumw2();
  hMChiHF_Sta->Sumw2();

  hDatahiHF_aux_Sta->Sumw2();
  hDatahiHF2_aux_Sta->Sumw2();
  hMChiHF_aux_Sta->Sumw2();

  hWeightedMC_Sta->Sumw2();

  dataTree = (TTree*)inputData->Get("tpTreeSta/fitter_tree");
  dataTree->SetBranchAddress("tag_hiHF",&DatahiHF);
  Int_t nData = dataTree->GetEntries();

  Double_t normData = 1.0/nData;

  for(size_t nEvent=0; nEvent<nData; ++nEvent){

    dataTree->GetEntry(nEvent);
    
    hDatahiHF_Sta->Fill(DatahiHF);
    hDatahiHF2_Sta->Fill(DatahiHF);

    hDatahiHF_aux_Sta->Fill(DatahiHF,normData);
    hDatahiHF2_aux_Sta->Fill(DatahiHF,normData);

  }

  MCTree = (TTree*)inputMC->Get("tpTreeSta/fitter_tree");
  MCTree->SetBranchAddress("tag_hiHF",&MChiHF);
  Int_t nMC = MCTree->GetEntries();

  Double_t normMC = 1.0/nMC;

  for(size_t nEvent=0; nEvent<nMC; ++nEvent){
    MCTree->GetEntry(nEvent);

    hMChiHF_Sta->Fill(MChiHF);

    hMChiHF_aux_Sta->Fill(MChiHF,normMC);

  }


  hWeighthiHF_Sta = hDatahiHF_Sta;
  hWeighthiHF_Sta->Divide(hMChiHF_Sta);

  hWeighthiHF_aux_Sta = hDatahiHF_aux_Sta;
  hWeighthiHF_aux_Sta->Divide(hMChiHF_aux_Sta);

  hDatahiHF_Sta->SetMarkerStyle(20);
  hDatahiHF2_Sta->SetMarkerStyle(20);
  hMChiHF_Sta->SetLineColor(2);

  hDatahiHF_aux_Sta->SetMarkerStyle(20);
  hDatahiHF2_aux_Sta->SetMarkerStyle(20);
  hMChiHF_aux_Sta->SetLineColor(2);

  hDatahiHF_Sta->GetXaxis()->SetTitle("HF Energy");
  hDatahiHF2_Sta->GetXaxis()->SetTitle("HF Energy");
  hMChiHF_Sta->GetXaxis()->SetTitle("HF Energy");

  hDatahiHF_Sta->GetYaxis()->SetTitle("weight");
  hDatahiHF2_Sta->GetYaxis()->SetTitle("entries");
  hMChiHF_Sta->GetYaxis()->SetTitle("entries");

  TCanvas *c = new TCanvas();
  c->Divide(2,2);
  c->cd(1);
  hDatahiHF2_Sta->Draw("pe");
  c->cd(2);
  hMChiHF_Sta->Draw("");
  c->cd(3);
  hDatahiHF2_Sta->Draw("pe");
  hMChiHF_Sta->SetLineColor(2);
  hMChiHF_Sta->Draw("same");

  c->cd(4);
  hWeighthiHF_Sta->Draw("pe");
//  c->SaveAs("c.png");

  TCanvas *ca = new TCanvas();
  ca->Divide(2,2);
  ca->cd(1);
  hDatahiHF2_aux_Sta->Draw("pe");
  ca->cd(2);
  hMChiHF_aux_Sta->Draw("");
  ca->cd(3);
  hDatahiHF2_aux_Sta->Draw("pe");
  hMChiHF_aux_Sta->SetLineColor(2);
  hMChiHF_aux_Sta->Draw("same");

  ca->cd(4);
  hWeighthiHF_aux_Sta->Draw("pe");
//  ca->SaveAs("ca.png");

  TBranch *newBranch = MCTree->Branch("weight", &weight, "weight/F");

  for(size_t nEvent=0; nEvent<nMC; ++nEvent){

    MCTree->GetEntry(nEvent);

    weight = hWeighthiHF_aux_Sta->GetBinContent(hWeighthiHF_aux_Sta->FindBin(MChiHF));
    hWeightedMC_Sta->Fill(MChiHF,weight*normMC);
    newBranch->Fill();
  }

  TCanvas *cc = new TCanvas();
  cc->cd();
  hWeightedMC_Sta->SetLineColor(3);
  hWeightedMC_Sta->SetLineWidth(2);
  hWeightedMC_Sta->GetXaxis()->SetTitle("HF Energy");
  hWeightedMC_Sta->GetYaxis()->SetTitle("Weighted MC");
  hWeightedMC_Sta->Draw("");
//  hDatahiHF2_aux_Sta->Draw("pe same");
//  cc->SaveAs("cc.png");


  inputMC->Write("", TObject::kOverwrite);

}
