/* -*- C++ -*- */

/***************************************
Class: CS251
Assignment Number: 4c
Honor Pledge: I pledge that I have not recieved nor given help on this assignment.
***************************************/

#ifndef _Tree_H
#define _Tree_H
#include <string>
#include "Node.h"
#include "Refcounter.h"
#include "Typedefs.h"

// Forward declaration.

template <typename T>
class Tree_Iterator;

template <typename T>
class Const_Tree_Iterator;

class Visitor;

/**
 * @class Tree
 * @brief Defines a bridge to the node implementation that
 *        actually contains the data items for the tree.
 */



template <typename T>
class Tree
{
  friend class Tree_Iterator<T>;
  friend class Const_Tree_Iterator<T>;
public:
  /// Default ctor
  Tree ();

  /// Ctor that takes a Node<T> *.
  Tree (Node<T> *root, bool count = false);

  /// Ctor with an item to contain.
  Tree (const T &item);

  /// Ctor that takes a node and 2 children.
  Tree (const T &item, Node<T> *left, Node<T> *right);

  // Copy ctor
  Tree (const Tree &t);

  /// Assignment operator
  void operator= (const Tree &t);

  //Equality operator
  bool operator == (const Tree& rhs)const;

  //Inequality operator
  bool operator != (const Tree& rhs)const;

  /// Dtor
  ~Tree (void);

  /// Check if tree is null tree.
  bool is_null (void) const;

  /// Return the item in the tree.
  const T &item (void) const;

  /// Return the left child.
  Tree<T> left (void) const;

  /// Return the right child.
  Tree<T> right (void) const;

  // = Traits for the class.
  typedef T value_type;
  typedef Tree_Iterator<T> iterator;
  typedef Const_Tree_Iterator<T> const_iterator;
  
  // = Factory methods that create iterators.

  // Get an iterator that points to the beginning of the Tree 
  // based on the traversal order
  Tree_Iterator<T> begin(const std::string &traversal_order);

  // Get an iterator that points to the end of the Tree 
  // based on the traversal order
  Tree_Iterator<T> end(const std::string &traversal_order);

  // Get a const iterator that points to the beginning of the Tree 
  // based on the traversal order
  Const_Tree_Iterator<T> begin(const std::string &traversal_order) const;

  // Get a const iterator that points to the end of the Tree 
  // based on the traversal order
  Const_Tree_Iterator<T> end(const std::string &traversal_order) const;

  //Accept method for the Visitor 
  void accept (Visitor&);

private:
  /// The underlying pointer to the implementation. These are
  /// reference counted.
  Refcounter <Node<T> > root_;
};

#include "Tree_Iterator.h"

#include "Tree.cpp"

#endif /* _Tree_H */
