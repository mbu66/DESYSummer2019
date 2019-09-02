
#include <vector>

#include "TFile.h"
#include "TTree.h"
#include "TH1F.h"
#include "math.h"

void write(){

  // Read input file
  TFile *f = TFile::Open("../high_stat/root/extraction_long.root");
  TTree *t = (TTree*)f->Get("ObservablesTree");

  //Initialise variables
  std::vector<double> signal;
  std::vector<double> error;

  int m_isolepnumber;
  double m_mcLeptonFlavour;
  int m_trackmultiplicity;
  double m_recoMass;
  double m_recoMomentumT;
  double m_recoEnergy;
  double m_taudiscr;
  double m_omegaiso;
  float m_logyplus;
  double m_w_lepMass_1;
  double m_w_lepMass;
  double m_w_jetMass;
  double m_cosThetaW;
  double m_extractThetaMinus;
  double m_extractThetaLepton;
  double m_extractPhiLepton;

  // Assign Branch labels
  t->SetBranchAddress("m_isolepNumber",&m_isolepnumber);
  t->SetBranchAddress("m_mcLeptonFlavour",&m_mcLeptonFlavour);
  t->SetBranchAddress("m_trackultiplicity",&m_trackmultiplicity);
  t->SetBranchAddress("m_recoMass",&m_recoMass);
  t->SetBranchAddress("m_recoMomentumT",&m_recoMomentumT);
  t->SetBranchAddress("m_recoEnergy",&m_recoEnergy);
  t->SetBranchAddress("m_taudiscr",&m_taudiscr);
  t->SetBranchAddress("m_omegaiso",&m_omegaiso);
  t->SetBranchAddress("m_logyplus",&m_logyplus);
  t->SetBranchAddress("m_w_lepMass_1",&m_w_lepMass_1);
  t->SetBranchAddress("m_w_lepMass",&m_w_lepMass);
  t->SetBranchAddress("m_w_jetMass",&m_w_jetMass);
  t->SetBranchAddress("m_cosThetaW",&m_cosThetaW);
  t->SetBranchAddress("m_extractThetaMinus",&m_extractThetaMinus);
  t->SetBranchAddress("m_extractThetaLepton",&m_extractThetaLepton);
  t->SetBranchAddress("m_extractPhiLepton",&m_extractPhiLepton);

  // Create 3D histograms
  TH3D *hist0 = new TH3D("hist0","", 20, -1, 1, 10, -1, 1, 10, -3.2, 3.2);
  TH3D *hist1 = new TH3D("hist1","", 20, -1, 1, 10, -1, 1, 10, -3.2, 3.2);

  //Fill histograms
  int nEntries = t->GetEntries();

  for(int i=0; i < nEntries; i++){
    t->GetEntry(i);

    if(m_isolepnumber == 1 && abs(m_mcLeptonFlavour) == 13 && m_trackmultiplicity >= 9 && m_recoMass > 100 && m_recoMomentumT > 5 &&
                              m_recoEnergy < 500 && m_taudiscr > 1 && m_omegaiso > 0.5 && -12 <= m_logyplus && m_logyplus <= -3 && 20 <= m_w_lepMass_1 &&
                              m_logyplus<= 250 && 40 <= m_w_lepMass && m_logyplus <= 120 && 40 <= m_w_jetMass && m_w_jetMass <= 120 && m_cosThetaW >-0.95){
      hist0->Fill( cos(m_extractThetaMinus), cos(m_extractThetaLepton), m_extractPhiLepton);
    }

    if(abs(m_mcLeptonFlavour) == 13){
      hist1->Fill( cos(m_extractThetaMinus), cos(m_extractThetaLepton), m_extractPhiLepton);
    }
  }

  //Evaluate efficiency
  hist0->Divide(hist0, hist1, 1.0, 1.0, "B");

  //Fill std vectors
  for(int i=0; i < 20; i++){
    for(int j=0; j < 10; j++){
      for(int k=0; k < 10; k++){
      signal.push_back(hist0->GetBinContent(100*i + 10*j + 1*k));
      if(hist0->GetBinContent(100*i + 10*j + 1*k) == 0){
        error.push_back(1.0);
      }else{
        error.push_back(hist0->GetBinError(100*i + 10*j + 1*k));
      }
      //std::cout << signal[100*i + 10*j + 1*k] << '\t' << error[100*i + 10*j + 1*k] <<'\n';
      }
    }
  }

  //Convert to TvectorT
  const double * r_signal  = &signal[0];
  const double * r_error  = &error[0];
  TVectorT<double> t_signal (2000, r_signal);
  TVectorT<double> t_error (2000, r_error);

  //Write Tvectors to outputfile
  TFile *g = TFile::Open("SelectionEfficiency.root", "RECREATE");

  g->WriteObject(&t_signal, "signal");
  g->WriteObject(&t_error, "error");
  g->Close();

}

void SignalSelectionEfficiency_temp() {
  write();
}
