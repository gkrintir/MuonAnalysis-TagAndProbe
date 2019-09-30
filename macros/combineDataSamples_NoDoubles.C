#include "TTree.h"
#include "TFile.h"
#include "TMath.h"
#include <iostream>

//These variables are kept global, or they have to be put as arguments millions of time -> very slow
std::vector<Int_t*> index1;
std::vector<ULong64_t*> Event_number1;
std::vector<float*> pTrk1;
std::vector<float*> etaTrk1;
std::vector<Int_t> nentries1;
std::vector<Int_t*> index2;
std::vector<Int_t> nentries2;

bool evtInSortedList(ULong64_t event2, int treeNb, int *istart){
  bool foundIdx = false;
  
  for (int i= *istart;i<nentries1[treeNb];i++){
    //cout<<"istart = "<<*istart<<", i = "<<i<<"    and event_number = "<<Event_number1[treeNb][index1[treeNb][i]]<<endl;
    if(event2==Event_number1[treeNb][index1[treeNb][i]]) {
      foundIdx = true; 
      *istart=i; //could be =i, but keeping security for limit cases
      //cout<<"Found same event number "<< Event_number1[treeNb][index1[treeNb][i]] <<", with ordered index "<<i<<endl;
      break;
    }
    if(event2<Event_number1[treeNb][index1[treeNb][i]]) {
      //cout<<"Event number "<<event2<<" is not in list of indices below "<<Event_number1[treeNb][index1[treeNb][i]]<<endl; 
      *istart=i;
      break;} //Event_number list is in increasing order
  }

  return foundIdx;
}

// bool floatInSortedList(float p2, float eta2, int treeNb, int *istart){
//   bool foundIdx = false;

//   for (int i= *istart;i<nentries1[treeNb];i++){
//     //cout<<"istart = "<<*istart<<", i = "<<i<<"    and p,eta = "<<pTrk1[treeNb][index1[treeNb][i]]<<" "<<etaTrk1[treeNb][index1[treeNb][i]]<<endl;
//     if(fabs((p2-pTrk1[treeNb][index1[treeNb][i]])/p2)<1e-5 && fabs(eta2-etaTrk1[treeNb][index1[treeNb][i]])<1e-5) {
//       foundIdx = true; 
//       *istart=(i<10000)?i:(i-10000); //keeping security compared to rounded floats
//       //cout<<"Found same p,eta "<< p2<<" "<<eta2 <<", with ordered index "<<i<<endl;
//       break;
//     }
//     if(p2*(1+5e-5)<pTrk1[treeNb][index1[treeNb][i]]) {
//       //cout<<"p,eta "<< p2<<" "<<eta2 <<" is not in list of indices below momentum "<<pTrk1[treeNb][index1[treeNb][i]]<<" with eta = "<<etaTrk1[treeNb][index1[treeNb][i]] <<endl; 
//       *istart=(i<10000)?i:(i-10000);
//       break;} //Event_number list is in increasing order
//   }

//   return foundIdx;
// }


std::tuple<std::vector<Int_t*>, std::vector<ULong64_t*>, std::vector<float*>, std::vector<float*>, std::vector<Int_t> > sort(const char* filename, bool onlyIndex=false) {
  TFile f( ((string)filename+".root").c_str(),"read");
  //  cout<<((string)filename+".root").c_str()<<endl;
  std::vector<TTree*> trees;
  trees.push_back((TTree*)f.Get("tpTree/fitter_tree"));
  trees.push_back((TTree*)f.Get("tpTreeSta/fitter_tree"));
  trees.push_back((TTree*)f.Get("tpTreeTrk/fitter_tree"));
  std::vector<Int_t> nentries;
  std::vector<Int_t*> index;
  std::vector<ULong64_t*> Event_number;
  std::vector<float*> pTrk;
  std::vector<float*> etaTrk;

  ///////////////////////////////////////////
  //    Sort events in the tree
  ///////////////////////////////////////////
  for (int i=0;i<3;i++){
    nentries.push_back((Int_t)trees[i]->GetEntries());
    index.push_back(new Int_t[nentries[i]]);

    //    if(i<2){
    pTrk.push_back(new float[1]);
    etaTrk.push_back(new float[1]);
    Event_number.push_back(new ULong64_t[nentries[i]]);
          
    //Fill event_number array
    ULong64_t event;
    TBranch *b_event = trees[i]->GetBranch("event");
    b_event->SetAddress(&event);
    for (Int_t j=0;j<nentries[i];j++) {
      b_event->GetEntry(j);
      Event_number[i][j] = event;
    }

    //sort array containing event number in increasing order
    //The array index contains the entry numbers in increasing order of event number
    cout<<"sorting index list "<<i<<" w.r.t. event number"<<endl;
    TMath::Sort(nentries[i],Event_number[i],index[i],false);
    cout<<"sorted index list "<<i<<" w.r.t. event number"<<endl;
    //}

    // //special case for tpTreeTrk that does not have the event number branch
    // else{
    //   pTrk.push_back(new float[nentries[i]]);
    //   etaTrk.push_back(new float[nentries[i]]);
    //   Event_number.push_back(new ULong64_t[1]);

    //   //Fill event_number array
    //   float pProbe;
    //   TBranch *b_pProbe = trees[i]->GetBranch("p");
    //   b_pProbe->SetAddress(&pProbe);
    //   float etaProbe;
    //   TBranch *b_etaProbe = trees[i]->GetBranch("eta");
    //   b_etaProbe->SetAddress(&etaProbe);

    //   for (Int_t j=0;j<nentries[i];j++) {
    // 	b_pProbe->GetEntry(j);
    // 	pTrk[i][j] = pProbe;
    // 	if(!onlyIndex){
    // 	  b_etaProbe->GetEntry(j);
    // 	  etaTrk[i][j] = etaProbe;
    //   }
    // }

    // //sort array containing p in decreasing order
    // //The array index contains the entry numbers in decreasing order of p
    // cout<<"sorting index list "<<i<<" w.r.t. probe momentum"<<endl;
    // TMath::Sort(nentries[i],pTrk[i],index[i],false);
    // cout<<"sorted index list "<<i<<" w.r.t. probe momentum"<<endl;  
    
    if(onlyIndex){
      Event_number[i] = new ULong64_t[1];
      pTrk[i] = new float[1];
      etaTrk[i] = new float[1];
    }
  }

  return std::make_tuple(index,Event_number,pTrk,etaTrk,nentries);
}

void combineDataSamples_NoDoubles(){
  const char* filename1 = "/home/llr/cms/falmagne/tuples/pp17/TnP/data/TNP_SingleMu_pp5TeVRun2017G_PromptReco_v1_AOD_20190924/tnpJpsi_data_pp5TeV_SingleMu";
  const char* filename2 = "/home/llr/cms/falmagne/tuples/pp17/TnP/data/TNP_SingleMuTnP_pp5TeVRun2017G_PromptReco_v1_AOD_20190924/tnpJpsi_data_pp5TeV_SingleMuTnP";

  //Get indices of sorted event list
  cout<<"Sorting events in the trees of file "<<filename1<<".root"<<endl;
  std::tuple<std::vector<Int_t*>, std::vector<ULong64_t*>, std::vector<float*>, std::vector<float*>, std::vector<Int_t> > tuple1 = sort(filename1);
  index1 = std::get<0>(tuple1);
  Event_number1 = std::get<1>(tuple1);
  pTrk1 = std::get<2>(tuple1);
  etaTrk1 = std::get<3>(tuple1);
  nentries1 = std::get<4>(tuple1);
  
  cout<<"Sorting events in the trees of file "<<filename2<<".root"<<endl;
  std::tuple<std::vector<Int_t*>, std::vector<ULong64_t*>, std::vector<float*>, std::vector<float*>, std::vector<Int_t> > tuple2 = sort(filename2,true);
  index2 = std::get<0>(tuple2);
  // std::vector<ULong64_t*> Event_number2 = std::get<1>(tuple2);
  // std::vector<float*> pTrk2 = std::get<2>(tuple2);
  // std::vector<float*> etaTrk2 = std::get<3>(tuple2);
  nentries2 = std::get<4>(tuple2);


  ///////////////////////////////////////////
  //    Open a new file, and copy the events of the second tree that are not doubles (events that are not already in the first tree)
  ///////////////////////////////////////////

  TFile f2( ((string)filename2+".root").c_str(),"read");
  std::vector<TTree*> trees2;
  trees2.push_back((TTree*)f2.Get("tpTree/fitter_tree"));
  trees2.push_back((TTree*)f2.Get("tpTreeSta/fitter_tree"));
  trees2.push_back((TTree*)f2.Get("tpTreeTrk/fitter_tree"));

  //open new file to store the output Tree
  TFile *f3 = new TFile("f_SingleMuTnP_relevantEntries.root","recreate");
  std::vector<TTree*> trees_skimmed;

  for (int i=0;i<3;i++){

    TDirectory *dir = f3->mkdir((i==0)?"tpTree":((i==1)?"tpTreeSta":"tpTreeTrk"));
    dir->cd();

    int istart=0;
    ULong64_t event;
    float p;
    float eta;
    //    if(i<2){
    TBranch *b_event = trees2[i]->GetBranch("event");
    b_event->SetAddress(&event);
    //}
    // else{
    //   TBranch *b_p = trees2[i]->GetBranch("p");
    //   b_p->SetAddress(&p);
    //   TBranch *b_eta = trees2[i]->GetBranch("eta");
    //   b_eta->SetAddress(&eta);
    // }

    trees_skimmed.push_back((TTree*)trees2[i]->CloneTree(0));

    int keptEvents = 0;

    //    if(i<2){
    for (Int_t j=0;j<(int)nentries2[i];j++) {
      if(j%5000==0){cout<<"Scanned fraction of indices : "<<100.*(double)j/nentries2[i]<<"%"<<endl;}
      trees2[i]->GetEntry(index2[i][j]);

      // 	cout<<"\n Looking for event with event_number = "<<event<<endl;
      if(!evtInSortedList(event,i,&istart)
	 ){      
	keptEvents+=1;
	trees_skimmed[i]->Fill();
      }
    }
    //}
    
    // if(i==2){
    // for (Int_t j=0;j<(int)nentries2[i];j++) {
    //   if(j%5000==0){cout<<"Scanned fraction of indices : "<<100.*(double)j/nentries2[i]<<"%"<<endl;}
    //   trees2[i]->GetEntry(index2[i][j]);

    //   //cout<<"\n Looking for event with p,eta = "<<p<<" "<<eta<<endl;
    //   if(!floatInSortedList(p,eta,i,&istart)
    // 	 ){      
    // 	keptEvents+=1;
    // 	trees_skimmed[i]->Fill();
    //   }
    // }
    // }

    cout<<"Added "<< keptEvents <<" events from second file, for tree "<<i<<endl;
    trees_skimmed[i]->Print();
    trees_skimmed[i]->AutoSave();
    delete [] index1[i];
    delete [] index2[i];
  }

}
