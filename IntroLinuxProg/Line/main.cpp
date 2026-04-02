//
// Standard library includes
//
#include <iostream>

//
// Include the class interface
//
#include "Line.h"

using namespace std;  //On utilise un espace de nom ici


int main()
{
   //
   // Create a line object
   //
   //Line l(Point(0.0, 0.0), Point(10.0, 10.0));
   Line l(Point(0.0, 0.0), Point(33.0, 33.0));
   Point inizio = l.start();
   Point fine = l.end();

   cout << "line start = " << inizio.getX() << "," << inizio.getY() << "; fin ligne = "<< fine.getX() << "," << fine.getY() << endl;
   //
   // Translate it
   //
   l.translate(10.0, 35.0);

   // Show its length
   //
   cout << "l.length() = " << l.length() << endl;
   
   cout << "start of line = " << (l.start()).getX() << "," << (l.start()).getY() << "; end of line = "<< (l.end()).getX() << "," << (l.end()).getY() << endl;
   cout << "C++ script compiled by:" << endl;
   cout << "Javier Alonzo ROMO LEON."<< endl;
   cout << "M.Sc. NE-PIA Candidate: j25romol." << endl;
   cout << "As of: 1 april 2026." << endl;
   return 0;
};
