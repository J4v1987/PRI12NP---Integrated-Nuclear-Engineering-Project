// --------------------------------------------------------------//
// File:   Line.h                                                //
// Author: Fabio HERNANDEZ                                       //
//         Fabio.Hernandez@in2p3.fr                              //
// Date:   August 1998                                           //
// --------------------------------------------------------------//

#if !defined(LINE_H)
#define LINE_H

#include <iostream>


#include "j25romol-line-Point.h"

class Line {

public:
 
   //
   // Constructors/Destructor
   //
   Line(const Point& start, const Point& end);
   Line(const Line& aLine);
   ~Line();
   
   //
   // Operators
   //
   bool operator==(const Line& aLine) const;
   bool operator!=(const Line& aLine) const;
   Line& operator=(const Line& aLine);

   //
   // Modifiers
   //
   void translate(float horizontal, float vertical);
   void rotate(float angle);

   //
   // Selectors
   //
   const Point& start() const;     // starting point
   const Point& end() const;       // ending point
   float length() const;


private:
 
   //
   // Data members
   //
   Point start_;
   Point end_;
};


// --------------------------------------------------------------//
//               Inline member fonction implementation           //
// --------------------------------------------------------------//


// --------------------------------------------------------------//
//                           Operators                           //
// --------------------------------------------------------------//

//
// operator !=
//
inline bool Line::operator!=(const Line& aLine) const
{
   return (*this == aLine) ? false : true;
};


// --------------------------------------------------------------//
//                           Selectors                           //
// --------------------------------------------------------------//

//
// start
//
inline const Point& Line::start() const
{
   return start_;
};

//
// end
//
inline const Point& Line::end() const
{
   return end_;
};


//
// length
//
inline float Line::length() const
{
   return start_.distanceTo(end_);
}

#endif // LINE_H

