#include <iostream>
#include <string>
#include "util.h"
#include "DictionaryTrie.h"
#include <unordered_map>
#include <stack>
#include <queue>
#include <tuple>

/* Create a new Dictionary that uses a Trie back end */
DictionaryTrie::DictionaryTrie(){
  root = new TrieNode();
}

/* Insert a word with its frequency into the dictionary.
 * Return true if the word was inserted, and false if it
 * was not (i.e. it was already in the dictionary or it was
 * invalid (empty string) */
bool DictionaryTrie::insert(std::string word, unsigned int freq)
{
    int wordCount = 0;
    //when word is an empty string
    if(word.empty()){
      return false;
    }
    TrieNode * curr = root;
    for(auto c : word) {
        if(!isalpha(c) && !isspace(c)){
            return false;
        }
        //char does not exist in hashtable
        if(curr->childMap.find(c) == curr->childMap.end()){
          TrieNode * newNode = new TrieNode();
          curr->childMap.insert(std::make_pair(c, newNode));
          newNode->wordlength = wordCount++;
        }

        curr = (*(curr->childMap.find(c))).second;
    }
    
    
    //when it is already a word
    if(curr->isWord == true){
        if(freq >= curr->frequency){
          curr->frequency = freq;
        }
        return false;
    }
    else{
        curr->isWord = true;
        curr->wordlength = wordCount;
        curr->word = word;
        curr->frequency = freq;
        return true;
    }
}

/* Return true if word is in the dictionary, and false otherwise */
bool DictionaryTrie::find(std::string word) const
{
    TrieNode * curr = root;
    for(auto c : word) {
        if(curr->childMap.find(c) == curr->childMap.end()){
            return false;
        }
        curr = (*(curr->childMap.find(c))).second;
    }
    if(curr->isWord == true){
      return true;
    }
    return false;
}

/* Return up to num_completions of the most frequent completions
 * of the prefix, such that the completions are words in the dictionary.
 * These completions should be listed from most frequent to least.
 * If there are fewer than num_completions legal completions, this
 * function returns a vector with as many completions as possible.
 * If no completions exist, then the function returns a vector of size 0.
 * The prefix itself might be included in the returned words if the prefix
 * is a word (and is among the num_completions most frequent completions
 * of the prefix)
 */
std::vector<std::string> DictionaryTrie::predictCompletions(std::string prefix, unsigned int num_completions)
{
  //declaration
  std::vector<std::string> words;
  std::queue<TrieNode*> search;
  std::priority_queue<std::pair<int ,std::string>> rvector;
  TrieNode * curr = root;
  std::string possWords = prefix;
  //check for errors
    if ( prefix == "" ) {
        fprintf(stderr, "Invalid Input. Please retry with correct input");
        return words;
    }
    
    for(auto c : prefix) {

        if(curr->childMap.find(c) == curr->childMap.end()){
            fprintf(stderr, "Invalid Input. Please retry with correct input");
            return words;
        }

        curr = (*(curr->childMap.find(c))).second;
    }
    
    search.push(curr);

    while (!search.empty()) {
        
        TrieNode* tmp = search.front();
        search.pop();
        
        if (tmp->isWord) {
          rvector.push(make_pair(tmp->frequency,tmp->word));
        }
        
        for (auto child : tmp->childMap) {
            search.push(child.second);
        }
    }
    
    for (unsigned int i = 0; i < num_completions; ++i) {
        
        if (rvector.empty()) {
            return words;
        }
        
        words.push_back(rvector.top().second);
        rvector.pop();
    }

  return words;
}

/*
 * Return the most similar word of equal length to the query, based
 * on their Hamming distance. 
 * In case of ties, return the word with the highest frequency (you may
 * assume there will always be one should a tie happen.)
 * In case there isn't any word of equal length to the query in the
 * trie, return an empty string.
 */
std::string DictionaryTrie::checkSpelling(std::string query)
{
    std::priority_queue<std::tuple<int, int, std::string>, std::vector<std::tuple<int, int, std::string>>, mycompare> sort;
    std::string wordcheck = "";
    int currWordDiff = 0;
    int bestDistance = 0;
    std::queue<TrieNode*> search;
    
    search.push(root);

    while (!search.empty()) {
        
      TrieNode* current = search.front();
      search.pop();
      
        if (current->isWord && current->word.length() == query.length()) {
  
            for (unsigned int i = 0; i < query.length(); ++i) {
                if (query[i] != current->word[i]) {
                    currWordDiff++;
                }
            }
            
            if (sort.empty()) {
                bestDistance = currWordDiff;
                 sort.push(make_tuple(currWordDiff, current->frequency, current->word));
            }
            else {
                if (currWordDiff<=bestDistance) {
            sort.push(make_tuple(currWordDiff, current->frequency, current->word));
                }
            }
            currWordDiff = 0;
        }

        for (auto child : current->childMap) {
  
            if (child.second->wordlength <= query.length()) {
            search.push(child.second);
            }
        }
    }
    
    if (!sort.empty()) {
     wordcheck = std::get<2>(sort.top());
    }
    
    return wordcheck;
}


/* Destructor */
DictionaryTrie::~DictionaryTrie(){
    std::queue<TrieNode*> remove;
    remove.push(root);
    
    while (!remove.empty()) {
        
        TrieNode* tmp = remove.front();
        remove.pop();


        for (auto child : tmp->childMap) {
            remove.push(child.second);
        }
        delete(tmp);
    }
}
