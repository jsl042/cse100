#ifndef BSTNODE_HPP
#define BSTNODE_HPP
#include <iostream>
#include <iomanip>

/** //TODO: list real name(s) and login name(s) 
 *  // of the author(s) of this assignment
 *
 *  Terry Chu tjchu
 *  Patrick Ngyen phn031 
 *
 */


/** This class template defines a node type for the BST container.
 *  Note that all members are public. So, the BST implementation should
 *  take care not to expose any BSTNode objects.
 */
template<typename Data>
class BSTNode {

public:

  /** Member variables. */
  BSTNode<Data>* parent;
  BSTNode<Data>* left;
  BSTNode<Data>* right;
  const Data data;  // the const Data in this node
  int info;  // variable used in advanced algorithms 

  /** Constructor.  Initialize a BSTNode with the given Data item,
   *  no parent, and no children.
   */
  BSTNode(const Data & d): data(d) {
    left = right = parent = nullptr;
  }


  /** Return the inorder successor of this BSTNode in a BST,
   *  or nullptr if none.
   *  PRECONDITION: this BSTNode is a node in a BST.
   *  POSTCONDITION:  the BST is unchanged.
   *  RETURNS: the BSTNode that is the inorder successor of this BSTNode,
   *  or nullptr if there is none.
   */ // TODO
  BSTNode<Data>* successor() const { 
    //if right child of the BSTNode exists
    if(this->right)
    {
      //return the node from the first() called on right child of the node 
      return first(this->right);
    }
    
    //if right child doesn't exist and the left one does
    else if( !(this->right) && ((this->parent)->left == this))
    {
      return parent; //return the parent  
    }
    
    //if right child doesn't exist and the node is right child of the parent
    else if( !(this->right) && ((this->parent)->right == this))
    {
      //create constant currNode equal to the called node
      const BSTNode<Data>* currNode = this;

      //create a currParent node
      BSTNode<Data>* currParent;

      //set currParent node to the parent of the calle node
      currParent = currNode->parent;

      /*while currParent is not null and the 
      right child of currParent is currNode, traverse throug thre BST*/
      while(currParent && currParent->right == currNode)
      {
        currNode = currParent;
        currParent = currNode->parent;
      }
      return currParent;
    }
    else
    {
      return nullptr;
    } 
  }

  private:
  //Helper function to call in successor
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
    return n;
  }
}; 

/** Overload operator<< to insert a BSTNode's fields in an ostream. */
template <typename Data>
std::ostream & operator<<(std::ostream& stm, const BSTNode<Data> & n) {
  stm << '[';
  stm << std::setw(10) << &n;                 // address of the BSTNode
  stm << "; p:" << std::setw(10) << n.parent; // address of its parent
  stm << "; l:" << std::setw(10) << n.left;   // address of its left child
  stm << "; r:" << std::setw(10) << n.right;  // address of its right child
  stm << "; i:" << std::setw(10) << n.info;   // its info field
  stm << "; d:" << n.data;                    // its data field
  stm << ']';
  return stm;
}

#endif // BSTNODE_HPP
