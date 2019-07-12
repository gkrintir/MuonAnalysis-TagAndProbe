import FWCore.ParameterSet.Config as cms

process = cms.Process("TagProbe")

process.load('FWCore.MessageService.MessageLogger_cfi')

process.source = cms.Source("EmptySource")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1) )    

PDFName = "CBGPlusPol1"

process.TagProbeFitTreeAnalyzer = cms.EDAnalyzer("TagProbeFitTreeAnalyzer",
    # IO parameters:
    #InputFileNames = cms.vstring("root://cms-xrd-global.cern.ch//store/group/phys_heavyions/dileptons/TNPTagAndProbe2015/Data2015/pp502TeV/TTrees/tnpJPsi_Data_pp5TeV_AOD.root"),
    InputFileNames = cms.vstring("file:/home/llr/cms/falmagne/tuples/pp17/TnP/data/tnpJpsi_pp5TeVRun2017G_PromptReco_20190415_SingleMuTnP_and_SingleMu_NoDuplicates_wAddedFlags.root"),
    InputDirectoryName = cms.string("tpTree"),
    InputTreeName = cms.string("fitter_tree"),
    OutputFileName = cms.string("file:tnp_fitOutput_MuonIDTrigger_data_pp_pol1_narrowMrange.root"),
    #numbrer of CPUs to use for fitting
    NumCPU = cms.uint32(16),
    # specifies whether to save the RooWorkspace containing the data for each bin and
    # the pdf object with the initial and final state snapshots
    binnedFit = cms.bool(True),
    binsForFit = cms.uint32(90),
    binsForMassPlots = cms.uint32(50),
    SaveWorkspace = cms.bool(False),
    
    # defines all the real variables of the probes available in the input tree and intended for use in the efficiencies
    Variables = cms.PSet(
                         mass             = cms.vstring("Tag-Probe Mass", "2.8", "3.4", "GeV/c^{2}"),
                         pt               = cms.vstring("Probe p_{T}", "0.0", "1000", "GeV/c"),
                         eta              = cms.vstring("Probe #eta", "-2.4", "2.4", ""),
                         abseta           = cms.vstring("Probe |#eta|", "0", "2.5", ""),
    ),
    # defines all the discrete variables of the probes available in the input tree and intended for use in the efficiency calculations
    Categories = cms.PSet(
                          Glb = cms.vstring("Glb", "dummy[true=1,false=0]"),
                          SoftIdWithoutDxyz = cms.vstring("SoftIdWithoutDxyz", "dummy[true=1,false=0]"),
                          HybridSoftId_2018 = cms.vstring("HybridSoftId_2018", "dummy[true=1,false=0]"),
                          HLTL1_DoubleMu0_v0   = cms.vstring("HLTL1_DoubleMu0_v0", "dummy[true=1,false=0]"),
                          HLTL1_DoubleMu0_v2   = cms.vstring("HLTL1_DoubleMu0_v2", "dummy[true=1,false=0]"),
                          HLTL2_DoubleMu0_v0   = cms.vstring("HLTL2_DoubleMu0_v0", "dummy[true=1,false=0]"),
                          HLTL3_DoubleMu0_v0   = cms.vstring("HLTL3_DoubleMu0_v0", "dummy[true=1,false=0]"),
                          passedDZ_SOFT = cms.vstring("passedDZ_SOFT","dummy[true=1,false=0]"),
                          passedDXY_SOFT = cms.vstring("passedDXY_SOFT","dummy[true=1,false=0]"),
                          InAcceptance_2018_Tight = cms.vstring("InAcceptance_2018_Tight","dummy[true=1,false=0]"),
                          InAcceptance_2018_Loose = cms.vstring("InAcceptance_2018_Loose","dummy[true=1,false=0]"),
                          #dxyPVdzmin = cms.vstring("dxyPVdzmin","dummy[true=1,false=0]"),
                          #dxyzPVCuts = cms.vstring("dxyzPVCuts","dummy[true=1,false=0]"),
    ),

    # defines all the PDFs that will be available for the efficiency calculations; uses RooFit's "factory" syntax;
    # each pdf needs to define "signal", "backgroundPass", "backgroundFail" pdfs, "efficiency[0.9,0,1]" and "signalFractionInPassing[0.9]" are used for initial values  
    PDFs = cms.PSet(
        CBPlusPol2 = cms.vstring(
            "CBShape::signal1(mass, mean[3.1,3.0,3.2], sigma1[0.025, 0.008, 0.08], alpha[2.1, 0.9, 50.0], n[3.0, 0.5, 50.])",
            "Chebychev::backgroundPass(mass, {cPass[0.,-1.1,1.1], cPass2[0.,-1.1,1.1]})",
            "Chebychev::backgroundFail(mass, {cFail[0.,-1.1,1.1], cFail2[0.,-1.1,1.1]})",
            "efficiency[0.9,0,1]",
            "signalFractionInPassing[0.9]"
        ),
        
        CBPlusPol1 = cms.vstring(
            "CBShape::signal(mass, mean[3.1,3.02,3.15], sigma[0.025, 0.011, 0.07], alpha[2.1, 0.2, 50.0], n[3.0, 2., 50.])",
            "Chebychev::backgroundPass(mass, {cPass[0,-3.0,3.0]})",
            "Chebychev::backgroundFail(mass, {cFail[0,-3.0,3.0]})",
            "efficiency[0.9,0.0,1.0]",
            "signalFractionInPassing[0.9]"            
        ),
        
        CBGPlusPol1 = cms.vstring(
            "CBShape::signal1(mass, mean[3.1,3.02,3.15], sigma1[0.025, 0.014, 0.07], alpha[2.1, 0.2, 50.0], n[3.0, 2., 50.])",
            "Gaussian::signal2(mass, mean, sigma2[0.04, 0.012, 0.3])",
            "SUM::signal(vFrac[0.6,0.0,1.0]*signal1, signal2)",
            "Chebychev::backgroundPass(mass, {cPass[0,-3.0,3.0]})",
            "Chebychev::backgroundFail(mass, {cFail[0,-3.0,3.0]})",
            "efficiency[0.9,0.0,1.0]",
            "signalFractionInPassing[0.9]"            
        ),
        
        CBGPlusPol2 = cms.vstring(
            "CBShape::signal1(mass, mean[3.1,3.02,3.15], sigma1[0.025, 0.014, 0.07], alpha[2.1, 0.2, 50.0], n[3.0, 2., 50.])",
            "Gaussian::signal2(mass, mean, sigma2[0.04, 0.012, 0.3])",
            "SUM::signal(vFrac[0.6,0.0,1.0]*signal1, signal2)",
            "Chebychev::backgroundPass(mass, {cPass[0,-2.0,2.0], cPass2[0,-2.0,2.0]})",
            "Chebychev::backgroundFail(mass, {cFail[0,-2.0,2.0], cFail2[0,-2.0,2.0]})",
            "efficiency[0.9,0.3,1.0]",
            "signalFractionInPassing[0.9]"            
        ),
    ),
    # defines a set of efficiency calculations, what PDF to use for fitting and how to bin the data;
    # there will be a separate output directory for each calculation that includes a simultaneous fit, side band subtraction and counting. 
     Efficiencies = cms.PSet(
         MuIdTrg_1bin = cms.PSet(
             EfficiencyCategoryAndState = cms.vstring("SoftIdWithoutDxyz","true","HLTL1_DoubleMu0_v0","true","HLTL1_DoubleMu0_v2","true","passedDXY_SOFT","true","passedDZ_SOFT","true"),
             UnbinnedVariables = cms.vstring("mass"),
             BinnedVariables = cms.PSet(
                pt = cms.vdouble(1.5, 30),
                eta = cms.vdouble(-2.4, 2.4),
                InAcceptance_2018_Tight = cms.vstring("true"),
                Glb = cms.vstring("true"),
             ),
             BinToPDFmap = cms.vstring(PDFName)
         ),

        MuIdTrg_abseta00_12 = cms.PSet(
            EfficiencyCategoryAndState = cms.vstring("SoftIdWithoutDxyz","true","HLTL1_DoubleMu0_v0","true","HLTL1_DoubleMu0_v2","true","passedDXY_SOFT","true","passedDZ_SOFT","true"),
            UnbinnedVariables = cms.vstring("mass"),
            BinnedVariables = cms.PSet(
                #pt = cms.vdouble(3.5, 4, 4.5, 5, 5.5, 6, 6.5, 7, 7.5, 8, 8.5, 9, 9.5, 10.5, 11.5, 13, 16, 30), for 1500 evt
                pt = cms.vdouble(3.5, 3.75, 4, 4.25, 4.5, 4.75, 5, 5.25, 5.5, 5.75, 6, 6.5, 7, 7.5, 8, 9.25, 10.5, 12.25, 14, 16, 18, 24, 30),         
                #pt = cms.vdouble(3.5, 4, 4.5, 5, 5.5, 6, 7, 8, 10.5, 14, 18, 30),
                abseta = cms.vdouble(0, 1.2),
                InAcceptance_2018_Tight = cms.vstring("true"),
                Glb = cms.vstring("true"),
            ),
             BinToPDFmap = cms.vstring(PDFName)
         ),
         
         MuIdTrg_abseta12_18 = cms.PSet(
             EfficiencyCategoryAndState = cms.vstring("SoftIdWithoutDxyz","true","HLTL1_DoubleMu0_v0","true","HLTL1_DoubleMu0_v2","true","passedDXY_SOFT","true","passedDZ_SOFT","true"),
             UnbinnedVariables = cms.vstring("mass"),
             BinnedVariables = cms.PSet(
                #pt = cms.vdouble(2.75, 3.5, 4, 4.5, 5, 5.5, 6, 6.5, 7, 8, 9.5, 30),
                #pt = cms.vdouble(2.06, 2.4, 3, 3.5, 4, 4.5, 5, 6, 7, 9, 14, 18, 30),
                pt = cms.vdouble(2.06, 2.5, 2.75, 3, 3.25, 3.5, 3.75, 4, 4.5, 5, 5.5, 6, 7, 8.5, 10, 12, 14.5, 19, 30),
                abseta = cms.vdouble(1.2,1.8),
                InAcceptance_2018_Tight = cms.vstring("true"),
                Glb = cms.vstring("true"),
             ),
             BinToPDFmap = cms.vstring(PDFName)
         ),
         
         MuIdTrg_abseta18_21 = cms.PSet(
             EfficiencyCategoryAndState = cms.vstring("SoftIdWithoutDxyz","true","HLTL1_DoubleMu0_v0","true","HLTL1_DoubleMu0_v2","true","passedDXY_SOFT","true","passedDZ_SOFT","true"),
             UnbinnedVariables = cms.vstring("mass"),
             BinnedVariables = cms.PSet(
                 #pt = cms.vdouble(1.8, 2.5, 3, 3.5, 4, 4.5, 5, 5.5, 6, 6.5, 7.5, 8.5, 10.5, 30),
                 #pt = cms.vdouble(1.5, 1.85, 2.2, 2.5, 3, 3.5, 4, 4.5, 5, 6.5, 8.5, 11, 14, 30),
                 pt = cms.vdouble(1.5, 1.9, 2.2, 2.5, 2.8, 3.1, 3.4, 4, 5, 6, 8, 11, 15, 30),
                 abseta = cms.vdouble(1.8,2.1),
                 InAcceptance_2018_Tight = cms.vstring("true"),
                 Glb = cms.vstring("true"),
             ),
             BinToPDFmap = cms.vstring(PDFName)
         ),
         
         MuIdTrg_abseta21_24 = cms.PSet(
             EfficiencyCategoryAndState = cms.vstring("SoftIdWithoutDxyz","true","HLTL1_DoubleMu0_v0","true","HLTL1_DoubleMu0_v2","true","passedDXY_SOFT","true","passedDZ_SOFT","true"),
             UnbinnedVariables = cms.vstring("mass"),
             BinnedVariables = cms.PSet(
                #pt = cms.vdouble(1.8, 2, 2.5, 3, 3.5, 4, 4.5, 5, 6, 7.5, 30),
                #pt = cms.vdouble(1.5, 1.85, 2.2, 2.5, 3, 3.5, 4, 4.5, 5, 6.5, 8.5, 11, 14, 30),
                pt = cms.vdouble(1.5, 1.9, 2.3, 2.7, 3, 3.5, 4.25, 5, 6, 7, 8.5, 13, 30),
                abseta = cms.vdouble(2.1,2.4),
                InAcceptance_2018_Tight = cms.vstring("true"),
                Glb = cms.vstring("true"),
             ),
             BinToPDFmap = cms.vstring(PDFName)
         ),
         
         MuIdTrg_etadep = cms.PSet(
             EfficiencyCategoryAndState = cms.vstring("SoftIdWithoutDxyz","true","HLTL1_DoubleMu0_v0","true","HLTL1_DoubleMu0_v2","true","passedDXY_SOFT","true","passedDZ_SOFT","true"),
             UnbinnedVariables = cms.vstring("mass"),
             BinnedVariables = cms.PSet(
                 pt = cms.vdouble(1.5, 30),
                 eta = cms.vdouble(-2.4,-2.1,-1.8,-1.2,0,1.2,1.8,2.1,2.4),
                 InAcceptance_2018_Tight = cms.vstring("true"),
                 Glb = cms.vstring("true"),
             ),
             BinToPDFmap = cms.vstring(PDFName)
         ),
         
         MuIdTrg_absetadep = cms.PSet(
             EfficiencyCategoryAndState = cms.vstring("SoftIdWithoutDxyz","true","HLTL1_DoubleMu0_v0","true","HLTL1_DoubleMu0_v2","true","passedDXY_SOFT","true","passedDZ_SOFT","true"),
             UnbinnedVariables = cms.vstring("mass"),
             BinnedVariables = cms.PSet(
                 pt = cms.vdouble(1.5, 30),
                 abseta = cms.vdouble(0,1.2,1.8,2.1,2.4),
                 InAcceptance_2018_Tight = cms.vstring("true"),
                 Glb = cms.vstring("true"),
             ),
             BinToPDFmap = cms.vstring(PDFName)
         ),

         MuIdTrg_absetadep_HighPt = cms.PSet(
             EfficiencyCategoryAndState = cms.vstring("SoftIdWithoutDxyz","true","HLTL1_DoubleMu0_v0","true","HLTL1_DoubleMu0_v2","true","passedDXY_SOFT","true","passedDZ_SOFT","true"),
             UnbinnedVariables = cms.vstring("mass"),
             BinnedVariables = cms.PSet(
                 pt = cms.vdouble(3, 30),
                 abseta = cms.vdouble(0,1.2,1.8,2.1,2.4),
                 InAcceptance_2018_Tight = cms.vstring("true"),
                 Glb = cms.vstring("true"),
             ),
             BinToPDFmap = cms.vstring(PDFName)
         ),
         
         #MuIdTrg_absetadep_ext = cms.PSet(
          #   EfficiencyCategoryAndState = cms.vstring("SoftIdWithoutDxyz","true","HLTL1_DoubleMu0_v0","true","HLTL1_DoubleMu0_v2","true","passedDXY_SOFT","true","passedDZ_SOFT","true"),
           #  UnbinnedVariables = cms.vstring("mass"),
            # BinnedVariables = cms.PSet(
             #    pt = cms.vdouble(1.8, 30),
              #   abseta = cms.vdouble(0,1.2,2.1,2.4),
              #Glb = cms.vstring("true"),
             #),
             #BinToPDFmap = cms.vstring(PDFName)
         #),
     )
)

process.fitness = cms.Path(
    process.TagProbeFitTreeAnalyzer
)
