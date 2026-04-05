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
// $Id: B2TrackerSD.cc 87359 2014-12-01 16:04:27Z gcosmo $
//
/// \file B2TrackerSD.cc
/// \brief Implementation of the B2TrackerSD class

#include "B2TrackerSD.hh" //j25romol: found in 'TP GEANT4/B2a/B2a/include/B2TrackerSD.hh'
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"
#include "TObject.h"
#include "TH1F.h"
#include "TFile.h"
#include "G4AnalysisManager.hh"
#include "G4RunManager.hh"
#include "B2EventAction.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B2TrackerSD::B2TrackerSD(const G4String& name,
                         const G4String& hitsCollectionName) 
 : G4VSensitiveDetector(name),
   fHitsCollection(NULL)
{
  collectionName.insert(hitsCollectionName);
  // fRoot = new TFile("simulation.root","RECREATE");
  ///  fRoot = TFile::Open("simulation.root","RECREATE");
  // std::unique_ptr<TFile> fRoot(TFile::Open("simulation.root","RECREATE"));
  /// fH1 = new TH1F("fH1"," Deposited energy (MeV) ",100,0.,5.);
  // G4RunManager::GetRunManager()->SetPrintProgress(1);
    // Create analysis manager
  // The choice of the output format is done via the specified
  // file extension.
  auto analysisManager = G4AnalysisManager::Instance();

 // Get analysis manager
  //auto analysisManager = G4AnalysisManager::Instance();

  // Open an output file
  //
  G4String fileName = "simulation.root";
  // Other supported output types:
  // G4String fileName = "B4.csv";
  // G4String fileName = "B4.hdf5";
  // G4String fileName = "B4.xml";
  analysisManager->OpenFile(fileName);
  G4cout << "Using " << analysisManager->GetType() << G4endl;
  
  // Creating histograms
  analysisManager->CreateH1("fH1"," Deposited energy (MeV)", 100, 0., 5.);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B2TrackerSD::~B2TrackerSD() 
{
  // G4cout << "passa qui " <<G4endl;
 //fH1->Write();
 //  std::unique_ptr<TFile> fRoot(TFile::Open("simulation.root","RECREATE"));
  // fRoot->WriteObject(fH1,"fH1");
 //fRoot->TFile::Write();
 //fRoot->TFile::Close();
 ////fRoot->Write();
 //G4cout << "dopo write " <<G4endl;
  /// fRoot->Close();
 //G4cout << "dopo close " <<G4endl;
  auto analysisManager = G4AnalysisManager::Instance();
 // save histograms & ntuple
  //
  analysisManager->Write();
  analysisManager->CloseFile();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B2TrackerSD::Initialize(G4HCofThisEvent* hce)
{
  
  // Get analysis manager
  // auto analysisManager = G4AnalysisManager::Instance();

  // Open an output file
  //
  //G4String fileName = "simulation.root";
  // Other supported output types:
  // G4String fileName = "B4.csv";
  // G4String fileName = "B4.hdf5";
  // G4String fileName = "B4.xml";
  // analysisManager->OpenFile(fileName);
  //G4cout << "Using " << analysisManager->GetType() << G4endl;
  // Create hits collection

  fHitsCollection 
    = new B2TrackerHitsCollection(SensitiveDetectorName, collectionName[0]); 

  // Add this collection in hce

  G4int hcID 
    = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
  hce->AddHitsCollection( hcID, fHitsCollection ); 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4bool B2TrackerSD::ProcessHits(G4Step* aStep,            
                                     G4TouchableHistory*)
{ 
  // energy deposit
  G4double edep = aStep->GetTotalEnergyDeposit();
/*j25romol: prefer the following revisions*/
  /*auto fB2EventAction = const_cast<B2EventAction*>(G4RunManager::GetRunManager()->GetUserEventAction());
  if (EventAction) {
    fB2EventAction->AddEdep(edep);
  }*/
  auto eventAction = const_cast<B2EventAction*>(static_cast<const B2EventAction*>(G4RunManager::GetRunManager()->GetUserEventAction()));

  if (eventAction) {
    eventAction->AddEdep(edep);
  }
/*j25romol: end of advised revisions*/

  if (edep==0.) return false;

  B2TrackerHit* newHit = new B2TrackerHit();

  newHit->SetTrackID  (aStep->GetTrack()->GetTrackID());
  newHit->SetChamberNb(aStep->GetPreStepPoint()->GetTouchableHandle()
                                               ->GetCopyNumber());
  newHit->SetEdep(edep);
  newHit->SetPos (aStep->GetPostStepPoint()->GetPosition());

  fHitsCollection->insert( newHit );

  /*j25romol: additional outputs*/
  //G4cout << "Hit edep: " << edep << G4endl;
  /*j25romol: end of additional outputs*/

  //newHit->Print();

  return true;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B2TrackerSD::EndOfEvent(G4HCofThisEvent*)
{
  G4int nofHits = fHitsCollection->entries();
  if ( verboseLevel>1 ) { 
     G4cout << G4endl
            << "-------->Hits Collection: in this event they are " << nofHits 
            << " hits in the tracker chambers: " << G4endl;
     for ( G4int i=0; i<nofHits; i++ ) (*fHitsCollection)[i]->Print();
  }

  G4double eDepTot = 0;
  for (G4int i=0;i<nofHits;i++) {
    eDepTot += (*fHitsCollection)[i]->GetEdep();
  }
//    printf(" Total deposited energy = %f \n",eDepTot);
  ///  fH1->Fill(eDepTot);
   // get analysis manager
  auto analysisManager = G4AnalysisManager::Instance();

  // fill histograms
  analysisManager->FillH1(0, eDepTot);
  G4cout << "eDepTot" << eDepTot <<G4endl;
  
  // fRoot->Write();
  // fRoot->Close();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
