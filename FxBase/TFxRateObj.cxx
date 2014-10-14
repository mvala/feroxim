//
// Class TFxRateObj
//
// TODO
//
// authors:
//          Martin Vala (mvala@saske.sk)
//

#include "TFxRateObj.h"

ClassImp(TFxRateObj)

//_________________________________________________________________________________________________
TFxRateObj::TFxRateObj() :
		TObject(), fDateTime(0), fRate1(0.0), fRate2(0.0) {
//
// Std constructor
//

}

//_________________________________________________________________________________________________
TFxRateObj::~TFxRateObj() {
//
// Destructor
//

	delete fDateTime;
}

//_________________________________________________________________________________________________
void TFxRateObj::Reset() {
	delete fDateTime;
	fDateTime = 0;
	fRate1 = 0.0;
	fRate2 = 0.0;
}
