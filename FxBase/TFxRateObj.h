//
// Class TFxRateObj
//
// TODO
//
// authors:
//          Martin Vala (mvala@saske.sk)
//

#ifndef ROOT_TFxRateObj
#define ROOT_TFxRateObj

#include <TObject.h>
#include <TTimeStamp.h>
class TFxRateObj: public TObject {

public:
	TFxRateObj();
	virtual ~TFxRateObj();

	void SetDateTime(TTimeStamp *time) {
		fDateTime = time;
	}
	void SetRate1(Double_t rate) {
		fRate1 = rate;
	}
	void SetRate2(Double_t rate) {
		fRate2 = rate;
	}

	Double_t GetRate1() const {
		return fRate1;
	}

	TTimeStamp* GetDateTime() const;
	void Reset();

private:

	TTimeStamp *fDateTime;
	Double_t fRate1;
	Double_t fRate2;

ClassDef(TFxRateObj, 1)


};

#endif
