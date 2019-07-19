#!/bin/bash
echo "copying file over"
cp /eos/cms/store/group/phys_heavyions/okukral/TagAndProbe2016/LowPt/MC_notweighted/tnpJPsi_MC_Pbp-NoWeightSkimmed.root .
#cp /eos/cms/store/group/phys_heavyions/okukral/TagAndProbe2016/LowPt/tnpJPsi_MC_Pbp_noWeight.root .
root -b -l -q AddWeightMC_2D_Pbp.C
mkdir weights_Pbp_$1
cp AddWeightMC_2D_Pbp.C weights_Pbp_$1/AddWeightMC_2D_Pbp_$1.C
mv *.png weights_Pbp_$1/
mv histfile2d.root weights_Pbp_$1/
mv tnpJPsi_MC_Pbp_noWeight.root weights_Pbp_$1/tnpJPsi_MC_Pbp_Weighted.root

