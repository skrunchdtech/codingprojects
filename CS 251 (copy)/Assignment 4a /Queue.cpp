/* -*- C++ -*- */

/***************************************
Class: CS251
Assignment Number: 4a
Honor Pledge: I pledge that I have not recieved nor given help on this assignment.
***************************************/

#if !defined (_Queue_CPP)
#define _Queue_CPP

#include "Queue.h"
#include <iostream>

// Constructor.
template <typename T, typename QUEUE>
Queue_Adapter<T, QUEUE>::Queue_Adapter (size_t size)
  :queue_(size) 
{
}

// Destructor.
template <typename T>
Queue<T>::~Queue (void)
{
  
}

// Copy constructor.
template <typename T, typename QUEUE>
Queue_Adapter<T, QUEUE>::Queue_Adapter (const Queue_Adapter<T, QUEUE> &rhs)
 :queue_(rhs.queue_) 
{
}

// Assignment operator.
template <typename T, typename QUEUE>
Queue_Adapter<T, QUEUE> &
Queue_Adapter<T, QUEUE>::operator= (const Queue_Adapter<T, QUEUE> &rhs) 
{
  if(this != &rhs)
    {
        queue_= rhs.queue_;        
    }

    return *this;
}

// Perform actions needed when queue goes out of scope.
template <typename T, typename QUEUE>
Queue_Adapter<T, QUEUE>::~Queue_Adapter (void)
{
  
}

// Compare this queue with <rhs> for equality.  Returns true if the
// size()'s of the two queues are equal and all the elements from 0
// .. size() are equal, else false.
template <typename T, typename QUEUE>
bool
Queue_Adapter<T, QUEUE>::operator== (const Queue_Adapter<T, QUEUE> &rhs) const
{
  return queue_ == rhs.queue_;
}

// Compare this queue with <rhs> for inequality such that <*this> !=
// <s> is always the complement of the boolean return value of
// <*this> == <s>.
template <typename T, typename QUEUE>
bool 
Queue_Adapter<T, QUEUE>::operator!= (const Queue_Adapter<T, QUEUE> &rhs) const
{
   return !(*this == rhs);
}

// Place a <new_item> at the tail of the queue.  Throws
// the <Overflow> exception if the queue is full.
template <typename T, typename QUEUE>
void
Queue_Adapter<T, QUEUE>::enqueue (const T &new_item)
{
    try{ queue_.enqueue(new_item);}
    catch(typename QUEUE::Overflow&)
    { 
        throw typename Queue<T>::Overflow();
    }
}

// Remove the front item on the queue.  Throws the <Underflow>
// exception if the queue is empty.
template <typename T, typename QUEUE>
void
Queue_Adapter<T, QUEUE>::dequeue (void)
{
  if(! queue_.is_empty())
    {
        queue_.dequeue();
    }
  else
    throw typename Queue<T>::Underflow();
}

// Returns the front queue item without removing it. 
// Throws the <Underflow> exception if the queue is empty. 
template <typename T, typename QUEUE>
T
Queue_Adapter<T, QUEUE>::front (void) const
{
    if(!queue_.is_empty())
    {
        return queue_.front();
    }
    else
        throw typename Queue<T>::Underflow();
}

// Returns true if the queue is empty, otherwise returns false.
template <typename T, typename QUEUE>
bool
Queue_Adapter<T, QUEUE>::is_empty (void) const 
{
  return queue_.is_empty(); 
}

// Returns true if the queue is full, otherwise returns false.
template <typename T, typename QUEUE>
bool
Queue_Adapter<T, QUEUE>::is_full (void) const 
{
  return queue_.is_full(); 
}

// Returns the current size.
template <typename T, typename QUEUE>
size_t 
Queue_Adapter<T, QUEUE>::size (void) const
{
  return queue_.size(); 
}

#endif /* _Queue_CPP */
