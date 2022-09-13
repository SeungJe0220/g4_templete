#include "G4ParticleGun.hh"

#include "PrimaryGeneratorAction.hh"
#include "G4Gamma.hh"
#include "G4SystemOfUnits.hh"
#include "G4Geantino.hh"
#include "G4RandomTools.hh"


PrimaryGeneratorAction::PrimaryGeneratorAction()
    : G4VUserPrimaryGeneratorAction()
{
    fPrimary = new G4ParticleGun();
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  delete fPrimary;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event *anEvent)
{
  double randomNumber {0};
  double y = 0.;
  double z = 0.;
  double ySquare = 0.;
  double zSquare = 0.;

  y = sin(CLHEP::twopi * G4UniformRand());
  z = cos(CLHEP::twopi * G4UniformRand());
  if ((y*y + z*z) < 1)
  {
    fPrimary->SetParticlePosition(G4ThreeVector(0, y * 75 * cm, z * 75 * cm));
  }


  fPrimary->SetParticleDefinition(G4Gamma::Definition());
  fPrimary->SetParticleMomentumDirection(G4ThreeVector(1,0,0));
  fPrimary->SetParticleEnergy(0.662 * MeV);


  fPrimary->GeneratePrimaryVertex(anEvent);
}
