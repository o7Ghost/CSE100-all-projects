//
//  BitInputStream.hpp
//  huffman
//
//  Created by Jorden Tang on 5/16/18.
//  Copyright © 2018 Jorden Tang. All rights reserved.
//

#ifndef BitInputStream_h
#define BitInputStream_h

#include <stdio.h>
#include <iostream>
using namespace std;

class BitInputStream
{
private:
    unsigned char buf;  // bitwise buffer (one byte)
    int nbits;          // number of bits that have been read from bitwise buffer
    istream & in;       // reference to the bytewise input stream (a C++ istream)
    
public:
    // constructor: assign 'in' to 'is', 'buf' to 0, and 'nbits' to 8
    BitInputStream(istream & is) : in(is), buf(0), nbits(8) {}
    
    // fill the bitwise buffer by reading one byte from the input stream
    void fill();
       
    // read bit from the bitwise buffer
    unsigned char readBit();

};

#endif /* BitInputStream_h */
