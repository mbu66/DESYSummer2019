# Histogram showing the effect ofcheating beam background removal
# on the reconstruction of the leptionic W mass

from ROOT import *

# Load in root trees
f = TFile("../root_files/extraction_long_cheat.root")
t = f.Get("ObservablesTree")
g = TFile("../root_files/extraction_long.root")
r = g.Get("ObservablesTree")

nEntries = t.GetEntries()

# Construct and format histograms
hist = TH1F("hist", "; M_{W_{lep}}[GeV]; a.u.", 50, 0,  200)
hist.SetLineColor(kGreen+1)
hist.SetLineWidth(3)
hist1 = TH1F("hist1", "; M_{W_{lep}}[GeV]; a.u.", 50, 0, 200)
hist1.SetLineColor(kBlue)
hist1.SetLineWidth(3)

# Construct canvas and stack
c1 = TCanvas("c1", "Test Stacked Histograms", 1000, 1000)
s1 = THStack("s1", "; M_{W_{lep}}[GeV]; a.u.")

# Define efficiency cut
def applycut(tree):
    makesCut = False
    if(tree.m_isolepnumber == 1 and abs(tree.m_mcLeptonFlavour) == 13):
       makesCut = True
    return makesCut

# Fill histograms
for i in range(0,nEntries):
  t.GetEntry(i)
  r.GetEntry(i)
  hist.Fill(t.m_w_lepMass_2, applycut(t) )
  hist1.Fill(r.m_w_lepMass_2, applycut(r) )

# Add histograms to stack and draw
s1.Add(hist)
s1.Add(hist1)
s1.Draw("hist nostack")

# Add legend entries and draw
legend = TLegend(0.67, 0.7, 0.89, 0.91)
legend.SetHeader("e_{L}^{-} e_{R}^{+}", "C")
legend.AddEntry(hist, "Overlay Cheated", "l")
legend.AddEntry(hist1, "Fastjet Overlay Removal", "l")
legend.Draw()
