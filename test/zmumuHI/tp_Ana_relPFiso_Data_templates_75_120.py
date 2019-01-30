import FWCore.ParameterSet.Config as cms

process = cms.Process("TagProbe")
process.load('FWCore.MessageService.MessageLogger_cfi')
process.source = cms.Source("EmptySource")
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1) )    





process.TagProbeFitTreeAnalyzer = cms.EDAnalyzer("TagProbeFitTreeAnalyzer",
    # IO parameters:
    InputFileNames = cms.vstring("file:datanew3.root"),
    InputDirectoryName = cms.string("tpTree"),
    InputTreeName = cms.string("fitter_tree"),
    OutputFileName = cms.string("tnp_Ana_Data_newIso_vpv_iso0p15_dxyz_ptGT7_M75120.root"),
    #numbrer of CPUs to use for fitting
    NumCPU = cms.uint32(25),
    # specifies whether to save the RooWorkspace containing the data for each bin and
    # the pdf object with the initial and final state snapshots
    binnedFit = cms.bool(True),
    binsForFit = cms.uint32(50),
    binsForMassPlots = cms.uint32(50),
    SaveWorkspace = cms.bool(False),
    # WeightVariable = cms.string("weight"),
    
    # defines all the real variables of the probes available in the input tree and intended for use in the efficiencies
    Variables = cms.PSet(
                         mass             = cms.vstring("Tag-Probe Mass", "75.0", "120.0", "GeV/c^{2}"), # mass range syst: 65-110, nom 60-120 - TBA
                         pt               = cms.vstring("Probe p_{T}", "0.0", "1000", "GeV/c"),
                         eta              = cms.vstring("Probe #eta", "-2.4", "2.4", ""),
                         abseta           = cms.vstring("Probe |#eta|", "0", "2.5", ""),
                         tag_hiNtracks    = cms.vstring("N Tracks", "0", "400", ""),
                         tag_hiHF         = cms.vstring("HF", "0", "500", ""),
                         tag_nVertices    = cms.vstring("PU - nVertices", "0", "10", ""),
                         # weight           = cms.vstring("weight","0","10",""),
    ),
    # defines all the discrete variables of the probes available in the input tree and intended for use in the efficiency calculations
    Categories = cms.PSet(
       TightId = cms.vstring("TightId", "dummy[true=1,false=0]"),
       iso0p15 = cms.vstring("iso0p15", "dummy[true=1,false=0]"),

       ),

    # defines all the PDFs that will be available for the efficiency calculations; uses RooFit's "factory" syntax;
    # each pdf needs to define "signal", "backgroundPass", "backgroundFail" pdfs, "efficiency[0.9,0,1]" and "signalFractionInPassing[0.9]" are used for initial values  
    PDFs = cms.PSet(
       # Nominal
       BWResCBExp = cms.vstring(
          "BreitWigner::bw(mass, m0[91.2,81.2,101.2], width[2.495,1,10])",
          "RooCBShape::res(mass, peak[0], sigma[1.7,0.01,10], alpha[1.8,0,3], n[0.8,0,10])",
          "FCONV::signal(mass, bw, res)",
          "Exponential::backgroundPass(mass, lp[0,-5,5])",
          "Exponential::backgroundFail(mass, lf[0,-5,5])",
          "efficiency[0.95,0.1,1]",
          "signalFractionInPassing[0.9]",
          ),    
       # templates
       templates_abseta_0_24_pt_7_200 = cms.vstring(
          "#import MassTemplatesForTnP_relPFiso0p15_M75120.root:ws_templates:hpass_abseta_0_24_pt_7_200_roohistpdf",
          "#import MassTemplatesForTnP_relPFiso0p15_M75120.root:ws_templates:hfail_abseta_0_24_pt_7_200_roohistpdf",
          "Gaussian::res(mass, mean[-0.2], sigma[4e-4])",
          "FCONV::signalPass(mass, hpass_abseta_0_24_pt_7_200_roohistpdf, res)",
          "FCONV::signalFail(mass, hfail_abseta_0_24_pt_7_200_roohistpdf, res)",
          "Exponential::backgroundPass(mass, lp[0,-5,5])",
          "Exponential::backgroundFail(mass, lf[0,-5,5])",
          "efficiency[0.95,0.1,1]",
          "signalFractionInPassing[0.9]",
          ),
       templates_abseta_0_24_pt_7_12 = cms.vstring(
          "#import MassTemplatesForTnP_relPFiso0p15_M75120.root:ws_templates:hpass_abseta_0_24_pt_7_12_roohistpdf",
          "#import MassTemplatesForTnP_relPFiso0p15_M75120.root:ws_templates:hfail_abseta_0_24_pt_7_12_roohistpdf",
          "Gaussian::res(mass, mean[-0.2], sigma[4e-4])",
          "FCONV::signalPass(mass, hpass_abseta_0_24_pt_7_12_roohistpdf, res)",
          "FCONV::signalFail(mass, hfail_abseta_0_24_pt_7_12_roohistpdf, res)",
          "Exponential::backgroundPass(mass, lp[0,-5,5])",
          "Exponential::backgroundFail(mass, lf[0,-5,5])",
          "efficiency[0.95,0.1,1]",
          "signalFractionInPassing[0.9]",
          ),
       templates_abseta_0_24_pt_12_15 = cms.vstring(
          "#import MassTemplatesForTnP_relPFiso0p15_M75120.root:ws_templates:hpass_abseta_0_24_pt_12_15_roohistpdf",
          "#import MassTemplatesForTnP_relPFiso0p15_M75120.root:ws_templates:hfail_abseta_0_24_pt_12_15_roohistpdf",
          "Gaussian::res(mass, mean[-0.2], sigma[4e-4])",
          "FCONV::signalPass(mass, hpass_abseta_0_24_pt_12_15_roohistpdf, res)",
          "FCONV::signalFail(mass, hfail_abseta_0_24_pt_12_15_roohistpdf, res)",
          "Exponential::backgroundPass(mass, lp[0,-5,5])",
          "Exponential::backgroundFail(mass, lf[0,-5,5])",
          "efficiency[0.95,0.1,1]",
          "signalFractionInPassing[0.9]",
          ),
       templates_abseta_0_24_pt_15_30 = cms.vstring(
          "#import MassTemplatesForTnP_relPFiso0p15_M75120.root:ws_templates:hpass_abseta_0_24_pt_15_30_roohistpdf",
          "#import MassTemplatesForTnP_relPFiso0p15_M75120.root:ws_templates:hfail_abseta_0_24_pt_15_30_roohistpdf",
          "Gaussian::res(mass, mean[-0.2], sigma[4e-4])",
          "FCONV::signalPass(mass, hpass_abseta_0_24_pt_15_30_roohistpdf, res)",
          "FCONV::signalFail(mass, hfail_abseta_0_24_pt_15_30_roohistpdf, res)",
          "Exponential::backgroundPass(mass, lp[0,-5,5])",
          "Exponential::backgroundFail(mass, lf[0,-5,5])",
          "efficiency[0.95,0.1,1]",
          "signalFractionInPassing[0.9]",
          ),
       templates_abseta_0_24_pt_30_40 = cms.vstring(
          "#import MassTemplatesForTnP_relPFiso0p15_M75120.root:ws_templates:hpass_abseta_0_24_pt_30_40_roohistpdf",
          "#import MassTemplatesForTnP_relPFiso0p15_M75120.root:ws_templates:hfail_abseta_0_24_pt_30_40_roohistpdf",
          "Gaussian::res(mass, mean[-0.2], sigma[4e-4])",
          "FCONV::signalPass(mass, hpass_abseta_0_24_pt_30_40_roohistpdf, res)",
          "FCONV::signalFail(mass, hfail_abseta_0_24_pt_30_40_roohistpdf, res)",
          "Exponential::backgroundPass(mass, lp[0,-5,5])",
          "Exponential::backgroundFail(mass, lf[0,-5,5])",
          "efficiency[0.95,0.1,1]",
          "signalFractionInPassing[0.9]",
          ),
       templates_abseta_0_24_pt_40_50 = cms.vstring(
          "#import MassTemplatesForTnP_relPFiso0p15_M75120.root:ws_templates:hpass_abseta_0_24_pt_40_50_roohistpdf",
          "#import MassTemplatesForTnP_relPFiso0p15_M75120.root:ws_templates:hfail_abseta_0_24_pt_40_50_roohistpdf",
          "Gaussian::res(mass, mean[-0.2], sigma[4e-4])",
          "FCONV::signalPass(mass, hpass_abseta_0_24_pt_40_50_roohistpdf, res)",
          "FCONV::signalFail(mass, hfail_abseta_0_24_pt_40_50_roohistpdf, res)",
          "Exponential::backgroundPass(mass, lp[0,-5,5])",
          "Exponential::backgroundFail(mass, lf[0,-5,5])",
          "efficiency[0.95,0.1,1]",
          "signalFractionInPassing[0.9]",
          ),
       templates_abseta_0_24_pt_50_60 = cms.vstring(
          "#import MassTemplatesForTnP_relPFiso0p15_M75120.root:ws_templates:hpass_abseta_0_24_pt_50_60_roohistpdf",
          "#import MassTemplatesForTnP_relPFiso0p15_M75120.root:ws_templates:hfail_abseta_0_24_pt_50_60_roohistpdf",
          "Gaussian::res(mass, mean[-0.2], sigma[4e-4])",
          "FCONV::signalPass(mass, hpass_abseta_0_24_pt_50_60_roohistpdf, res)",
          "FCONV::signalFail(mass, hfail_abseta_0_24_pt_50_60_roohistpdf, res)",
          "Exponential::backgroundPass(mass, lp[0,-5,5])",
          "Exponential::backgroundFail(mass, lf[0,-5,5])",
          "efficiency[0.95,0.1,1]",
          "signalFractionInPassing[0.9]",
          ),
       templates_abseta_0_24_pt_60_70 = cms.vstring(
          "#import MassTemplatesForTnP_relPFiso0p15_M75120.root:ws_templates:hpass_abseta_0_24_pt_60_70_roohistpdf",
          "#import MassTemplatesForTnP_relPFiso0p15_M75120.root:ws_templates:hfail_abseta_0_24_pt_60_70_roohistpdf",
          "Gaussian::res(mass, mean[-0.2], sigma[4e-4])",
          "FCONV::signalPass(mass, hpass_abseta_0_24_pt_60_70_roohistpdf, res)",
          "FCONV::signalFail(mass, hfail_abseta_0_24_pt_60_70_roohistpdf, res)",
          "Exponential::backgroundPass(mass, lp[0,-5,5])",
          "Exponential::backgroundFail(mass, lf[0,-5,5])",
          "efficiency[0.95,0.1,1]",
          "signalFractionInPassing[0.9]",
          ),
       templates_abseta_0_24_pt_70_80 = cms.vstring(
          "#import MassTemplatesForTnP_relPFiso0p15_M75120.root:ws_templates:hpass_abseta_0_24_pt_70_80_roohistpdf",
          "#import MassTemplatesForTnP_relPFiso0p15_M75120.root:ws_templates:hfail_abseta_0_24_pt_70_80_roohistpdf",
          "Gaussian::res(mass, mean[-0.2], sigma[4e-4])",
          "FCONV::signalPass(mass, hpass_abseta_0_24_pt_70_80_roohistpdf, res)",
          "FCONV::signalFail(mass, hfail_abseta_0_24_pt_70_80_roohistpdf, res)",
          "Exponential::backgroundPass(mass, lp[0,-5,5])",
          "Exponential::backgroundFail(mass, lf[0,-5,5])",
          "efficiency[0.95,0.1,1]",
          "signalFractionInPassing[0.9]",
          ),
       templates_abseta_0_24_pt_80_100 = cms.vstring(
          "#import MassTemplatesForTnP_relPFiso0p15_M75120.root:ws_templates:hpass_abseta_0_24_pt_80_100_roohistpdf",
          "#import MassTemplatesForTnP_relPFiso0p15_M75120.root:ws_templates:hfail_abseta_0_24_pt_80_100_roohistpdf",
          "Gaussian::res(mass, mean[-0.2], sigma[4e-4])",
          "FCONV::signalPass(mass, hpass_abseta_0_24_pt_80_100_roohistpdf, res)",
          "FCONV::signalFail(mass, hfail_abseta_0_24_pt_80_100_roohistpdf, res)",
          "Exponential::backgroundPass(mass, lp[0,-5,5])",
          "Exponential::backgroundFail(mass, lf[0,-5,5])",
          "efficiency[0.95,0.1,1]",
          "signalFractionInPassing[0.9]",
          ),
       templates_abseta_0_24_pt_100_200 = cms.vstring(
          "#import MassTemplatesForTnP_relPFiso0p15_M75120.root:ws_templates:hpass_abseta_0_24_pt_100_200_roohistpdf",
          "#import MassTemplatesForTnP_relPFiso0p15_M75120.root:ws_templates:hfail_abseta_0_24_pt_100_200_roohistpdf",
          "Gaussian::res(mass, mean[-0.2], sigma[4e-4])",
          "FCONV::signalPass(mass, hpass_abseta_0_24_pt_100_200_roohistpdf, res)",
          "FCONV::signalFail(mass, hfail_abseta_0_24_pt_100_200_roohistpdf, res)",
          "Exponential::backgroundPass(mass, lp[0,-5,5])",
          "Exponential::backgroundFail(mass, lf[0,-5,5])",
          "efficiency[0.95,0.1,1]",
          "signalFractionInPassing[0.9]",
          ),
       templates_abseta_0_12_pt_7_12 = cms.vstring(
          "#import MassTemplatesForTnP_relPFiso0p15_M75120.root:ws_templates:hpass_abseta_0_12_pt_7_12_roohistpdf",
          "#import MassTemplatesForTnP_relPFiso0p15_M75120.root:ws_templates:hfail_abseta_0_12_pt_7_12_roohistpdf",
          "Gaussian::res(mass, mean[-0.2], sigma[4e-4])",
          "FCONV::signalPass(mass, hpass_abseta_0_12_pt_7_12_roohistpdf, res)",
          "FCONV::signalFail(mass, hfail_abseta_0_12_pt_7_12_roohistpdf, res)",
          "Exponential::backgroundPass(mass, lp[0,-5,5])",
          "Exponential::backgroundFail(mass, lf[0,-5,5])",
          "efficiency[0.95,0.1,1]",
          "signalFractionInPassing[0.9]",
          ),
       templates_abseta_0_12_pt_12_15 = cms.vstring(
          "#import MassTemplatesForTnP_relPFiso0p15_M75120.root:ws_templates:hpass_abseta_0_12_pt_12_15_roohistpdf",
          "#import MassTemplatesForTnP_relPFiso0p15_M75120.root:ws_templates:hfail_abseta_0_12_pt_12_15_roohistpdf",
          "Gaussian::res(mass, mean[-0.2], sigma[4e-4])",
          "FCONV::signalPass(mass, hpass_abseta_0_12_pt_12_15_roohistpdf, res)",
          "FCONV::signalFail(mass, hfail_abseta_0_12_pt_12_15_roohistpdf, res)",
          "Exponential::backgroundPass(mass, lp[0,-5,5])",
          "Exponential::backgroundFail(mass, lf[0,-5,5])",
          "efficiency[0.95,0.1,1]",
          "signalFractionInPassing[0.9]",
          ),
       templates_abseta_0_12_pt_15_25 = cms.vstring(
          "#import MassTemplatesForTnP_relPFiso0p15_M75120.root:ws_templates:hpass_abseta_0_12_pt_15_25_roohistpdf",
          "#import MassTemplatesForTnP_relPFiso0p15_M75120.root:ws_templates:hfail_abseta_0_12_pt_15_25_roohistpdf",
          "Gaussian::res(mass, mean[-0.2], sigma[4e-4])",
          "FCONV::signalPass(mass, hpass_abseta_0_12_pt_15_25_roohistpdf, res)",
          "FCONV::signalFail(mass, hfail_abseta_0_12_pt_15_25_roohistpdf, res)",
          "Exponential::backgroundPass(mass, lp[0,-5,5])",
          "Exponential::backgroundFail(mass, lf[0,-5,5])",
          "efficiency[0.95,0.1,1]",
          "signalFractionInPassing[0.9]",
          ),
       templates_abseta_0_12_pt_25_30 = cms.vstring(
          "#import MassTemplatesForTnP_relPFiso0p15_M75120.root:ws_templates:hpass_abseta_0_12_pt_25_30_roohistpdf",
          "#import MassTemplatesForTnP_relPFiso0p15_M75120.root:ws_templates:hfail_abseta_0_12_pt_25_30_roohistpdf",
          "Gaussian::res(mass, mean[-0.2], sigma[4e-4])",
          "FCONV::signalPass(mass, hpass_abseta_0_12_pt_25_30_roohistpdf, res)",
          "FCONV::signalFail(mass, hfail_abseta_0_12_pt_25_30_roohistpdf, res)",
          "Exponential::backgroundPass(mass, lp[0,-5,5])",
          "Exponential::backgroundFail(mass, lf[0,-5,5])",
          "efficiency[0.95,0.1,1]",
          "signalFractionInPassing[0.9]",
          ),
       templates_abseta_0_12_pt_30_35 = cms.vstring(
          "#import MassTemplatesForTnP_relPFiso0p15_M75120.root:ws_templates:hpass_abseta_0_12_pt_30_35_roohistpdf",
          "#import MassTemplatesForTnP_relPFiso0p15_M75120.root:ws_templates:hfail_abseta_0_12_pt_30_35_roohistpdf",
          "Gaussian::res(mass, mean[-0.2], sigma[4e-4])",
          "FCONV::signalPass(mass, hpass_abseta_0_12_pt_30_35_roohistpdf, res)",
          "FCONV::signalFail(mass, hfail_abseta_0_12_pt_30_35_roohistpdf, res)",
          "Exponential::backgroundPass(mass, lp[0,-5,5])",
          "Exponential::backgroundFail(mass, lf[0,-5,5])",
          "efficiency[0.95,0.1,1]",
          "signalFractionInPassing[0.9]",
          ),
       templates_abseta_0_12_pt_35_40 = cms.vstring(
          "#import MassTemplatesForTnP_relPFiso0p15_M75120.root:ws_templates:hpass_abseta_0_12_pt_35_40_roohistpdf",
          "#import MassTemplatesForTnP_relPFiso0p15_M75120.root:ws_templates:hfail_abseta_0_12_pt_35_40_roohistpdf",
          "Gaussian::res(mass, mean[-0.2], sigma[4e-4])",
          "FCONV::signalPass(mass, hpass_abseta_0_12_pt_35_40_roohistpdf, res)",
          "FCONV::signalFail(mass, hfail_abseta_0_12_pt_35_40_roohistpdf, res)",
          "Exponential::backgroundPass(mass, lp[0,-5,5])",
          "Exponential::backgroundFail(mass, lf[0,-5,5])",
          "efficiency[0.95,0.1,1]",
          "signalFractionInPassing[0.9]",
          ),
       templates_abseta_0_12_pt_40_45 = cms.vstring(
          "#import MassTemplatesForTnP_relPFiso0p15_M75120.root:ws_templates:hpass_abseta_0_12_pt_40_45_roohistpdf",
          "#import MassTemplatesForTnP_relPFiso0p15_M75120.root:ws_templates:hfail_abseta_0_12_pt_40_45_roohistpdf",
          "Gaussian::res(mass, mean[-0.2], sigma[4e-4])",
          "FCONV::signalPass(mass, hpass_abseta_0_12_pt_40_45_roohistpdf, res)",
          "FCONV::signalFail(mass, hfail_abseta_0_12_pt_40_45_roohistpdf, res)",
          "Exponential::backgroundPass(mass, lp[0,-5,5])",
          "Exponential::backgroundFail(mass, lf[0,-5,5])",
          "efficiency[0.95,0.1,1]",
          "signalFractionInPassing[0.9]",
          ),
       templates_abseta_0_12_pt_45_50 = cms.vstring(
          "#import MassTemplatesForTnP_relPFiso0p15_M75120.root:ws_templates:hpass_abseta_0_12_pt_45_50_roohistpdf",
          "#import MassTemplatesForTnP_relPFiso0p15_M75120.root:ws_templates:hfail_abseta_0_12_pt_45_50_roohistpdf",
          "Gaussian::res(mass, mean[-0.2], sigma[4e-4])",
          "FCONV::signalPass(mass, hpass_abseta_0_12_pt_45_50_roohistpdf, res)",
          "FCONV::signalFail(mass, hfail_abseta_0_12_pt_45_50_roohistpdf, res)",
          "Exponential::backgroundPass(mass, lp[0,-5,5])",
          "Exponential::backgroundFail(mass, lf[0,-5,5])",
          "efficiency[0.95,0.1,1]",
          "signalFractionInPassing[0.9]",
          ),
       templates_abseta_0_12_pt_50_80 = cms.vstring(
          "#import MassTemplatesForTnP_relPFiso0p15_M75120.root:ws_templates:hpass_abseta_0_12_pt_50_80_roohistpdf",
          "#import MassTemplatesForTnP_relPFiso0p15_M75120.root:ws_templates:hfail_abseta_0_12_pt_50_80_roohistpdf",
          "Gaussian::res(mass, mean[-0.2], sigma[4e-4])",
          "FCONV::signalPass(mass, hpass_abseta_0_12_pt_50_80_roohistpdf, res)",
          "FCONV::signalFail(mass, hfail_abseta_0_12_pt_50_80_roohistpdf, res)",
          "Exponential::backgroundPass(mass, lp[0,-5,5])",
          "Exponential::backgroundFail(mass, lf[0,-5,5])",
          "efficiency[0.95,0.1,1]",
          "signalFractionInPassing[0.9]",
          ),
       templates_abseta_0_12_pt_80_200 = cms.vstring(
          "#import MassTemplatesForTnP_relPFiso0p15_M75120.root:ws_templates:hpass_abseta_0_12_pt_80_200_roohistpdf",
          "#import MassTemplatesForTnP_relPFiso0p15_M75120.root:ws_templates:hfail_abseta_0_12_pt_80_200_roohistpdf",
          "Gaussian::res(mass, mean[-0.2], sigma[4e-4])",
          "FCONV::signalPass(mass, hpass_abseta_0_12_pt_80_200_roohistpdf, res)",
          "FCONV::signalFail(mass, hfail_abseta_0_12_pt_80_200_roohistpdf, res)",
          "Exponential::backgroundPass(mass, lp[0,-5,5])",
          "Exponential::backgroundFail(mass, lf[0,-5,5])",
          "efficiency[0.95,0.1,1]",
          "signalFractionInPassing[0.9]",
          ),
       templates_abseta_12_21_pt_7_12 = cms.vstring(
          "#import MassTemplatesForTnP_relPFiso0p15_M75120.root:ws_templates:hpass_abseta_12_21_pt_7_12_roohistpdf",
          "#import MassTemplatesForTnP_relPFiso0p15_M75120.root:ws_templates:hfail_abseta_12_21_pt_7_12_roohistpdf",
          "Gaussian::res(mass, mean[-0.2], sigma[4e-4])",
          "FCONV::signalPass(mass, hpass_abseta_12_21_pt_7_12_roohistpdf, res)",
          "FCONV::signalFail(mass, hfail_abseta_12_21_pt_7_12_roohistpdf, res)",
          "Exponential::backgroundPass(mass, lp[0,-5,5])",
          "Exponential::backgroundFail(mass, lf[0,-5,5])",
          "efficiency[0.95,0.1,1]",
          "signalFractionInPassing[0.9]",
          ),
       templates_abseta_12_21_pt_12_15 = cms.vstring(
          "#import MassTemplatesForTnP_relPFiso0p15_M75120.root:ws_templates:hpass_abseta_12_21_pt_12_15_roohistpdf",
          "#import MassTemplatesForTnP_relPFiso0p15_M75120.root:ws_templates:hfail_abseta_12_21_pt_12_15_roohistpdf",
          "Gaussian::res(mass, mean[-0.2], sigma[4e-4])",
          "FCONV::signalPass(mass, hpass_abseta_12_21_pt_12_15_roohistpdf, res)",
          "FCONV::signalFail(mass, hfail_abseta_12_21_pt_12_15_roohistpdf, res)",
          "Exponential::backgroundPass(mass, lp[0,-5,5])",
          "Exponential::backgroundFail(mass, lf[0,-5,5])",
          "efficiency[0.95,0.1,1]",
          "signalFractionInPassing[0.9]",
          ),
       templates_abseta_12_21_pt_15_25 = cms.vstring(
          "#import MassTemplatesForTnP_relPFiso0p15_M75120.root:ws_templates:hpass_abseta_12_21_pt_15_25_roohistpdf",
          "#import MassTemplatesForTnP_relPFiso0p15_M75120.root:ws_templates:hfail_abseta_12_21_pt_15_25_roohistpdf",
          "Gaussian::res(mass, mean[-0.2], sigma[4e-4])",
          "FCONV::signalPass(mass, hpass_abseta_12_21_pt_15_25_roohistpdf, res)",
          "FCONV::signalFail(mass, hfail_abseta_12_21_pt_15_25_roohistpdf, res)",
          "Exponential::backgroundPass(mass, lp[0,-5,5])",
          "Exponential::backgroundFail(mass, lf[0,-5,5])",
          "efficiency[0.95,0.1,1]",
          "signalFractionInPassing[0.9]",
          ),
       templates_abseta_12_21_pt_25_30 = cms.vstring(
          "#import MassTemplatesForTnP_relPFiso0p15_M75120.root:ws_templates:hpass_abseta_12_21_pt_25_30_roohistpdf",
          "#import MassTemplatesForTnP_relPFiso0p15_M75120.root:ws_templates:hfail_abseta_12_21_pt_25_30_roohistpdf",
          "Gaussian::res(mass, mean[-0.2], sigma[4e-4])",
          "FCONV::signalPass(mass, hpass_abseta_12_21_pt_25_30_roohistpdf, res)",
          "FCONV::signalFail(mass, hfail_abseta_12_21_pt_25_30_roohistpdf, res)",
          "Exponential::backgroundPass(mass, lp[0,-5,5])",
          "Exponential::backgroundFail(mass, lf[0,-5,5])",
          "efficiency[0.95,0.1,1]",
          "signalFractionInPassing[0.9]",
          ),
       templates_abseta_12_21_pt_30_35 = cms.vstring(
          "#import MassTemplatesForTnP_relPFiso0p15_M75120.root:ws_templates:hpass_abseta_12_21_pt_30_35_roohistpdf",
          "#import MassTemplatesForTnP_relPFiso0p15_M75120.root:ws_templates:hfail_abseta_12_21_pt_30_35_roohistpdf",
          "Gaussian::res(mass, mean[-0.2], sigma[4e-4])",
          "FCONV::signalPass(mass, hpass_abseta_12_21_pt_30_35_roohistpdf, res)",
          "FCONV::signalFail(mass, hfail_abseta_12_21_pt_30_35_roohistpdf, res)",
          "Exponential::backgroundPass(mass, lp[0,-5,5])",
          "Exponential::backgroundFail(mass, lf[0,-5,5])",
          "efficiency[0.95,0.1,1]",
          "signalFractionInPassing[0.9]",
          ),
       templates_abseta_12_21_pt_35_40 = cms.vstring(
          "#import MassTemplatesForTnP_relPFiso0p15_M75120.root:ws_templates:hpass_abseta_12_21_pt_35_40_roohistpdf",
          "#import MassTemplatesForTnP_relPFiso0p15_M75120.root:ws_templates:hfail_abseta_12_21_pt_35_40_roohistpdf",
          "Gaussian::res(mass, mean[-0.2], sigma[4e-4])",
          "FCONV::signalPass(mass, hpass_abseta_12_21_pt_35_40_roohistpdf, res)",
          "FCONV::signalFail(mass, hfail_abseta_12_21_pt_35_40_roohistpdf, res)",
          "Exponential::backgroundPass(mass, lp[0,-5,5])",
          "Exponential::backgroundFail(mass, lf[0,-5,5])",
          "efficiency[0.95,0.1,1]",
          "signalFractionInPassing[0.9]",
          ),
       templates_abseta_12_21_pt_40_45 = cms.vstring(
          "#import MassTemplatesForTnP_relPFiso0p15_M75120.root:ws_templates:hpass_abseta_12_21_pt_40_45_roohistpdf",
          "#import MassTemplatesForTnP_relPFiso0p15_M75120.root:ws_templates:hfail_abseta_12_21_pt_40_45_roohistpdf",
          "Gaussian::res(mass, mean[-0.2], sigma[4e-4])",
          "FCONV::signalPass(mass, hpass_abseta_12_21_pt_40_45_roohistpdf, res)",
          "FCONV::signalFail(mass, hfail_abseta_12_21_pt_40_45_roohistpdf, res)",
          "Exponential::backgroundPass(mass, lp[0,-5,5])",
          "Exponential::backgroundFail(mass, lf[0,-5,5])",
          "efficiency[0.95,0.1,1]",
          "signalFractionInPassing[0.9]",
          ),
       templates_abseta_12_21_pt_45_50 = cms.vstring(
          "#import MassTemplatesForTnP_relPFiso0p15_M75120.root:ws_templates:hpass_abseta_12_21_pt_45_50_roohistpdf",
          "#import MassTemplatesForTnP_relPFiso0p15_M75120.root:ws_templates:hfail_abseta_12_21_pt_45_50_roohistpdf",
          "Gaussian::res(mass, mean[-0.2], sigma[4e-4])",
          "FCONV::signalPass(mass, hpass_abseta_12_21_pt_45_50_roohistpdf, res)",
          "FCONV::signalFail(mass, hfail_abseta_12_21_pt_45_50_roohistpdf, res)",
          "Exponential::backgroundPass(mass, lp[0,-5,5])",
          "Exponential::backgroundFail(mass, lf[0,-5,5])",
          "efficiency[0.95,0.1,1]",
          "signalFractionInPassing[0.9]",
          ),
       templates_abseta_12_21_pt_50_80 = cms.vstring(
          "#import MassTemplatesForTnP_relPFiso0p15_M75120.root:ws_templates:hpass_abseta_12_21_pt_50_80_roohistpdf",
          "#import MassTemplatesForTnP_relPFiso0p15_M75120.root:ws_templates:hfail_abseta_12_21_pt_50_80_roohistpdf",
          "Gaussian::res(mass, mean[-0.2], sigma[4e-4])",
          "FCONV::signalPass(mass, hpass_abseta_12_21_pt_50_80_roohistpdf, res)",
          "FCONV::signalFail(mass, hfail_abseta_12_21_pt_50_80_roohistpdf, res)",
          "Exponential::backgroundPass(mass, lp[0,-5,5])",
          "Exponential::backgroundFail(mass, lf[0,-5,5])",
          "efficiency[0.95,0.1,1]",
          "signalFractionInPassing[0.9]",
          ),
       templates_abseta_12_21_pt_80_200 = cms.vstring(
          "#import MassTemplatesForTnP_relPFiso0p15_M75120.root:ws_templates:hpass_abseta_12_21_pt_80_200_roohistpdf",
          "#import MassTemplatesForTnP_relPFiso0p15_M75120.root:ws_templates:hfail_abseta_12_21_pt_80_200_roohistpdf",
          "Gaussian::res(mass, mean[-0.2], sigma[4e-4])",
          "FCONV::signalPass(mass, hpass_abseta_12_21_pt_80_200_roohistpdf, res)",
          "FCONV::signalFail(mass, hfail_abseta_12_21_pt_80_200_roohistpdf, res)",
          "Exponential::backgroundPass(mass, lp[0,-5,5])",
          "Exponential::backgroundFail(mass, lf[0,-5,5])",
          "efficiency[0.95,0.1,1]",
          "signalFractionInPassing[0.9]",
          ),
       templates_abseta_21_24_pt_7_12 = cms.vstring(
          "#import MassTemplatesForTnP_relPFiso0p15_M75120.root:ws_templates:hpass_abseta_21_24_pt_7_12_roohistpdf",
          "#import MassTemplatesForTnP_relPFiso0p15_M75120.root:ws_templates:hfail_abseta_21_24_pt_7_12_roohistpdf",
          "Gaussian::res(mass, mean[-0.2], sigma[4e-4])",
          "FCONV::signalPass(mass, hpass_abseta_21_24_pt_7_12_roohistpdf, res)",
          "FCONV::signalFail(mass, hfail_abseta_21_24_pt_7_12_roohistpdf, res)",
          "Exponential::backgroundPass(mass, lp[0,-5,5])",
          "Exponential::backgroundFail(mass, lf[0,-5,5])",
          "efficiency[0.95,0.1,1]",
          "signalFractionInPassing[0.9]",
          ),
       templates_abseta_21_24_pt_12_15 = cms.vstring(
          "#import MassTemplatesForTnP_relPFiso0p15_M75120.root:ws_templates:hpass_abseta_21_24_pt_12_15_roohistpdf",
          "#import MassTemplatesForTnP_relPFiso0p15_M75120.root:ws_templates:hfail_abseta_21_24_pt_12_15_roohistpdf",
          "Gaussian::res(mass, mean[-0.2], sigma[4e-4])",
          "FCONV::signalPass(mass, hpass_abseta_21_24_pt_12_15_roohistpdf, res)",
          "FCONV::signalFail(mass, hfail_abseta_21_24_pt_12_15_roohistpdf, res)",
          "Exponential::backgroundPass(mass, lp[0,-5,5])",
          "Exponential::backgroundFail(mass, lf[0,-5,5])",
          "efficiency[0.95,0.1,1]",
          "signalFractionInPassing[0.9]",
          ),
       templates_abseta_21_24_pt_15_25 = cms.vstring(
          "#import MassTemplatesForTnP_relPFiso0p15_M75120.root:ws_templates:hpass_abseta_21_24_pt_15_25_roohistpdf",
          "#import MassTemplatesForTnP_relPFiso0p15_M75120.root:ws_templates:hfail_abseta_21_24_pt_15_25_roohistpdf",
          "Gaussian::res(mass, mean[-0.2], sigma[4e-4])",
          "FCONV::signalPass(mass, hpass_abseta_21_24_pt_15_25_roohistpdf, res)",
          "FCONV::signalFail(mass, hfail_abseta_21_24_pt_15_25_roohistpdf, res)",
          "Exponential::backgroundPass(mass, lp[0,-5,5])",
          "Exponential::backgroundFail(mass, lf[0,-5,5])",
          "efficiency[0.95,0.1,1]",
          "signalFractionInPassing[0.9]",
          ),
       templates_abseta_21_24_pt_25_40 = cms.vstring(
          "#import MassTemplatesForTnP_relPFiso0p15_M75120.root:ws_templates:hpass_abseta_21_24_pt_25_40_roohistpdf",
          "#import MassTemplatesForTnP_relPFiso0p15_M75120.root:ws_templates:hfail_abseta_21_24_pt_25_40_roohistpdf",
          "Gaussian::res(mass, mean[-0.2], sigma[4e-4])",
          "FCONV::signalPass(mass, hpass_abseta_21_24_pt_25_40_roohistpdf, res)",
          "FCONV::signalFail(mass, hfail_abseta_21_24_pt_25_40_roohistpdf, res)",
          "Exponential::backgroundPass(mass, lp[0,-5,5])",
          "Exponential::backgroundFail(mass, lf[0,-5,5])",
          "efficiency[0.95,0.1,1]",
          "signalFractionInPassing[0.9]",
          ),
       templates_abseta_21_24_pt_40_80 = cms.vstring(
          "#import MassTemplatesForTnP_relPFiso0p15_M75120.root:ws_templates:hpass_abseta_21_24_pt_40_80_roohistpdf",
          "#import MassTemplatesForTnP_relPFiso0p15_M75120.root:ws_templates:hfail_abseta_21_24_pt_40_80_roohistpdf",
          "Gaussian::res(mass, mean[-0.2], sigma[4e-4])",
          "FCONV::signalPass(mass, hpass_abseta_21_24_pt_40_80_roohistpdf, res)",
          "FCONV::signalFail(mass, hfail_abseta_21_24_pt_40_80_roohistpdf, res)",
          "Exponential::backgroundPass(mass, lp[0,-5,5])",
          "Exponential::backgroundFail(mass, lf[0,-5,5])",
          "efficiency[0.95,0.1,1]",
          "signalFractionInPassing[0.9]",
          ),
       templates_abseta_21_24_pt_80_200 = cms.vstring(
          "#import MassTemplatesForTnP_relPFiso0p15_M75120.root:ws_templates:hpass_abseta_21_24_pt_80_200_roohistpdf",
          "#import MassTemplatesForTnP_relPFiso0p15_M75120.root:ws_templates:hfail_abseta_21_24_pt_80_200_roohistpdf",
          "Gaussian::res(mass, mean[-0.2], sigma[4e-4])",
          "FCONV::signalPass(mass, hpass_abseta_21_24_pt_80_200_roohistpdf, res)",
          "FCONV::signalFail(mass, hfail_abseta_21_24_pt_80_200_roohistpdf, res)",
          "Exponential::backgroundPass(mass, lp[0,-5,5])",
          "Exponential::backgroundFail(mass, lf[0,-5,5])",
          "efficiency[0.95,0.1,1]",
          "signalFractionInPassing[0.9]",
          ),
       templates_abseta_0_12_pt_7_200 = cms.vstring(
          "#import MassTemplatesForTnP_relPFiso0p15_M75120.root:ws_templates:hpass_abseta_0_12_pt_7_200_roohistpdf",
          "#import MassTemplatesForTnP_relPFiso0p15_M75120.root:ws_templates:hfail_abseta_0_12_pt_7_200_roohistpdf",
          "Gaussian::res(mass, mean[-0.2], sigma[4e-4])",
          "FCONV::signalPass(mass, hpass_abseta_0_12_pt_7_200_roohistpdf, res)",
          "FCONV::signalFail(mass, hfail_abseta_0_12_pt_7_200_roohistpdf, res)",
          "Exponential::backgroundPass(mass, lp[0,-5,5])",
          "Exponential::backgroundFail(mass, lf[0,-5,5])",
          "efficiency[0.95,0.1,1]",
          "signalFractionInPassing[0.9]",
          ),
       templates_abseta_12_21_pt_7_200 = cms.vstring(
          "#import MassTemplatesForTnP_relPFiso0p15_M75120.root:ws_templates:hpass_abseta_12_21_pt_7_200_roohistpdf",
          "#import MassTemplatesForTnP_relPFiso0p15_M75120.root:ws_templates:hfail_abseta_12_21_pt_7_200_roohistpdf",
          "Gaussian::res(mass, mean[-0.2], sigma[4e-4])",
          "FCONV::signalPass(mass, hpass_abseta_12_21_pt_7_200_roohistpdf, res)",
          "FCONV::signalFail(mass, hfail_abseta_12_21_pt_7_200_roohistpdf, res)",
          "Exponential::backgroundPass(mass, lp[0,-5,5])",
          "Exponential::backgroundFail(mass, lf[0,-5,5])",
          "efficiency[0.95,0.1,1]",
          "signalFractionInPassing[0.9]",
          ),
       templates_abseta_21_24_pt_7_200 = cms.vstring(
          "#import MassTemplatesForTnP_relPFiso0p15_M75120.root:ws_templates:hpass_abseta_21_24_pt_7_200_roohistpdf",
          "#import MassTemplatesForTnP_relPFiso0p15_M75120.root:ws_templates:hfail_abseta_21_24_pt_7_200_roohistpdf",
          "Gaussian::res(mass, mean[-0.2], sigma[4e-4])",
          "FCONV::signalPass(mass, hpass_abseta_21_24_pt_7_200_roohistpdf, res)",
          "FCONV::signalFail(mass, hfail_abseta_21_24_pt_7_200_roohistpdf, res)",
          "Exponential::backgroundPass(mass, lp[0,-5,5])",
          "Exponential::backgroundFail(mass, lf[0,-5,5])",
          "efficiency[0.95,0.1,1]",
          "signalFractionInPassing[0.9]",
          ),
       templates_abseta_0_3_pt_7_200 = cms.vstring(
          "#import MassTemplatesForTnP_relPFiso0p15_M75120.root:ws_templates:hpass_abseta_0_3_pt_7_200_roohistpdf",
          "#import MassTemplatesForTnP_relPFiso0p15_M75120.root:ws_templates:hfail_abseta_0_3_pt_7_200_roohistpdf",
          "Gaussian::res(mass, mean[-0.2], sigma[4e-4])",
          "FCONV::signalPass(mass, hpass_abseta_0_3_pt_7_200_roohistpdf, res)",
          "FCONV::signalFail(mass, hfail_abseta_0_3_pt_7_200_roohistpdf, res)",
          "Exponential::backgroundPass(mass, lp[0,-5,5])",
          "Exponential::backgroundFail(mass, lf[0,-5,5])",
          "efficiency[0.95,0.1,1]",
          "signalFractionInPassing[0.9]",
          ),
       templates_abseta_3_6_pt_7_200 = cms.vstring(
          "#import MassTemplatesForTnP_relPFiso0p15_M75120.root:ws_templates:hpass_abseta_3_6_pt_7_200_roohistpdf",
          "#import MassTemplatesForTnP_relPFiso0p15_M75120.root:ws_templates:hfail_abseta_3_6_pt_7_200_roohistpdf",
          "Gaussian::res(mass, mean[-0.2], sigma[4e-4])",
          "FCONV::signalPass(mass, hpass_abseta_3_6_pt_7_200_roohistpdf, res)",
          "FCONV::signalFail(mass, hfail_abseta_3_6_pt_7_200_roohistpdf, res)",
          "Exponential::backgroundPass(mass, lp[0,-5,5])",
          "Exponential::backgroundFail(mass, lf[0,-5,5])",
          "efficiency[0.95,0.1,1]",
          "signalFractionInPassing[0.9]",
          ),
       templates_abseta_6_9_pt_7_200 = cms.vstring(
          "#import MassTemplatesForTnP_relPFiso0p15_M75120.root:ws_templates:hpass_abseta_6_9_pt_7_200_roohistpdf",
          "#import MassTemplatesForTnP_relPFiso0p15_M75120.root:ws_templates:hfail_abseta_6_9_pt_7_200_roohistpdf",
          "Gaussian::res(mass, mean[-0.2], sigma[4e-4])",
          "FCONV::signalPass(mass, hpass_abseta_6_9_pt_7_200_roohistpdf, res)",
          "FCONV::signalFail(mass, hfail_abseta_6_9_pt_7_200_roohistpdf, res)",
          "Exponential::backgroundPass(mass, lp[0,-5,5])",
          "Exponential::backgroundFail(mass, lf[0,-5,5])",
          "efficiency[0.95,0.1,1]",
          "signalFractionInPassing[0.9]",
          ),
       templates_abseta_9_12_pt_7_200 = cms.vstring(
          "#import MassTemplatesForTnP_relPFiso0p15_M75120.root:ws_templates:hpass_abseta_9_12_pt_7_200_roohistpdf",
          "#import MassTemplatesForTnP_relPFiso0p15_M75120.root:ws_templates:hfail_abseta_9_12_pt_7_200_roohistpdf",
          "Gaussian::res(mass, mean[-0.2], sigma[4e-4])",
          "FCONV::signalPass(mass, hpass_abseta_9_12_pt_7_200_roohistpdf, res)",
          "FCONV::signalFail(mass, hfail_abseta_9_12_pt_7_200_roohistpdf, res)",
          "Exponential::backgroundPass(mass, lp[0,-5,5])",
          "Exponential::backgroundFail(mass, lf[0,-5,5])",
          "efficiency[0.95,0.1,1]",
          "signalFractionInPassing[0.9]",
          ),
       templates_abseta_12_16_pt_7_200 = cms.vstring(
          "#import MassTemplatesForTnP_relPFiso0p15_M75120.root:ws_templates:hpass_abseta_12_16_pt_7_200_roohistpdf",
          "#import MassTemplatesForTnP_relPFiso0p15_M75120.root:ws_templates:hfail_abseta_12_16_pt_7_200_roohistpdf",
          "Gaussian::res(mass, mean[-0.2], sigma[4e-4])",
          "FCONV::signalPass(mass, hpass_abseta_12_16_pt_7_200_roohistpdf, res)",
          "FCONV::signalFail(mass, hfail_abseta_12_16_pt_7_200_roohistpdf, res)",
          "Exponential::backgroundPass(mass, lp[0,-5,5])",
          "Exponential::backgroundFail(mass, lf[0,-5,5])",
          "efficiency[0.95,0.1,1]",
          "signalFractionInPassing[0.9]",
          ),
       templates_abseta_16_21_pt_7_200 = cms.vstring(
          "#import MassTemplatesForTnP_relPFiso0p15_M75120.root:ws_templates:hpass_abseta_16_21_pt_7_200_roohistpdf",
          "#import MassTemplatesForTnP_relPFiso0p15_M75120.root:ws_templates:hfail_abseta_16_21_pt_7_200_roohistpdf",
          "Gaussian::res(mass, mean[-0.2], sigma[4e-4])",
          "FCONV::signalPass(mass, hpass_abseta_16_21_pt_7_200_roohistpdf, res)",
          "FCONV::signalFail(mass, hfail_abseta_16_21_pt_7_200_roohistpdf, res)",
          "Exponential::backgroundPass(mass, lp[0,-5,5])",
          "Exponential::backgroundFail(mass, lf[0,-5,5])",
          "efficiency[0.95,0.1,1]",
          "signalFractionInPassing[0.9]",
          )
       ),

    # defines a set of efficiency calculations, what PDF to use for fitting and how to bin the data;
    # there will be a separate output directory for each calculation that includes a simultaneous fit, side band subtraction and counting. 
    Efficiencies = cms.PSet(
          cms.PSet(
             Iso_abseta_0_24_pt_7_200 = cms.PSet(
                EfficiencyCategoryAndState = cms.vstring("iso0p15","true"),
                UnbinnedVariables = cms.vstring("mass"),
                BinnedVariables = cms.PSet(
                   pt = cms.vdouble(7, 200),
                   abseta = cms.vdouble(0, 2.4),
                   TightId = cms.vstring("true"),
                   ),
                BinToPDFmap = cms.vstring("templates_abseta_0_24_pt_7_200")
                ),
             Iso_abseta_0_24_pt_7_12 = cms.PSet(
                EfficiencyCategoryAndState = cms.vstring("iso0p15","true"),
                UnbinnedVariables = cms.vstring("mass"),
                BinnedVariables = cms.PSet(
                   pt = cms.vdouble(7, 12),
                   abseta = cms.vdouble(0, 2.4),
                   TightId = cms.vstring("true"),
                   ),
                BinToPDFmap = cms.vstring("templates_abseta_0_24_pt_7_12")
                ),
             Iso_abseta_0_24_pt_12_15 = cms.PSet(
                EfficiencyCategoryAndState = cms.vstring("iso0p15","true"),
                UnbinnedVariables = cms.vstring("mass"),
                BinnedVariables = cms.PSet(
                   pt = cms.vdouble(12, 15),
                   abseta = cms.vdouble(0, 2.4),
                   TightId = cms.vstring("true"),
                   ),
                BinToPDFmap = cms.vstring("templates_abseta_0_24_pt_12_15")
                ),
             Iso_abseta_0_24_pt_15_30 = cms.PSet(
                EfficiencyCategoryAndState = cms.vstring("iso0p15","true"),
                UnbinnedVariables = cms.vstring("mass"),
                BinnedVariables = cms.PSet(
                   pt = cms.vdouble(15, 30),
                   abseta = cms.vdouble(0, 2.4),
                   TightId = cms.vstring("true"),
                   ),
                BinToPDFmap = cms.vstring("templates_abseta_0_24_pt_15_30")
                ),
             Iso_abseta_0_24_pt_30_40 = cms.PSet(
                EfficiencyCategoryAndState = cms.vstring("iso0p15","true"),
                UnbinnedVariables = cms.vstring("mass"),
                BinnedVariables = cms.PSet(
                   pt = cms.vdouble(30, 40),
                   abseta = cms.vdouble(0, 2.4),
                   TightId = cms.vstring("true"),
                   ),
                BinToPDFmap = cms.vstring("templates_abseta_0_24_pt_30_40")
                ),
             Iso_abseta_0_24_pt_40_50 = cms.PSet(
                EfficiencyCategoryAndState = cms.vstring("iso0p15","true"),
                UnbinnedVariables = cms.vstring("mass"),
                BinnedVariables = cms.PSet(
                   pt = cms.vdouble(40, 50),
                   abseta = cms.vdouble(0, 2.4),
                   TightId = cms.vstring("true"),
                   ),
                BinToPDFmap = cms.vstring("templates_abseta_0_24_pt_40_50")
                ),
             Iso_abseta_0_24_pt_50_60 = cms.PSet(
                EfficiencyCategoryAndState = cms.vstring("iso0p15","true"),
                UnbinnedVariables = cms.vstring("mass"),
                BinnedVariables = cms.PSet(
                   pt = cms.vdouble(50, 60),
                   abseta = cms.vdouble(0, 2.4),
                   TightId = cms.vstring("true"),
                   ),
                BinToPDFmap = cms.vstring("templates_abseta_0_24_pt_50_60")
                ),
             Iso_abseta_0_24_pt_60_70 = cms.PSet(
                EfficiencyCategoryAndState = cms.vstring("iso0p15","true"),
                UnbinnedVariables = cms.vstring("mass"),
                BinnedVariables = cms.PSet(
                   pt = cms.vdouble(60, 70),
                   abseta = cms.vdouble(0, 2.4),
                   TightId = cms.vstring("true"),
                   ),
                BinToPDFmap = cms.vstring("templates_abseta_0_24_pt_60_70")
                ),
             Iso_abseta_0_24_pt_70_80 = cms.PSet(
                EfficiencyCategoryAndState = cms.vstring("iso0p15","true"),
                UnbinnedVariables = cms.vstring("mass"),
                BinnedVariables = cms.PSet(
                   pt = cms.vdouble(70, 80),
                   abseta = cms.vdouble(0, 2.4),
                   TightId = cms.vstring("true"),
                   ),
                BinToPDFmap = cms.vstring("templates_abseta_0_24_pt_70_80")
                ),
             Iso_abseta_0_24_pt_80_100 = cms.PSet(
                EfficiencyCategoryAndState = cms.vstring("iso0p15","true"),
                UnbinnedVariables = cms.vstring("mass"),
                BinnedVariables = cms.PSet(
                   pt = cms.vdouble(80, 100),
                   abseta = cms.vdouble(0, 2.4),
                   TightId = cms.vstring("true"),
                   ),
                BinToPDFmap = cms.vstring("templates_abseta_0_24_pt_80_100")
                ),
             Iso_abseta_0_24_pt_100_200 = cms.PSet(
                EfficiencyCategoryAndState = cms.vstring("iso0p15","true"),
                UnbinnedVariables = cms.vstring("mass"),
                BinnedVariables = cms.PSet(
                   pt = cms.vdouble(100, 200),
                   abseta = cms.vdouble(0, 2.4),
                   TightId = cms.vstring("true"),
                   ),
                BinToPDFmap = cms.vstring("templates_abseta_0_24_pt_100_200")
                ),
             Iso_abseta_0_12_pt_7_12 = cms.PSet(
                EfficiencyCategoryAndState = cms.vstring("iso0p15","true"),
                UnbinnedVariables = cms.vstring("mass"),
                BinnedVariables = cms.PSet(
                   pt = cms.vdouble(7, 12),
                   abseta = cms.vdouble(0, 1.2),
                   TightId = cms.vstring("true"),
                   ),
                BinToPDFmap = cms.vstring("templates_abseta_0_12_pt_7_12")
                ),
             Iso_abseta_0_12_pt_12_15 = cms.PSet(
                EfficiencyCategoryAndState = cms.vstring("iso0p15","true"),
                UnbinnedVariables = cms.vstring("mass"),
                BinnedVariables = cms.PSet(
                   pt = cms.vdouble(12, 15),
                   abseta = cms.vdouble(0, 1.2),
                   TightId = cms.vstring("true"),
                   ),
                BinToPDFmap = cms.vstring("templates_abseta_0_12_pt_12_15")
                ),
             Iso_abseta_0_12_pt_15_25 = cms.PSet(
                EfficiencyCategoryAndState = cms.vstring("iso0p15","true"),
                UnbinnedVariables = cms.vstring("mass"),
                BinnedVariables = cms.PSet(
                   pt = cms.vdouble(15, 25),
                   abseta = cms.vdouble(0, 1.2),
                   TightId = cms.vstring("true"),
                   ),
                BinToPDFmap = cms.vstring("templates_abseta_0_12_pt_15_25")
                ),
             Iso_abseta_0_12_pt_25_30 = cms.PSet(
                EfficiencyCategoryAndState = cms.vstring("iso0p15","true"),
                UnbinnedVariables = cms.vstring("mass"),
                BinnedVariables = cms.PSet(
                   pt = cms.vdouble(25, 30),
                   abseta = cms.vdouble(0, 1.2),
                   TightId = cms.vstring("true"),
                   ),
                BinToPDFmap = cms.vstring("templates_abseta_0_12_pt_25_30")
                ),
             Iso_abseta_0_12_pt_30_35 = cms.PSet(
                EfficiencyCategoryAndState = cms.vstring("iso0p15","true"),
                UnbinnedVariables = cms.vstring("mass"),
                BinnedVariables = cms.PSet(
                   pt = cms.vdouble(30, 35),
                   abseta = cms.vdouble(0, 1.2),
                   TightId = cms.vstring("true"),
                   ),
                BinToPDFmap = cms.vstring("templates_abseta_0_12_pt_30_35")
                ),
             Iso_abseta_0_12_pt_35_40 = cms.PSet(
                EfficiencyCategoryAndState = cms.vstring("iso0p15","true"),
                UnbinnedVariables = cms.vstring("mass"),
                BinnedVariables = cms.PSet(
                   pt = cms.vdouble(35, 40),
                   abseta = cms.vdouble(0, 1.2),
                   TightId = cms.vstring("true"),
                   ),
                BinToPDFmap = cms.vstring("templates_abseta_0_12_pt_35_40")
                ),
             Iso_abseta_0_12_pt_40_45 = cms.PSet(
                EfficiencyCategoryAndState = cms.vstring("iso0p15","true"),
                UnbinnedVariables = cms.vstring("mass"),
                BinnedVariables = cms.PSet(
                   pt = cms.vdouble(40, 45),
                   abseta = cms.vdouble(0, 1.2),
                   TightId = cms.vstring("true"),
                   ),
                BinToPDFmap = cms.vstring("templates_abseta_0_12_pt_40_45")
                ),
             Iso_abseta_0_12_pt_45_50 = cms.PSet(
                EfficiencyCategoryAndState = cms.vstring("iso0p15","true"),
                UnbinnedVariables = cms.vstring("mass"),
                BinnedVariables = cms.PSet(
                   pt = cms.vdouble(45, 50),
                   abseta = cms.vdouble(0, 1.2),
                   TightId = cms.vstring("true"),
                   ),
                BinToPDFmap = cms.vstring("templates_abseta_0_12_pt_45_50")
                ),
             Iso_abseta_0_12_pt_50_80 = cms.PSet(
                EfficiencyCategoryAndState = cms.vstring("iso0p15","true"),
                UnbinnedVariables = cms.vstring("mass"),
                BinnedVariables = cms.PSet(
                   pt = cms.vdouble(50, 80),
                   abseta = cms.vdouble(0, 1.2),
                   TightId = cms.vstring("true"),
                   ),
                BinToPDFmap = cms.vstring("templates_abseta_0_12_pt_50_80")
                ),
             Iso_abseta_0_12_pt_80_200 = cms.PSet(
                EfficiencyCategoryAndState = cms.vstring("iso0p15","true"),
                UnbinnedVariables = cms.vstring("mass"),
                BinnedVariables = cms.PSet(
                   pt = cms.vdouble(80, 200),
                   abseta = cms.vdouble(0, 1.2),
                   TightId = cms.vstring("true"),
                   ),
                BinToPDFmap = cms.vstring("templates_abseta_0_12_pt_80_200")
                ),
             Iso_abseta_12_21_pt_7_12 = cms.PSet(
                EfficiencyCategoryAndState = cms.vstring("iso0p15","true"),
                UnbinnedVariables = cms.vstring("mass"),
                BinnedVariables = cms.PSet(
                   pt = cms.vdouble(7, 12),
                   abseta = cms.vdouble(1.2, 2.1),
                   TightId = cms.vstring("true"),
                   ),
                BinToPDFmap = cms.vstring("templates_abseta_12_21_pt_7_12")
                ),
             Iso_abseta_12_21_pt_12_15 = cms.PSet(
                EfficiencyCategoryAndState = cms.vstring("iso0p15","true"),
                UnbinnedVariables = cms.vstring("mass"),
                BinnedVariables = cms.PSet(
                   pt = cms.vdouble(12, 15),
                   abseta = cms.vdouble(1.2, 2.1),
                   TightId = cms.vstring("true"),
                   ),
                BinToPDFmap = cms.vstring("templates_abseta_12_21_pt_12_15")
                ),
             Iso_abseta_12_21_pt_15_25 = cms.PSet(
                EfficiencyCategoryAndState = cms.vstring("iso0p15","true"),
                UnbinnedVariables = cms.vstring("mass"),
                BinnedVariables = cms.PSet(
                   pt = cms.vdouble(15, 25),
                   abseta = cms.vdouble(1.2, 2.1),
                   TightId = cms.vstring("true"),
                   ),
                BinToPDFmap = cms.vstring("templates_abseta_12_21_pt_15_25")
                ),
             Iso_abseta_12_21_pt_25_30 = cms.PSet(
                EfficiencyCategoryAndState = cms.vstring("iso0p15","true"),
                UnbinnedVariables = cms.vstring("mass"),
                BinnedVariables = cms.PSet(
                   pt = cms.vdouble(25, 30),
                   abseta = cms.vdouble(1.2, 2.1),
                   TightId = cms.vstring("true"),
                   ),
                BinToPDFmap = cms.vstring("templates_abseta_12_21_pt_25_30")
                ),
             Iso_abseta_12_21_pt_30_35 = cms.PSet(
                EfficiencyCategoryAndState = cms.vstring("iso0p15","true"),
                UnbinnedVariables = cms.vstring("mass"),
                BinnedVariables = cms.PSet(
                   pt = cms.vdouble(30, 35),
                   abseta = cms.vdouble(1.2, 2.1),
                   TightId = cms.vstring("true"),
                   ),
                BinToPDFmap = cms.vstring("templates_abseta_12_21_pt_30_35")
                ),
             Iso_abseta_12_21_pt_35_40 = cms.PSet(
                EfficiencyCategoryAndState = cms.vstring("iso0p15","true"),
                UnbinnedVariables = cms.vstring("mass"),
                BinnedVariables = cms.PSet(
                   pt = cms.vdouble(35, 40),
                   abseta = cms.vdouble(1.2, 2.1),
                   TightId = cms.vstring("true"),
                   ),
                BinToPDFmap = cms.vstring("templates_abseta_12_21_pt_35_40")
                ),
             Iso_abseta_12_21_pt_40_45 = cms.PSet(
                EfficiencyCategoryAndState = cms.vstring("iso0p15","true"),
                UnbinnedVariables = cms.vstring("mass"),
                BinnedVariables = cms.PSet(
                   pt = cms.vdouble(40, 45),
                   abseta = cms.vdouble(1.2, 2.1),
                   TightId = cms.vstring("true"),
                   ),
                BinToPDFmap = cms.vstring("templates_abseta_12_21_pt_40_45")
                ),
             Iso_abseta_12_21_pt_45_50 = cms.PSet(
                EfficiencyCategoryAndState = cms.vstring("iso0p15","true"),
                UnbinnedVariables = cms.vstring("mass"),
                BinnedVariables = cms.PSet(
                   pt = cms.vdouble(45, 50),
                   abseta = cms.vdouble(1.2, 2.1),
                   TightId = cms.vstring("true"),
                   ),
                BinToPDFmap = cms.vstring("templates_abseta_12_21_pt_45_50")
                ),
             Iso_abseta_12_21_pt_50_80 = cms.PSet(
                EfficiencyCategoryAndState = cms.vstring("iso0p15","true"),
                UnbinnedVariables = cms.vstring("mass"),
                BinnedVariables = cms.PSet(
                   pt = cms.vdouble(50, 80),
                   abseta = cms.vdouble(1.2, 2.1),
                   TightId = cms.vstring("true"),
                   ),
                BinToPDFmap = cms.vstring("templates_abseta_12_21_pt_50_80")
                ),
             Iso_abseta_12_21_pt_80_200 = cms.PSet(
                EfficiencyCategoryAndState = cms.vstring("iso0p15","true"),
                UnbinnedVariables = cms.vstring("mass"),
                BinnedVariables = cms.PSet(
                   pt = cms.vdouble(80, 200),
                   abseta = cms.vdouble(1.2, 2.1),
                   TightId = cms.vstring("true"),
                   ),
                BinToPDFmap = cms.vstring("templates_abseta_12_21_pt_80_200")
                ),
             Iso_abseta_21_24_pt_7_12 = cms.PSet(
                EfficiencyCategoryAndState = cms.vstring("iso0p15","true"),
                UnbinnedVariables = cms.vstring("mass"),
                BinnedVariables = cms.PSet(
                   pt = cms.vdouble(7, 12),
                   abseta = cms.vdouble(2.1, 2.4),
                   TightId = cms.vstring("true"),
                   ),
                BinToPDFmap = cms.vstring("templates_abseta_21_24_pt_7_12")
                ),
             Iso_abseta_21_24_pt_12_15 = cms.PSet(
                EfficiencyCategoryAndState = cms.vstring("iso0p15","true"),
                UnbinnedVariables = cms.vstring("mass"),
                BinnedVariables = cms.PSet(
                   pt = cms.vdouble(12, 15),
                   abseta = cms.vdouble(2.1, 2.4),
                   TightId = cms.vstring("true"),
                   ),
                BinToPDFmap = cms.vstring("templates_abseta_21_24_pt_12_15")
                ),
             Iso_abseta_21_24_pt_15_25 = cms.PSet(
                EfficiencyCategoryAndState = cms.vstring("iso0p15","true"),
                UnbinnedVariables = cms.vstring("mass"),
                BinnedVariables = cms.PSet(
                   pt = cms.vdouble(15, 25),
                   abseta = cms.vdouble(2.1, 2.4),
                   TightId = cms.vstring("true"),
                   ),
                BinToPDFmap = cms.vstring("templates_abseta_21_24_pt_15_25")
                ),
             Iso_abseta_21_24_pt_25_40 = cms.PSet(
                EfficiencyCategoryAndState = cms.vstring("iso0p15","true"),
                UnbinnedVariables = cms.vstring("mass"),
                BinnedVariables = cms.PSet(
                   pt = cms.vdouble(25, 40),
                   abseta = cms.vdouble(2.1, 2.4),
                   TightId = cms.vstring("true"),
                   ),
                BinToPDFmap = cms.vstring("templates_abseta_21_24_pt_25_40")
                ),
             Iso_abseta_21_24_pt_40_80 = cms.PSet(
                EfficiencyCategoryAndState = cms.vstring("iso0p15","true"),
                UnbinnedVariables = cms.vstring("mass"),
                BinnedVariables = cms.PSet(
                   pt = cms.vdouble(40, 80),
                   abseta = cms.vdouble(2.1, 2.4),
                   TightId = cms.vstring("true"),
                   ),
                BinToPDFmap = cms.vstring("templates_abseta_21_24_pt_40_80")
                ),
             Iso_abseta_21_24_pt_80_200 = cms.PSet(
                EfficiencyCategoryAndState = cms.vstring("iso0p15","true"),
                UnbinnedVariables = cms.vstring("mass"),
                BinnedVariables = cms.PSet(
                   pt = cms.vdouble(80, 200),
                   abseta = cms.vdouble(2.1, 2.4),
                   TightId = cms.vstring("true"),
                   ),
                BinToPDFmap = cms.vstring("templates_abseta_21_24_pt_80_200")
                ),
             Iso_abseta_0_12_pt_7_200 = cms.PSet(
                EfficiencyCategoryAndState = cms.vstring("iso0p15","true"),
                UnbinnedVariables = cms.vstring("mass"),
                BinnedVariables = cms.PSet(
                   pt = cms.vdouble(7, 200),
                   abseta = cms.vdouble(0, 1.2),
                   TightId = cms.vstring("true"),
                   ),
                BinToPDFmap = cms.vstring("templates_abseta_0_12_pt_7_200")
                ),
             Iso_abseta_12_21_pt_7_200 = cms.PSet(
                EfficiencyCategoryAndState = cms.vstring("iso0p15","true"),
                UnbinnedVariables = cms.vstring("mass"),
                BinnedVariables = cms.PSet(
                   pt = cms.vdouble(7, 200),
                   abseta = cms.vdouble(1.2, 2.1),
                   TightId = cms.vstring("true"),
                   ),
                BinToPDFmap = cms.vstring("templates_abseta_12_21_pt_7_200")
                ),
             Iso_abseta_21_24_pt_7_200 = cms.PSet(
                EfficiencyCategoryAndState = cms.vstring("iso0p15","true"),
                UnbinnedVariables = cms.vstring("mass"),
                BinnedVariables = cms.PSet(
                   pt = cms.vdouble(7, 200),
                   abseta = cms.vdouble(2.1, 2.4),
                   TightId = cms.vstring("true"),
                   ),
                BinToPDFmap = cms.vstring("templates_abseta_21_24_pt_7_200")
                ),
             Iso_abseta_0_3_pt_7_200 = cms.PSet(
                EfficiencyCategoryAndState = cms.vstring("iso0p15","true"),
                UnbinnedVariables = cms.vstring("mass"),
                BinnedVariables = cms.PSet(
                   pt = cms.vdouble(7, 200),
                   abseta = cms.vdouble(0, 0.3),
                   TightId = cms.vstring("true"),
                   ),
                BinToPDFmap = cms.vstring("templates_abseta_0_3_pt_7_200")
                ),
             Iso_eta_0_3_pt_7_200 = cms.PSet(
                EfficiencyCategoryAndState = cms.vstring("iso0p15","true"),
                UnbinnedVariables = cms.vstring("mass"),
                BinnedVariables = cms.PSet(
                   pt = cms.vdouble(7, 200),
                   eta = cms.vdouble(0, 0.3),
                   TightId = cms.vstring("true"),
                   ),
                BinToPDFmap = cms.vstring("templates_abseta_0_3_pt_7_200")
                ),
             Iso_eta_3_6_pt_7_200 = cms.PSet(
                EfficiencyCategoryAndState = cms.vstring("iso0p15","true"),
                UnbinnedVariables = cms.vstring("mass"),
                BinnedVariables = cms.PSet(
                   pt = cms.vdouble(7, 200),
                   eta = cms.vdouble(0.3, 0.6),
                   TightId = cms.vstring("true"),
                   ),
                BinToPDFmap = cms.vstring("templates_abseta_3_6_pt_7_200")
                ),
             Iso_eta_6_9_pt_7_200 = cms.PSet(
                EfficiencyCategoryAndState = cms.vstring("iso0p15","true"),
                UnbinnedVariables = cms.vstring("mass"),
                BinnedVariables = cms.PSet(
                   pt = cms.vdouble(7, 200),
                   eta = cms.vdouble(0.6, 0.9),
                   TightId = cms.vstring("true"),
                   ),
                BinToPDFmap = cms.vstring("templates_abseta_6_9_pt_7_200")
                ),
             Iso_eta_9_12_pt_7_200 = cms.PSet(
                EfficiencyCategoryAndState = cms.vstring("iso0p15","true"),
                UnbinnedVariables = cms.vstring("mass"),
                BinnedVariables = cms.PSet(
                   pt = cms.vdouble(7, 200),
                   eta = cms.vdouble(0.9, 1.2),
                   TightId = cms.vstring("true"),
                   ),
                BinToPDFmap = cms.vstring("templates_abseta_9_12_pt_7_200")
                ),
             Iso_eta_12_16_pt_7_200 = cms.PSet(
                EfficiencyCategoryAndState = cms.vstring("iso0p15","true"),
                UnbinnedVariables = cms.vstring("mass"),
                BinnedVariables = cms.PSet(
                   pt = cms.vdouble(7, 200),
                   eta = cms.vdouble(1.2, 1.6),
                   TightId = cms.vstring("true"),
                   ),
                BinToPDFmap = cms.vstring("templates_abseta_12_16_pt_7_200")
                ),
             Iso_eta_16_21_pt_7_200 = cms.PSet(
                EfficiencyCategoryAndState = cms.vstring("iso0p15","true"),
                UnbinnedVariables = cms.vstring("mass"),
                BinnedVariables = cms.PSet(
                   pt = cms.vdouble(7, 200),
                   eta = cms.vdouble(1.6, 2.1),
                   TightId = cms.vstring("true"),
                   ),
                BinToPDFmap = cms.vstring("templates_abseta_16_21_pt_7_200")
                ),
             Iso_eta_21_24_pt_7_200 = cms.PSet(
                EfficiencyCategoryAndState = cms.vstring("iso0p15","true"),
                UnbinnedVariables = cms.vstring("mass"),
                BinnedVariables = cms.PSet(
                   pt = cms.vdouble(7, 200),
                   eta = cms.vdouble(2.1, 2.4),
                   TightId = cms.vstring("true"),
                   ),
                BinToPDFmap = cms.vstring("templates_abseta_21_24_pt_7_200")
                ),
             Iso_eta_m24_m21_pt_7_200 = cms.PSet(
                EfficiencyCategoryAndState = cms.vstring("iso0p15","true"),
                UnbinnedVariables = cms.vstring("mass"),
                BinnedVariables = cms.PSet(
                   pt = cms.vdouble(7, 200),
                   eta = cms.vdouble(-2.4, -2.1),
                   TightId = cms.vstring("true"),
                   ),
                BinToPDFmap = cms.vstring("templates_abseta_21_24_pt_7_200")
                ),
             Iso_eta_m21_m16_pt_7_200 = cms.PSet(
                EfficiencyCategoryAndState = cms.vstring("iso0p15","true"),
                UnbinnedVariables = cms.vstring("mass"),
                BinnedVariables = cms.PSet(
                   pt = cms.vdouble(7, 200),
                   eta = cms.vdouble(-2.1, -1.6),
                   TightId = cms.vstring("true"),
                   ),
                BinToPDFmap = cms.vstring("templates_abseta_16_21_pt_7_200")
                ),
             Iso_eta_m16_m12_pt_7_200 = cms.PSet(
                EfficiencyCategoryAndState = cms.vstring("iso0p15","true"),
                UnbinnedVariables = cms.vstring("mass"),
                BinnedVariables = cms.PSet(
                   pt = cms.vdouble(7, 200),
                   eta = cms.vdouble(-1.6, -1.2),
                   TightId = cms.vstring("true"),
                   ),
                BinToPDFmap = cms.vstring("templates_abseta_12_16_pt_7_200")
                ),
             Iso_eta_m12_m9_pt_7_200 = cms.PSet(
                EfficiencyCategoryAndState = cms.vstring("iso0p15","true"),
                UnbinnedVariables = cms.vstring("mass"),
                BinnedVariables = cms.PSet(
                   pt = cms.vdouble(7, 200),
                   eta = cms.vdouble(-1.2, -0.9),
                   TightId = cms.vstring("true"),
                   ),
                BinToPDFmap = cms.vstring("templates_abseta_9_12_pt_7_200")
                ),
             Iso_eta_m9_m6_pt_7_200 = cms.PSet(
                EfficiencyCategoryAndState = cms.vstring("iso0p15","true"),
                UnbinnedVariables = cms.vstring("mass"),
                BinnedVariables = cms.PSet(
                   pt = cms.vdouble(7, 200),
                   eta = cms.vdouble(-0.9, -0.6),
                   TightId = cms.vstring("true"),
                   ),
                BinToPDFmap = cms.vstring("templates_abseta_6_9_pt_7_200")
                ),
             Iso_eta_m6_m3_pt_7_200 = cms.PSet(
                EfficiencyCategoryAndState = cms.vstring("iso0p15","true"),
                UnbinnedVariables = cms.vstring("mass"),
                BinnedVariables = cms.PSet(
                   pt = cms.vdouble(7, 200),
                   eta = cms.vdouble(-0.6, -0.3),
                   TightId = cms.vstring("true"),
                   ),
                BinToPDFmap = cms.vstring("templates_abseta_3_6_pt_7_200")
                ),
             Iso_eta_m3_m0_pt_7_200 = cms.PSet(
                EfficiencyCategoryAndState = cms.vstring("iso0p15","true"),
                UnbinnedVariables = cms.vstring("mass"),
                BinnedVariables = cms.PSet(
                   pt = cms.vdouble(7, 200),
                   eta = cms.vdouble(-0.3, -0),
                   TightId = cms.vstring("true"),
                   ),
                BinToPDFmap = cms.vstring("templates_abseta_0_3_pt_7_200")
                )
             ),
          )
)

process.fitness = cms.Path(
    process.TagProbeFitTreeAnalyzer
)
