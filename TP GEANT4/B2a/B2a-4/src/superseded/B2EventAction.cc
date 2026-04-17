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
// $Id: B2EventAction.cc 75214 2013-10-29 16:04:42Z gcosmo $
//
/// \file B2EventAction.cc
/// \brief Implementation of the B2EventAction class

#include "B2EventAction.hh"

#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4TrajectoryContainer.hh"
#include "G4Trajectory.hh"
#include "G4VHitsCollection.hh" //j25romol: temporary troubleshooting header for G4VHitsCollection. CONV2: 🚨 This explains EVERYTHING (2026.04.06)
#include "G4SDManager.hh" //j25romol: temporary troubleshooting header for G4SDManager. CONV2: 🚨 This explains EVERYTHING (2026.04.06)
#include "G4ios.hh"

/*j25romol: temporary troubleshooting headers*/
//#include "g4analysis.hh" // requires rebuilding local GEANT4 with analysis support. CONV2: 🚨 This explains EVERYTHING (2026.04.06)
#include <fstream>
#include "B2TrackerHit.hh"

/*j25romol: end of temporary troubleshooting headers*/

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B2EventAction::B2EventAction()
: G4UserEventAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B2EventAction::~B2EventAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B2EventAction::BeginOfEventAction(const G4Event*)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
/*j25romol: temporary troubleshooting supression
void B2EventAction::EndOfEventAction(const G4Event* event)
{
  // get number of stored trajectories

  G4TrajectoryContainer* trajectoryContainer = event->GetTrajectoryContainer();
  G4int n_trajectories = 0;
  if (trajectoryContainer) n_trajectories = trajectoryContainer->entries();

  // periodic printing

  G4int eventID = event->GetEventID();

  if ( eventID < 100 || eventID % 100 == 0) {
    G4cout << ">>> Event: " << eventID  << G4endl;
    if ( trajectoryContainer ) {
      G4cout << "    " << n_trajectories
             << " trajectories stored in this event." << G4endl;
    }
    G4VHitsCollection* hc = event->GetHCofThisEvent()->GetHC(0);
    G4cout << "    "  
           << hc->GetSize() << " hits stored in this event" << G4endl;
  }
}  
*/
/*j25romol: temporary troubleshooting asset*/
void B2EventAction::EndOfEventAction(const G4Event* event)
{
  G4int eventID = event->GetEventID();

  // --- Retrieve hits container ---
  G4HCofThisEvent* hce = event->GetHCofThisEvent();
  if (!hce) {
    G4cout << "[EventAction] No HCofThisEvent!" << G4endl;
    return;
  }

  // --- Get collection ID safely ---
  static G4int hcID = -1;
  if (hcID == -1) {
    hcID = G4SDManager::GetSDMpointer()
             ->GetCollectionID("TrackerHitsCollection");

    G4cout << "[DEBUG] Retrieved hcID = " << hcID << G4endl;
  }

  // --- Retrieve hits collection using hcID ---
  auto hitsCollection =
    static_cast<B2TrackerHitsCollection*>(hce->GetHC(hcID));

  if (!hitsCollection) {
    G4cout << "[EventAction] Hits collection is NULL!" << G4endl;
    return;
  }

  // --- Compute total deposited energy ---
  G4double eDepTot = 0.;

  for (size_t i = 0; i < hitsCollection->GetSize(); i++) {
    auto hit = (*hitsCollection)[i];
    G4double edep = hit->GetEdep();

    G4cout << "[EventAction] Hit " << i
           << " Edep = " << edep / CLHEP::keV << " keV"
           << G4endl;

    eDepTot += edep;
  }

  // --- Debug summary ---
  G4cout << "\n>>> Event: " << eventID << G4endl;
  G4cout << "    Hits stored: " << hitsCollection->GetSize() << G4endl;
  G4cout << "    DEBUG eDepTot = "
         << eDepTot / CLHEP::keV << " keV" << G4endl;

  /*
         // --- Fill histogram ---
  auto analysisManager = G4AnalysisManager::Instance();

  G4cout << "    Filling histogram with: "
         << eDepTot / CLHEP::keV << " keV" << G4endl;

  analysisManager->FillH1(0, eDepTot);
  */
  /*
  std::ofstream out("edep.txt", std::ios::app);
  out << eDepTot / CLHEP::keV << std::endl;
  //out << "Event " << eventID << ": " << eDepTot / CLHEP::keV << " keV" << std::endl;
  out.close();
  */
  /*
  std::ofstream out("edep_hits.csv", std::ios::app);
  out << "eventID, hits, eDepTot" << std::endl;
  out << eventID << "," << hitsCollection->GetSize() << "," << eDepTot/CLHEP::keV << std::endl;
  out.close();
  */
  std::ofstream out("edep_hits.csv", std::ios::app);
  out << eventID << "," << hitsCollection->GetSize()
      << "," << eDepTot / CLHEP::keV << std::endl;
  out.close();
}
/*j25romol: end of temporary troubleshooting asset*/
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
