#include "MyFirstObservableProcessor.h"

void MyFirstObservableProcessor::getMCAngles(){

  TLorentzVector _WmomentumMinus {};
  if(m_mcLeptonFlavour < 0){
      _WmomentumMinus = m_mcHadronicMomentum;
  }
  else if(m_mcLeptonFlavour > 0){
      _WmomentumMinus = m_mcLeptonicMomentum;
  }
  else{
    streamlog_out(WARNING) << "no lepton" << std::endl;
  }

   _boost_system_minus = TLorentzVector(500.0*sin(0.014 / 2.0), 0, 0, 500.0);

   _boost_minus = getBoostVector(_WmomentumMinus, _boost_system_minus);
   m_extractThetaMinus =_boost_minus.Theta();

   _boost_system_leptonic = m_mcLeptonicMomentum;

   _boost_lepton = getBoostVector(m_mcLeptonMomentum, _boost_system_leptonic);
   m_extractRhoLepton =_boost_lepton.Rho();
   m_extractThetaLepton =_boost_lepton.Theta();
   m_extractPhiLepton =_boost_lepton.Phi();

}
