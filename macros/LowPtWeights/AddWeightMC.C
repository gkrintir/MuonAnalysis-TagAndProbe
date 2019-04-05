void AddWeightMC(){
// Weighting is for probe muons

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
  TFile *inputData = TFile::Open("/afs/cern.ch/user/s/stuli/stuliWork/public/TnP_run2/Current/InputFiles/LowPt_Nov2018/tnpJPsi_Data_bothDir.root");
  TFile *inputMC   = TFile::Open("/afs/cern.ch/user/s/stuli/stuliWork/public/TnP_run2/Current/InputFiles/LowPt_Nov2018/tnpJPsi_MC-bothDir_noWeight.root","update");
//  }

  Float_t Data_TYPE;
  Float_t MC_TYPE;
  Float_t weight_TYPE;
  Float_t weighted_TYPE;
  Int_t Data_SoftHI;
  Int_t MC_SoftHI;

  TH1F* hData_TYPE   = new TH1F("hData_TYPE"  ,"",nBins,LowLimit,HighLimit);
  TH1F* hMC_TYPE     = new TH1F("hMC_TYPE"    ,"",nBins,LowLimit,HighLimit);
  TH1F* hWeight_TYPE = new TH1F("hWeight_TYPE","",nBins,LowLimit,HighLimit);
  TH1F* hData_TYPE_Normalized  = new TH1F("hData_TYPE_Normalized" ,"",nBins,LowLimit,HighLimit);
  TH1F* hMC_TYPE_Normalized     = new TH1F("hMC_TYPE_Normalized"  ,"",nBins,LowLimit,HighLimit);
  TH1F* hWeight_TYPE_Normalized = new TH1F("hWeight_TYPE_Normalized","",nBins,LowLimit,HighLimit);
  TH1F* hWeightedMC_TYPE = new TH1F("hWeightedMC_TYPE","",nBins,LowLimit,HighLimit);

  hData_TYPE->Sumw2();
  hMC_TYPE->Sumw2();
  hData_TYPE_Normalized->Sumw2();
  hMC_TYPE_Normalized->Sumw2();
  hWeightedMC_TYPE->Sumw2();

  dataTree = (TTree*)inputData->Get("tpTree/fitter_tree");
  dataTree->SetBranchAddress("TYPE",&Data_TYPE);
  dataTree->SetBranchAddress("SoftHI",&Data_SoftHI);

  Int_t nData = dataTree->GetEntries();
  cout << " Nentries data: " << nData << endl;
  Double_t normData = 1.0/nData;

  for(size_t nEvent=0; nEvent<nData; ++nEvent){
    dataTree->GetEntry(nEvent);
    if(Data_SoftHI == 1){
    	hData_TYPE->Fill(Data_TYPE);
    	hData_TYPE_Normalized->Fill(Data_TYPE,normData);
    }
  }

  MCTree = (TTree*)inputMC->Get("tpTree/fitter_tree");
  MCTree->SetBranchAddress("TYPE",&MC_TYPE);
  MCTree->SetBranchAddress("SoftHI",&MC_SoftHI);

  Int_t nMC = MCTree->GetEntries();
  cout << " Nentries MC: " << nMC << endl;
  Double_t normMC = 1.0/nMC;

  for(size_t nEvent=0; nEvent<nMC; ++nEvent){
    MCTree->GetEntry(nEvent);
    if(MC_SoftHI == 1){
    	hMC_TYPE->Fill(MC_TYPE);
    	hMC_TYPE_Normalized->Fill(MC_TYPE,normMC);
    }
  }

  hWeight_TYPE = hData_TYPE;
  hWeight_TYPE->Divide(hMC_TYPE);
  hWeight_TYPE_Normalized = hData_TYPE_Normalized;
  hWeight_TYPE_Normalized->Divide(hMC_TYPE_Normalized);

  hData_TYPE->SetMarkerStyle(20);
  hData_TYPE->SetMarkerColor(3); // Neon Green
  hMC_TYPE->SetLineColor(2); // Red
  hMC_TYPE->SetMarkerColor(4); // Blue
  hData_TYPE_Normalized->SetMarkerStyle(21);
  hData_TYPE_Normalized->SetMarkerColor(5); // Yellow
  hMC_TYPE_Normalized->SetLineColor(1); // Black
  hMC_TYPE_Normalized->SetMarkerColor(6); // Pink
  hWeight_TYPE->SetMarkerColor(7); // Teal
  hWeight_TYPE_Normalized-> SetMarkerColor(9); // Violet
 
  hData_TYPE->GetXaxis()->SetTitle(" Data TYPE ");
  hMC_TYPE->GetXaxis()->SetTitle(" MC TYPE ");
  hData_TYPE->GetYaxis()->SetTitle(" Entries ");
  hMC_TYPE->GetYaxis()->SetTitle(" Entries ");
  hWeight_TYPE->GetYaxis()->SetTitle(" Entries ");
  hWeight_TYPE->GetXaxis()->SetTitle(" Weights TYPE ");

  hData_TYPE_Normalized->GetXaxis()->SetTitle(" Normalized Data TYPE ");
  hMC_TYPE_Normalized->GetXaxis()->SetTitle(" Normalized MC TYPE ");
  hData_TYPE_Normalized->GetYaxis()->SetTitle(" Entries ");
  hMC_TYPE_Normalized->GetYaxis()->SetTitle(" Entries ");
  hWeight_TYPE_Normalized->GetYaxis()->SetTitle(" Entries ");
  hWeight_TYPE_Normalized->GetXaxis()->SetTitle(" Normalized Weights TYPE ");

  TCanvas *c = new TCanvas();
  c->Divide(2,2);
  c->cd(1);
  hData_TYPE->Draw();
  c->cd(2);
  hMC_TYPE->Draw();
  c->cd(3);
//  hMC_TYPE->Draw();
  hData_TYPE->Draw("pe");
  hMC_TYPE->Draw("same");
  c->cd(4);
  hWeight_TYPE->Draw();
  c->Update();
  c->SaveAs("WeightingFactors_TYPE.png");

  TCanvas *ca = new TCanvas();
  ca->Divide(2,2);
  ca->cd(1);
  hData_TYPE_Normalized->Draw("pe");
  ca->cd(2);
  hMC_TYPE_Normalized->Draw("pe");
  ca->cd(3);
//  hMC_TYPE_Normalized->Draw("pe");
  hData_TYPE_Normalized->Draw("pe");
  hMC_TYPE_Normalized->Draw("same");
  ca->cd(4);
  hWeight_TYPE_Normalized->Draw("pe");
  ca->Update();
  ca->SaveAs("WeightingFactors_TYPE_Normalized.png");

  TBranch *newBranch_weights = MCTree->Branch("weight_TYPE", &weight_TYPE, "weight_TYPE/F");
  TBranch *newBranch_weightedMC = MCTree->Branch("weighted_TYPE", &weighted_TYPE, "weighted_TYPE/F");

  for(size_t nEvent=0; nEvent<nMC; ++nEvent){
    MCTree->GetEntry(nEvent);
    weight_TYPE = hWeight_TYPE_Normalized->GetBinContent(hWeight_TYPE_Normalized->FindBin(MC_TYPE));
    hWeightedMC_TYPE->Fill(MC_TYPE,weight_TYPE*normMC);
    weighted_TYPE = hWeightedMC_TYPE->GetBinContent(hWeightedMC_TYPE->FindBin(MC_TYPE)); 
    newBranch_weights->Fill();
    newBranch_weightedMC->Fill();
  }

  hWeightedMC_TYPE->SetLineColor(8); // Green
  hWeightedMC_TYPE->SetLineWidth(2);
  hWeightedMC_TYPE->GetXaxis()->SetTitle(" Weighted MC TYPE "); // With normalized weights
  hWeightedMC_TYPE->GetYaxis()->SetTitle(" Entries ");

  TCanvas *cc = new TCanvas();
  cc->Divide(1,2);
  cc->cd(1);
  hMC_TYPE_Normalized->Draw("pe");
  cc->cd(2);
  hWeightedMC_TYPE->Draw("pe");
  cc->Update();
  cc->SaveAs("WeightedMC_TYPE.png");

  inputMC->Write("", TObject::kOverwrite);

}
