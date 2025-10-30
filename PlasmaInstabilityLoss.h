#ifndef CRPROPA_PLASMAINSTABILITYLOSS_H
#define CRPROPA_PLASMAINSTABILITYLOSS_H

#include <crpropa/Cosmology.h>
#include <crpropa/Module.h>
#include <crpropa/ParticleID.h>
#include <crpropa/ParticleMass.h>
#include <crpropa/Random.h>
#include <crpropa/Units.h>

class PlasmaInstabilityLoss : public crpropa::Module {
        protected:
                double EnergyDensityNorm;
                double IGMEnergyDens;
                double BeamEnergyDens;

        public:
                PlasmaInstabilityLoss(double EnergyDensityNorm, double IGMEnergyDens, double BeamEnergyDens);
                void setPlasmaNormEnergyDensity(double deltaplasma);
                void setIGMDensity(double IGMEnergyDensplasma);
                void setBeamDensity(double BeamEnergyDensplasma);
                double getPlasmaNormEnergyDensity() const;
                double getIGMDensity() const;
                double getBeamDensity() const;
                double coolingPower(double energy, double redshift) const;
                std::string getDescription() const;
                void process(crpropa::Candidate *candidate) const;
};

#endif
