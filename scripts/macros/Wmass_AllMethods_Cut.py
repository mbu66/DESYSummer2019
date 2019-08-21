from ROOT import *

f = TFile("../high_stat/extraction_long.root")
t = f.Get("ObservablesTree")
nEntries = t.GetEntries()

hist = TH1F("hist", "; M_{W_{lep}}[GeV]; a.u.", 200, 0,  200)
hist.SetLineColor(kGreen+1)
hist.SetLineWidth(3)
hist1 = TH1F("hist1", "; M_{W_{lep}}[GeV]; a.u.", 200, 0, 200)
hist1.SetLineColor(kBlue)
hist1.SetLineWidth(3)

hist2 = TH1F("hist2", "; M_{W_{lep}}[GeV]; a.u.", 200, 0,  200)
hist2.SetLineColor(kRed)
hist2.SetLineWidth(3)


c1 = TCanvas("c1", "Test Stacked Histograms", 1000, 1000)
s1 = THStack("s1", "; M_{W_{lep}}[GeV]; a.u.")

def applycut(mass):
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
       (40 <= mass <= 120) and \
       (40 <= t.m_w_jetMass <= 120) and \
       t.m_cosThetaW >-0.95 and \
       True):

       makesCut = True
    return makesCut

for i in range(0,nEntries):
  t.GetEntry(i)
  hist.Fill(t.m_w_lepMass_1, applycut(t.m_w_lepMass_1) )
  hist1.Fill(t.m_w_lepMass_2, applycut(t.m_w_lepMass_2) )
  hist2.Fill(t.m_w_lepMass, applycut(t.m_w_lepMass) )

s1.Add(hist)
s1.Add(hist1)
s1.Add(hist2)
s1.Draw("hist nostack")

legend = TLegend(0.67, 0.7, 0.89, 0.91)
legend.SetHeader("e_{L}^{-} e_{R}^{+} with cuts", "C")
legend.AddEntry(hist, "E_{ISR} = 0", "l")
legend.AddEntry(hist1, "E_{ISR} from formula", "l")
legend.AddEntry(hist2, "E_{ISR} with both", "l")
legend.Draw()
print(nEntries)
#c1.Print("../plots/W_lep_mass_cut.root")
