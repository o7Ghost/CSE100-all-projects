//
//  uncompress.cpp
//  huffman
//
//  Created by Jorden Tang on 5/16/18.
//  Copyright © 2018 Jorden Tang. All rights reserved.
//

#include <string>
#include <stdio.h>
#include <fstream>
#include <vector>
#include "HCTree.h"
#include "HCNode.h"
#include <iostream>
//#include <HCTree.h>
using namespace std;

string temp = "";
vector<int> freqs(256,0);
int readIn;
int totalSymbols;
filebuf inFile;
ofstream outfile;

void buildPreorder(HCNode* node, int count, BitInputStream &bis ){
{
     if (count == 0){
          return;
     }
     //create root
     if(bis.readBit() == 0){
        node = new HCNode(0, NULL, nullptr, nullptr, nullptr);
     }
     else{
       
     }
        
     buildPreorder(node->c0, count - 1, bis);
     buildPreorder(node->c1, count - 1, bis);
}    

int main(int argc, char* argv[]){
  

 // int c;
 // int tmp;
  
  inFile.open(argv[1],std::ios::in);
  //scan through encoded file
  outfile.open(argv[2]);
 
  istream is(&inFile);
  BitInputStream read(is);
    
 /*
  for(int i = 0; i < 256; i++){
    is.read((char*)&readIn, sizeof(readIn));
  //  cout << i << " " << readIn << endl; 
    freqs[i] = readIn;
  }
 */

  is.read((char*)&readIn, sizeof(readIn));
  //buildTreeHelper(readIn);


  HCTree* tree = new HCTree();
  buildTreeHelper(tree->getRoot(), readIn);
  tree->build(freqs);
  
  /*
  is.read((char*)&totalSymbols, sizeof(totalSymbols));
  while(totalSymbols != 0){
    outfile << (char)tree->decode(read);   
    totalSymbols--;
  }
  */

  outfile.close();
  inFile.close();

  //delete tree;
  return 0;
}
