void CopyDir(TDirectory *source, const char* newname);

void reorganise_tnp(const char* filename, const char* output="out.root") {
   TFile *fin = TFile::Open(filename);
   TFile *fout = TFile::Open(output,"RECREATE");
   if (!fin->IsOpen() || !fout->IsOpen()) return;


   // let's do everything by hand, at least for now
   fout->cd();
   TDirectory *topdir = fout->mkdir("tpTree");

   ////////////////////////////////////////////////
   // 1bin
   topdir->cd();
   TDirectoryFile *torig = (TDirectoryFile*) fin->Get("tpTree/Iso_abseta_0_24_pt_7_200");
   if (!torig) cerr << "ERROR! missing tpTree/Iso_abseta_0_24_pt_7_200" << endl;
   else {
      topdir->cd();
      CopyDir(torig,"Iso_1bin");
   }

   ////////////////////////////////////////////////
   // abseta00_12
   double ael = 0;
   double aeh = 1.2;
   double ptl[14] = {7  ,12 ,15, 20 ,25 ,30 ,35 ,40 ,45 ,50, 60, 70 ,80 ,100 };
   double pth[14] = {12 ,15, 20 ,25 ,30 ,35 ,40 ,45 ,50, 60, 70 ,80 ,100,200};

   // first bin
   torig = (TDirectoryFile*) fin->Get("tpTree/Iso_abseta_0_12_pt_7_12");
   topdir->cd();
   CopyDir(torig,"Iso_abseta00_12");

   // now add other bins
   TDirectoryFile *topdir2 = (TDirectoryFile*) fout->Get("tpTree/Iso_abseta00_12");
   // prepare the combined RooDataSet with all effs in
   RooDataSet *ds = (RooDataSet*) topdir2->Get("fit_eff");
   RooDataSet *dsc = (RooDataSet*) topdir2->Get("cnt_eff");

   for (int i=1; i<14; i++) {
      // take care of the plots and fit results
      torig = (TDirectoryFile*) fin->Get(Form("tpTree/Iso_abseta_%.0f_%.0f_pt_%.0f_%.0f/abseta_bin0__pt_bin0__TightId_true__templates_abseta_%.0f_%.0f_pt_%.0f_%.0f",ael*10.,aeh*10.,ptl[i],pth[i],ael*10.,aeh*10.,ptl[i],pth[i]));
      TString tname = torig->GetName();
      tname.ReplaceAll("bin0",Form("bin%d",i));
      topdir2->cd();
      CopyDir(torig,tname);

      // now the RooDataSets
      RooDataSet *dsnew = (RooDataSet*) fin->Get(Form("tpTree/Iso_abseta_%.0f_%.0f_pt_%.0f_%.0f/fit_eff",ael*10.,aeh*10.,ptl[i],pth[i]));
      ds->append(*dsnew);
      dsnew = (RooDataSet*) fin->Get(Form("tpTree/Iso_abseta_%.0f_%.0f_pt_%.0f_%.0f/cnt_eff",ael*10.,aeh*10.,ptl[i],pth[i]));
      dsc->append(*dsnew);
   }
   topdir2->Delete("fit_eff;*");
   topdir2->WriteTObject(ds);
   topdir2->Delete("cnt_eff;*");
   topdir2->WriteTObject(dsc);


   ////////////////////////////////////////////////
   // abseta12_21
   ael = 1.2;
   aeh = 2.1;

   // first bin
   torig = (TDirectoryFile*) fin->Get("tpTree/Iso_abseta_12_21_pt_7_12");
   topdir->cd();
   CopyDir(torig,"Iso_abseta12_21");

   // now add other bins
   topdir2 = (TDirectoryFile*) fout->Get("tpTree/Iso_abseta12_21");
   // prepare the combined RooDataSet with all effs in
   ds = (RooDataSet*) topdir2->Get("fit_eff");
   dsc = (RooDataSet*) topdir2->Get("cnt_eff");

   for (int i=1; i<14; i++) {
      // take care of the plots and fit results
      torig = (TDirectoryFile*) fin->Get(Form("tpTree/Iso_abseta_%.0f_%.0f_pt_%.0f_%.0f/abseta_bin0__pt_bin0__TightId_true__templates_abseta_%.0f_%.0f_pt_%.0f_%.0f",ael*10.,aeh*10.,ptl[i],pth[i],ael*10.,aeh*10.,ptl[i],pth[i]));
      TString tname = torig->GetName();
      tname.ReplaceAll("bin0",Form("bin%d",i));
      topdir2->cd();
      CopyDir(torig,tname);

      // now the RooDataSets
      RooDataSet *dsnew = (RooDataSet*) fin->Get(Form("tpTree/Iso_abseta_%.0f_%.0f_pt_%.0f_%.0f/fit_eff",ael*10.,aeh*10.,ptl[i],pth[i]));
      ds->append(*dsnew);
      dsnew = (RooDataSet*) fin->Get(Form("tpTree/Iso_abseta_%.0f_%.0f_pt_%.0f_%.0f/cnt_eff",ael*10.,aeh*10.,ptl[i],pth[i]));
      dsc->append(*dsnew);
   }
   topdir2->Delete("fit_eff;*");
   topdir2->WriteTObject(ds);
   topdir2->Delete("cnt_eff;*");
   topdir2->WriteTObject(dsc);

   ////////////////////////////////////////////////
   // abseta21_24
   ael = 2.1;
   aeh = 2.4;
   double ptl2[6] = {7  ,12 ,15 ,25 ,40 ,80};
   double pth2[6] = {12 ,15 ,25 ,40 ,80 ,200};

   // first bin
   torig = (TDirectoryFile*) fin->Get("tpTree/Iso_abseta_21_24_pt_7_12");
   topdir->cd();
   CopyDir(torig,"Iso_abseta21_24");

   // now add other bins
   topdir2 = (TDirectoryFile*) fout->Get("tpTree/Iso_abseta21_24");
   // prepare the combined RooDataSet with all effs in
   ds = (RooDataSet*) topdir2->Get("fit_eff");
   dsc = (RooDataSet*) topdir2->Get("cnt_eff");

   for (int i=1; i<6; i++) {
      // take care of the plots and fit results
      torig = (TDirectoryFile*) fin->Get(Form("tpTree/Iso_abseta_%.0f_%.0f_pt_%.0f_%.0f/abseta_bin0__pt_bin0__TightId_true__templates_abseta_%.0f_%.0f_pt_%.0f_%.0f",ael*10.,aeh*10.,ptl2[i],pth2[i],ael*10.,aeh*10.,ptl2[i],pth2[i]));
      TString tname = torig->GetName();
      tname.ReplaceAll("bin0",Form("bin%d",i));
      topdir2->cd();
      CopyDir(torig,tname);

      // now the RooDataSets
      RooDataSet *dsnew = (RooDataSet*) fin->Get(Form("tpTree/Iso_abseta_%.0f_%.0f_pt_%.0f_%.0f/fit_eff",ael*10.,aeh*10.,ptl2[i],pth2[i]));
      ds->append(*dsnew);
      dsnew = (RooDataSet*) fin->Get(Form("tpTree/Iso_abseta_%.0f_%.0f_pt_%.0f_%.0f/cnt_eff",ael*10.,aeh*10.,ptl2[i],pth2[i]));
      dsc->append(*dsnew);
   }
   topdir2->Delete("fit_eff;*");
   topdir2->WriteTObject(ds);
   topdir2->Delete("cnt_eff;*");
   topdir2->WriteTObject(dsc);

   ////////////////////////////////////////////////
   // absetadep
   double ael3[3] = {0, 1.2, 2.1};
   double aeh3[3] = {1.2, 2.1, 2.4};
   double ptl3 = 7;
   double pth3 = 200;

   // first bin
   torig = (TDirectoryFile*) fin->Get("tpTree/Iso_abseta_0_12_pt_7_200");
   topdir->cd();
   CopyDir(torig,"Iso_absetadep");

   // now add other bins
   topdir2 = (TDirectoryFile*) fout->Get("tpTree/Iso_absetadep");
   // prepare the combined RooDataSet with all effs in
   ds = (RooDataSet*) topdir2->Get("fit_eff");
   dsc = (RooDataSet*) topdir2->Get("cnt_eff");

   for (int i=1; i<3; i++) {
      // take care of the plots and fit results
      torig = (TDirectoryFile*) fin->Get(Form("tpTree/Iso_abseta_%.0f_%.0f_pt_%.0f_%.0f/abseta_bin0__pt_bin0__TightId_true__templates_abseta_%.0f_%.0f_pt_%.0f_%.0f",ael3[i]*10.,aeh3[i]*10.,ptl3,pth3,ael3[i]*10.,aeh3[i]*10.,ptl3,pth3));
      TString tname = torig->GetName();
      tname.ReplaceAll("bin0",Form("bin%d",i));
      topdir2->cd();
      CopyDir(torig,tname);

      // now the RooDataSets
      RooDataSet *dsnew = (RooDataSet*) fin->Get(Form("tpTree/Iso_abseta_%.0f_%.0f_pt_%.0f_%.0f/fit_eff",ael3[i]*10.,aeh3[i]*10.,ptl3,pth3));
      ds->append(*dsnew);
      dsnew = (RooDataSet*) fin->Get(Form("tpTree/Iso_abseta_%.0f_%.0f_pt_%.0f_%.0f/cnt_eff",ael3[i]*10.,aeh3[i]*10.,ptl3,pth3));
      dsc->append(*dsnew);
   }
   topdir2->Delete("fit_eff;*");
   topdir2->WriteTObject(ds);
   topdir2->Delete("cnt_eff;*");
   topdir2->WriteTObject(dsc);

   ////////////////////////////////////////////////
   // etadep
   double ael4[14] = {-2.4,-2.1,-1.6,-1.2,-0.9,-0.6,-0.3,0,0.3,0.6,0.9,1.2,1.6,2.1};
   double aeh4[14] = {-2.1,-1.6,-1.2,-0.9,-0.6,-0.3,0,0.3,0.6,0.9,1.2,1.6,2.1,2.4};
   double ptl4 = 7;
   double pth4 = 200;

   // first bin
   torig = (TDirectoryFile*) fin->Get("tpTree/Iso_eta_m24_m21_pt_7_200");
   topdir->cd();
   CopyDir(torig,"Iso_etadep");

   // now add other bins
   topdir2 = (TDirectoryFile*) fout->Get("tpTree/Iso_etadep");
   // prepare the combined RooDataSet with all effs in
   ds = (RooDataSet*) topdir2->Get("fit_eff");
   dsc = (RooDataSet*) topdir2->Get("cnt_eff");

   for (int i=1; i<14; i++) {
      // take care of the plots and fit results
      TString tagname = Form("eta_%.0f_%.0f_pt_%.0f_%.0f",ael4[i]*10.,aeh4[i]*10.,ptl4,pth4);
      tagname.ReplaceAll("-","m");
      tagname.ReplaceAll("m3_0","m3_m0");
      TString tagname2;
      if (i<7) tagname2 = Form("abseta_%.0f_%.0f_pt_%.0f_%.0f",-aeh4[i]*10.,-ael4[i]*10.,ptl4,pth4);
      else tagname2 = Form("abseta_%.0f_%.0f_pt_%.0f_%.0f",ael4[i]*10.,aeh4[i]*10.,ptl4,pth4);
      tagname2.ReplaceAll("-0","0");
      torig = (TDirectoryFile*) fin->Get(TString("tpTree/Iso_") + tagname + "/eta_bin0__pt_bin0__TightId_true__templates_" + tagname2);
      TString tname = torig->GetName();
      tname.ReplaceAll("bin0",Form("bin%d",i));
      topdir2->cd();
      CopyDir(torig,tname);

      // now the RooDataSets
      RooDataSet *dsnew = (RooDataSet*) fin->Get(TString("tpTree/Iso_") + tagname + "/fit_eff");
      ds->append(*dsnew);
      dsnew = (RooDataSet*) fin->Get(TString("tpTree/Iso_") + tagname + "/cnt_eff");
      dsc->append(*dsnew);
   }
   topdir2->Delete("fit_eff;*");
   topdir2->WriteTObject(ds);
   topdir2->Delete("cnt_eff;*");
   topdir2->WriteTObject(dsc);

   ////////////////////////////////////////////////
   // pt
   double ael5 = 0;
   double aeh5 = 2.4;
   double ptl5[14] = {7  ,12 ,15, 20 ,25 ,30 ,35 ,40 ,45 ,50, 60, 70 ,80 ,100 };
   double pth5[14] = {12 ,15, 20 ,25 ,30 ,35 ,40 ,45 ,50, 60, 70 ,80 ,100,200};

   // first bin
   torig = (TDirectoryFile*) fin->Get("tpTree/Iso_abseta_0_24_pt_7_12");
   topdir->cd();
   CopyDir(torig,"Iso_ptdep");

   // now add other bins
   topdir2 = (TDirectoryFile*) fout->Get("tpTree/Iso_ptdep");
   // prepare the combined RooDataSet with all effs in
   ds = (RooDataSet*) topdir2->Get("fit_eff");
   dsc = (RooDataSet*) topdir2->Get("cnt_eff");

   for (int i=1; i<14; i++) {
      // take care of the plots and fit results
      torig = (TDirectoryFile*) fin->Get(Form("tpTree/Iso_abseta_%.0f_%.0f_pt_%.0f_%.0f/abseta_bin0__pt_bin0__TightId_true__templates_abseta_%.0f_%.0f_pt_%.0f_%.0f",ael5*10.,aeh5*10.,ptl5[i],pth5[i],ael5*10.,aeh5*10.,ptl5[i],pth5[i]));
      TString tname = torig->GetName();
      tname.ReplaceAll("bin0",Form("bin%d",i));
      topdir2->cd();
      CopyDir(torig,tname);

      // now the RooDataSets
      RooDataSet *dsnew = (RooDataSet*) fin->Get(Form("tpTree/Iso_abseta_%.0f_%.0f_pt_%.0f_%.0f/fit_eff",ael5*10.,aeh5*10.,ptl5[i],pth5[i]));
      ds->append(*dsnew);
      dsnew = (RooDataSet*) fin->Get(Form("tpTree/Iso_abseta_%.0f_%.0f_pt_%.0f_%.0f/cnt_eff",ael5*10.,aeh5*10.,ptl5[i],pth5[i]));
      dsc->append(*dsnew);
   }
   topdir2->Delete("fit_eff;*");
   topdir2->WriteTObject(ds);
   topdir2->Delete("cnt_eff;*");
   topdir2->WriteTObject(dsc);

   // ////////////////////////////////////////////////
   // // absetadep
   // double ael6[3] = {0, 1.2, 2.1};
   // double aeh6[3] = {1.2, 2.1, 2.4};
   // double ptl6 = 7;
   // double pth6 = 200;

   // // first bin
   // torig = (TDirectoryFile*) fin->Get("tpTree/Iso_abseta_00_12_pt_7_200");
   // topdir->cd();
   // CopyDir(torig,"Iso_absetadep");

   // // now add other bins
   // topdir2 = (TDirectoryFile*) fout->Get("tpTree/Iso_absetadep");
   // // prepare the combined RooDataSet with all effs in
   // ds = (RooDataSet*) topdir2->Get("fit_eff");
   // dsc = (RooDataSet*) topdir2->Get("cnt_eff");

   // for (int i=1; i<3; i++) {
   //    // take care of the plots and fit results
   //    torig = (TDirectoryFile*) fin->Get(Form("tpTree/Iso_abseta_%.0f_%.0f_pt_%.0f_%.0f/abseta_bin0__pt_bin0__TightId_true__templates_abseta_%.0f_%.0f_pt_%.0f_%.0f",ael6[i],aeh6[i]*10.,ptl6,pth6,ael6[i]*10.,aeh6[i]*10.,ptl6,pth6));
   //    TString tname = torig->GetName();
   //    tname.ReplaceAll("bin0",Form("bin%d",i));
   //    topdir2->cd();
   //    CopyDir(torig,tname);

   //    // now the RooDataSets
   //    RooDataSet *dsnew = (RooDataSet*) fin->Get(Form("tpTree/Iso_abseta_%.0f_%.0f_pt_%.0f_%.0f/fit_eff",ael6[i]*10.,aeh6[i]*10.,ptl6,pth6));
   //    ds->append(*dsnew);
   //    dsnew = (RooDataSet*) fin->Get(Form("tpTree/Iso_abseta_%.0f_%.0f_pt_%.0f_%.0f/cnt_eff",ael6[i]*10.,aeh6[i]*10.,ptl6,pth6));
   //    dsc->append(*dsnew);
   // }
   // topdir2->Delete("fit_eff;*");
   // topdir2->WriteTObject(ds);
   // topdir2->Delete("cnt_eff;*");
   // topdir2->WriteTObject(dsc);

   ////////////////////////////////////////////////
   // centdep
   topdir->cd();
   torig = (TDirectoryFile*) fin->Get("tpTree/Iso_centdep");
   if (!torig) cerr << "ERROR! missing tpTree/Iso_centdep" << endl;
   else {
      topdir->cd();
      CopyDir(torig,"Iso_centdep");
   }

   ////////////////////////////////////////////////
   // centdepHF
   topdir->cd();
   torig = (TDirectoryFile*) fin->Get("tpTree/Iso_centdepHF");
   if (!torig) cerr << "ERROR! missing tpTree/Iso_centdepHF" << endl;
   else {
      topdir->cd();
      CopyDir(torig,"Iso_centdepHF");
   }

   ////////////////////////////////////////////////
   // nPV
   topdir->cd();
   torig = (TDirectoryFile*) fin->Get("tpTree/Iso_nPV");
   if (!torig) cerr << "ERROR! missing tpTree/Iso_nPV" << endl;
   else {
      topdir->cd();
      CopyDir(torig,"Iso_nPV");
   }

   ////////////////////////////////////////////////
   // rundep
   topdir->cd();
   torig = (TDirectoryFile*) fin->Get("tpTree/Iso_rundep");
   if (!torig) cerr << "ERROR! missing tpTree/Iso_rundep" << endl;
   else {
      topdir->cd();
      CopyDir(torig,"Iso_rundep");
   }

   fout->Close();
}

void CopyDir(TDirectory *source, const char* newname="") {
   //copy all objects and subdirs of directory source as a subdir of the current directory
   // source->ls();
   TDirectory *savdir = gDirectory;
   TDirectory *adir = savdir->mkdir(TString(newname)!="" ? newname : source->GetName());
   adir->cd();
   //loop on all entries of this directory
   TKey *key;
   TIter nextkey(source->GetListOfKeys());
   while ((key = (TKey*)nextkey())) {
      const char *classname = key->GetClassName();
      TClass *cl = gROOT->GetClass(classname);
      if (!cl) continue;
      if (cl->InheritsFrom(TDirectory::Class())) {
         source->cd(key->GetName());
         TDirectory *subdir = gDirectory;
         adir->cd();
         CopyDir(subdir);
         adir->cd();
      } else if (cl->InheritsFrom(TTree::Class())) {
         TTree *T = (TTree*)source->Get(key->GetName());
         adir->cd();
         TTree *newT = T->CloneTree(-1,"fast");
         newT->Write();
      } else {
         source->cd();
         TObject *obj = key->ReadObj();
         adir->cd();
         obj->Write();
         delete obj;
     }
  }
  adir->SaveSelf(kTRUE);
  savdir->cd();
}
