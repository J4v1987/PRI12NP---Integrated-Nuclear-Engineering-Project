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
#include "j25romol-line-Point.h"

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
//
bool Point::operator==(const Point& aPoint) const
{
   TRACE("Point::operator==(const Point&) const")

   return (x_ == aPoint.x_) && (y_ == aPoint.y_);
};


//
// operator =
//
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
// rotate
//
void Point::rotate(float angle)
{
   TRACE("Point::rotate(float)")

   float currentRho = rho();
   float newTheta = theta() + angle;

   x_ = currentRho + (float)cos(newTheta);
   y_ = currentRho + (float)sin(newTheta);
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
// theta
//
float Point::theta() const
{
   TRACE("Point::theta() const")

   if (x_ == 0.0) {  // Not really safe
      if (y_ == 0.0)
         return 0.0;
      const float Pi = 3.1415926535F;
      return (float)((y_ > 0.0) ? 0.5*Pi : 1.5*Pi);
   }

   return (float)atan(y_/x_);
};



//
// distanceTo
//
float Point::distanceTo(const Point& aPoint) const
{
   TRACE("Point::distanceTo(const Point&) const")
   
   float deltaX = aPoint.x_ - x_;
   deltaX *= deltaX;
   
   float deltaY = aPoint.y_ - y_;
   deltaY *= deltaY;

   return (float)sqrt(deltaX + deltaY);
};

//-------------------------------------------------------------------------//

