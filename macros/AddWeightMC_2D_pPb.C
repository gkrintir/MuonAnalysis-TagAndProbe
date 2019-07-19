
void AddWeightMC_2D_pPb() {

  //input files

  //pPb
  TFile *inputData = TFile::Open("/eos/cms/store/group/phys_heavyions/okukral/TagAndProbe2016/LowPt/tnpJPsi_Data_pPb-merged.root");
  //TFile *inputMC   = TFile::Open("tnpJPsi_MC_pPb_noWeight.root","update");
  TFile *inputMC   = TFile::Open("tnpJPsi_MC_pPb-Skimmed.root","update");

  //binning x=pt, y=eta
  Double_t xbins[47] = {0, 0.5, 1, 1.5, 2, 2.5, 3, 3.5, 4, 4.5, 5, 5.5, 6, 6.5, 7, 7.5, 8, 8.5, 9, 9.5, 10, 10.5, 11, 11.5, 12, 12.5, 13, 13.5, 14, 14.5, 15, 15.5, 16, 16.5, 17, 17.5, 18, 18.5, 19, 19.5, 20, 22.5, 25, 27.5, 30, 35, 40};
  const int nbinsx = sizeof(xbins)/sizeof(Double_t)-1;
  cout << "nbinsx = " << nbinsx << endl;

  Int_t nbinsy = 24;
  Double_t ylow = -2.4;
  Double_t yup = 2.4;

  //Use soft muons to get weights.
  TString cut = "SoftID==1";

  //DATA
  cout << "Loading data" << endl;
  TTree* DataTree = (TTree*)inputData->Get("tpTree/fitter_tree");

  TH2D* hData = new TH2D("hData","hData",nbinsx, xbins, nbinsy, ylow, yup);
  hData->Sumw2();
  hData->GetXaxis()->SetTitle("p_T");
  hData->GetYaxis()->SetTitle("eta");
  hData->SetTitle("pT, eta dist in Data");

  TCanvas* cData = new TCanvas("cData","cData",50,50,400,400);
  cData->cd();
  cout << "Plotting data distribution" << endl;
  DataTree->Draw("eta:pt>>hData",cut.Data(),"colz");

  cout << "Saving plots" << endl;
  cData->SaveAs("Data_2D.png");
  cData->SaveAs("Data_2D.pdf");

  //MC
  cout << "Loading MC" << endl;
  TTree* MCTree = (TTree*)inputMC->Get("tpTree/fitter_tree");

  TH2D* hMC = new TH2D("hMC","hMC",nbinsx, xbins, nbinsy, ylow, yup);
  hMC->Sumw2();
  hMC->GetXaxis()->SetTitle("p_T");
  hMC->GetYaxis()->SetTitle("eta");
  hMC->SetTitle("pT, eta dist in MC");

  TCanvas* cMC = new TCanvas("cMC","cMC",450,50,400,400);
  cMC->cd();
  cout << "Plotting MC distribution" << endl;
  MCTree->Draw("eta:pt>>hMC",cut.Data(),"colz");

  cout << "Saving plots" << endl;
  cMC->SaveAs("MC_2D.png");
  cMC->SaveAs("MC_2D.pdf");

  //Weight
  cout << "Calculating 2D weights" << endl;
  TH2F* hWeight = (TH2F*)hData->Clone();
  hWeight->Sumw2();
  hWeight->Divide(hMC);
  long nDataSoft = hData->GetEntries();
  cout << " Nentries Data (SoftID): " << nDataSoft << endl;
  long nMCSoft = hMC->GetEntries();
  cout << " Nentries MC (SoftID): " << nMCSoft << endl;
  double scalefactor = ((double)nMCSoft)/((double)nDataSoft);
  hWeight->Scale(scalefactor);
  hWeight->GetXaxis()->SetTitle("p_T");
  hWeight->GetYaxis()->SetTitle("eta");
  hWeight->SetTitle("pT, eta dist of Data/MC");
  hWeight->SetName("hWeight");

  TCanvas* cWeight = new TCanvas("cWeight","cWeight",850,50,400,400);
  cWeight->cd();
  cout << "Plotting weights distribution" << endl;
  hWeight->Draw("colz");

  cout << "Saving plots" << endl;
  cWeight->SaveAs("Weights_2D.png");
  cWeight->SaveAs("Weights_2D.pdf");

  //Weighted MC
  cout << "Weighting MC Histogram" << endl;
  TH2D* hWMC = (TH2D*)hMC->Clone();
  hWMC->SetName("hWMC");
  hWMC->Sumw2();
  hWMC->Multiply(hWeight);
  hWMC->GetXaxis()->SetTitle("p_T");
  hWMC->GetYaxis()->SetTitle("eta");
  hWMC->SetTitle("pT, eta dist of Weighted MC");

  TCanvas* cWMC = new TCanvas("cWMC","cWMC",50,450,400,400);
  cWMC->cd();
  cout << "Plotting weighted MC distribution" << endl;
  hWMC->Draw("colz");

  cout << "Saving plots" << endl;
  cWMC->SaveAs("WeightedMC_2D.png");
  cWMC->SaveAs("WeightedMC_2D.pdf");

  //RD over weighted MC
  cout << "Dividing Data by weighted MC" << endl;
  TH2D* hDiv = (TH2D*)hData->Clone();
  hDiv->Sumw2();
  hDiv->Divide(hWMC);
  hDiv->Scale(scalefactor);
  hDiv->GetXaxis()->SetTitle("p_T");
  hDiv->GetYaxis()->SetTitle("eta");
  hDiv->SetTitle("pT, eta dist of Data/WeightedMC");
  hDiv->SetName("hDiv");

  //find average of data/mc subtract 1. Perfect weights should now be zero.
  float avgVal = 0.0;
  for (int i=1; i<nbinsx+1; i++) {
    for (int j=1; j<nbinsy+1; j++) {
		if (hDiv->GetBinContent(i, j) == 0) { continue; } //skip empty bins
		avgVal = avgVal + hDiv->GetBinContent(i,j);
		hDiv->SetBinContent(i,j,hDiv->GetBinContent(i,j)-1.0);
    }
  }
  avgVal = avgVal/(nbinsx*nbinsy);
  cout << "avgVal (should be somewhat close to 1) = " << avgVal << endl;

  TCanvas* cDiv = new TCanvas("cDiv","cDiv",850,450,400,400);
  cDiv->cd();
  cout << "Plotting weights distribution" << endl;
  hDiv->Draw("colz");

  cout << "Saving plots" << endl;
  cDiv->SaveAs("DataOverMCMinusOne_2D.png");
  cDiv->SaveAs("DataOverMCMinusOne_2D.pdf");

  //Reweighting MC Tree
  Float_t MC_eta;
  Float_t MC_pt;
  Float_t weight;
  Float_t weighted_eta;
  Float_t weighted_pt;
  MCTree->SetBranchAddress("eta",&MC_eta);
  MCTree->SetBranchAddress("pt",&MC_pt);
  TBranch *newBranch_weight = MCTree->Branch("weight", &weight, "weight/F");
  //TBranch *newBranch_weighted_eta = MCTree->Branch("weighted_eta", &weighted_eta, "weighted_eta/F"); // O: this is nonsense, so I commented it out
  //TBranch *newBranch_weighted_pt = MCTree->Branch("weighted_pt", &weighted_pt, "weighted_pt/F");

  TH1F* hWeightedMC_eta = new TH1F("hWeightedMC_eta","hWeightedMC_eta",nbinsy,ylow,yup);
  TH1F* hWeightedMC_pt = new TH1F("hWeightedMC_pt","hWeightedMC_pt",nbinsx,xbins);

  cout << "Reweighting MC Tree" << endl;
  Int_t nMC = MCTree->GetEntries();
  for(size_t nEvent=0; nEvent<nMC; ++nEvent){
    if(nEvent%100000==0) cout << ">>>>> EVENT " << nEvent << " / " << nMC <<  " ("<<(int)(100.*nEvent/nMC) << "%)" << endl;
    MCTree->GetEntry(nEvent);

    Int_t ptbin = hWeight->GetXaxis()->FindBin(MC_pt);
    Int_t etabin = hWeight->GetYaxis()->FindBin(MC_eta);

    weight = hWeight->GetBinContent(ptbin,etabin);


    hWeightedMC_eta->Fill(MC_eta,weight); 
   // weighted_eta = MC_eta*weight;  //O: you cannot weight like this

    hWeightedMC_pt->Fill(MC_pt,weight);
  //  weighted_pt = MC_pt*weight;

    newBranch_weight->Fill();
   // newBranch_weighted_eta->Fill();
   // newBranch_weighted_pt->Fill();
  }

  //Write changes to MC file
  cout << "Writing to File" << endl;
  inputMC->Write("", TObject::kOverwrite);

  //Save histograms.
  TFile* histfile2d = new TFile("histfile2d.root","RECREATE");
  hData->Write();
  hMC->Write();
  hWeight->Write();
  hWMC->Write();
  hDiv->Write();
  hWeightedMC_eta->Write();
  hWeightedMC_pt->Write();
  histfile2d->Close();
  delete histfile2d;

  inputMC->Close();
  inputData->Close();
  delete inputMC;
  delete inputData;

}
