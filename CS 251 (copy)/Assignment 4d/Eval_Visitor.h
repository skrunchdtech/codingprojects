/* -*- C++ -*- */
#ifndef _Eval_Visitor_H
#define _Eval_Visitor_H

#include <stack>
#include "Visitor.h"
#include "Typedefs.h"

/**
 * @class Eval_Visitor is a subclass of Visitor
 * @brief Defines a Expression Evaluator - evaluates the expression represented
          by a tree in default order - post order
 */

class Eval_Visitor : public Visitor
{
public:

  ///Dtor
  virtual ~Eval_Visitor();
  
  /// Visit method for LEAF_NODE instances
  virtual void visit(const LEAF_NODE& node) ;

  /// Visit method for COMPOSITE_NEGATE_NODE instances
  virtual void visit(const COMPOSITE_NEGATE_NODE& node);

  /// Visit method for COMPOSITE_ADD_NODE instances
  virtual void visit(const COMPOSITE_ADD_NODE& node);

  /// Visit method for COMPOSITE_SUBTRACT_NODE instances
  virtual void visit(const COMPOSITE_SUBTRACT_NODE& node);

  /// Visit method for COMPOSITE_MULTIPLY_NODE instances
  virtual void visit(const COMPOSITE_MULTIPLY_NODE& node);

  /// Visit method for COMPOSITE_DIVIDE_NODE instances
  virtual void visit(const COMPOSITE_DIVIDE_NODE& node);

  int yield();

protected:
  std::stack<int> stack_;
};

/**
 * @class Post_Order_Eval_Visitor is a subclass of Eval_Visitor
 * @brief Defines a Expression Evaluator - evaluates the expression represented
          by a tree in Post order.
*/

class Post_Order_Eval_Visitor : public Eval_Visitor
{
public:
  ///Ctor
  Post_Order_Eval_Visitor();

  ///Dtor
  virtual ~Post_Order_Eval_Visitor();
};

/**
 * @class Post_Order_Eval_Visitor is a subclass of Eval_Visitor
 * @brief Defines a Expression Evaluator - evaluates the expression represented
          by a tree in Post order.
*/

class Pre_Order_Eval_Visitor : public Eval_Visitor
{
public:

  ///Ctor
  Pre_Order_Eval_Visitor();

  ///Dtor
  virtual ~Pre_Order_Eval_Visitor();

  /// Visit method for COMPOSITE_SUBTRACT_NODE instances
  virtual void visit(const COMPOSITE_SUBTRACT_NODE& node);

  /// Visit method for COMPOSITE_DIVIDE_NODE instances
  virtual void visit(const COMPOSITE_DIVIDE_NODE& node);
};

#endif /* _Eval_Visitor_H */
