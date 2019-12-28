#include "util.h"
#include "DictionaryHashtable.h"
#include <unordered_set>
#include <iostream>

/* Create a new Dictionary that uses a Hashset back end */
DictionaryHashtable::DictionaryHashtable(){}

/* Insert a word into the dictionary. */
bool DictionaryHashtable::insert(std::string word)
{
    if(hashSet.insert(word).second == true){
        return true;
    }
    return false;
}

/* Return true if word is in the dictionary, and false otherwise */
bool DictionaryHashtable::find(std::string word) const
{
    if(hashSet.find(word) != hashSet.end()){
      return true;
    }
    return false;
}

/* Destructor */
DictionaryHashtable::~DictionaryHashtable(){}
