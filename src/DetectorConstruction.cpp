#include "DetectorConstruction.h"
#include "SensitiveDetector.h"
#include "G4Tubs.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include <G4SDManager.hh>
#include "G4VisAttributes.hh"
#include <G4SubtractionSolid.hh>
#include <G4UnionSolid.hh>
#include <G4PhysicalVolumeStore.hh>
#include "G4PhysicalConstants.hh"
#include "myglobals.h"

DetectorConstruction::DetectorConstruction()
	: G4VUserDetectorConstruction() {
}

G4VPhysicalVolume* DetectorConstruction::Construct() {
	defineMaterials();

	G4Material* air = G4Material::GetMaterial("G4_AIR");

	G4Box* worldBox = new G4Box("World", 1.5 * m, 1.5 * m, 1.5 * m);

	G4LogicalVolume* worldLog
		= new G4LogicalVolume(
			worldBox,
			air,
			"world");

	G4VPhysicalVolume* worldPhys
		= new G4PVPlacement(
			nullptr,
			G4ThreeVector(),
			worldLog,
			"world",
			nullptr,
			false,
			0);

// 	G4double density = 3.54*g/cm3;
// 	G4double atomicMass = 140.28*g/mole;
// 	G4int nElements = 2;
// 	G4Element* elSi = new G4Element("Silicon", "Si", 14., 28.09*g/mole);
// 	G4Element* elN = new G4Element("Nitrogen", "N", 7., 14.01*g/mole);
// 	G4Material* MySi3N4 = new G4Material("Si3N4", density, nElements);
// 	MySi3N4->AddElement(elSi, 3);
// 	MySi3N4->AddElement(elN, 4);
	// Define the cylinder dimensions
	G4bool checkOverlaps = true;
	G4double target_radius = 3.3*cm; // diameter = 5cm, so radius = 2.5cm
	G4double target_length = 20.0*mm;
	G4double z;
	G4double density;
	G4double a;
// 	auto nistManagerr = G4NistManager::Instance();
	G4NistManager* nist = G4NistManager::Instance();
// 	nistManagerr->FindOrBuildMaterial("G4_Ge");

// 	nistManagerr->FindOrBuildMaterial("G4_N");
// 	nistManagerr->FindOrBuildMaterial("G4_Si");
	G4Material* MySi = nist->FindOrBuildMaterial("G4_B");
// 	G4Material* MyN = nist->FindOrBuildMaterial("G4_N");
// 	new G4Material("HPGE", z = 32., a = 72.64 * g / mole, density = 5.323 * g / cm3, kStateSolid, 77.0 * kelvin, 1 * atmosphere);
// 	new G4Material("G4_N",  z = 7,  a = 14.003  * g / mole, density = 0.807 * g / cm3, kStateLiquid,  77.0 * kelvin, 1 * atmosphere);
// 	new G4Material("G4_Si", z = 14, a = 28.0855 * g / mole, density = 2.330 * g / cm3, kStateSolid,  293.0 * kelvin, 1 * atmosphere);
	// Define the cylinder shape
	G4Tubs* solidCylinder = new G4Tubs("CylinderLogical", 0, target_radius, target_length/2.0, 0, 2*M_PI);
	// Define the logical volume for the cylinder
 	G4LogicalVolume* logicalCylinder_Si = new G4LogicalVolume(solidCylinder, MySi , "CylinderLogical_Si");
//  	G4LogicalVolume* logicalCylinder_N  = new G4LogicalVolume(solidCylinder, MyN, "CylinderLogical_N");


	// Place the cylinder at the origin
  	G4VPhysicalVolume* physicalCylinder_Si = new G4PVPlacement(0, G4ThreeVector(0, 0, 0), logicalCylinder_Si, "CylinderLogical_Si", worldLog, false, 0, checkOverlaps);
// 	G4VPhysicalVolume* physicalCylinder_N  = new G4PVPlacement(0, G4ThreeVector(-2.5 *cm, 0, 0), logicalCylinder_N,  "CylinderLogical_N",  worldLog, false, 1, checkOverlaps);
//  	G4VisAttributes* visAttributes_N = new G4VisAttributes(G4Colour(1.0, 0.0, 0.0)); // red
// 	logicalCylinder_N->SetVisAttributes(visAttributes_N);
// 	visAttributes_N->SetVisibility(true);
// 	visAttributes_N->SetForceSolid(true);
//     logicalCylinder_N->SetVisAttributes(visAttributes_N);

// 	G4VPhysicalVolume* physicalCylinder_Si = new G4PVPlacement(0, G4ThreeVector(1,0,0), logicalCylinder_Si, "CylinderPhysical", worldLog, false, 0);
//  	G4VisAttributes* visAttributes_Si = new G4VisAttributes(G4Colour(0.0, 1.0, 0.0)); // blue
// 	logicalCylinder_Si->SetVisAttributes(visAttributes_Si);
// 	visAttributes_Si->SetVisibility(true);
// 	visAttributes_Si->SetForceSolid(true);
//     logicalCylinder_Si->SetVisAttributes(visAttributes_Si);



	/*
	For each of detector:
	- Translate in z-direction by detector-distance.
	- Rotate by theta and phi around z-axis
	- place physical volume
	*/
	for (auto& det : MYGLOBALS::DET_SPECS) {
        //G4cout << det.number << "  " << "G E E E E T" << G4endl;
		G4LogicalVolume* detectorLog = buildDetector(det);
		G4double detectorHalfLength = dynamic_cast<G4Tubs*>(detectorLog->GetSolid())->GetZHalfLength();

		G4Transform3D translation(G4RotationMatrix(), {0, 0, det.distance + detectorHalfLength });
		G4Transform3D rotation(G4RotationMatrix(0, det.theta, det.phi), G4ThreeVector());
		G4Transform3D transform = rotation * translation;

		new G4PVPlacement(transform, "Det" + std::to_string(det.number), detectorLog, worldPhys, false, det.number);
	}

	return worldPhys;
}

void DetectorConstruction::ConstructSDandField()
{
	auto sensitiveDetector = new SensitiveDetector("GAINSSD");
	G4SDManager::GetSDMpointer()->AddNewDetector(sensitiveDetector);

	for (auto& det : MYGLOBALS::DET_SPECS)
		SetSensitiveDetector("crystal" + std::to_string(det.number), sensitiveDetector);
}

void DetectorConstruction::defineMaterials()
{
	auto nistManager = G4NistManager::Instance();
	G4String name, symbol;
	G4int ncomponents, natoms,nel;
	nistManager->FindOrBuildMaterial("G4_Ge");
	nistManager->FindOrBuildMaterial("G4_AIR");
	nistManager->FindOrBuildMaterial("G4_Al");
    nistManager->FindOrBuildMaterial("G4_CESIUM_IODIDE");
    nistManager->FindOrBuildMaterial("G4_SODIUM_IODIDE");
	nistManager->FindOrBuildMaterial("G4_N");
	nistManager->FindOrBuildMaterial("G4_Si");
	G4Element *  Si = new G4Element ("Silicon","Si",14., 28.0855*g/mole);
	G4Element*   N  = new G4Element ("Nitrogen", "N", 7., 14.01*g/mole);
	G4double z;
	G4double density;
	G4double a;
	new G4Material("Vacuum", z = 1., a = 1.01 * g / mole, density = universe_mean_density,
		kStateGas, 2.73 * kelvin, 3.e-18 * pascal);

	new G4Material("Carbon-epoxy", z = 6., a = 12. * g / mole, density = 2 * g / cm3);

	new G4Material("HPGE", z = 32., a = 72.64 * g / mole, density = 5.323 * g / cm3,
		kStateSolid, 77.0 * kelvin, 1 * atmosphere);

// 	new G4Material("Silicon-Nitride", z = 2., a = 140.283 * g / mole, density = 3.44 * g / cm3,
// 		kStateSolid, 293.0 * kelvin, 1 * atmosphere);

//	 G4Material* Si3N4 = new G4Material(name = "Si3N4", 3.44 *g / cm3, nel = 2);
//	 Si3N4->AddElement (Si, natoms=3);
//	 Si3N4->AddElement (N, natoms=4);
}

G4LogicalVolume* DetectorConstruction::buildDetector(const Specs& det)
{
	auto boxMat = G4Material::GetMaterial("Vacuum");
	//auto crystalMat = G4Material::GetMaterial("HPGE");
    G4cout << det.number << "   " << G4endl;

    auto crystalMat = G4Material::GetMaterial(det.number < 13 ? "HPGE" : "G4_SODIUM_IODIDE");
	crystalMat = G4Material::GetMaterial(det.number > 12 ? "G4_SODIUM_IODIDE" : "HPGE");
    G4cout << crystalMat << G4endl;
	auto windowMat = G4Material::GetMaterial(det.number == 9 ? "G4_Al" : "Carbon-epoxy");
	auto capMat = G4Material::GetMaterial("G4_Al");
    //G4cout << (1 ? 1 : 0) << G4endl;
    //G4cout << (1 ? 0 : 0) << G4endl;
    int xx = 4;
    int yy = 4;
    // G4cout << (xx == yy ? "sameeeeeeee" : "not sameeeeeeeee");
    for (int j = 1; j < 25; j ++) {
        //G4cout << " \n \n \n \n \n \n \n \n " << j << G4endl;
        //G4cout << G4Material::GetMaterial(det.number) << G4endl;
        //G4cout << " ------------------------------------ " << G4endl;
    }
	G4double distanceToCap = det.distanceToCap;
	G4double windowThickness = det.windowThickness;
	G4double capThickness = det.capThickness;
	G4double crystalRadius = .5 * det.crystalDiameter;
	G4double crystalLength = det.crystalLength;
	G4double holeRadius = .5 * det.holeDiameter;
	G4double holeDepth = det.holeDepth;

	G4double fullRadius = det.fullRadius();
	G4double fullHalfLength = det.fullHalfLength();
	G4double capHalfLength = 2 * fullHalfLength;

	//Create a box large enough to include crystal, cap and window
	G4Tubs* detectorSolid =
		new G4Tubs("HPGeDetector",
			0,
			fullRadius,
			fullHalfLength,
			0,
			360 * deg);

	G4LogicalVolume* detectorLog =
		new G4LogicalVolume(detectorSolid,
			boxMat,
			"HPGeDetector");
//     G4VisAttributes* red = new G4VisAttributes(G4Colour::Red());
//     red->SetVisibility(true);
//     red->SetForceSolid(true);
//     detectorLog->SetVisAttributes(red);
	detectorLog->SetVisAttributes(G4VisAttributes::GetInvisible());

	/*
	* ===========================================
	* ===========================================
	*/

	/*
	* ===========================================
	* Crystal
	* ===========================================
	*/
	//Create the crystal without the hole
	G4Tubs* crystalSolidWithoutHole =
		new G4Tubs("crystalWithoutHole",
			0,
			crystalRadius,
			crystalLength * .5,
			0,
			360 * deg);

	/*
	Create a cylinder, to be subtracted from the crystal
	Cylinder is made slightly longer to prevent surface overlap
	*/
	G4double extra = 1 * mm;
	G4Tubs* holeSolid =
		new G4Tubs("hole",
			0,
			holeRadius,
			holeDepth * .5 + extra,
			0,
			360 * deg);

	//Subtract the cylinder from the crystal
	G4SubtractionSolid* crystalSolid =
		new G4SubtractionSolid("crystal",
			crystalSolidWithoutHole,
			holeSolid,
			nullptr,
			G4ThreeVector(0, 0, (crystalLength - holeDepth) * .5 + extra));

	G4LogicalVolume* crystalLogic =
		new G4LogicalVolume(crystalSolid,
			crystalMat,
			"crystal" + std::to_string(det.number));

	new G4PVPlacement(0,
		G4ThreeVector(0, 0, fullHalfLength - .5 * crystalLength),
		crystalLogic,
		"crystal",
		detectorLog,
		false,
		0);

	/*
	* ===========================================
	* Window
	* ===========================================
	*/
	G4Tubs* windowSolid =
		new G4Tubs("window",
			0,
			crystalRadius,
			windowThickness,
			0,
			360 * deg);

	G4LogicalVolume* windowLogic =
		new G4LogicalVolume(windowSolid,
			windowMat,
			"window");

	new G4PVPlacement(0,
		G4ThreeVector(0, 0, .5 * windowThickness - fullHalfLength),
		windowLogic,
		"window",
		detectorLog,
		false,
		0);

	/*
	* ===========================================
	* End cap
	* ===========================================
	*/
	G4Tubs* capOuterSolid =
		new G4Tubs("outercap",
			fullRadius - capThickness,
			fullRadius,
			capHalfLength,
			0,
			360 * deg);
	G4Tubs* capInnerSolid =
		new G4Tubs("innercap",
			crystalRadius,
			crystalRadius + distanceToCap,
			.5 * capThickness,
			0,
			360 * deg);
	G4UnionSolid* capSolid =
		new G4UnionSolid("cap",
			capOuterSolid,
			capInnerSolid,
			nullptr,
			G4ThreeVector(0, 0, .5 * capThickness - capHalfLength));


	G4LogicalVolume* capLogic =
		new G4LogicalVolume(capSolid,
			capMat,
			"cap");

	new G4PVPlacement(0,
		G4ThreeVector(0, 0, capHalfLength - fullHalfLength),
		capLogic,
		"cap",
		detectorLog,
		false,
		0);
	return detectorLog;
}
