// -------------------------------------------------------------- //
// File:    Line.cpp                                              //
// Purpose: class Line implementation                             //
// Author:  Fabio HERNANDEZ                                       //
//          Fabio.Hernandez@in2p3.fr                              //
// Date:    August 1998                                           //
// -------------------------------------------------------------- //


//
// Standard library includes
//
#include <iostream>
#include <iomanip>
#include <math.h>

//
// Include this class interface
//
#include "Line.h"


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
Line::Line(const Point& start, const Point& end)
{
   TRACE("Line::Line(const Point&, const Point&)")

   start_ = start;
   end_ = end;
};

//
// Copy constructor
//
Line::Line(const Line& aLine)
{
   TRACE("Line::Line(const Line&)")

   start_ = aLine.start_;
   end_ = aLine.end_;
};

//
// Destructor
//
Line::~Line()
{
   TRACE("Line::~Line()")
   // Nothing more to do here
};



// --------------------------------------------------------------//
//                             Operators                         //
// --------------------------------------------------------------//


//
// operator ==
//
bool Line::operator==(const Line& aLine) const
{
   TRACE("Line::operator==(const Line&) const")

   return (start_ == aLine.start_) && (end_ == aLine.end_);
};


//
// operator =
//
Line& Line::operator=(const Line& aLine)
{
   TRACE("Line::operator=(const Line&)")

   if (this == &aLine)
      return *this;
      
   start_ = aLine.start_;
   end_ = aLine.end_;
   return *this;
};




// --------------------------------------------------------------//
//                             Modifiers                         //
// --------------------------------------------------------------//

//
// translate
//
void Line::translate(float horizontal, float vertical)
{
   TRACE("Line::translate(float, float)")

   start_.translate(horizontal, vertical);
   end_.translate(horizontal, vertical);
};


//
// rotate
//
void Line::rotate(float angle)
{
   TRACE("Line::rotate(float)")

   start_.rotate(angle);
   end_.rotate(angle);
};

//-------------------------------------------------------------------------//
