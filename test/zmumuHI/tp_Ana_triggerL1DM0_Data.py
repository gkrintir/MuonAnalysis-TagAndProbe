import FWCore.ParameterSet.Config as cms

process = cms.Process("TagProbe")
process.load('FWCore.MessageService.MessageLogger_cfi')
process.source = cms.Source("EmptySource")
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1) )    
PDFName = "VoigtExp"





process.TagProbeFitTreeAnalyzer = cms.EDAnalyzer("TagProbeFitTreeAnalyzer",
    # IO parameters:
    InputFileNames = cms.vstring("file:datanew3.root"),
   # InputFileNames = cms.vstring("file:/afs/cern.ch/work/o/okukral/TnP_pPb/Data/MC_trees_pPb.root"),
    InputDirectoryName = cms.string("tpTree"),
    InputTreeName = cms.string("fitter_tree"),
    OutputFileName = cms.string("tnp_Ana_Data_L1DoubleMu0_ptGT7_M60120.root"),
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
                         mass             = cms.vstring("Tag-Probe Mass", "60.0", "120.0", "GeV/c^{2}"), # mass range syst: 65-110, nom 60-120 - TBA
                         pt               = cms.vstring("Probe p_{T}", "0.0", "1000", "GeV/c"),
                         eta              = cms.vstring("Probe #eta", "-2.4", "2.4", ""),
                         abseta           = cms.vstring("Probe |#eta|", "0", "2.5", ""),
                         tag_hiNtracks    = cms.vstring("N Tracks", "0", "400", ""),
                         tag_hiHF         = cms.vstring("HF", "0", "500", ""),
                         tag_nVertices    = cms.vstring("PU - nVertices", "0", "10", ""),
                         run              = cms.vstring("run number", "285479", "286496", ""),
                         # weight           = cms.vstring("weight","0","10",""),
    ),
    # defines all the discrete variables of the probes available in the input tree and intended for use in the efficiency calculations
    Categories = cms.PSet(
                        TightId = cms.vstring("TightId", "dummy[true=1,false=0]"),
                        # reltkiso0p2 = cms.vstring("reltkiso0p2", "dummy[true=1,false=0]"),
                        iso0p15 = cms.vstring("iso0p15", "dummy[true=1,false=0]"),
                        l1ok = cms.vstring("l1ok", "dummy[true=1,false=0]"),
                        # l1OpenQ = cms.vstring("l1OpenQ", "dummy[true=1,false=0]"),
                        l1DoubleQ = cms.vstring("l1DoubleQ", "dummy[true=1,false=0]"),
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
	    	"efficiency[0.99,0.5,1]",
		    "signalFractionInPassing[0.9]",
    	),    
        # Signal syst
	    VoigtExp = cms.vstring(
		    "Voigtian::signal(mass, mean[91,85,95], width[3,1,10], sigma[3,1,10])",
		    "Exponential::backgroundPass(mass, lp[-0.1,-5,0])",
		    "Exponential::backgroundFail(mass, lf[-0.1,-5,0])",
		    "efficiency[0.95,0,1]",
		    "signalFractionInPassing[0.9]"
	    ),
       vpvPlusExpo = cms.vstring(
          "Voigtian::signal1(mass, mean1[90,80,100], width[2.495], sigma1[2,1,3])",
          "Voigtian::signal2(mass, mean2[90,80,100], width,        sigma2[4,2,10])",
          "SUM::signal(vFrac[0.8,0,1]*signal1, signal2)",
          "Exponential::backgroundPass(mass, lp[-0.1,-1,0.1])",
          "Exponential::backgroundFail(mass, lf[-0.1,-1,0.1])",
          "efficiency[0.9,0,1]",
          "signalFractionInPassing[0.9]"
          ),
        # Background syst
	    BWResCBPowerlaw = cms.vstring(
	    	"BreitWigner::bw(mass, m0[91.2,81.2,101.2], width[2.495,1,10])",
	    	"RooCBShape::res(mass, peak[0], sigma[1.7,0.01,10], alpha[1.8,0,3], n[0.8,0,10])",
	    	"FCONV::signal(mass, bw, res)",
            "EXPR::passPW ('mass^powerp[-1,-10,10]',mass)",
		    "EXPR::failPW ('mass^powerf[-1,-10,10]',mass)",
	    	"Chebychev::passPol (mass, {c1p[0,-10,10]})",
	    	"Chebychev::failPol (mass, {c1f[0,-10,10]})",
	    	"SUM::backgroundPass(passPol, passPW)",
	    	"SUM::backgroundFail(failPol, failPW)",
	    	"efficiency[0.9,0.5,1]",
	    	"signalFractionInPassing[0.9]",
    	),
        # Other
	    VoigtPol3 = cms.vstring(
		    "Voigtian::signal(mass, mean[91,85,95], width[3,1,10], sigma[3,1,10])",
		    "Chebychev::backgroundPass(mass, {c1p[0,-10,10], c2p[0,-10,10], c3p[0,-10,10]})",
		    "Chebychev::backgroundFail(mass, {c1f[0,-10,10], c2f[0,-10,10], c3f[0,-10,10]})",
		    "efficiency[0.9,0,1]",
		    "signalFractionInPassing[0.9]"
	    ),
	    BWResCBCheb = cms.vstring(
	    	"BreitWigner::bw(mass, m0[91.2,81.2,101.2], width[2.495,1,10])",
	    	"RooCBShape::res(mass, peak[0], sigma[1.7,0.01,10], alpha[1.8,0,3], n[0.8,0,10])",
		    "FCONV::signal(mass, bw, res)",
	    	"Chebychev::backgroundPass(mass, {c1p[0,-10,10], c2p[0,-10,10], c3p[0,-10,10]})",
	    	"Chebychev::backgroundFail(mass, {c1f[0,-10,10], c2f[0,-10,10], c3f[0,-10,10]})",
	    	"efficiency[0.9,0.5,1]",
	    	"signalFractionInPassing[0.9]",
	    ),
    ),

    # defines a set of efficiency calculations, what PDF to use for fitting and how to bin the data;
    # there will be a separate output directory for each calculation that includes a simultaneous fit, side band subtraction and counting. 
    Efficiencies = cms.PSet(
          # Order: 0 total, 1 pT, 2-8 pT fits in abseta bins, 9 abseta, 10 eta, 11-12 centrality   NOTE: IS NOT SAME AS SCENARIO
          cms.PSet(
             Iso_1bin = cms.PSet(
                EfficiencyCategoryAndState = cms.vstring("l1ok","true","l1DoubleQ","true"),
                UnbinnedVariables = cms.vstring("mass"),
                BinnedVariables = cms.PSet(
                   pt = cms.vdouble(7, 200),
                   eta = cms.vdouble(-2.4, 2.4),
                   #tag_nVertices    = cms.vdouble(0.9,1.1),
                   TightId = cms.vstring("true"),
                   iso0p15 = cms.vstring("true"),
                   #hltL3fL1sSingleMu7BptxANDL1f0L2f0L3Filtered12 = cms.vstring("true"),
                   #hltL3fL1sSingleMu7BptxANDL1f0L2f0L3Filtered15 = cms.vstring("true"),
                   ),
                BinToPDFmap = cms.vstring(PDFName)
                )
             ),
          cms.PSet(
             Iso_pt = cms.PSet(
                EfficiencyCategoryAndState = cms.vstring("l1ok","true","l1DoubleQ","true"),
                UnbinnedVariables = cms.vstring("mass"),
                BinnedVariables = cms.PSet(
                   pt = cms.vdouble(7, 12, 15, 20, 25, 30, 35, 50, 45, 50, 55, 60, 70, 80, 100, 200),
                   eta = cms.vdouble(-2.4,2.4),
                   #tag_nVertices    = cms.vdouble(0.9,1.1),
                   TightId = cms.vstring("true"),
                   iso0p15 = cms.vstring("true"),
                   #hltL3fL1sSingleMu7BptxANDL1f0L2f0L3Filtered12 = cms.vstring("true"),
                   # hltL3fL1sSingleMu7BptxANDL1f0L2f0L3Filtered15 = cms.vstring("true"),
                   ),
                BinToPDFmap = cms.vstring(PDFName)
                )
             ),
          cms.PSet(
             Iso_abseta00_12 = cms.PSet(
                EfficiencyCategoryAndState = cms.vstring("l1ok","true","l1DoubleQ","true"),
                UnbinnedVariables = cms.vstring("mass"),
                BinnedVariables = cms.PSet(
                   pt = cms.vdouble(7, 12, 15, 20, 25, 30, 35, 40, 45,50, 80, 200),
                   abseta = cms.vdouble(0, 1.2),
                   #tag_nVertices    = cms.vdouble(0.9,1.1),
                   TightId = cms.vstring("true"),
                   iso0p15 = cms.vstring("true"),
                   #hltL3fL1sSingleMu7BptxANDL1f0L2f0L3Filtered12 = cms.vstring("true"),
                   # hltL3fL1sSingleMu7BptxANDL1f0L2f0L3Filtered15 = cms.vstring("true"),
                   ),
                BinToPDFmap = cms.vstring(PDFName)
                )
             ), 
          cms.PSet(         
             Iso_abseta12_21 = cms.PSet(
                EfficiencyCategoryAndState = cms.vstring("l1ok","true","l1DoubleQ","true"),
                UnbinnedVariables = cms.vstring("mass"),
                BinnedVariables = cms.PSet(
                   pt = cms.vdouble(7, 12, 15, 20, 25, 30,35, 40,45,50, 80, 200),
                   abseta = cms.vdouble(1.2,2.1),
                   #tag_nVertices    = cms.vdouble(0.9,1.1),
                   TightId = cms.vstring("true"),
                   iso0p15 = cms.vstring("true"),
                   #hltL3fL1sSingleMu7BptxANDL1f0L2f0L3Filtered12 = cms.vstring("true"),
                   # hltL3fL1sSingleMu7BptxANDL1f0L2f0L3Filtered15 = cms.vstring("true"),
                   ),
                BinToPDFmap = cms.vstring(PDFName)
                )
             ), 
          cms.PSet(
                Iso_abseta21_24 = cms.PSet(
                   EfficiencyCategoryAndState = cms.vstring("l1ok","true","l1DoubleQ","true"),
                   UnbinnedVariables = cms.vstring("mass"),
                   BinnedVariables = cms.PSet(
                      pt = cms.vdouble(7, 12, 15, 20, 25, 30, 35, 40, 50, 80, 200),
                      abseta = cms.vdouble(2.1,2.4),
                      #tag_nVertices    = cms.vdouble(0.9,1.1),
                      TightId = cms.vstring("true"),
                      iso0p15 = cms.vstring("true"),
                      #hltL3fL1sSingleMu7BptxANDL1f0L2f0L3Filtered12 = cms.vstring("true"),
                      #hltL3fL1sSingleMu7BptxANDL1f0L2f0L3Filtered15 = cms.vstring("true"),
                      ),
                   BinToPDFmap = cms.vstring(PDFName)
                   )
                ), 
          cms.PSet(
                Iso_absetadep = cms.PSet(
                   EfficiencyCategoryAndState = cms.vstring("l1ok","true","l1DoubleQ","true"),
                   UnbinnedVariables = cms.vstring("mass"),
                   BinnedVariables = cms.PSet(
                      pt = cms.vdouble(7, 200),
                      abseta = cms.vdouble(0,1.2,2.1,2.4),
                      #tag_nVertices    = cms.vdouble(0.9,1.1),
                      TightId = cms.vstring("true"),
                      iso0p15 = cms.vstring("true"),
                      #hltL3fL1sSingleMu7BptxANDL1f0L2f0L3Filtered12 = cms.vstring("true"),
                      #hltL3fL1sSingleMu7BptxANDL1f0L2f0L3Filtered15 = cms.vstring("true"),
                      ),
                   BinToPDFmap = cms.vstring(PDFName)
                   )
                ), 
          cms.PSet(      
                Iso_etadep = cms.PSet(
                   EfficiencyCategoryAndState = cms.vstring("l1ok","true","l1DoubleQ","true"),
                   UnbinnedVariables = cms.vstring("mass"),
                   BinnedVariables = cms.PSet(
                      pt = cms.vdouble(7, 200),
                      eta = cms.vdouble(-2.4,-2.1,-1.6,-1.2,-0.9,-0.6,-0.3,0,0.3,0.6,0.9,1.2,1.6,2.1,2.4),
                      #tag_nVertices    = cms.vdouble(0.9,1.1),
                      TightId = cms.vstring("true"),
                      iso0p15 = cms.vstring("true"),
                      #hltL3fL1sSingleMu7BptxANDL1f0L2f0L3Filtered12 = cms.vstring("true"),
                      # hltL3fL1sSingleMu7BptxANDL1f0L2f0L3Filtered15 = cms.vstring("true"),
                      ),
                   BinToPDFmap = cms.vstring(PDFName)
                   )
                ), 
          cms.PSet(      
                Iso_centdep = cms.PSet(
                   EfficiencyCategoryAndState = cms.vstring("l1ok","true","l1DoubleQ","true"),
                   UnbinnedVariables = cms.vstring("mass"),
                   BinnedVariables = cms.PSet(
                      pt = cms.vdouble(7, 200),
                      eta = cms.vdouble(-2.4,2.4),
                      tag_hiNtracks = cms.vdouble(0,30,50,75,100,125,150,175,400),
                      #tag_nVertices    = cms.vdouble(0.9,1.1),
                      TightId = cms.vstring("true"),
                      iso0p15 = cms.vstring("true"),
                      #hltL3fL1sSingleMu7BptxANDL1f0L2f0L3Filtered12 = cms.vstring("true"),
                      # hltL3fL1sSingleMu7BptxANDL1f0L2f0L3Filtered15 = cms.vstring("true"),
                      ),
                   BinToPDFmap = cms.vstring(PDFName)
                   )
                ), 
          cms.PSet(      
                Iso_centdepHF = cms.PSet(
                   EfficiencyCategoryAndState = cms.vstring("l1ok","true","l1DoubleQ","true"),
                   UnbinnedVariables = cms.vstring("mass"),
                   BinnedVariables = cms.PSet(
                      pt = cms.vdouble(7, 200),
                      eta = cms.vdouble(-2.4,2.4),
                      tag_hiHF = cms.vdouble(0,30,50,75,100,125,150,175,500),
                      #tag_nVertices    = cms.vdouble(0.9,1.1),
                      TightId = cms.vstring("true"),
                      iso0p15 = cms.vstring("true"),
                      #hltL3fL1sSingleMu7BptxANDL1f0L2f0L3Filtered12 = cms.vstring("true"),
                      # hltL3fL1sSingleMu7BptxANDL1f0L2f0L3Filtered15 = cms.vstring("true"),
                      ),
                   BinToPDFmap = cms.vstring(PDFName)
                   )
                ), 
          cms.PSet(      
                Iso_nPV = cms.PSet(
                   EfficiencyCategoryAndState = cms.vstring("l1ok","true","l1DoubleQ","true"),
                   UnbinnedVariables = cms.vstring("mass"),
                   BinnedVariables = cms.PSet(
                      pt = cms.vdouble(7, 200),
                      eta = cms.vdouble(-2.4,2.4),
                      tag_nVertices = cms.vdouble(0.5,1.5,2.5,3.5,10.5),
                      #tag_nVertices    = cms.vdouble(0.9,1.1),
                      TightId = cms.vstring("true"),
                      iso0p15 = cms.vstring("true"),
                      #hltL3fL1sSingleMu7BptxANDL1f0L2f0L3Filtered12 = cms.vstring("true"),
                      # hltL3fL1sSingleMu7BptxANDL1f0L2f0L3Filtered15 = cms.vstring("true"),
                      ),
                   BinToPDFmap = cms.vstring(PDFName)
                   )
                ), 
          cms.PSet(      
                Iso_rundep = cms.PSet(
                   EfficiencyCategoryAndState = cms.vstring("l1ok","true","l1DoubleQ","true"),
                   UnbinnedVariables = cms.vstring("mass"),
                   BinnedVariables = cms.PSet(
                      pt = cms.vdouble(7, 200),
                      eta = cms.vdouble(-2.4,2.4),
                      run = cms.vdouble(285479,285900,286496),
                      #tag_nVertices    = cms.vdouble(0.9,1.1),
                      TightId = cms.vstring("true"),
                      iso0p15 = cms.vstring("true"),
                      #hltL3fL1sSingleMu7BptxANDL1f0L2f0L3Filtered12 = cms.vstring("true"),
                      # hltL3fL1sSingleMu7BptxANDL1f0L2f0L3Filtered15 = cms.vstring("true"),
                      ),
                   BinToPDFmap = cms.vstring(PDFName)
                   )
                ), 
          )
)

process.fitness = cms.Path(
    process.TagProbeFitTreeAnalyzer
)
