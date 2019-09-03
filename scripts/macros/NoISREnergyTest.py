#psudo pull distribution for 3 energy reconstruction techniques

from ROOT import *
import math as np

# Load in root tree
f = TFile("../root_files/extraction_long.root")
t = f.Get("ObservablesTree")

# Construct and format histograms
hist = TH1F("hist", ";Cutflow ;Efficiency [%]", 200, -100, 100)
hist.SetLineWidth(3)
hist.SetLineColor(kRed)
hist1 = TH1F("hist1", ";Cutflow ;Efficiency [%]", 200, -100, 100)
hist1.SetLineColor(kBlue)
hist1.SetLineWidth(3)
hist2 = TH1F("hist2", ";Cutflow ;Efficiency [%]", 200, -100, 100)
hist2.SetLineColor(kGreen+1)
hist2.SetLineWidth(3)

# Construct canvas and stack
c1 = TCanvas("c1", "Test Stacked Histograms", 1000, 1000)
c1.SetLogy()
s1 = THStack("s1", "; E_{#gamma}^{Reco} - E_{#gamma}^{MC} [GeV]; a.u.")

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
  hist.Fill( (t.m_recoPhotonEnergy - t.m_mcPhotonEnergy) , applycut() )
  hist1.Fill( (t.m_recoPhotonEnergyA - t.m_mcPhotonEnergy), applycut() and t.m_recoPhotonEnergyChosen2 == 1)
  hist1.Fill( (t.m_recoPhotonEnergyB - t.m_mcPhotonEnergy), applycut() and t.m_recoPhotonEnergyChosen2 == 2)
  hist2.Fill( (0.0 - t.m_mcPhotonEnergy) , applycut() )

# Normalise histograms
hist.Scale(1 / hist.Integral())
hist1.Scale(1 / hist1.Integral())
hist2.Scale(1 / hist2.Integral())

# Add histograms to stack and draw
s1.Add(hist2)
s1.Add(hist1)
s1.Add(hist)
s1.Draw("hist nostack")

# Add legend entries and draw
legend = TLegend(0.67, 0.7, 0.89, 0.91)
legend.SetHeader("e_{L}^{-} e_{R}^{+}", "C")
legend.AddEntry(hist2, "E_{ISR} = 0", "l")
legend.AddEntry(hist1, "E_{ISR} from formula", "l")
legend.AddEntry(hist, "E_{ISR} with both", "l")
legend.Draw()
