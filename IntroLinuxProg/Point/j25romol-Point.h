

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
   //variabile bool � variabile logica (vero o falso)

   bool operator==(const Point& aPoint) const;
   bool operator!=(const Point& aPoint) const;
   Point& operator=(const Point& aPoint);

   //
   // Modifiers
   //
   //void � una funzione che non ritorna un valore
   void translate(float horizontal, float vertical);
   Point& moveTo(float x, float y);

   //
   // Selectors
   //
   float getX() const;       // x coordinate
   float getY() const;       // y coordinate
   float rho() const;     // distance to the origin
   float distanceTo(const Point& aPoint) const;

   
   //float theta() const;
   float phi() const;     //j25romol: the method 'theta' has been renamed to 'phi' in consistency with ISO 80000-2:2009(E) standard, which defines the 'azimuthal' angle (from x towards y) in a spherical coordinate system as 'phi' or 'φ', while the 'polar' angle 'theta' or 'ϑ' refers to the angle from z towards the xy plane. See: https://en.wikipedia.org/wiki/Spherical_coordinate_system#ISO_80000-2:2009(E)_standard

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
