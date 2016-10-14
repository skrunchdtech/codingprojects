/* -*- C++ -*- */

/***************************************
Class: CS251
Assignment Number: 4c
Honor Pledge: I pledge that I have not recieved nor given help on this assignment.
***************************************/

#ifndef _Node_H
#define _Node_H

// Forward declaration.

template <typename T>
class Tree;

template <typename T>
class Refcounter;


class Visitor;


/**
 * @class Node
 * @brief Defines a very simple implementation of a binary tree node.
 */
template <typename T>
class Node
{
  /// Needed for reference counting.
  friend class Tree<T>;
  friend class Refcounter<Node<T> >;

public:
  /// Ctor
  Node (const T &item, Node *left = 0, Node *right = 0);

  /// Dtor
  virtual ~Node ();

  /// Return the item stored in the node.
  virtual const T &item (void) const;

  /// Return the left child.
  virtual Node *left (void) const;

  /// Return the right child.
  virtual Node *right (void) const;

  virtual void accept (Visitor& v);

private:
  /// Item stored in the node.
  T item_;

  /// Left child.
  Node *left_;

  /// Right child.
  Node *right_;

  /// Reference counter
  int use_;
};

#include "Node.cpp"

#endif /* _Node_H */
