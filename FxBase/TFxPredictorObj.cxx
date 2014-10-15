//
// Class TFxPredictorObj
//
// TODO
//
// authors:
//          Martin Vala (mvala@saske.sk)
//

#include <TMath.h>
#include <TArrayD.h>

#include "TFxPredictorObj.h"

ClassImp(TFxPredictorObj)

//_________________________________________________________________________________________________
TFxPredictorObj::TFxPredictorObj() :
        TObject(), fMoS(0.0) {
//
// Std constructor
//

}

//_________________________________________________________________________________________________
TFxPredictorObj::~TFxPredictorObj() {
//
// Destructor
//

}

//_________________________________________________________________________________________________
void TFxPredictorObj::Reset() {
    fMoS = -2.0;
}

//_________________________________________________________________________________________________
Double_t TFxPredictorObj::GetMoS() const {
    return fMoS;
}

//_________________________________________________________________________________________________
void TFxPredictorObj::SetMoS(Double_t moS) {
    fMoS = moS;
}
