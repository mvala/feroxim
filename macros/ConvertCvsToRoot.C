#ifndef __CINT__
#include <Rtypes.h>
#include <Riostream.h>
#include <TSystem.h>
#include <TFile.h>
#include <TTree.h>
#include <TTimeStamp.h>
#include <TFxRateObj.h>
#endif
void ConvertCvsToRoot(const char *filename = "/home/mvala/Work/SASKE/EKOPHYS/FeroxSim/EKOPHI/OANDA-EUR-USD.csv",
		const char *prefix = "EUR-USD_") {

	TFile *f = 0;
	TTree *t = 0;
	TFxRateObj *ro = new TFxRateObj();

	string line;
	char date[16], time[16];
	float rate1, rate2;
	struct tm tm;
	memset(&tm, 0, sizeof(struct tm));
	ifstream myfile(filename);
	TString tmp;
	Long64_t nLines = 0;
	Bool_t dateChanged = kTRUE;
	TString lastDate;

	if (myfile.is_open()) {
		while (getline(myfile, line)) {
			sscanf(line.c_str(), "%s %s %f %f", date, time, &rate1, &rate2);
//            Printf("XXX %s %s %f %f",date, time, rate1, rate2);
			int year, month, day;
			sscanf(date, "%d/%d/%d", &day, &month, &year);
			int hour, minute, sec;
			sscanf(time, "%d:%d:%d", &hour, &minute, &sec);

			TString myDate = date;
			if (lastDate.CompareTo(myDate)) {
				lastDate = myDate;
				dateChanged = kTRUE;
			}
			if (dateChanged) {
				dateChanged = kFALSE;
				if (f) {
					t->Write();
					//f->Close();
					delete t;
					delete f;
				}

				Printf("%s %s %s", lastDate.Data(), myDate.Data(),
						TString::Format("%s%02d%02d%02d.root", prefix, year,
								month, day).Data());
				f = TFile::Open(
						TString::Format("%s%02d%02d%02d.root", prefix, year,
								month, day).Data(), "RECREATE");
				t = new TTree("eproTree", "EkoPhysiscs Rate Object");
				t->Branch("epro", &ro);

			}

			TTimeStamp *timeStamp = new TTimeStamp(year, month, day, hour,
					minute, sec);
			ro->SetDateTime(timeStamp);
			ro->SetRate1(rate1);
			ro->SetRate2(rate2);
			t->Fill();
			ro->Reset();
			nLines++;
		}
		myfile.close();
	}

	if (f) {
		f->Write();
	}
}
