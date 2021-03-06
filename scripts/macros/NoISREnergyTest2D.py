# 2D histogram of reconstructed vs MC photon energy

from ROOT import *
import math as np

# Load in root tree
f = TFile("../root_files/extraction_long.root")
t = f.Get("ObservablesTree")
nEntries = t.GetEntries()

# Construct and format histograms
hist = TH2F("hist", "; E^{MC}; E^{Reco}", 120, 0, 0.2, 100, -100, 100)
hist1 = TH2F("hist1", "; E_{MC} [GeV]; E_{Reco} [GeV]",200, 0, 200, 200, 0, 200)

# Construct canvas
c1 = TCanvas("c1", "Test Stacked Histograms", 1000, 1000)

# Fill histograms
for i in range(0,nEntries):
  t.GetEntry(i)
  #hist1.Fill(t.m_mcPhotonEnergy, t.m_photonenergyA, t.m_isolepnumber == 1 and abs(t.m_mcLeptonFlavour) == 13 and t.m_recoPhotonEnergyChosen2 == 1 )
  #hist1.Fill(t.m_mcPhotonEnergy, t.m_photonenergyB, t.m_isolepnumber == 1 and abs(t.m_mcLeptonFlavour) == 13 and t.m_recoPhotonEnergyChosen2 == 2 )
  hist1.Fill(t.m_mcPhotonEnergy, t.m_recoPhotonEnergy, t.m_isolepnumber == 1 and abs(t.m_mcLeptonFlavour) == 13)

# Draw histogram
hist1.Draw("colz")

# Add legend entries and draw
legend = TLegend(0.47, 0.2, 0.69, 0.41)
legend.SetHeader("e_{L}^{-} e_{R}^{+}", "C")
legend.Draw()
