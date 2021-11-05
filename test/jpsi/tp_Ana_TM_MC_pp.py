import FWCore.ParameterSet.Config as cms

process = cms.Process("TagProbe")

process.load('FWCore.MessageService.MessageLogger_cfi')

process.source = cms.Source("EmptySource")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1) )    

PDFName = "twoGaussPlusPol2"

process.TagProbeFitTreeAnalyzer = cms.EDAnalyzer("TagProbeFitTreeAnalyzer",
    # IO parameters:
    #InputFileNames = cms.vstring("root://cms-xrd-global.cern.ch//store/group/phys_heavyions/dileptons/TNPTagAndProbe2015/Data2015/pp502TeV/TTrees/tnpJPsi_Data_pp5TeV_AOD.root"),
    InputFileNames = cms.vstring("file:/home/llr/cms/falmagne/tuples/pp17/TnP/TNP_JpsiMM_5p02TeV_TuneCUETP8M1_RunIIpp5Spring18DR-94X_AODSIM_20190415/tnpJpsi_mc_pp5TeV_PromptJpsi_wAddedFlags.root"),
    InputDirectoryName = cms.string("tpTreeTrk"),
    InputTreeName = cms.string("fitter_tree"),
    OutputFileName = cms.string("file:./tnp_fitOutput_TM_MC_pp_pol2.root"),
    NumCPU = cms.uint32(16),
    # specifies wether to save the RooWorkspace containing the data for each bin and
    # the pdf object with the initial and final state snapshots
    SaveWorkspace = cms.bool(False),
    binsForMassPlots = cms.uint32(50),
    binnedFit = cms.bool(True),
    binsForFit = cms.uint32(90),
    #WeightVariable = cms.string("weight"),
    
    # defines all the real variables of the probes available in the input tree and intended for use in the efficiencies
    Variables = cms.PSet(
        mass = cms.vstring("Tag-Probe Mass", "2.6", "3.5", "GeV/c^{2}"),
        pt = cms.vstring("Probe p_{T}", "0", "1000", "GeV/c"),
        pair_pt = cms.vstring("Dimuon p_{T}", "0", "1000", "GeV/c"),
        eta = cms.vstring("Probe #eta", "-2.4", "2.4", ""),
        abseta = cms.vstring("Probe |#eta|", "0", "2.4", ""),
    ),
    # defines all the discrete variables of the probes available in the input tree and intended for use in the efficiency calculations
    Categories = cms.PSet(
        TM = cms.vstring("TM", "dummy[true=1,false=0]"),
        InAcceptance_2018_Tight = cms.vstring("InAcceptance_2018_Tight","dummy[true=1,false=0]"),
        InAcceptance_2018_Loose = cms.vstring("InAcceptance_2018_Loose","dummy[true=1,false=0]"),
    ),

    # defines all the PDFs that will be available for the efficiency calculations; uses RooFit's "factory" syntax;
    # each pdf needs to define "signal", "backgroundPass", "backgroundFail" pdfs, "efficiency[0.9,0,1]" and "signalFractionInPassing[0.9]" are used for initial values  
    PDFs = cms.PSet(
        twoGaussPlusPol2 = cms.vstring(
            "Gaussian::signal1(mass, mean[3.1,3.0,3.2], sigma1[0.025, 0.0017, 0.08])",
            "Gaussian::signal2(mass, mean, sigma2[0.05, 0.018, 0.12])",
            "SUM::signal(vFrac[0.8,0,1]*signal1, signal2)",
            "Chebychev::backgroundPass(mass, {cPass[0,-1.0,1.0], cPass2[0,-0.1,0.1]})",
            "Chebychev::backgroundFail(mass, {cFail[0,-1.0,1.0], cFail2[0.02,-0.18,0.18]})",
            "efficiency[0.99,0.7,1.0]",
            "signalFractionInPassing[0.9]"
             ),
        twoGaussPlusPol1 = cms.vstring(
            "Gaussian::signal1(mass, mean[3.1,3.0,3.2], sigma1[0.025, 0.018, 0.08])",
            "Gaussian::signal2(mass, mean, sigma2[0.04, 0.012, 0.25])",
            "SUM::signal(vFrac[0.8,0,1]*signal1, signal2)",
            "Chebychev::backgroundPass(mass, {cPass[0,-2.0,2.0]})",
            "Chebychev::backgroundFail(mass, {cFail[0,-2.0,2.0]})",
            "efficiency[0.9,0.0,1.0]",
            "signalFractionInPassing[0.9]"
             ),
    ),
    # defines a set of efficiency calculations, what PDF to use for fitting and how to bin the data;
    # there will be a separate output directory for each calculation that includes a simultaneous fit, side band subtraction and counting. 
    Efficiencies = cms.PSet(
        #the name of the parameter set becomes the name of the directory
        TM_abseta00_12 = cms.PSet(
            EfficiencyCategoryAndState = cms.vstring("TM","true"),
            UnbinnedVariables = cms.vstring("mass"),
            BinnedVariables = cms.PSet(
                #pt = cms.vdouble(3.5, 3.65, 3.8, 4, 4.25, 4.5, 5, 5.5, 6, 6.5, 7, 7.5, 8, 8.5, 9, 9.5, 10.5, 11.5, 13, 16, 30),
                pt = cms.vdouble(3.4, 3.8, 4.4, 5.2, 7, 30),
                pair_pt = cms.vdouble(2.5, 30),
                abseta = cms.vdouble(0.0, 1.2), 
                InAcceptance_2018_Loose = cms.vstring("true"),
            ),
            BinToPDFmap = cms.vstring(PDFName)
        ),
        TM_abseta12_18 = cms.PSet(
            EfficiencyCategoryAndState = cms.vstring("TM","true"),
            UnbinnedVariables = cms.vstring("mass"),
            BinnedVariables = cms.PSet(
                #pt = cms.vdouble(2.4, 2.55, 2.7, 2.85, 3, 3.25, 3.5, 4, 4.5, 5, 5.5, 6, 6.5, 7, 8, 9.5, 15, 30), 
                pt = cms.vdouble(1.75, 2.75, 4, 20),
                #pt = cms.vdouble(1.75, 2.1, 2.4, 2.7, 3, 3.25, 3.5, 3.75, 4, 4.25, 4.5, 4.75, 5, 5.5, 6, 6.5, 7, 7.5, 8, 8.5, 9, 11.5, 14, 22, 30),
                pair_pt = cms.vdouble(2.5,30),
                abseta = cms.vdouble(1.2, 1.8),
                InAcceptance_2018_Loose = cms.vstring("true"),
            ),
            BinToPDFmap = cms.vstring(PDFName)
        ),
        TM_abseta18_24 = cms.PSet(
            EfficiencyCategoryAndState = cms.vstring("TM","true"),
            UnbinnedVariables = cms.vstring("mass"),
            BinnedVariables = cms.PSet(
                #pt = cms.vdouble(1.8, 2.5, 3, 3.5, 4, 4.5, 5, 6, 7, 10, 30),
                pt = cms.vdouble(1.2, 2.5, 3.7, 20),
                #pt = cms.vdouble(1.33, 1.6, 1.9, 2.2, 2.5, 2.75, 3, 3.25, 3.5, 3.75, 4, 4.25, 4.5, 4.75, 5, 5.5, 6, 6.5, 7, 8.5, 10, 20, 30),
                pair_pt = cms.vdouble(2.5,30),
                abseta = cms.vdouble(1.8, 2.4),
                InAcceptance_2018_Loose = cms.vstring("true"),
            ),
            BinToPDFmap = cms.vstring(PDFName)
        ),
        TM_1bin = cms.PSet(
            EfficiencyCategoryAndState = cms.vstring("TM","true"),
            UnbinnedVariables = cms.vstring("mass"),
            BinnedVariables = cms.PSet(
                pt = cms.vdouble(1.2,30.),
                eta = cms.vdouble(-2.4,2.4),
                InAcceptance_2018_Loose = cms.vstring("true"),
            ),
            BinToPDFmap = cms.vstring(PDFName)
        ),
        TM_etadep = cms.PSet(
            EfficiencyCategoryAndState = cms.vstring("TM","true"),
            UnbinnedVariables = cms.vstring("mass"),
            BinnedVariables = cms.PSet(
                #eta = cms.vdouble(-2.4,-2.1,-1.8,-1.2,0,1.2,1.8,2.1,2.4),
                eta = cms.vdouble(-2.4,-1.8,-1.2,0,1.2,1.8,2.4),
                pair_pt = cms.vdouble(2.5,30),
                pt = cms.vdouble(1.2,30.),
                InAcceptance_2018_Loose = cms.vstring("true"),
            ),
            BinToPDFmap = cms.vstring(PDFName)
        ),
        TM_absetadep = cms.PSet(
            EfficiencyCategoryAndState = cms.vstring("TM","true"),
            UnbinnedVariables = cms.vstring("mass"),
            BinnedVariables = cms.PSet(
                abseta = cms.vdouble(0,1.2,1.8,2.4),
                pair_pt = cms.vdouble(2.5,30),
                pt = cms.vdouble(1.2,30),
                InAcceptance_2018_Loose = cms.vstring("true"),
            ),
            BinToPDFmap = cms.vstring(PDFName)
        ),

    )
)

'''
        TM_Trg_abseta21_24 = cms.PSet(
            EfficiencyCategoryAndState = cms.vstring("TM","true"),
            UnbinnedVariables = cms.vstring("mass"),
            BinnedVariables = cms.PSet(
                #pt = cms.vdouble(1.8, 2.5, 3, 3.5, 4, 4.5, 5, 6, 7, 10, 30),
                pt = cms.vdouble(1.2, 1.5, 1.8, 2.15, 2.5, 2.75, 3, 3.25, 3.5, 3.75, 4, 4.25, 4.5, 4.75, 5, 5.5, 6, 6.5, 7, 8.5, 10, 20, 30),
                pair_pt = cms.vdouble(2.5,30),
                abseta = cms.vdouble(2.1, 2.4),
            ),
            BinToPDFmap = cms.vstring(PDFName)
        ),
'''


process.fitness = cms.Path(
    process.TagProbeFitTreeAnalyzer
)
