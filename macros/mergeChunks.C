//The TnPEff macro gets these things from the file:
//	(RooDataSet*)fData[k]->Get(treeTag + "/" + ptTag[i] + "/fit_eff"));
//      (RooDataSet*)fData[i]->Get(treeTag + "/" + etaTag + "/fit_eff");
//      (RooDataSet*)fData[i]->Get(treeTag + "/" + allTag + "/fit_eff");
//      (RooDataSet*)fData[i]->Get(treeTag + "/" + absetaTag + "/fit_eff");
//      (RooDataSet*)fData[i]->Get(treeTag + "/" + centTag + "/fit_eff");
//So that's all we need to get into the merged file. It would be nice to merge the efficiency plots as well, but not necessary.

void PrintRooDataSet(RooDataSet* rds) {
  int nBins = rds->numEntries();
  cout << "nBins = " << nBins << endl;
  for (int i=0; i<nBins; i++) {
    const RooArgSet *set0 = rds->get(i);
    if (i==0) set0->Print();
    RooRealVar *eta = (RooRealVar*)set0->find("eta");
    RooRealVar *abseta = (RooRealVar*)set0->find("abseta");
    RooRealVar *pt = (RooRealVar*)set0->find("pt");
    RooRealVar *tag_hiNtracks = (RooRealVar*)set0->find("tag_hiNtracks");
    RooRealVar *tag_nVertices = (RooRealVar*)set0->find("tag_nVertices");
    RooRealVar *eff = (RooRealVar*)set0->find("efficiency");
    double efflo = eff->getAsymErrorLo();
    double effhi = eff->getAsymErrorHi();
    cout << "RooArgSet:: = (";
    if (eta != NULL) cout << eta->getVal() << ",";
    if (abseta != NULL) cout << abseta->getVal() << ",";
    if (pt != NULL) cout << pt->getVal() << ",";
    if (tag_hiNtracks != NULL) cout << tag_hiNtracks->getVal() << ",";
    if (tag_nVertices != NULL) cout << tag_nVertices->getVal() << ",";
    if (eff != NULL) cout << eff->getVal() << " + " << effhi << " - " << efflo;
    else cout << "NULL";
    cout << ")" << endl;
  }
}

RooDataSet* mergeDataSets(list<RooDataSet*>dsetList) {

  cout << "Starting mergeDataSets" << endl;

  int nFiles = dsetList.size();
  cout << "nFiles = " << nFiles << endl;

  list<RooDataSet*>::iterator firstrds = dsetList.begin();
  int nBins = (*firstrds)->numEntries();
  cout << "nBins = " << nBins << endl;

  // Sanity check: data sets must have the same size
  for (list<RooDataSet*>::iterator iter = dsetList.begin(); iter != dsetList.end(); ++iter) {
    if (nBins!=(*iter)->numEntries()) {
      cout << "ERROR: datasets have different size" << endl;
    }
  }

  // Load efficiencies from the datasets
  double teff[nFiles][nBins], teffhi[nFiles][nBins], tefflo[nFiles][nBins];
  int fileNum = 0;
  for (list<RooDataSet*>::iterator iter = dsetList.begin(); iter != dsetList.end(); ++iter) {
    //cout << "loading efficiency from file #" << fileNum << endl;
    //cout << "nBins = " << (*iter)->numEntries() << endl;
    const RooArgSet *set = (*iter)->get();
    RooRealVar *eff_tmp = (RooRealVar*)set->find("efficiency");
    for (int i=0; i<nBins; i++) {
      (*iter)->get(i);
      //cout << "File " << fileNum << ", bin " << i << ": eff = " << eff_tmp->getVal() << endl;
      teff[fileNum][i] = eff_tmp->getVal();
      teffhi[fileNum][i] = fabs(eff_tmp->getAsymErrorHi());
      tefflo[fileNum][i] = fabs(eff_tmp->getAsymErrorLo());
    }
    fileNum = fileNum + 1;
  }
  //cout << "Finished loading efficiencies" << endl;

  //It's necessary to get the entries from the first dataset and create an argset before being able to loop through the rest. Maybe there's a prettier way to do this, but it works.
  const RooArgSet *set0 = (*firstrds)->get(0);
  set0->Print();
  RooRealVar *eta = (RooRealVar*)set0->find("eta");
  RooRealVar *abseta = (RooRealVar*)set0->find("abseta");
  RooRealVar *pt = (RooRealVar*)set0->find("pt");
  RooRealVar *tag_hiNtracks = (RooRealVar*)set0->find("tag_hiNtracks");
  RooRealVar *tag_nVertices = (RooRealVar*)set0->find("tag_nVertices");
  RooRealVar *eff = new RooRealVar("efficiency","Efficiency",0,1);
  eff->setAttribute("StoreAsymError");

  //find average efficiency and std. to check for outliers.
  double outlierCutoff = 1.5;//standard deviations.
  double effavg0[nBins];
  double effstd0[nBins];
  double effsumsqrs0[nBins];
  for (int i=0; i<nBins; i++) {
    effavg0[i] = 0;
    effsumsqrs0[i] = 0;
    effstd0[i] = 0;
    for (int k=0; k<nFiles; k++) {
      effavg0[i] = effavg0[i] + teff[k][i];
      effsumsqrs0[i] = effsumsqrs0[i] + pow(teff[k][i],2);
    }
    effavg0[i] = effavg0[i]/nFiles;
    effsumsqrs0[i] = effsumsqrs0[i]/nFiles;
    effstd0[i] = sqrt(effsumsqrs0[i]-effavg0[i]*effavg0[i]);
    //cout << "effavg0 = " << effavg0[i] << " +/- " << effstd0[i] << endl;
    //cout << "effsumsqrs0 = " << effsumsqrs0[i] << endl;
  }
  double effavg[nBins];
  double effstd[nBins];
  double effsumsqrs[nBins];
  for (int i=0; i<nBins; i++) {
    effavg[i] = 0;
    effsumsqrs[i] = 0;
    effstd[i] = 0;
    int numpoints = 0;
    for (int k=0; k<nFiles; k++) {
      if (abs(teff[k][i]-effavg0[i])>outlierCutoff*effstd0[i]) continue;//omit outliers in 2nd run.
      if ((tefflo[k][i]+teffhi[k][i])*10<effstd0[i]) continue;//omit bad fits in 2nd run.
      numpoints = numpoints + 1;
      effavg[i] = effavg[i] + teff[k][i];
      effsumsqrs[i] = effsumsqrs[i] + pow(teff[k][i],2);
    }
    effavg[i] = effavg[i]/numpoints;
    effsumsqrs[i] = effsumsqrs[i]/numpoints;
    effstd[i] = sqrt(effsumsqrs[i]-effavg[i]*effavg[i]);
    //cout << "effavg = " << effavg[i] << " +/- " << effstd[i] << endl;
    //cout << "effsumsqrs = " << effsumsqrs[i] << endl;
  }

  cout << "merging entry #0" << endl;
  double effTot = 0;
  double eyhTot = 0;
  double eylTot = 0;
  int numProbesTot = 0;
  double varWeightTot = 0;
  double eyh = 0;
  double eyl = 0;
  for (int k=0; k<nFiles; k++) {
    double effy = teff[k][0];
    eyh = teffhi[k][0];
    eyl = tefflo[k][0];
    //double varWeight = pow(0.5*(eyh*eyh + eyl*eyl),-1);
    double variance = (eyh*eyh + eyl*eyl)/2 - pow(eyh-eyl,2)/(2*3.14159);
    double varWeight = 1/variance;
    double numProbes = 1;
    cout << "eff" << k << " = " << effy << " + " << eyh << " - " << eyl << "   numProbes = " << numProbes << "; ";
    if (abs(effy-effavg[0])>outlierCutoff*effstd[0]) {
      cout << "outlier!" << endl;
      //continue;
    }
    if ((eyl+eyh)*10<effstd[0]) {
      cout << "bad fit!" << endl;
      //continue;
    }
    else cout << endl;
    effTot = effTot + varWeight*effy;
    eylTot = eylTot + pow(varWeight*eyl,2);
    eyhTot = eyhTot + pow(varWeight*eyh,2);
    numProbesTot = numProbesTot + numProbes;
    varWeightTot = varWeightTot + varWeight;
  }
  effTot = effTot/varWeightTot;
  eylTot = -sqrt(eylTot)/varWeightTot;
  eyhTot = sqrt(eyhTot)/varWeightTot;
  eff->setVal((double)effTot);
  eff->setAsymError((double)eylTot,(double)eyhTot);
  cout << "eff = " << effTot << " + " << eyhTot << " - " << eylTot << "   numProbesTot = " << numProbesTot << endl;
  cout << "effavg = " << effavg[0] << " +/- " << effstd[0] << endl;

  RooArgSet* argSet = new RooArgSet();
  cout << "argSet = ";
  argSet->Print();
  cout << "RooArgSet:: = (";
  if (eta != NULL) {
    argSet->add(*eta);
    cout << eta->getVal() << ",";
  }
  if (abseta != NULL) {
    argSet->add(*abseta);
    cout << abseta->getVal() << ",";
  }
  if (pt != NULL) {
    argSet->add(*pt);
    cout << pt->getVal() << ",";
  }
  if (tag_hiNtracks != NULL) {
    argSet->add(*tag_hiNtracks);
    cout << tag_hiNtracks->getVal() << ",";
  }
  if (tag_nVertices != NULL) {
    argSet->add(*tag_nVertices);
    cout << tag_nVertices->getVal() << ",";
  }
  //if (eff != NULL) {
    argSet->add(*eff);
    cout << eff->getVal() << "";
  //}
  cout << ")" << endl << endl;

  cout << "argSet = ";
  argSet->Print();
  RooDataSet* rds_merged = new RooDataSet("fit_eff","Efficiency from unbinned ML fit",*argSet);
  rds_merged->add(*argSet);

  cout << "nBins = " << rds_merged->numEntries() << " so far." << endl;

  for (int i=1; i<nBins; i++) {
    cout << "merging entry #" << i << endl;
    (*firstrds)->get(i);//gets the ith entry in the dataset. The RooRealVars are automatically updated to the i-th entry.
    effTot = 0;
    eylTot = 0;
    eyhTot = 0;
    numProbesTot = 0;
    varWeightTot = 0;
    eyh = 0;
    eyl = 0;
    for (int k=0; k<nFiles; k++) {
      double effy = teff[k][i];
      eyh = teffhi[k][i];
      eyl = tefflo[k][i];
      double numProbes = 1;
      //double varWeight = pow(0.5*(eyh*eyh + eyl*eyl),-1);
      double variance = (eyh*eyh + eyl*eyl)/2 - pow(eyh-eyl,2)/(2*3.14159);
      double varWeight = 1/variance;
      cout << "eff" << k << " = " << effy << " + " << eyh << " - " << eyl << "   numProbes = " << numProbes << "; ";
      if (abs(effy-effavg[i])>outlierCutoff*effstd[i] && effstd[i]>0) {
        cout << "outlier!" << endl;
        //continue;
      }
      if ((eyl+eyh)*10<effstd[i]) {
        cout << "bad fit!" << endl;
        //continue;
      }
      else cout << endl;
      effTot = effTot + varWeight*effy;
      eylTot = eylTot + pow(varWeight*eyl,2);
      eyhTot = eyhTot + pow(varWeight*eyh,2);
      numProbesTot = numProbesTot + numProbes;
      varWeightTot = varWeightTot + varWeight;
    }
    effTot = effTot/varWeightTot;
    eylTot = -sqrt(eylTot)/varWeightTot;
    eyhTot = sqrt(eyhTot)/varWeightTot;
    eff->setVal((double)effTot);
    eff->setAsymError((double)eylTot,(double)eyhTot);
    cout << "eff = " << eff->getVal() << " + " << eyhTot << " - " << eylTot << "   numProbesTot = " << numProbesTot << endl;
    cout << "effavg = " << effavg[i] << " +/- " << effstd[i] << endl;

    cout << "RooArgSet:: = (";
    if (eta != NULL) {
      argSet->add(*eta);
      cout << eta->getVal() << ",";
    }
    if (abseta != NULL) {
      argSet->add(*abseta);
      cout << abseta->getVal() << ",";
    }
    if (pt != NULL) {
      argSet->add(*pt);
      cout << pt->getVal() << ",";
    }
    if (tag_hiNtracks != NULL) {
      argSet->add(*tag_hiNtracks);
      cout << tag_hiNtracks->getVal() << ",";
    }
    if (tag_nVertices != NULL) {
      argSet->add(*tag_nVertices);
      cout << tag_nVertices->getVal() << ",";
    }
    //if (eff != NULL) {
      argSet->add(*eff);
      cout << eff->getVal() << "";
      cout << " + " << fabs(eff->getAsymErrorHi()) << " - " << fabs(eff->getAsymErrorLo());
    //}
    cout << ")" << endl << endl;

    rds_merged->add(*argSet);

    cout << "nBins = " << rds_merged->numEntries() << " so far." << endl;
  }

  return rds_merged;

}


// ********************** MAIN ****************************** //
void mergeChunks(TString inDirectory="Fits_to_merge", TString outDirectory="Fits_merged", TString whichFunc="DCBPassFailPol3", TString todaysDate="2020_02_22"){

  cout << "Initializing" << endl;

  //Define all the names of the trees and branches.
  TString etaTag("TrkM_etadep");
  TString absetaTag("TrkM_absetadep");
  TString centTag("TrkM_centdep");
  const int nAbsEtaBins = 5;
  TString ptTag[nAbsEtaBins] = {"TrkM_abseta00_10", "TrkM_abseta10_15", "TrkM_abseta15_20", "TrkM_abseta20_24", "TrkM_pt"};
  TString allTag("TrkM_1bin");
  TString treeTag("tpTree");

  //Set up the output tree.
  TString outFileName = Form("tnp_Ana_RD_TrkM_pPb_%s_%s_merged.root",whichFunc.Data(),todaysDate.Data());
  TFile* outFile = new TFile(Form("%s/%s",outDirectory.Data(),outFileName.Data()),"recreate");
  TDirectory *tpTreedir = outFile->mkdir("tpTree");
  tpTreedir->cd();    // make the "tpTree" directory the current directory
  TDirectory *alldir = tpTreedir->mkdir(allTag);
  TDirectory *ptdir[nAbsEtaBins];
  for (int j=0; j<nAbsEtaBins; j++) {
    ptdir[j] = tpTreedir->mkdir(ptTag[j]);
  }
  TDirectory *absetadir = tpTreedir->mkdir(absetaTag);
  TDirectory *etadir = tpTreedir->mkdir(etaTag);
  TDirectory *centdir = tpTreedir->mkdir(centTag);

  //Read in files to be merged.
  const int nFiles = 4;
  TString fDataName[4];
  cout << "INPUT FILES:" << endl;
  for (int i=0; i<nFiles; i++) {
    fDataName[i] = Form("tnp_Ana_RD_TrkM_pPb-quarter%i_%s_%s.root",i+1,whichFunc.Data(),todaysDate.Data());
    cout << fDataName[i] << endl;
  }
  cout << endl << "OUTPUT FILE:" << endl;
  cout << outFileName << endl << endl;

  TFile* fData[nFiles];
  for (int i=0; i<nFiles; i++) {
    fData[i] = new TFile( Form("%s/%s",inDirectory.Data(),fDataName[i].Data()) );
  }

  RooDataSet* rds_pt[nFiles][nAbsEtaBins];
  RooDataSet* rds_eta[nFiles];
  RooDataSet* rds_abseta[nFiles];
  RooDataSet* rds_all[nFiles];
  RooDataSet* rds_cent[nFiles];

  RooDataSet* rds_pt_merged[nAbsEtaBins];
  RooDataSet* rds_eta_merged;
  RooDataSet* rds_abseta_merged;
  RooDataSet* rds_all_merged;
  RooDataSet* rds_cent_merged;

  list<RooDataSet*> ptList[nAbsEtaBins];
  list<RooDataSet*> etaList;
  list<RooDataSet*> allList;
  list<RooDataSet*> absetaList;
  list<RooDataSet*> centList;

  cout << "Loading datasets" << endl;
  for (int k=0; k<nFiles; k++) {
    for (int j=0; j<nAbsEtaBins; j++) {
      rds_pt[k][j] = (RooDataSet*)fData[k]->Get(treeTag + "/" + ptTag[j] + "/fit_eff");
      ptList[j].push_back(rds_pt[k][j]);
    }
    rds_eta[k] = (RooDataSet*)fData[k]->Get(treeTag + "/" + etaTag + "/fit_eff");
    rds_all[k] = (RooDataSet*)fData[k]->Get(treeTag + "/" + allTag + "/fit_eff");
    rds_abseta[k] = (RooDataSet*)fData[k]->Get(treeTag + "/" + absetaTag + "/fit_eff");
    rds_cent[k] = (RooDataSet*)fData[k]->Get(treeTag + "/" + centTag + "/fit_eff");
    etaList.push_back(rds_eta[k]);
    allList.push_back(rds_all[k]);
    absetaList.push_back(rds_abseta[k]);
    centList.push_back(rds_cent[k]);
  }

  //Extract the numProbes in each bin.
/*  TH1D* hProbes[10];
  for (int i = 0; i<10; i++) {
    hProbes[i] = new TH1D(Form("hProbes[%i]",i),Form("hProbes[%i]",i),numBins,0,numBins);
    for (int jBin=0; jBin<numBins; jBin++){
      RooFitResult* fitRes = (RooFitResult*)fData[k]->Get(Form("tpTree/TrkM_pt/eta_bin0__pt_bin%i__tag_nVertices_bin0__cbFixedNalphaGausPol3/fitresult_simPdf_data_binned;1",jBin));
      RooRealVar* numTot_fitRes = (RooRealVar*)fitRes->floatParsFinal().find("numTot");
      double numTotval = numTot_fitRes->getVal();
      double numToterr = numTot_fitRes->getError();
      hProbes[i]->SetBinContent(jBin+1,numTotval);
      hProbes[i]->SetBinError(jBin+1,numToterr);
      //cout << "numTot = " << numTotval << " +/- " << numToterr << endl;
    }
  }*/

  //Merge and write the datasets into the directories.
  cout << "Merging datasets" << endl;
  for (int j=0; j<nAbsEtaBins; j++) {
    ptdir[j]->cd();
    cout << endl << "will now merge " << ptTag[j] << endl;
    rds_pt_merged[j] = mergeDataSets(ptList[j]);
    rds_pt_merged[j]->Write();
  }
  etadir->cd();
  cout << endl << "will now merge " << etaTag << endl;
  rds_eta_merged = mergeDataSets(etaList);
  rds_eta_merged->Write();
  alldir->cd();
  cout << endl << "will now merge " << allTag << endl;
  rds_all_merged = mergeDataSets(allList);
  rds_all_merged->Write();
  absetadir->cd();
  cout << endl << "will now merge " << absetaTag << endl;
  rds_abseta_merged = mergeDataSets(absetaList);
  rds_abseta_merged->Write();
  centdir->cd();
  cout << endl << "will now merge " << centTag << endl;
  rds_cent_merged = mergeDataSets(centList);
  rds_cent_merged->Write();

  //Check results:
  for (int j=0; j<nAbsEtaBins; j++) {
    cout << endl << "rds_pt_merged[" << j << "] = " << endl;
    PrintRooDataSet(rds_pt_merged[j]);
  }
  cout << endl << "rds_eta_merged = " << endl;
  PrintRooDataSet(rds_eta_merged);
  cout << endl << "rds_all_merged = " << endl;
  PrintRooDataSet(rds_all_merged);
  cout << endl << "rds_abseta_merged = " << endl;
  PrintRooDataSet(rds_abseta_merged);
  cout << endl << "rds_all_merged = " << endl;
  PrintRooDataSet(rds_cent_merged);

  //Plot dataset
  const RooArgSet *set0 = rds_pt_merged[0]->get();
  RooRealVar *eta = (RooRealVar*)set0->find("eta");
  RooRealVar *abseta = (RooRealVar*)set0->find("abseta");
  RooRealVar *pt = (RooRealVar*)set0->find("pt");
  RooPlot* ptframe = pt->frame();
  rds_pt_merged[0]->plotOn(ptframe);
  ptframe->Draw();

  //Write everything to the output file
  cout << "Writing to File " << outFileName << endl;
  outFile->cd();
  tpTreedir->Write();
  //delete tpTreedir;
  //outFile->Close();
  //delete outFile;

}
