#include "TGraphAsymmErrors.h"
#include "TCanvas.h"
#include <map>
#include <vector>
#include <string>
#include <iostream>
#include "TError.h"
#include "TH1.h"
#include "TH2.h"
#include "TFile.h"
#include "TROOT.h"
#include "TTree.h"
#include "TChain.h"
#include "math.h"
#include "TLorentzVector.h"
#define Pi 3.141593

using namespace std;
Double_t Sig(std::string filename)
{	Double_t detajj_=1.66; Double_t zepp_=0.88; Double_t delta_phi_=2.26;
	cout<<"begin calc "<<endl;
//	Double_t detajj_=1.6; Double_t zepp_=1.2; Double_t delta_phi_=2;
	TH2F* ID_BF=0;TH2F* ID_GH=0;TH2F* ISO_BF=0;TH2F* ISO_GH=0;TGraphAsymmErrors* track_SF=0;TH2D* di_lep_trigger=0;

	TFile* ID_eff_BF = TFile::Open("./SFs/ID_eff_BCDEF.root");
        TDirectoryFile* d_ID_BF=(TDirectoryFile*)ID_eff_BF->Get("MC_NUM_TightID_DEN_genTracks_PAR_pt_eta");
        d_ID_BF->GetObject("abseta_pt_ratio", ID_BF);

        TFile* ID_eff_GH = TFile::Open("./SFs/ID_eff_GH.root");
        TDirectoryFile* d_ID_GH=(TDirectoryFile*)ID_eff_GH->Get("MC_NUM_TightID_DEN_genTracks_PAR_pt_eta");
        d_ID_GH->GetObject("abseta_pt_ratio", ID_GH);

        TFile* ISO_eff_BF = TFile::Open("./SFs/ISO_eff_BCDEF.root");
        TDirectoryFile* d_ISO_BF=(TDirectoryFile*)ISO_eff_BF->Get("TightISO_TightID_pt_eta");
        d_ISO_BF->GetObject("abseta_pt_ratio", ISO_BF);

        TFile* ISO_eff_GH = TFile::Open("./SFs/ISO_eff_GH.root");
        TDirectoryFile* d_ISO_GH=(TDirectoryFile*)ISO_eff_GH->Get("TightISO_TightID_pt_eta");
        d_ISO_GH->GetObject("abseta_pt_ratio", ISO_GH);

        TFile* Track_eff = TFile::Open("./SFs/Tracking_EfficienciesAndSF_BCDEFGH.root");
        Track_eff->GetObject("ratio_eff_aeta_dr030e030_corr",track_SF);

        TFile* trigger_eff = TFile::Open("./SFs/di_lep_trigger.root");
        trigger_eff->GetObject("2Dh2",di_lep_trigger);


	std::string name = "out" + filename + ".root";
	TFile *filein = TFile::Open(name.c_str());
	//TFile *filein = TFile::Open("outZA_signal.root");
	TTree *treein = (TTree*)filein->Get("outtree");
	Double_t scalef;
	Int_t nVtx;
	Double_t theWeight;
	Double_t lumiWeight;
	Double_t pileupWeight;
	Int_t HLT_Ele1;
	Int_t HLT_Mu1;
	Double_t nump;
	Double_t numm;
	Double_t npT;
	Int_t lep;
	Double_t ptVlep;
	Double_t yVlep;
	Double_t phiVlep;
	Double_t massVlep;
	Double_t ptlep1;
	Double_t etalep1;
	Double_t philep1;
	Double_t ptlep2;
	Double_t etalep2;
	Double_t philep2;
	Double_t drla;
	Double_t drla2;
	Double_t drj1a;
	Double_t drj2a;
	Double_t drj1l;
	Double_t drj1l2;
	Double_t drj2l;
	Double_t drj2l2;
	Int_t nlooseeles;
	Int_t nloosemus;
	Double_t MET_et;
	Double_t photonet;
	Double_t photoneta;
	Double_t photonphi;
	Double_t photone;
	Double_t photonsieie;
	Double_t photonphoiso;
	Double_t photonchiso;
	Double_t photonnhiso;
	Int_t isprompt;
	Double_t jet1pt;
	Double_t jet1eta;
	Double_t jet1phi;
	Double_t jet1e;
	Double_t jet2pt;
	Double_t jet2eta;
	Double_t jet2phi;
	Double_t jet2e;
	Double_t Mjj;
	Double_t zepp;
	Double_t deltaeta;
	Double_t actualWeight;
	Double_t detajj;
	Double_t delta_phi;
	Double_t drjj;
	Double_t yields=0.;


	treein->SetBranchAddress("scalef", &scalef);
	treein->SetBranchAddress("nVtx", &nVtx);
	treein->SetBranchAddress("theWeight", &theWeight);
	treein->SetBranchAddress("lumiWeight", &lumiWeight);
	treein->SetBranchAddress("pileupWeight", &pileupWeight);
	treein->SetBranchAddress("HLT_Ele1", &HLT_Ele1);
	treein->SetBranchAddress("HLT_Mu1", &HLT_Mu1);
	treein->SetBranchAddress("nump", &nump);
	treein->SetBranchAddress("numm", &numm);
	treein->SetBranchAddress("npT", &npT);
	treein->SetBranchAddress("lep", &lep);
	treein->SetBranchAddress("ptVlep", &ptVlep);
	treein->SetBranchAddress("yVlep", &yVlep);
	treein->SetBranchAddress("phiVlep", &phiVlep);
	treein->SetBranchAddress("massVlep", &massVlep);
	treein->SetBranchAddress("ptlep1", &ptlep1);
	treein->SetBranchAddress("etalep1", &etalep1);
	treein->SetBranchAddress("philep1", &philep1);
	treein->SetBranchAddress("ptlep2", &ptlep2);
	treein->SetBranchAddress("etalep2", &etalep2);
	treein->SetBranchAddress("philep2", &philep2);
	treein->SetBranchAddress("drla", &drla);
	treein->SetBranchAddress("drla2", &drla2);
	treein->SetBranchAddress("drj1a", &drj1a);
	treein->SetBranchAddress("drj2a", &drj2a);
	treein->SetBranchAddress("drj1l", &drj1l);
	treein->SetBranchAddress("drj2l", &drj2l);
	treein->SetBranchAddress("drj1l2", &drj1l2);
	treein->SetBranchAddress("drj2l2", &drj2l2);
	treein->SetBranchAddress("nlooseeles", &nlooseeles);
	treein->SetBranchAddress("nloosemus", &nloosemus);
	treein->SetBranchAddress("MET_et", &MET_et);
	treein->SetBranchAddress("photonet", &photonet);
	treein->SetBranchAddress("photoneta", &photoneta);
	treein->SetBranchAddress("photonphi", &photonphi);
	treein->SetBranchAddress("photone", &photone);
	treein->SetBranchAddress("photonsieie", &photonsieie);
	treein->SetBranchAddress("photonphoiso", &photonphoiso);
	treein->SetBranchAddress("photonchiso", &photonchiso);
	treein->SetBranchAddress("photonnhiso", &photonnhiso);
	treein->SetBranchAddress("isprompt", &isprompt);
	treein->SetBranchAddress("jet1pt", &jet1pt);
	treein->SetBranchAddress("jet1eta", &jet1eta);
	treein->SetBranchAddress("jet1phi", &jet1phi);
	treein->SetBranchAddress("jet1e", &jet1e);
	treein->SetBranchAddress("jet2pt", &jet2pt);
	treein->SetBranchAddress("jet2eta", &jet2eta);
	treein->SetBranchAddress("jet2phi", &jet2phi);
	treein->SetBranchAddress("jet2e", &jet2e);
	treein->SetBranchAddress("Mjj", &Mjj);
	treein->SetBranchAddress("zepp", &zepp);
	treein->SetBranchAddress("deltaeta", &deltaeta);

	TLorentzVector j1p4, j2p4, photonp4, Zp4;
	Int_t numentry = treein->GetEntries();
	cout<< "entries is "<<numentry<<endl;
	Double_t ID_lep1, ID_lep2, ISO_lep1, ISO_lep2, Track_lep1, Track_lep2, trigger_SF, photon_ID, photon_eveto;
	for(Int_t i=0; i<numentry; i++)
	{
		treein->GetEntry(i);
		actualWeight = lumiWeight * pileupWeight * scalef;

		detajj = fabs(jet1eta - jet2eta);  

		if (fabs(jet1phi-jet2phi)>Pi) drjj = sqrt((jet1eta-jet2eta)*(jet1eta-jet2eta)+(2*Pi-fabs(jet1phi-jet2phi))*(2*Pi-fabs(jet1phi-jet2phi)));
        else drjj = sqrt((jet1eta-jet2eta)*(jet1eta-jet2eta)+(fabs(jet1phi-jet2phi))*(fabs(jet1phi-jet2phi)));

		j1p4.SetPtEtaPhiE(jet1pt, jet1eta, jet1phi, jet1e);
		j2p4.SetPtEtaPhiE(jet2pt, jet2eta, jet2phi, jet2e);
		photonp4.SetPtEtaPhiE(photonet, photoneta, photonphi, photone);
		Zp4.SetPtEtaPhiE(ptVlep, yVlep, phiVlep, massVlep);
		delta_phi=fabs((Zp4+photonp4).Phi()-(j1p4+j2p4).Phi());
		if (delta_phi>Pi) delta_phi=2*Pi-delta_phi;
		
		/// apply eff SF
		ID_lep1=0.55*ID_BF->GetBinContent(ID_BF->FindBin(fabs(etalep1),ptlep1))+0.45*ID_GH->GetBinContent(ID_GH->FindBin(fabs(etalep1),ptlep1));
                ID_lep2=0.55*ID_BF->GetBinContent(ID_BF->FindBin(fabs(etalep2),ptlep2))+0.45*ID_GH->GetBinContent(ID_GH->FindBin(fabs(etalep2),ptlep2));
                ISO_lep1=0.55*ISO_BF->GetBinContent(ISO_BF->FindBin(fabs(etalep1),ptlep1))+0.45*ISO_GH->GetBinContent(ISO_GH->FindBin(fabs(etalep1),ptlep1));
                ISO_lep2=0.55*ISO_BF->GetBinContent(ISO_BF->FindBin(fabs(etalep2),ptlep2))+0.45*ISO_GH->GetBinContent(ISO_GH->FindBin(fabs(etalep2),ptlep2));
                Track_lep1=track_SF->Eval(0.1+0.2*int(fabs(etalep1)/0.2));
                Track_lep2=track_SF->Eval(0.1+0.2*int(fabs(etalep2)/0.2));
                trigger_SF=di_lep_trigger->GetBinContent(di_lep_trigger->FindBin(fabs(etalep1),fabs(etalep2)));
                photon_ID=0.9938;
		photon_eveto=0.9938;
		
		actualWeight = actualWeight*ID_lep1*ID_lep2*ISO_lep1*ISO_lep2*Track_lep1*Track_lep2*trigger_SF*photon_ID*photon_eveto;

		/// event selection
		if(jet1pt > 30 && jet2pt > 30 &&fabs(jet1eta) < 4.7 && fabs(jet2eta) < 4.7 && Mjj >1000
			&& drjj > 0.5 && drj1l > 0.5 && drj1l2 > 0.5 && drj2l > 0.5 && drj2l2 > 0.5
			&& zepp < zepp_ && delta_phi > delta_phi_ && detajj > detajj_) yields += actualWeight;		

	}
	ID_eff_BF->Close();
	ID_eff_GH->Close();
	ISO_eff_BF->Close();
	ISO_eff_GH->Close();
	Track_eff->Close();
	trigger_eff->Close();
	filein->Close();
	return yields;
}


Double_t Sig_plj(std::string filename)
{	Double_t detajj_=1.66; Double_t zepp_=0.88; Double_t delta_phi_=2.26;	
	cout<<"begin calc "<<endl;
	double scale_plj[6] = {0.100698, 0.0703795, 0.0574917, 0.0396483, 0.042675, 0.0448665};
	std::string name = "out" + filename + ".root";
	TFile *filein = TFile::Open(name.c_str());
	//TFile *filein = TFile::Open("outZA_signal.root");
	TTree *treein = (TTree*)filein->Get("outtree");
	Double_t scalef;
	Int_t nVtx;
	Double_t theWeight;
	Double_t lumiWeight;
	Double_t pileupWeight;
	Int_t HLT_Ele1;
	Int_t HLT_Mu1;
	Double_t nump;
	Double_t numm;
	Double_t npT;
	Int_t lep;
	Double_t ptVlep;
	Double_t yVlep;
	Double_t phiVlep;
	Double_t massVlep;
	Double_t ptlep1;
	Double_t etalep1;
	Double_t philep1;
	Double_t ptlep2;
	Double_t etalep2;
	Double_t philep2;
	Double_t drla;
	Double_t drla2;
	Double_t drj1a;
	Double_t drj2a;
	Double_t drj1l;
	Double_t drj1l2;
	Double_t drj2l;
	Double_t drj2l2;
	Int_t nlooseeles;
	Int_t nloosemus;
	Double_t MET_et;
	Double_t photonet;
	Double_t photoneta;
	Double_t photonphi;
	Double_t photone;
	Double_t photonsieie;
	Double_t photonphoiso;
	Double_t photonchiso;
	Double_t photonnhiso;
	Int_t isprompt;
	Double_t jet1pt;
	Double_t jet1eta;
	Double_t jet1phi;
	Double_t jet1e;
	Double_t jet2pt;
	Double_t jet2eta;
	Double_t jet2phi;
	Double_t jet2e;
	Double_t Mjj;
	Double_t zepp;
	Double_t deltaeta;
	Double_t actualWeight;
	Double_t detajj;
	Double_t delta_phi;
	Double_t drjj;
	Double_t yields=0.;


	treein->SetBranchAddress("scalef", &scalef);
	treein->SetBranchAddress("nVtx", &nVtx);
	treein->SetBranchAddress("theWeight", &theWeight);
	treein->SetBranchAddress("lumiWeight", &lumiWeight);
	treein->SetBranchAddress("pileupWeight", &pileupWeight);
	treein->SetBranchAddress("HLT_Ele1", &HLT_Ele1);
	treein->SetBranchAddress("HLT_Mu1", &HLT_Mu1);
	treein->SetBranchAddress("nump", &nump);
	treein->SetBranchAddress("numm", &numm);
	treein->SetBranchAddress("npT", &npT);
	treein->SetBranchAddress("lep", &lep);
	treein->SetBranchAddress("ptVlep", &ptVlep);
	treein->SetBranchAddress("yVlep", &yVlep);
	treein->SetBranchAddress("phiVlep", &phiVlep);
	treein->SetBranchAddress("massVlep", &massVlep);
	treein->SetBranchAddress("ptlep1", &ptlep1);
	treein->SetBranchAddress("etalep1", &etalep1);
	treein->SetBranchAddress("philep1", &philep1);
	treein->SetBranchAddress("ptlep2", &ptlep2);
	treein->SetBranchAddress("etalep2", &etalep2);
	treein->SetBranchAddress("philep2", &philep2);
	treein->SetBranchAddress("drla", &drla);
	treein->SetBranchAddress("drla2", &drla2);
	treein->SetBranchAddress("drj1a", &drj1a);
	treein->SetBranchAddress("drj2a", &drj2a);
	treein->SetBranchAddress("drj1l", &drj1l);
	treein->SetBranchAddress("drj2l", &drj2l);
	treein->SetBranchAddress("drj1l2", &drj1l2);
	treein->SetBranchAddress("drj2l2", &drj2l2);
	treein->SetBranchAddress("nlooseeles", &nlooseeles);
	treein->SetBranchAddress("nloosemus", &nloosemus);
	treein->SetBranchAddress("MET_et", &MET_et);
	treein->SetBranchAddress("photonet", &photonet);
	treein->SetBranchAddress("photoneta", &photoneta);
	treein->SetBranchAddress("photonphi", &photonphi);
	treein->SetBranchAddress("photone", &photone);
	treein->SetBranchAddress("photonsieie", &photonsieie);
	treein->SetBranchAddress("photonphoiso", &photonphoiso);
	treein->SetBranchAddress("photonchiso", &photonchiso);
	treein->SetBranchAddress("photonnhiso", &photonnhiso);
	treein->SetBranchAddress("isprompt", &isprompt);
	treein->SetBranchAddress("jet1pt", &jet1pt);
	treein->SetBranchAddress("jet1eta", &jet1eta);
	treein->SetBranchAddress("jet1phi", &jet1phi);
	treein->SetBranchAddress("jet1e", &jet1e);
	treein->SetBranchAddress("jet2pt", &jet2pt);
	treein->SetBranchAddress("jet2eta", &jet2eta);
	treein->SetBranchAddress("jet2phi", &jet2phi);
	treein->SetBranchAddress("jet2e", &jet2e);
	treein->SetBranchAddress("Mjj", &Mjj);
	treein->SetBranchAddress("zepp", &zepp);
	treein->SetBranchAddress("deltaeta", &deltaeta);

	TLorentzVector j1p4, j2p4, photonp4, Zp4;
	Int_t numentry = treein->GetEntries();
	cout<< "entries is "<<numentry<<endl;
	Double_t ID_lep1, ID_lep2, ISO_lep1, ISO_lep2, Track_lep1, Track_lep2, trigger_SF, photon_ID, photon_eveto;
	for(Int_t i=0; i<numentry; i++)
	{
		treein->GetEntry(i);
		actualWeight = lumiWeight * pileupWeight * scalef;

		detajj = fabs(jet1eta - jet2eta);  

		if (fabs(jet1phi-jet2phi)>Pi) drjj = sqrt((jet1eta-jet2eta)*(jet1eta-jet2eta)+(2*Pi-fabs(jet1phi-jet2phi))*(2*Pi-fabs(jet1phi-jet2phi)));
        else drjj = sqrt((jet1eta-jet2eta)*(jet1eta-jet2eta)+(fabs(jet1phi-jet2phi))*(fabs(jet1phi-jet2phi)));

		j1p4.SetPtEtaPhiE(jet1pt, jet1eta, jet1phi, jet1e);
		j2p4.SetPtEtaPhiE(jet2pt, jet2eta, jet2phi, jet2e);
		photonp4.SetPtEtaPhiE(photonet, photoneta, photonphi, photone);
		Zp4.SetPtEtaPhiE(ptVlep, yVlep, phiVlep, massVlep);
		delta_phi=fabs((Zp4+photonp4).Phi()-(j1p4+j2p4).Phi());
		if (delta_phi>Pi) delta_phi=2*Pi-delta_phi;
		
		if(photonet>120.) actualWeight = scale_plj[5];
        if(photonet>80.) actualWeight = scale_plj[4];
        if(photonet>60.) actualWeight = scale_plj[3];
        if(photonet>45.) actualWeight = scale_plj[2];
        if(photonet>35.) actualWeight = scale_plj[1];
        if(photonet>25.) actualWeight = scale_plj[0];
		/// event selection
		if(jet1pt > 30 && jet2pt > 30 &&fabs(jet1eta) < 4.7 && fabs(jet2eta) < 4.7 && Mjj >1000
			&& drjj > 0.5 && drj1l > 0.5 && drj1l2 > 0.5 && drj2l > 0.5 && drj2l2 > 0.5
			&& zepp < zepp_ && delta_phi > delta_phi_ && detajj > detajj_) yields += actualWeight;		

	}
	filein->Close();
	return yields;
}

void draw(std::string name, Double_t *a, int ii)
{
	TCanvas *c1 = new TCanvas("c","c",800,600);
    Double_t delta_phi[11] = {0, 0.3, 0.6, 0.9, 1.2, 1.5, 1.8, 2.1, 2.4, 2.7, 3};
    Double_t zepp[11] = {0, 0.3, 0.6, 0.9, 1.2, 1.5, 1.8, 2.1, 2.4, 2.7, 3};
    TH2D *h2D = new TH2D("2Dh","significance",10,delta_phi,10,zepp);
    for (int i=0; i<10; i++)
    {
    	for (int j=0; j<10; j++)
    	{
    		h2D->Fill(delta_phi[j]+0.1,zepp[i]+0.1,a[100*ii+10*i+j]);
    	}
    }
    h2D->SetMinimum(0);
    h2D->SetMaximum(3.5);
    h2D->SetStats(kFALSE);
    h2D->SetOption("colztext");
    h2D->SetContour(18);
    h2D->SetContourLevel(0,0);
    h2D->SetContourLevel(1,0.2);
    h2D->SetContourLevel(2,0.4);
    h2D->SetContourLevel(3,0.6);
    h2D->SetContourLevel(4,0.8);
    h2D->SetContourLevel(5,1.);
    h2D->SetContourLevel(6,1.2);
    h2D->SetContourLevel(7,1.4);
    h2D->SetContourLevel(8,1.6);
    h2D->SetContourLevel(9,1.8);
    h2D->SetContourLevel(10,2.);
    h2D->SetContourLevel(11,2.2);
    h2D->SetContourLevel(12,2.4);
    h2D->SetContourLevel(13,2.6);
    h2D->SetContourLevel(14,2.8);
    h2D->SetContourLevel(15,3.);
    h2D->SetContourLevel(16,3.2);
    h2D->SetContourLevel(17,3.5);
    h2D->Draw("");
    h2D->SetContourLevel(0,0);
    h2D->GetXaxis()->SetTitle("delta_phi");
    h2D->GetYaxis()->SetTitle("zepp");
    char buffer[256];
    sprintf(buffer, "sig_detajj_%s.png", name.c_str());
    c1->SaveAs(buffer);
}

int main()
{	//detajj_,	zepp_,	delta_phi_
	Double_t lumi = 35.862;
	Double_t yields_EWK=0.;
	Double_t yields_ZA=0.;
	Double_t yields_ST=0.;
	Double_t yields_TTA=0.;
	Double_t yields_VV=0.;
	Double_t yields_WA=0.;
	Double_t yields_plj=0.;
	yields_EWK=Sig("ZA_signal");
	yields_ZA=Sig("ZA");
	yields_ST=Sig("ST");
	yields_TTA=Sig("TTA");
	yields_VV=Sig("VV");
	yields_WA=Sig("WA");
	yields_plj=Sig_plj("photonlikejet");
	cout<<"yields_EWK "<<yields_EWK*lumi<<endl;
	cout<<"yields_ZA "<<1.25*lumi*yields_ZA<<endl;
	cout<<"yields_ST "<<lumi*yields_ST<<endl;
	cout<<"yields_TTA "<<lumi*yields_TTA<<endl;
	cout<<"yields_VV "<<lumi*yields_VV<<endl;
	cout<<"yields_WA "<<lumi*yields_WA<<endl;
	cout<<"yields_plj "<<yields_plj<<endl;	

	return 1;
}
