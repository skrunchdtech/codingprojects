#############################################################################
#
#  makefile for tree traversal
#
#############################################################################
#
#  If you move this makefile, update the variable below
#  or else depend won't work.
#
#############################################################################

MAKEFILE	= Makefile
CC		= g++
CFILES		= main-pre-order-eval.cpp main-post-order.cpp Interpreter.cpp LQueue.cpp AQueue.cpp Array.cpp Queue.cpp getopt.cpp Options.cpp  Visitor.cpp Print_Vistor.cpp Eval_Visitor.cpp 
HFILES		= Interpreter.h LQueue.h AQueue.h Array.h Queue.h getopt.h Queue.h Options.h Typedefs.h  Tree.h Node.h Visitor.h Print_Visitor.h Eval_Visitor.h 
OFILESPRE	= main-pre-order-eval.o LQueue.o AQueue.o Array.o getopt.o Queue.o Options.o Visitor.o Print_Visitor.o Eval_Visitor.o Interpreter.o
OFILESPOST	= main-post-order-eval.o LQueue.o AQueue.o Array.o getopt.o Queue.o Options.o Visitor.o Print_Visitor.o Eval_Visitor.o Interpreter.o


#############################################################################
# Flags for Installation
#############################################################################
BINDIR		= .
#############################################################################

DFLAGS		= -ggdb
IFLAGS          = 
OPTFLAGS	=  # Enable this flag if compiler supports templates...
LDFLAGS		= -g
CFLAGS		= $(IFLAGS) $(OPTFLAGS) $(DFLAGS)

#############################################################################
# G++ directives
#############################################################################
.SUFFIXES: .C .cpp
.cpp.o:
	$(CC) $(CFLAGS) -c $<
#############################################################################

all: tree-traversal-pre tree-traversal-post

tree-traversal-pre: $(OFILESPRE)
	$(CC) $(LDFLAGS) $(OFILESPRE) -o $@

tree-traversal-post: $(OFILESPOST)
	$(CC) $(LDFLAGS) $(OFILESPOST) -o $@


clean:
	/bin/rm -f *.o *.out *~ core

realclean: clean
	/bin/rm -rf tree-traversal-pre 
	/bin/rm -rf tree-traversal-post 

depend:
	g++dep -f $(MAKEFILE) $(CFILES)

# DO NOT DELETE THIS LINE -- g++dep uses it.
# DO NOT PUT ANYTHING AFTER THIS LINE, IT WILL GO AWAY.

main-pre-order-eval.o: main-pre-order-eval.cpp Tree.h Component_Node.h \
 Component_Node.cpp Leaf_Node.h Leaf_Node.cpp Composite_Unary_Node.h\
 Composite_Unary_Node.cpp Composite_Negate_Node.h Composite_Negate_Node.cpp\
 Composite_Binary_Node.h Composite_Binary_Node.cpp Composite_Add_Node.h\
 Composite_Add_Node.cpp Composite_Subtract_Node.h Composite_Subtract_Node.cpp\
 Composite_Multiply_Node.h Composite_Multiply_Node.cpp Composite_Divide_Node.h\
 Composite_Divide_Node.cpp Typedefs.h Tree.cpp\
 Tree_Iterator.h Options.h Options.cpp Visitor.cpp

main-post-order-eval.o: main-post-order-eval.cpp Tree.h Component_Node.h \
 Component_Node.cpp Leaf_Node.h Leaf_Node.cpp Composite_Unary_Node.h\
 Composite_Unary_Node.cpp Composite_Negate_Node.h Composite_Negate_Node.cpp\
 Composite_Binary_Node.h Composite_Binary_Node.cpp Composite_Add_Node.h\
 Composite_Add_Node.cpp Composite_Subtract_Node.h Composite_Subtract_Node.cpp\
 Composite_Multiply_Node.h Composite_Multiply_Node.cpp Composite_Divide_Node.h\
 Composite_Divide_Node.cpp Typedefs.h Tree.cpp\
 Tree_Iterator.h Options.h Options.cpp Visitor.cpp

 
Interpreter.o: Interpreter.cpp Tree.h Component_Node.h \
 Component_Node.cpp Leaf_Node.h Leaf_Node.cpp Composite_Unary_Node.h\
 Composite_Unary_Node.cpp Composite_Negate_Node.h Composite_Negate_Node.cpp\
 Composite_Binary_Node.h Composite_Binary_Node.cpp Composite_Add_Node.h\
 Composite_Add_Node.cpp Composite_Subtract_Node.h Composite_Subtract_Node.cpp\
 Composite_Multiply_Node.h Composite_Multiply_Node.cpp Composite_Divide_Node.h\
 Composite_Divide_Node.cpp Typedefs.h Tree.cpp Visitor.cpp

getopt.o: getopt.cpp
Options.o: Options.cpp Options.h getopt.h
Visitor.o:  Visitor.cpp
Print_Visitor.o: Print_Visitor.cpp
Eval_Visitor.o: Eval_Visitor.cpp 


# IF YOU PUT ANYTHING HERE IT WILL GO AWAY
