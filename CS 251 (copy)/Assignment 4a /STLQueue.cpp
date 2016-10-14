/* -*- C++ -*- */

/***************************************
Class: CS251
Assignment Number: 4a
Honor Pledge: I pledge that I have not recieved nor given help on this assignment.
***************************************/

#if !defined (_STLQUEUE_CPP)
#define _STLQUEUE_CPP

#include "STLQueue.h"

template <typename T, typename QUEUE>
STLQueue_Adapter<T, QUEUE>::STLQueue_Adapter (size_t)
  :queue_() 
{
}

template <typename T, typename QUEUE>
STLQueue_Adapter<T, QUEUE>::STLQueue_Adapter (const STLQueue_Adapter<T, QUEUE> &rhs)
  : queue_(rhs.queue_)
{
}

template <typename T, typename QUEUE> STLQueue_Adapter<T, QUEUE> &
STLQueue_Adapter<T, QUEUE>::operator= (const STLQueue_Adapter &rhs)
{
  if(this != &rhs)
    {
        queue_= rhs.queue_;
    }

    return *this;
}

// Place a <new_item> at the tail of the queue.  Throws the
// <Overflow> exception if the queue is full, e.g., if memory is
// exhausted.
template <typename T, typename QUEUE>
void 
STLQueue_Adapter<T, QUEUE>::enqueue (const T &new_item)
{
  try{ queue_.push(new_item);}
    catch(std::bad_alloc &)
    { 
        throw Overflow();
    }
}

// Remove the front item on the queue.  Throws the <Underflow>
// exception if the queue is empty.
template <typename T, typename QUEUE>
void 
STLQueue_Adapter<T, QUEUE>::dequeue (void)
{
  if(! queue_.empty())
    {
        queue_.pop();
    }
  else
    throw Underflow();
}  

// Returns the front queue item without removing it. 
// Throws the <Underflow> exception if the queue is empty. 
template <typename T, typename QUEUE>
T 
STLQueue_Adapter<T, QUEUE>::front (void) const
{
  if(!queue_.empty())
    {
        return queue_.front();
    }
  else
    throw Underflow();
}

// = Check boundary conditions for Queue operations. 

// Returns 1 if the queue is empty, otherwise returns 0. 
template <typename T, typename QUEUE>
bool 
STLQueue_Adapter<T, QUEUE>::is_empty (void) const
{
  return queue_.empty();
}

// Returns 1 if the queue is full, otherwise returns 0. 
template <typename T, typename QUEUE>
bool 
STLQueue_Adapter<T, QUEUE>::is_full (void) const
{
  return false;
}

// Returns the current number of elements in the queue.
template <typename T, typename QUEUE>
size_t 
STLQueue_Adapter<T, QUEUE>::size (void) const
{
  return queue_.size();
}

#endif /* _STLQUEUE_CPP */
