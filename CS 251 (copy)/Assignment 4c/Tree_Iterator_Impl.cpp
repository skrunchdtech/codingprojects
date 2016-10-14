/* -*- C++ -*- */

/***************************************
Class: CS251
Assignment Number: 4c
Honor Pledge: I pledge that I have not recieved nor given help on this assignment.
***************************************/

#if !defined (_Tree_Iterator_Impl_CPP)
#define _Tree_Iterator_Impl_CPP

#include "Tree_Iterator_Impl.h"
#include "LQueue.h"
#include "AQueue.h"
#include <iostream>

// Size for the AQueue.
const size_t AQUEUE_SIZE = 80;

// Default ctor - needed for reference counting.
template <typename T>
Tree_Iterator_Impl<T>::Tree_Iterator_Impl ()
  :use_(1)// You fill in here.
{
}

template <typename T>
Tree_Iterator_Impl<T>::Tree_Iterator_Impl (Tree<T> &tree)
  :use_(1)// You fill in here.
{
}


// This needs to be virtual so that subclasses are correctly destroyed.
template <typename T>
Tree_Iterator_Impl<T>::~Tree_Iterator_Impl ()
{
}

// Ctor
template <typename T>
Level_Order_Tree_Iterator_Impl<T>::Level_Order_Tree_Iterator_Impl()
  : queue_(make_queue_strategy (Options::instance()->queue_type ())),
    level_tree_(),
    root_()
{
}

// Ctor
template <typename T>
Level_Order_Tree_Iterator_Impl<T>::Level_Order_Tree_Iterator_Impl (Tree<T> &tree)
  : queue_(make_queue_strategy (Options::instance()->queue_type ())),
    level_tree_(tree),
    root_(tree)
{
    if(!level_tree_.is_null())  
        queue_->enqueue(level_tree_);
}

// Copy Ctor
template <typename T>
Level_Order_Tree_Iterator_Impl<T>::Level_Order_Tree_Iterator_Impl
  (const Level_Order_Tree_Iterator_Impl<T>& rhs)
  : queue_(Copy_Queue(rhs)),
    level_tree_(rhs.level_tree_),
    root_(rhs.root_)
{
    
}

// A Factory method for creating queues.
template <typename T>
Queue<Tree <T> > *
Level_Order_Tree_Iterator_Impl<T>::make_queue_strategy (const std::string &queue_type)
{
    if (queue_type == "LQueue")
        return new Queue_Adapter<Tree <T>, LQueue<Tree <T> > >(AQUEUE_SIZE); 

//use new to place on heap
    else if (queue_type == "AQueue")
        return new Queue_Adapter<Tree <T>, AQueue<Tree <T> > > (AQUEUE_SIZE);

    else
    //throw copy of string
        throw std::string(queue_type);
}

template <typename T>
Level_Order_Tree_Iterator_Impl<T>::~Level_Order_Tree_Iterator_Impl(void)
{
  // The queue is held in an auto_ptr which will call the destructor
  // when moving out of scope.
}

template <typename T>
Tree<T>& Level_Order_Tree_Iterator_Impl<T>::operator* (void)
{
    level_tree_ = queue_->front();
    return level_tree_;
}

template <typename T>
const Tree<T>& Level_Order_Tree_Iterator_Impl<T>::operator* (void) const
{
    level_tree_ = queue_->front();
    return level_tree_;
}

template <typename T>
Level_Order_Tree_Iterator_Impl<T>& 
Level_Order_Tree_Iterator_Impl<T>::operator++ (void)
{
    if(!queue_->front().left().is_null())
        queue_->enqueue(queue_->front().left());
    if(!queue_->front().right().is_null())
        queue_->enqueue(queue_->front().right());

    queue_->dequeue(); 
    return *this;
}

/// Equality operator
template <typename T>
bool Level_Order_Tree_Iterator_Impl<T>::operator== (const Tree_Iterator_Impl<T> &rhs) const
{   

    const Level_Order_Tree_Iterator_Impl<T>* temp = 
        dynamic_cast<const Level_Order_Tree_Iterator_Impl<T>*> (&rhs);

    if(temp == 0)
        return false;

    if(queue_->is_empty() && temp->queue_->is_empty()) 
        return true;

    if(!queue_->is_empty() && temp->queue_->is_empty() ||
        queue_->is_empty() && !temp->queue_->is_empty()) 
            return false;

    return queue_->front() == temp->queue_->front() &&
        root_ == temp->root_;
}

/// Nonequality operator
template <typename T>
bool Level_Order_Tree_Iterator_Impl<T>::operator!= (const Tree_Iterator_Impl<T> &rhs) const
{
    return !((*this) == rhs);//use the operator==
}

//clone for post increment in the bridge class
template <typename T>
Level_Order_Tree_Iterator_Impl<T>* 
Level_Order_Tree_Iterator_Impl<T>::clone(void)
{
    return new Level_Order_Tree_Iterator_Impl(*this); 
}

#endif /*_Tree_Iterator_Impl_CPP */
