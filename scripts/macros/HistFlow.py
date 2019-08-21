from ROOT import *

f = TFile("../high_stat/extraction_long.root")
t = f.Get("ObservablesTree")
nEntries = t.GetEntries()

flow = [0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0]
binlabels = ["muon","n_{tracks}","#sqrt{s}","P_{T}","E_{SUM}","ln(y_{+})", "lepton","m_{W}^{lep} (pre ISR)", "#tau_{discr}", "Q_{lepton}", "\Delta\Omega_{iso}", "m_{W}^{lep}","m_{W}^{had}","cos(#theta_{W})"]
ivan = [107233.0, 107229.0, 105050.0, 103681.0, 102259.0, 101882.0, 84443.0, 82149.0, 79423.0, 78830.0, 78730.0, 75204.0, 71776.0, 71611.0]

for i in range(0,nEntries):
    t.GetEntry(i)
    if abs(t.m_mcLeptonFlavour) == 13:
        flow[0] += 1
        if t.m_trackmultiplicity >= 9:
            flow[1] +=1
            if t.m_recoMass > 100:
                flow[2] += 1
                if t.m_recoMomentumT > 5:
                    flow[3] += 1
                    if t.m_recoEnergy < 500:
                        flow[4] += 1
                        if -12 <= t.m_logyplus <= -3:
                            flow[5] += 1
                            if t.m_isolepnumber == 1:
                                flow[6] += 1
                                if  20 <= t.m_w_lepMass_1 <= 250:
                                    flow[7] += 1
                                    if t.m_taudiscr > 1:
                                        flow[8] += 1
                                        if True:
                                            flow[9] += 1
                                            if t.m_omegaiso > 0.5:
                                                flow[10] += 1
                                                if 40 <= t.m_w_lepMass <= 120:
                                                    flow[11] += 1
                                                    if 40 <= t.m_w_jetMass <= 120:
                                                        flow[12] += 1
                                                        if t.m_cosThetaW > -0.95:
                                                            flow[13] += 1

c1 = TCanvas("c1","c1",800,800)

hist = TH1F("hist", ";Cutflow ;Efficiency [%]", 14, 0, 14)
hist.SetLineWidth(3)
hist1 = TH1F("hist1", ";Cutflow ;Efficiency [%]", 14, 0, 14)
hist1.SetLineColor(kRed)
hist1.SetLineWidth(3)
scale = flow[0]
scale1 = ivan[0]
print(scale)
for i in range(0, 14):
    flow[i] = 100 * flow[i] / scale
    ivan[i] = 100 * ivan[i] / scale1
    hist.Fill(i, flow[i])
    hist1.Fill(i, ivan[i])
    hist1.GetXaxis().SetBinLabel(i+1, binlabels[i])
    hist1.GetXaxis().ChangeLabel(i+1, 0.8)
    print(flow[i], ivan[i])

hist1.GetXaxis().SetLabelOffset(0.008)
hist1.GetXaxis().SetLabelSize(0.03)

hist1.GetYaxis().SetRangeUser(0, 110)
hist1.Draw("hist")
hist.Draw("hist same")

legend = TLegend(0.67, 0.7, 0.89, 0.91)
legend.SetHeader("e_{L}^{-} e_{R}^{+}", "C")
legend.AddEntry(hist, "My Results", "l")
legend.AddEntry(hist1, "Ivan's Results", "l")
legend.Draw()
