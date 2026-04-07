void fH1_export() {

    TFile *f = new TFile("simulation.root");

    TH1D *fH1 = (TH1D*)f->Get("fH1");

    std::ofstream out("fH1.csv");
    out << "Energy(MeV),Counts\n";

    int nBins = fH1->GetNbinsX();

    for (int i = 1; i <= nBins; i++) {
        double x = fH1->GetBinCenter(i);
        double y = fH1->GetBinContent(i);
/*
        if (y > 0) {  // optional: skip empty bins
            out << x << "," << y << "\n";
        }*/
        out << x << "," << y << "\n";
    }

    out.close();

    std::cout << "CSV file written: fH1.csv" << std::endl;
}
