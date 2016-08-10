/*
 * Terry Chu tjchu
 * Anthony Wong anw046
 */

#ifndef BITOUTPUTSTREAM_HPP
#define BITOUTPUTSTREAM_HPP

#include <iostream>
#include <fstream>


class BitOutputStream{
private:
  char buf; //one byte buffer of bits
  int nbits; //how many bits have been written to buf
  std::ostream & out; //reference to the output stream to use

public:
    
  BitOutputStream(std::ostream & os) : out(os){
    buf = 0;
    nbits = 0;
  }  

  /** Send the buffer to the output, and clear it */
  void flush(); 

  /** Write the least significant bit of the argument to 
  the bit buffer, and increment the bit buffer index.
  But flush the buffer first, if it is full. 
  */
  void writeBit(int i);
};

#endif
