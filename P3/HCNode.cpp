/*
 * Terry Chu tjchu
 * Anthony Wong anw046
 */ 

#include "HCNode.hpp"
#include <map>

/** Less-than comparison, so HCNodes will work in std::priority_queue
  *  We want small counts to have high priority.
  *  And we want to break ties deterministically.
  */
bool HCNode:: operator<(const HCNode& other){
  /*if the other node's count is not equal to the called object's count,
  return the statement count is larger than other.count so that the small
  count has higher priority*/
  if(other.count!=count){
    return count>other.count;
  }

  //else, return symbol less than other.symbol to break ties deterministically  
  else{
    return symbol>other.symbol;
  }
}



