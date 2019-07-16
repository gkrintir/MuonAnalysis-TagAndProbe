import FWCore.ParameterSet.Config as cms

import sys
args =sys.argv[1:]
if len(args) < 2: scenario = "0"
else: 
   scenario = args[1]
print("Will run scenario " + scenario) 
# scenario: 1 pT, 2-3 pT in detailed abseta bins, 4-5 pT in overall abseta bins, 6 abseta, 7, eta, 8 centrality, 9 added nPV, 0 (or no parameter) run all


process = cms.Process("TagProbe")
process.load('FWCore.MessageService.MessageLogger_cfi')
process.source = cms.Source("EmptySource")
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1) )    
#PDFName = "cbFixedNGausExp"
PDFName = "cbFixedNGausExp3"


VEFFICIENCYSET =cms.VPSet(
# Order: 0 total, 1 pT, 2-8 pT fits in abseta bins, 9 abseta, 10 eta, 11-12 centrality   NOTE: IS NOT SAME AS SCENARIO
    cms.PSet(
        MuId_1bin = cms.PSet(
            EfficiencyCategoryAndState = cms.vstring("SoftID","true"),
            UnbinnedVariables = cms.vstring("mass"),
            BinnedVariables = cms.PSet(
                pt = cms.vdouble(0.8, 25.0),
                eta = cms.vdouble(-2.4, 2.4),
                tag_nVertices    = cms.vdouble(0.9,1.1),
                #TM = cms.vstring("true"),
                #isNotMuonSeeded = cms.vstring("true"),
                #Glb = cms.vstring("true"),
                #PF = cms.vstring("true"),
            ),
         BinToPDFmap = cms.vstring(PDFName)
        )
    ),
    cms.PSet(
       MuId_pt = cms.PSet(
           EfficiencyCategoryAndState = cms.vstring("SoftID","true"),
           UnbinnedVariables = cms.vstring("mass"),
           BinnedVariables = cms.PSet(
               pt = cms.vdouble(0.8, 1.5, 2.5, 3.5, 4.5, 5.5, 6.5, 8.0, 10.5, 14.0, 18.0, 25.0),
               eta = cms.vdouble(-2.4,2.4),
               tag_nVertices    = cms.vdouble(0.9,1.1),
               #TM = cms.vstring("true"),
               #isNotMuonSeeded = cms.vstring("true"),
               #Glb = cms.vstring("true"),
               #PF = cms.vstring("true"),
           ),
           BinToPDFmap = cms.vstring(PDFName)
       )
    ),
    cms.PSet(
        MuId_abseta00_08 = cms.PSet(
            EfficiencyCategoryAndState = cms.vstring("SoftID","true"),
            UnbinnedVariables = cms.vstring("mass"),
            BinnedVariables = cms.PSet(
                pt = cms.vdouble(3.3, 4.5, 5.5, 6.5, 8.0, 10.5, 14.0, 18.0, 25.0),
                abseta = cms.vdouble(0, 0.8),
                tag_nVertices    = cms.vdouble(0.9,1.1),
                #TM = cms.vstring("true"),
                #isNotMuonSeeded = cms.vstring("true"),
                #Glb = cms.vstring("true"),
                #PF = cms.vstring("true"),
            ),
            BinToPDFmap = cms.vstring(PDFName)
        )
    ), 
    cms.PSet(
        MuId_abseta08_15 = cms.PSet(
            EfficiencyCategoryAndState = cms.vstring("SoftID","true"),
            UnbinnedVariables = cms.vstring("mass"),
            BinnedVariables = cms.PSet(
                pt = cms.vdouble(1.1, 2.5, 3.5, 4.5, 5.5, 6.5, 8.0, 10.5, 14.0, 18.0, 25.0),
                abseta = cms.vdouble(0.8, 1.5),
                tag_nVertices    = cms.vdouble(0.9,1.1),
                #TM = cms.vstring("true"),
                #isNotMuonSeeded = cms.vstring("true"),
                #Glb = cms.vstring("true"),
                #PF = cms.vstring("true"),
            ),
            BinToPDFmap = cms.vstring(PDFName)
        )
    ), 
    cms.PSet(#4 unused
        MuId_abseta00_12 = cms.PSet(
            EfficiencyCategoryAndState = cms.vstring("SoftID","true"),
            UnbinnedVariables = cms.vstring("mass"),
            BinnedVariables = cms.PSet(
                pt = cms.vdouble(2.5, 3.5, 4.5, 5.5, 6.5, 8.0, 10.5, 14.0, 18.0, 25.0),
                abseta = cms.vdouble(0, 1.2),
                tag_nVertices    = cms.vdouble(0.9,1.1),
                #TM = cms.vstring("true"),
                #isNotMuonSeeded = cms.vstring("true"),
                #Glb = cms.vstring("true"),
                #PF = cms.vstring("true"),
            ),
            BinToPDFmap = cms.vstring(PDFName)
        )
    ), 
    cms.PSet( #5 unused
         MuId_abseta12_16 = cms.PSet(
             EfficiencyCategoryAndState = cms.vstring("SoftID","true"),
             UnbinnedVariables = cms.vstring("mass"),
             BinnedVariables = cms.PSet(
                pt = cms.vdouble(1.5, 3.0, 4.5, 6.5, 10.0, 14.0, 25.0),
                abseta = cms.vdouble(1.2,1.6),
                tag_nVertices    = cms.vdouble(0.9,1.1),
                #TM = cms.vstring("true"),
                #isNotMuonSeeded = cms.vstring("true"),
                #Glb = cms.vstring("true"),
                #PF = cms.vstring("true"),
             ),
             BinToPDFmap = cms.vstring(PDFName)
        )
    ), 
    cms.PSet(         
         MuId_abseta15_21 = cms.PSet(
             EfficiencyCategoryAndState = cms.vstring("SoftID","true"),
             UnbinnedVariables = cms.vstring("mass"),
             BinnedVariables = cms.PSet(
                pt = cms.vdouble(0.8, 2.0, 3.0, 4.5, 6.5, 10.0, 14.0, 25.0),
                abseta = cms.vdouble(1.5,2.1),
                tag_nVertices    = cms.vdouble(0.9,1.1),
                #TM = cms.vstring("true"),
                #isNotMuonSeeded = cms.vstring("true"),
                #Glb = cms.vstring("true"),
                #PF = cms.vstring("true"),
             ),
             BinToPDFmap = cms.vstring(PDFName)
        )
    ), 
    cms.PSet(         
         MuId_abseta08_21 = cms.PSet(
             EfficiencyCategoryAndState = cms.vstring("SoftID","true"),
             UnbinnedVariables = cms.vstring("mass"),
             BinnedVariables = cms.PSet(
                pt = cms.vdouble(0.8, 2.0, 3.0, 4.5, 6.5, 10.0, 14.0, 25.0),
                abseta = cms.vdouble(0.8,2.1),
                tag_nVertices    = cms.vdouble(0.9,1.1),
                #TM = cms.vstring("true"),
                #isNotMuonSeeded = cms.vstring("true"),
                #Glb = cms.vstring("true"),
                #PF = cms.vstring("true"),
             ),
             BinToPDFmap = cms.vstring(PDFName)
        )
    ), 
    cms.PSet(
        MuId_abseta21_24 = cms.PSet(
            EfficiencyCategoryAndState = cms.vstring("SoftID","true"),
            UnbinnedVariables = cms.vstring("mass"),
            BinnedVariables = cms.PSet(
                pt = cms.vdouble(0.8, 2.0, 3.5, 5.5, 8.0, 12.0, 25.0),
                abseta = cms.vdouble(2.1,2.4),
                tag_nVertices    = cms.vdouble(0.9,1.1),
                #TM = cms.vstring("true"),
                #isNotMuonSeeded = cms.vstring("true"),
                #Glb = cms.vstring("true"),
                #PF = cms.vstring("true"),
            ),
            BinToPDFmap = cms.vstring(PDFName)
        )
    ), 
    cms.PSet(
        MuId_absetadep = cms.PSet(
            EfficiencyCategoryAndState = cms.vstring("SoftID","true"),
            UnbinnedVariables = cms.vstring("mass"),
            BinnedVariables = cms.PSet(
                pt = cms.vdouble(0.8, 25.0),
                abseta = cms.vdouble(0,0.9,1.2,1.6,2.1,2.4),
                tag_nVertices    = cms.vdouble(0.9,1.1),
                #TM = cms.vstring("true"),
                #isNotMuonSeeded = cms.vstring("true"),
                #Glb = cms.vstring("true"),
                #PF = cms.vstring("true"),
            ),
            BinToPDFmap = cms.vstring(PDFName)
        )
    ), 
    cms.PSet(      
        MuId_etadep = cms.PSet(
            EfficiencyCategoryAndState = cms.vstring("SoftID","true"),
            UnbinnedVariables = cms.vstring("mass"),
            BinnedVariables = cms.PSet(
                pt = cms.vdouble(0.8, 25.0),
                eta = cms.vdouble(-2.4,-2.1,-1.6,-1.2,-0.9,-0.6,-0.3,0,0.3,0.6,0.9,1.2,1.6,2.1,2.4),
                tag_nVertices    = cms.vdouble(0.9,1.1),
                #TM = cms.vstring("true"),
                #isNotMuonSeeded = cms.vstring("true"),
                #Glb = cms.vstring("true"),
                #PF = cms.vstring("true"),
            ),
            BinToPDFmap = cms.vstring(PDFName)
        )
    ), 
    cms.PSet(
        MuId_centdep = cms.PSet(
            EfficiencyCategoryAndState = cms.vstring("SoftID","true"),
            UnbinnedVariables = cms.vstring("mass"),
            BinnedVariables = cms.PSet(
                pt = cms.vdouble(0.8, 25.0),
                eta = cms.vdouble(-2.4,2.4),
                tag_nVertices    = cms.vdouble(0.9,1.1),
                tag_hiNtracks = cms.vdouble(0,30,50,75,100,125,150,175,400),
                #TM = cms.vstring("true"),
                #isNotMuonSeeded = cms.vstring("true"),
                #Glb = cms.vstring("true"),
                #PF = cms.vstring("true"),
            ),
            BinToPDFmap = cms.vstring(PDFName)
        )
    ), 
    cms.PSet(
        MuId_centdepHF = cms.PSet(
            EfficiencyCategoryAndState = cms.vstring("SoftID","true"),
            UnbinnedVariables = cms.vstring("mass"),
            BinnedVariables = cms.PSet(
                pt = cms.vdouble(0.8, 25.0),
                eta = cms.vdouble(-2.4,2.4),
                tag_nVertices    = cms.vdouble(0.9,1.1),
                tag_hiHF = cms.vdouble(0,30,50,75,100,125,150,175,400),
                #TM = cms.vstring("true"),
                #isNotMuonSeeded = cms.vstring("true"),
                #Glb = cms.vstring("true"),
                #PF = cms.vstring("true"),
            ),
            BinToPDFmap = cms.vstring(PDFName)
        )
    ), 
    #13 and further below: centrality versions:
    cms.PSet(      
        MuId_etadep_cent1 = cms.PSet(
            EfficiencyCategoryAndState = cms.vstring("SoftID","true"),
            UnbinnedVariables = cms.vstring("mass"),
            BinnedVariables = cms.PSet(
                pt = cms.vdouble(0.8, 25.0),
                eta = cms.vdouble(-2.4,-2.1,-1.6,-1.2,-0.9,-0.6,-0.3,0,0.3,0.6,0.9,1.2,1.6,2.1,2.4),
                tag_hiNtracks = cms.vdouble(0,30),
                tag_nVertices    = cms.vdouble(0.9,1.1),
                #TM = cms.vstring("true"),
                #isNotMuonSeeded = cms.vstring("true"),
                #Glb = cms.vstring("true"),
                #PF = cms.vstring("true"),
            ),
            BinToPDFmap = cms.vstring(PDFName)
        )
    ), 
    cms.PSet(      
        MuId_etadep_cent2 = cms.PSet(
            EfficiencyCategoryAndState = cms.vstring("SoftID","true"),
            UnbinnedVariables = cms.vstring("mass"),
            BinnedVariables = cms.PSet(
                pt = cms.vdouble(0.8, 25.0),
                eta = cms.vdouble(-2.4,-2.1,-1.6,-1.2,-0.9,-0.6,-0.3,0,0.3,0.6,0.9,1.2,1.6,2.1,2.4),
                tag_hiNtracks = cms.vdouble(30,75),
                tag_nVertices    = cms.vdouble(0.9,1.1),
                #TM = cms.vstring("true"),
                #isNotMuonSeeded = cms.vstring("true"),
                #Glb = cms.vstring("true"),
                #PF = cms.vstring("true"),
            ),
            BinToPDFmap = cms.vstring(PDFName)
        )
    ), 
    cms.PSet(      
        MuId_etadep_cent3 = cms.PSet(
            EfficiencyCategoryAndState = cms.vstring("SoftID","true"),
            UnbinnedVariables = cms.vstring("mass"),
            BinnedVariables = cms.PSet(
                pt = cms.vdouble(0.8, 25.0),
                eta = cms.vdouble(-2.4,-2.1,-1.6,-1.2,-0.9,-0.6,-0.3,0,0.3,0.6,0.9,1.2,1.6,2.1,2.4),
                tag_hiNtracks = cms.vdouble(75,400),
                tag_nVertices    = cms.vdouble(0.9,1.1),
                #TM = cms.vstring("true"),
                #isNotMuonSeeded = cms.vstring("true"),
                #Glb = cms.vstring("true"),
                #PF = cms.vstring("true"),
            ),
            BinToPDFmap = cms.vstring(PDFName)
        )
    ), 
    cms.PSet(
       MuId_pt_cent1 = cms.PSet(
           EfficiencyCategoryAndState = cms.vstring("SoftID","true"),
           UnbinnedVariables = cms.vstring("mass"),
           BinnedVariables = cms.PSet(
               pt = cms.vdouble(0.5, 1.5, 3.0, 4.5, 6.0, 8.0, 11.0, 15.0, 25.0),
               eta = cms.vdouble(-2.4,2.4),
               tag_nVertices    = cms.vdouble(0.9,1.1),
               tag_hiNtracks = cms.vdouble(0,30),
               #TM = cms.vstring("true"),
               #isNotMuonSeeded = cms.vstring("true"),
               #Glb = cms.vstring("true"),
               #PF = cms.vstring("true"),
           ),
           BinToPDFmap = cms.vstring(PDFName)
       )
    ),
    cms.PSet(
       MuId_pt_cent2 = cms.PSet(
           EfficiencyCategoryAndState = cms.vstring("SoftID","true"),
           UnbinnedVariables = cms.vstring("mass"),
           BinnedVariables = cms.PSet(
               pt = cms.vdouble(0.5, 1.5, 3.0, 4.5, 6.0, 8.0, 11.0, 15.0, 25.0),
               eta = cms.vdouble(-2.4,2.4),
               tag_nVertices    = cms.vdouble(0.9,1.1),
               tag_hiNtracks = cms.vdouble(30,75),
               #TM = cms.vstring("true"),
               #isNotMuonSeeded = cms.vstring("true"),
               #Glb = cms.vstring("true"),
               #PF = cms.vstring("true"),
           ),
           BinToPDFmap = cms.vstring(PDFName)
       )
    ),
    cms.PSet(
       MuId_pt_cent3 = cms.PSet(
           EfficiencyCategoryAndState = cms.vstring("SoftID","true"),
           UnbinnedVariables = cms.vstring("mass"),
           BinnedVariables = cms.PSet(
               pt = cms.vdouble(0.5, 1.5, 3.0, 4.5, 6.0, 8.0, 11.0, 15.0, 25.0),
               eta = cms.vdouble(-2.4,2.4),
               tag_nVertices    = cms.vdouble(0.9,1.1),
               tag_hiNtracks = cms.vdouble(75,400),
               #TM = cms.vstring("true"),
               #isNotMuonSeeded = cms.vstring("true"),
               #Glb = cms.vstring("true"),
               #PF = cms.vstring("true"),
           ),
           BinToPDFmap = cms.vstring(PDFName)
       )
    ),
    cms.PSet( #19
        MuId_centdepHighPt = cms.PSet(
            EfficiencyCategoryAndState = cms.vstring("SoftID","true"),
            UnbinnedVariables = cms.vstring("mass"),
            BinnedVariables = cms.PSet(
                pt = cms.vdouble(1.5, 25.0),
                eta = cms.vdouble(-2.4,2.4),
                tag_nVertices    = cms.vdouble(0.9,1.1),
                tag_hiNtracks = cms.vdouble(0,35,60,120,250),
                #TM = cms.vstring("true"),
                #isNotMuonSeeded = cms.vstring("true"),
                #Glb = cms.vstring("true"),
                #PF = cms.vstring("true"),
            ),
            BinToPDFmap = cms.vstring(PDFName)
        )
    ), 
    cms.PSet( #20
        MuId_centdepLowPt = cms.PSet(
            EfficiencyCategoryAndState = cms.vstring("SoftID","true"),
            UnbinnedVariables = cms.vstring("mass"),
            BinnedVariables = cms.PSet(
                pt = cms.vdouble(0.0, 1.5),
                eta = cms.vdouble(-2.4,2.4),
                tag_nVertices    = cms.vdouble(0.9,1.1),
                tag_hiNtracks = cms.vdouble(0,35,60,120,250),
                #TM = cms.vstring("true"),
                #isNotMuonSeeded = cms.vstring("true"),
                #Glb = cms.vstring("true"),
                #PF = cms.vstring("true"),
            ),
            BinToPDFmap = cms.vstring(PDFName)
        )
    ), 
    cms.PSet( #21
        MuId_centdepNB = cms.PSet(
            EfficiencyCategoryAndState = cms.vstring("SoftID","true"),
            UnbinnedVariables = cms.vstring("mass"),
            BinnedVariables = cms.PSet(
                pt = cms.vdouble(0.0, 25),
                eta = cms.vdouble(-2.4,2.4),
                tag_nVertices    = cms.vdouble(0.9,1.1),
                tag_hiNtracks = cms.vdouble(0,35,60,120,250),
                #TM = cms.vstring("true"),
                #isNotMuonSeeded = cms.vstring("true"),
                #Glb = cms.vstring("true"),
                #PF = cms.vstring("true"),
            ),
            BinToPDFmap = cms.vstring(PDFName)
        )
    ), 
    cms.PSet( 
        MuId_centdepLowPt12_16 = cms.PSet(
            EfficiencyCategoryAndState = cms.vstring("SoftID","true"),
            UnbinnedVariables = cms.vstring("mass"),
            BinnedVariables = cms.PSet(
                pt = cms.vdouble(0.0, 1.5),
                abseta = cms.vdouble(1.2,1.6),
                tag_nVertices    = cms.vdouble(0.9,1.1),
                tag_hiNtracks = cms.vdouble(0,35,60,120,250),
                #TM = cms.vstring("true"),
                #isNotMuonSeeded = cms.vstring("true"),
                #Glb = cms.vstring("true"),
                #PF = cms.vstring("true"),
            ),
            BinToPDFmap = cms.vstring(PDFName)
        )
    ), 
    cms.PSet( 
        MuId_centdepLowPt16_21 = cms.PSet(
            EfficiencyCategoryAndState = cms.vstring("SoftID","true"),
            UnbinnedVariables = cms.vstring("mass"),
            BinnedVariables = cms.PSet(
                pt = cms.vdouble(0.0, 1.5),
                abseta = cms.vdouble(1.6,2.1),
                tag_nVertices    = cms.vdouble(0.9,1.1),
                tag_hiNtracks = cms.vdouble(0,35,60,120,250),
                #TM = cms.vstring("true"),
                #isNotMuonSeeded = cms.vstring("true"),
                #Glb = cms.vstring("true"),
                #PF = cms.vstring("true"),
            ),
            BinToPDFmap = cms.vstring(PDFName)
        )
    ), 
)

#Actual selection 
#if scenario == "1": EFFICIENCYSET = cms.PSet(VEFFICIENCYSET[0], VEFFICIENCYSET[1])
if scenario == "1": EFFICIENCYSET = cms.PSet(VEFFICIENCYSET[0])
#if scenario == "1": EFFICIENCYSET = cms.PSet(VEFFICIENCYSET[19], VEFFICIENCYSET[20], VEFFICIENCYSET[21], VEFFICIENCYSET[22], VEFFICIENCYSET[23])
if scenario == "2": EFFICIENCYSET = cms.PSet(VEFFICIENCYSET[1], VEFFICIENCYSET[2])
if scenario == "3": EFFICIENCYSET = cms.PSet(VEFFICIENCYSET[3], VEFFICIENCYSET[6])
#if scenario == "2": EFFICIENCYSET = cms.PSet(VEFFICIENCYSET[13], VEFFICIENCYSET[14],VEFFICIENCYSET[15])
#if scenario == "3": EFFICIENCYSET = cms.PSet(VEFFICIENCYSET[16], VEFFICIENCYSET[17],VEFFICIENCYSET[18])
if scenario == "4": EFFICIENCYSET = cms.PSet(VEFFICIENCYSET[7])
if scenario == "5": EFFICIENCYSET = cms.PSet(VEFFICIENCYSET[8])
if scenario == "6": EFFICIENCYSET = cms.PSet(VEFFICIENCYSET[9])
if scenario == "7": EFFICIENCYSET = cms.PSet(VEFFICIENCYSET[10])
if scenario == "8": EFFICIENCYSET = cms.PSet(VEFFICIENCYSET[11])#, VEFFICIENCYSET[12])
if scenario == "0": EFFICIENCYSET = cms.PSet(VEFFICIENCYSET[1],VEFFICIENCYSET[2],VEFFICIENCYSET[3],VEFFICIENCYSET[6], VEFFICIENCYSET[7],VEFFICIENCYSET[8], VEFFICIENCYSET[9], VEFFICIENCYSET[10],VEFFICIENCYSET[11])#,VEFFICIENCYSET[12])
#if scenario == "0": EFFICIENCYSET = cms.PSet(VEFFICIENCYSET[1],VEFFICIENCYSET[2], VEFFICIENCYSET[3],VEFFICIENCYSET[4], VEFFICIENCYSET[5],VEFFICIENCYSET[6], VEFFICIENCYSET[7],VEFFICIENCYSET[8], VEFFICIENCYSET[9], VEFFICIENCYSET[10],VEFFICIENCYSET[11],VEFFICIENCYSET[12])






process.TagProbeFitTreeAnalyzer = cms.EDAnalyzer("TagProbeFitTreeAnalyzer",
    # IO parameters:
    #InputFileNames = cms.vstring("file:/afs/cern.ch/work/o/okukral/TnP_pPb/Data/PASingleMuon_PARun2016C-PromptReco-v1TnpTress_Pbpv1CentralityInfo.root"),
    InputFileNames = cms.vstring("file:/eos/cms/store/group/phys_heavyions/okukral/TagAndProbe2016/LowPt/tnpJPsi_Data_bothDirMuId.root"),
    InputDirectoryName = cms.string("tpTree"),
    InputTreeName = cms.string("fitter_tree"),
    OutputFileName = cms.string("tnp_Ana_RD_MuId_pPb_bkg_%s.root" % (scenario)),
    #number of CPUs to use for fitting
    NumCPU = cms.uint32(12),
    # specifies whether to save the RooWorkspace containing the data for each bin and
    # the pdf object with the initial and final state snapshots
    binnedFit = cms.bool(True),
    binsForFit = cms.uint32(50),
    binsForMassPlots = cms.uint32(50),
    SaveWorkspace = cms.bool(False),
    
    # defines all the real variables of the probes available in the input tree and intended for use in the efficiencies
    Variables = cms.PSet(
                         mass             = cms.vstring("Tag-Probe Mass", "2.6", "3.6", "GeV/c^{2}"), # mass range syst: 2.8-3.4
                         pt               = cms.vstring("Probe p_{T}", "0.0", "30", "GeV/c"),
                         eta              = cms.vstring("Probe #eta", "-2.4", "2.4", ""),
                         abseta           = cms.vstring("Probe |#eta|", "0", "2.4", ""),
                         tag_hiNtracks    = cms.vstring("N Tracks", "0", "400", ""),
                         #tag_hiHF         = cms.vstring("HF", "0", "500", ""),
                         tag_nVertices    = cms.vstring("PU - nVertices", "0", "10", ""),
                         tag_pt           = cms.vstring("tag_pt", "0", "1000", "GeV/c"),
    ),
    # defines all the discrete variables of the probes available in the input tree and intended for use in the efficiency calculations
    Categories = cms.PSet(
                        #Glb = cms.vstring("Glb", "dummy[true=1,false=0]"),
                        #PF = cms.vstring("PF", "dummy[true=1,false=0]"),
                        SoftID = cms.vstring("SoftID", "dummy[true=1,false=0]"),
                        #TM = cms.vstring("TM", "dummy[true=1,false=0]"),
                        #isNotMuonSeeded = cms.vstring("isNotMuonSeeded", "dummy[true=1,false=0]"),
                      
    ),

    # defines all the PDFs that will be available for the efficiency calculations; uses RooFit's "factory" syntax;
    # each pdf needs to define "signal", "backgroundPass", "backgroundFail" pdfs, "efficiency[0.9,0,1]" and "signalFractionInPassing[0.9]" are used for initial values  
    PDFs = cms.PSet(
	VoigtExp = cms.vstring(
		"Voigtian::signal(mass, mean[91,85,95], width[3,1,10], sigma[3,1,10])",
		"Exponential::backgroundPass(mass, lp[0,-5,5])",
		"Exponential::backgroundFail(mass, lf[0,-5,5])",
		"efficiency[0.9,0,1]",
		"signalFractionInPassing[0.9]"
	),
	BWResCBExp = cms.vstring(
		"BreitWigner::bw(mass, m0[91.2,81.2,101.2], width[2.495,1,10])",
		"RooCBShape::res(mass, peak[0], sigma[1.7,0.01,10], alpha[1.8,0,3], n[0.8,0,10])",
		"FCONV::signal(mass, bw, res)",
		"Exponential::backgroundPass(mass, lp[0,-5,5])",
		"Exponential::backgroundFail(mass, lf[0,-5,5])",
		"efficiency[0.9,0.5,1]",
		"signalFractionInPassing[0.9]",
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
        #nominal:
    cbPlusPol1 = cms.vstring(
        "CBShape::signal(mass, mean[3.08,3.00,3.3], sigma[0.03, 0.01, 0.10], alpha[1.85, 0.1, 50], n[1.7, 0.2, 50])",
        "Chebychev::backgroundPass(mass, {cPass[0.,-1.1,1.1]})",
        "Chebychev::backgroundFail(mass, {cFail[0.,-1.1,1.1]})",
        "efficiency[0.9,0,1]",
        "signalFractionInPassing[0.9]"
    ),
        #background syst:
    cbPlusPol2 = cms.vstring(
        "CBShape::signal(mass, mean[3.08,3.00,3.2], sigma[0.03, 0.01, 0.10], alpha[1.85, 0.1, 50], n[1.7, 0.2, 50])",
        "Chebychev::backgroundPass(mass, {cPass[0.,-1.1,1.1], cPass2[0.,-1.1,1.1]})",
        "Chebychev::backgroundFail(mass, {cFail[0.,-1.1,1.1], cFail2[0.,-1.1,1.1]})",
        "efficiency[0.9,0,1]",
        "signalFractionInPassing[0.9]"
    ),
        #signal syst:
    cbGausPlusPol1 = cms.vstring(
        "CBShape::signal1(mass, mean[3.08,3.00,3.3], sigma1[0.03, 0.01, 0.10], alpha[1.85, 0.1, 50], n[1.7, 0.2, 50])",
        "RooFormulaVar::sigma2('@0*@1',{fracS[1.8,1.2,2.4],sigma1})",
        "Gaussian::signal2(mass, mean, sigma2)",
        "SUM::signal(frac[0.8,0.5,1.]*signal1,signal2)",
        "Chebychev::backgroundPass(mass, {cPass[0.,-1.1,1.1]})",
        "Chebychev::backgroundFail(mass, {cFail[0.,-1.1,1.1]})",
        "efficiency[0.9,0,1]",
        "signalFractionInPassing[0.9]"
    ),
    cbGausExp = cms.vstring(
        "CBShape::signal1(mass, mean[3.08,3.00,3.3], sigma1[0.03, 0.01, 0.10], alpha[1.85, 0.1, 50], n[1.7, 0.2, 50])",
        "RooFormulaVar::sigma2('@0*@1',{fracS[1.8,1.2,2.4],sigma1})",
        "Gaussian::signal2(mass, mean, sigma2)",
        "SUM::signal(frac[0.8,0.5,1.]*signal1,signal2)",
        "Exponential::backgroundPass(mass, lp[0,-5,5])",
        "Exponential::backgroundFail(mass, lf[0,-5,5])",
        "efficiency[0.9,0,1]",
        "signalFractionInPassing[0.9]"
    ),
    cbFixedNGausExp = cms.vstring( #n fixed to average value in the MC abseta fits
        "CBShape::signal1(mass, mean[3.08,3.00,3.3], sigma1[0.03, 0.01, 0.10], alpha[1.85, 0.1, 50], n[1.3])",
        "RooFormulaVar::sigma2('@0*@1',{fracS[1.8,1.2,2.4],sigma1})",
        "Gaussian::signal2(mass, mean, sigma2)",
        "SUM::signal(frac[0.8,0.5,1.]*signal1,signal2)",
        "Exponential::backgroundPass(mass, lp[0,-5,5])",
        "Exponential::backgroundFail(mass, lf[0,-5,5])",
        "efficiency[0.9,0,1]",
        "signalFractionInPassing[0.9]"
    ),
    cbFixedNGausPol3 = cms.vstring( #n fixed to average value in the MC abseta fits
        "CBShape::signal1(mass, mean[3.08,3.00,3.3], sigma1[0.03, 0.01, 0.10], alpha[1.85, 0.1, 50], n[1.3])",
        "RooFormulaVar::sigma2('@0*@1',{fracS[1.8,1.2,2.4],sigma1})",
        "Gaussian::signal2(mass, mean, sigma2)",
        "SUM::signal(frac[0.8,0.5,1.]*signal1,signal2)",
        "Chebychev::backgroundPass(mass, {cPass[0.,-1.1,1.1], cPass2[0.,-1.1,1.1], cPass3[0.,-1.1,1.1]})",
        "Chebychev::backgroundFail(mass, {cFail[0.,-1.1,1.1], cFail2[0.,-1.1,1.1], cPass3[0.,-1.1,1.1]})",
        "efficiency[0.9,0,1]",
        "signalFractionInPassing[0.9]"
    ),
    cbFixedNGausExp3 = cms.vstring( #n fixed to average value in the MC abseta fits
        "CBShape::signal1(mass, mean[3.08,3.00,3.3], sigma1[0.03, 0.01, 0.10], alpha[1.85, 0.1, 50], n[1.3])",
        "RooFormulaVar::sigma2('@0*@1',{fracS[1.8,1.2,2.4],sigma1})",
        "Gaussian::signal2(mass, mean, sigma2)",
        "SUM::signal(frac[0.8,0.5,1.]*signal1,signal2)",
        "Exponential::backgroundPass(RooFormulaVar::mass3p('@1*@0 + @2*@0*@0 + @2*@0*@0*@0',{mass, lp1[0,-5,5], lp2[0,-5,5], lp3[0,-5,5]}), One[1.0])",
        "Exponential::backgroundFail(RooFormulaVar::mass3f('@1*@0 + @2*@0*@0 + @2*@0*@0*@0',{mass, lf1[0,-5,5], lf2[0,-5,5], lf3[0,-5,5]}), One[1.0])",
        "efficiency[0.9,0,1]",
        "signalFractionInPassing[0.9]"
    ),

    ),

    # defines a set of efficiency calculations, what PDF to use for fitting and how to bin the data;
    # there will be a separate output directory for each calculation that includes a simultaneous fit, side band subtraction and counting. 
    Efficiencies = EFFICIENCYSET 
)

process.fitness = cms.Path(
    process.TagProbeFitTreeAnalyzer
)
