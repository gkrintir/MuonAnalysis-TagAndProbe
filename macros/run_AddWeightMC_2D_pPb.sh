#!/bin/bash
echo "copying file over"
cp /eos/cms/store/group/phys_heavyions/okukral/TagAndProbe2016/LowPt/MC_notweighted/tnpJPsi_MC_pPb-NoWeightSkimmed.root .
#cp /eos/cms/store/group/phys_heavyions/okukral/TagAndProbe2016/LowPt/tnpJPsi_MC_pPb_noWeight.root .
root -b -l -q AddWeightMC_2D_pPb.C
mkdir weights_pPb_$1
cp AddWeightMC_2D_pPb.C weights_pPb_$1/AddWeightMC_2D_pPb_$1.C
mv *.png weights_pPb_$1/
mv histfile2d.root weights_pPb_$1/
mv tnpJPsi_MC_pPb_noWeight.root weights_pPb_$1/tnpJPsi_MC_pPb_Weighted.root

