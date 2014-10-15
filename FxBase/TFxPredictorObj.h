//
// Class TFxPredictorObj
//
// TODO
//
// authors:
//          Martin Vala (mvala@saske.sk)
//

#ifndef ROOT_TFxPredictorObj
#define ROOT_TFxPredictorObj

#include <TObject.h>

class TFxPredictorObj: public TObject {

public:
    TFxPredictorObj();
    virtual ~TFxPredictorObj();
    void Reset();

    Double_t GetMoS() const;
    void SetMoS(Double_t moS);

private:

    Double_t fMoS;  // Moment of String

ClassDef(TFxPredictorObj, 1)


};

#endif
