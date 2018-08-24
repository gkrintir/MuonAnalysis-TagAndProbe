void isocut() {
   TFile *f = TFile::Open("MCnew.root");
   TTree *tr = (TTree*) f->Get("tpTree/fitter_tree");

   float mass, pt, eta, relPFiso, tkIso;
   int TightId;
   tr->SetBranchStatus("*",0);
   tr->SetBranchStatus("mass",1); tr->SetBranchAddress("mass",&mass);
   tr->SetBranchStatus("pt",1); tr->SetBranchAddress("pt",&pt);
   tr->SetBranchStatus("eta",1); tr->SetBranchAddress("eta",&eta);
   tr->SetBranchStatus("combRelIsoPF03",1); tr->SetBranchAddress("combRelIsoPF03",&relPFiso);
   tr->SetBranchStatus("tkIso",1); tr->SetBranchAddress("tkIso",&tkIso);
   tr->SetBranchStatus("TightId",1); tr->SetBranchAddress("TightId",&TightId);

   // 4 abseta ranges: 0-2.4 0-1.2 1.2-2.1 2.1-2.4
   // 40 bins 0--100 GeV (2 first bins empty)
   TH1F *hpfiso_00_24[40];
   TH1F *hpfiso_00_12[40];
   TH1F *hpfiso_12_21[40];
   TH1F *hpfiso_21_24[40];
   TH1F *htkiso_00_24[40];
   TH1F *htkiso_00_12[40];
   TH1F *htkiso_12_21[40];
   TH1F *htkiso_21_24[40];

   for (int i=0; i<40; i++) {
      htkiso_00_24[i] = new TH1F(Form("h_tkiso_pt_%d_%d_eta_00_24",25*i,25*(i+1)),"h_tkiso",2000,0,20);
      htkiso_00_12[i] = new TH1F(Form("h_tkiso_pt_%d_%d_eta_00_12",25*i,25*(i+1)),"h_tkiso",2000,0,20);
      htkiso_12_21[i] = new TH1F(Form("h_tkiso_pt_%d_%d_eta_12_21",25*i,25*(i+1)),"h_tkiso",2000,0,20);
      htkiso_21_24[i] = new TH1F(Form("h_tkiso_pt_%d_%d_eta_21_24",25*i,25*(i+1)),"h_tkiso",2000,0,20);
      hpfiso_00_24[i] = new TH1F(Form("h_pfiso_pt_%d_%d_eta_00_24",25*i,25*(i+1)),"h_pfiso",2000,0,20);
      hpfiso_00_12[i] = new TH1F(Form("h_pfiso_pt_%d_%d_eta_00_12",25*i,25*(i+1)),"h_pfiso",2000,0,20);
      hpfiso_12_21[i] = new TH1F(Form("h_pfiso_pt_%d_%d_eta_12_21",25*i,25*(i+1)),"h_pfiso",2000,0,20);
      hpfiso_21_24[i] = new TH1F(Form("h_pfiso_pt_%d_%d_eta_21_24",25*i,25*(i+1)),"h_pfiso",2000,0,20);
   }

   int n = tr->GetEntries();
   cout << n << endl;
   for (int i=0; i<n; i++) {
   // for (int i=0; i<10; i++) {
      tr->GetEntry(i);
      // cout << TightId << " " << mass << " " << pt << " " << eta << " " << relPFiso << " " << tkIso << " " << endl;
      if (TightId==0) continue;
      if (mass<70||mass>110) continue;
      if (pt<5) continue;
      int ibin = min((int) (pt/2.5),39);
      if (fabs(eta)<2.4) {
         hpfiso_00_24[ibin]->Fill(relPFiso);
         htkiso_00_24[ibin]->Fill(tkIso);
      } 
      if (fabs(eta)<1.2) {
         hpfiso_00_12[ibin]->Fill(relPFiso);
         htkiso_00_12[ibin]->Fill(tkIso);
      } else if (fabs(eta)<2.1) {
         hpfiso_12_21[ibin]->Fill(relPFiso);
         htkiso_12_21[ibin]->Fill(tkIso);
      } else if (fabs(eta)<2.4) {
         hpfiso_21_24[ibin]->Fill(relPFiso);
         htkiso_21_24[ibin]->Fill(tkIso);
      }
   }

   // quantiles
   double xq[5] = {0.98, 0.985, 0.99, 0.995, 0.999};
   double yq[5];


   double ptbins[38]; for (int i=0; i<38; i++) ptbins[i] = (i+2)*2.5;
   double tkisocut_00_24[5][38];
   double tkisocut_00_12[5][38];
   double tkisocut_12_21[5][38];
   double tkisocut_21_24[5][38];
   double pfisocut_00_24[5][38];
   double pfisocut_00_12[5][38];
   double pfisocut_12_21[5][38];
   double pfisocut_21_24[5][38];

   for (int i=0; i<38; i++) {
      htkiso_00_24[i+2]->GetQuantiles(5,yq,xq);
      for (int j=0; j<5; j++) tkisocut_00_24[j][i] = yq[j];
      htkiso_00_12[i+2]->GetQuantiles(5,yq,xq);
      for (int j=0; j<5; j++) tkisocut_00_12[j][i] = yq[j];
      htkiso_12_21[i+2]->GetQuantiles(5,yq,xq);
      for (int j=0; j<5; j++) tkisocut_12_21[j][i] = yq[j];
      htkiso_21_24[i+2]->GetQuantiles(5,yq,xq);
      for (int j=0; j<5; j++) tkisocut_21_24[j][i] = yq[j];
      hpfiso_00_24[i+2]->GetQuantiles(5,yq,xq);
      for (int j=0; j<5; j++) pfisocut_00_24[j][i] = yq[j];
      hpfiso_00_12[i+2]->GetQuantiles(5,yq,xq);
      for (int j=0; j<5; j++) pfisocut_00_12[j][i] = yq[j];
      hpfiso_12_21[i+2]->GetQuantiles(5,yq,xq);
      for (int j=0; j<5; j++) pfisocut_12_21[j][i] = yq[j];
      hpfiso_21_24[i+2]->GetQuantiles(5,yq,xq);
      for (int j=0; j<5; j++) pfisocut_21_24[j][i] = yq[j];
   }

   TCanvas *c1 = new TCanvas("c1","c1",800,600);
   TH1F *haxes = new TH1F("h","h",1,0,100);
   haxes->Draw();
   haxes->GetXaxis()->SetTitle("p_{T} (GeV)");
   haxes->GetYaxis()->SetTitle("iso cut");
   haxes->GetYaxis()->SetRangeUser(0,10);
   
   TGraph *g[5];
   for (int i=0; i<5; i++) {
      g[i] = new TGraph(38,ptbins,tkisocut_00_24[i]);
      g[i]->SetLineColor(kRed+i);
   }
   haxes->Draw();
   for (int i=0; i<5; i++) g[i]->Draw("L");
   TLegend *tleg = new TLegend(0.6,0.6,1,1);
   tleg->SetBorderSize(0);
   tleg->SetHeader("tk iso, 0<|#eta|<2.4");
   tleg->AddEntry(g[0],"98% eff","L");
   tleg->AddEntry(g[1],"98.5% eff","L");
   tleg->AddEntry(g[2],"99% eff","L");
   tleg->AddEntry(g[3],"99.5% eff","L");
   tleg->AddEntry(g[4],"99.9% eff","L");
   tleg->Draw();
   c1->SaveAs("tkiso_00_24.pdf");
   c1->SaveAs("tkiso_00_24.root");

   for (int i=0; i<5; i++) {
      g[i] = new TGraph(38,ptbins,tkisocut_00_12[i]);
      g[i]->SetLineColor(kRed+i);
   }
   haxes->Draw();
   for (int i=0; i<5; i++) g[i]->Draw("L");
   tleg->SetHeader("tk iso, 0<|#eta|<1.2");
   tleg->Draw();
   c1->SaveAs("tkiso_00_12.pdf");
   c1->SaveAs("tkiso_00_12.root");

   for (int i=0; i<5; i++) {
      g[i] = new TGraph(38,ptbins,tkisocut_12_21[i]);
      g[i]->SetLineColor(kRed+i);
   }
   haxes->Draw();
   for (int i=0; i<5; i++) g[i]->Draw("L");
   tleg->SetHeader("tk iso, 1.2<|#eta|<2.1");
   tleg->Draw();
   c1->SaveAs("tkiso_12_21.pdf");
   c1->SaveAs("tkiso_12_21.root");

   for (int i=0; i<5; i++) {
      g[i] = new TGraph(38,ptbins,tkisocut_21_24[i]);
      g[i]->SetLineColor(kRed+i);
   }
   haxes->Draw();
   for (int i=0; i<5; i++) g[i]->Draw("L");
   tleg->SetHeader("tk iso, 2.1<|#eta|<2.4");
   tleg->Draw();
   c1->SaveAs("tkiso_21_24.pdf");
   c1->SaveAs("tkiso_21_24.root");

   for (int i=0; i<5; i++) {
      g[i] = new TGraph(38,ptbins,pfisocut_00_24[i]);
      g[i]->SetLineColor(kRed+i);
   }
   haxes->Draw();
   for (int i=0; i<5; i++) g[i]->Draw("L");
   tleg->SetHeader("PF iso, 0<|#eta|<2.4");
   tleg->Draw();
   c1->SaveAs("pfiso_00_24.pdf");
   c1->SaveAs("pfiso_00_24.root");

   for (int i=0; i<5; i++) {
      g[i] = new TGraph(38,ptbins,pfisocut_00_12[i]);
      g[i]->SetLineColor(kRed+i);
   }
   haxes->Draw();
   for (int i=0; i<5; i++) g[i]->Draw("L");
   tleg->SetHeader("PF iso, 0<|#eta|<1.2");
   tleg->Draw();
   c1->SaveAs("pfiso_00_12.pdf");
   c1->SaveAs("pfiso_00_12.root");

   for (int i=0; i<5; i++) {
      g[i] = new TGraph(38,ptbins,pfisocut_12_21[i]);
      g[i]->SetLineColor(kRed+i);
   }
   haxes->Draw();
   for (int i=0; i<5; i++) g[i]->Draw("L");
   tleg->SetHeader("PF iso, 1.2<|#eta|<2.1");
   tleg->Draw();
   c1->SaveAs("pfiso_12_21.pdf");
   c1->SaveAs("pfiso_12_21.root");

   for (int i=0; i<5; i++) {
      g[i] = new TGraph(38,ptbins,pfisocut_21_24[i]);
      g[i]->SetLineColor(kRed+i);
   }
   haxes->Draw();
   for (int i=0; i<5; i++) g[i]->Draw("L");
   tleg->SetHeader("PF iso, 2.1<|#eta|<2.4");
   tleg->Draw();
   c1->SaveAs("pfiso_21_24.pdf");
   c1->SaveAs("pfiso_21_24.root");
}
