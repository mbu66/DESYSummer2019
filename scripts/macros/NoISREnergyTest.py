from ROOT import *
import math as np

f = TFile("../high_stat/root/extraction_long.root")
t = f.Get("ObservablesTree")
nEntries = t.GetEntries()

hist = TH1F("hist", "; E_{mc}; E_{reco}", 800, -2, 5)
hist1 = TH1F("hist1", "; E_{mc}; E_{reco}", 800, -2, 5)

c1 = TCanvas("c1", "Test Stacked Histograms", 1000, 1000)

def applycut():
    makesCut = False
    if(True and \
       t.m_isolepnumber == 1 and \
       abs(t.m_mcLeptonFlavour) == 13 and \
       t.m_trackmultiplicity >= 9 and \
       t.m_recoMass > 100 and \
       t.m_recoMomentumT > 5 and \
       t.m_recoEnergy < 500 and \
       t.m_taudiscr > 1 and \
       t.m_omegaiso > 0.5 and \
       (-12 <= t.m_logyplus <= -3) and \
       (20 <= t.m_w_lepMass_1 <= 250) and \
       (40 <= t.m_w_lepMass <= 120) and \
       (40 <= t.m_w_jetMass <= 120) and \
       t.m_cosThetaW >-0.95 and \
       True):

       makesCut = True
    return makesCut

for i in range(0,nEntries):
  t.GetEntry(i)
  if t.m_mcPhotonEnergy != 0 and t.m_recoPhotonEnergy !=0:
      hist1.Fill( (t.m_recoPhotonEnergy - t.m_mcPhotonEnergy) / t.m_mcPhotonEnergy, applycut() )
#  if t.m_mcPhotonEnergy != 0:
#      hist1.Fill( (t.m_mcPhotonEnergy - t.m_photonenergyA) / t.m_mcPhotonEnergy, applycut() and t.m_recoPhotonEnergyChosen2 == 1 and t.m_recoPhotonEnergyChosen == 3)
#      hist1.Fill( (t.m_mcPhotonEnergy - t.m_photonenergyB) / t.m_mcPhotonEnergy, applycut() and t.m_recoPhotonEnergyChosen2 == 2 and t.m_recoPhotonEnergyChosen == 3)

hist1.Draw("hist")

legend = TLegend(0.67, 0.7, 0.89, 0.91)
legend.SetHeader("e_{L}^{-} e_{R}^{+}", "C")
legend.Draw()

#c1.Print("../checks/plots/check_photon.root")
