#Histogram showing the recnstructed leptonic W mass for all 3 reconstruction techniques
# TODO: Change mean and error values to be not hard coded (line 52)
from ROOT import *

# Load in root tree
f = TFile("../root_files/extraction_long.root")
t = f.Get("ObservablesTree")

# Construct and format histograms
hist = TH1F("hist", "; M_{W_{lep}}[GeV]; a.u.", 200, 0,  200)
hist.SetLineColor(kGreen+1)
hist.SetLineWidth(3)
hist1 = TH1F("hist1", "; M_{W_{lep}}[GeV]; a.u.", 200, 0, 200)
hist1.SetLineColor(kBlue)
hist1.SetLineWidth(3)

hist2 = TH1F("hist2", "; M_{W_{lep}}[GeV]; a.u.", 200, 0,  200)
hist2.SetLineColor(kRed)
hist2.SetLineWidth(3)

# Construct canvas and stack
c1 = TCanvas("c1", "Test Stacked Histograms", 1000, 1000)
s1 = THStack("s1", "; M_{W_{lep}}[GeV]; a.u.")

# Define efficiency cut
def applycut(mass):
    makesCut = False
    if(t.m_isolepnumber == 1 and abs(t.m_mcLeptonFlavour) == 13):

       makesCut = True
    return makesCut

# Fill histograms
nEntries = t.GetEntries()
for i in range(0,nEntries):
  t.GetEntry(i)
  hist.Fill(t.m_w_lepMass_1, applycut(t.m_w_lepMass_1) )
  hist1.Fill(t.m_w_lepMass_2, applycut(t.m_w_lepMass_2) )
  hist2.Fill(t.m_w_lepMass, applycut(t.m_w_lepMass) )

# Normalise histograms
hist.Scale(1 / hist.Integral())
hist1.Scale(1 / hist1.Integral())
hist2.Scale(1 / hist2.Integral())

# Add histograms to stack and draw
s1.Add(hist)
s1.Add(hist1)
s1.Add(hist2)
s1.Draw("hist nostack")

# Add mean and error boxes ***VALUES HARD CODED***
box1 = TPaveText(0.2, 0.7, 0.4, 0.85, "blNDC")
box1.SetFillColor(0)
box1.SetTextAlign(12)
box1.SetBorderSize(1)
box1.SetLineColor(kRed)
myTextEntry= box1.AddText("80.95 #pm 0.06")
box1.Draw()

box2 = TPaveText(0.2, 0.5, 0.4, 0.65, "blNDC")
box1.SetFillColor(0)
box2.SetTextAlign(12)
box2.SetBorderSize(1)
box2.SetLineColor(kBlue)
myTextEntry= box2.AddText("80.92 #pm 0.06")
box2.Draw()

box3 = TPaveText(0.2, 0.3, 0.4, 0.45, "blNDC")
box3.SetFillColor(0)
box3.SetTextAlign(12)
box3.SetBorderSize(1)
box3.SetLineColor(kGreen+1)
myTextEntry= box3.AddText("88.02 #pm 0.10")
box3.Draw()

# Add legend entries and draw
legend = TLegend(0.67, 0.7, 0.89, 0.91)
legend.SetHeader("e_{L}^{-} e_{R}^{+}", "C")
legend.AddEntry(hist, "E_{ISR} = 0", "l")
legend.AddEntry(hist1, "E_{ISR} from formula", "l")
legend.AddEntry(hist2, "E_{ISR} with both", "l")
legend.Draw()

# Print means and errors
print(hist.GetMean(), hist1.GetMean(), hist2.GetMean() )
print(hist.GetMeanError(), hist1.GetMeanError(), hist2.GetMeanError() )
