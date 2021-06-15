#include "cutThingsFromSkim_Jared.C"

void makeFourQuarters(int whichChunk=1) {

  //TString filein = "/eos/cms/store/group/phys_heavyions/okukral/TagAndProbe2016/LowPt/tnpJPsi_Data_bothDir_noTC_v5.root";
  TString filein = "/eos/cms/store/group/phys_heavyions/okukral/TagAndProbe2016/LowPt/tnpJPsi_Data_bothDir_v5_NEW.root";
  TString fileout = Form("/eos/cms/store/group/phys_heavyions/dileptons/jjay/TagAndProbe2016/tnpJPsi_Data_bothDir_noTC_v5_forTM_Quarter%i.root",whichChunk);
  cutThingsFromSkim_Jared(filein.Data(), fileout.Data(), "MuID", 1, whichChunk);

}
