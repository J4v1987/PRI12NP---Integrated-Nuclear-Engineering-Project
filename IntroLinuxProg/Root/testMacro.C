void testMacro()
{

  // on crée un histogramme de 100 canaux pour des valeurs comprises entre -5 et 5
  // la classe root s'appelle TH1F
  // le "new" permet de faire une allocation dynamique de m�moire  

 //TH1F *h1 = new TH1F("h1"," histogram ",100,-5,5);    //j25romol: superseded in the context of the "Random number generator, ROOT. Laboratory: 'Initiation to Linux'"
 //TH1F *h2 = new TH1F("h2"," histogram ",100,0,1000);  //j25romol: superseded in the context of the "Random number generator, ROOT. Laboratory: 'Initiation to Linux'"
 TH1F *h3 = new TH1F("h3"," histogram ",100,-0.5,0.5);  //j25romol: assumed 100 bins are acceptable in the context of the "Random number generator, ROOT. Laboratory: 'Initiation to Linux'

 // on genere 1000000 nombres aléatoires x distribués suivant une loi uniforme entre -0.5 et 0.5 en utilisant le générateur de nombres pseudoaleatoires gRandom (classe TRandom de ROOT)
 // et on remplit l'histogramme h3

  for (int i = 0; i < 1000000; i++) {
    float x = gRandom->Exp(100);
    //float x = gRandom->Uniform(-2,2);
    //h2->Fill(x);  //j25romol: superseded in the context of the "Random number generator, ROOT. Laboratory: 'Initiation to Linux'"
    h3->Fill(x);    //j25romol: filling of histogram 'h3' with 100 bins for random values in the range of [-0.5,0.5] for 1E6 random samples weighted to e^(-x/100), in the context of the "Random number generator, ROOT. Laboratory: 'Initiation to Linux'
  }

  // on dessine l'histogramme

  //h2->Draw();
  h3->Draw();
  
  // ADD THIS LINE:
  gPad->SaveAs("j25romol-alpha_results.pdf");
  //gPad->Print("alpha_results.pdf");

  printf("Simulation complete. Histogram saved to j25romol-alpha_results.pdf\n");
  printf("C++ script compiled by:\n");
  printf("Javier Alonzo ROMO LEON.\n");
  printf("M.Sc. NE-PIA Candidate: j25romol.\n");
}
