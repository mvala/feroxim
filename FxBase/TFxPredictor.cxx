//
// Class TFxPredictor
//
// TODO
//
// authors:
//          Martin Vala (mvala@saske.sk)
//


#include <TArrayD.h>
#include <TMath.h>

#include "TFxPredictor.h"

ClassImp(TFxPredictor)

//_________________________________________________________________________________________________
TFxPredictor::TFxPredictor(Int_t ls, Double_t pq, Double_t m, Double_t phi) :
        TObject(), fLs(ls), fPQ(pq), fM(m), fPhi(phi) {
//
// Std constructor
//

}

//_________________________________________________________________________________________________
TFxPredictor::~TFxPredictor() {
//
// Destructor
//

}

//_________________________________________________________________________________________________
void TFxPredictor::Reset() {
}

Double_t TFxPredictor::Calulate(TArrayD *rates) {

    // setting m to 0.0
    Double_t m = -1.0;

    // TODO calculate min, max
    Double_t min = 1.0;
    Double_t max = 2.0;

    if (rates->GetSize() < fLs) return -1.0;

    Double_t tau, stand, x, fcs;
    for (Int_t i = 0; i < rates->GetSize(); i++) {
        tau = rates->At(i);
        stand = (tau - min) / (max - min);
        x = 2. * TMath::Pi() * fM * i / (fLs + 1.);
        fcs = (1. + TMath::Cos(x + fPhi)) / 2.;
        m = m + TMath::Power(TMath::Abs(stand - fcs), fPQ);

    }
    m = m / (fLs + 1.);
    m = TMath::Power(m, 1 / fPQ);

//    ::Info("", "m=%f", m);

//    // t >= pLs
//
//    for (int th = t; th <= t + pLs; th++) {
//        h = th - t;
//        ptau = ... // currency rate at th
//        pstand = (ptau-pmin)/(pmax-pmin);
//        x = 2.*pi*pM*h/(pLs+1.);
//        fcs = (1. + cos(x+pPhi))/2.;
//        m = m + pow(abs(pstand - fcs),pQ);
//    }
//    m = m/(pLs + 1.);
//    m = pow(m,1/pQ);
//
    return m;
}

Int_t TFxPredictor::GetLs() const {
    return fLs;
}

void TFxPredictor::SetLs(Int_t ls) {
    fLs = ls;
}

Double_t TFxPredictor::GetM() const {
    return fM;
}

void TFxPredictor::SetM(Double_t m) {
    fM = m;
}

Double_t TFxPredictor::GetPhi() const {
    return fPhi;
}

void TFxPredictor::SetPhi(Double_t phi) {
    fPhi = phi;
}

Double_t TFxPredictor::GetPq() const {
    return fPQ;
}

void TFxPredictor::SetPq(Double_t pq) {
    fPQ = pq;
}
