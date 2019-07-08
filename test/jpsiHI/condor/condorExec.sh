#!/bin/bash
#cd /afs/cern.ch/work/j/jjay/public/TagAndProbe_pPb/CMSSW_8_0_30/src
#eval `scramv1 runtime -sh`
cd ../
cmsenv
cmsRun tp_Ana_Trig_$1_pPb.py $2
