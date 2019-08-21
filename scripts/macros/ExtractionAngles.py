from ROOT import *

f = TFile("../high_stat/extraction_long.root")
t = f.Get("ObservablesTree")

nEntries = t.GetEntries()

hist = TH1F("hist", ";{#theta_{W^{-}} [rad]; a.u.", 80, 0, 3.2 )
hist.SetLineColor(kBlack)
hist.SetLineWidth(3)
hist1 = TH1F("hist1", "; #theta_{W^{lep}} [rad]; a.u.", 80, 0, 3.2)
hist1.SetLineColor(kBlack)
hist1.SetLineWidth(3)
hist2 = TH1F("hist2", "; #phi_{W^{lep}} [rad]; a.u.", 160, -3.2, 3.2)
hist2.SetLineColor(kBlack)
hist2.SetLineWidth(3)

s = THStack("s1", "; #theta_{W^{-}} [rad]; a.u.")
s1 = THStack("s1", "; #theta_{W^{lep}} [rad]; a.u.")
s2 = THStack("s1", "; #phi_{W^{lep}} [rad]; a.u.")

for i in range(0,nEntries):
  t.GetEntry(i)
  hist.Fill(t.m_extractThetaMinus, abs(t.m_mcLeptonFlavour) == 13)
  hist1.Fill(t.m_extractThetaLepton, abs(t.m_mcLeptonFlavour) == 13)
  hist2.Fill(t.m_extractPhiLepton, abs(t.m_mcLeptonFlavour) == 13)

hist.Scale(1 / hist.Integral() )
hist1.Scale(1 / hist1.Integral() )
hist2.Scale(1 / hist2.Integral() )

c = TCanvas("c", "Test Stacked Histograms", 1000, 1000)
s.Add(hist)
s.Draw("hist nostack")

c1 = TCanvas("c1", "Test Stacked Histograms", 1000, 1000)
s1.Add(hist1)
s1.Draw("hist nostack")

c2 = TCanvas("c2", "Test Stacked Histograms", 1000, 1000)
s2.Add(hist2)
s2.Draw("hist nostack")

#c1.Print("../plots/W_mass_full_MC_mass.root")
