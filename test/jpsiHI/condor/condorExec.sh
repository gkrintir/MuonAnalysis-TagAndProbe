#!/bin/bash
cd /afs/cern.ch/user/s/stuli/stuliWork/public/TnP_run2/Current/CMSSW_8_0_30/src
eval `scramv1 runtime -sh`
cd MuonAnalysis/TagAndProbe/test/jpsiHI
cmsRun tp_Ana_Trig_${1}_pPb.py $2
