#include <TError.h>
#include <TH1.h>
#include <TFile.h>
#include <TTree.h>
#include <TFxRateObj.h>
#include <TFxPredictorObj.h>
#include <TFxPredictor.h>

#include "TFxRateSelector.h"

ClassImp(TFxRateSelector)

TFxRateSelector::TFxRateSelector(TTree * /*tree*/) :
        TSelector(), fChain(0), fRate(0), fPredictorObj(0), fPredictor(0), fHist(0), fFilename(
                "noname.root"), fOutputFile(0), fOutputTree(0),fRates(0),fNRatesInCache(0) {

}

TFxRateSelector::~TFxRateSelector() {
    delete fRate;
    delete fPredictor;
}

void TFxRateSelector::Init(TTree *tree) {
    if (!tree) return;
    fChain = tree;
    fRate = new TFxRateObj();
    fChain->SetBranchAddress("epro", &fRate);
}

Bool_t TFxRateSelector::Notify() {
    ::Info("",fChain->GetCurrentFile()->GetName());
    return kTRUE;
}

void TFxRateSelector::Begin(TTree* /*tree*/) {
}

void TFxRateSelector::SlaveBegin(TTree * /*tree*/) {
    TString option = GetOption();

    fHist = new TH1D("h", "My Hist", 1000, 1.0, 2.0);
    fOutput->Add(fHist);

    ::Info("TFxRateSelector::SlaveBegin", "Creating output file %s ...",
            fFilename.Data());
    fOutputFile = TFile::Open(fFilename.Data(), "RECREATE");
    if (fOutputFile) {
        fPredictorObj = new TFxPredictorObj();
        fOutputTree = new TTree("predictTree", "EkoPhysiscs Predictor Object");
        fOutputTree->Branch("predictor", &fPredictorObj);
    } else {
        ::Error("TFxRateSelector::SlaveBegin",
                "Output file was not created !!!");
    }

    fRates = new TArrayD(fPredictor->GetLs());

}

Bool_t TFxRateSelector::Process(Long64_t entry) {

    GetEntry(entry);

    fHist->Fill(fRate->GetRate1());
//    Printf("%f", fRate->GetRate1());
//    fRate->GetDateTime()->Print();

//    PrintArray(fRates);

    if (fNRatesInCache < fRates->GetSize()) {
        fRates->AddAt(fRate->GetRate1(),fNRatesInCache);
        fNRatesInCache++;
        return kTRUE;
    } else {
        ShiftArray(fRates);
        fRates->AddAt(fRate->GetRate1(),fRates->GetSize()-1);
    }

    fPredictorObj->Reset();
    fPredictorObj->SetMoS(fPredictor->Calulate(fRates));
    fOutputTree->Fill();
    return kTRUE;
}

void TFxRateSelector::SlaveTerminate() {
    fOutputTree->Print("all");
    fOutputFile->Write();
//    fOutputFile->Close();
    delete fOutputFile;
    delete fRates;
}

void TFxRateSelector::Terminate() {
    fHist = dynamic_cast<TH1D*>(fOutput->FindObject("h"));
    if (fHist) fHist->DrawCopy();

}

Int_t TFxRateSelector::Version() const {
    return 2;
}

Int_t TFxRateSelector::GetEntry(Long64_t entry, Int_t getall) {
    return fChain ? fChain->GetTree()->GetEntry(entry, getall) : 0;
}

const TString& TFxRateSelector::GetFilename() const {
    return fFilename;
}

void TFxRateSelector::SetFilename(const TString& filename) {
    fFilename = filename;
}

TFxPredictor* TFxRateSelector::GetPredictor() const {
    return fPredictor;
}

void TFxRateSelector::SetPredictor(TFxPredictor*predictor) {
    fPredictor = predictor;
}

void TFxRateSelector::ShiftArray(TArrayD* array) {

    for (Int_t i = 1; i < array->GetSize(); i++) {
        array->AddAt(array->At(i),i-1);
//        Printf ("%d -> %d", i, i-1);
    }
    array->AddAt(0.0,array->GetSize()-1);
}

void TFxRateSelector::PrintArray(TArrayD* array) {

    for (Int_t i = 0; i < array->GetSize(); i++) {
        Printf ("[%d]-> %f", i, array->At(i));
    }
}
