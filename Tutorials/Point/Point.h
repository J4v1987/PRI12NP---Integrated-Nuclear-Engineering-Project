

#if !defined(POINT_H)
#define POINT_H

#include <iostream>

class Point {

public:
 
  // function members - Methods

   //
   // Constructors/Destructor
   //
   Point(float initialX = 0.0, float initialY = 0.0);
   Point(const Point& aPoint);
   ~Point();
   
   //
   // Operators
   //
   //variabile bool é variabile logica (vero o falso)

   bool operator==(const Point& aPoint) const;
   bool operator!=(const Point& aPoint) const;
   Point& operator=(const Point& aPoint);

   //
   // Modifiers
   //
   //void é una funzione che non ritorna un valore
   void translate(float horizontal, float vertical);
   Point& moveTo(float x, float y);

   //
   // Selectors
   //
   float getX() const;       // x coordinate
   float getY() const;       // y coordinate
   float rho() const;     // distance to the origin
   float distanceTo(const Point& aPoint) const;

   //theta
   float theta() const;

private:
 
   //
   // Data members
   //
   float x_;
   float y_;
};


// --------------------------------------------------------------//
//               Inline member fonction implementation           //
// --------------------------------------------------------------//


// --------------------------------------------------------------//
//                           Operators                           //
// --------------------------------------------------------------//

//
// operator !=
//se i 2 punti sono diversi risponde vero
inline bool Point::operator!=(const Point& aPoint) const
{
   return (*this == aPoint) ? false : true;
};


// --------------------------------------------------------------//
//                           Selectors                           //
// --------------------------------------------------------------//

//
// getX
//
inline float Point::getX() const
{
   return x_;
};

//
// getY
//
inline float Point::getY() const
{
   return y_;
};

#endif // POINT_H
