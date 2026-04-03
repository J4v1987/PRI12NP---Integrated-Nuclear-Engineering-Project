//
// Standard library includes
//
#include <iostream>

//
// Include the class interface
//
#include "j25romol-Line.h"

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
   
   cout << "" << endl;
   cout << "------------------" << endl;
   cout << "j25romol-line-main.cpp edit:" << endl;
   cout << "EndPoint.moveTo operation is executed." << endl;
   fine.moveTo(66.0,33.0);
   cout << "Point 'fine'= " << fine.getX() <<" y= "<< fine.getY() <<" address "<<&fine << endl;
   cout << "New line object 'l2' is created with revised point 'fine' and original 'inizio'." << endl;
   Line l2(inizio, fine);
   cout << "l2.length() = " << l2.length() << endl;
   cout << "Start of line 'l2' = " << (l2.start()).getX() << "," << (l2.start()).getY() << "; End of line 'l2'= "<< (l2.end()).getX() << "," << (l2.end()).getY() << endl;
   cout << "C++ script compiled by:" << endl;
   cout << "Javier Alonzo ROMO LEON."<< endl;
   cout << "M.Sc. NE-PIA Candidate: j25romol." << endl;
   return 0;
};

