#include "G4SystemOfUnits.hh"
#include "G4NistManager.hh"

#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"

#include "G4Tubs.hh"
#include "G4Box.hh"

#include "G4PVReplica.hh"
#include "G4VisAttributes.hh"

#include "DetectorConstruction.hh"

#include "G4SDManager.hh"
#include "G4MultiFunctionalDetector.hh"
#include "G4PSDoseDeposit.hh"

DetectorConstruction::DetectorConstruction()
    : G4VUserDetectorConstruction()
{
}

DetectorConstruction::~DetectorConstruction()
{
}

G4VPhysicalVolume *DetectorConstruction::Construct()
{
  // materials
  G4NistManager *nist = G4NistManager::Instance();
  auto matAir = nist->FindOrBuildMaterial("G4_AIR");
  auto matWater = nist->FindOrBuildMaterial("G4_WATER");

  // World
  auto worldSize = 15. * m;
  G4Box *worldSol = new G4Box("World", .5 * worldSize, .5 * worldSize, .5 * worldSize);
  G4LogicalVolume *worldLog = new G4LogicalVolume(worldSol, matAir, "World"); // auto == G4LogicalVolume *worldLog
  G4PVPlacement *worldPhy = new G4PVPlacement(0, G4ThreeVector(), worldLog, "World", nullptr, false, 0); // auto == G4PVPlacement *worldphy

  // auto phantomSol = new G4Box("phantom", .5 * 30 *cm, .5 * 30 *cm, .5 * 50 *cm);
  // auto phnatomLog = new G4LogicalVolume(phantomSol, matWater, "phantom");
  // new G4PVPlacement(0, G4ThreeVector(515*cm, 0, 0), phnatomLog, "phantom", worldLog, false, 0);

  //G4PVReplica Example
  G4Tubs *phantomSol = new G4Tubs("phantom", 20* cm, 50. * cm, 30. * cm, 0., 360. * deg);
  G4LogicalVolume *phantomLog = new G4LogicalVolume(phantomSol, matWater, "phantom");
  new G4PVPlacement(0, G4ThreeVector(515*cm, 0, 0), phantomLog, "phantom", worldLog, false, 0);

  G4double divDegree = 360*degree/6 ;
  G4VSolid* tubeDivSol = new G4Tubs("divPhantom", 20* cm, 50. * cm, 30. * cm, 0., divDegree);
  G4LogicalVolume *phantomDivLog = new G4LogicalVolume(tubeDivSol, matWater, "divphantom");
  new G4PVReplica("divPhantom", phantomDivLog, phantomLog, kPhi, 5, divDegree);

  G4VisAttributes *va_divPhantom = new G4VisAttributes(G4Colour(1.0, 0.0, 1.0));
  va_divPhantom->SetForceSolid(true);
  phantomDivLog->SetVisAttributes(va_divPhantom);

  return worldPhy;
}

void DetectorConstruction::ConstructSDandField()
{
  // auto mfd = new G4MultiFunctionalDetector("Detector"); // The mfd is assigned pointer by auto variable
  // G4SDManager::GetSDMpointer()->AddNewDetector(mfd);
  // auto psDoseDep = new G4PSDoseDeposit("DoseDep");
  // mfd->RegisterPrimitive(psDoseDep); // public declaration variable can use, in this case utilize '->' operator 
  // SetSensitiveDetector("phantom", mfd);

}
