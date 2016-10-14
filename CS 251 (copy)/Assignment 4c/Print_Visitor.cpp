/* -*- C++ -*- */

/***************************************
Class: CS251
Assignment Number: 4c
Honor Pledge: I pledge that I have not recieved nor given help on this assignment.
***************************************/

#if !defined (_Print_Visitor_CPP)
#define _Print_Visitor_CPP

#include <iostream>

#include "Print_Visitor.h"
#include "Tree.h"

/// visit method for Node<char> instance
void Print_Visitor::visit(const NODE& node)
{
    std::cout << node.item();
}

#endif //_Print_Visitor_CPP
