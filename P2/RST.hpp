/* 
 * Terry Chu tjchu 
 * Patrick Nguyen phn031
 */

#ifndef RST_HPP
#define RST_HPP
#include "BST.hpp"
#include "BSTIterator.hpp"
#include "BSTNode.hpp"
#include <utility>
#include <cstdlib>
#include <ctime>

template <typename Data> class RST : public BST<Data> {

public:
 
 virtual std::pair<typename BST<Data>::iterator,bool> insert(const Data& item) 
 { // TODO: implement this function!
   
    int priority = rand(); //Genrate random priority with rand()

    //Insert the newNode w/ the usual BST insertion algorithm
    std::pair<typename BST<Data>::iterator,bool> pair=  
    BST<Data>::insert(item); 

    //Dereference the pair to access the node
    BSTNode<Data>* newNode = (pair.first).curr;
   
    //if boolean in pair is false then the Item data wasn't inserted successfully. Return the pair immediately before executing the while loop
    if((pair.second) == false) 
    {
      return pair;
    }
    
    //set member variable info to randomly generated priority 
    newNode->info = priority;

    /*if the inserted node's priority is less than its parent
      and bigger than its children's, then the RST already has its heap 
      property and do not need to be altered.*/
    if( (newNode->parent != NULL) && (newNode->info < newNode->parent->info))
    {
      return pair;
    }  
    
    /* Keep rotating while the inserted node's priority is greater than its
       parent's priority*/
    while(newNode->parent != NULL && newNode->parent->info <  newNode->info)
    {
      /*if it's a left child
      call right rotation*/
      if(newNode->parent->left == newNode)
      {
        this->rotateWithLeftChild(newNode->parent); 
      }   
      /*if it's a right child
        call left rotation*/
      else if(newNode->parent->right == newNode)
      {
        this->rotateWithRightChild(newNode->parent);
      }
    }

    //return pair  
    return pair;
 }

private:
  //Private helper method for right rotation
  BSTNode<Data>* rotateWithLeftChild( BSTNode<Data>* x)
  {
    //create BSTNode copy of the left child of x node
    BSTNode<Data>* l = x->left;

    //left child of x becomes the right child of its left child 
    x->left = l->right;
     
    // if x's left child exists, its parent is x 
    if( x->left != NULL)
      x->left->parent = x;

    //if x's parent exists check the key values to ensure BST property
    if( x->parent != NULL)
    { 
      /*if x's parent key value larger than left child's, 
      make its right child become the left child*/
      if( (x->parent->data) < (l->data) )
        x->parent->right = l;
      //else, x's parent's right child is x's left child
      else
        x->parent->left = l;
    }
    //if no parent, then it's root. set the left child to be root
    else{
      this->root = l;
    }

    l->parent = x->parent; //l parent pointer becomes x's parent
    x->parent = l; //x's parent pointer become l
    l->right = x; //l's right child pointer become x
    return l;
  }


  BSTNode<Data>* rotateWithRightChild(BSTNode<Data>* x)
  {
    //create BSTNode copy of the right child of x node
    BSTNode<Data>* r = x->right;

    //right child of x becomes the left child of its right child 
    x->right = r->left;

    // if x's right child exists, its parent is x 
    if( x->right != NULL )
      x->right->parent = x;

    //if x's parent exists, check the key values to ensure BST property
    if( x->parent )
    {  
      /*if x's parent key value larger than right child's,
      make its left child become the right child*/
      if( (x->parent->data) < (r->data) )
        x->parent->right = r;

      //else, x's parent's left child become r
      else
        x->parent->left = r;
    }
     
    //if no parent, then it's the root. set left child to be root
    else{
      this->root = r;
    }

    r->parent = x->parent;
    x->parent = r;
    r->left = x;
    return r;
 }
};
#endif // RST_HPP
