/* -*- C++ -*- */

/***************************************
Class: CS251
Assignment Number: 4b
Honor Pledge: I pledge that I have not recieved nor given help on this assignment.
***************************************/

#if !defined (_Traversal_Strategy_Impl_CPP)
#define _Traversal_Strategy_Impl_CPP

#include <iostream>

#include "Traversal_Strategy_Impl.h"
#include "Options.h"
#include "Node.h"
#include "Queue.h"
#include "Typedefs.h"

// Size for the AQueue.
const size_t AQUEUE_SIZE = 80;

// Default ctor - needed for reference counting.
Traversal_Strategy_Impl::Traversal_Strategy_Impl ()
  : use_ (1)
{
}

// This needs to be virtual so that subclasses are correctly destroyed.
Traversal_Strategy_Impl::~Traversal_Strategy_Impl ()
{
}

// Ctor
Level_Order_Traversal_Strategy::Level_Order_Traversal_Strategy ()
  : queue_(make_queue_strategy (Options::instance()->queue_type ()))
{
}

// Dtor
Level_Order_Traversal_Strategy::~Level_Order_Traversal_Strategy ()
{
  // auto_ptr takes care of queue deletion
}

// Traverse the tree in level order.
void
Level_Order_Traversal_Strategy::traverse (const TREE &root)
{

    queue_->enqueue(root);

    while(!queue_->is_empty())
    {
        if(!queue_->front().is_null())
        { 
            std::cout << queue_->front().item();
            queue_->enqueue(queue_->front().left());
            queue_->enqueue(queue_->front().right());       
        } 
        
        queue_->dequeue();
    }

}

// A Factory method for creating queues.
QUEUE *
Level_Order_Traversal_Strategy::make_queue_strategy (const std::string &queue_type)
{
    if (queue_type == "LQueue")
        return new LQUEUE_ADAPTER(AQUEUE_SIZE); //use new to place on heap
    else if (queue_type == "AQueue")
        return new AQUEUE_ADAPTER(AQUEUE_SIZE);
}

// Traverse the tree in preorder.
void
Pre_Order_Traversal_Strategy::traverse (const TREE &root)
{
    if(!root.is_null())
    {
        std::cout<<root.item();

        if(!root.left().is_null())
            traverse(root.left());

        if(!root.right().is_null())
            traverse(root.right());
    }
}

// Traverse the tree in postorder.
void
Post_Order_Traversal_Strategy::traverse (const TREE &root)
{
    if(!root.is_null())
    {
        if(!root.left().is_null())
        traverse(root.left());

        if(!root.right().is_null())
        traverse(root.right());

        std::cout<<root.item();
    }
}

// Traverse the tree in inorder.
void
In_Order_Traversal_Strategy::traverse (const TREE &root)
{
    if(!root.is_null())
    {

        if(!root.left().is_null())
            traverse(root.left());

        std::cout<<root.item();

        if(!root.right().is_null())
            traverse(root.right());


    }
}

// Traverse the tree in inorder.
void
Null_Traversal_Strategy::traverse (const TREE &)
{
  // no-op
}

#endif /* _Traversal_Strategy_Impl_CPP */
