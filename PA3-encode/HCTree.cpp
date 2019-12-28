#include <stdio.h>
#include "HCTree.h"
#include <queue>
#include <vector>
#include <fstream>
#include <iostream>
#include "BitInputStream.h"
#include "BitOutputStream.h"
#include <string>
#include <algorithm>
#include <vector>

//default destructor
HCTree::~HCTree(){
  deleteAll(root);
//    for ( int i = 0; i < leaves.size(); i++) {
//        if (leaves[i] != nullptr) {
//        delete leaves[i];
//        }
//    }
}
void HCTree::deleteAll(HCNode* n) {
  if(n == nullptr){
    return;
  }
  deleteAll(n->c0);
  deleteAll(n->c1);
  delete(n);
}

void HCTree::build(const vector<int>& freqs) {
    //extract char with frequency > 0
    HCNode* firstSmallest = nullptr;
    HCNode* secondSmallest = nullptr;
    for(int i = 0; i < freqs.size(); i++){
        if(freqs.at(i) != 0){
          HCNode* curr = new HCNode(freqs.at(i), (unsigned char)i, nullptr, nullptr, nullptr);
          leaves[i] = curr;
          forest.push(curr);
	  size++;
        }
    }
  
     
    while(forest.size() > 1){
      firstSmallest = forest.top();
      forest.pop();
      secondSmallest = forest.top();
      forest.pop();
      size++;
        HCNode * parent = new HCNode(firstSmallest->count + secondSmallest->count, firstSmallest->symbol, firstSmallest, secondSmallest, nullptr);
        firstSmallest->p = parent;
        secondSmallest->p = parent;
        forest.push(parent);
    }
    
    //assign root
    if(forest.size() != 0){
      root = forest.top();
    }

}

void HCTree::encode(byte symbol, BitOutputStream& out) const {
    string encodedStr = "";
    HCNode* curr = leaves.at((int)symbol);
    vector<int> a;
 
    while(curr != root){
        if(curr->p->c0 == curr){
            a.push_back(0); 
            //out.writeBit(0);
        }
        
        else{
            a.push_back(1);
            //out.writeBit(1);
        } 
        curr = curr->p;
    }

    reverse(a.begin(), a.end());
    for (int i = 0; i < a.size(); i++) {
      out.writeBit(a.at(i));
    }
}

void HCTree:: encode(byte symbol, ofstream& out) const{
    string encodedStr = "";
    HCNode* curr = leaves.at((int)symbol);
    while(curr != root){
        if(curr->p->c0 == curr){
            encodedStr.append("0");
        }
        else{
          encodedStr.append("1");
        }
	curr = curr->p;
    }
    reverse(encodedStr.begin(),encodedStr.end());
    out << encodedStr;
}

int HCTree::decode(BitInputStream& in) const {
    HCNode* curr = root;
    unsigned int c = 0;
    
    while (curr -> c0 != nullptr || curr -> c1 != nullptr) {
        c = in.readBit();
        //cout << c << endl;
        if(c == 0){
            
            curr = curr->c0;
        }
        else{
           
            curr = curr->c1;
        }
    }
    
    return (int)curr->symbol;
}

int HCTree::decode(ifstream& in) const{
    HCNode* curr = root;
    int c = 0;
    
      while (curr -> c0 != nullptr || curr -> c1 != nullptr) {
        c = (int)in.get();
        if(c % 48 == 0){
          curr = curr->c0;
        }
        else{
          curr = curr->c1;
        }
      }
      
    return (int)curr->symbol;
}

HCNode * HCTree::getRoot() const{
    return root;
}

int HCTree::getSize() const{
  return size;

}
