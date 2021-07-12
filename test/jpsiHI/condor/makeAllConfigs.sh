#!/bin/bash
source /afs/cern.ch/user/j/jjay/.bashrc
cd /afs/cern.ch/work/j/jjay/public/TagAndProbe_pPb_SL7/CMSSW_8_0_30/
#cd /afs/cern.ch/work/j/jjay/public/TagAndProbe_pPb/CMSSW_8_0_30/src
eval `scramv1 runtime -sh`
cd MuonAnalysis/TagAndProbe/test/jpsiHI/condor
for whichFunc in 0 1 2 3
do
  ./makeSplitConfig.sh Trig MC $whichFunc 0
  ./makeSplitConfig.sh Trig RD $whichFunc 0

  ./makeSplitConfig.sh TrkM MC $whichFunc 0

  ./makeSplitConfig.sh MuIDfromGT MC $whichFunc 0
  ./makeSplitConfig.sh MuIDfromGTonePair RD $whichFunc 0
  ./makeSplitConfig.sh MuIDfromGTonePair MC $whichFunc 0

  ./makeSplitConfig.sh MuIDfromTM MC $whichFunc 0
  ./makeSplitConfig.sh MuIDfromTM RD $whichFunc 0

  for whichChunk in {0..10}
  do
    ./makeSplitConfig.sh TrkM RD $whichFunc $whichChunk
    ./makeSplitConfig.sh MuIDfromGT RD $whichFunc $whichChunk
  done
done
