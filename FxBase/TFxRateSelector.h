#ifndef TFxRateSelector_H
#define TFxRateSelector_H

#include <TTree.h>
#include <TSelector.h>

class TFxRateObj;
class TH1D;

class TFxRateSelector: public TSelector {

public:

	TFxRateSelector(TTree *tree = 0);
	virtual ~TFxRateSelector() {
		delete fRateObj;
	}
	virtual Int_t Version() const {
		return 2;
	}
	virtual void Begin(TTree */*tree*/) {
		;
	}
	virtual void SlaveBegin(TTree *tree);
	virtual void Init(TTree *tree);
	virtual Bool_t Notify() {
		return kTRUE;
	}
	virtual Bool_t Process(Long64_t entry);
	virtual Int_t GetEntry(Long64_t entry, Int_t getall = 0) {
		return fChain ? fChain->GetTree()->GetEntry(entry, getall) : 0;
	}
	virtual void SlaveTerminate() {
		;
	}
	virtual void Terminate();
private:

	TTree *fChain;   //!pointer to the analyzed TTree or TChain
	TFxRateObj *fRateObj; 	//! pointer to rate object
	TH1D *fHist;		//! histogram

ClassDef(TFxRateSelector, 1)
	;
};

#endif
