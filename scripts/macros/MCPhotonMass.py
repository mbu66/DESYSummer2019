# Plot histogram of mc photon mass

from ROOT import *
import math

# Load in root tree
f = TFile("../root_files/extraction_long.root")
t = f.Get("ObservablesTree")

# Construct and format histograms
hist = TH1F("hist", ";cos( #theta_{W^{-}} [rad] ); a.u.", 50, 0, 2 )
hist.SetLineColor(kBlack)
hist.SetLineWidth(3)
hist1 = TH1F("hist1", "; cos( #theta_{W^{lep}} [rad] ); a.u.", 50, 0, 2)
hist1.SetLineColor(kRed)
hist1.SetLineWidth(3)

# Construct canvas and stack
c = TCanvas("c", "Test Stacked Histograms", 1000, 1000)
s = THStack("s1", "; E_{#gamma}^{MC} [GeV]; a.u.")

# Define efficiency cut
def applycut(tree):
    makesCut = False
    if(True and \
       tree.m_isolepnumber == 1 and \
       abs(tree.m_mcLeptonFlavour) == 13 and \
       tree.m_trackmultiplicity >= 9 and \
       tree.m_recoMass > 100 and \
       tree.m_recoMomentumT > 5 and \
       tree.m_recoEnergy < 500 and \
       tree.m_taudiscr > 1 and \
       tree.m_omegaiso > 0.5 and \
       (-12 <= tree.m_logyplus <= -3) and \
       (20 <= tree.m_w_lepMass_1 <= 250) and \
       (40 <= tree.m_w_lepMass <= 120) and \
       (40 <= tree.m_w_jetMass <= 120) and \
       tree.m_cosThetaW >-0.95 and \
       True):

       makesCut = True
    return makesCut

# Fill histograms
nEntries = t.GetEntries()
for i in range(0,nEntries):
  t.GetEntry(i)
  hist.Fill(t.m_mcPhotonMass)
  hist1.Fill(t.m_mcPhotonMass, applycut(t) )

# Normalise histograms
hist.Scale(1 / hist.Integral() )
hist1.Scale(1 / hist1.Integral() )

# Add histograms to stack and draw
s.Add(hist)
s.Add(hist1)
s.Draw("hist nostack")
