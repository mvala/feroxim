Int_t SETUP(TList *input = 0) {

   if (gSystem->Load("libFxBase.so") < 0) return 1;

   // Set the include paths
   gROOT->ProcessLine(".include FxBase");

   // Set our location, so that other packages can find us
   gSystem->Setenv("FxBase_INCLUDE", "FxBase");

   return 0;
}
