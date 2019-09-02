from ROOT import *
import math

f = TFile("../high_stat/root/extraction_long.root")
t = f.Get("ObservablesTree")

nEntries = t.GetEntries()

hist = TH1F("hist", ";cos( #theta_{W^{-}} [rad] ); a.u.", 50, 0, 3.2 )
hist.SetLineColor(kBlack)
hist.SetLineWidth(3)
hist1 = TH1F("hist1", "; cos( #theta_{W^{lep}} [rad] ); a.u.", 50, -1, 1)
hist1.SetLineColor(kBlack)
hist1.SetLineWidth(3)

s = THStack("s1", "; cos( #theta_{W^{-}} [rad]); a.u.")
s1 = THStack("s1", "; cos( #theta*_{l} [rad]); a.u.")
s2 = THStack("s1", "; #phi*_{l} [rad]; a.u.")

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

for i in range(0,nEntries):
  t.GetEntry(i)
  hist.Fill(t.m_extractThetaLepton)
  hist1.Fill( math.cos(t.m_extractThetaLepton) )

hist.Scale(1 / hist.Integral() )
hist1.Scale(1 / hist1.Integral() )

c = TCanvas("c", "Test Stacked Histograms", 1000, 1000)
s.Add(hist)
s.Draw("hist nostack")

c1 = TCanvas("c1", "Test Stacked Histograms", 1000, 1000)
s1.Add(hist1)
s1.Draw("hist nostack")

#c1.Print("../plots/W_mass_full_MC_mass.root")
