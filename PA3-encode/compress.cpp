
//  compress.cpp
//  huffman
//
//  Created by Jorden Tang on 5/16/18.
//  Copyright © 2018 Jorden Tang. All rights reserved.
//
#include <stdio.h>
#include <fstream>
#include <vector>
#include "HCTree.h"
#include <iostream>
#include <bitset>
using namespace std;

vector<int> freqs(256, 0);
ifstream infile;
ifstream infile2;
filebuf fb;
int c;
int tmp;
int totalSymbols = 0;
int totalNodes = 0;

void createHeader(HCNode * curr, BitOutputStream &out){
    if(curr == NULL){
        return ;
    }
    //visiting the node
    //non-leaf node
    if(curr->c0 != NULL || curr->c1 != NULL){
      out.writeBit(0);
    }
    //leaf node
    else{
      out.writeBit(1);
      bitset<8>bits(curr->symbol);
      //writes the symbol

      for(int i = 0; i < bits.size(); i++){
        out.writeBit(bits[i]);
      }
    }
    createHeader(curr->c0, out); 
    createHeader(curr->c1, out);
}

int main(int argc, char* argv[])
{

    //scan through file, count occurance
   infile.open(argv[1]);
    
    while(!infile.eof()){
      c = infile.get();
      if (c == -1){
        break;
      }
      freqs[c] = freqs.at(c)+1;
    }
   
    //close the input file
    infile.close();

    HCTree* tree = new HCTree();
    tree->build(freqs);
    totalNodes = tree->getSize();
    //open output file
    fb.open(argv[2],std::ios::out);
    infile2.open(argv[1]);
    ostream os(&fb);
   
    /*
    //creates header    
    for(int i = 0; i < 256; i++){
      int num = freqs[i];
      totalSymbols += freqs[i];
      os.write((char*)&num, sizeof(num));
    }
    
    //write the counter
    os.write((char*)&totalSymbols, sizeof(totalSymbols));
    */
    

    BitOutputStream oB(os);   
    os.write((char*)&totalNodes, sizeof(totalNodes));
    
    createHeader(tree->getRoot(), oB);

    oB.flush();

    /*
    while(!infile2.eof()){
        
        tmp = infile2.get();
        if ( tmp  == -1 ) {
          break;
        }
        tree->encode((char)tmp, oB);
    }
    oB.flush();
    */
    
    fb.close();
    infile2.close();
   
    delete tree;
    
    return 0;
}

