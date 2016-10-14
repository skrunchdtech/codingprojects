/* -*- C++ -*- */

/***************************************
Class: CS251
Assignment Number: 4b
Honor Pledge: I pledge that I have not recieved nor given help on this assignment.
***************************************/

#if !defined (_Tree_Factory_Impl_CPP)
#define _Tree_Factory_Impl_CPP

#include "Tree_Factory_Impl.h"
//#include "Traversal_Strategy_Impl.h"

// Tree_Factory_Impl Constructor.
Tree_Factory_Impl::Tree_Factory_Impl ()
  : use_(1)
{
}

// Tree_Factory_Impl Destructor.
Tree_Factory_Impl::~Tree_Factory_Impl ()
{
}

// Constructor.
Binary_Tree_Factory_Impl::Binary_Tree_Factory_Impl ()
{
}

// Destructor
Binary_Tree_Factory_Impl::~Binary_Tree_Factory_Impl (void)
{
}

// Constructor.
/*Traversal_Strategy
Binary_Tree_Factory_Impl::make_traversal_strategy (const std::string &name)
{
    if (name == "Level")
        return new Level_Order_Traversal_Strategy;
   
    else if (name == "Preorder")
        return new Pre_Order_Traversal_Strategy;
    
    else if (name == "Postorder")
        return new Post_Order_Traversal_Strategy;
    
    else if (name == "Inorder")
        return new In_Order_Traversal_Strategy;
    
    else
    {
        throw Traversal_Strategy_Impl::Unknown_Strategy(name);
    }
}*/

// Create the binary tree.
TREE
Binary_Tree_Factory_Impl::make_tree ()
{
  //             *
  //        /         \
  //      +             -
  //    /   \         /   \
  //  1       5     7       9
  // 
  // Make/return an expression tree that matches what's shown above.

    NODE *nodeptr1 = new NODE ('1');
    NODE *nodeptr2 = new NODE ('5');
    NODE *nodeptr3 = new NODE ('+', nodeptr1, nodeptr2);
    NODE *nodeptr4 = new NODE ('7');
    NODE *nodeptr5 = new NODE ('9');
    NODE *nodeptr6 = new NODE ('-', nodeptr4, nodeptr5);
    return TREE ('*', nodeptr3, nodeptr6);
}

#endif /* _Tree_Factory_Impl_CPP */
