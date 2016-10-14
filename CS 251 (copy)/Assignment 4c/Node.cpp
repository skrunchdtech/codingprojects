/* -*- C++ -*- */

/***************************************
Class: CS251
Assignment Number: 4c
Honor Pledge: I pledge that I have not recieved nor given help on this assignment.
***************************************/

#if !defined (_Node_CPP)
#define _Node_CPP

#include "Visitor.h"

// Ctor
template <typename T>
Node<T>::Node (const T &item, Node *left, Node *right)
  : item_ (item),
    left_ (left),
    right_ (right),
    use_ (1)
{    
}

// Dtor
template <typename T>
Node<T>::~Node ()
{
    // Clean up the subtrees first and then the root recursively
    delete left_;
    delete right_;
}

// Return the item in the node.
template <typename T>
const T &
Node<T>::item (void) const
{
    return item_;
}

// Return the left child.
template <typename T>
Node<T> *
Node<T>::left (void) const
{
    return left_;
}

// Return the right child.
template <typename T>
Node<T> *
Node<T>::right (void) const
{
    return right_;
}

template <typename T>
void 
Node<T>::accept (Visitor& v)
{
    v.visit(*this);
}

#endif /* _Node_CPP */
