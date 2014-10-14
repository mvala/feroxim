#ifndef __CINT__
#include <TString.h>
#include <TSystem.h>
#include <TStopwatch.h>
#include <TROOT.h>
#endif

void MainRun(TString macro, TString macro_argc, TString projectDir = "") {

	gSystem->Load("libTree.so");
	gSystem->Load("libProof.so");
	gSystem->Load("libFxBase.so");
	gSystem->AddIncludePath(
			TString::Format("-I%sFxBase", projectDir.Data()).Data());
	TStopwatch timer;
	timer.Start();

	if (!macro.IsNull()) {
		if (macro.EndsWith(".C")) {
			gROOT->ProcessLine(TString::Format(".L %s+", macro.Data()).Data());
			macro.ReplaceAll(".C", "");
			gROOT->ProcessLine(
					TString::Format("%s(%s)", macro.Data(), macro_argc.Data()).Data());
		}
	}

	timer.Stop();
	timer.Print();

	Printf("Working dir: '%s'", gSystem->WorkingDirectory());
}
