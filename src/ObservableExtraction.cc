#include "MyFirstObservableProcessor.h"

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------
TLorentzVector MyFirstObservableProcessor::analyseReconstructedVectors(std::string _CollectionName)
{
    LCCollection *_col = NULL;

    try{
        _col = m_event->getCollection(_CollectionName);
    }
    catch (lcio::DataNotAvailableException e)
    {
        streamlog_out(WARNING) << _CollectionName << " collection not available" << std::endl;
        _col = NULL;
    }

    // this will only be entered if the collection is available
    streamlog_out(DEBUG) << "Number of " << _CollectionName << " particles = " << _col->getNumberOfElements() << std::endl;
    TLorentzVector _momentum(0., 0., 0., 0.);
    if (_col != NULL)
    {
        for (int i = 0; i < _col->getNumberOfElements(); i++)
        {
            ReconstructedParticle *particle = dynamic_cast <EVENT::ReconstructedParticle *>(_col->getElementAt(i));
            if (nullptr == particle)
            {
                streamlog_out(ERROR) << "ERROR in analyseReconstructedVectors: Wrong object type in collection '"
                                     << _CollectionName << "'" << std::endl;
                continue;
            }
            _momentum += TLorentzVector(particle->getMomentum(), particle->getEnergy());
        }
    }
    return(_momentum);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------
double MyFirstObservableProcessor::analyseTrackMultiplicity(std::string _CollectionName)
{
    LCCollection *_col = NULL;

    try{
        _col = m_event->getCollection(_CollectionName);
    }
    catch (lcio::DataNotAvailableException e)
    {
        streamlog_out(WARNING) << _CollectionName << " collection not available" << std::endl;
        _col = NULL;
    }

    double _multiplicity = 0;
    // this will only be entered if the collection is available
    if (_col != NULL)
    {
        for (int i = 0; i < _col->getNumberOfElements(); i++)
        {
            ReconstructedParticle *particle = dynamic_cast <EVENT::ReconstructedParticle *>(_col->getElementAt(i));
            if (nullptr == particle)
            {
                streamlog_out(ERROR) << "ERROR in analyseReconstructedMass: Wrong object type in collection '"
                                     << _CollectionName << "'" << std::endl;
                continue;
            }
            if (particle->getCharge() != 0)
            {
                _multiplicity += 1;
            }
        }
    }
    return(_multiplicity);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------
int MyFirstObservableProcessor::analyseleptonFlavour(std::string _CollectionName)
{
    LCCollection *_col = NULL;

    try{
        _col = m_event->getCollection(_CollectionName);
    }
    catch (lcio::DataNotAvailableException e)
    {
        streamlog_out(WARNING) << _CollectionName << " collection not available" << std::endl;
        _col = NULL;
    }

    int _flavour = 0;
    // this will only be entered if the collection is available
    if (_col != NULL)
    {
        for (int i = 0; i < _col->getNumberOfElements(); i++)
        {
            ReconstructedParticle *particle = dynamic_cast <EVENT::ReconstructedParticle *>(_col->getElementAt(i));
            if (nullptr == particle)
            {
                streamlog_out(ERROR) << "ERROR in analyseReconstructedMass: Wrong object type in collection '"
                                     << _CollectionName << "'" << std::endl;
                continue;
            }
            _flavour = particle->getType();
        }
    }
    return(_flavour);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------
void MyFirstObservableProcessor::analyseReconstructed()
{
    m_isolepnumber  = (m_event->getCollection(m_isolatedLeptonsCollectionName))->getNumberOfElements();
    m_isolepflavour = analyseleptonFlavour(m_isolatedLeptonsCollectionName);

    m_isolepmomentum        = analyseReconstructedVectors(m_isolatedLeptonsCollectionName);
    m_isolepmomentum_energy = m_isolepmomentum.Energy();
    m_isolepmomentum_theta  = m_isolepmomentum.Theta();
    m_isolepmomentum_phi    = m_isolepmomentum.Phi();
    m_isolepmomentum_rho    = m_isolepmomentum.Rho();
    m_isolepmomentumT       = m_isolepmomentum.Perp();

    m_jetmomentum        = analyseReconstructedVectors(m_jetsCollectionName);
    m_jetmomentum_mass   = m_jetmomentum.M();
    m_jetmomentum_energy = m_jetmomentum.Energy();
    m_jetmomentum_theta  = m_jetmomentum.Theta();
    m_jetmomentum_phi    = m_jetmomentum.Phi();
    m_jetmomentum_rho    = m_jetmomentum.Rho();
    m_jetmomentumT       = m_jetmomentum.Perp();
    m_jetmomentumZ       = m_jetmomentum.Pz();

    m_recomomentum        = m_jetmomentum + m_isolepmomentum;
    m_recomomentum_mass   = m_recomomentum.M();
    m_recomomentum_energy = m_recomomentum.Energy();
    m_recomomentum_theta  = m_recomomentum.Theta();
    m_recomomentum_phi    = m_recomomentum.Phi();
    m_recomomentum_rho    = m_recomomentum.Rho();
    m_recomomentumT       = m_recomomentum.Perp();
    m_recomomentumZ       = m_recomomentum.Pz();

    // Omega Isolated
    if (m_isolepmomentum_phi - m_jetmomentum_phi < M_PI)
    {
        m_omegaiso = sqrt(pow(m_isolepmomentum_theta - m_jetmomentum_theta, 2) + pow(m_isolepmomentum_phi - m_jetmomentum_phi, 2));
    }
    else
    {
        m_omegaiso = sqrt(pow(m_isolepmomentum_theta - m_jetmomentum_theta, 2) + pow(2 * M_PI - fabs(m_isolepmomentum_phi - m_jetmomentum_phi), 2));
    }

    // Track multiplicity
    m_trackmultiplicity = analyseTrackMultiplicity(m_pfoCollectionName);

    // y_plus and y_minus
    m_y_plus  = logf((m_event->getCollection(m_jetsCollectionName))->getParameters().getFloatVal("y_{n,n+1}"));
    m_y_minus = logf((m_event->getCollection(m_jetsCollectionName))->getParameters().getFloatVal("y_{n-1,n}"));

    // cos Theta_W
    if (m_isolepflavour <= 0)
    {
        m_cosThetaW = cos(m_jetmomentum_theta);
    }
    else
    {
        m_cosThetaW = cos(fmod((m_jetmomentum_theta + M_PI), (2 * M_PI)));
    }
}
