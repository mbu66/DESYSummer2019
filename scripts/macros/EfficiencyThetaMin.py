
# Plot histogram of thetaMin dependance of efficiency, for whole signal
# and E_ISR < 1 GeV, with binomal errors.

from ROOT import *
import math

# Load in root tree
f = TFile("../root_files/extraction_long.root")
t = f.Get("ObservablesTree")

# Construct and format histograms
hist = TH1F("hist", ";cos( #theta_{W^{-}} [rad] ); a.u.", 50, -1, 1 )
hist.SetLineColor(kBlack)
hist.SetLineWidth(3)
hist1 = TH1F("hist1", "; cos( #theta_{W^{-}} [rad] ); a.u.", 50, -1, 1)
hist1.SetLineColor(kBlack)
hist1.SetLineWidth(3)

hist_P = TH1F("hist_P", ";cos( #theta_{W^{-}} [rad] ); a.u.", 50, -1, 1 )
hist_P.SetLineColor(kRed)
hist_P.SetLineWidth(3)
hist_P1 = TH1F("hist_P1", "; cos( #theta_{W^{-}} [rad] ); a.u.", 50, -1, 1)
hist_P1.SetLineColor(kRed)
hist_P1.SetLineWidth(3)

# Construct canvas and stack
c1 = TCanvas("c1", "Test Stacked Histograms", 1000, 1000)
s1 = THStack("s1", "; cos( #theta_{W^{-}} [rad] ); Efficiency [%]")

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
  hist.Fill( math.cos(t.m_extractThetaMinus), applycut(t))
  hist1.Fill( math.cos(t.m_extractThetaMinus), abs(t.m_mcLeptonFlavour) == 13 )
  hist_P.Fill( math.cos(t.m_extractThetaMinus), applycut(t) and t.m_mcPhotonEnergy < 1 )
  hist_P1.Fill( math.cos(t.m_extractThetaMinus), abs(t.m_mcLeptonFlavour) == 13 and t.m_mcPhotonEnergy < 1)

# Divide histograms to get efficiency and binomial errors
hist.Divide(hist, hist1, 1.0, 1.0, "B")
hist.Scale(100)
hist_P.Divide(hist_P, hist_P1, 1.0, 1.0, "B")
hist_P.Scale(100)

hist_error = hist.Clone()
hist_error.SetFillColor(kGray)
hist_error.SetMarkerColor(kGray)

hist_error_P = hist_P.Clone()
hist_error_P.SetFillColorAlpha(kRed, 0.3)
hist_error_P.SetMarkerColorAlpha(kRed, 0.3)

gStyle.SetErrorX(0.5)

# Add current efficiency value
line = TLine(-1, 60, 1, 60)
line.SetLineWidth(3)
line.SetLineColor(kGreen+1)

# Add histograms to stack and draw
s1.Add(hist_error, "E2")
s1.Add(hist, "hist")
s1.Add(hist_error_P, "E2")
s1.Add(hist_P, "hist")
s1.Draw("nostack")
line.Draw()

# Add legend entries and draw
legend = TLegend(0.5, 0.2, 0.89, 0.65)
legend.SetHeader("#splitline{       e_{L}^{-} e_{R}^{+}}{binomial errors}", "C")
legend.AddEntry(hist, "My Efficiency", "l")
legend.AddEntry(hist_P, "E^{MC}_{#gamma} < 1", "l")
legend.AddEntry(line, "Current Efficiency", "l")
legend.Draw()
