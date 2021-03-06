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

void GeneratePredictors(Int_t ls=100, Double_t q=1, Double_t m=0.0, Double_t phi=0.0) {

    TString filename = "/home/mvala/git/github/mvala/feroxim/macros/files.txt";
	filename = "/eos/saske.sk/scratch/files_eos.txt";

    const char *dsname = "myds";

    Bool_t refreshDS = kTRUE;
//	refreshDS = kFALSE;

    TString proofSource = "";
//	proofSource="mgmt1";

    TFileCollection *fc = new TFileCollection("myfc", "");
    fc->AddFromFile(filename.Data());

    TProof *p = TProof::Open(proofSource.Data(),"workers=1");
    if (!p) return;
//	p->SetParameter("PROOF_CacheSize", 2e3);

    p->UploadPackage("FxBase.par");
    if (p->EnablePackage("FxBase")) return;

//    if (!p->GetDataSet(dsname) || refreshDS) {
//        if (refreshDS) p->RemoveDataSet(dsname);
//        p->RegisterDataSet(dsname, fc);
//        p->VerifyDataSet(dsname);
//    }
//    p->ShowDataSets(dsname);

    TString outFileName = TString::Format("%s/FXSIM_%d_%.2f_%.2f_%.2f.root",gSystem->WorkingDirectory(),ls,q,m,phi);
    TFxRateSelector *sel = new TFxRateSelector();
    sel->SetFilename(outFileName.Data());

    Printf("Output file => %s",outFileName.Data());
//    TFxPredictor *predictor = new TFxPredictor(1300,8,1,0);
    TFxPredictor *predictor = new TFxPredictor(ls,q,m,phi);
    sel->SetPredictor(predictor);


//    p->Process(dsname, sel, "", 1e5);
    p->Process(dsname, sel);
//    p->Process(fc, sel);
//    p->Process(fc, sel, "" , 41.3*1e6, 30.3*1e6);
}
