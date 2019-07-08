#!/bin/bash
cd /afs/cern.ch/work/j/jjay/public/TagAndProbe_pPb_SL7/CMSSW_8_0_30/
#cd /afs/cern.ch/work/j/jjay/public/TagAndProbe_pPb/CMSSW_8_0_30/src
eval `scramv1 runtime -sh`
cd MuonAnalysis/TagAndProbe/test/jpsiHI
cmsRun tp_Ana_${2}_${1}_pPb.py $3 
