void testMacro()
{

  // on crée un hitogramme de 100 canaux pour des valeurs comprises entre -5 et 5
  // la classe root s'appelle TH1F
  // le "new" permet de faire une allocation dynamique de mémoire  

 TH1F *h1 = new TH1F("h1"," histogram ",100,-5,5);
 TH1F *h2 = new TH1F("h1"," histogram ",100,0,1000);
  

 // on genere 10000 nombres aléatoires x distribués suivant une loi uniforme entre -2 et 2 en utilisant le générateur de nombres pseudoaleatoires gRandom (classe TRandom de ROOT)
 // et on remplit l'histogramme h1

  for (int i = 0; i < 10000; i++) {
    float x = gRandom->Exp(100);
    //float x = gRandom->Uniform(-2,2);
    h2->Fill(x);
  }

  // on dessine l'histogramme

  h2->Draw();


}
