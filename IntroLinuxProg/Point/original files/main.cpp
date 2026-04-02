//
// Standard library includes
//
#include <iostream>

//
// Include the class interface
//
#include "Point.h"

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
        << target.rho() << endl;
   target.translate(10.0, 35.0);

   cout << "After translate, distance to the origin: " << target.rho() << endl;
   cout << "Target x= " << target.getX() <<" y= "<< target.getY() << endl;
   
   //
   // Compute distance to origin by using 'distanceTo'
   //
   const Point origin(0.0, 0.0);
   cout << "Distance to origin = " << target.distanceTo(origin) << endl;

   //
   // Create another one using the other constructor
   //
   Point p(15.5, 18.9);
   cout << "p x= " << p.getX() <<" y= "<< p.getY() << endl;
   p.moveTo(10.0, 20.0);
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
   cout << "p4 x= " << p4.getX() <<" y= "<< p4.getY() <<" address "<<&p4 << endl;
   cout << "p5 x= " << p5.getX() <<" y= "<< p5.getY() <<" address "<<&p5 << endl;

   Point p6(0,-10);
   //theta
   cout << "Theta(p6) "<<p6.theta() <<endl;

   return 0;
};
