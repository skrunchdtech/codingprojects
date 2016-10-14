/* -*- C++ -*- */

/***************************************
Class: CS251
Assignment Number: 4c
Honor Pledge: I pledge that I have not recieved nor given help on this assignment.
***************************************/

#if !defined (_Tree_Iterator_CPP)
#define _Tree_Iterator_CPP

template <typename T>
Tree_Iterator<T>::Tree_Iterator(Tree_Iterator_Impl<T>* impl)
  : tree_iterator_impl_(impl)
{
}

/// Copy ctor - needed for reference counting.
template <typename T>
Tree_Iterator<T>::Tree_Iterator(const Tree_Iterator<T> &rhs)
  : tree_iterator_impl_(rhs.tree_iterator_impl_)
{
}

/// Assignment operator - needed for reference counting.
template <typename T>
void Tree_Iterator<T>::operator= (const Tree_Iterator<T> &rhs)
{
    if(this != &rhs)
        tree_iterator_impl_ = rhs.tree_iterator_impl_;

}

  /// Dereference operator returns a reference to the item contained
  /// at the current position
template <typename T>
Tree<T>& Tree_Iterator<T>::operator* (void)
{
    return **tree_iterator_impl_;
}

/// Returns a const reference to the item contained at the current position
template <typename T>
const Tree<T>& Tree_Iterator<T>::operator* (void) const
{
    return **tree_iterator_impl_;
}

/// Preincrement operator
template <typename T>
Tree_Iterator<T>& Tree_Iterator<T>::operator++ (void)
{
    ++*tree_iterator_impl_;
    return *this;
}

/// Postincrement operator
template <typename T>
Tree_Iterator<T> Tree_Iterator<T>::operator++ (int)
{
    Tree_Iterator<T> temp(tree_iterator_impl_ -> clone());
    ++*tree_iterator_impl_;
    return temp;
}

  
/// Equality operator
template <typename T>
bool Tree_Iterator<T>::operator== (const Tree_Iterator<T> &rhs) const
{
    *tree_iterator_impl_ == *rhs.tree_iterator_impl_;
}

/// Nonequality operator
template <typename T>
bool Tree_Iterator<T>::operator!= (const Tree_Iterator<T> &rhs) const
{
    return !((*this)==rhs);
}

template <typename T>  
Const_Tree_Iterator<T>::Const_Tree_Iterator (Tree_Iterator_Impl<T>* impl)
  : tree_iterator_impl_(impl)
{
}

/// Copy ctor - needed for reference counting.
template <typename T>
Const_Tree_Iterator<T>::Const_Tree_Iterator (const Const_Tree_Iterator<T> &rhs)
  : tree_iterator_impl_(rhs)
{
}

/// Assignment operator - needed for reference counting.
template <typename T>
void Const_Tree_Iterator<T>::operator= (const Const_Tree_Iterator<T> &rhs)
{
    if(this != &rhs)
        tree_iterator_impl_ = rhs.tree_iterator_impl_;

}



/// Returns a const reference to the item contained at the current position
template <typename T>
const Tree<T>& Const_Tree_Iterator<T>::operator* (void) const
{
    return (*(*tree_iterator_impl_));
}

/// Preincrement operator
template <typename T>
Const_Tree_Iterator<T>& Const_Tree_Iterator<T>::operator++ (void)
{
    ++(*tree_iterator_impl_);
  return (*this);

}

/// Postincrement operator
template <typename T>
Const_Tree_Iterator<T> Const_Tree_Iterator<T>::operator++ (int)
{
     //new tree_iterator instance using the cloned copy of impl
  Tree_Iterator<T> ret = Tree_Iterator<T>(*(tree_iterator_impl_->clone()));
  //increment
  ++(*tree_iterator_impl_);
  return ret;//return instance with the previous state
}

  
/// Equality operator
template <typename T>
bool Const_Tree_Iterator<T>::operator== (const Const_Tree_Iterator<T> &rhs) const
{
//right??
    return ((this ==&rhs) 
          || ((*tree_iterator_impl_)==(*(rhs.tree_iterator_impl_))));
}

/// Nonequality operator
template <typename T>
bool Const_Tree_Iterator<T>::operator!= (const Const_Tree_Iterator<T> &rhs) const
{
    return !((*this)==rhs);
}

#endif //_Tree_Iterator_CPP
