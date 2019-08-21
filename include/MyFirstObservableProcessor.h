#ifndef MyFirstObservableProcessor_h
#define MyFirstObservableProcessor_h 1

#include "StandardIncludes.h"


class MyFirstObservableProcessor : public Processor {

 public:
   /**
    *  @brief  Factory method to create a processor
    *
    *  This method is called internally by Marlin to create an instance of your processor
    */
   Processor*  newProcessor() { return new MyFirstObservableProcessor ; }

     /**
   *  @brief  Constructor
   *  Regiter your parameters in there. See MtFirstObservableProcessor.cc
   */
   MyFirstObservableProcessor() ;

   // These two lines avoid frequent compiler warnings when using -Weffc++
   MyFirstObservableProcessor( const MyFirstObservableProcessor& ) = delete;
   MyFirstObservableProcessor& operator=( const MyFirstObservableProcessor& ) = delete;

   /**
    *  @brief  Called once at the begin of the job before anything is read.
    *  Use to initialize the processor
    */
   virtual void init() ;

   // Called for every run.
   virtual void processRunHeader( LCRunHeader* run ) ;

   // Called for every event - the working horse.
   virtual void processEvent( LCEvent * evt ) ;

   // Called after data processing for clean up.
   virtual void end() ;

 private:
   // Typedefs for easier readability
   typedef std::set<MCParticle*> MCParticleSet;

   // Additional class memeber functions for analysis.
   void setTTreeBranches();
   void setObservablesBranches( TTree* tree );

   void analyseMCParticles();
   void analyseReconstructed();
   void neutrinoCorrection( TLorentzVector _momentumVector );
   void getMCAngles();

   double getLeptonFlavour();
   double analyseTrackMultiplicity(std::string _CollectionName);
   double getPhotonEnergy(TLorentzVector &_momentumIn, const double &_photonMassIn, const double &_neutrinoMassIn,const std::string &_type,const std::string &_mode);

   int analyseleptonFlavour(std::string _CollectionName);

   TLorentzVector analyseMCPhoton();
   TLorentzVector analyseMCParticle();
   TLorentzVector analyseMCNeutrino();
   TLorentzVector analyseMCHadronic();
   TLorentzVector analyseReconstructedVectors(std::string _CollectionName);
   TLorentzVector analyseMCLeptonic();
   TLorentzVector analyseMCLepton();


   // LCEvent
   LCEvent*              m_event {};

   // Collections
   std::string           m_pfoCollectionName {};
   std::string           m_pfoCollectionName_temp {};
   std::string           m_mcCollectionName {};
   std::string           m_jetsCollectionName {};
   std::string           m_isolatedLeptonsCollectionName {};
   std::string           m_TJJetRecoParticleFinderCollectionName {};
   // Root file
   TFile*                m_rootfile {};
   std::string           m_rootfilename {};
   TTree*                m_testtree {};

   // Mass of W boson (GeV) from PDG Live 30/07/2019
   double                m_w_true = 80.379;
   double                m_w_true_err = 0.012;
   // Extracted scalars (not from TLorentzVector)

   int                   m_trackmultiplicity {};
   int                   m_isolepnumber {};
   int                   m_isolepflavour {};

   float                 m_y_plus {};
   float                 m_y_minus {};

   double                m_com_E {};
   double                m_omegaiso {};
   double                m_taudiscr {};
   double                m_cosThetaW {};
   double                m_photonenergyA {};
   double                m_photonenergyB {};
   double                m_photonEnergyChosen {};
   double                m_photonEnergyChosen_temp {};
   double                m_photonEnergy {};
   double                m_mcLeptonFlavour {};
   double                m_lambda {};

   // Extracted variables (from TLorentzVector)
   TLorentzVector        m_recomomentum {};   // (p_x, p_y, p_z, E)
   double                m_recomomentum_mass {};
   double                m_recomomentum_energy {};
   double                m_recomomentum_theta {};
   double                m_recomomentum_phi {};
   double                m_recomomentum_rho {};
   double                m_recomomentumT  {};

   TLorentzVector        m_isolepmomentum {};
   double                m_isolepmomentum_energy {};
   double                m_isolepmomentum_theta {};
   double                m_isolepmomentum_phi {};
   double                m_isolepmomentum_rho {};
   double                m_isolepmomentumT {};
   double                m_recomomentumZ {};

   TLorentzVector        m_jetmomentum {};
   double                m_jetmomentum_energy {};
   double                m_jetmomentum_mass {};
   double                m_jetmomentum_theta {};
   double                m_jetmomentum_phi {};
   double                m_jetmomentum_rho {};
   double                m_jetmomentumT {};
   double                m_jetmomentumZ {};

   TLorentzVector        m_neutrinomomentumA {};
   TLorentzVector        m_neutrinomomentumB {};
   TLorentzVector        m_neutrinomomentumC {};


   TLorentzVector        m_leptonicmomentum {};
   double                m_leptonicmomentum_mass {};
   double                m_leptonicmomentum_energy {};
   double                m_leptonicmomentum_theta {};
   double                m_leptonicmomentum_phi {};
   double                m_leptonicmomentum_rho {};
   double                m_leptonicmomentumT {};
   double                m_leptonicmomentumZ {};

   TLorentzVector        m_leptonicmomentum_temp {};
   double                m_w_lepMass_1 {};
   double                m_w_lepMass_2 {};

   TLorentzVector        m_leptonicmomentumA {};
   TLorentzVector        m_leptonicmomentumB {};
   TLorentzVector        m_leptonicmomentumC {};

   TLorentzVector        m_mcPhotonMomentum {};
   double                m_mcPhotonEnergy {};
   double                m_mcPhotonTheta {};
   double                m_mcPhotonMass {};

   TLorentzVector        m_mcParticleMomentum {};
   double                m_mcParticleMomentumT {};
   double                m_mcParticleMomentumZ {};
   double                m_mcParticleEnergy {};
   double                m_mcParticleMass {};

   TLorentzVector        m_mcLeptonicMomentum {};
   double                m_mcLeptonicMomentumT {};
   double                m_mcLeptonicMomentumZ {};
   double                m_mcLeptonicMomentumEnergy {};

   TLorentzVector        m_mcHadronicMomentum {};

   TLorentzVector        m_mcNeutrinoMomentum {};
   double                m_mcNeutrinoMass {};

   TLorentzVector        m_mcLeptonMomentum {};

   //DEBUGGING
   int                   num_neg_A = 0;
   int                   num_neg_B = 0;
   int                   num_neg_BOTH = 0;

   // Lorentz boost
  TLorentzVector getBoostVector(TLorentzVector &to_be_boosted, TLorentzVector &_boost_system);

  TLorentzVector m_photonmomentumA {};
  TLorentzVector m_photonmomentumB {};
  TLorentzVector m_photonmomentum {};

  TLorentzVector _boost_system_com {};
  TLorentzVector _boost_system_com_inv {};

  TLorentzVector _boost {};
  TLorentzVector _boostIso {};
  TLorentzVector _boostLepA {};
  TLorentzVector _boostLepB {};
  TLorentzVector _boostLepC {};
  TLorentzVector _boostPhotonA {};
  TLorentzVector _boostPhotonB {};

  double         m_extractThetaMinus {};
  double         m_extractRhoLepton {};
  double         m_extractThetaLepton {};
  double         m_extractPhiLepton {};


  TLorentzVector _boost_system_minus {};
  TLorentzVector _boost_system_leptonic {};
  TLorentzVector _boost_minus {};
  TLorentzVector _boost_lepton {};
 };

#endif
