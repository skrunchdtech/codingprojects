/***************************************
Class: CS251
Assignment Number: 3
Honor Pledge: I pledge that I have not recieved nor given help on this assignment.
***************************************/

#if !defined (_LQUEUE_CPP)
#define _LQUEUE_CPP

#include <functional>
#include <algorithm>
#include "LQueue.h"

/* static */
template <typename T> LQueue_Node<T> *
LQueue_Node<T>::free_list_ = 0;

// Allocate a new <LQueue_Node>, trying first from the
// <free_list_> and if that's empty try from the global <::operator
// new>.
//Operator new does not call system ::operator new does
template <typename T> void *
LQueue_Node<T>::operator new (size_t)
{
    if(free_list_ != 0)
    {
        //no need for static_cast because downcasting is implicit
        LQueue_Node<T> * temp = free_list_;
        free_list_ = free_list_->next_;
        return temp;
    }
    else
    {
        return ::operator new (sizeof(LQueue_Node<T>)); 
    }
    
}

// Return <ptr> to the <free_list_>.

template <typename T> void
LQueue_Node<T>::operator delete (void *ptr)
{
    LQueue_Node<T> * temp = free_list_;
    free_list_= static_cast<LQueue_Node <T>* > (ptr);
    free_list_-> next_ = temp;
}

// Returns all dynamic memory on the free list to the free store.

template <typename T> void
LQueue_Node<T>::free_list_release (void)
{
    while(free_list_ != 0)
    {   
        LQueue_Node<T> * temp = free_list_->next_;
        ::operator delete (free_list_);
        free_list_ = temp;           
    }
}

// Preallocate <n> <LQueue_Nodes> and store them on the
// <free_list_>.

template <typename T> void
LQueue_Node<T>::free_list_allocate (size_t n)
{
    for(size_t i = 0; i < n; ++i)
    {
        LQueue_Node<T> * temp = 
          static_cast<LQueue_Node <T> * > 
          (::operator new (sizeof(LQueue_Node<T>)));

        temp->next_ = free_list_;
        free_list_ = temp;
    }
}

template <typename T>
LQueue_Node<T>::LQueue_Node (LQueue_Node<T> *next,
                             LQueue_Node<T> *prev)
  : next_ (next),
    prev_ (prev)
{
    next_->prev_ = this;
    prev_->next_ = this;
}

template <typename T>
LQueue_Node<T>::LQueue_Node (void)
  // this is helpful to implement the dummy node in a concise way.
  : next_ (this),
    prev_ (this)
{
}

template <typename T>
LQueue_Node<T>::~LQueue_Node (void)
{
    next_->prev_ = prev_;
    prev_->next_ = next_;
}


// Returns the current size.
template<typename T, typename LQUEUE_NODE> size_t
LQueue<T, LQUEUE_NODE>::size (void) const
{
    return count_;
}

// Constructor.

template<typename T, typename LQUEUE_NODE> 
LQueue<T, LQUEUE_NODE>::LQueue (size_t size_hint)
  // Initialize fields here.
  : tail_ (new LQUEUE_NODE),
    count_ (0)
{
    //make sure trait doesn't need to be used
    LQUEUE_NODE::free_list_allocate (size_hint);
}

//functor that aids in copying nodes
template<typename T, typename LQUEUE_NODE>
class list_copier
{
public:
  list_copier (LQueue<T, LQUEUE_NODE>& queue)
    : queue_ (queue) {}

  void operator() (const T &item)
  {
    // Add a line that enqueues item into queue_
    queue_.enqueue(item);
  }

private:
    LQueue<T, LQUEUE_NODE>& queue_;
};

template<typename T, typename LQUEUE_NODE> void
LQueue<T, LQUEUE_NODE>::swap (LQueue<T, LQUEUE_NODE> &new_queue)
{
    std::swap(tail_, new_queue.tail_);
    
    std::swap(count_, new_queue.count_);
}

// Copy constructor.

template <typename T, typename LQUEUE_NODE>
LQueue<T, LQUEUE_NODE>::LQueue (const LQueue<T, LQUEUE_NODE> &rhs)
  // Initialize fields here.
  : tail_ (0), // tail_ will be set correctly by swap().
    count_ (0) // count_ will be set correctly by swap().
{
    LQueue<T, LQUEUE_NODE> temp;

    std::for_each (rhs.begin (), rhs.end (), list_copier<T, LQUEUE_NODE> 
        (temp));
    
    swap(temp);
}

// Assignment operator.
template <typename T, typename LQUEUE_NODE> LQueue<T, LQUEUE_NODE> &
LQueue<T, LQUEUE_NODE>::operator= (const LQueue<T, LQUEUE_NODE> &rhs) 
{
    if(this != &rhs)
    {
        LQueue<T, LQUEUE_NODE> temp (rhs);

        swap(temp);
    }

    return *this;
}

// Perform actions needed when queue goes out of scope.

template <typename T, typename LQUEUE_NODE>
LQueue<T, LQUEUE_NODE>::~LQueue (void)
{
    while(!is_empty())
    {
        dequeue_i();
    }
    
    delete tail_;
}

// Compare this queue with <rhs> for equality.  Returns true if the
// size()'s of the two queues are equal and all the elements from 0
// .. size() are equal, else false.

template <typename T, typename LQUEUE_NODE> bool 
LQueue<T, LQUEUE_NODE>::operator== (const LQueue<T, LQUEUE_NODE> &rhs) const
{
    return size() == rhs.size() && std::equal(begin(), end(), rhs.begin());
}

// Compare this queue with <rhs> for inequality such that <*this> !=
// <s> is always the complement of the boolean return value of
// <*this> == <s>.

template <typename T, typename LQUEUE_NODE> bool 
LQueue<T, LQUEUE_NODE>::operator!= (const LQueue<T, LQUEUE_NODE> &rhs) const
{
    return !(*this == rhs);
}

// Place a <new_item> at the tail of the queue.  Throws
// the <Overflow> exception if the queue is full.

template <typename T, typename LQUEUE_NODE> void
LQueue<T, LQUEUE_NODE>::enqueue (const T &new_item)
{
    try
    {
       tail_-> item_ = new_item; //put new item in tail_
       tail_ = new LQUEUE_NODE(tail_->next_, tail_);//tail_ points to new dummy
       ++count_;
    }
    catch(std::bad_alloc &)
    {
        throw Overflow();
    }
}

// Remove the front item on the queue without checking if the queue is empty.

template <typename T, typename LQUEUE_NODE> void
LQueue<T, LQUEUE_NODE>::dequeue_i (void)
{
    delete tail_->next_; //delete 
    --count_;
}

// Throws the <Underflow> exception if the queue is empty. 
template <typename T, typename LQUEUE_NODE> void
LQueue<T, LQUEUE_NODE>::dequeue (void)
{
    if(!is_empty())
    {
       dequeue_i();
    }
    else
    {
        throw Underflow();
    }
}

// Returns the front queue item without removing it. 
// Throws the <Underflow> exception if the queue is empty. 

template <typename T, typename LQUEUE_NODE> T 
LQueue<T, LQUEUE_NODE>::front (void) const
{
    if(!is_empty())
    {
        return tail_->next_->item_; //returns item in head node
    }
    else
    {
        throw Underflow();
    }
}

// Returns true if the queue is empty, otherwise returns false.

template <typename T, typename LQUEUE_NODE> bool
LQueue<T, LQUEUE_NODE>::is_empty (void) const 
{
    return count_ == 0;
}

// Returns true if the queue is full, otherwise returns false.

template <typename T, typename LQUEUE_NODE> bool
LQueue<T, LQUEUE_NODE>::is_full (void) const 
{
    return false;
}

// Get an iterator to the begining of the queue
template <typename T, typename LQUEUE_NODE> 
    typename LQueue<T, LQUEUE_NODE>::iterator
        LQueue<T, LQUEUE_NODE>::begin (void)
{
    return iterator(tail_->next_);
}

// Get an iterator pointing past the end of the queue
template <typename T, typename LQUEUE_NODE> 
    typename LQueue<T, LQUEUE_NODE>::iterator
        LQueue<T, LQUEUE_NODE>::end (void)
{
    return iterator(tail_);
}

// Get an iterator to the begining of the queue
template <typename T, typename LQUEUE_NODE> 
    typename LQueue<T, LQUEUE_NODE>::const_iterator
        LQueue<T, LQUEUE_NODE>::begin (void) const
{
    return const_iterator(tail_->next_);
}

// Get an iterator pointing past the end of the queue
template <typename T, typename LQUEUE_NODE> 
    typename LQueue<T, LQUEUE_NODE>::const_iterator
        LQueue<T, LQUEUE_NODE>::end (void) const
{
    return const_iterator(tail_);
}

// Get an iterator to the begining of the queue
template <typename T, typename LQUEUE_NODE> 
    typename LQueue<T, LQUEUE_NODE>::reverse_iterator
        LQueue<T, LQUEUE_NODE>::rbegin (void)
{
    return reverse_iterator(tail_->prev_);
}

// Get an iterator pointing past the end of the queue
template <typename T, typename LQUEUE_NODE> 
    typename LQueue<T, LQUEUE_NODE>::reverse_iterator
        LQueue<T, LQUEUE_NODE>::rend (void)
{
    return reverse_iterator(tail_);
}

// Get an iterator to the begining of the queue
template <typename T, typename LQUEUE_NODE> 
    typename LQueue<T, LQUEUE_NODE>::const_reverse_iterator
        LQueue<T, LQUEUE_NODE>::rbegin (void) const
{
    return const_reverse_iterator(tail_->prev_);
}

// Get an iterator pointing past the end of the queue
template <typename T, typename LQUEUE_NODE> 
    typename LQueue<T, LQUEUE_NODE>::const_reverse_iterator
        LQueue<T, LQUEUE_NODE>::rend (void) const
{
    return const_reverse_iterator(tail_);
}

template <typename T, typename LQUEUE_NODE> T &
LQueue_Iterator<T, LQUEUE_NODE>::operator* (void)
{
    return pos_->item_;
}

template <typename T, typename LQUEUE_NODE> const T &
LQueue_Iterator<T, LQUEUE_NODE>::operator* (void) const
{
    return pos_->item_;
}

template <typename T, typename LQUEUE_NODE> LQueue_Iterator<T, LQUEUE_NODE> &
LQueue_Iterator<T, LQUEUE_NODE>::operator++ (void) 
{
    pos_ = pos_->next_;
    return *this;
}

// Post-increment.
template <typename T, typename LQUEUE_NODE> LQueue_Iterator<T, LQUEUE_NODE> 
LQueue_Iterator<T, LQUEUE_NODE>::operator++ (int) 
{
    LQueue_Iterator<T, LQUEUE_NODE> temp(*this);
	++*this;
	return temp;
}

template <typename T, typename LQUEUE_NODE> LQueue_Iterator<T, LQUEUE_NODE> &
LQueue_Iterator<T, LQUEUE_NODE>::operator-- (void)
{
    pos_ = pos_->prev_;
    return *this;
}

// Post-increment.
template <typename T, typename LQUEUE_NODE> LQueue_Iterator<T, LQUEUE_NODE> 
LQueue_Iterator<T, LQUEUE_NODE>::operator-- (int) 
{
     LQueue_Iterator<T, LQUEUE_NODE> temp(*this);
	--*this;
	return temp;
}

template <typename T, typename LQUEUE_NODE> bool
LQueue_Iterator<T, LQUEUE_NODE>::operator== 
    (const LQueue_Iterator<T, LQUEUE_NODE> &rhs) const
{
    return rhs.pos_== pos_;
}

template <typename T, typename LQUEUE_NODE> bool
LQueue_Iterator<T, LQUEUE_NODE>::operator!= 
    (const LQueue_Iterator<T, LQUEUE_NODE> &rhs) const
{
    // implement != in terms of ==
    return !(*this == rhs);
}

template <typename T, typename LQUEUE_NODE>
LQueue_Iterator<T, LQUEUE_NODE>::LQueue_Iterator (LQUEUE_NODE *pos)
  : pos_ (pos)
{
}

template <typename T, typename LQUEUE_NODE> const T &
Const_LQueue_Iterator<T, LQUEUE_NODE>::operator* (void) const
{
    return pos_->item_;
}

template <typename T, typename LQUEUE_NODE> 
    const Const_LQueue_Iterator<T, LQUEUE_NODE> &
        Const_LQueue_Iterator<T, LQUEUE_NODE>::operator++ (void) const
{
    pos_ = pos_->next_;
    return *this;
}

template <typename T, typename LQUEUE_NODE> 
    Const_LQueue_Iterator<T, LQUEUE_NODE>
        Const_LQueue_Iterator<T, LQUEUE_NODE>::operator++ (int) const
{
    Const_LQueue_Iterator<T, LQUEUE_NODE> temp(*this);
	++*this;
	return temp;
}

template <typename T, typename LQUEUE_NODE> 
    const Const_LQueue_Iterator<T, LQUEUE_NODE> &
        Const_LQueue_Iterator<T, LQUEUE_NODE>::operator-- (void) const
{
    pos_ = pos_->prev_;
    return *this;
}

template <typename T, typename LQUEUE_NODE> 
    Const_LQueue_Iterator<T, LQUEUE_NODE>
        Const_LQueue_Iterator<T, LQUEUE_NODE>::operator-- (int) const
{
    Const_LQueue_Iterator<T, LQUEUE_NODE> temp(*this);
	--*this;
	return temp;
}

template <typename T, typename LQUEUE_NODE> bool
Const_LQueue_Iterator<T, LQUEUE_NODE>::operator== 
    (const Const_LQueue_Iterator<T, LQUEUE_NODE> &rhs) const
{
    return rhs.pos_ == pos_;
}

template <typename T, typename LQUEUE_NODE> bool
Const_LQueue_Iterator<T, LQUEUE_NODE>::operator!= 
    (const Const_LQueue_Iterator<T, LQUEUE_NODE> &rhs) const
{
    return !(*this == rhs);
}

template <typename T, typename LQUEUE_NODE>
Const_LQueue_Iterator<T, LQUEUE_NODE>::Const_LQueue_Iterator (LQUEUE_NODE *pos)
  : pos_ (pos)
{
}

template <typename T, typename LQUEUE_NODE> T &
LQueue_Reverse_Iterator<T, LQUEUE_NODE>::operator* (void)
{
    return pos_->item_;
}

template <typename T, typename LQUEUE_NODE> const T &
LQueue_Reverse_Iterator<T, LQUEUE_NODE>::operator* (void) const
{
    return pos_->item_;
}

template <typename T, typename LQUEUE_NODE> 
    LQueue_Reverse_Iterator<T, LQUEUE_NODE> &
        LQueue_Reverse_Iterator<T, LQUEUE_NODE>::operator++ (void) 
{
    pos_ = pos_->prev_;
    return *this;
}

// Post-increment.
template <typename T, typename LQUEUE_NODE> 
    LQueue_Reverse_Iterator<T, LQUEUE_NODE> 
        LQueue_Reverse_Iterator<T, LQUEUE_NODE>::operator++ (int) 
{
    LQueue_Reverse_Iterator<T, LQUEUE_NODE> temp(*this);
	++*this;
	return temp;
}

template <typename T, typename LQUEUE_NODE> 
    LQueue_Reverse_Iterator<T, LQUEUE_NODE> &
        LQueue_Reverse_Iterator<T, LQUEUE_NODE>::operator-- (void)
{
    pos_ = pos_->next_;
    return *this;
}

template <typename T, typename LQUEUE_NODE> 
    LQueue_Reverse_Iterator<T, LQUEUE_NODE>
        LQueue_Reverse_Iterator<T, LQUEUE_NODE>::operator-- (int)
{
    LQueue_Reverse_Iterator<T, LQUEUE_NODE> temp(*this);
	--*this;
	return temp;
}

template <typename T, typename LQUEUE_NODE> bool
LQueue_Reverse_Iterator<T, LQUEUE_NODE>::operator== 
    (const LQueue_Reverse_Iterator<T, LQUEUE_NODE> &rhs) const
{
    return rhs.pos_ == pos_;
}

template <typename T, typename LQUEUE_NODE> bool
LQueue_Reverse_Iterator<T, LQUEUE_NODE>::operator!= 
    (const LQueue_Reverse_Iterator<T, LQUEUE_NODE> &rhs) const
{
    // implement != in terms of ==
    return !(*this == rhs);
}

template <typename T, typename LQUEUE_NODE>
LQueue_Reverse_Iterator<T, LQUEUE_NODE>::
    LQueue_Reverse_Iterator (LQUEUE_NODE *pos)
        : pos_ (pos)
{}

template <typename T, typename LQUEUE_NODE> const T &
Const_LQueue_Reverse_Iterator<T, LQUEUE_NODE>::operator* (void) const
{
    return pos_->item_;
}

template <typename T, typename LQUEUE_NODE> 
    const Const_LQueue_Reverse_Iterator<T, LQUEUE_NODE> &
        Const_LQueue_Reverse_Iterator<T, LQUEUE_NODE>::operator++ (void) const
{
    pos_ = pos_->prev_;
    return *this;
}

template <typename T, typename LQUEUE_NODE> 
    Const_LQueue_Reverse_Iterator<T, LQUEUE_NODE>
        Const_LQueue_Reverse_Iterator<T, LQUEUE_NODE>::operator++ (int) const
{
    Const_LQueue_Reverse_Iterator<T, LQUEUE_NODE> temp(*this);
	++*this;
	return temp;
}

template <typename T, typename LQUEUE_NODE> 
    const Const_LQueue_Reverse_Iterator<T, LQUEUE_NODE> &
        Const_LQueue_Reverse_Iterator<T, LQUEUE_NODE>::operator-- (void) const
{
    pos_ = pos_->next_;
    return *this;
}

template <typename T, typename LQUEUE_NODE> 
    Const_LQueue_Reverse_Iterator<T, LQUEUE_NODE>
        Const_LQueue_Reverse_Iterator<T, LQUEUE_NODE>::operator-- (int) const
{
    Const_LQueue_Reverse_Iterator<T, LQUEUE_NODE> temp(*this);
	--*this;
	return temp;
}

template <typename T, typename LQUEUE_NODE> bool
Const_LQueue_Reverse_Iterator<T, LQUEUE_NODE>::operator== 
    (const Const_LQueue_Reverse_Iterator<T, LQUEUE_NODE> &rhs) const
{
    return rhs.pos_ == pos_;
}

template <typename T, typename LQUEUE_NODE> bool
Const_LQueue_Reverse_Iterator<T, LQUEUE_NODE>::operator!= 
    (const Const_LQueue_Reverse_Iterator<T, LQUEUE_NODE> &rhs) const
{
  return !(*this == rhs);
}

template <typename T, typename LQUEUE_NODE>
Const_LQueue_Reverse_Iterator<T, LQUEUE_NODE>::
    Const_LQueue_Reverse_Iterator (LQUEUE_NODE *pos)
        : pos_ (pos)
{
}

#endif /* _LQUEUE_CPP */
