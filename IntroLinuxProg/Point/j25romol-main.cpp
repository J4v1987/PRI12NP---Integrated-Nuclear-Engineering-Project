//
// Standard library includes
//
#include <iostream>
#include <cfloat>
#include <cmath>
#include <limits>
//
// Include the class interface
//
#include "j25romol-Point.h"

using namespace std;  //On utilise un espace de nom ici


int main()
{
   //
   // Create a point object using the default constructor
   //
   Point target;

   //
   // Print its coordinates
   //
   cout << "Target x= " << target.getX() <<" y= "<< target.getY() << endl;

   //
   // Translate it
   //
   cout << "Before translate, distance to the origin: "
        << target.rho() << endl;    //j25romol: rho 'ρ' is a method that assumes an origin is located at (0,0) and then calculates the distance of a point object from this origin by applying the Pythagorean theorem directly to the x and y coordinates of the point object. See: https://mathworld.wolfram.com/PythagoreanTheorem.html
   target.translate(10.0, 35.0);  //j25romol: applying the translate method to the point object 'target', to set target at x=10.0 and y=35.0, by adding 10.0 to the x coordinate and 35.0 to the y coordinate of the target point object.
   
   cout << "After translate, distance to the origin: " << target.rho() << endl;
   cout << "Target x= " << target.getX() <<" y= "<< target.getY() << endl;
   
   /*
   j25romol:
      From class conversation with Prof. M. Settimo, and instructions in file "Initiation to Linux",
      It is required to move point object 'target' to coordinates (20,20).
      The upcoming lines achieve this result and print it to Terminal:
   */
   target.moveTo(20,20);
   cout << "------------------" << endl;
   cout << "Initiation to Linux 2026 update 1: move 'target' to (20,20)" << endl;
   cout << "After target moveTo(20.0, 20.0) x= " << target.getX() <<" y= "<< target.getY() << endl;
   cout << "------------------" << endl;

   //
   // Compute distance to origin by using 'distanceTo'
   //
   const Point origin(0.0, 0.0);
   cout << "Distance to origin = " << target.distanceTo(origin) << endl;   //j25romol: distanceTo is a method that calculates the distance between the target point from which this method is called and some other point fed to the method, using the Pythagorean theorem. See: https://mathworld.wolfram.com/PythagoreanTheorem.html

   //
   // Create another one using the other constructor
   //
   Point p(15.5, 18.9);
   cout << "p x= " << p.getX() <<" y= "<< p.getY() << endl;
   p.moveTo(10.0, 20.0);   //j25romol: given the point object 'p' with initial coordinates x=15.5 and y=18.9, its method moveTo overwrites these coordinates with the new values x=10.0 and y=20.0.
   cout << "After p moveTo(10.0, 20.0) x= " << p.getX() <<" y= "<< p.getY() << endl;
   
   Point p1(0, 1);
   Point p2(2, 2);
   
   float step = p1.distanceTo(p2);
   cout << "p1 x= " << p1.getX() <<" y= "<< p1.getY() << endl;
   cout << "p2 x= " << p2.getX() <<" y= "<< p2.getY() << endl;
   cout << "Distance p1 to p2 = " << step << endl;

   //
   // Create a copy  
   //
   cout << "Create a copy: " <<endl;
   Point p3(10,20);
   // using copy constructor
   Point p4(p3);
   // using operator =
   Point p5 = p3;

   cout << "p3 x= " << p3.getX() <<" y= "<< p3.getY() <<" address "<<&p3 << endl;
   cout << "p4 x= " << p4.getX() <<" y= "<< p4.getY() <<" address "<<&p4 << endl;   //j25romol: the copy constructor creates a new point with the same coordinates as those fed to the constructor, but with a different memory address, allegedly demanding less memory than the built-in C++ assignment operator '='.
   cout << "p5 x= " << p5.getX() <<" y= "<< p5.getY() <<" address "<<&p5 << endl;   //j25romol: copying p3 to p5 using the built-in C++ assignment operator to demonstrate its memory address, and how it differs slightly more with respect from p4, in comparison to the difference between p4 to p3, allegedly demanding more memory than the copy constructor.

   Point p6(0,-10);
   //theta --- IGNORE ---                                   //j25romol: superseded, see the method 'phi' below.
   //cout << "Theta(p6) "<<p6.theta() <<endl;               //j25romol: superseded, the method 'theta' has been renamed to 'phi' in consistency with ISO 80000-2:2009(E) standard, which defines the 'azimuthal' angle (from x towards y) in a spherical coordinate system as 'phi' or 'φ', while the 'polar' angle 'theta' or 'ϑ' refers to the angle from z towards the xy plane. See: https://en.wikipedia.org/wiki/Spherical_coordinate_system#ISO_80000-2:2009(E)_standard
   //j25romol: In attempting to evaluate to real float 0, the following could be tried:
   //float epsilon = std::numeric_limits<float>::epsilon(); //j25romol
   //cout << "Epsilon = " << epsilon << endl;               //j25romol
   //cout << "Float 0.0 = " << 0.0f << endl;                //j25romol 
   //cout << "0.0 = " << 0.0 << endl;                       //j25romol
   cout << "Phi(p6) "<<p6.phi() <<endl;                     //j25romol: the method 'theta' has been renamed to 'phi' in consistency with ISO 80000-2:2009(E) standard, which defines the 'azimuthal' angle (from x towards y) in a spherical coordinate system as 'phi' or 'φ', while the 'polar' angle 'theta' or 'ϑ' refers to the angle from z towards the xy plane. See: https://en.wikipedia.org/wiki/Spherical_coordinate_system#ISO_80000-2:2009(E)_standard

   cout << "------------------" << endl;
   cout << "C++ script compiled by:" << endl;
   cout << "Javier Alonzo ROMO LEON."<< endl;
   cout << "M.Sc. NE-PIA Candidate: j25romol." << endl;

   return 0;
};
