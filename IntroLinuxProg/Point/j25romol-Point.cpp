// #define DEBUG

//
// Standard library includes
//
#include <iostream>
#include <iomanip>
#include <math.h>

//
// Include this class interface
//
#include "j25romol-Point.h"

using namespace std;  //On utilise un espace de nom ici

//
// Macro definitions
//
#if defined(DEBUG)
#  define TRACE(message)    cout << "DEBUG: entering " << message << endl;
#else
#  define TRACE(message)
#endif

// --------------------------------------------------------------//
//                   Constructor/Destructor                      //
// --------------------------------------------------------------//

//
// Constructor from initial values
//
Point::Point(float initialX, float initialY)
{
   TRACE("Point::Point(float, float)")

   x_ = initialX;
   y_ = initialY;
};

//
// Copy constructor
//
Point::Point(const Point& aPoint)
{
   TRACE("Point::Point(const Point&)")

   x_ = aPoint.x_;
   y_ = aPoint.y_;
};

//
// Destructor
//
Point::~Point()
{
   TRACE("Point::~Point()")
   // Nothing more to do here
};



// --------------------------------------------------------------//
//                             Operators                         //
// --------------------------------------------------------------//


//
// operator ==
// vero se 2 punti sono =
bool Point::operator==(const Point& aPoint) const
{
   TRACE("Point::operator==(const Point&) const")

   return (x_ == aPoint.x_) && (y_ == aPoint.y_);
};


//
// operator =
//se i 2 punti sono diversi mette uno = all'altro
Point& Point::operator=(const Point& aPoint)
{
   TRACE("Point::operator=(const Point&)")

   if (this == &aPoint)
      return *this;
      
   x_ = aPoint.x_;
   y_ = aPoint.y_;
   return *this;
};




// --------------------------------------------------------------//
//                             Modifiers                         //
// --------------------------------------------------------------//

//
// translate
//
void Point::translate(float horizontal, float vertical)
{
   TRACE("Point::translate(float, float)")

   x_ += horizontal;
   y_ += vertical;
};



//
// moveTo
//
Point& Point::moveTo(float x, float y)
{
   TRACE("Point::moveTo(float, float)")
   x_ = x;
   y_ = y;
   return *this;
};


// --------------------------------------------------------------//
//                             Selectors                         //
// --------------------------------------------------------------//

//
// rho
//
float Point::rho() const
{
   TRACE("Point::rho() const")

   return (float)sqrt(x_*x_ + y_*y_);
};

//
// distanceTo
//
float Point::distanceTo(const Point& aPoint) const //j25romol: fetches the (x,y) coordinates of a point fed to the 'distanceTo' method.
{
   TRACE("Point::distanceTo(const Point&) const")
   //j25romol: Let there be a 'target' Point  with x_ and y_ coordinates, from which the method distanceTo is called. 
   //j25romol: Let there be an 'aPoint' Point with aPoint.x_ and aPoint.y_ coordinates, fed to the method.
   float deltaX = aPoint.x_ - x_;         //j25romol: this line subtracts the x_ coordinate of the target Point from the x_ coordinate of the aPoint, and stores the result in deltaX.
   deltaX *= deltaX;                      //j25romol: this line squares the value of deltaX, in preparation to feed calculations on the Pythagorean theorem. See: https://mathworld.wolfram.com/PythagoreanTheorem.html
   float deltaY = aPoint.y_ - y_;         //j25romol: this line subtracts the y_ coordinate of the target Point from the y_ coordinate of the aPoint, and stores the result in deltaY.
   deltaY *= deltaY;                      //j25romol: this line squares the value of deltaY, in preparation to feed calculations on the Pythagorean theorem. See: https://mathworld.wolfram.com/PythagoreanTheorem.html

   return (float)sqrt(deltaX + deltaY);   //j25romol: implementing the Pythagorean theorem, by squaring deltaX and deltaY, adding them together, and then taking the square root of the result to get the distance between the target Point and the aPoint.
};

//theta
/*float Point::theta() const
{
   TRACE("Point::theta()")
     //return (float) asin(y_/sqrt(x_*x_ + y_*y_));
     return (float) 2*atan(y_/(sqrt(x_*x_ + y_*y_)+x_));
};*/

//float Point::theta() const
float Point::phi() const   //j25romol: the method 'theta' has been renamed to 'phi' in consistency with ISO 80000-2:2009(E) standard, which defines the 'azimuthal' angle (from x towards y) in a spherical coordinate system as 'phi' or 'φ', while the 'polar' angle 'theta' or 'ϑ' refers to the angle from z towards the xy plane. See: https://en.wikipedia.org/wiki/Spherical_coordinate_system#ISO_80000-2:2009(E)_standard
{
   //TRACE("Point::theta() const")
   TRACE("Point::phi() const")

   if (x_ == 0.0) {  // Not really safe //j25romol: ∵x=0 ∴(ρ=y) → [φ=(90ᵒ ∨ 270ᵒ)].
      if (y_ == 0.0) //j25romol: ∵{[φ=(90ᵒ ∨ 270ᵒ)] ∧ y=0} ∴ρ=0.
         return 0.0; //j25romol: ∵ρ=0 ∴φ=0. There's nothing to calculate, return 0.
      const float Pi = 3.1415926535F;  //j25romol: recall that the value of π is approximately 3.1415926535, and that the 'F' suffix indicates that this constant is a float literal, which is appropriate for the return type of the method 'phi'.
      return (float)((y_ > 0.0) ? 0.5*Pi : 1.5*Pi); //j25romol: if the Point object's y-coordinate is larger than 0, then evaluate 0.5*Pi, else evaluate 1.5*Pi. This would yield the angle of ρ in radians. See 'ternary operators' in: https://www.learncpp.com/cpp-tutorial/the-conditional-operator/
   }

   return (float)atan(y_/x_);
}

//-------------------------------------------------------------------------//
