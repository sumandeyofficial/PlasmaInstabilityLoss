#include "crpropa/module/PlasmaInstabilityLoss.h"

PlasmaInstabilityLoss::PlasmaInstabilityLoss(double del, double nIGM, double nBeam) : crpropa::Module() {
        setPlasmaNormEnergyDensity(del);
        setIGMDensity(nIGM);
        setBeamDensity(nBeam);
        setDescription("PlasmaInstabilityLoss");
}

void PlasmaInstabilityLoss::setPlasmaNormEnergyDensity(double delta) {
        EnergyDensityNorm = delta;
}

void PlasmaInstabilityLoss::setIGMDensity(double DensIGM) {
        IGMEnergyDens = DensIGM;
}

void PlasmaInstabilityLoss::setBeamDensity(double DensBeam) {
        BeamEnergyDens = DensBeam;
}

double PlasmaInstabilityLoss::getPlasmaNormEnergyDensity() const {
        return EnergyDensityNorm;
}

double PlasmaInstabilityLoss::getIGMDensity() const {
        return IGMEnergyDens;
}

double PlasmaInstabilityLoss::getBeamDensity() const {
        return BeamEnergyDens;
}

void PlasmaInstabilityLoss::process(crpropa::Candidate *candidate) const {
        int id = candidate->current.getId();

        // only works for electrons and positrons
        if (fabs(id) != 11)
                return;

        double dx = candidate->getCurrentStep();
        double z = candidate->getRedshift();
        double E = candidate->current.getEnergy();
        double dEdx = coolingPower(E, z);

        if (dEdx < 0)
                dEdx = 0;
        double Enew = E - dEdx * dx;
        candidate->current.setEnergy(Enew);
        candidate->limitNextStep(0.1 * E / dEdx);
}

double PlasmaInstabilityLoss::coolingPower(double E, double z) const {
        double dEdx = 0;
        E /= (1 + z);
        const double lightspeed_inv = 3.33556e-9; // sec/meter
        const double electroncharge = 4.803204e-10; // statC
        const double m_e = 9.10938e-28; // in grams

        return lightspeed_inv * 2 * EnergyDensityNorm * (1.211e-10) * pow(((4 * std::numbers::pi * pow(electroncharge, 2))/(m_e)), 0.5) * pow((IGMEnergyDens / 1e-7), -0.5) * (BeamEnergyDens / 1e-20) * E;
} // nIGM and nBeam values are in cm^-3 and the loss-time calculation is based on the Eqs. (11) and (14) of Alawashra and Pohl 2022 ApJ 929 67 

std::string PlasmaInstabilityLoss::getDescription() const {
        std::stringstream s;
        s << "PlasmaInstabilityLoss";
        s << "IGM Density: " << getIGMDensity() << " in cm^-3\n";
        s << "Beam Density: " << getBeamDensity() << " in cm^-3\n";
        s << "Normalized wave energy density at the equilibrium level (delta = U_ES / U_beam): " << getPlasmaNormEnergyDensity() << " \n";

        return s.str();
}
