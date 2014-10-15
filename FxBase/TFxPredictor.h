//
// Class TFxPredictor
//
// TODO
//
// authors:
//          Martin Vala (mvala@saske.sk)
//

#ifndef ROOT_TFxPredictor
#define ROOT_TFxPredictor

#include <TObject.h>

class TArrayD;
class TFxPredictor: public TObject {

public:
    TFxPredictor(Int_t ls=100, Double_t pq=1, Double_t m=0, Double_t phi=0);
    virtual ~TFxPredictor();
    void Reset();

    Int_t GetLs() const;
    void SetLs(Int_t ls);
    Double_t GetM() const;
    void SetM(Double_t m);
    Double_t GetPhi() const;
    void SetPhi(Double_t phi);
    Double_t GetPq() const;
    void SetPq(Double_t pq);

    virtual Double_t Calulate(TArrayD *rates);

private:

    Int_t fLs;   // String lenght
    Double_t fPQ;   // Power constant
    Double_t fM;    // Frequecny
    Double_t fPhi;  // Phase Shift

ClassDef(TFxPredictor, 1)


};

#endif
