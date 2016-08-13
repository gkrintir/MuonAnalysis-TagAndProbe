import FWCore.ParameterSet.Config as cms

process = cms.Process("TagProbe")

process.load('Configuration.StandardSequences.Services_cff')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring('root://cms-xrd-global.cern.ch//store/data/Run2015E/SingleMuLowPt/AOD/PromptReco-v1/000/262/204/00000/C27AD0CE-9894-E511-942F-02163E013475.root')
)
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )    

process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')
process.load("Configuration.StandardSequences.Reconstruction_cff")

process.GlobalTag.globaltag = cms.string('75X_dataRun2_Prompt_ppAt5TeV_v1')

## ==== Filters ====
process.goodVertexFilter = cms.EDFilter("VertexSelector",
    src = cms.InputTag("offlinePrimaryVertices"),
    cut = cms.string("!isFake && abs(z) <= 25 && position.Rho <= 2 && tracksSize >= 2"),
    filter = cms.bool(True),
)

process.noScraping = cms.EDFilter("FilterOutScraping",
    applyfilter = cms.untracked.bool(True),
    debugOn = cms.untracked.bool(False),
    numtrack = cms.untracked.uint32(10),
    thresh = cms.untracked.double(0.25)
)

process.fastFilter = cms.Sequence(process.goodVertexFilter + process.noScraping)

##    __  __                       
##   |  \/  |_   _  ___  _ __  ___ 
##   | |\/| | | | |/ _ \| '_ \/ __|
##   | |  | | |_| | (_) | | | \__ \
##   |_|  |_|\__,_|\___/|_| |_|___/
##                                 
## ==== Merge CaloMuons and Tracks into the collection of reco::Muons  ====

InAcceptance = '((abs(eta)<1.2 && pt>=3.5) || (1.2<=abs(eta) && abs(eta)<2.1 && pt>=5.77-1.89*abs(eta)) || (2.1<=abs(eta) && abs(eta)<2.4 && pt>=1.8))'

from RecoMuon.MuonIdentification.calomuons_cfi import calomuons;
process.mergedMuons = cms.EDProducer("CaloMuonMerger",
    mergeTracks = cms.bool(True),
    mergeCaloMuons = cms.bool(False), # AOD
    muons     = cms.InputTag("muons"), 
    caloMuons = cms.InputTag("calomuons"),
    tracks    = cms.InputTag("generalTracks"),
    minCaloCompatibility = calomuons.minCaloCompatibility,
    ## Apply some minimal pt cut
    muonsCut     = cms.string(InAcceptance),
    caloMuonsCut = cms.string(InAcceptance),
    tracksCut    = cms.string(InAcceptance),
)

## ==== Trigger matching
process.load("MuonAnalysis.MuonAssociators.patMuonsWithTrigger_cff")
## with some customization
process.muonL1Info.maxDeltaR = 0.3
process.muonL1Info.fallbackToME1 = True
process.muonMatchHLTL1.maxDeltaR = 0.3
process.muonMatchHLTL1.fallbackToME1 = True
process.muonMatchHLTL2.maxDeltaR = 0.3
process.muonMatchHLTL2.maxDPtRel = 10.0
process.muonMatchHLTL3.maxDeltaR = 0.1
process.muonMatchHLTL3.maxDPtRel = 10.0

from MuonAnalysis.MuonAssociators.patMuonsWithTrigger_cff import *
changeRecoMuonInput(process, "mergedMuons")
switchOffAmbiguityResolution(process) # Switch off ambiguity resolution: allow multiple reco muons to match to the same trigger muon
addHLTL1Passthrough(process)

process.patTriggerFull.l1GtReadoutRecordInputTag = cms.InputTag("gtDigis","","RECO")                 
process.patTrigger.collections.remove("hltL3MuonCandidates")
process.patTrigger.collections.append("hltHIL3MuonCandidates")
process.muonMatchHLTL3.matchedCuts = cms.string('coll("hltHIL3MuonCandidates")')

## ==== Tag and probe definitions
from MuonAnalysis.TagAndProbe.common_variables_cff import *
process.load("MuonAnalysis.TagAndProbe.common_modules_cff")

TightId =  "isGlobalMuon && globalTrack.normalizedChi2 < 10 && globalTrack.hitPattern.numberOfValidMuonHits > 0 && numberOfMatchedStations > 1 && track.hitPattern.trackerLayersWithMeasurement > 5 && track.hitPattern.numberOfValidPixelHits > 0 && abs(dB) < 0.2"

HybridSoftId = "isTrackerMuon && isGlobalMuon && muonID('TMOneStationTight') && track.hitPattern.trackerLayersWithMeasurement > 5 && track.hitPattern.numberOfValidPixelHits > 0"

TRACK_CUTS = "track.isNonnull && track.numberOfValidHits > 10 && track.normalizedChi2 < 4 && track.hitPattern.pixelLayersWithMeasurement > 0"

HighPtTriggerFlags = cms.PSet(
   HIL2Mu5_NHitQ10 = cms.string("!triggerObjectMatchesByPath('HLT_HIL2Mu5_NHitQ10_v*',1,0).empty()"),
   HIL3Mu5_NHitQ15 = cms.string("!triggerObjectMatchesByPath('HLT_HIL3Mu5_NHitQ15_v*',1,0).empty()"),
   HIL2Mu7_NHitQ10 = cms.string("!triggerObjectMatchesByPath('HLT_HIL2Mu7_NHitQ10_v*',1,0).empty()"),
   HIL3Mu7_NHitQ15 = cms.string("!triggerObjectMatchesByPath('HLT_HIL3Mu7_NHitQ15_v*',1,0).empty()"),
   HIL2Mu15 = cms.string("!triggerObjectMatchesByPath('HLT_HIL2Mu15_v*',1,0).empty()"),
   HIL3Mu15 = cms.string("!triggerObjectMatchesByPath('HLT_HIL3Mu15_v*',1,0).empty()"),
   HIL2Mu20 = cms.string("!triggerObjectMatchesByPath('HLT_HIL2Mu20_v*',1,0).empty()"),
   HIL3Mu20 = cms.string("!triggerObjectMatchesByPath('HLT_HIL3Mu20_v*',1,0).empty()"),
)

LowPtTriggerFlags = cms.PSet(
   HIL2Mu3_NHitQ10 = cms.string("!triggerObjectMatchesByPath('HLT_HIL2Mu3_NHitQ10_v*',1,0).empty()"),
   HIL3Mu3_NHitQ15 = cms.string("!triggerObjectMatchesByPath('HLT_HIL3Mu3_NHitQ15_v*',1,0).empty()"),
)

TrigTagFlags = cms.PSet(HighPtTriggerFlags, LowPtTriggerFlags)

TrigProbeFlags = cms.PSet(
      HLTL1v0 = cms.string("!triggerObjectMatchesByPath('HLT_HIL1DoubleMu0_v*',1,0).empty()"),
      HLTL1v1 = cms.string("!triggerObjectMatchesByFilter('hltHIDoubleMu0L1Filtered').empty()"),
      HLTL1v2 = cms.string("(!triggerObjectMatchesByPath('HLT_HIL1DoubleMu0_v*',1,0).empty() && !triggerObjectMatchesByFilter('hltHIDoubleMu0L1Filtered').empty())"),
      )

process.tagMuons = cms.EDFilter("PATMuonSelector",
    src = cms.InputTag("patMuonsWithTrigger"),
    cut = cms.string(InAcceptance + ' && ' + HybridSoftId
       + " && (!triggerObjectMatchesByPath('HLT_HIL2Mu3_NHitQ10_v*',1,0).empty()"
       + "|| !triggerObjectMatchesByPath('HLT_HIL3Mu3_NHitQ15_v*',1,0).empty()"
       + "|| !triggerObjectMatchesByPath('HLT_HIL2Mu5_NHitQ10_v*',1,0).empty()"
       + "|| !triggerObjectMatchesByPath('HLT_HIL3Mu5_NHitQ15_v*',1,0).empty()"
       + "|| !triggerObjectMatchesByPath('HLT_HIL2Mu7_NHitQ10_v*',1,0).empty()"
       + "|| !triggerObjectMatchesByPath('HLT_HIL3Mu7_NHitQ15_v*',1,0).empty()"
       + "|| !triggerObjectMatchesByPath('HLT_HIL2Mu15_v*',1,0).empty()"
       + "|| !triggerObjectMatchesByPath('HLT_HIL3Mu15_v*',1,0).empty()"
       + "|| !triggerObjectMatchesByPath('HLT_HIL2Mu20_v*',1,0).empty()"
       + "|| !triggerObjectMatchesByPath('HLT_HIL3Mu20_v*',1,0).empty()"
       + ")"
       ),
)

process.oneTag  = cms.EDFilter("CandViewCountFilter", src = cms.InputTag("tagMuons"), minNumber = cms.uint32(1))

process.probeMuons = cms.EDFilter("PATMuonSelector",
    src = cms.InputTag("patMuonsWithTrigger"),
    cut = cms.string("isGlobalMuon"), 
)

process.muonDxyPVdzMinID = cms.EDProducer("MuonDxyPVdzmin",
    probes = cms.InputTag("probeMuons"),
)

process.tpPairs = cms.EDProducer("CandViewShallowCloneCombiner",
    cut = cms.string('2.5 < mass < 3.5'),
    decay = cms.string('tagMuons@+ probeMuons@-')
)

process.tnPairsDeltaPhiID = cms.EDProducer("DiMuonDeltaPhi",
    tagProbePairs = cms.InputTag("tpPairs"),
)

process.onePair = cms.EDFilter("CandViewCountFilter", src = cms.InputTag("tpPairs"), minNumber = cms.uint32(1))

process.tpTree = cms.EDAnalyzer("TagProbeFitTreeProducer",
    # choice of tag and probe pairs, and arbitration
    tagProbePairs = cms.InputTag("tpPairs"),
    arbitration   = cms.string("None"),
    # probe variables: all useful ones
    variables = cms.PSet(
        KinematicVariables,
	MuonIDVariables,
	TrackQualityVariables,
	GlobalTrackQualityVariables,
	StaOnlyVariables,
        dxyPVdzmin = cms.InputTag("muonDxyPVdzMinID","dxyPVdzmin"),
        dzPV       = cms.InputTag("muonDxyPVdzMinID","dzPV"),
    ),
    flags = cms.PSet(
       TrackQualityFlags,
       MuonIDFlags,
       LowPtTriggerFlags,
       HighPtTriggerFlags,
       TrigProbeFlags,
       TightHI = cms.string(TightId),
       HybridSoftHI = cms.string(HybridSoftId),
       StaTkSameCharge = cms.string("outerTrack.isNonnull && innerTrack.isNonnull && (outerTrack.charge == innerTrack.charge)"),
       outerValidHits = cms.string("outerTrack.isNonnull && outerTrack.numberOfValidHits > 0"),
    ),
    tagVariables = cms.PSet(
        KinematicVariables,
	MuonIDVariables,
	TrackQualityVariables,
	GlobalTrackQualityVariables,
	StaOnlyVariables,
        nVertices   = cms.InputTag("nverticesModule"),
    ),
    tagFlags = cms.PSet(
        TrigTagFlags
    ),
    pairVariables = cms.PSet(
        dz      = cms.string("daughter(0).vz - daughter(1).vz"),
        pt      = cms.string("pt"), 
        rapidity = cms.string("rapidity"),
        deltaR   = cms.string("deltaR(daughter(0).eta, daughter(0).phi, daughter(1).eta, daughter(1).phi)"),
        deltaPhi = cms.InputTag("tnPairsDeltaPhiID","deltaPhi"),
        probeMultiplicity = cms.InputTag("probeMultiplicity"),
        probeMultiplicity_TMGM = cms.InputTag("probeMultiplicityTMGM"),
    ),
    pairFlags = cms.PSet(
        BestJPsi = cms.InputTag("bestPairByJpsiMass"),
    ),
    isMC           = cms.bool(False),
    addRunLumiInfo = cms.bool(True),
    allProbes      = cms.InputTag("probeMuons")
)

process.tnpSimpleSequence = cms.Sequence(
    process.tagMuons +
    process.oneTag     +
    process.probeMuons +
    process.muonDxyPVdzMinID +
    process.tpPairs    +
    process.onePair    +
    process.tnPairsDeltaPhiID +
    process.nverticesModule +
    process.probeMultiplicities + 
    process.bestPairByJpsiMass + 
    process.tpTree
)

process.tagAndProbe = cms.Path( 
      process.fastFilter
    * process.mergedMuons
    * process.patMuonsWithTriggerSequence
    * process.tnpSimpleSequence
)

##    _____               _    _             
##   |_   _| __ __ _  ___| | _(_)_ __   __ _ 
##     | || '__/ _` |/ __| |/ / | '_ \ / _` |
##     | || | | (_| | (__|   <| | | | | (_| |
##     |_||_|  \__,_|\___|_|\_\_|_| |_|\__, |
##                                     |___/ 

## Then make another collection for standalone muons, using standalone track to define the 4-momentum
process.muonsSta = cms.EDProducer("RedefineMuonP4FromTrack",
    src   = cms.InputTag("muons"),
    track = cms.string("outer"),
)

## Match to trigger, to measure the efficiency of HLT tracking
from PhysicsTools.PatAlgos.tools.helpers import *
process.patMuonsWithTriggerSequenceSta = cloneProcessingSnippet(process, process.patMuonsWithTriggerSequence, "Sta")
process.muonMatchHLTL2Sta.maxDeltaR = 0.5
process.muonMatchHLTL3Sta.maxDeltaR = 0.5
massSearchReplaceAnyInputTag(process.patMuonsWithTriggerSequenceSta, "mergedMuons", "muonsSta")

## Define probes and T&P pairs
process.probeMuonsSta = cms.EDFilter("PATMuonSelector",
    src = cms.InputTag("patMuonsWithTriggerSta"),
    cut = cms.string("outerTrack.isNonnull"), # no real cut now
)

process.tpPairsSta = process.tpPairs.clone(decay = "tagMuons@+ probeMuonsSta@-", cut = '1. < mass < 6.')

process.tnPairsDeltaPhiSta = cms.EDProducer("DiMuonDeltaPhi",
    tagProbePairs = cms.InputTag("tpPairsSta"),
)

process.onePairSta = cms.EDFilter("CandViewCountFilter", src = cms.InputTag("tpPairsSta"), minNumber = cms.uint32(1))

process.staToTkMatch.maxDeltaR     = 0.3
process.staToTkMatch.maxDeltaPtRel = 2.
process.staToTkMatchNoJPsi.maxDeltaR     = 0.3
process.staToTkMatchNoJPsi.maxDeltaPtRel = 2.

process.load("MuonAnalysis.TagAndProbe.tracking_reco_info_cff")

process.tpTreeSta = process.tpTree.clone(
    tagProbePairs = "tpPairsSta",
    arbitration   = "OneProbe",
    variables = cms.PSet(
        KinematicVariables, 
        StaOnlyVariables,
        ## track matching variables
        tk_deltaR     = cms.InputTag("staToTkMatch","deltaR"),
        tk_deltaEta   = cms.InputTag("staToTkMatch","deltaEta"),
        tk_deltaR_NoJPsi   = cms.InputTag("staToTkMatchNoJPsi","deltaR"),
        tk_deltaEta_NoJPsi = cms.InputTag("staToTkMatchNoJPsi","deltaEta"),
    ),
    flags = cms.PSet(
        outerValidHits = cms.string("outerTrack.isNonnull && outerTrack.numberOfValidHits > 0"),
        TM  = cms.string("isTrackerMuon"),
        Glb = cms.string("isGlobalMuon"),
        Tk  = cms.string("track.isNonnull"),
        isNonMuonSeeded = cms.string("innerTrack.isNonnull && innerTrack.originalAlgo<13"), #   muonSeededStepInOut = 13
        StaTkSameCharge = cms.string("outerTrack.isNonnull && innerTrack.isNonnull && (outerTrack.charge == innerTrack.charge)"),
    ),
    tagVariables = cms.PSet(
        pt = cms.string("pt"),
        eta = cms.string("eta"),
        phi = cms.string("phi"),
        nVertices = cms.InputTag("nverticesModule"),
    ),
    tagFlags = cms.PSet(
        TrigTagFlags
    ),
    pairVariables = cms.PSet(
        dz      = cms.string("daughter(0).vz - daughter(1).vz"),
        pt      = cms.string("pt"), 
        rapidity = cms.string("rapidity"),
        deltaR   = cms.string("deltaR(daughter(0).eta, daughter(0).phi, daughter(1).eta, daughter(1).phi)"),
        deltaPhi = cms.InputTag("tnPairsDeltaPhiSta","deltaPhi"),
    ),
    pairFlags = cms.PSet(),
    allProbes     = cms.InputTag("probeMuonsSta")
)

process.tnpSimpleSequenceSta = cms.Sequence(
    process.tagMuons +
    process.oneTag     +
    process.probeMuonsSta   +
    process.tpPairsSta      +
    process.onePairSta      +
    process.tnPairsDeltaPhiSta +
    process.nverticesModule +
    process.staToTkMatchSequenceJPsi +
    process.tpTreeSta
)

process.tagAndProbeSta = cms.Path( 
      process.fastFilter
    * process.muonsSta
    * process.patMuonsWithTriggerSequenceSta
    * process.tnpSimpleSequenceSta
)

#--------------------------------------------------------------------
##    ____                   _____               _      ____            _               
##   | __ )  __ _ _ __ ___  |_   _| __ __ _  ___| | __ |  _ \ _ __ ___ | |__   ___  ___ 
##   |  _ \ / _` | '__/ _ \   | || '__/ _` |/ __| |/ / | |_) | '__/ _ \| '_ \ / _ \/ __|
##   | |_) | (_| | | |  __/   | || | | (_| | (__|   <  |  __/| | | (_) | |_) |  __/\__ \
##   |____/ \__,_|_|  \___|   |_||_|  \__,_|\___|_|\_\ |_|   |_|  \___/|_.__/ \___||___/
##                                                                                      
##   

process.probeMuonsTrk = cms.EDFilter("PATMuonSelector",
    src = cms.InputTag("patMuonsWithTrigger"),
    cut = cms.string(TRACK_CUTS + ' && ' + InAcceptance + ' && ' + 'innerTrack.isNonnull && innerTrack.originalAlgo<13'), #   muonSeededStepInOut = 13              
)

process.muonDxyPVdzMinTrk = cms.EDProducer("MuonDxyPVdzmin",
    probes = cms.InputTag("probeMuonsTrk"),
)

process.tpPairsTrk = cms.EDProducer("CandViewShallowCloneCombiner",
    cut = cms.string('2.5 < mass < 3.5'),
    decay = cms.string('tagMuons@+ probeMuonsTrk@-')
)

process.tnPairsDeltaPhiTrk = cms.EDProducer("DiMuonDeltaPhi",
    tagProbePairs = cms.InputTag("tpPairsTrk"),
)

process.onePairTrk = cms.EDFilter("CandViewCountFilter",
     src = cms.InputTag('tpPairsTrk'),
     minNumber = cms.uint32(1),
)

process.tpTreeTrk = cms.EDAnalyzer("TagProbeFitTreeProducer",
     # choice of tag and probe pairs, and arbitration
     tagProbePairs = cms.InputTag("tpPairsTrk"),
     arbitration   = cms.string("OneProbe"),
     # probe variables: all useful ones
     variables = cms.PSet(
        KinematicVariables,
        StaOnlyVariables,
        dxyPVdzmin = cms.InputTag("muonDxyPVdzMinTrk","dxyPVdzmin"),
        dzPV       = cms.InputTag("muonDxyPVdzMinTrk","dzPV"),
     ),
     flags = cms.PSet(
        isSTA = cms.string("isStandAloneMuon"),
        outerValidHits  = cms.string("? outerTrack.isNull() ? 0 : outerTrack.numberOfValidHits > 0"),
     ),
     tagVariables = cms.PSet(
        TrackQualityVariables,
        GlobalTrackQualityVariables,
        pt  = cms.string("pt"),
        eta = cms.string("eta"),
        abseta = cms.string("abs(eta)"),
        l2dr  = cms.string("? triggerObjectMatchesByCollection('hltL2MuonCandidates').empty() ? 999 : "+
                           " deltaR( eta, phi, " +
                           "         triggerObjectMatchesByCollection('hltL2MuonCandidates').at(0).eta, "+
                           "         triggerObjectMatchesByCollection('hltL2MuonCandidates').at(0).phi ) "),

     ),
     tagFlags     = cms.PSet(
        TrigTagFlags,
     ),
     pairVariables = cms.PSet(
        pt  = cms.string("pt"),
        y = cms.string("rapidity"),
        absy = cms.string("abs(rapidity)"),
        deltaR   = cms.string("deltaR(daughter(0).eta, daughter(0).phi, daughter(1).eta, daughter(1).phi)"),
        deltaPhi = cms.InputTag("tnPairsDeltaPhiTrk","deltaPhi"),
     ),
     pairFlags = cms.PSet(),
     isMC           = cms.bool(False),
     #addRunLumiInfo = cms.bool(True),
     allProbes     = cms.InputTag("probeMuonsTrk")
)

process.tnpSimpleSequenceTrk = cms.Sequence(
    process.probeMuonsTrk +
    process.muonDxyPVdzMinTrk +
    process.tpPairsTrk    +
    process.onePairTrk +
    process.tnPairsDeltaPhiTrk +
    process.tpTreeTrk
)

process.tagAndProbeTrk = cms.Path(
      process.fastFilter
    * process.tnpSimpleSequenceTrk
)

process.RandomNumberGeneratorService.tkTracksNoJPsi = cms.PSet( initialSeed = cms.untracked.uint32(81) )
process.RandomNumberGeneratorService.tkTracksNoBestJPsi = cms.PSet( initialSeed = cms.untracked.uint32(81) )

process.schedule = cms.Schedule(
   process.tagAndProbe, 
   process.tagAndProbeSta,
   process.tagAndProbeTrk,
)

process.TFileService = cms.Service("TFileService", fileName = cms.string("tnpJPsi_Data_pp5TeV_AOD.root"))
