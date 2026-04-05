void Edep_export() {

    TFile *f = new TFile("simulation.root");

    TH1D *Edep = (TH1D*)f->Get("Edep");

    std::ofstream out("Edep.csv");
    out << "Energy(MeV),Counts\n";

    int nBins = Edep->GetNbinsX();

    for (int i = 1; i <= nBins; i++) {
        double x = Edep->GetBinCenter(i);
        double y = Edep->GetBinContent(i);
/*
        if (y > 0) {  // optional: skip empty bins
            out << x << "," << y << "\n";
        }*/
    }

    out.close();

    std::cout << "CSV file written: Edep.csv" << std::endl;
}
