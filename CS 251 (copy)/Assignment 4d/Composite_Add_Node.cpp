/* -*- C++ -*- */
#if !defined (_Composite_Add_Node_CPP)
#define _Composite_Add_Node_CPP

template <typename T>
Composite_Add_Node<T>::Composite_Add_Node 
(Component_Node<T> *left,Component_Node<T> *right)
  : Composite_Binary_Node<T>(left, right)
{    
}

template <typename T>
Composite_Add_Node<T>::~Composite_Add_Node()
{
}

// Visitor.
template <typename T>
void
Composite_Add_Node<T>::accept (Visitor& v)
{
  v.visit(*this);
}

#endif /*_Composite_Add_Node_CPP*/
