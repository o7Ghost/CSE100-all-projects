#include <utility>
#include <set>
#include <iostream>
#include <string>
#include "util.h"
#include "DictionaryBST.h"

/* Create a new Dictionary that uses a BST back end */
DictionaryBST::DictionaryBST(){
};

/* Insert a word into the dictionary. */
bool DictionaryBST::insert(std::string word)
{
    if(bst.insert(word).second == true){
        return true;
    }
    return false;
}

/* Return true if word is in the dictionary, and false otherwise*/
bool DictionaryBST::find(std::string word) const
{
    if(bst.find(word) != bst.end()){
      return true;
    }
    return false;
}

/* Destructor */
DictionaryBST::~DictionaryBST(){}
