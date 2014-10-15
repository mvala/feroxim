#ifndef __CINT__
#include <Riostream.h>
#include <TChain.h>
#include <TString.h>
#include <TFileCollection.h>
#include <TProof.h>
#include <TFxRateObj.h>
#include <TFxRateSelector.h>
#include <TFxPredictor.h>
#endif

void GeneratePredictors(Bool_t refreshDS = kFALSE) {

    TString filename = "/home/mvala/git/github/mvala/feroxim/macros/files.txt";
//	filename = "/home/mvala/git/github/mvala/feroxim/macros/files_eos.txt";

    const char *dsname = "myds";
//	refreshDS = kTRUE;

    TString proofSource = "";
//	proofSource="mgmt1";

    TFileCollection *fc = new TFileCollection("myfc", "");
    fc->AddFromFile(filename.Data());

    TProof *p = TProof::Open(proofSource.Data(),"workers=1");
    if (!p) return;
//	p->SetParameter("PROOF_CacheSize", 2e3);

    p->UploadPackage("FxBase.par");
    if (p->EnablePackage("FxBase")) return;

    if (!p->GetDataSet(dsname) || refreshDS) {
        if (refreshDS) p->RemoveDataSet(dsname);
        p->RegisterDataSet(dsname, fc);
        p->VerifyDataSet(dsname);
    }
    p->ShowDataSets(dsname);

    TFxRateSelector *sel = new TFxRateSelector();
    sel->SetFilename("/tmp/my.root");

    TFxPredictor *predictor = new TFxPredictor(1300,8,1,0);
    sel->SetPredictor(predictor);


//    p->Process(fc, sel, "", 1e7);
    p->Process(fc, sel);
}
