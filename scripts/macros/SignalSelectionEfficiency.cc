
#include <vector>

#include "TFile.h"
#include "TTree.h"
#include "TH1F.h"
#include "cmath.h"

void write()
{
   TFile *f = TFile::Open("../high_stat/root/extraction_long.root");
   TTree *t = TTree::Get("ObservablesTree")

   TFile *g = new TFile::Open("SelectionEfficiency.root", "RECREATE");
   TTree *r = new TTree::Get("ObservablesTree", "tree with vectors");

   std::vector<double> signal;
   std::vector<double> error;

   r->Branch("signal",&signal);
   r->Branch("error",&error);

   // Create one histograms
   TH3D *hist0 = new TH1D("hist0","", 20, -1, 1, 10, -1, 1, 10, -3.2, 3.2);
   TH3D *hist1 = new TH1D("hist1","", 20, -1, 1, 10, -1, 1, 10, -3.2, 3.2);

   int nEntries = t::GetEntries()

for(int i=0; i < nEntries; i++){
  if(t->m_isolepnumber == 1 && abs(t.m_mcLeptonFlavour) == 13 && t->m_trackmultiplicity >= 9 && t.->recoMass > 100 && t->m_recoMomentumT > 5 &&
     t->m_recoEnergy < 500 && t->m_taudiscr > 1 && t->m_omegaiso > 0.5 && (-12 <= t->m_logyplus <= -3) && (20 <= t->m_w_lepMass_1 <= 250) && (40 <= t->m_w_lepMass <= 120) &&
     (40 <= t->m_w_jetMass <= 120) && t->m_cosThetaW >-0.95){
       hist0::Fill( cos(t->m_extractThetaMinus), cos(t->m_extractThetaLepton), t->m_extractPhiLepton)
     }
  if(abs(t.m_mcLeptonFlavour) == 13){
       hist1::Fill( cos(t->m_extractThetaMinus), cos(t->m_extractThetaLepton), t->m_extractPhiLepton)
     }
}

hist0::Divide(hist0, hist1, 1.0, 1.0, "B")

for(int i=0; i < 20; i++){
  for(int i=0; i < 20; i++){
    for(int i=0; i < 20; i++){
      signal->push_back(hist0::GetBinContent((100*i + 10*j + 1*k))
      error->push_back(hist1::GetBinError((100*i + 10*j + 1*k))
      t->Fill();
      }
    }
  }

  f->Write();
  delete f;
}
