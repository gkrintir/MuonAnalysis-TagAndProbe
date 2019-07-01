from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()

config.section_('General')
config.General.requestName     = 'TNP_Psi1SToMuMu_pTMu-2p5_pPb-Bst_8p16-Pythia8-pPb816Summer16DR-pPbBst_80X_mcRun2_pA_v4-v3'
config.General.workArea        = 'crab_projects'
config.General.transferOutputs = True
config.General.transferLogs    = False

config.section_('JobType')
config.JobType.pluginName  = 'Analysis'
config.JobType.psetName    = 'tnp_pPb_mc.py'
config.JobType.maxMemoryMB = 2500
config.JobType.outputFiles = ['tnpJPsi_MC_pPb_AOD.root']
config.JobType.allowUndistributedCMSSW = True #allow use of SL7

config.section_('Data')
config.Data.inputDataset  = '/Psi1SToMuMu_pTMu-2p5_pPb-Bst_8p16-Pythia8/pPb816Summer16DR-pPbBst_80X_mcRun2_pA_v4-v1/AODSIM'
config.Data.inputDBS      = 'global'
config.Data.unitsPerJob   = 10 #3 was suggested by dryrun, but turned out to be too small
config.Data.totalUnits   = -1
config.Data.splitting     = 'FileBased'
config.Data.outLFNDirBase = '/store/group/phys_heavyions/dileptons/%s/TagAndProbe2016/%s' % (getUsernameFromSiteDB(), config.General.requestName)
config.Data.publication   = False

config.section_('Site')
config.Site.storageSite = 'T2_CH_CERN'
