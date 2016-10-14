#if !defined (_Composite_Multiply_Node_CPP)
#define _Composite_Multiply_Node_CPP

template <typename T>
Composite_Multiply_Node<T>::Composite_Multiply_Node 
(Component_Node<T> *left,Component_Node<T> *right)
  : Composite_Binary_Node<T>(left, right)// You fill in here.
{    
}

template <typename T>
Composite_Multiply_Node<T>::~Composite_Multiply_Node()
{
}

// Visitor.
template <typename T>
void
Composite_Multiply_Node<T>::accept (Visitor& v)
{
  v.visit(*this);// You fill in here.
}

#endif /*_Composite_Multiply_Node_CPP*/
