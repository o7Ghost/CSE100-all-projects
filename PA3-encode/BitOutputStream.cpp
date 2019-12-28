//
//  BitOutputStream.cpp
//  huffman
//
//  Created by Jorden Tang on 5/16/18.
//  Copyright © 2018 Jorden Tang. All rights reserved.
//

#include "BitOutputStream.h"
#include <iostream>
void BitOutputStream::flush() {
    out.put(buf);  // write the bitwise buffer to the ostream
    out.flush();   // flush the ostream (optional, slower to do it here)
    buf = 0;       // clear the bitwise buffer
    nbits = 0;     // bitwise buffer is cleared, so there are 0 bits in it
}

// write bit to the bitwise buffer
void BitOutputStream::writeBit(unsigned int bit) {
    //unsigned char mask = bit << (7 - nbits);
    // flush the bitwise buffer if it is full
    if(nbits == 8) {
        flush();
    }
    
    // set the next open bit of the bitwise buffer to 'bit' (how?)
    buf = buf | (bit << nbits); 
    // increment the number of bits in our bitwise buffer
    nbits++;
}


