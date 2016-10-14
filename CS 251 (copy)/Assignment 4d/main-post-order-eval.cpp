#include <iostream>
#include <memory>
#include <algorithm>
#include <string>
#include <vector>

#include "Tree.h"
#include "Options.h"
#include "Interpreter.h"
#include "Eval_Visitor.h"

struct acceptor
{
  acceptor (Visitor &v): visitor_ (v) {}

  void operator()(TREE t)
  {
    t.accept (visitor_);
  }

private:
  Visitor &visitor_;
};

int 
main (int argc, char *argv[])
{
  try 
    {
      // Create options class to parse command line options.
      std::auto_ptr<Options> options (Options::instance ());

      // Parse the command-line options. If the user requested help (via "-h"
      // or "-?") then print out the usage and return.
      if (!Options::instance ()->parse_args (argc, argv))
        return 0;

      std::cout << "--Testing options class (singleton)--\n\n";

      // Print out the options used.
      std::cout << "  traversal option: " << options->traversal_strategy ()
                << std::endl;
      std::cout << "  queue option: " << options->queue_type ()
                << std::endl << std::endl;

      Interpreter_Context context;
      Interpreter interpreter;

      std::cout << "Please enter an expression..: " << std::endl;

      std::string input;
      std::getline (std::cin, input);

      // Use the Interpreter to create the TREE.
      TREE root_node = interpreter.interpret (context, input);

      std::cout << "Testing the Eval_Visitor: " << std::endl;

      Post_Order_Eval_Visitor visitor;

      std::for_each (root_node.begin ("Postorder"),
                     root_node.end ("Postorder"),
                     acceptor (visitor));

      std::cout << std::endl << "yield of the tree = " << visitor.yield () << std::endl;
    }
  catch (...)
    {
      std::cout << "some exception occurred" << std::endl;
    }

  return 0;
}
