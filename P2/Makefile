# A simple makefile for CSE 100 P2

#use g++ for everything
CC= g++  	

# include debugging symbols in object files,
# and enable all warnings
CXXFLAGS= -std=c++11 -g -Wall

#include debugging symbols in executable
LDFLAGS= -g	

rst: test_RST.o 
	g++ -o rst test_RST.o countint.cpp


bst: test_BST.o 
	g++ -o bst test_BST.o 

test_BST.o: BST.hpp BSTNode.hpp BSTIterator.hpp RST.hpp

benchtree: benchtree.o countint.o
	g++ -o benchtree benchtree.o countint.cpp

benchtree.o:BST.hpp BSTNode.hpp BSTIterator.hpp RST.hpp

test_RST.o: BST.hpp BSTNode.hpp BSTIterator.hpp RST.hpp countint.hpp 
 


