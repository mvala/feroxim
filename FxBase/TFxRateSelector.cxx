#include <TH1.h>
#include <TFxRateObj.h>

#include "TFxRateSelector.h"

ClassImp(TFxRateSelector)

TFxRateSelector::TFxRateSelector(TTree * /*tree*/) :
		TSelector(), fChain(0), fRateObj(0), fHist(0) {

}

void TFxRateSelector::Init(TTree *tree) {
	if (!tree)
		return;
	fChain = tree;

	fRateObj = new TFxRateObj();
	fChain->SetBranchAddress("epro", &fRateObj);

}

void TFxRateSelector::SlaveBegin(TTree * /*tree*/) {
	TString option = GetOption();

	fHist = new TH1D("h", "My Hist", 1000, 1.0, 2.0);
	fOutput->Add(fHist);

}

Bool_t TFxRateSelector::Process(Long64_t entry) {

	GetEntry(entry);

	fHist->Fill(fRateObj->GetRate1());

//	Printf ("Entry = %d" ,GetEntry(entry));
	return kTRUE;
}

void TFxRateSelector::Terminate() {
	fHist = dynamic_cast<TH1D*>(fOutput->FindObject("h"));
	if (fHist)
		fHist->DrawCopy();
}
