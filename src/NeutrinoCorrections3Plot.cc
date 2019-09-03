#include "MyFirstObservableProcessor.h"

//-------------------------------------------------------------------------------------------------//

TLorentzVector MyFirstObservableProcessor::getBoostVector(TLorentzVector &to_be_boosted, TLorentzVector &_boost_system){
  /**
  Boost to_be_boosted into the center of mass frame of _boost_system
  Return boosted vector
  **/
  TLorentzVector _boost_vector = to_be_boosted;
  TVector3 _boost_beta_vector = -1.0*_boost_system.BoostVector();
  _boost_vector.Boost(_boost_beta_vector);
  return _boost_vector;
}

//-------------------------------------------------------------------------------------------------//

double MyFirstObservableProcessor::getPhotonEnergy(TLorentzVector &_momentumIn, const double &_photonMassIn, const double &_neutrinoMassIn, const std::string &_type, const std::string &_mode){
  /**
  Return energy of photon from simple or full formula from visible system _momentumIn
  Mass of photon _photonMassIn can come from MC particles m_mcPhotonMass
  Mass of neutrino _neutrinoMassIn = 0
  Which of 2 energy solutions to calculate _type = ["A", "B"]
  Which equation to use _mode = ["simple", "full"] -> "full" with _photonMassIn = _neutrinoMassIn = 0 is the same as 'simple'
  **/

  //Calculate lambda
  m_lambda = 0.5 * ( pow( 500.0 -  _momentumIn.E() , 2) -  pow( _momentumIn.P() , 2) +  pow( _photonMassIn , 2) -  pow( _neutrinoMassIn , 2) );

  //Evaluate full formula for both solutions
  double _numeratorA = m_lambda*( 500.0 - _momentumIn.E() ) + _momentumIn.Pz()*sqrt( pow( m_lambda, 2) - pow( _photonMassIn , 2)*( pow( 500.0 - _momentumIn.E(), 2) -  pow( _momentumIn.Pz(), 2) ) );
  double _numeratorB = m_lambda*( 500.0 - _momentumIn.E() ) - _momentumIn.Pz()*sqrt( pow( m_lambda, 2) - pow( _photonMassIn , 2)*( pow( 500.0 - _momentumIn.E(), 2) -  pow( _momentumIn.Pz(), 2) ) );
  double _denominator =  pow( 500.0 - _momentumIn.E(), 2) - pow( _momentumIn.Pz(), 2);

  //Choose solution from input
  double _energyOut {};

  if(_mode == "simple" && _type == "A"){
    _energyOut = ( pow( 500.0 - _momentumIn.E(), 2) - pow( _momentumIn.P() , 2) ) / ( 1000.0 - 2*_momentumIn.E() - 2*_momentumIn.Pz() );
  }
  else if(_mode == "simple" && _type == "B"){
    _energyOut = ( pow( 500.0 - _momentumIn.E(), 2) - pow( _momentumIn.P() , 2) ) / ( 1000.0 - 2*_momentumIn.E() + 2*_momentumIn.Pz() );
  }
  else if(_mode == "full" && _type == "A" && m_lambda >= 0){
    _energyOut = _numeratorA / _denominator;
  }
  else if(_mode == "full" && _type == "A" && m_lambda < 0){
    //If lambda < 0 the solutions swap due to sqrt(lambda^2) evaluating to |lambda|
    _energyOut = _numeratorB / _denominator;
  }
  else if(_mode == "full" && _type == "B" && m_lambda >= 0){
    _energyOut = _numeratorB / _denominator;
  }
  else if(_mode == "full" && _type == "B" && m_lambda < 0){
    //If lambda < 0 the solutions swap due to sqrt(lambda^2) evaluating to |lambda|
    _energyOut = _numeratorA / _denominator;
  }
  else{
    streamlog_out(WARNING) << "getPhotonEnergy has wrong inputs" << std::endl;
  }
  return _energyOut;
}

//-------------------------------------------------------------------------------------------------//

void MyFirstObservableProcessor::neutrinoCorrection( TLorentzVector _momentumVector ){

  /**
  Correct for neutrino and ISR
  Fill relevant tree variables for analysis
  Evaluate tau discrimination variable and cos(Theta_W_had)
  **/

  //Boost visible and lepton momenta into CoM frame
  _boost_system_com = TLorentzVector(500.0*sin(0.014 / 2.0), 0, 0, 500.0);
  _boost_system_com_inv = TLorentzVector(-500.0*sin(0.014 / 2.0), 0, 0, 500.0);

  _boost = getBoostVector(_momentumVector, _boost_system_com);
  _boostIso = getBoostVector(m_isolepmomentum, _boost_system_com);
  _boostJet = getBoostVector(m_jetmomentum, _boost_system_com);

  /** Non-boosted solution (raise comments 3 lines to switch boost to non-boost mode)
  _boost = _momentumVector;
  _boostIso = m_isolepmomentum;
  _boostJet = m_jetmomentum;
  **/

  //1st energy solution - photon. neutrino and leptonic W boson
  _boostPhotonA.SetE( getPhotonEnergy(_boost, 0.0, 0.0, "A", "full") );
  _boostPhotonA.SetPx(0.0);
  _boostPhotonA.SetPy(0.0);
  _boostPhotonA.SetPz(-1.0*_boostPhotonA.E());

  m_neutrinomomentumA.SetPx( -1*_boost.Px() );
  m_neutrinomomentumA.SetPy( -1*_boost.Py() );
  m_neutrinomomentumA.SetPz( -1*( _boost.Pz() + _boostPhotonA.Pz() ) );
  m_neutrinomomentumA.SetE( 500.0 - _boostPhotonA.E() - _boost.E() );

  _boostLepA =  m_neutrinomomentumA + _boostIso;

  //2nd energy solution - photon. neutrino and leptonic W boson
  _boostPhotonB.SetE( getPhotonEnergy(_boost, 0.0, 0.0, "B", "full") );
  _boostPhotonB.SetPx(0.0);
  _boostPhotonB.SetPy(0.0);
  _boostPhotonB.SetPz(_boostPhotonB.E());

  m_neutrinomomentumB.SetPx( -1*_boost.Px() );
  m_neutrinomomentumB.SetPy( -1*_boost.Py() );
  m_neutrinomomentumB.SetPz( -1*( _boost.Pz() + _boostPhotonB.Pz() ) );
  m_neutrinomomentumB.SetE( 500.0 - _boostPhotonB.E() - _boost.E() );

  _boostLepB =  m_neutrinomomentumB + _boostIso;

  //3rd energy solution - neurtino and leptonic W boson (No ISR photon)
  m_neutrinomomentumC.SetPx( -1*_boost.Px() );
  m_neutrinomomentumC.SetPy( -1*_boost.Py() );
  m_neutrinomomentumC.SetPz( -1*_boost.Pz() );
  m_neutrinomomentumC.SetE( fabs( _boost.P() ) );

  _boostLepC =  m_neutrinomomentumC + _boostIso;

  //Evaluate cos Theta_W
  if(m_isolepflavour <= 0){
    m_cosThetaW = cos(_boostJet.Theta());
  }
  else{
    m_cosThetaW = cos( fmod( (_boostJet.Theta() + M_PI), ( 2 * M_PI) ) );
  }

  //Boost leptonic W boson and photon solutions back into Lab frame
  m_leptonicmomentumA = getBoostVector(_boostLepA, _boost_system_com_inv);
  m_leptonicmomentumB = getBoostVector(_boostLepB, _boost_system_com_inv);
  m_leptonicmomentumC = getBoostVector(_boostLepC, _boost_system_com_inv);

  m_photonmomentumA = getBoostVector(_boostPhotonA, _boost_system_com_inv);
  m_photonmomentumB = getBoostVector(_boostPhotonB, _boost_system_com_inv);

  /** Non-boosted solution (raise comments 7 lines to switch boost to non-boost mode)
  m_leptonicmomentumA = _boostLepA;
  m_leptonicmomentumB = _boostLepB;
  m_leptonicmomentumC = _boostLepC;

  m_photonmomentumA = _boostPhotonA;
  m_photonmomentumB = _boostPhotonB;
  **/

  //Choose solution with better W_mass estimate, all 3 solutions (enforce positive photon energy)
  if( fabs( m_leptonicmomentumA.M() - m_w_true) < fabs( m_leptonicmomentumB.M()  - m_w_true ) &&  fabs( m_leptonicmomentumA.M() - m_w_true) < fabs( m_leptonicmomentumC.M() - m_w_true )  && m_photonmomentumA.E() >= 0){
    m_leptonicmomentum = m_leptonicmomentumA;
    m_photonEnergyChosen = 1;
    m_photonmomentum = m_photonmomentumA;
  }
  else if( fabs( m_leptonicmomentumA.M() - m_w_true) > fabs( m_leptonicmomentumB.M() - m_w_true ) &&  fabs( m_leptonicmomentumB.M() - m_w_true) < fabs( m_leptonicmomentumC.M() - m_w_true )  && m_photonmomentumB.E() >= 0){
    m_leptonicmomentum = m_leptonicmomentumB;
    m_photonEnergyChosen = 2;
    m_photonmomentum = m_photonmomentumB;
  }
  else{
    m_leptonicmomentum = m_leptonicmomentumC;
    m_photonEnergyChosen = 3;
    m_photonmomentum = TLorentzVector(0.0, 0.0, 0.0, 0.0);
  }

  //Choose solution with better W_mass estimate without 3rd option
  if( fabs( m_leptonicmomentumA.M() - m_w_true) < fabs( m_leptonicmomentumB.M() - m_w_true )){
     m_leptonicmomentum_temp = m_leptonicmomentumA;
     m_photonEnergyChosen_temp = 1;
  }
  else{
    m_leptonicmomentum_temp = m_leptonicmomentumB;
    m_photonEnergyChosen_temp = 2;
  }

  //Evaluate leptonic W boson all 3 solutions
  m_leptonicmomentum_mass = m_leptonicmomentum.M();
  m_leptonicmomentum_energy = m_leptonicmomentum.Energy();
  m_leptonicmomentum_theta = m_leptonicmomentum.Theta();
  m_leptonicmomentum_phi = m_leptonicmomentum.Phi();
  m_leptonicmomentum_rho = m_leptonicmomentum.Rho();
  m_leptonicmomentumT = m_leptonicmomentum.Perp();
  m_leptonicmomentumZ = m_leptonicmomentum.Z();

  //Evaluate leptonic W boson - no ISR and 2 solutions
  m_w_lepMass_1 = m_leptonicmomentumC.M() ;
  m_w_lepMass_2 = m_leptonicmomentum_temp.M() ;

  //Fill photon energy vairables
  m_photonenergyA = m_photonmomentumA.E();
  m_photonenergyB = m_photonmomentumB.E();
  m_photonEnergy = m_photonmomentum.E();

  //Fill tau discrimination variable
  m_taudiscr = pow( ( (2*m_isolepmomentum_energy) / _momentumVector.M() ) , 2 ) + pow( ( m_leptonicmomentum_mass / m_w_true ), 2 );
}

//-------------------------------------------------------------------------------------------------//
