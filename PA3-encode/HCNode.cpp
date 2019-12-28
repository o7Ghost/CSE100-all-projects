#include <stdio.h>
#include "HCNode.h"

bool HCNode::operator<(const HCNode& other){
  if(this->count != other.count){
    return this->count > other.count;
  }
  return this->symbol > other.symbol;
}
