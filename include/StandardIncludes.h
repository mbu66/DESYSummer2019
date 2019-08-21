#ifndef STANDARD_INCLUDES_H
#define STANDARD_INCLUDES_H 1

#include "lcio.h"
#include <iostream>
#include <fstream>
#include <set>
#include <cmath>

//#include <math>
#include <string>
#include <vector>
#include <set>
#include <algorithm> // for std::find
#include <iterator> // for std::begin, std::end
#include <limits> // for getting maximum value that class (e.g. float) can have


//ROOT
#include "TFile.h"
#include "TTree.h"
#include "TH1F.h"
#include "TLorentzVector.h"
#include "TString.h"

//LCIO
#include <EVENT/LCCollection.h>
#include <IMPL/LCParametersImpl.h>
#include <IMPL/MCParticleImpl.h>
#include <EVENT/MCParticle.h>
#include <EVENT/ReconstructedParticle.h>
#include <EVENT/Vertex.h>
#include "UTIL/LCTOOLS.h"

//Marlin
#include "marlin/Processor.h"

//----- include for verbosity dependend logging ---------
#include "marlin/VerbosityLevels.h"

using namespace lcio ;
using namespace marlin ;

#endif
