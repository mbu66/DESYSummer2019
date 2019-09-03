#include "MyFirstObservableProcessor.h"


MyFirstObservableProcessor aMyFirstObservableProcessor ;

//-------------------------------------------------------------------------------------------------//

MyFirstObservableProcessor::MyFirstObservableProcessor() : Processor("MyFirstObservableProcessor") {

  //Processor description
  _description = "MyFirstObservableProcessor creates a root with with a tree containing variables used for analysis" ;

  //Register steering parameters: name, description, class-variable, default value

  registerInputCollection( LCIO::MCPARTICLE,
          "MCParticleCollection",
          "Name of the MC particle collection",
          m_mcCollectionName,
          std::string("MCParticle") );

  registerInputCollection(
          LCIO::RECONSTRUCTEDPARTICLE,
          "PfoCollectionOverlayRemoved",
          "Name of Reconstructed particles without overlay",
          m_pfoCollectionName,
          std::string("PFOsOverlayRemoved") );

  registerInputCollection(
          LCIO::RECONSTRUCTEDPARTICLE,
          "InputIsolepsCollection",
          "Name of the isolated lepton collection",
          m_isolatedLeptonsCollectionName,
          std::string("Isoleps") );

  registerInputCollection(
          LCIO::RECONSTRUCTEDPARTICLE,
          "InputJetsCollection",
          "Name of jets collection",
          m_jetsCollectionName,
          std::string("FastJets") );

  registerProcessorParameter("OutputRootFileName",
          "Path of output rootfile",
          m_rootfilename,
          std::string("test.root"));
}

//-------------------------------------------------------------------------------------------------//

void MyFirstObservableProcessor::init() {

  //Construct root file and tree
  m_rootfile = new TFile(m_rootfilename.c_str(), "recreate");
  m_testtree  = new TTree("ObservablesTree", "ObservablesTree");

  //Fill tree with branches
  this->setTTreeBranches();
}

//-------------------------------------------------------------------------------------------------//

void MyFirstObservableProcessor::processRunHeader( EVENT::LCRunHeader* run) {
    streamlog_out(MESSAGE) << "Starting run no " << run->getRunNumber() << std::endl;
}

//-------------------------------------------------------------------------------------------------//

void MyFirstObservableProcessor::processEvent( EVENT::LCEvent * evt ) {

  //Label event
  m_event = evt;

  //Get center of mass energy
  m_com_E = m_event->getParameters().getFloatVal( "Energy" );

  //Analysie MC particle information
  this->analyseMCParticles();

  //Analysie Reconstructed particle information
  this->analyseReconstructed();

  //Correct for ISR and neutrino
  this->neutrinoCorrection(m_recomomentum);

  //Extract angles for analysis
  this->getMCAngles();

  //Fill tree with extracted variables
  m_testtree->Fill();
}

//-------------------------------------------------------------------------------------------------//

void MyFirstObservableProcessor::end(){

  //State end of processor and generation of root file
  std::cout << "MyFirstObservableProcessor: end()" << this->name() << " Rootfile: "
            << m_rootfilename.c_str() << std::endl << std::endl;

  //Write to root file
  m_rootfile->cd();
  streamlog_out(DEBUG) << "In end: Writing trees." << std::endl;
  m_testtree->Write();

  //Close root file
  streamlog_out(DEBUG) << "In end: Closing file." << std::endl;
  m_rootfile->Close();

  //Clean up and end
  delete m_rootfile;
  streamlog_out(DEBUG) << "In end: Done." << std::endl << std::endl;
}

//-------------------------------------------------------------------------------------------------//
