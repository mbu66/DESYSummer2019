/**
Read the root file containing the signal and error TVectors from the angle efficiency dependance analysis
**/
#include <vector>
#include "TFile.h"
#include "TTree.h"
#include "TH1F.h"
#include "math.h"

void read()
{
  //Read input file
  TFile *g = TFile::Open("SelectionEfficiency.root", "READ");

  //Initialise vectors
  TVectorT<double> *signal;
  TVectorT<double> *error;

  //Extract and fill vectors
  signal = (TVectorT<double>*)g->Get("signal");
  error = (TVectorT<double>*)g->Get("error");

  //Print vector contents
  for(int i=0; i< 2000; i++){
    //std::cout << "signal = " << ( (*signal) )[i] << '\t' << '\t' << "error = " << ( (*error) )[i] << '\n';
  }

}

void SignalSelectionEfficiency_read() {
  read();
}
