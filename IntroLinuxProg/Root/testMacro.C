void testMacro()
{

  // on crée un hitogramme de 100 canaux pour des valeurs comprises entre -5 et 5
  // la classe root s'appelle TH1F
  // le "new" permet de faire une allocation dynamique de mémoire  

 TH1F *h1 = new TH1F("h1"," histogram ",100,-5,5);
 TH1F *h2 = new TH1F("h2"," histogram ",100,0,1000);
  

 // on genere 1000000 nombres aléatoires x distribués suivant une loi uniforme entre -2 et 2 en utilisant le générateur de nombres pseudoaleatoires gRandom (classe TRandom de ROOT)
 // et on remplit l'histogramme h1

  for (int i = 0; i < 1000000; i++) {
    float x = gRandom->Exp(100);
    //float x = gRandom->Uniform(-2,2);
    h2->Fill(x);
  }

  // on dessine l'histogramme

  h2->Draw();
  
  // ADD THIS LINE:
  gPad->SaveAs("alpha_results.pdf");
  //gPad->Print("alpha_results.pdf");

  printf("Simulation complete. Histogram saved to 20260401-j25romol-alpha_results.pdf\n");
  printf("C++ script compiled by:\n");
  printf("Javier Alonzo ROMO LEON.\n");
  printf("M.Sc. NE-PIA Candidate: j25romol.\n");
  printf("As of: 1 april 2026.");

}
