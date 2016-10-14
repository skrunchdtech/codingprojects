/* -*- C++ -*- */

/***************************************
Class: CS251
Assignment Number: 4c
Honor Pledge: I pledge that I have not recieved nor given help on this assignment.
***************************************/

#ifndef _Tree_Iterator_Impl_H
#define _Tree_Iterator_Impl_H

#include "Tree.h"
#include "Queue.h"
#include "LQueue.h"
#include "AQueue.h"
#include "Typedefs.h"
#include "Refcounter.h"
#include "Options.h"

/**
 * @class Tree_Iterator_Impl
 * @brief Abstract base class of the actual implementation of 
 *		  Tree_Iterator.
 *
 */
template <typename T>
class Tree_Iterator_Impl 
{
  friend class Tree_Iterator<T>;
  friend class Refcounter <Tree_Iterator_Impl<T> >; // allows refcounting

public:

  /// Unknown_Order class for exceptions when an unknown order
  /// name is passed to the begin or end methods

  class Unknown_Order
  {
  public:
    Unknown_Order(const std::string &msg)
    {
      msg_ = msg;
    }

    const std::string what(void)
    {
      return msg_;
    }
  private:
    std::string msg_;
  };

  /// Default ctor - needed for reference counting, for ::end
  Tree_Iterator_Impl ();

  //Should these constructor methods be defined in the base class
  //The class is abstract

  //Constructor that takes in an entry
  Tree_Iterator_Impl (Tree<T> &tree);
  
  //Tree_Iterator_Impl(const Tree_Iterator_Impl<T>& rhs);

  virtual ~Tree_Iterator_Impl(void);

  /// Dereference operator returns a reference to the item contained
  /// at the current position
  virtual Tree<T>& operator* (void) = 0;

  /// Returns a const reference to the item contained at the current position
  virtual const Tree<T>& operator* (void) const = 0;

  /// Preincrement operator
  virtual Tree_Iterator_Impl<T> &operator++ (void) = 0;

  /// Equality operator
  virtual bool operator== (const Tree_Iterator_Impl<T> &rhs) const =0;

  /// Nonequality operator
  virtual bool operator!= (const Tree_Iterator_Impl<T> &lhs) const =0;

  virtual Tree_Iterator_Impl<T>* clone (void) = 0;

  // = Necessary traits
  typedef std::forward_iterator_tag iterator_category;
  typedef T value_type;
  typedef T *pointer;
  typedef T &reference;
  typedef int difference_type;

private:
  /// Reference counter
  int use_;
};

/**
 * @class Level_Order_Tree_Iterator_Impl
 * @brief Implementation of the Tree_Iterator based on 
 *		  Level_Order traversal.
 *
 */

template <typename T>
class Level_Order_Tree_Iterator_Impl : public Tree_Iterator_Impl<T>
{
public:

  /// Default ctor - needed for reference counting, for end
  Level_Order_Tree_Iterator_Impl();
  
  /// Constructor that takes in an entry
  Level_Order_Tree_Iterator_Impl (Tree<T> &tree);

  //copy
  Level_Order_Tree_Iterator_Impl(const Level_Order_Tree_Iterator_Impl<T>& rhs);

  virtual ~ Level_Order_Tree_Iterator_Impl(void);

  /// Dereference operator returns a reference to the item contained
  /// at the current position
  virtual Tree<T>& operator* (void);

  /// Returns a const reference to the item contained at the current position
  virtual const Tree<T>& operator* (void) const;

  /// Preincrement operator
  virtual Level_Order_Tree_Iterator_Impl<T>& operator++ (void);

  /// Equality operator
  virtual bool operator== (const Tree_Iterator_Impl<T> &rhs) const;

  /// Nonequality operator
  virtual bool operator!= (const Tree_Iterator_Impl<T> &lhs) const;

  /// Clone the iterator.
  virtual Level_Order_Tree_Iterator_Impl<T>* clone(void);

private:
  /// Factory method to create the appropriate type of queue.
  Queue<Tree <T> > *make_queue_strategy (const std::string &queue_type);

  /// Pointer to Queue class used for level traversal.
  std::auto_ptr<Queue<Tree <T> > > queue_;

  ///Tree 
  mutable Tree<T> level_tree_;
  
  Tree<T> root_;

  Queue<Tree <T> >* Copy_Queue(const Level_Order_Tree_Iterator_Impl<T>& rhs)
    {
        //downcast to derived class type and use it's equality stuff.
        std::string queue_type = Options::instance()->queue_type();

        if (queue_type == "LQueue")
        {
            //downcast the queue_ to LQUEUE_ADAPTER
            // downcast - explicit type case required 
	        const Queue_Adapter<Tree <T>, LQueue <Tree <T> > > *temp = 
                dynamic_cast < const Queue_Adapter<Tree <T>, 
                    LQueue <Tree <T> > > *>(rhs.queue_.get());

            //then copy the queue using the assignment operator
            return new Queue_Adapter<Tree <T>, LQueue <Tree <T> > > (*temp);
        }
        else if (queue_type == "AQueue")
        {
            //downcast the queue_ to AQUEUE_ADAPTER
            const Queue_Adapter<Tree <T>, AQueue <Tree <T> > > *temp = 
                dynamic_cast < const Queue_Adapter<Tree <T>, 
                    AQueue <Tree <T> > > *> (rhs.queue_.get());

           // then copy the queue using the assignment operator
           return new Queue_Adapter<Tree <T>, AQueue <Tree <T> > > (*temp);
        }
    }
};

#include "Tree_Iterator_Impl.cpp"

#endif /* __Tree_Iterator_Impl_H */
