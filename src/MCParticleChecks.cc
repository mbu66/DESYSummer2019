#include "MyFirstObservableProcessor.h"

//-------------------------------------------------------------------------------------------------//

TLorentzVector MyFirstObservableProcessor::analyseMCPhoton(){
  /**
  Returns 4-momenta of 'ISR photon', the sum of 2 ISR photons from MC particles
  **/

  //Try to extract MC collection
  LCCollection* _col = NULL;
  try{
    _col = m_event->getCollection( m_mcCollectionName );
  }
  catch( lcio::DataNotAvailableException e )
  {
    streamlog_out(WARNING) << m_mcCollectionName << " collection not available" << std::endl;
    _col = NULL;
  }

  //If collection available, extract 4 momenta of ISR into TLorentz vectors and sum
  TLorentzVector _momentum {};
  if( _col != NULL ){
    MCParticle* particle1 = dynamic_cast<EVENT::MCParticle*>(_col->getElementAt(4));
    if(nullptr == particle1) {
      streamlog_out(ERROR) << "ERROR in analyseMCPhoton: Wrong object type in collection '"
      << m_mcCollectionName << "'" << std::endl;
    }
    _momentum += TLorentzVector( particle1->getMomentum(), particle1->getEnergy() );

    MCParticle* particle2 = dynamic_cast<EVENT::MCParticle*>(_col->getElementAt(5));
    if(nullptr == particle2) {
      streamlog_out(ERROR) << "ERROR in analyseMCPhoton: Wrong object type in collection '"
      << m_mcCollectionName << "'" << std::endl;
    }
    _momentum += TLorentzVector( particle2->getMomentum(), particle2->getEnergy() );

    //Check both particles are of type photon
    if(particle1->getPDG() != 22 || particle1->getPDG() != 22){
      streamlog_out(WARNING) << "ERROR in analyseMCPhoton: Not ISR Photons" << std::endl;
    }
  }
  return _momentum;
}

//-------------------------------------------------------------------------------------------------//

TLorentzVector MyFirstObservableProcessor::analyseMCHadronicW(){
  /**
  Returns 4-momenta of hadronic W, by summing over 2 quarks from MC particles
  **/

  //Try to extract MC collection
  LCCollection* _col = NULL;
  try{
      _col = m_event->getCollection( m_mcCollectionName );
  }
  catch( lcio::DataNotAvailableException e )
  {
      streamlog_out(WARNING) << m_mcCollectionName << " collection not available" << std::endl;
      _col = NULL;
  }

  //If collection available, extract 4 momenta of quarks into TLorentz vector and sum
  TLorentzVector _momentum {};
  if( _col != NULL ){
      MCParticle* particle1 = dynamic_cast<EVENT::MCParticle*>(_col->getElementAt(6));
      if(nullptr == particle1) {
          streamlog_out(ERROR) << "ERROR in analyseMCHadronicW: Wrong object type in collection '"
          << m_mcCollectionName << "'" << std::endl;
      }
      _momentum += TLorentzVector( particle1->getMomentum(), particle1->getEnergy() );

      MCParticle* particle2 = dynamic_cast<EVENT::MCParticle*>(_col->getElementAt(7));
      if(nullptr == particle2) {
          streamlog_out(ERROR) << "ERROR in analyseMCHadronicW: Wrong object type in collection '"
          << m_mcCollectionName << "'" << std::endl;
      }
      _momentum += TLorentzVector( particle2->getMomentum(), particle2->getEnergy() );
  }
  return _momentum;
}

//-------------------------------------------------------------------------------------------------//

TLorentzVector MyFirstObservableProcessor::analyseMCLeptonicW(){
  /**
  Returns 4-momenta of leptonic W, by summing over neutrino and lepton from MC particles
  **/

  //Try to extract MC collection
  LCCollection* _col = NULL;
  try{
      _col = m_event->getCollection( m_mcCollectionName );
  }
  catch( lcio::DataNotAvailableException e )
  {
      streamlog_out(WARNING) << m_mcCollectionName << " collection not available" << std::endl;
      _col = NULL;
  }

  //If collection available, extract 4 momenta of quarks into TLorentz vector and sum
  TLorentzVector _momentum {};
  if( _col != NULL ){
      MCParticle* particle = dynamic_cast<EVENT::MCParticle*>(_col->getElementAt(9));
      if(nullptr == particle) {
          streamlog_out(ERROR) << "ERROR in analyseMCLeptonicW: Wrong object type in collection '"
          << m_mcCollectionName << "'" << std::endl;
      }
      _momentum += TLorentzVector( particle->getMomentum(), particle->getEnergy() );

      MCParticle* particle1= dynamic_cast<EVENT::MCParticle*>(_col->getElementAt(8));
      if(nullptr == particle1) {
          streamlog_out(ERROR) << "ERROR in analyseMCLeptonicW: Wrong object type in collection '"
          << m_mcCollectionName << "'" << std::endl;
      }
      _momentum += TLorentzVector( particle1->getMomentum(), particle1->getEnergy() );
  }
  return _momentum;
}

//-------------------------------------------------------------------------------------------------//

TLorentzVector MyFirstObservableProcessor::analyseMCLepton(){
  /**
  Returns 4-momenta of lepton from MC particles
  **/

  //Try to extract MC collection
  LCCollection* _col = NULL;
  try{
      _col = m_event->getCollection( m_mcCollectionName );
  }
  catch( lcio::DataNotAvailableException e )
  {
      streamlog_out(WARNING) << m_mcCollectionName << " collection not available" << std::endl;
      _col = NULL;
  }

  //If collection available, extract 4 momenta of lepton into TLorentz vector
  TLorentzVector _momentum {};
  if( _col != NULL ){
      // Lepton
      MCParticle* particle1= dynamic_cast<EVENT::MCParticle*>(_col->getElementAt(8));
      if(nullptr == particle1) {
          streamlog_out(ERROR) << "ERROR in analyseMCLepton: Wrong object type in collection '"
          << m_mcCollectionName << "'" << std::endl;
      }
      _momentum = TLorentzVector( particle1->getMomentum(), particle1->getEnergy() );
  }
    return _momentum;
}

//-------------------------------------------------------------------------------------------------//

TLorentzVector MyFirstObservableProcessor::analyseMCNeutrino(){
  /**
  Returns 4-momenta of neutrino from MC particles
  **/

  //Try to extract MC collection
  LCCollection* _col = NULL;
  try{
    _col = m_event->getCollection( m_mcCollectionName );
  }
  catch( lcio::DataNotAvailableException e )
  {
    streamlog_out(WARNING) << m_mcCollectionName << " collection not available" << std::endl;
    _col = NULL;
  }

  //If collection available, extract 4 momenta of neutrino into TLorentz vector
  TLorentzVector _momentum {};
  if( _col != NULL ){
    MCParticle* particle = dynamic_cast<EVENT::MCParticle*>(_col->getElementAt(9));
    if(nullptr == particle) {
      streamlog_out(ERROR) << "ERROR in analyseMCNeutrino: Wrong object type in collection '"
      << m_mcCollectionName << "'" << std::endl;
    }
    _momentum = TLorentzVector( particle->getMomentum(), particle->getEnergy() );
  }
  return _momentum;
}

//-------------------------------------------------------------------------------------------------//

double MyFirstObservableProcessor::getLeptonFlavour(){
  /**
  Returns flavour of lepton from MC particles
  **/

  //Try to extract MC collection
  LCCollection* _col = NULL;
  try{
    _col = m_event->getCollection( m_mcCollectionName );
  }
  catch( lcio::DataNotAvailableException e )
  {
    streamlog_out(WARNING) << m_mcCollectionName << " collection not available" << std::endl;
    _col = NULL;
  }

  //If collection available, extract lepton flavour
  float          _leptonFlavour {};
  if( _col != NULL ){
    MCParticle* particle= dynamic_cast<EVENT::MCParticle*>(_col->getElementAt(8));
    if(nullptr == particle) {
      streamlog_out(ERROR) << "ERROR in getLeptonFlavour: Wrong object type in collection '"
      << m_mcCollectionName << "'" << std::endl;
    }
    _leptonFlavour = particle->getPDG();
  }
  return _leptonFlavour;
}

//-------------------------------------------------------------------------------------------------//

void MyFirstObservableProcessor::analyseMCParticles(){
  /**
  Evaluates 4 momenta of W bosons, lepton, neutrino and ISR photon from MC particles
  Evaluates visible 4 momenta from MC particles
  Gets the flavour of the lepton from MC particles
  Evaluates relevant variables for analysis
  **/

  //Evaluate leptonic W
  m_mcLeptonicWMomentum = analyseMCLeptonicW();
  m_mcLeptonicWMomentumT = m_mcLeptonicWMomentum.Perp();
  m_mcLeptonicWMomentumEnergy = m_mcLeptonicWMomentum.Energy();

  //Evaluate hadronic W
  m_mcHadronicWMomentum = analyseMCHadronicW();

  //Evaluate lepton
  m_mcLeptonMomentum = analyseMCLepton();

  //Evaluate neutrino
  m_mcNeutrinoMomentum = analyseMCNeutrino();
  m_mcNeutrinoMass = m_mcNeutrinoMomentum.M();

  //Evaluate ISR photon
  m_mcPhotonMomentum = analyseMCPhoton();
  m_mcPhotonEnergy = m_mcPhotonMomentum.Energy();
  m_mcPhotonTheta = m_mcPhotonMomentum.Theta();
  m_mcPhotonMass = m_mcPhotonMomentum.M();

  //Evaluate visible 4 momenta (lepton + quarks)
  m_mcParticleMomentum = m_mcLeptonMomentum + m_mcHadronicWMomentum;
  m_mcParticleMomentumT = m_mcParticleMomentum.Perp();
  m_mcParticleMomentumZ = m_mcParticleMomentum.Pz();
  m_mcParticleEnergy = m_mcParticleMomentum.Energy();
  m_mcParticleMass = m_mcParticleMomentum.M();

  //Gets lepton flavour
  m_mcLeptonFlavour = getLeptonFlavour();
}

//-------------------------------------------------------------------------------------------------//
