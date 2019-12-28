#include "util.h"
#include "SuffixArray.h"
#include <queue>
#include<string>
using namespace std;
/**
 *  The class for a suffix array, represented as an int array
 *  storing the indices of the sorted suffixes.
 */
SuffixArray::SuffixArray(std::string word) : 
  word(word),
  suffixIdxs(new int[word.length()+1])
{
  buildSuffixArray(word);
}

/*
 * Helper method that constructs the suffix array derived from `word`
 * preferably using an efficient algorithm, such as the DC3 algorithm
 * (if you want the 5 points for efficiency, of course.)
 */
void SuffixArray::buildSuffixArray(std::string word){
    word.append("$");
    priority_queue<pair<string ,int>> sort;
    int indx = 0;
    
    for (size_t i = word.length(); i > 0; --i) {
        word[i - 1] = '$';
        sort.push(make_pair(word.substr(0,i), indx));
       
        indx++;
    }

          //  cout << sort.top().first << endl;
    for (int i = 0; i < word.length(); ++i) {
        suffixIdxs[i] = sort.top().second;
        //cout << sort.top().first << endl;
        sort.pop();
    }

    
    for ( int i = 0; i < word.length(); ++i) {
        cout << suffixIdxs[i] << endl;
    }
    
  return;
}

/* 
 * Return true if `pattern` exists in the word encoded by the suffix array,
 * false otherwise 
 */
bool SuffixArray::find(std::string pattern) const
{
  // TODO: Implement this method
  return false;
}

/* Destructor */
SuffixArray::~SuffixArray(){
  delete [] this->suffixIdxs;
}
