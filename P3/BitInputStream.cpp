/*
 * Terry Chu tjchu
 * Anthony Wong anw046
 */

#include "BitInputStream.hpp"
#include <fstream>


/*Fill the buffer from the input*/
void BitInputStream::fill(){
  buf = in.get();
  nbits = 0;
}
 
/*Read the next bit from the bit buffer. Fill the buffer from 
  the input stream first if needed.
  Return 1 if the bit read is 1.
  Return 0 if the bit read is 0. 
  */
int BitInputStream::readBit(){
  // If all bits in the buffer are read, fill the buffer first  
  if(nbits == 8){  
    fill();
  }

  /* Get the bit at the appriopriate location in the bit buffer*/
  int result = 1 & (buf >> (8-1-nbits));
  
  nbits++; // Increment the index

  return result; //return the appropriate int
}

