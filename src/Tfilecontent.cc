#include "MyFirstObservableProcessor.h"


//-------------------------------------------------------------------------------------------------
void MyFirstObservableProcessor::setObservablesBranches( TTree* tree ){
  tree->Branch( "m_com_E",                   &m_com_E,                    "m_com_E/D");
  tree->Branch( "m_omegaiso",                &m_omegaiso,                 "m_omegaiso/D");
  tree->Branch( "m_taudiscr",                &m_taudiscr,                 "m_taudiscr/D");
  tree->Branch( "m_trackultiplicity",        &m_trackmultiplicity,        "m_trackmultiplicity/I");
  tree->Branch( "m_logyplus",                &m_y_plus,                   "m_y_plus/F");
  tree->Branch( "m_logyminus",               &m_y_minus,                  "m_y_minus/F");
  tree->Branch( "m_cosThetaW",               &m_cosThetaW,                "m_cosThetaW/D");

  tree->Branch( "m_recoEnergy",              &m_recomomentum_energy,      "m_recoenergy/D");
  tree->Branch( "m_recoMomentumT",           &m_recomomentumT,            "m_recomomentumT/D");
  tree->Branch( "m_recoMass",                &m_recomomentum_mass,        "m_recomomentum_mass/D");
  tree->Branch( "m_recoMomentumZ",           &m_recomomentumZ,            "m_recomomentumZ/D");

  tree->Branch( "m_recoPhotonEnergyA",       &m_photonenergyA,            "m_photonenergyA/D");
  tree->Branch( "m_recoPhotonEnergyB",       &m_photonenergyB,            "m_photonenergyB/D");
  tree->Branch( "m_recoPhotonEnergyChosen",  &m_photonEnergyChosen,       "m_photonEnergyChosen/D");
  tree->Branch( "m_recoPhotonEnergyChosen2", &m_photonEnergyChosen_temp,  "m_photonEnergyChosen_temp/D");
  tree->Branch( "m_recoPhotonEnergy",        &m_photonEnergy,             "m_photonEnergy/D");
  tree->Branch( "m_lambda",                  &m_lambda,                   "m_lambda/D");

  tree->Branch( "m_isolepFlavour",           &m_isolepflavour,            "m_isolepflavour/I");
  tree->Branch( "m_isolepNumber",            &m_isolepnumber,             "m_isolepnumber/I");
  tree->Branch( "m_isolepEnergy",            &m_isolepmomentum_energy,    "m_isolepenergy/D");
  tree->Branch( "m_isoleptTheta",            &m_isolepmomentum_theta,     "m_isolepmomentum_theta/D");
  tree->Branch( "m_isolepPhi",               &m_isolepmomentum_phi,       "m_isolepmomentum_phi/D");
  tree->Branch( "m_isolepMomentumT",         &m_isolepmomentumT,          "m_isolepmomentumT/D");

  tree->Branch( "m_w_jetMass",               &m_jetmomentum_mass,         "m_jetmass/D");
  tree->Branch( "m_w_jetEnergy",             &m_jetmomentum_energy,       "m_jetenergy/D");
  tree->Branch( "m_w_jetTheta",              &m_jetmomentum_theta,        "m_jetmomentum_theta/D");
  tree->Branch( "m_w_jetPhi",                &m_jetmomentum_phi,          "m_jetmomentum_phi/D");
  tree->Branch( "m_w_jetMomentumT",          &m_jetmomentumT,             "m_jetmomentumT/D");
  tree->Branch( "m_w_jetMomentumZ",          &m_jetmomentumZ,             "m_jetmomentumZ/D");

  tree->Branch( "m_w_lepMass",               &m_leptonicmomentum_mass,    "m_leptonicmass/D");
  tree->Branch( "m_w_lepEnergy",             &m_leptonicmomentum_energy,  "m_leptonicenergy/D");
  tree->Branch( "m_w_lepTheta",              &m_leptonicmomentum_theta,   "m_leptonicmomentum_theta/D");
  tree->Branch( "m_w_lepPhi",                &m_leptonicmomentum_phi,     "m_leptonicmomentum_phi/D");
  tree->Branch( "m_w_lepMomentumT",          &m_leptonicmomentumT,        "m_leptonicmomentumT/D");
  tree->Branch( "m_w_lepMomentumZ",          &m_leptonicmomentumZ,        "m_leptonicmomentumZ/D");
  tree->Branch( "m_w_lepMass_1",             &m_w_lepMass_1,              "m_w_lepMass_1/D");
  tree->Branch( "m_w_lepMass_2",             &m_w_lepMass_2,              "m_w_lepMass_2/D");

  tree->Branch( "m_mcPhotonEnergy",          &m_mcPhotonEnergy,           "m_mcPhotonEnergy/D");
  tree->Branch( "m_mcPhotonTheta",           &m_mcPhotonTheta,            "m_mcPhotonTheta/D");
  tree->Branch( "m_mcParticleEnergy",        &m_mcParticleEnergy,         "m_mcParticleEnergy/D" );
  tree->Branch( "m_mcParticleMomentumT",     &m_mcParticleMomentumT,      "m_mcParticleMomentumT/D" );
  tree->Branch( "m_mcParticleMomentumZ",     &m_mcParticleMomentumZ,      "m_mcParticleMomentumZ/D" );
  tree->Branch( "m_mcLeptonFlavour",         &m_mcLeptonFlavour,          "m_mcLeptonFlavour/D");
  tree->Branch( "m_mcLeptonicEnergy",        &m_mcLeptonicMomentumEnergy, "m_mcLeptonicMomentumEnergy/D");
  tree->Branch( "m_mcLeptonicMomentumT",     &m_mcLeptonicMomentumT,      "m_mcLeptonicMomentumT/D");
  tree->Branch( "m_mcPhotonMass",            &m_mcPhotonMass,             "m_mcPhotonMass/D");

  tree->Branch( "m_extractThetaMinus",       &m_extractThetaMinus,         "m_extractThetaMinus/D");
  tree->Branch( "m_extractRhoLepton",        &m_extractRhoLepton,          "m_extractRhoLepton/D");
  tree->Branch( "m_extractThetaLepton",      &m_extractThetaLepton,        "m_extractThetaLepton/D");
  tree->Branch( "m_extractPhiLepton",        &m_extractPhiLepton,          "m_extractPhiLepton/D");

}
//-------------------------------------------------------------------------------------------------

void MyFirstObservableProcessor::setTTreeBranches() {
  this->setObservablesBranches(m_testtree);
}

//-------------------------------------------------------------------------------------------------
