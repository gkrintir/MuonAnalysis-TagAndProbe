#include <iostream>
#include "TString.h"

using namespace std;

const int nbins = 47;
const double ael[nbins] = {0  ,
   0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,
   0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,
   1.2,1.2,1.2,1.2,1.2,1.2,1.2,1.2,1.2,1.2,
   2.1,2.1,2.1,2.1,2.1,2.1,
   0  ,1.2,2.1,
   0  ,0.3,0.6,0.9,1.2,1.6,2.1
};
const double aeh[nbins] = {2.4,
   2.4,2.4,2.4,2.4,2.4,2.4,2.4,2.4,2.4,2.4,
   1.2,1.2,1.2,1.2,1.2,1.2,1.2,1.2,1.2,1.2,
   2.1,2.1,2.1,2.1,2.1,2.1,2.1,2.1,2.1,2.1,
   2.4,2.4,2.4,2.4,2.4,2.4,
   1.2,2.1,2.4,
   0.3,0.6,0.9,1.2,1.6,2.1,2.4
};
const double ptl[nbins] = {7  ,
   7  ,12 ,15 ,30 ,40 ,50, 60 ,70 ,80 ,100,
   7  ,12 ,15 ,25 ,30 ,35 ,40 ,45 ,50 ,80 ,
   7  ,12 ,15 ,25 ,30 ,35 ,40 ,45 ,50 ,80 ,
   7  ,12 ,15 ,25 ,40 ,80 ,
   7  ,7  ,7  ,
   7  ,7  ,7  ,7  ,7  ,7,  7
};
const double pth[nbins] = {200,
   12 ,15 ,30 ,40 ,50, 60 ,70 ,80 ,100,200,
   12 ,15 ,25 ,30 ,35 ,40 ,45 ,50 ,80 ,200,
   12 ,15 ,25 ,30 ,35 ,40 ,45 ,50 ,80 ,200,
   12 ,15 ,25 ,40 ,80 ,200,
   200,200,200,
   200,200,200,200,200,200,200
};

void print_tnp_config(int massmin=75, int massmax=120, const char* templatefilename="MassTemplatesForTnP_relPF" << tagname << "_M75120.root", const char* isotagname="" << tagname << "") {
   cout << "import FWCore.ParameterSet.Config as cms" << endl;
   cout << "" << endl;
   cout << "process = cms.Process(\"TagProbe\")" << endl;
   cout << "process.load('FWCore.MessageService.MessageLogger_cfi')" << endl;
   cout << "process.source = cms.Source(\"EmptySource\")" << endl;
   cout << "process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1) )    " << endl;
   cout << "" << endl;
   cout << "" << endl;
   cout << "" << endl;
   cout << "" << endl;
   cout << "" << endl;
   cout << "process.TagProbeFitTreeAnalyzer = cms.EDAnalyzer(\"TagProbeFitTreeAnalyzer\"," << endl;
   cout << "    # IO parameters:" << endl;
   cout << "    InputFileNames = cms.vstring(\"file:datanew3.root\")," << endl;
   cout << "    InputDirectoryName = cms.string(\"tpTree\")," << endl;
   cout << "    InputTreeName = cms.string(\"fitter_tree\")," << endl;
   cout << "    OutputFileName = cms.string(\"tnp_Ana_Data_newIso_vpv_" << isotagname << "_dxyz_ptGT7_M" << massmin << massmax << ".root\")," << endl;
   cout << "    #numbrer of CPUs to use for fitting" << endl;
   cout << "    NumCPU = cms.uint32(25)," << endl;
   cout << "    # specifies whether to save the RooWorkspace containing the data for each bin and" << endl;
   cout << "    # the pdf object with the initial and final state snapshots" << endl;
   cout << "    binnedFit = cms.bool(False)," << endl;
   cout << "    #binsForFit = cms.uint32(30)," << endl;
   cout << "    binsForMassPlots = cms.uint32(50)," << endl;
   cout << "    SaveWorkspace = cms.bool(False)," << endl;
   cout << "    # WeightVariable = cms.string(\"weight\")," << endl;
   cout << "    " << endl;
   cout << "    # defines all the real variables of the probes available in the input tree and intended for use in the efficiencies" << endl;
   cout << "    Variables = cms.PSet(" << endl;
   cout << "                         mass             = cms.vstring(\"Tag-Probe Mass\", \"" << massmin << ".0\", \"" << massmax << ".0\", \"GeV/c^{2}\"), # mass range syst: 65-110, nom 60-120 - TBA" << endl;
   cout << "                         pt               = cms.vstring(\"Probe p_{T}\", \"0.0\", \"1000\", \"GeV/c\")," << endl;
   cout << "                         eta              = cms.vstring(\"Probe #eta\", \"-2.4\", \"2.4\", \"\")," << endl;
   cout << "                         abseta           = cms.vstring(\"Probe |#eta|\", \"0\", \"2.5\", \"\")," << endl;
   cout << "                         tag_hiNtracks    = cms.vstring(\"N Tracks\", \"0\", \"400\", \"\")," << endl;
   cout << "                         tag_hiHF         = cms.vstring(\"HF\", \"0\", \"500\", \"\")," << endl;
   cout << "                         tag_nVertices    = cms.vstring(\"PU - nVertices\", \"0\", \"10\", \"\")," << endl;
   cout << "                         # weight           = cms.vstring(\"weight\",\"0\",\"10\",\"\")," << endl;
   cout << "    )," << endl;
   cout << "    # defines all the discrete variables of the probes available in the input tree and intended for use in the efficiency calculations" << endl;
   cout << "    Categories = cms.PSet(" << endl;
   cout << "       TightId = cms.vstring(\"TightId\", \"dummy[true=1,false=0]\")," << endl;
   cout << "       " << isotagname << " = cms.vstring(\"" << isotagname << "\", \"dummy[true=1,false=0]\")," << endl;
   cout << "" << endl;
   cout << "       )," << endl;
   cout << "" << endl;
   cout << "    # defines all the PDFs that will be available for the efficiency calculations; uses RooFit's \"factory\" syntax;" << endl;
   cout << "    # each pdf needs to define \"signal\", \"backgroundPass\", \"backgroundFail\" pdfs, \"efficiency[0.9,0,1]\" and \"signalFractionInPassing[0.9]\" are used for initial values  " << endl;
   cout << "    PDFs = cms.PSet(" << endl;
   cout << "       # Nominal" << endl;
   cout << "       BWResCBExp = cms.vstring(" << endl;
   cout << "          \"BreitWigner::bw(mass, m0[91.2,81.2,101.2], width[2.495,1,10])\"," << endl;
   cout << "          \"RooCBShape::res(mass, peak[0], sigma[1.7,0.01,10], alpha[1.8,0,3], n[0.8,0,10])\"," << endl;
   cout << "          \"FCONV::signal(mass, bw, res)\"," << endl;
   cout << "          \"Exponential::backgroundPass(mass, lp[0,-5,5])\"," << endl;
   cout << "          \"Exponential::backgroundFail(mass, lf[0,-5,5])\"," << endl;
   cout << "          \"efficiency[0.95,0.1,1]\"," << endl;
   cout << "          \"signalFractionInPassing[0.9]\"," << endl;
   cout << "          ),    " << endl;
   cout << "       # templates" << endl;

   // build the PDFs
   for (int ibin=0; ibin<nbins-1; ibin++) {
      TString tagname = Form("abseta_%.0f_%.0f_pt_%.0f_%.0f",ael[ibin]*10.,aeh[ibin]*10.,ptl[ibin],pth[ibin]);
      cout << "       templates_" << tagname << " = cms.vstring(" << endl;
      cout << "          \"#import " << templatefilename << ":ws_templates:hpass_" << tagname << "_roohistpdf\"," << endl;
      cout << "          \"#import " << templatefilename << ":ws_templates:hfail_" << tagname << "_roohistpdf\"," << endl;
      cout << "          \"Gaussian::res(mass, mean[0,-1,1], sigma[0.001,1e-10,10])\"," << endl;
      cout << "          \"FCONV::signalPass(mass, hpass_" << tagname << "_roohistpdf, res)\"," << endl;
      cout << "          \"FCONV::signalFail(mass, hfail_" << tagname << "_roohistpdf, res)\"," << endl;
      cout << "          \"Exponential::backgroundPass(mass, lp[0,-5,5])\"," << endl;
      cout << "          \"Exponential::backgroundFail(mass, lf[0,-5,5])\"," << endl;
      cout << "          \"efficiency[0.95,0.1,1]\"," << endl;
      cout << "          \"signalFractionInPassing[0.9]\"," << endl;
      cout << "          )";
      if (ibin!=nbins-2) cout << ",";
      cout << endl;
   }

   cout << "       )," << endl;
   cout << "" << endl;
   cout << "    # defines a set of efficiency calculations, what PDF to use for fitting and how to bin the data;" << endl;
   cout << "    # there will be a separate output directory for each calculation that includes a simultaneous fit, side band subtraction and counting. " << endl;
   cout << "    Efficiencies = cms.PSet(" << endl;
   cout << "          cms.PSet(" << endl;

   // build the efficiency definitions
   for (int ibin=0; ibin<nbins-6; ibin++) {
      TString tagname = Form("abseta_%.0f_%.0f_pt_%.0f_%.0f",ael[ibin]*10.,aeh[ibin]*10.,ptl[ibin],pth[ibin]);
      cout << "             Iso_" << tagname << " = cms.PSet(" << endl;
      cout << "                EfficiencyCategoryAndState = cms.vstring(\"" << tagname << "\",\"true\")," << endl;
      cout << "                UnbinnedVariables = cms.vstring(\"mass\")," << endl;
      cout << "                BinnedVariables = cms.PSet(" << endl;
      cout << "                   pt = cms.vdouble(" << ptl[ibin] << ", " << pth[ibin] << ")," << endl;
      cout << "                   abseta = cms.vdouble(" << ael[ibin] << ", " << aeh[ibin] << ")," << endl;
      cout << "                   TightId = cms.vstring(\"true\")," << endl;
      cout << "                   )," << endl;
      cout << "                BinToPDFmap = cms.vstring(\"templates_" << tagname << "\")" << endl;
      cout << "                ),";
      cout << endl;
   }
   for (int ibin=nbins-7; ibin<nbins; ibin++) {
      TString tagname = Form("abseta_%.0f_%.0f_pt_%.0f_%.0f",ael[ibin]*10.,aeh[ibin]*10.,ptl[ibin],pth[ibin]);
      TString tagname2 = Form("eta_%.0f_%.0f_pt_%.0f_%.0f",ael[ibin]*10.,aeh[ibin]*10.,ptl[ibin],pth[ibin]);
      cout << "             Iso_" << tagname2 << " = cms.PSet(" << endl;
      cout << "                EfficiencyCategoryAndState = cms.vstring(\"" << tagname << "\",\"true\")," << endl;
      cout << "                UnbinnedVariables = cms.vstring(\"mass\")," << endl;
      cout << "                BinnedVariables = cms.PSet(" << endl;
      cout << "                   pt = cms.vdouble(" << ptl[ibin] << ", " << pth[ibin] << ")," << endl;
      cout << "                   eta = cms.vdouble(" << ael[ibin] << ", " << aeh[ibin] << ")," << endl;
      cout << "                   TightId = cms.vstring(\"true\")," << endl;
      cout << "                   )," << endl;
      cout << "                BinToPDFmap = cms.vstring(\"templates_" << tagname << "\")" << endl;
      cout << "                ),";
      cout << endl;
   }
   // add the ones for etadep for negative eta
   for (int ibin=nbins-1; ibin>=nbins-7; ibin--) {
      TString tagname = Form("abseta_%.0f_%.0f_pt_%.0f_%.0f",ael[ibin]*10.,aeh[ibin]*10.,ptl[ibin],pth[ibin]);
      TString tagname2 = Form("eta_%.0f_%.0f_pt_%.0f_%.0f",-aeh[ibin]*10.,-ael[ibin]*10.,ptl[ibin],pth[ibin]);
      tagname2.ReplaceAll("-","m");
      cout << "             Iso_" << tagname2 << " = cms.PSet(" << endl;
      cout << "                EfficiencyCategoryAndState = cms.vstring(\"" << tagname << "\",\"true\")," << endl;
      cout << "                UnbinnedVariables = cms.vstring(\"mass\")," << endl;
      cout << "                BinnedVariables = cms.PSet(" << endl;
      cout << "                   pt = cms.vdouble(" << ptl[ibin] << ", " << pth[ibin] << ")," << endl;
      cout << "                   eta = cms.vdouble(" << -aeh[ibin] << ", " << -ael[ibin] << ")," << endl;
      cout << "                   TightId = cms.vstring(\"true\")," << endl;
      cout << "                   )," << endl;
      cout << "                BinToPDFmap = cms.vstring(\"templates_" << tagname << "\")" << endl;
      cout << "                )";
      if (ibin!=nbins-7) cout << ",";
      cout << endl;
   }

   cout << "             )," << endl;
   cout << "          )" << endl;
   cout << ")" << endl;
   cout << "" << endl;
   cout << "process.fitness = cms.Path(" << endl;
   cout << "    process.TagProbeFitTreeAnalyzer" << endl;
   cout << ")" << endl;
}
