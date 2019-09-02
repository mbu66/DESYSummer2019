from ROOT import *
import math

f = TFile("../high_stat/root/extraction_long.root")
t = f.Get("ObservablesTree")

nEntries = t.GetEntries()

hist0 = TH3D("hist0", "", 20, -1, 1, 10, -1, 1, 10, -3.2, 3.2)
hist1 = TH3D("hist1", "", 20, -1, 1, 10, -1, 1, 10, -3.2, 3.2)

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
    if applycut(t):
        hist0.Fill( math.cos(t.m_extractThetaMinus), math.cos(t.m_extractThetaLepton), t.m_extractPhiLepton)
    if abs(t.m_mcLeptonFlavour) == 13:
        hist1.Fill( math.cos(t.m_extractThetaMinus), math.cos(t.m_extractThetaLepton), t.m_extractPhiLepton)

hist0.Divide(hist0, hist1, 1.0, 1.0, "B")

g = TFile( "SignalEfficiency.root", "recreate" )
r = TTree( "SignalEfficiencyTree", "tree of tvectors" )

signal = TVector(2000)
error = TVector(2000)

r.Branch( "efficiency", signal, "efficiency/D" )
r.Branch( "uncertainty", error, "uncertainty/D" )

for i in range(20):
    for j in range(10):
        for k in range(10):
            signal(100*i + 10*j + 1*k) = hist0.GetBinContent(i, j, k)
            error(100*i + 10*j + 1*k) = hist0.GetBinError(i, j, k)
            if signal[100*i + 10*j + 1*k] == 0.0:
                error[100*i + 10*j + 1*k] = 1.0
            r.Fill()

print(signal)
g.Write()
g.Close()
