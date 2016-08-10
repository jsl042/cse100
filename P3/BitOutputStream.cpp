/*
 * Terry Chu tjchu
 * Anthony Wong anw046
 */

#include "BitOutputStream.hpp" 
#include <fstream>
#include <ostream>

/** Send the buffer to the output, and clear it */
void BitOutputStream:: flush() {
  BitOutputStream::out.put(buf);
  BitOutputStream::out.flush();
  buf = nbits = 0;
}  

/** Write the least significant bit of the argument to 
the bit buffer, and increment the bit buffer index.
But flush the buffer first, if it is full. 
*/
void BitOutputStream:: writeBit(int i){
  //If bit buffer full, flush it.
  if(nbits == 8){
    flush();
  }

  buf = buf | (i << ( 8-1-nbits));
  nbits++;  //Increment the index
}

