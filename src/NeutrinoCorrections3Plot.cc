#include "MyFirstObservableProcessor.h"

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------
TLorentzVector MyFirstObservableProcessor::getBoostVector(TLorentzVector &to_be_boosted, TLorentzVector &_boost_system){
    TLorentzVector _boost_vector = to_be_boosted;
    TVector3 _boost_beta_vector = -1.0*_boost_system.BoostVector();
    _boost_vector.Boost(_boost_beta_vector);
    return _boost_vector;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------
double MyFirstObservableProcessor::getPhotonEnergy(TLorentzVector &_momentumIn, const double &_photonMassIn, const double &_neutrinoMassIn, const std::string &_type, const std::string &_mode){
    m_lambda = 0.5 * ( pow( 500.0 -  _momentumIn.E() , 2) -  pow( _momentumIn.P() , 2) +  pow( _photonMassIn , 2) -  pow( _neutrinoMassIn , 2) );

    double _numeratorA = m_lambda*( 500.0 - _momentumIn.E() ) + _momentumIn.Pz()*sqrt( pow( m_lambda, 2) - pow( _photonMassIn , 2)*( pow( 500.0 - _momentumIn.E(), 2) -  pow( _momentumIn.Pz(), 2) ) );
    double _numeratorB = m_lambda*( 500.0 - _momentumIn.E() ) - _momentumIn.Pz()*sqrt( pow( m_lambda, 2) - pow( _photonMassIn , 2)*( pow( 500.0 - _momentumIn.E(), 2) -  pow( _momentumIn.Pz(), 2) ) );
    double _denominator =  pow( 500.0 - _momentumIn.E(), 2) - pow( _momentumIn.Pz(), 2);

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
        _energyOut = _numeratorB / _denominator;
    }
    else if(_mode == "full" && _type == "B" && m_lambda >= 0){
        _energyOut = _numeratorB / _denominator;
    }
    else if(_mode == "full" && _type == "B" && m_lambda < 0){
        _energyOut = _numeratorA / _denominator;
    }
    else{
        streamlog_out(WARNING) << "getPhotonEnergy has wrong inputs" << std::endl;
    }
    return _energyOut;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------
void MyFirstObservableProcessor::neutrinoCorrection( TLorentzVector _momentumVector ){
   // Boost into CoM frame
   _boost_system_com = TLorentzVector(500.0*sin(0.014 / 2.0), 0, 0, 500.0);
   _boost_system_com_inv = TLorentzVector(-500.0*sin(0.014 / 2.0), 0, 0, 500.0);

   _boost = getBoostVector(_momentumVector, _boost_system_com);
   _boostIso = getBoostVector(m_isolepmomentum, _boost_system_com);

   /** Non-boosted solution
   _boost = _momentumVector;
   _boostIso = m_isolepmomentum;
   **/

   //-------------------------------------------------------------------------------------------------------------------------------------------------------------------

   // Photon momentum parallel
   _boostPhotonA.SetE( getPhotonEnergy(_boost, 0.0, 0.0, "A", "full") );
   _boostPhotonA.SetPx(0.0);
   _boostPhotonA.SetPy(0.0);
   _boostPhotonA.SetPz(-1.0*_boostPhotonA.E());

   m_neutrinomomentumA.SetPx( -1*_boost.Px() );
   m_neutrinomomentumA.SetPy( -1*_boost.Py() );
   m_neutrinomomentumA.SetPz( -1*( _boost.Pz() + _boostPhotonA.Pz() ) );
   m_neutrinomomentumA.SetE( 500.0 - _boostPhotonA.E() - _boost.E() );

   _boostLepA =  m_neutrinomomentumA + _boostIso;

   //-------------------------------------------------------------------------------------------------------------------------------------------------------------------

   // Photon momentum anit-parallel
   _boostPhotonB.SetE( getPhotonEnergy(_boost, 0.0, 0.0, "B", "full") );
   _boostPhotonB.SetPx(0.0);
   _boostPhotonB.SetPy(0.0);
   _boostPhotonB.SetPz(_boostPhotonB.E());

   m_neutrinomomentumB.SetPx( -1*_boost.Px() );
   m_neutrinomomentumB.SetPy( -1*_boost.Py() );
   m_neutrinomomentumB.SetPz( -1*( _boost.Pz() + _boostPhotonB.Pz() ) );
   m_neutrinomomentumB.SetE( 500.0 - _boostPhotonB.E() - _boost.E() );

   _boostLepB =  m_neutrinomomentumB + _boostIso;

   //-------------------------------------------------------------------------------------------------------------------------------------------------------------------

   // No ISR photon
   m_neutrinomomentumC.SetPx( -1*_boost.Px() );
   m_neutrinomomentumC.SetPy( -1*_boost.Py() );
   m_neutrinomomentumC.SetPz( -1*_boost.Pz() );
   m_neutrinomomentumC.SetE( fabs( _boost.P() ) );

   _boostLepC =  m_neutrinomomentumC + _boostIso;

   //-------------------------------------------------------------------------------------------------------------------------------------------------------------------
   // Count negative energy solutions
   if( abs(m_isolepflavour) == 13 && m_isolepnumber == 1){
       if(  _boostPhotonA.E() < -0.1){
         // streamlog_out(ERROR) << "photonenergyA  < 0" << std::endl;
         num_neg_A += 1;
       }
       if( _boostPhotonB.E() < -0.1){
         // streamlog_out(ERROR) << "photonenergyB  < 0" << std::endl;
         num_neg_B += 1;
       }
       if(  _boostPhotonA.E() < -0.1 && _boostPhotonB.E() < -0.1){
         num_neg_BOTH += 1;
       }
     }

   //-------------------------------------------------------------------------------------------------------------------------------------------------------------------
   // Boost into Lab frame
   m_leptonicmomentumA = getBoostVector(_boostLepA, _boost_system_com_inv);
   m_leptonicmomentumB = getBoostVector(_boostLepB, _boost_system_com_inv);
   m_leptonicmomentumC = getBoostVector(_boostLepC, _boost_system_com_inv);

   m_photonmomentumA = getBoostVector(_boostPhotonA, _boost_system_com_inv);
   m_photonmomentumB = getBoostVector(_boostPhotonB, _boost_system_com_inv);

   /** Non-boosted solution
   m_leptonicmomentumA = _boostLepA;
   m_leptonicmomentumB = _boostLepB;
   m_leptonicmomentumC = _boostLepC;

   m_photonmomentumA = _boostPhotonA;
   m_photonmomentumB = _boostPhotonB;
   **/

   //-------------------------------------------------------------------------------------------------------------------------------------------------------------------
   // Choose scheme with better W_mass estimate
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

   // Choose scheme with better W_mass estimate without 3rd option
   if( fabs( m_leptonicmomentumA.M() - m_w_true) < fabs( m_leptonicmomentumB.M() - m_w_true )){
         m_leptonicmomentum_temp = m_leptonicmomentumA;
         m_photonEnergyChosen_temp = 1;
   }
   else{
        m_leptonicmomentum_temp = m_leptonicmomentumB;
        m_photonEnergyChosen_temp = 2;
   }

   //-------------------------------------------------------------------------------------------------------------------------------------------------------------------
   // Fill variables
   m_leptonicmomentum_mass = m_leptonicmomentum.M();
   m_leptonicmomentum_energy = m_leptonicmomentum.Energy();
   m_leptonicmomentum_theta = m_leptonicmomentum.Theta();
   m_leptonicmomentum_phi = m_leptonicmomentum.Phi();
   m_leptonicmomentum_rho = m_leptonicmomentum.Rho();
   m_leptonicmomentumT = m_leptonicmomentum.Perp();
   m_leptonicmomentumZ = m_leptonicmomentum.Z();

   m_w_lepMass_1 = m_leptonicmomentumC.M() ;
   m_w_lepMass_2 = m_leptonicmomentum_temp.M() ;

   m_photonenergyA = m_photonmomentumA.E();
   m_photonenergyB = m_photonmomentumB.E();
   m_photonEnergy = m_photonmomentum.E();

   //-------------------------------------------------------------------------------------------------------------------------------------------------------------------
   // Tau discrimination
   m_taudiscr = pow( ( (2*m_isolepmomentum_energy) / _momentumVector.M() ) , 2 ) + pow( ( m_leptonicmomentum_mass / m_w_true ), 2 );

}
