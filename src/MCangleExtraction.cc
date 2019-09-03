#include "MyFirstObservableProcessor.h"

//-------------------------------------------------------------------------------------------------//

void MyFirstObservableProcessor::getMCAngles(){
  /**
  Extracts angles from MC particles
  Extracts W_minus theta coordinate from the center of mass frame
  Extracts W_lepton theta and phi coordinate from W_lepton center of mass frame
  **/

  //Choose which W boson is negatively charged
  TLorentzVector _WmomentumMinus {};
  if(m_mcLeptonFlavour < 0){
    _WmomentumMinus = m_mcHadronicWMomentum;
  }
  else if(m_mcLeptonFlavour > 0){
    _WmomentumMinus = m_mcLeptonicWMomentum;
  }
  else{
    streamlog_out(WARNING) << "no lepton" << std::endl;
  }

  //Boost into CoM frame
  _boost_system_minus = TLorentzVector(500.0*sin(0.014 / 2.0), 0, 0, 500.0);
  _boost_minus = getBoostVector(_WmomentumMinus, _boost_system_minus);

  //Get theta coordinate
  m_extractThetaMinus =_boost_minus.Theta();

  //Boost into W_lepton CoM frame
  _boost_system_leptonic = m_mcLeptonicWMomentum;
  _boost_lepton = getBoostVector(m_mcLeptonMomentum, _boost_system_leptonic);

  //Get theta and phi coordinate
  m_extractThetaLepton =_boost_lepton.Theta();
  m_extractPhiLepton =_boost_lepton.Phi();

}

//-------------------------------------------------------------------------------------------------//
