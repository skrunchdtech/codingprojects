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
CFILES		= main.cpp LQueue.cpp AQueue.cpp Array.cpp Queue.cpp getopt.cpp Tree_Factory_Impl.cpp Options.cpp  Visitor.cpp Print_Visitor.cpp Tree_Factory.cpp
HFILES		= LQueue.h AQueue.h Array.h Queue.h getopt.h Queue.h Tree_Factory_Impl.h Options.h Typedefs.h  Tree.h Node.h Visitor.h Print_Visitor.h Tree_Factory.h Refcounter.h
OFILES		= main.o getopt.o Tree_Factory_Impl.o Options.o Visitor.o Print_Visitor.o Tree_Factory.o

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

all: tree-traversal

tree-traversal: $(OFILES)
	$(CC) $(LDFLAGS) $(OFILES) -o $@

clean:
	/bin/rm -f *.o *.out *~ core

realclean: clean
	/bin/rm -rf tree-traversal

depend:
	g++dep -f $(MAKEFILE) $(CFILES)

# DO NOT DELETE THIS LINE -- g++dep uses it.
# DO NOT PUT ANYTHING AFTER THIS LINE, IT WILL GO AWAY.

main.o: main.cpp Tree.h Node.h Node.cpp Visitor.h Typedefs.h Refcounter.h \
  Tree_Iterator.h Tree_Iterator_Impl.h Queue.h Queue.cpp LQueue.h \
  LQueue.cpp AQueue.h Array.h scoped_array.h Array.cpp Array.inl \
  AQueue.cpp Options.h Tree_Iterator_Impl.cpp Tree_Iterator.cpp Tree.cpp \
  Tree_Factory.h Tree_Factory_Impl.h Print_Visitor.h
LQueue.o: LQueue.cpp LQueue.h LQueue.cpp
AQueue.o: AQueue.cpp AQueue.h Array.h scoped_array.h Array.cpp Array.inl \
  AQueue.cpp
Array.o: Array.cpp Array.h scoped_array.h Array.cpp Array.inl
Queue.o: Queue.cpp Queue.h Queue.cpp
getopt.o: getopt.cpp
Tree_Factory_Impl.o: Tree_Factory_Impl.cpp Tree_Factory_Impl.h Tree.h \
  Node.h Node.cpp Visitor.h Typedefs.h Refcounter.h Tree_Iterator.h \
  Tree_Iterator_Impl.h Queue.h Queue.cpp LQueue.h LQueue.cpp AQueue.h \
  Array.h scoped_array.h Array.cpp Array.inl AQueue.cpp Options.h \
  Tree_Iterator_Impl.cpp Tree_Iterator.cpp Tree.cpp
Options.o: Options.cpp Options.h getopt.h LQueue.h LQueue.cpp Tree.h \
  Node.h Node.cpp Visitor.h Typedefs.h Refcounter.h Tree_Iterator.h \
  Tree_Iterator_Impl.h Queue.h Queue.cpp AQueue.h Array.h scoped_array.h \
  Array.cpp Array.inl AQueue.cpp Tree_Iterator_Impl.cpp Tree_Iterator.cpp \
  Tree.cpp
Visitor.o: Visitor.cpp Visitor.h Typedefs.h
Print_Visitor.o: Print_Visitor.cpp Print_Visitor.h Visitor.h Typedefs.h \
  Tree.h Node.h Node.cpp Refcounter.h Tree_Iterator.h \
  Tree_Iterator_Impl.h Queue.h Queue.cpp LQueue.h LQueue.cpp AQueue.h \
  Array.h scoped_array.h Array.cpp Array.inl AQueue.cpp Options.h \
  Tree_Iterator_Impl.cpp Tree_Iterator.cpp Tree.cpp
Tree_Factory.o: Tree_Factory.cpp Tree_Factory.h Refcounter.h \
  Tree_Factory_Impl.h Tree.h Node.h Node.cpp Visitor.h Typedefs.h \
  Tree_Iterator.h Tree_Iterator_Impl.h Queue.h Queue.cpp LQueue.h \
  LQueue.cpp AQueue.h Array.h scoped_array.h Array.cpp Array.inl \
  AQueue.cpp Options.h Tree_Iterator_Impl.cpp Tree_Iterator.cpp Tree.cpp

# IF YOU PUT ANYTHING HERE IT WILL GO AWAY
