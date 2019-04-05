#!/bin/bash
#Only one argument: $1 = date.  // Before: $1 = TYPE (eta, pt), $2 = nBins (100, 100), $3 = LowLimit (-2.4, 0 (actual low value 1.8)), $4 = HighLimit (2.4, 15), $5 = Date       
#Only eta and pt for now. (abseta, 50, 0, 2.4) and (p, 200, 0 (actual low value 3.5), 20).
mkdir weights_$1
for vartype in "eta 100 -2.4 2.4" "pt 100 0 40"
do
set -- $1 $vartype
mkdir weights_$1/$2
cp /afs/cern.ch/user/s/stuli/stuliWork/public/TnP_run2/Current/CMSSW_8_0_25/src/MuonAnalysis/TagAndProbe/macros/LowPtWeights/AddWeightMC.C /afs/cern.ch/user/s/stuli/stuliWork/public/TnP_run2/Current/CMSSW_8_0_25/src/MuonAnalysis/TagAndProbe/macros/LowPtWeights/AddWeightMC_$2_$1.C
sed -i "s/TYPE/$2/g;" /afs/cern.ch/user/s/stuli/stuliWork/public/TnP_run2/Current/CMSSW_8_0_25/src/MuonAnalysis/TagAndProbe/macros/LowPtWeights/AddWeightMC_$2_$1.C
sed -i "s/nBins/$3/g;" /afs/cern.ch/user/s/stuli/stuliWork/public/TnP_run2/Current/CMSSW_8_0_25/src/MuonAnalysis/TagAndProbe/macros/LowPtWeights/AddWeightMC_$2_$1.C
sed -i "s/LowLimit/$4/g;" /afs/cern.ch/user/s/stuli/stuliWork/public/TnP_run2/Current/CMSSW_8_0_25/src/MuonAnalysis/TagAndProbe/macros/LowPtWeights/AddWeightMC_$2_$1.C
sed -i "s/HighLimit/$5/g;" /afs/cern.ch/user/s/stuli/stuliWork/public/TnP_run2/Current/CMSSW_8_0_25/src/MuonAnalysis/TagAndProbe/macros/LowPtWeights/AddWeightMC_$2_$1.C
sed -i "s/AddWeightMC/AddWeightMC_$2_$1/g;" /afs/cern.ch/user/s/stuli/stuliWork/public/TnP_run2/Current/CMSSW_8_0_25/src/MuonAnalysis/TagAndProbe/macros/LowPtWeights/AddWeightMC_$2_$1.C
cp /afs/cern.ch/user/s/stuli/stuliWork/public/TnP_run2/Current/CMSSW_8_0_25/src/MuonAnalysis/TagAndProbe/macros/LowPtWeights/AddWeightMC_$2_$1.C /afs/cern.ch/user/s/stuli/stuliWork/public/TnP_run2/Current/CMSSW_8_0_25/src/MuonAnalysis/TagAndProbe/macros/LowPtWeights/weights_$1/$2/
root -l -q -b /afs/cern.ch/user/s/stuli/stuliWork/public/TnP_run2/Current/CMSSW_8_0_25/src/MuonAnalysis/TagAndProbe/macros/LowPtWeights/AddWeightMC_$2_$1.C
#This line is optional ^^^ You can run later. But if you do, don't remove it below!
rm /afs/cern.ch/user/s/stuli/stuliWork/public/TnP_run2/Current/CMSSW_8_0_25/src/MuonAnalysis/TagAndProbe/macros/LowPtWeights/AddWeightMC_$2_$1.C
mv /afs/cern.ch/user/s/stuli/stuliWork/public/TnP_run2/Current/CMSSW_8_0_25/src/MuonAnalysis/TagAndProbe/macros/LowPtWeights/*.png /afs/cern.ch/user/s/stuli/stuliWork/public/TnP_run2/Current/CMSSW_8_0_25/src/MuonAnalysis/TagAndProbe/macros/LowPtWeights/weights_$1/$2/
done
mv /afs/cern.ch/user/s/stuli/stuliWork/public/TnP_run2/Current/InputFiles/LowPt_Nov2018/tnpJPsi_MC-bothDir_noWeight.root /afs/cern.ch/user/s/stuli/stuliWork/public/TnP_run2/Current/InputFiles/LowPt_Nov2018/tnpJPsi_MC-bothDir_Weighted_$1.root
cp /eos/cms/store/group/phys_heavyions/okukral/TagAndProbe2016/LowPt/tnpJPsi_MC-bothDir_noWeight.root /afs/cern.ch/user/s/stuli/stuliWork/public/TnP_run2/Current/InputFiles/LowPt_Nov2018/
