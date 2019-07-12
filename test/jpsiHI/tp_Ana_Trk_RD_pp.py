import FWCore.ParameterSet.Config as cms

process = cms.Process("TagProbe")

process.load('FWCore.MessageService.MessageLogger_cfi')

process.source = cms.Source("EmptySource")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1) )    

PDFName = "triGaussPlusPol2"

process.TagProbeFitTreeAnalyzer = cms.EDAnalyzer("TagProbeFitTreeAnalyzer",
    # IO parameters:
    #InputFileNames = cms.vstring("root://cms-xrd-global.cern.ch//store/group/phys_heavyions/dileptons/TNPTagAndProbe2015/Data2015/pp502TeV/TTrees/tnpJPsi_Data_pp5TeV_AOD.root"),
    InputFileNames = cms.vstring("file:/home/llr/cms/falmagne/tuples/pp17/TnP/data/tnpJpsi_pp5TeVRun2017G_PromptReco_20190415_SingleMuTnP_and_SingleMu_NoDuplicates_wAddedFlags.root"),
    InputDirectoryName = cms.string("tpTreeSta"),
    InputTreeName = cms.string("fitter_tree"),
    #numbrer of CPUs to use for fitting
    OutputFileName = cms.string("file:./tnp_fitOutput_Tracking_data_pp_triGaussPlusPol2_narrowMrange.root"),#file:/afs/cern.ch/work/v/vabdulla/private/TnP/Trk/tnp_Ana_Trk_RD_pp_etapT_220217_ValHits.root"), #wPsi2Spol2
    NumCPU = cms.uint32(16),
    # specifies wether to save the RooWorkspace containing the data for each bin and
    # the pdf object with the initial and final state snapshots
    SaveWorkspace = cms.bool(False),
    binsForMassPlots = cms.uint32(50),
    binnedFit = cms.bool(True),
    binsForFit = cms.uint32(90),
    WeightVariable = cms.string("weight"),
    
    # defines all the real variables of the probes available in the input tree; can be used to select a subset of the probes
    Variables = cms.PSet(
        mass             = cms.vstring("Tag-Probe Mass", "2", "5", "GeV/c^{2}"),
        pt               = cms.vstring("Probe p_{T}", "0.0", "1000", "GeV/c"),
        p                = cms.vstring("Probe p", "0", "1000", "GeV/c"),
        eta              = cms.vstring("Probe #eta", "-2.4", "2.4", ""),
        abseta           = cms.vstring("Probe |#eta|", "0", "2.5", ""),
        staQoverP        = cms.vstring("Probe Q/p", "-200", "200", ""),
        staQoverPerror   = cms.vstring("Probe Q/p error", "0", "650", ""),
        staValidStations = cms.vstring("Probe STA valid stations", "0", "15", ""),
        staNumValidHits  = cms.vstring("Probe Valid Hits", "0", "60", ""),
        
        tag_pt           = cms.vstring("Tag p_{T}", "0.0", "1000", "GeV/c"),
        tag_eta          = cms.vstring("Tag #eta", "-2.4", "2.4", ""),
        tag_abseta       = cms.vstring("Tag |#eta|", "0", "2.5", ""),
        tag_nVertices    = cms.vstring("Tag nVtx", "0", "30", ""),
        pair_pt          = cms.vstring("Pair p_{T}", "0.0", "1000", "GeV/c"),
        pair_absy        = cms.vstring("Pair |Y|", "-2.4", "2.4", ""),
        pair_y           = cms.vstring("Pair Y", "0", "2.5", ""),
        weight           = cms.vstring("weight","0","1000",""),
    ),
    # defines all the Flags on which one can test the probe against (if true, is 'pass', if false is 'failed')
    Categories = cms.PSet(
        Glb        = cms.vstring("Glb", "dummy[true=1,false=0]"),
        tk         = cms.vstring("tk", "dummy[true=1,false=0]"),
        outerValidHits          = cms.vstring("outerValidHits", "dummy[true=1,false=0]"),
        staAtLeastTwoStations   = cms.vstring("staAtLeastTwoStations", "dummy[true=1,false=0]"),
        InAcceptance_2018_Tight = cms.vstring("InAcceptance_2018_Tight","dummy[true=1,false=0]"),
        InAcceptance_2018_Loose = cms.vstring("InAcceptance_2018_Loose","dummy[true=1,false=0]"),
    ),

    # defines all the PDFs that will be available for the efficiency calculations; uses RooFit's "factory" syntax;
    # each pdf needs to define "signal", "backgroundPass", "backgroundFail" pdfs, "efficiency[0.9,0,1]" and "signalFractionInPassing[0.9]" are used for initial values
    PDFs = cms.PSet(
        triGaussPlusPol3 = cms.vstring(
            "Gaussian::signal1(mass, m1[3.1,3.0,3.2], sigma1[0.1,0.06,0.25])",
            "Gaussian::signal2(mass, m1, sigma2[0.2,0.08,0.33])",
            "SUM::signalJpsi(vFrac[0.9,0.0,1.0]*signal1, signal2)",
            "Gaussian::signal3(mass, 3.686, sigma3[0.11,0.1,0.26])", #m2[3.69,3.55,3.8]
            "SUM::signal(vFracJpsi[0.97,0.92,0.99]*signalJpsi, signal3)",
            "Chebychev::backgroundPass(mass, {zP[0.0,-1.0,1.0], zP2[0.0,-1.0,1.0], zP3[0,-1.0,1.0]})", ### good
            "Chebychev::backgroundFail(mass, {zF[-0.0,-1.0,1.0], zF2[0.0,-1.0,1.0], zF3[0.01,-0.14,0.14]})", ### good
            "efficiency[0.9,0,1]",
            "signalFractionInPassing[0.9]"
        ),

        triGaussPlusPol2 = cms.vstring(
            "Gaussian::signal1(mass, mean[3.1,3.0,3.2], sigma1[0.1,0.06,0.25])",
            "Gaussian::signal2(mass, mean, sigma2[0.2,0.08,0.33])",
            "SUM::signalJpsi(vFrac[0.9,0.0,1.0]*signal1, signal2)",
            "Gaussian::signal3(mass, 3.686, sigma3[0.11,0.1,0.26])", #m2[3.69,3.55,3.8]
            "SUM::signal(vFracJpsi[0.97,0.92,0.99]*signalJpsi, signal3)",
            "Chebychev::backgroundPass(mass, {cPass[0,-1.0,1.0], cPass2[0,-1.0,1.0]})",
            "Chebychev::backgroundFail(mass, {cFail[0,-1.0,1.0], cFail2[0,-1.0,1.0]})",
            "efficiency[0.9,0,1]",
            "signalFractionInPassing[0.9]"
        ),
        
        VoigtGaussPlusPol3= cms.vstring(
            "Voigtian::signal1(mass, mean[3.1,3.0,3.2],width[0.05,0.04,0.15], sigma1[0.15, 0.03, 0.25])",
            "Gaussian::signal2(mass, mean, sigma2[0.2,0.1,0.34])",
            "SUM::signal(vFrac[0.5,0,1]*signal1, signal2)",
            "Chebychev::backgroundPass(mass, {zP[0.0,-1.0,1.0], zP2[0.0,-1.0,1.0], zP3[0,-1.0,1.0]})", ### good
            "Chebychev::backgroundFail(mass, {zF[-0.0,-1.0,1.0], zF2[0.0,-1.0,1.0], zF3[0.01,-0.14,0.14]})", ### good
            "efficiency[0.9,0,1]",
            "signalFractionInPassing[0.9]"
        ),

        VoigtGaussPlusPol2= cms.vstring(
            "Voigtian::signal1(mass, mean[3.1,3.0,3.2],width[0.05,0.04,0.15], sigma1[0.15, 0.03, 0.25])",
            "Gaussian::signal2(mass, mean, sigma2[0.2,0.1,0.34])",
            "SUM::signal(vFrac[0.5,0,1]*signal1, signal2)",
            "Chebychev::backgroundPass(mass, {zP[0.0,-1.0,1.0], zP2[0.0,-1.0,1.0]})", ### good
            "Chebychev::backgroundFail(mass, {zF[-0.0,-1.0,1.0], zF2[0.0,-1.0,1.0]})", ### good
            "efficiency[0.9,0,1]",
            "signalFractionInPassing[0.9]"
        ),

        twoGaussPlusPol2 = cms.vstring(
            "Gaussian::signal1(mass, mean[3.1,3.0,3.2], sigma1[0.1, 0.07, 0.3])",
            "Gaussian::signal2(mass, mean, sigma2[0.2,0.1,0.4])",
            "SUM::signal(vFrac[0.5,0,1]*signal1, signal2)",
            "Chebychev::backgroundPass(mass, {cPass[0,-1.0,1.0], cPass2[0,-1.0,1.0]})",
            "Chebychev::backgroundFail(mass, {cFail[0,-1.0,1.0], cFail2[0,-1.0,1.0]})",
            "efficiency[0.9,0,1]",
            "signalFractionInPassing[0.9]"
        ),

    ),
   # defines a set of efficiency calculations, what PDF to use for fitting and how to bin the data;
    # there will be a separate output directory for each calculation that includes a simultaneous fit, side band subtraction and counting. 
    Efficiencies = cms.PSet(
            #the name of the parameter set becomes the name of the directory
            # for multiple passing flags in EfficiencyCategorAndState = cms.vstring("flag1","state","flag2","state",...),
            Trk_1bin = cms.PSet(
                EfficiencyCategoryAndState = cms.vstring("Glb","true"),
                UnbinnedVariables = cms.vstring("mass"),
                BinnedVariables = cms.PSet(
                    pt  = cms.vdouble(1.5,30),
                    eta = cms.vdouble(-2.4,2.4),
                    InAcceptance_2018_Tight = cms.vstring("true"),
                    staAtLeastTwoStations = cms.vstring("true"),
                ),
                BinToPDFmap = cms.vstring(PDFName)
            ),
            Trk_pt = cms.PSet(
                EfficiencyCategoryAndState = cms.vstring("Glb","true"),
                UnbinnedVariables = cms.vstring("mass"),
                BinnedVariables = cms.PSet(
                    #pt = cms.vdouble(0, 3.5, 7., 10.5, 30.0),
                    pt = cms.vdouble(1.5, 2.5, 3.5, 4.8, 6.5, 8.5, 12, 30),
                    eta = cms.vdouble(-2.4,2.4),
                    InAcceptance_2018_Tight = cms.vstring("true"),
                    staAtLeastTwoStations = cms.vstring("true"),
                ),
                BinToPDFmap = cms.vstring(PDFName)
            ),
            Trk_etadep = cms.PSet(
                EfficiencyCategoryAndState = cms.vstring("Glb","true"),
                UnbinnedVariables = cms.vstring("mass"),
                BinnedVariables = cms.PSet(
                    #eta = cms.vdouble(-2.4,-1.6,-1.2,-0.9,0.9,1.2,1.6,2.4),
                    eta = cms.vdouble(-2.4,-1.8,-1.2,-0.9,-0.6,-0.2,0.2,0.6,0.9,1.2,1.8,2.4),
                    pt = cms.vdouble(1.5,30.0),
                    InAcceptance_2018_Tight = cms.vstring("true"),
                    staAtLeastTwoStations = cms.vstring("true"),
                ),
                BinToPDFmap = cms.vstring(PDFName)
            ),
            Trk_absetadep = cms.PSet(
                EfficiencyCategoryAndState = cms.vstring("Glb","true"),
                UnbinnedVariables = cms.vstring("mass"),
                BinnedVariables = cms.PSet(
                    #eta = cms.vdouble(-2.4,-1.6,-1.2,-0.9,0.9,1.2,1.6,2.4),
                    abseta = cms.vdouble(0.,0.3,0.6,0.9,1.2,1.8,2.4),
                    pt = cms.vdouble(1.5,30.0),
                    InAcceptance_2018_Tight = cms.vstring("true"),
                    staAtLeastTwoStations = cms.vstring("true"),
                ),
                BinToPDFmap = cms.vstring(PDFName)
            ),
            Trk_nVtx = cms.PSet(
                EfficiencyCategoryAndState = cms.vstring("Glb","true"),
                UnbinnedVariables = cms.vstring("mass"),
                BinnedVariables = cms.PSet(
                    #eta = cms.vdouble(-2.4,-1.6,-1.2,-0.9,0.9,1.2,1.6,2.4),
                    #abseta = cms.vdouble(0.,0.3,0.6,0.9,1.2,1.8,2.4),
                    tag_nVertices = cms.vdouble(0.5,1.5,2.5,3.5,4.5,5.5,7.5,29.5),
                    pt = cms.vdouble(1.5,30.0),
                    InAcceptance_2018_Tight = cms.vstring("true"),
                    staAtLeastTwoStations = cms.vstring("true"),
                ),
                BinToPDFmap = cms.vstring(PDFName)
            ),
        
    )
)

'''
            Trk_1binSeg = cms.PSet(
                EfficiencyCategoryAndState = cms.vstring("Glb","true"),
                UnbinnedVariables = cms.vstring("mass"),
                BinnedVariables = cms.PSet(
                    pt  = cms.vdouble(1.2,30),
                    eta = cms.vdouble(-2.4,2.4),
                    InAcceptance_2018_Tight = cms.vstring("true"),
                    staNumValidHits= cms.vdouble(1,60),
                ),
                BinToPDFmap = cms.vstring(PDFName)
            ),
            Trk_ptSeg = cms.PSet(
                EfficiencyCategoryAndState = cms.vstring("Glb","true"),
                UnbinnedVariables = cms.vstring("mass"),
                BinnedVariables = cms.PSet(
                    #pt = cms.vdouble(0, 3.5, 7., 10.5, 30.0),
                    pt = cms.vdouble(1.2, 2.5, 3.5, 4.8, 6.5, 8.5, 12, 30),
                    eta = cms.vdouble(-2.4,2.4),
                    InAcceptance_2018_Tight = cms.vstring("true"),
                    staNumValidHits= cms.vdouble(1,60),
                ),
                BinToPDFmap = cms.vstring(PDFName)
            ),
            Trk_etadepSeg = cms.PSet(
                EfficiencyCategoryAndState = cms.vstring("Glb","true"),
                UnbinnedVariables = cms.vstring("mass"),
                BinnedVariables = cms.PSet(
                    #eta = cms.vdouble(-2.4,-1.6,-1.2,-0.9,0.9,1.2,1.6,2.4),
                    eta = cms.vdouble(-2.4,-1.8,-1.2,-0.9,-0.6,-0.2,0.2,0.6,0.9,1.2,1.8,2.4),
                    pt = cms.vdouble(1.2,30.0),
                    InAcceptance_2018_Tight = cms.vstring("true"),
                    staNumValidHits= cms.vdouble(1,60),
                ),
                BinToPDFmap = cms.vstring(PDFName)
            ),
'''
process.fitness = cms.Path(
    process.TagProbeFitTreeAnalyzer
)

