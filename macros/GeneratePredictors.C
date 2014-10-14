#ifndef __CINT__
#include <Riostream.h>
#include <TChain.h>
#include <TFileCollection.h>
#include <TProof.h>
#include <TFxRateObj.h>
#include <TFxRateSelector.h>
#endif

void GeneratePredictors(Bool_t refreshDS = kFALSE) {

//	const char *filename =
//			"/home/mvala/git/github/mvala/feroxim/macros/files.txt";
	const char *filename =
			"/home/mvala/git/github/mvala/feroxim/macros/files_eos.txt";

	const char *dsname = "myds";
//	refreshDS = kTRUE;

	TFileCollection *fc = new TFileCollection("myfc", "");
	fc->AddFromFile(filename);

	TProof *p = TProof::Open("");
	if (!p)
		return;
//	p->SetParameter("PROOF_CacheSize", 2e3);

	p->UploadPackage("FxBase.par");
	if (p->EnablePackage("FxBase"))
		return;

	if (!p->GetDataSet(dsname) || refreshDS) {
		if (refreshDS)
			p->RemoveDataSet(dsname);
		p->RegisterDataSet(dsname, fc);
		p->VerifyDataSet(dsname);
	}
	p->ShowDataSets(dsname);

	TFxRateSelector *sel = new TFxRateSelector();
	p->Process(fc, sel);
}
