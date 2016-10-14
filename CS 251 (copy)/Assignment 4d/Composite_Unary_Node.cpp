/* -*- C++ -*- */
#if !defined (_Composite_Unary_Node_CPP)
#define _Composite_Unary_Node_CPP

template <typename T>
Composite_Unary_Node<T>::Composite_Unary_Node (Component_Node<T> *right)
 : right_(right)// You fill in here.
{    
}

template <typename T>
Composite_Unary_Node<T>::~Composite_Unary_Node()
{
}

// Return the right child.
template <typename T>
Component_Node<T> *
Composite_Unary_Node<T>::right (void) const
{
  return right_.get();//to return underlying raw pointer
}

#endif /*_Composite__Unary_Node_CPP*/
