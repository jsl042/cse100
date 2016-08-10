/*
 * Terry Chu tjchu
 * Anthony Wong anw046
 */ 

#include "HCTree.hpp"
#include "BitOutputStream.hpp"
#include "BitInputStream.hpp"
#include <queue>
#include <stack>
#include <ostream>
#include <stdio.h>
#include <stdlib.h>
#include <bitset>

/**
 * Builds a Huffman coding trie with the HUffman algorithm. 
 */
void HCTree:: build(const vector<int>& freqs){
  std::priority_queue<HCNode*,std::vector<HCNode*>,HCNodePtrComp> pq;
  //Determine the count of each symbol in input msg
  int i = 0;
  //go through the freqs vector and access all existing symbols
  for(; i < 256; i++){
    if(freqs[i]){
      /*create newNode with currently accessed element in freqs as the 
      symbol of the node and the count as the current index in freqs*/
      HCNode* newNode = new HCNode(freqs[i], i);
      leaves[i] = newNode; //update the leaves vector
      pq.push(newNode); //push newNode into pq
    }
  }
  
  //if the pq size is only 1, insert in just one node
  if(pq.size()==1)
    pq.push(new HCNode(0,0));

  //if the pq is empty, create an root node
  if(pq.size() == 0){
    root = new HCNode(0,0);
    return;
  }  

  /*while the size is larger than 1, keep building the tree. This means
  that the building process will only end when there is a single tree*/
  while(pq.size()>=2){ 
    HCNode* N1 = pq.top(); //N1 is the top element of pq
    pq.pop(); //remove the top element
    HCNode* N2 = pq.top(); //N2 is the second top element of pq
    pq.pop(); //remove the second top element

    /*Create a parent node of N1 and N2 where the count is the 
    sum of the counts of N1 and N2*/
    HCNode* N3 = new HCNode((N1->count + N2->count),0, N1, N2, 0);
    
    //update parent pointer of N1 and N2 to N3
    N1->p = N3; 
    N2->p = N3;
    
    //insert N3 into pq
    pq.push(N3); 
  }
  //update the root of HCTree to the top element of pq
  root = pq.top();  
}

void HCTree::encode( byte symbol, BitOutputStream & out ) const{
       stack<bool> bitSequence;
       HCNode* node = leaves[symbol];
       
       while(node != root){
         //if node is a c1 child, add 1 (true) to bitSequence
         if(node->p->c1 == node)
           bitSequence.push(true);
         //else, node is a c0 child, add 0 (false) to bitSequence
         else
           bitSequence.push(false);

          node = node->p;
       }

    /*Write the bits in reverse order*/
    while (bitSequence.empty() == false){
      out.writeBit(bitSequence.top());
      bitSequence.pop();
    }
}

/*Return symbol coded in the next sequence of bits from
the stream.*/
int HCTree:: decode(BitInputStream& in) const{
  HCNode* traverse = root; //create a node pointing to the root
  
  //traverse down the HCTree while the node's children pointers are not null
  while(traverse->c0 != 0 || traverse->c1 != 0){
    bool bit = in.readBit();
    //if the bit is 0, traverse to its c0 child
    if(bit == false)
      traverse = traverse->c0;  
    //if the bit is 1, traverse to its c1 child
    else
      traverse = traverse->c1;
  }
  
  //return symbol 
  return (traverse->symbol);      
}



