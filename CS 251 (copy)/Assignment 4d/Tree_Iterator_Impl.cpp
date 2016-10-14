/* -*- C++ -*- */
#if !defined (_Tree_Iterator_Impl_CPP)
#define _Tree_Iterator_Impl_CPP

#include "Tree_Iterator_Impl.h"
#include <iostream>
#include "AQueue.h"
#include "LQueue.h"

// Size for the AQueue.
const size_t AQUEUE_SIZE = 80;

// Default ctor - needed for reference counting.
template <typename T>
Tree_Iterator_Impl<T>::Tree_Iterator_Impl ()
  : use_ (1)
{
}

template <typename T>
Tree_Iterator_Impl<T>::Tree_Iterator_Impl (Tree<T> &tree)
  : use_ (1)
{
}


// This needs to be virtual so that subclasses are correctly destroyed.
template <typename T>
Tree_Iterator_Impl<T>::~Tree_Iterator_Impl ()
{
}

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
    //throw copy 
        throw std::string(queue_type);
}

// Ctor
template <typename T>
Level_Order_Tree_Iterator_Impl<T>::Level_Order_Tree_Iterator_Impl()
  : queue_(make_queue_strategy  
    (Options::instance   ()->queue_type ())),
    level_tree_(),
    root_()
{
}

// Ctor
template <typename T>
Level_Order_Tree_Iterator_Impl<T>::Level_Order_Tree_Iterator_Impl (Tree<T> &tree)
  : queue_(make_queue_strategy (Options::instance
    ()->queue_type ())),
    level_tree_(tree),
    root_(tree)
{
   if(!level_tree_.is_null())  
        queue_->enqueue(level_tree_);
}

// Ctor
template <typename T>
Level_Order_Tree_Iterator_Impl<T>::Level_Order_Tree_Iterator_Impl(
	const Level_Order_Tree_Iterator_Impl<T>& rhs)
  : queue_(Copy_Queue(rhs)),
    level_tree_(rhs.level_tree_),
    root_(rhs.root_)
{
 
}

template <typename T>
Level_Order_Tree_Iterator_Impl<T>::~Level_Order_Tree_Iterator_Impl(void)
{
  //The queue is held in an auto_ptr which will call the destructor
  //when moving out of scope
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

// Ctor
template <typename T>
Pre_Order_Tree_Iterator_Impl<T>::Pre_Order_Tree_Iterator_Impl():
  dummy_(),
    cur_(dummy_)// You fill in here.
{
  //No tree so don't do anything
}

// Ctor
template <typename T>
Pre_Order_Tree_Iterator_Impl<T>::Pre_Order_Tree_Iterator_Impl
(Tree<T> &tree):
  dummy_(),
    cur_(dummy_)// You fill in here.
{
    if (!tree.is_null())
    {
      //stack_.clear();

      populateStack(tree);
		
      cur_ = stack_.top();//use the newly defined operator=
    }
}

// Ctor
template <typename T>
Pre_Order_Tree_Iterator_Impl<T>::Pre_Order_Tree_Iterator_Impl(
	const Pre_Order_Tree_Iterator_Impl<T>& rhs):
  dummy_(),
  cur_(dummy_),//the current node is assigned the  dummy node
  stack_(rhs.stack_)
{
  if (!stack_.empty())
    cur_ = stack_.top();//use the newly defined operator=
}


template <typename T>
Pre_Order_Tree_Iterator_Impl<T>::~Pre_Order_Tree_Iterator_Impl(void)
{
}

template <typename T>
Tree<T>& Pre_Order_Tree_Iterator_Impl<T>::operator* (void)
{
 //1) cur is used here to respect the compiler warning of returning 
  // temporary object when queue->front was returned
  //2) This makes it simple to return cur which contains either
  // stack_.top or the dummy node based on the circumstances
  return (cur_);//return the content of cur
}

template <typename T>
const Tree<T>& Pre_Order_Tree_Iterator_Impl<T>::operator* (void) const
{
 //1) cur is used here to respect the compiler warning of returning 
  // temporary object when queue->front was returned
  //2) This makes it simple to return cur which contains either
  // stack_.top or the dummy node based on the circumstances
  return (cur_);//return the content of cur
}

template <typename T>
Pre_Order_Tree_Iterator_Impl<T>& 
Pre_Order_Tree_Iterator_Impl<T>::operator++ (void)
{
  Tree<T> root = stack_.top();//get the top of the queue
  //check if the left and right nodes of the top node
  // are not null. If not, enqueue them
		
  stack_.pop();//remove the top element
		
  //set the cur entity based on the current state of the queue
  if (!stack_.empty())
    cur_ = stack_.top();
  else
    cur_ = dummy_;

  return (*this);
}

/// Equality operator
template <typename T>
bool Pre_Order_Tree_Iterator_Impl<T>::operator== 
(const Tree_Iterator_Impl<T> &rhs) const
{
  //dynamically cast the rhs to PreOrder_Tree_Iterator
  const Pre_Order_Tree_Iterator_Impl<T>* temp =
    dynamic_cast<const Pre_Order_Tree_Iterator_Impl<T>*>(&rhs);

  // cur is being compared here just for consistency with the rest of the
  // code. It is equivalent to comparing stack_.top when the stack's 
  // are not empty.
  // when either queue is empty, the above method won't work and additional
  // checks would be required for this.
  // using cur simplifies the code here.
  if(temp)//if the casting is valid
    {
      return (cur_==temp->cur_); // compare the two cur entries
      // which is equal to comparing the two
      // root node pointers

    }

  return false;
}

/// Nonequality operator
template <typename T>
bool Pre_Order_Tree_Iterator_Impl<T>::operator!= 
(const Tree_Iterator_Impl<T> &rhs) const
{
	return !((*this) == rhs);//use the operator==
}

//clone for post increment in the bridge class
template <typename T>
Pre_Order_Tree_Iterator_Impl<T>* 
Pre_Order_Tree_Iterator_Impl<T>::clone(void)
{
  return new Pre_Order_Tree_Iterator_Impl(*this); 
}

template <typename T> void 
Pre_Order_Tree_Iterator_Impl<T>::populateStack(Tree<T> tree)
{
  
  if (!tree.right().is_null())
    populateStack(tree.right());
  if (!tree.left().is_null())
    populateStack(tree.left());
  stack_.push(tree);
}

// Ctor
template <typename T>
Post_Order_Tree_Iterator_Impl<T>::Post_Order_Tree_Iterator_Impl():
    dummy_(),
    cur_(dummy_)
{
  //No need to do anything here since no tree is passed
}

// Ctor
template <typename T>
Post_Order_Tree_Iterator_Impl<T>::Post_Order_Tree_Iterator_Impl
(Tree<T> &tree):
  dummy_(),
  cur_(dummy_)//the current node is assigned the  dummy node
{
	
  if (!tree.is_null())
    {
      //stack_.clear();

      populateStack(tree);
		
      cur_ = stack_.top();//use the newly defined operator=
    }
}

// Ctor
template <typename T>
Post_Order_Tree_Iterator_Impl<T>::Post_Order_Tree_Iterator_Impl(
	const Post_Order_Tree_Iterator_Impl<T>& rhs):
  dummy_(),
  cur_(dummy_),//the current node is assigned the  dummy node
  stack_(rhs.stack_)
{
  if (!stack_.empty())
    cur_ = stack_.top();//use the newly defined operator=
}

template <typename T>
Post_Order_Tree_Iterator_Impl<T>::~Post_Order_Tree_Iterator_Impl(void)
{
}

template <typename T>
Tree<T>& Post_Order_Tree_Iterator_Impl<T>::operator* (void)
{
  //1) cur is used here to respect the compiler warning of returning 
  // temporary object when queue->front was returned
  //2) This makes it simple to return cur which contains either
  // stack_.top or the dummy node based on the circumstances
  return (cur_);//return the content of cur
}

template <typename T>
const Tree<T>& Post_Order_Tree_Iterator_Impl<T>::operator* (void) const
{
  //1) cur is used here to respect the compiler warning of returning 
  // temporary object when queue->front was returned
  //2) This makes it simple to return cur which contains either
  // stack_.top or the dummy node based on the circumstances
  return (cur_);//return the content of cur
}

template <typename T>
Post_Order_Tree_Iterator_Impl<T>& 
Post_Order_Tree_Iterator_Impl<T>::operator++ (void)
{
  Tree<T> root = stack_.top();//get the top of the queue
  //check if the left and right nodes of the top node
  // are not null. If not, enqueue them
		
  stack_.pop();//remove the top element
		
  //set the cur entity based on the current state of the queue
  if (!stack_.empty())
    cur_ = stack_.top();
  else
    cur_ = dummy_;

  return (*this);
}

/// Equality operator
template <typename T>
bool Post_Order_Tree_Iterator_Impl<T>::operator== 
(const Tree_Iterator_Impl<T> &rhs) const
{
  //dynamically cast the rhs to PreOrder_Tree_Iterator
  const Post_Order_Tree_Iterator_Impl<T>* temp =
    dynamic_cast<const Post_Order_Tree_Iterator_Impl<T>*>(&rhs);

  // cur is being compared here just for consistency with the rest of the
  // code. It is equivalent to comparing stack_.top when the stack's 
  // are not empty.
  // when either queue is empty, the above method won't work and additional
  // checks would be required for this.
  // using cur simplifies the code here.
  if(temp)//if the casting is valid
    {
      return (cur_==temp->cur_); // compare the two cur entries
      // which is equal to comparing the two
      // root node pointers

    }

  return false; 
}

/// Nonequality operator
template <typename T>
bool Post_Order_Tree_Iterator_Impl<T>::operator!= 
(const Tree_Iterator_Impl<T> &rhs) const
{
  return !((*this) == rhs);//use the operator==
}

//clone for post increment in the bridge class
template <typename T>
Post_Order_Tree_Iterator_Impl<T>* 
Post_Order_Tree_Iterator_Impl<T>::clone(void)
{
  return new Post_Order_Tree_Iterator_Impl(*this); 
}

template <typename T> void 
Post_Order_Tree_Iterator_Impl<T>::populateStack(Tree<T> tree)
{
  stack_.push(tree);
  if (!tree.right().is_null())
    populateStack(tree.right());
  if (!tree.left().is_null())
    populateStack(tree.left());
}

#endif /*_Tree_Iterator_Impl_CPP */
