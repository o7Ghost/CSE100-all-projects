//
//  BitInputStream.cpp
//  huffman
//
//  Created by Jorden Tang on 5/16/18.
//  Copyright © 2018 Jorden Tang. All rights reserved.
//

#include "BitInputStream.h"
#include <bitset>
using namespace std;
void BitInputStream::fill() {
    buf = (unsigned char)in.get(); // read one byte from istream to bitwise buffer
    nbits = 0;      // no bits have been read from bitwise buffer
}

unsigned char BitInputStream::readBit() {
    
    //unsigned char mask = ~(1<<nbits); // to clear bits
    // fill bitwise buffer if there are no more unread bits
    if(nbits == 8) {
        fill();
    }
  
    bitset<8> bits(buf); 
    // get the next unread bit from the bitwise buffer (how?)
    unsigned char nextBit = bits[nbits];
    //buf & 1; //buf & mask;
    //buf = buf >> 1;
    /*
    cout << bits[0] << endl; 
    cout << bits[1] << endl; 
    cout << bits[2] << endl; 
    cout << bits[3] << endl; 
    cout << bits[4] << endl; 
    cout << bits[5] << endl; 
    cout << bits[6] << endl;
    */ 
    // increment the number of bits we have read from the bitwise buffer

    //cout << bits[7-nbits];
    nbits++; 
    // return the bit we just read
    
    return nextBit;
}
