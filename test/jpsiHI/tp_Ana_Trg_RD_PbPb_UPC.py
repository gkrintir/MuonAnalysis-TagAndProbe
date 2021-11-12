import FWCore.ParameterSet.Config as cms

process = cms.Process("TagProbe")

process.load('FWCore.MessageService.MessageLogger_cfi')

process.source = cms.Source("EmptySource")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1) )    

PDFName = "cbPlusPol1"

process.TagProbeFitTreeAnalyzer = cms.EDAnalyzer("TagProbeFitTreeAnalyzer",
    # IO parameters:
    InputFileNames = cms.vstring("file:/eos/cms/store/group/phys_top/gkrintir/TagAndProbe2015/TNP_HIUPCTnP_HIRun2015_PromptReco_v1_AOD_20211109/HIForward/crab_TNP_HIUPCTnP_HIRun2015_PromptReco_v1_AOD_20211109/211109_231518/merged.root"),
    InputDirectoryName = cms.string("tpTree"),
    InputTreeName = cms.string("fitter_tree"),
    OutputFileName = cms.string("tnp_Ana_RD_PbPb_Trg_AllUPC.root"),
    #numbrer of CPUs to use for fitting
    NumCPU = cms.uint32(25),
    # specifies whether to save the RooWorkspace containing the data for each bin and
    # the pdf object with the initial and final state snapshots
    binnedFit = cms.bool(False),
    #binsForFit = cms.uint32(30),
    binsForMassPlots = cms.uint32(50),
    SaveWorkspace = cms.bool(False),
    
    # defines all the real variables of the probes available in the input tree and intended for use in the efficiencies
    Variables = cms.PSet(
                         mass             = cms.vstring("Tag-Probe Mass", "2.6", "3.5", "GeV/c^{2}"),   # mass range syst:  2.8-3.4
                         pt               = cms.vstring("Probe p_{T}", "0.0", "1000", "GeV/c"),
                         eta              = cms.vstring("Probe #eta", "-2.4", "2.4", ""),
                         abseta           = cms.vstring("Probe |#eta|", "0", "2.5", ""),
                         tag_hiBin        = cms.vstring("Centrality", "0", "200", ""),
    ),
    # defines all the discrete variables of the probes available in the input tree and intended for use in the efficiency calculations
    Categories = cms.PSet(
                          HybridSoftHI = cms.vstring("HybridSoftHI", "dummy[true=1,false=0]"),
                          L1Filter  = cms.vstring("L1Filter", "dummy[true=1,false=0]"),
                          L1Seed    = cms.vstring("L1Seed", "dummy[true=1,false=0]"),
                          HLTL1v0   = cms.vstring("HLTL1v0", "dummy[true=1,false=0]"),
                          HLTL1v1   = cms.vstring("HLTL1v1", "dummy[true=1,false=0]"),
                          HLTL1v2   = cms.vstring("HLTL1v2", "dummy[true=1,false=0]"),
                          dxyzPVCuts = cms.vstring("dxyzPVCuts","dummy[true=1,false=0]"),
    ),

    # defines all the PDFs that will be available for the efficiency calculations; uses RooFit's "factory" syntax;
    # each pdf needs to define "signal", "backgroundPass", "backgroundFail" pdfs, "efficiency[0.9,0,1]" and "signalFractionInPassing[0.9]" are used for initial values  
    PDFs = cms.PSet(
        #nominal:
       cbPlusPol1 = cms.vstring(
        "CBShape::signal(mass, mean[3.08,3.00,3.2], sigma[0.03, 0.01, 0.10], alpha[1.85, 0.1, 50], n[1.7, 0.2, 50])",
        "Chebychev::backgroundPass(mass, {cPass[0.,-2,2]})",
        "Chebychev::backgroundFail(mass, {cFail[0.,-2,2]})",
        "efficiency[0.9,0,1]",
        "signalFractionInPassing[0.9]"
      ), 
        #background syst:
        cbPlusPol2 = cms.vstring(
        "CBShape::signal(mass, mean[3.08,3.00,3.2], sigma[0.03, 0.01, 0.10], alpha[1.85, 0.1, 50], n[1.7, 0.2, 50])",
        "Chebychev::backgroundPass(mass, {cPass[0.,-2,2], cPass2[0.,-2,2]})",
        "Chebychev::backgroundFail(mass, {cFail[0.,-2,2], cFail2[0.,-2,2]})",
        "efficiency[0.9,0,1]",
        "signalFractionInPassing[0.9]"
      ),
        #signal syst:
      cbGausPlusPol1 = cms.vstring(
        "CBShape::signal1(mass, mean[3.08,3.00,3.2], sigma1[0.03, 0.01, 0.10], alpha[1.85, 0.1, 50], n[1.7, 0.2, 50])",
        "RooFormulaVar::sigma2('@0*@1',{fracS[1.8,1.2,2.4],sigma1})",
        "Gaussian::signal2(mass, mean, sigma2)",
        "SUM::signal(frac[0.8,0.1,1.]*signal1,signal2)",
        "Chebychev::backgroundPass(mass, {cPass[0.,-2,2]})",
        "Chebychev::backgroundFail(mass, {cFail[0.,-2,2]})",
        "efficiency[0.9,0,1]",
        "signalFractionInPassing[0.9]"
      ),
    ),
    # defines a set of efficiency calculations, what PDF to use for fitting and how to bin the data;
    # there will be a separate output directory for each calculation that includes a simultaneous fit, side band subtraction and counting. 
   Efficiencies = cms.PSet(
        MuIdTrg_1bin = cms.PSet(
            EfficiencyCategoryAndState = cms.vstring("HLTL1v0","true","L1Seed","true"),
            UnbinnedVariables = cms.vstring("mass"),
            BinnedVariables = cms.PSet(
                pt = cms.vdouble(1.2, 30),
                eta = cms.vdouble(-2.4, 2.4),
                HybridSoftHI = cms.vstring("true"),
                dxyzPVCuts = cms.vstring("true"),
            ),
            BinToPDFmap = cms.vstring(PDFName)
        ),
        
        MuIdTrg_abseta00_11 = cms.PSet(
            EfficiencyCategoryAndState = cms.vstring("HLTL1v0","true","L1Seed","true"),
            UnbinnedVariables = cms.vstring("mass"),
            BinnedVariables = cms.PSet(
                pt = cms.vdouble(3.3,4.7,30),#1.8, 3, 3.5, 5.5, 8, 30.),
                abseta = cms.vdouble(0, 1.1),
                HybridSoftHI = cms.vstring("true"),
                dxyzPVCuts = cms.vstring("true"),
            ),
            BinToPDFmap = cms.vstring(PDFName)
        ),
        MuIdTrg_abseta11_16 = cms.PSet(
            EfficiencyCategoryAndState = cms.vstring("HLTL1v0","true","L1Seed","true"),
            UnbinnedVariables = cms.vstring("mass"),
            BinnedVariables = cms.PSet(
                pt = cms.vdouble(2.7,3.3,4.3,5.3,30),#1.8, 3, 3.5, 5.5, 8, 30),
                abseta = cms.vdouble(1.1,1.6),
                HybridSoftHI = cms.vstring("true"),
                dxyzPVCuts = cms.vstring("true"),
            ),
            BinToPDFmap = cms.vstring(PDFName)
        ),
          MuIdTrg_abseta16_24 = cms.PSet(
            EfficiencyCategoryAndState = cms.vstring("HLTL1v0","true","L1Seed","true"),
            UnbinnedVariables = cms.vstring("mass"),
            BinnedVariables = cms.PSet(
                pt = cms.vdouble(1.2,1.45,2.2,2.7,30),#1.8, 3, 3.5, 5.5, 8, 30),
                abseta = cms.vdouble(1.6,2.4),
                HybridSoftHI = cms.vstring("true"),
                dxyzPVCuts = cms.vstring("true"),
            ),
            BinToPDFmap = cms.vstring(PDFName)
        ),
         MuIdTrg_absetadep = cms.PSet(
            EfficiencyCategoryAndState = cms.vstring("HLTL1v0","true","L1Seed","true"),
            UnbinnedVariables = cms.vstring("mass"),
            BinnedVariables = cms.PSet(
                pt = cms.vdouble(1.2, 30),
                abseta = cms.vdouble(0,1.1,1.6,2.4),
                HybridSoftHI = cms.vstring("true"),
                dxyzPVCuts = cms.vstring("true"),
            ),
            BinToPDFmap = cms.vstring(PDFName)
        ), 

      MuIdTrg_etadep = cms.PSet(
            EfficiencyCategoryAndState = cms.vstring("HLTL1v0","true","L1Seed","true"),
            UnbinnedVariables = cms.vstring("mass"),
            BinnedVariables = cms.PSet(
                pt = cms.vdouble(1.8, 30),
                eta = cms.vdouble(-2.4,-1.8,0,1.8,2.4),
                HybridSoftHI = cms.vstring("true"),
                dxyzPVCuts = cms.vstring("true"),
            ),
            BinToPDFmap = cms.vstring(PDFName)
        ),

            MuIdTrg_centdep = cms.PSet(
                EfficiencyCategoryAndState = cms.vstring("HLTL1v0","true","L1Seed","true"),
                UnbinnedVariables = cms.vstring("mass"),
                BinnedVariables = cms.PSet(
                    pt = cms.vdouble(1.8, 30),
                    eta = cms.vdouble(-2.4,2.4),
                    tag_hiBin = cms.vdouble(0,80,100,200),
                ),
                BinToPDFmap = cms.vstring(PDFName)
            ),
    )
)

process.fitness = cms.Path(
    process.TagProbeFitTreeAnalyzer
)
