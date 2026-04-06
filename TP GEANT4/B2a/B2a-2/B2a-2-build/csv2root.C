// csv2root.C
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TROOT.h"
#include "TImage.h"

void csv2root() {
    // Enable batch mode (no GUI required)
    gROOT->SetBatch(kTRUE); // j25romol: ensures canvases can be saved without GUI

    // Open output ROOT file
    TFile *file = TFile::Open("simulation.root", "RECREATE");

    // Create TTree
    TTree *tree = new TTree("Hits", "Energy deposition per event");

    int eventID, hits;
    double eDepTot_keV;

    tree->Branch("eventID", &eventID, "eventID/I");
    tree->Branch("hits", &hits, "hits/I");
    tree->Branch("eDepTot_keV", &eDepTot_keV, "eDepTot_keV/D");

    std::ifstream in("edep_hits.csv");
    if (!in.is_open()) {
        std::cerr << "ERROR: Cannot open edep_hits.csv" << std::endl;
        return;
    }

    std::string line;
    std::getline(in, line); // skip header

    double eDepMax = 0.0;

    // Fill TTree and track max
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

        if (eDepTot_keV > eDepMax) eDepMax = eDepTot_keV;
    }
    in.close();

    tree->Write();

    int nbinsHits = static_cast<int>(std::sqrt(tree->GetEntries()));
    int nbinsEDep = static_cast<int>(std::sqrt(tree->GetEntries()));

    TH1D *hHits = new TH1D("hHits", "Number of Hits;Hits;Events",
                           nbinsHits, 0, 2000);
    TH1D *hEDep = new TH1D("hEDep", "Total Deposited Energy;E_dep [keV];Events",
                           nbinsEDep, 0, eDepMax*1.05);// j25romol: last three variable or numeric arguments mean respectively number of bins based on sqrt(data points), minimum energy value (starts at 0), maximum energy value with 5% margin. See: https://root.cern/doc/v636/classTH1D.html

    // Fill histograms from TTree
    for (Long64_t i = 0; i < tree->GetEntries(); ++i) {
        tree->GetEntry(i);
        hHits->Fill(hits);
        hEDep->Fill(eDepTot_keV);
    }

    hHits->Write();
    hEDep->Write();

    // Save histograms as PNG safely using off-screen rendering
    TCanvas c1("c1", "Hits Histogram", 800, 600);
    hHits->Draw(); // Draw into canvas
    c1.Update();
    c1.SaveAs("hits_hist.pdf"); // Works in batch mode

    TCanvas c2("c2", "Deposited Energy Histogram", 800, 600);
    hEDep->Draw(); // Draw into canvas
    c2.Update();
    c2.SaveAs("edep_hist.pdf"); // Works in batch mode

    file->Close();

    std::cout << "ROOT file simulation.root created successfully!" << std::endl;
}