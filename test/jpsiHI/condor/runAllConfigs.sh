#!/bin/bash
for whichFunc in 0 1 2 3
do
  #whichFunc=0
  #condor_submit condorConfig_tnp_Trig_MC_pPb_${whichFunc}_0.sub
  #condor_submit condorConfig_tnp_Trig_RD_pPb_${whichFunc}_0.sub
  #condor_submit condorConfig_tnp_TrkM_MC_pPb_${whichFunc}_0.sub
  #condor_submit condorConfig_tnp_MuIDfromGT_MC_pPb_${whichFunc}_0.sub
  #condor_submit condorConfig_tnp_MuIDfromGT_RD_pPb_${whichFunc}_1.sub
  #condor_submit condorConfig_tnp_MuIDfromTM_MC_pPb_${whichFunc}_0.sub
  #condor_submit condorConfig_tnp_MuIDfromTM_RD_pPb_${whichFunc}_0.sub
  for whichChunk in {1..4}
  do
    #condor_submit condorConfig_tnp_TrkM_RD_pPb_${whichFunc}_${whichChunk}.sub
    condor_submit condorConfig_tnp_MuIDfromGT_RD_pPb_${whichFunc}_${whichChunk}.sub
  done
done
