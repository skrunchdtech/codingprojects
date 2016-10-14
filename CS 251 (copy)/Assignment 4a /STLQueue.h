/* -*- C++ -*- */

/***************************************
Class: CS251
Assignment Number: 4a
Honor Pledge: I pledge that I have not recieved nor given help on this assignment.
***************************************/

/* -*- C++ -*- */
#if !defined (_STLQUEUE_H)
#define _STLQUEUE_H

#include <queue>
#include <stdlib.h>

template <typename T, typename QUEUE = std::queue<T> >
class STLQueue_Adapter
{
public:
  // = Exceptions thrown by methods in this class.
  class Underflow {};
  class Overflow {};

  // Constructor.
  STLQueue_Adapter (size_t size);

  // Copy constructor.
  STLQueue_Adapter (const STLQueue_Adapter<T, QUEUE> &rhs);

  // Assignment operator.
  STLQueue_Adapter<T, QUEUE> &operator= (const STLQueue_Adapter<T, QUEUE> &rhs);

  // Place a <new_item> at the tail of the queue.  Throws the
  // <Overflow> exception if the queue is full, e.g., if memory is
  // exhausted.
  void enqueue (const T &new_item);

  // Remove the front item on the queue.  Throws the <Underflow>
  // exception if the queue is empty.
  void dequeue (void);

  // Returns the front queue item without removing it. 
  // Throws the <Underflow> exception if the queue is empty. 
  T front (void) const;

  // = Check boundary conditions for Queue operations. 

  // Returns 1 if the queue is empty, otherwise returns 0. 
  bool is_empty (void) const;

  // Returns 1 if the queue is full, otherwise returns 0. 
  bool is_full (void) const;

  // Returns the current number of elements in the queue.
  size_t size (void) const;

private:
  // Instance of an STL queue.
  // You fill in here.
  QUEUE queue_;
};

#include "STLQueue.cpp"

#endif /* _STDQUEUE_H */
