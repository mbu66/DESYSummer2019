from ROOT import *

f = TFile("../test_W5_full_MC_mass.root")
t = f.Get("ObservablesTree")

g = TFile("../root_files/W5/test_W5_full.root")
r = g.Get("ObservablesTree")

nEntries = t.GetEntries()

hist = TH1F("hist", "; M_{W_{lep}}[GeV]; a.u.", 50, 0,  200)
hist.SetLineColor(kRed)
hist.SetLineWidth(3)
hist1 = TH1F("hist1", "; M_{W_{lep}}[GeV]; a.u.", 50, 0, 200)
hist1.SetLineColor(kBlack)
hist1.SetLineWidth(3)

c1 = TCanvas("c1", "Test Stacked Histograms", 1000, 1000)
s1 = THStack("s1", "; M_{W_{lep}}[GeV]; a.u.")

def applycut(tree):
    makesCut = False
    if(True and \
       tree.m_isolepnumber == 1 and \
       abs(tree.m_mcLeptonFlavour) == 13 and \
#       tree.m_trackmultiplicity >= 9 and \
#       tree.m_recoMass > 100 and \
#       tree.m_recoMomentumT > 5 and \
#       tree.m_recoEnergy < 500 and \
#       tree.m_taudiscr > 1 and \
#       tree.m_omegaiso > 0.5 and \
#       (-12 <= tree.m_logyplus <= -3) and \
#       (-9 <= tree.m_logyminus <= -1.5) and \
#       (20 <= tree.m_w_lepMass_1 <= 250) and \
#       (40 <= tree.m_w_lepMass_2 <= 120) and \
#       (40 <= tree.m_w_jetMass <= 120) and \
#       tree.m_cosThetaW >-0.95 and \
       True):

       makesCut = True
    return makesCut

for i in range(0,nEntries):
  t.GetEntry(i)
  r.GetEntry(i)
  hist.Fill(t.m_w_lepMass_2, applycut(t) )
  hist1.Fill(r.m_w_lepMass_2, applycut(r) )

s1.Add(hist1)
s1.Add(hist)
s1.Draw("hist nostack")

legend = TLegend(0.67, 0.7, 0.89, 0.91)
legend.SetHeader("e_{L}^{-} e_{R}^{+}", "C")
legend.AddEntry(hist, "Full formula with MC Photon mass", "l")
legend.AddEntry(hist1, "Simple formula", "l")
legend.Draw()

c1.Print("../plots/W_mass_full_MC_mass.root")
