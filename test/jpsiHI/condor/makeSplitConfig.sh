#!/bin/bash
cp condorConfig_tnp_TrkM_${2}_pPb_generalForm.sub condorConfig_tnp_${1}_${2}_pPb_${3}_${4}.sub
sed -i "s/whichFunc/$3/g;" condorConfig_tnp_${1}_${2}_pPb_${3}_${4}.sub
sed -i "s/whichChunk/$4/g;" condorConfig_tnp_${1}_${2}_pPb_${3}_${4}.sub
sed -i "s/TrkM/$1/g;" condorConfig_tnp_${1}_${2}_pPb_${3}_${4}.sub

