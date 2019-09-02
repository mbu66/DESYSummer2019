from ROOT import *

f = TFile("../high_stat/root/extraction_long.root")
t = f.Get("ObservablesTree")
g = TFile("../high_stat/root/extraction_long_cheat.root")
r = g.Get("ObservablesTree")

nEntries = t.GetEntries()

flow = [0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0]
flow_cheat = [0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0]
flow_P = [0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0]
flow_cheat_P = [0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0]

binlabels = ["muon","n_{tracks}","#sqrt{s}","P_{T}","E_{SUM}","ln(y_{+})", "lepton","m_{W}^{lep} (pre ISR)", "#tau_{discr}", "Q_{lepton}", "\Delta\Omega_{iso}", "m_{W}^{lep}","m_{W}^{had}","cos(#theta_{W})"]
ivan = [107233.0, 107229.0, 105050.0, 103681.0, 102259.0, 101882.0, 84443.0, 82149.0, 79423.0, 78830.0, 78730.0, 75204.0, 71776.0, 71611.0]

def hist_flow(my_flow, _tree):
    for i in range(0,nEntries):
        _tree.GetEntry(i)
        if abs(_tree.m_mcLeptonFlavour) == 13:
            my_flow[0] += 1
            if _tree.m_trackmultiplicity >= 9 and _tree.m_isolepnumber == 1:
                my_flow[1] +=1
                if _tree.m_recoMass > 100:
                    my_flow[2] += 1
                    if _tree.m_recoMomentumT > 5:
                        my_flow[3] += 1
                        if _tree.m_recoEnergy < 500:
                            my_flow[4] += 1
                            if -12 <= _tree.m_logyplus <= -3:
                                my_flow[5] += 1
                                if _tree.m_isolepnumber == 1:
                                    my_flow[6] += 1
                                    if  20 <= _tree.m_w_lepMass_1 <= 250:
                                        my_flow[7] += 1
                                        if _tree.m_taudiscr > 1:
                                            my_flow[8] += 1
                                            if True:
                                                my_flow[9] += 1
                                                if _tree.m_omegaiso > 0.5:
                                                    my_flow[10] += 1
                                                    if 40 <= _tree.m_w_lepMass <= 120:
                                                        my_flow[11] += 1
                                                        if 40 <= _tree.m_w_jetMass <= 120:
                                                            my_flow[12] += 1
                                                            if _tree.m_cosThetaW > -0.95:
                                                                my_flow[13] += 1
def hist_flow_P(my_flow, _tree):
    for i in range(0,nEntries):
        _tree.GetEntry(i)
        if abs(_tree.m_mcLeptonFlavour) == 13 and _tree.m_mcPhotonEnergy < 1 :
            my_flow[0] += 1
            if _tree.m_trackmultiplicity >= 9 and _tree.m_isolepnumber == 1:
                my_flow[1] +=1
                if _tree.m_recoMass > 100:
                    my_flow[2] += 1
                    if _tree.m_recoMomentumT > 5:
                        my_flow[3] += 1
                        if _tree.m_recoEnergy < 500:
                            my_flow[4] += 1
                            if -12 <= _tree.m_logyplus <= -3:
                                my_flow[5] += 1
                                if _tree.m_isolepnumber == 1:
                                    my_flow[6] += 1
                                    if  20 <= _tree.m_w_lepMass_1 <= 250:
                                        my_flow[7] += 1
                                        if _tree.m_taudiscr > 1:
                                            my_flow[8] += 1
                                            if True:
                                                my_flow[9] += 1
                                                if _tree.m_omegaiso > 0.5:
                                                    my_flow[10] += 1
                                                    if 40 <= _tree.m_w_lepMass <= 120:
                                                        my_flow[11] += 1
                                                        if 40 <= _tree.m_w_jetMass <= 120:
                                                            my_flow[12] += 1
                                                            if _tree.m_cosThetaW > -0.95:
                                                                my_flow[13] += 1

hist_flow(flow, t)
hist_flow(flow_cheat, r)

hist_flow_P(flow_P, t)
hist_flow_P(flow_cheat_P, r)

c1 = TCanvas("c1","c1",800,800)

hist = TH1F("hist", ";Cutflow ;Efficiency [%]", 14, 0, 14)
hist.SetLineWidth(3)
hist1 = TH1F("hist1", ";Cutflow ;Efficiency [%]", 14, 0, 14)
hist1.SetLineColor(kRed)
hist1.SetLineWidth(3)
hist2 = TH1F("hist2", ";Cutflow ;Efficiency [%]", 14, 0, 14)
hist2.SetLineColor(kGreen+1)
hist2.SetLineWidth(3)

hist_P = TH1F("hist_P", ";Cutflow ;Efficiency [%]", 14, 0, 14)
hist_P.SetLineWidth(3)
hist_P.SetLineStyle(2)
hist_P2 = TH1F("hist_P2", ";Cutflow ;Efficiency [%]", 14, 0, 14)
hist_P2.SetLineColor(kGreen+1)
hist_P2.SetLineWidth(3)
hist_P2.SetLineStyle(2)

scale = flow[0]
scale1 = ivan[0]
scale2 = flow_cheat[0]

scale_P = flow_P[0]
scale_P2 = flow_cheat_P[0]

print(scale1)
print(scale)
print(scale2)
print(scale_P)
print(scale_P2)

for i in range(0, 14):
    flow[i] = 100 * flow[i] / scale
    ivan[i] = 100 * ivan[i] / scale1
    flow_cheat[i] = 100 * flow_cheat[i] / scale2
    flow_P[i] = 100 * flow_P[i] / scale_P
    flow_cheat_P[i] = 100 * flow_cheat_P[i] / scale_P2
    hist.Fill(i, flow[i])
    hist1.Fill(i, ivan[i])
    hist2.Fill(i, flow_cheat[i])
    hist1.GetXaxis().SetBinLabel(i+1, binlabels[i])
    hist1.GetXaxis().ChangeLabel(i+1, 0.8)
    hist_P.Fill(i, flow_P[i])
    hist_P2.Fill(i, flow_cheat_P[i])
    print(flow[i], ivan[i], flow_cheat[i], flow_P[i],flow_cheat_P[i])


hist1.GetXaxis().SetLabelOffset(0.008)
hist1.GetXaxis().SetLabelSize(0.03)

c1.SetGridx()

hist1.GetYaxis().SetRangeUser(0, 110)
hist1.Draw("hist")
hist2.Draw("hist same")
#hist_P2.Draw("hist same")
#hist_P.Draw("hist same")
hist.Draw("hist same")

legend = TLegend(0.67, 0.2, 0.89, 0.51)
legend.SetHeader("e_{L}^{-} e_{R}^{+}", "C")
legend.AddEntry(hist, "My Results", "l C")
#legend.AddEntry(hist_P, "#rightarrow E^{MC}_{#gamma} < 1", "l C")
legend.AddEntry(hist2, "Cheated Overlay", "l C")
#legend.AddEntry(hist_P2, "#rightarrow E^{MC}_{#gamma} < 1", "l C")
legend.AddEntry(hist1, "Ivan's Results", "l C")

legend.Draw()
