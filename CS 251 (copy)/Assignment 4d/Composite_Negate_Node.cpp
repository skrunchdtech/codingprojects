/* -*- C++ -*- */
#if !defined (_Composite_Negate_Node_CPP)
#define _Composite_Negate_Node_CPP

template <typename T>
Composite_Negate_Node<T>::Composite_Negate_Node (Component_Node<T> *right)
  : Composite_Unary_Node<T>(right)// You fill in here.
{    
}

template <typename T>
Composite_Negate_Node<T>::~Composite_Negate_Node()
{
}

// Visitor.
template <typename T>
void
Composite_Negate_Node<T>::accept (Visitor& v)
{
  v.visit(*this);// You fill in here.
}

#endif /*_Composite_Negate_Node_CPP*/
