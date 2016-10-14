/* -*- C++ -*- */

/***************************************
Class: CS251
Assignment Number: 4c
Honor Pledge: I pledge that I have not recieved nor given help on this assignment.
***************************************/

#ifndef _Print_Visitor_H
#define _Print_Visitor_H

#include "Visitor.h"

/**
 * @class Print_Visitor is a subclass of Visitor
 * @brief Defines a Print_Visitor - prints the contents of the visited entity.
 */

class Print_Visitor : public Visitor
{
public:
  //Visit method for NODE elements
  virtual void visit(const NODE& node);
};

//#include "Print_Visitor.cpp"

#endif /* _Print_Visitor_H */
