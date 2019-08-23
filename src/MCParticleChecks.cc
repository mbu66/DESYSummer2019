#include "MyFirstObservableProcessor.h"

TLorentzVector MyFirstObservableProcessor::analyseMCPhoton()
{
    LCCollection *_col = NULL;

    try{
        _col = m_event->getCollection(m_mcCollectionName);
    }
    catch (lcio::DataNotAvailableException e)
    {
        streamlog_out(WARNING) << m_mcCollectionName << " collection not available" << std::endl;
        _col = NULL;
    }

    // this will only be entered if the collection is available
    TLorentzVector _momentum {};
    if (_col != NULL)
    {
        MCParticle *particle1 = dynamic_cast <EVENT::MCParticle *>(_col->getElementAt(4));
        if (nullptr == particle1)
        {
            streamlog_out(ERROR) << "ERROR in analyseMCPhoton: Wrong object type in collection '"
                                 << m_mcCollectionName << "'" << std::endl;
        }
        _momentum += TLorentzVector(particle1->getMomentum(), particle1->getEnergy());

        MCParticle *particle2 = dynamic_cast <EVENT::MCParticle *>(_col->getElementAt(5));
        if (nullptr == particle2)
        {
            streamlog_out(ERROR) << "ERROR in analyseMCPhoton: Wrong object type in collection '"
                                 << m_mcCollectionName << "'" << std::endl;
        }
        _momentum += TLorentzVector(particle2->getMomentum(), particle2->getEnergy());
        if (particle1->getPDG() != 22 || particle1->getPDG() != 22)
        {
            streamlog_out(WARNING) << "ERROR in analyseMCPhoton: Not ISR Photons" << std::endl;
        }
    }
    return(_momentum);
}

TLorentzVector MyFirstObservableProcessor::analyseMCNeutrino()
{
    LCCollection *_col = NULL;

    try{
        _col = m_event->getCollection(m_mcCollectionName);
    }
    catch (lcio::DataNotAvailableException e)
    {
        streamlog_out(WARNING) << m_mcCollectionName << " collection not available" << std::endl;
        _col = NULL;
    }
    // this will only be entered if the collection is availables
    TLorentzVector _momentum {};
    if (_col != NULL)
    {
        // Neutrino
        MCParticle *particle = dynamic_cast <EVENT::MCParticle *>(_col->getElementAt(9));
        if (nullptr == particle)
        {
            streamlog_out(ERROR) << "ERROR in analyseMCParticle: Wrong object type in collection '"
                                 << m_mcCollectionName << "'" << std::endl;
        }
        _momentum = TLorentzVector(particle->getMomentum(), particle->getEnergy());
    }
    return(_momentum);
}

TLorentzVector MyFirstObservableProcessor::analyseMCHadronic()
{
    LCCollection *_col = NULL;

    try{
        _col = m_event->getCollection(m_mcCollectionName);
    }
    catch (lcio::DataNotAvailableException e)
    {
        streamlog_out(WARNING) << m_mcCollectionName << " collection not available" << std::endl;
        _col = NULL;
    }

    // this will only be entered if the collection is available
    TLorentzVector _momentum {};
    if (_col != NULL)
    {
        // Quarks
        MCParticle *particle1 = dynamic_cast <EVENT::MCParticle *>(_col->getElementAt(6));
        if (nullptr == particle1)
        {
            streamlog_out(ERROR) << "ERROR in analyseMCParticle: Wrong object type in collection '"
                                 << m_mcCollectionName << "'" << std::endl;
        }
        _momentum += TLorentzVector(particle1->getMomentum(), particle1->getEnergy());

        MCParticle *particle2 = dynamic_cast <EVENT::MCParticle *>(_col->getElementAt(7));
        if (nullptr == particle2)
        {
            streamlog_out(ERROR) << "ERROR in analyseMCParticle: Wrong object type in collection '"
                                 << m_mcCollectionName << "'" << std::endl;
        }
        _momentum += TLorentzVector(particle2->getMomentum(), particle2->getEnergy());
    }
    return(_momentum);
}

TLorentzVector MyFirstObservableProcessor::analyseMCLeptonic()
{
    LCCollection *_col = NULL;

    try{
        _col = m_event->getCollection(m_mcCollectionName);
    }
    catch (lcio::DataNotAvailableException e)
    {
        streamlog_out(WARNING) << m_mcCollectionName << " collection not available" << std::endl;
        _col = NULL;
    }

    // this will only be entered if the collection is availables
    TLorentzVector _momentum {};
    if (_col != NULL)
    {
        // Neutrino
        MCParticle *particle = dynamic_cast <EVENT::MCParticle *>(_col->getElementAt(9));
        if (nullptr == particle)
        {
            streamlog_out(ERROR) << "ERROR in analyseMCParticle: Wrong object type in collection '"
                                 << m_mcCollectionName << "'" << std::endl;
        }
        _momentum += TLorentzVector(particle->getMomentum(), particle->getEnergy());

        // Lepton
        MCParticle *particle1 = dynamic_cast <EVENT::MCParticle *>(_col->getElementAt(8));
        if (nullptr == particle1)
        {
            streamlog_out(ERROR) << "ERROR in analyseMCParticle: Wrong object type in collection '"
                                 << m_mcCollectionName << "'" << std::endl;
        }
        _momentum += TLorentzVector(particle1->getMomentum(), particle1->getEnergy());
    }
    return(_momentum);
}

TLorentzVector MyFirstObservableProcessor::analyseMCLepton()
{
    LCCollection *_col = NULL;

    try{
        _col = m_event->getCollection(m_mcCollectionName);
    }
    catch (lcio::DataNotAvailableException e)
    {
        streamlog_out(WARNING) << m_mcCollectionName << " collection not available" << std::endl;
        _col = NULL;
    }

    // this will only be entered if the collection is availables
    TLorentzVector _momentum {};
    if (_col != NULL)
    {
        // Lepton
        MCParticle *particle1 = dynamic_cast <EVENT::MCParticle *>(_col->getElementAt(8));
        if (nullptr == particle1)
        {
            streamlog_out(ERROR) << "ERROR in analyseMCParticle: Wrong object type in collection '"
                                 << m_mcCollectionName << "'" << std::endl;
        }
        _momentum = TLorentzVector(particle1->getMomentum(), particle1->getEnergy());
    }
    return(_momentum);
}

double MyFirstObservableProcessor::getLeptonFlavour()
{
    LCCollection *_col = NULL;

    try{
        _col = m_event->getCollection(m_mcCollectionName);
    }
    catch (lcio::DataNotAvailableException e)
    {
        streamlog_out(WARNING) << m_mcCollectionName << " collection not available" << std::endl;
        _col = NULL;
    }

    // this will only be entered if the collection is available
    float _leptonFlavour {};
    if (_col != NULL)
    {
        // Lepton
        MCParticle *particle = dynamic_cast <EVENT::MCParticle *>(_col->getElementAt(8));
        if (nullptr == particle)
        {
            streamlog_out(ERROR) << "ERROR in analyseMCParticle: Wrong object type in collection '"
                                 << m_mcCollectionName << "'" << std::endl;
        }
        _leptonFlavour = particle->getPDG();
    }
    return(_leptonFlavour);
}

void MyFirstObservableProcessor::analyseMCParticles()
{
    m_mcPhotonMomentum = analyseMCPhoton();
    m_mcPhotonEnergy   = m_mcPhotonMomentum.Energy();
    m_mcPhotonTheta    = m_mcPhotonMomentum.Theta();
    m_mcPhotonMass     = m_mcPhotonMomentum.M();

    m_mcLeptonicMomentum       = analyseMCLeptonic();
    m_mcLeptonicMomentumT      = m_mcLeptonicMomentum.Perp();
    m_mcLeptonicMomentumEnergy = m_mcLeptonicMomentum.Energy();


    m_mcHadronicMomentum = analyseMCHadronic();

    m_mcParticleMomentum  = m_mcLeptonicMomentum + m_mcHadronicMomentum;
    m_mcParticleMomentumT = m_mcParticleMomentum.Perp();
    m_mcParticleMomentumZ = m_mcParticleMomentum.Pz();

    m_mcParticleEnergy = m_mcParticleMomentum.Energy();
    m_mcParticleMass   = m_mcParticleMomentum.M();

    m_mcLeptonFlavour = getLeptonFlavour();

    m_mcNeutrinoMomentum = analyseMCNeutrino();
    m_mcNeutrinoMass     = m_mcNeutrinoMomentum.M();

    m_mcLeptonMomentum = analyseMCLepton();
}
