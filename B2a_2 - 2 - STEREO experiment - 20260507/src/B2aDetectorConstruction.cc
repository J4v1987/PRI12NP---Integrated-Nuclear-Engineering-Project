//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
// $Id: B2aDetectorConstruction.cc 101658 2016-11-21 09:00:41Z gcosmo $
//
/// \file B2aDetectorConstruction.cc
/// \brief Implementation of the B2aDetectorConstruction class
 
#include "B2aDetectorConstruction.hh"
#include "B2aDetectorMessenger.hh"
#include "B2TrackerSD.hh"

#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4SDManager.hh"

#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4GlobalMagFieldMessenger.hh"
#include "G4AutoDelete.hh"

#include "G4GeometryTolerance.hh"
#include "G4GeometryManager.hh"

#include "G4UserLimits.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
G4ThreadLocal 
G4GlobalMagFieldMessenger* B2aDetectorConstruction::fMagFieldMessenger = 0;

B2aDetectorConstruction::B2aDetectorConstruction()
:G4VUserDetectorConstruction(), 
 fNbOfChambers(0),
 fLogicTarget(NULL), fLogicChamber(NULL), 
 fTargetMaterial(NULL), fTrackerMaterial(NULL), 
 fStepLimit(NULL),
 fCheckOverlaps(true)
{
  fMessenger = new B2aDetectorMessenger(this);

  fNbOfChambers = 1;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
B2aDetectorConstruction::~B2aDetectorConstruction()
{
  delete [] fLogicChamber; 
  delete fStepLimit;
  delete fMessenger;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
G4VPhysicalVolume* B2aDetectorConstruction::Construct()
{
  // Define materials
  DefineMaterials();

  // Define volumes
  return DefineVolumes();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B2aDetectorConstruction::DefineMaterials()
{
  // Material definition 
  G4double a, z;
  G4double density, temperature, pressure;
  G4int nel;

  G4NistManager* nistManager = G4NistManager::Instance();

  // Air defined using NIST Manager
  nistManager->FindOrBuildMaterial("G4_AIR");
  nistManager->FindOrBuildMaterial("G4_POLYETHYLENE");
  // Lead defined using NIST Manager
  fTargetMaterial  = nistManager->FindOrBuildMaterial("G4_Pb");

  // Xenon gas defined using NIST Manager
  // G4NistManager* nistManager = G4NistManager::Instance();
  // G4Material* trackerMaterial = nistManager->FindOrBuildMaterial("G4_Xe");
  // Xenon liquid

  // Liquid xenon defined using class G4Material
  //fTrackerMaterial =
  //new G4Material("XenonLiquid", z=54., a=131.29*g/mole, density= 3.06*g/cm3,
    //             kStateLiquid, temperature= 293.15*kelvin, pressure= 1*atmosphere);
 G4Element* H = new G4Element("Hydrogen",   "H", z=1 , a=1.00*g/mole);
 G4Element* C = new G4Element("Carbon",     "C", z=6 , a=12.00*g/mole);
 G4Element* Gd = new G4Element("Gadolinium","Gd",z=56, a=157.00*g/mole);
  fTrackerMaterial =
  //new G4Material("XenonLiquid", z=54., a=131.29*g/mole, density= 3.06*g/cm3,
  new G4Material("GadoliniumLiquid", 0.88*g/cm3,3);
  fTrackerMaterial-> AddElement(H,  11.45*perCent);
   fTrackerMaterial-> AddElement(C, 88.35*perCent);
   fTrackerMaterial-> AddElement(Gd, 0.2*perCent);
  //Here you have to redefine the tracker material to have the liquid scintillator (composition in mass percentage : H 11,45%, Gd 0,2 %, C 88,35 %, density 0,88 g/cm3)
//refer to the GEANT4 slides to see how to define a material composed by different elements

  // Print materials
  G4cout << *(G4Material::GetMaterialTable()) << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* B2aDetectorConstruction::DefineVolumes()
{
  
  
  G4Material* air  = G4Material::GetMaterial("G4_AIR");
  G4Material* Lead  = G4Material::GetMaterial("G4_Pb");
  G4Material* POLYETHELENE  = G4Material::GetMaterial("G4_POLYETHYLENE");

  // Sizes of the principal geometrical components (solids)
  
  G4double worldLength = 4*m;

  G4double targetLength = 1.0*cm; // full length of Target (1 cm)
  G4double targetRadius  = 20*cm;   // Radius of Target

  G4double trackerLength = 20*cm;
  G4double trackerRadius = 20*cm;

  // Definitions of Solids, Logical Volumes, Physical Volumes

  // World

  G4GeometryManager::GetInstance()->SetWorldMaximumExtent(worldLength);

  G4cout << "Computed tolerance = "
         << G4GeometryTolerance::GetInstance()->GetSurfaceTolerance()/mm
         << " mm" << G4endl;

  G4Box* worldS
    = new G4Box("world",                                    //its name
		worldLength/2,worldLength/2,worldLength/2); //its size
  G4LogicalVolume* worldLV  = new G4LogicalVolume(
						  worldS,   //its solid
						  air,      //its material
						  "World"); //its name
  
  //  Must place the World Physical volume unrotated at (0,0,0).
  // 
  G4VPhysicalVolume* worldPV
    = new G4PVPlacement(
                 0,               // no rotation
                 G4ThreeVector(), // at (0,0,0)
                 worldLV,         // its logical volume
                 "World",         // its name
                 0,               // its mother  volume
                 false,           // no boolean operations
                 0,               // copy number
                 fCheckOverlaps); // checking overlaps 
 //
     G4Box* Poly = new G4Box("poly",((200*mm)+2220*mm/2),(200*mm+889*mm/2),(200*mm+918*mm/2));
 G4LogicalVolume* polyLV
    = new G4LogicalVolume(Poly, POLYETHELENE ,"Poly",0,0,0);

    new G4PVPlacement(0,               // no rotation
                  G4ThreeVector(0,0,0),  // at (x,y,z)
                   polyLV,    // its logical volume
                 "poly",        // its name
                  worldLV,         // its mother volume
                 false,           // no boolean operations
                 0,               // copy number
                fCheckOverlaps); // checking overlaps
    
  // You can put here your shielding
  
  G4ThreeVector positionTarget = G4ThreeVector(0,0,0);

  //G4Tubs* targetS
  //  = new G4Tubs("target",0.,targetRadius,targetLength/2.,0.*deg,360.*deg);
   G4Box* targetS = new G4Box("target",((100*mm)+2220*mm/2),(100*mm+889*mm/2),(100*mm+918*mm/2));
  fLogicTarget
    = new G4LogicalVolume(targetS, fTargetMaterial,"Target",0,0,0);

    new G4PVPlacement(0,               // no rotation
                  positionTarget,  // at (x,y,z)
                   fLogicTarget,    // its logical volume
                 "Target",        // its name
                  polyLV,         // its mother volume
                 false,           // no boolean operations
                 0,               // copy number
                fCheckOverlaps); // checking overlaps

  G4cout << "Target is " << targetLength/cm << " cm of "
         << fTargetMaterial->GetName() << G4endl;

  // this is you target in Nucifer
 
  G4ThreeVector positionTracker = G4ThreeVector(0,0,0);

 // G4Tubs* trackerS
   // = new G4Tubs("tracker",0,trackerRadius,trackerLength/2., 0.*deg, 360.*deg);
    G4Box* trackerS = new G4Box("tracker",2220*mm/2,889*mm/2,918*mm/2);
  G4LogicalVolume* trackerLV
    = new G4LogicalVolume(trackerS, fTrackerMaterial, "Tracker",0,0,0);  
  new G4PVPlacement(0,               // no rotation
                   positionTracker, // at (x,y,z)
                    trackerLV,       // its logical volume
                    "Tracker",       // its name
                    fLogicTarget,    // its mother  volume
                    false,           // no boolean operations
                    0,               // copy number
                    fCheckOverlaps); // checking overlaps

  // Visualization attributes

  G4VisAttributes* boxVisAtt= new G4VisAttributes(G4Colour(1.0,1.0,1.0));

  worldLV      ->SetVisAttributes(boxVisAtt);
  fLogicTarget ->SetVisAttributes(boxVisAtt);
  trackerLV    ->SetVisAttributes(boxVisAtt);

  // Tracker segments

  G4cout << "There are " << fNbOfChambers << " chambers in the tracker region. "
         << G4endl
         << G4endl;
  

  // Example of User Limits
  //
  // Below is an example of how to set tracking constraints in a given
  // logical volume
  //
  // Sets a max step length in the tracker region, with G4StepLimiter

  G4double maxStep = 0.5*cm;
  fStepLimit = new G4UserLimits(maxStep);
  trackerLV->SetUserLimits(fStepLimit);
 
  /// Set additional contraints on the track, with G4UserSpecialCuts
  ///
  /// G4double maxLength = 2*trackerLength, maxTime = 0.1*ns, minEkin = 10*MeV;
  /// trackerLV->SetUserLimits(new G4UserLimits(maxStep,
  ///                                           maxLength,
  ///                                           maxTime,
  ///                                           minEkin));

  // Always return the physical world

  return worldPV;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
void B2aDetectorConstruction::ConstructSDandField()
{
  // Sensitive detectors

  G4String trackerChamberSDname = "B2/TrackerChamberSD";
  B2TrackerSD* aTrackerSD = new B2TrackerSD(trackerChamberSDname,
                                            "TrackerHitsCollection");
  G4SDManager::GetSDMpointer()->AddNewDetector(aTrackerSD);
  // Setting aTrackerSD to all logical volumes with the same name 
  // of "Tracker".
  SetSensitiveDetector("Tracker", aTrackerSD, true);

  // Create global magnetic field messenger.
  // Uniform magnetic field is then created automatically if
  // the field value is not zero.
  G4ThreeVector fieldValue = G4ThreeVector();
  fMagFieldMessenger = new G4GlobalMagFieldMessenger(fieldValue);
  fMagFieldMessenger->SetVerboseLevel(1);
  
  // Register the field messenger for deleting
  G4AutoDelete::Register(fMagFieldMessenger);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
void B2aDetectorConstruction::SetTargetMaterial(G4String materialName)
{
  G4NistManager* nistManager = G4NistManager::Instance();

  G4Material* pttoMaterial = 
              nistManager->FindOrBuildMaterial(materialName);

  if (fTargetMaterial != pttoMaterial) {
     if ( pttoMaterial ) {
        fTargetMaterial = pttoMaterial;
        if (fLogicTarget) fLogicTarget->SetMaterial(fTargetMaterial);
        G4cout 
          << G4endl 
          << "----> The target is made of " << materialName << G4endl;
     } else {
        G4cout 
          << G4endl 
          << "-->  WARNING from SetTargetMaterial : "
          << materialName << " not found" << G4endl;
     }
  }
}
 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B2aDetectorConstruction::SetMaxStep(G4double maxStep)
{
  if ((fStepLimit)&&(maxStep>0.)) fStepLimit->SetMaxAllowedStep(maxStep);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B2aDetectorConstruction::SetCheckOverlaps(G4bool checkOverlaps)
{
  fCheckOverlaps = checkOverlaps;
}  
