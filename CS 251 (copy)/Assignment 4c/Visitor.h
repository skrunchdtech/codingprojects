/* -*- C++ -*- */

/***************************************
Class: CS251
Assignment Number: 4c
Honor Pledge: I pledge that I have not recieved nor given help on this assignment.
***************************************/

#ifndef _Visitor_H
#define _Visitor_H

#include "Typedefs.h"

/**
 * @class Visitor 
 * @brief Defines an abstract base class for all Visitor classes
 */

class Visitor
{
public:
  /// Dtor
  virtual ~Visitor () = 0;

  /// Visit method for NODE instances
  /// Pure virtual function.
  virtual void visit (const NODE& node) =0;
};

#endif /* _Visitor_H */
