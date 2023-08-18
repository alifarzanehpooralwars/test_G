#include <fstream>
#include <TH1F.h>
#include <TF1.h>
#include "TH2F.h"
#include "TTree.h"
#include "TFile.h"
#include "TMath.h"
#include <string>
#include <cmath>
#include <iostream>
#include <cstdlib>
#include <math.h>
#include <vector>
#include "TNtuple.h"
#include "TRandom.h"

//===================================================================
const double to_keV = 1e3;
const int N_DET = 12;

//===================================================================
// Histograms
TH1F* h_EnergyRaw[N_DET];
TH1F* h_Energy[N_DET];
//
TH2F* h_E_matrix;
TH1F* h_Nhits;
//
//===================================================================
// Tree
TFile* inFile = 0;
TTree* tree = 0;

//===================================================================
// Parameters
std::vector<std::vector<double>> params;
//
//===================================================================
#define MAKE_HST_IND(hstname,bins,minx,maxx,ind,tstr){\
    std::string tmpstr; \
    tmpstr = #hstname; \
    tmpstr += "_%2i"; \
    if(hstname[ind]) hstname[ind]->Reset(); \
    else { \
	sprintf(tstr,tmpstr.c_str(),i+1); \
	hstname[ind]=new TH1F(tstr,tstr,bins,minx,maxx); \
    } \
}
#define MAKE_HST2_IND(hstname,binsX,minx,maxx,binsY,miny,maxy,ind,tstr){\
    std::string tmpstr; \
    tmpstr = #hstname; \
    tmpstr += "_%2i"; \
    if(hstname[ind]) hstname[ind]->Reset(); \
    else { \
	sprintf(tsrt,tmpstr.c_str(),i+1); \
	hstname[ind]=new TH2F(tsrt,tsrt,binsX,minx,maxx,binsY,miny,maxy); \
    } \
}
#define MAKE_HST(hstname,bins,minx,maxx){\
    if(hstname) hstname->Reset(); \
    else \
	hstname=new TH1F(#hstname,#hstname,bins,minx,maxx); \
}
#define MAKE_HST2(hstname,bins,minx,maxx,binsy,miny,maxy){\
    if(hstname) hstname->Reset(); \
    else \
	hstname=new TH2F(#hstname,#hstname,bins,minx,maxx,binsy,miny,maxy); \
}
//===================================================================
void ut_PDAQ_init_hst() {
	char tstr[200];
	//
	for (int i = 0; i < N_DET; i++) {
		MAKE_HST_IND(h_EnergyRaw, 10000, 0, 10000, i, tstr);
		MAKE_HST_IND(h_Energy, 10000, 0, 10000, i, tstr);
	}
	//
	MAKE_HST2(h_E_matrix, 1000, 0, 10000, 1000, 0, 10000);
	MAKE_HST(h_Nhits, N_DET, 0, N_DET);
}
#undef MAKE_HST
#undef MAKE_HST2
#undef MAKE_HST_IND
#undef MAKE_HST2_IND

//===================================================================
// Energy-resolution smoothing function
double gesim_smoothing_sigma(double Emean, double detnum) {
	double sigma = 0;

	for (int i = 0; i < params[detnum].size(); i++) {
		double term = params[detnum][i];
		for (int j = 0; j < i; j++)
			term *= Emean;
		sigma += term;
	}

	return sigma;
}

//===================================================================
void smoothedHistos(char* intree = "GAINS_test1.root") {

	// Init
	ut_PDAQ_init_hst();
	TRandom rnd;

	//read energy resolution parameters
	params = std::vector<std::vector<double>>(N_DET, std::vector<double>(3));
	std::ifstream sigma_in("sigma_parameter_fits.txt");
	double c[2];
	sigma_in >> c[0] >> c[1];

	for (int i = 0; i < N_DET ; i++) {
		double a;
		sigma_in >> a;
		params[i][0] = a;
		params[i][1] = c[0];
		params[i][2] = c[1];
	}
// 	cout << "SSS" << endl;
// 	for (int i = 0; i < 13 ; i++) {
// 		double a;
// 		// PARAMS FOR CsI
//         params[i][0] = 118.9787; //c
//         params[i][1] = 0.1035;   //b
//         params[i][2] = 0.0000;   //a
// 	}
	sigma_in.close();

	if (!inFile) inFile = new TFile(intree);
	else {
		inFile->Close();
		delete inFile;
		inFile = new TFile(intree);
	}
	if (tree) tree = 0;
	tree = (TTree*)inFile->Get("GAINS;1 Energy deposition");
	if (!tree) {
		std::cerr << "Tree GAINS was not found\n";
		std::exit(1);
	}
	//-------------------------------------------------------------------
	// Event structure
	Double_t Edep[N_DET];
	//
	tree->SetBranchAddress("Edep1", Edep);
	tree->SetBranchAddress("Edep2", Edep + 1);
	tree->SetBranchAddress("Edep3", Edep + 2);
	tree->SetBranchAddress("Edep4", Edep + 3);
	tree->SetBranchAddress("Edep5", Edep + 4);
	tree->SetBranchAddress("Edep6", Edep + 5);
	tree->SetBranchAddress("Edep7", Edep + 6);
	tree->SetBranchAddress("Edep8", Edep + 7);
	tree->SetBranchAddress("Edep9", Edep + 8);
	tree->SetBranchAddress("Edep10", Edep + 9);
	tree->SetBranchAddress("Edep11", Edep + 10);
	tree->SetBranchAddress("Edep12", Edep + 11);

//  Following are CsI or NaI dets
//  tree->SetBranchAddress("Edep13", Edep + 12);
// 	tree->SetBranchAddress("Edep14", Edep + 13);
// 	tree->SetBranchAddress("Edep15", Edep + 14);
// 	tree->SetBranchAddress("Edep16", Edep + 15);
// 	tree->SetBranchAddress("Edep17", Edep + 16);
// 	tree->SetBranchAddress("Edep18", Edep + 17);
// 	tree->SetBranchAddress("Edep19", Edep + 18);
// 	tree->SetBranchAddress("Edep20", Edep + 19);
// 	tree->SetBranchAddress("Edep21", Edep + 20);
// 	tree->SetBranchAddress("Edep22", Edep + 21);
// 	tree->SetBranchAddress("Edep23", Edep + 22);
// 	tree->SetBranchAddress("Edep24", Edep + 23);
// 	//
	//
	for (int i = 0; i < N_DET ; i++) {
		h_EnergyRaw[i] = new TH1F(Form("h1%d", i + 1), Form("Detector %d sim", i + 1), 6000, 1, 3000);
		h_Energy[i] = new TH1F(Form("h1%d-s", i + 1), Form("Detector %d", i + 1), 6000, 1, 3000);
		h_Energy[i]->GetXaxis()->SetTitle("E (keV)");
		h_Energy[i]->GetYaxis()->SetTitle("Counts");
		h_Energy[i]->SetStats(kTRUE);

	}

	// Main event loop
	Int_t nentries = (Int_t)tree->GetEntries();
	//std::cout << "Events in the tree: " << nentries << "\n";
	// the event loop
	for (int e = 0; e < nentries; e++) {
		tree->GetEntry(e);

		for (int i = 0; i < N_DET ; i++) {
			double energy = Edep[i] * to_keV;
			if (energy > 1) {
				h_EnergyRaw[i]->Fill(energy);
                if(i < 13) {
				double energy_s = rnd.Gaus(energy, gesim_smoothing_sigma(energy, i));
				h_Energy[i]->Fill(energy_s);
                }
//                 if (i >12) {
// 				double energy_s = rnd.Gaus(energy, gesim_smoothing_sigma(energy, i));                       ///// for CsI or NaI
// 				h_Energy[1]->Fill(energy_s);
//                 }
                }
		}
	}

TCanvas *MyCanvas = new TCanvas ("MyCanvas", "Test Multipad Canvas", 1920, 1080);
    //MyCanvas->Divide(1, 2);

    MyCanvas->cd(1);
    h_Energy[0]->Draw();
    h_Energy[0]->SetTitle("HPGe_GAINS");

//     MyCanvas->cd(2);
//     h_Energy[1]->Draw();
//     h_Energy[1]->SetTitle("CsI_GAINS");


    TFile *file = new TFile("GAINS_smoothed.root", "RECREATE");
    h_Energy[0]->Write();
//     h_Energy[1]->Write();
       MyCanvas->Write();

    /////////////////////////////
//     Int_t summation_NaI_GAINS  = 0;
    Int_t summation_HPGe_GAINS  = 0;
    for (Int_t k = 0; k < 1000;  k++)

    {
    //summation_NaI_GAINS +=  h_Energy[0]->GetBinContent(k);
    summation_HPGe_GAINS += h_Energy[1]->GetBinContent(k);
    }
    printf(" HPGE: %i \n",  summation_HPGe_GAINS);


}
