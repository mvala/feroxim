#ifndef TFxRateSelector_H
#define TFxRateSelector_H

#include <TTree.h>
#include <TSelector.h>

class TFxRateObj;
class TFxPredictorObj;
class TFxPredictor;
class TFile;
class TTree;
class TH1D;


class TFxRateSelector: public TSelector {

public:

    TFxRateSelector(TTree *tree = 0);
    virtual ~TFxRateSelector();

    virtual Int_t Version() const;
    virtual void Begin(TTree */*tree*/);
    virtual void SlaveBegin(TTree *tree);
    virtual void Init(TTree *tree);
    virtual Bool_t Notify();
    virtual Bool_t Process(Long64_t entry);
    virtual Int_t GetEntry(Long64_t entry, Int_t getall = 0);
    virtual void SlaveTerminate();
    virtual void Terminate();

    const TString& GetFilename() const;
    void SetFilename(const TString& filename);

    TFxPredictor* GetPredictor() const;
    void SetPredictor(TFxPredictor* predictor);

    void ShiftArray(TArrayD *array);
    void PrintArray(TArrayD *array);

private:

    TTree *fChain;                  //!pointer to the analyzed TTree or TChain
    TFxRateObj *fRate; 	            //! pointer to rate object
    TFxPredictorObj *fPredictorObj; //! pointer to predictor Object
    TFxPredictor *fPredictor;       // pointer to Predictor
    TH1D *fHist;		            //! histogram
    TString fFilename;              //  Output file name
    TFile *fOutputFile;             //! Output file
    TTree *fOutputTree;             //! Output tree
    TArrayD *fRates;                //! Array of temporary rates
    Int_t fNRatesInCache;           //! N rates in cache


ClassDef(TFxRateSelector, 1)


};

#endif
