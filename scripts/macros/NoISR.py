# Plot histogram of reconstructed ISR energy with 2 solutions when
# the true ISR energy is 0

from ROOT import *
import math as np

# Load in root tree
f = TFile("../root_files/extraction_long.root")
t = f.Get("ObservablesTree")

# Construct and format histograms
hist1 = TH1F("hist1", ";Cutflow ;Efficiency [%]", 100, -200, 200)
hist1.SetLineWidth(3)

# Construct canvas and stack
c1 = TCanvas("c1", "Test Stacked Histograms", 1000, 1000)
c1.SetLogy()
s1 = THStack("s1", "; E_{#gamma}^{Reco} [GeV]; a.u.")

# Define efficiency cut
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

# Fill histograms
nEntries = t.GetEntries()
for i in range(0,nEntries):
  t.GetEntry(i)
  hist1.Fill( t.m_recoPhotonEnergyA, applycut() and t.m_mcPhotonEnergy == 0.0 and t.m_recoPhotonEnergyChosen2 == 1)
  hist1.Fill( t.m_recoPhotonEnergyB, applycut() and t.m_mcPhotonEnergy == 0.0 and t.m_recoPhotonEnergyChosen2 == 1)

# Normalise
hist1.Scale(1 / hist1.Integral())

# Add histograms to stack and draw
s1.Add(hist1)
s1.Draw("hist nostack")

# Add legend entries and draw
legend = TLegend(0.67, 0.7, 0.89, 0.91)
legend.SetHeader("e_{L}^{-} e_{R}^{+}, E_{#gamma}^{MC} = 0", "C")
legend.Draw()
