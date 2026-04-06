// csv2root.C
#include <fstream>
#include <sstream>
#include <string>
#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TCanvas.h"

void csv2root() {
    // Open output ROOT file
    TFile *file = TFile::Open("simulation.root", "RECREATE");

    // Create TTree
    TTree *tree = new TTree("Hits", "Energy deposition per event");

    // Variables
    int eventID, hits;
    double eDepTot_keV;

    // Branches
    tree->Branch("eventID", &eventID, "eventID/I");
    tree->Branch("hits", &hits, "hits/I");
    tree->Branch("eDepTot_keV", &eDepTot_keV, "eDepTot_keV/D");

    // Open CSV
    std::ifstream in("edep_hits.csv");
    if (!in.is_open()) {
        std::cerr << "ERROR: Cannot open edep_hits.csv" << std::endl;
        return;
    }

    std::string line;
    std::getline(in, line); // Skip header

    // Fill TTree
    while (std::getline(in, line)) {
        if (line.empty()) continue;
        std::stringstream ss(line);
        std::string item;
        if (!std::getline(ss, item, ',')) continue;
        eventID = std::stoi(item);
        if (!std::getline(ss, item, ',')) continue;
        hits = std::stoi(item);
        if (!std::getline(ss, item, ',')) continue;
        eDepTot_keV = std::stod(item);
        tree->Fill();
    }
    in.close();

    // Write TTree
    tree->Write();

    // Create histograms
    TH1D *hHits = new TH1D("hHits", "Number of Hits;Hits;Events", 100, 0, 2000);
    TH1D *hEDep = new TH1D("hEDep", "Total Deposited Energy;E_dep [keV];Events", 100, 0, 3e6);

    // Fill histograms from tree
    for (Long64_t i = 0; i < tree->GetEntries(); ++i) {
        tree->GetEntry(i);
        hHits->Fill(hits);
        hEDep->Fill(eDepTot_keV);
    }

    // Write histograms
    hHits->Write();
    hEDep->Write();

    // Optional: save canvases (if you have GUI, otherwise skip)
    TCanvas *c1 = new TCanvas("c1", "Hits Histogram", 800, 600);
    hHits->Draw();
    c1->SaveAs("hits_hist.png");

    TCanvas *c2 = new TCanvas("c2", "Deposited Energy Histogram", 800, 600);
    hEDep->Draw();
    c2->SaveAs("edep_hist.png");

    file->Close();

    std::cout << "ROOT file simulation.root created successfully!" << std::endl;
}