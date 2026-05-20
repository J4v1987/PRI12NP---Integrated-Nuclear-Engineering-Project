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
// $Id: B2PrimaryGeneratorAction.cc 97979 2016-06-30 09:36:20Z gcosmo $
//
/// \file B2PrimaryGeneratorAction.cc
/// \brief Implementation of the B2PrimaryGeneratorAction class

#include "B2PrimaryGeneratorAction.hh"

#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"

#include "Randomize.hh"
#include <iostream>
#include <fstream>
using namespace std;
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B2PrimaryGeneratorAction::B2PrimaryGeneratorAction()
 : G4VUserPrimaryGeneratorAction()
{
  G4int nofParticles = 1;
  fParticleGun = new G4ParticleGun(nofParticles);

  // default particle kinematic

  G4ParticleDefinition* particleDefinition
    = G4ParticleTable::GetParticleTable()->FindParticle("gamma");

  fParticleGun->SetParticleDefinition(particleDefinition);
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(1.,0.,0.));
  //fParticleGun->SetParticleEnergy(3.0*GeV);



  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B2PrimaryGeneratorAction::~B2PrimaryGeneratorAction()
{
  delete fParticleGun;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B2PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  // This function is called at the begining of event
  
  // In order to avoid dependence of PrimaryGeneratorAction
  // on DetectorConstruction class we get world volume
  // from G4LogicalVolumeStore.
//  G4int particle=1;
 G4double ene=0.;
  //gamma generator
//if(particle==1) {
  G4double E[37],I[37];
  ifstream myfile("gamma_file_effi.dat");
G4int j=1;
 G4double rand;
 G4double iratio=0;
 G4double iratiom1=0;
 G4double Itot=0;
if (myfile.is_open())
  {
//G4cout<<"test"<<G4endl;
    while (!myfile.eof())
    {
      myfile >> E[j] >> I[j];
      //G4cout<<E[j]<<" "<<I[j]<<"j "<<j<<G4endl;
      j=j+1;
   }
    myfile.close();
  }
  else G4cout << "Unable to open file";
 for(int m=1;m<37;m++)Itot=Itot+I[m];
 rand=G4UniformRand();
 //cout<<"rand "<<rand<<endl;

for(int n=1;n<37;n++)
  { 
    if(n==1)
      {
	if(rand<=I[n]/Itot)ene=E[n]*keV;
	iratio=I[n]/Itot;
      }
    else
      {
	iratio=iratio+I[n]/Itot;
	iratiom1=iratiom1+I[n-1]/Itot;   //doubt
	//cout<<"iratio "<<iratio<<endl;
	//	cout<<"iratiom1 "<<iratiom1<<endl;
	if(rand<=iratio && rand>iratiom1)ene=E[n]*keV;  //doubt
      }
  }
 // }
//neutron generator
// if(particle==2) { 
 // }
  G4double y= 60*cm * G4UniformRand();
  G4double z=-60*cm * G4UniformRand();


  G4double randY =y * (G4UniformRand()-0.5);
  G4double randZ =z * (G4UniformRand()-0.5);


//G4cout<<ene<<G4endl;
  //G4double position = 0.*cm;
  fParticleGun->SetParticlePosition(G4ThreeVector(-150.*cm,randY,randZ));
  fParticleGun->SetParticleEnergy(ene);
  fParticleGun->GeneratePrimaryVertex(anEvent);
 /* G4double worldZHalfLength = 0;
  G4LogicalVolume* worldLV
    = G4LogicalVolumeStore::GetInstance()->GetVolume("World");
  G4Box* worldBox = NULL;
  if ( worldLV ) worldBox = dynamic_cast<G4Box*>(worldLV->GetSolid());
  if ( worldBox ) worldZHalfLength = worldBox->GetZHalfLength();
  else  {
    G4cerr << "World volume of box not found." << G4endl;
    G4cerr << "Perhaps you have changed geometry." << G4endl;
    G4cerr << "The gun will be place in the center." << G4endl;
  }

  fParticleGun->SetParticlePosition(G4ThreeVector(0., 0., -worldZHalfLength));
 
  fParticleGun->GeneratePrimaryVertex(anEvent);
*/
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
