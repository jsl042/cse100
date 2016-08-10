#ifndef BST_HPP
#define BST_HPP
#include "BSTNode.hpp"
#include "BSTIterator.hpp"
#include <utility> // for std::pair

/** //TODO: list real name(s) and login name(s) 
 *  // of the author(s) of this assignment
 *
 * Terry Chu tjchu
 * Patrick Nguyen phn031
 */

template<typename Data>
class BST {

protected:

  /** Pointer to the root of this BST, or nullptr if the BST is empty */
  BSTNode<Data>* root;

  /** Number of Data items stored in this BST. */
  unsigned int isize;


public:

  /** iterator is an aliased typename for BSTIterator<Data>. */
  typedef BSTIterator<Data> iterator;

  /** Default constructor.
      Initialize an empty BST.
   */
  BST() : root(nullptr), isize(0)  {
  }


  /** Default destructor.
   *  It is virtual, to allow appropriate destruction of subclass objects.
   *  Delete every node in this BST.
   */ // TODO
  virtual ~BST() {
    clear(); //call clear() directly to delete all nodes    
  }

  /** Insert a Data item in the BST.
   *  Return a pair, with the pair's first member set to an
   *  iterator pointing to either the newly inserted element
   *  or to the equivalent element already in the set.
   *  The pair's second element is set to true
   *  if a new element was inserted or false if an
   *  equivalent element already existed.
   */ // TODO
  virtual std::pair<iterator,bool> insert(const Data& item) 
  {
    BSTNode<Data>* currPtr = root; //current pointer node set to root

    if(!root) //If theres no root, inserts new node as root
    {
      root = new BSTNode<Data>(item); //create the root node to insert
      isize++; //increase size of the BST
      return std::pair<iterator,bool>(iterator(root),true); //return pair
    }

    //while loop traversing through the BST
    while(true)     
    {
      //if the item is smaller than the data of current pointer
      if(item < currPtr->data)
      {
        /*if the current pointer's left child is null, 
        insert the node as left child*/
        if(currPtr->left == nullptr)
        {
          //set left child of current pointer to a new node with item's data
          currPtr->left = new BSTNode<Data>(item);
          
          //set the left child of the current pointer's parent to the current pointer 
          (currPtr->left)->parent = currPtr;
          isize++; //increase size of the BST

          /*return pair with first element as iterator pointing to the 
          inserted node and second element as boolean set as true*/
          return std::pair<iterator,bool>(iterator(currPtr->left), true);               
        }
        currPtr = currPtr->left; //update current pointer
        continue;  
      }
      
      //if the item is bigger than the data of current pointer
      else if(item > currPtr->data)
      { 
        /*if the current pointer's right child null,
        insert the node as right child*/
        if(currPtr->right == nullptr)
        {
          //set left child of current pointer to a new node with item's data
          currPtr->right = new BSTNode<Data>(item);

          //set the left child of the current pointer's parent to the current pointer 
          (currPtr->right)->parent = currPtr;

          isize++; //increase size of the BST

          /*return pair with first element as iterator pointing to the 
          inserted node and second element as boolean set as true*/
          return std::pair<iterator,bool>(iterator(currPtr->right), true); 
        }  
        currPtr = currPtr->right; //update current pointer
        continue;
      }
 
      /*The item already exists in the tree, return the pair with the iterator 
      and bool set false.*/
      else
      {
        /*return pair with first element as iterator pointing to the 
        already existing node and second element as boolean set as false*/
        return std::pair<iterator,bool>(iterator(currPtr), false); 
      }     
    }
  }



  /** Find a Data item in the BST.
   *  Return an iterator pointing to the item, or the end
   *  iterator if the item is not in the BST.
   */ // TODO
  iterator find(const Data& item) const 
  {
    //iterator returned by begin() called on the object
    iterator begin = this->begin();
    
    /*iterator returned by end() called on the object*/
    iterator end = this->end();
     
    /*if root in null, return end iterator because it's an empty BST */
    if(root == nullptr)
    {
      return end;
    } 

    /*traverse the BST while the begin iterator doesn't 
    equal to the end iterator*/
    while( begin != end)
    {
      /*if the begin node is equivalent to the argument node,
      return the begin iterator*/
      if( *begin == item)
      {
        return begin;
      }
      //to traverse the BST, increment the iterator to go to the next node
      ++begin;
    }

    /*return the end iterator which points past the last item in the BST
    after running the while loop because this means the node was not
    found in the BST.*/
    return end;
  }
  
  /** Return the number of items currently in the BST.
   */ // TODO
  unsigned int size() const {
    return isize;
  }

  /** Remove all elements from this BST, and destroy them,
   *  leaving this BST with a size of 0.
   */ // TODO
  void clear() 
  {
    clearHelper(root); //call the clear helper method
  }

  /** Return true if the BST is empty, else false.
   */ // TODO
  bool empty() const {
    //if the size is 0 then it's empty
    if(isize == 0)
    {
      return true;
    }

    //if size not 0, then it's not empty
    return false;
  }

  /** Return an iterator pointing to the first item in the BST.
   */ // TODO
  iterator begin() const {
    //call first() helper method with root as argument
    return BSTIterator<Data>(first(root));
  }

  /** Return an iterator pointing past the last item in the BST.
   */
  iterator end() const {
    return typename BST<Data>::iterator(nullptr);
  }

  /** Helper method to be called in begin().
   */
  private:
  static BSTNode<Data>* first(BSTNode<Data>* n)
  {
    //if the node is null, return nullptr
    if(!n)
    {
      return nullptr;
    }

    //while the node's left child exists, update the node to its left child
    while(n->left)
    {
      n = n->left;
    }

    return n; //return the node
  }

  //Helper function to be called in clear().
  void clearHelper(BSTNode<Data>* x)
  { 
    /*if the argument node is not null, call the clearHelper() recursively to
    keep traversing through the left and right of the BST*/
    if( x != NULL)
    {
      clearHelper(x->left);
      clearHelper(x->right);
      delete x; //clear memory of argument node
      x = nullptr; //set the argument ndoe to nullptr
      isize--; //decrement the size of the BST for every recursion
    }
    return; //return nothing because it's void method 
  }
};


#endif //BST_HPP
