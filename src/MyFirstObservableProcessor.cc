#include "MyFirstObservableProcessor.h"


MyFirstObservableProcessor aMyFirstObservableProcessor;

//-------------------------------------------------------------------------------------------------

MyFirstObservableProcessor::MyFirstObservableProcessor() : Processor("MyFirstObservableProcessor")
{
    // modify processor description
    _description = "MyFirstObservableProcessor creates a root branch containing energy information";


    // register steering parameters: name, description, class-variable, default value

/**
 *  registerInputCollection(
 *          LCIO::RECONSTRUCTEDPARTICLE,         // The collection type. Checkout the LCIO documentation for other types
 *          "PfoCollection",                     // The parameter name to read from steering file
 *          "The Pandora PFO collection name",   // A parameter description. Please fill this correctly
 *          m_pfoCollectionName_temp,            // Your variable to store the result after steering file parsing
 *          std::string("PandoraPFOs") );        // That's the default value, in case
 **/

    registerInputCollection(LCIO::MCPARTICLE,
                            "MCParticleCollection",
                            "Name of the MC particle collection",
                            m_mcCollectionName,
                            std::string("MCParticle"));

    registerInputCollection(
        LCIO::RECONSTRUCTEDPARTICLE,
        "PfoCollectionOverlayRemoved",
        "Name of Reconstructed particles without overlay",
        m_pfoCollectionName,
        std::string("PFOsOverlayRemoved"));

    registerInputCollection(
        LCIO::RECONSTRUCTEDPARTICLE,
        "InputIsolepsCollection",
        "Name of the isolated lepton collection",
        m_isolatedLeptonsCollectionName,
        std::string("Isoleps"));

    registerInputCollection(
        LCIO::RECONSTRUCTEDPARTICLE,
        "InputJetsCollection",
        "Name of jets collection",
        m_jetsCollectionName,
        std::string("FastJets"));

    registerProcessorParameter("OutputRootFileName",
                               "Path of output rootfile",
                               m_rootfilename,
                               std::string("test.root"));
}

//-------------------------------------------------------------------------------------------------
void MyFirstObservableProcessor::init()
{
    m_rootfile = new TFile(m_rootfilename.c_str(), "recreate");
    m_testtree = new TTree("ObservablesTree", "ObservablesTree");

    this->setTTreeBranches();
}

//-------------------------------------------------------------------------------------------------
void MyFirstObservableProcessor::processRunHeader(EVENT::LCRunHeader *run)
{
    streamlog_out(MESSAGE) << "Starting run no " << run->getRunNumber() << std::endl;
}

//-------------------------------------------------------------------------------------------------

void MyFirstObservableProcessor::processEvent(EVENT::LCEvent *evt)
{
    //this->readInputInfo(); // Read info about process

    m_event = evt;

    //streamlog_out(DEBUG) <<"Processing event no " << m_event->getEventNumber() << " - run " << m_event->getEventNumber() << std::endl;
    m_com_E = m_event->getParameters().getFloatVal("Energy");

    this->analyseMCParticles();
    this->analyseReconstructed();
    this->neutrinoCorrection(m_recomomentum);
    this->getMCAngles();

    m_testtree->Fill();
    streamlog_out(DEBUG) << std::endl;
}

//-------------------------------------------------------------------------------------------------

void MyFirstObservableProcessor::end()
{
    std::cout << "MyFirstObservableProcessor: end()" << this->name() << " Rootfile: "
              << m_rootfilename.c_str() << std::endl << std::endl;

    streamlog_out(WARNING) << "Num of negative photon A = " << num_neg_A << std::endl;
    streamlog_out(WARNING) << "Num of negative photon B = " << num_neg_B << std::endl << std::endl;
    streamlog_out(WARNING) << "Num of negative photon A and B = " << num_neg_BOTH << std::endl;


    // Write to .root file
    m_rootfile->cd();

    streamlog_out(DEBUG) << "In end: Writing trees." << std::endl;
    m_testtree->Write();

    streamlog_out(DEBUG) << "In end: Closing file." << std::endl;
    m_rootfile->Close();

    delete m_rootfile;
    streamlog_out(DEBUG) << "In end: Done." << std::endl << std::endl;
}
