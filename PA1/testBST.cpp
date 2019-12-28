#include "BSTInt.h"
#include "BST.hpp"
#include "BSTIterator.hpp"

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <set>

using namespace std;

/**
 * A test driver for the BST int class and class template.
 * PA1 CSE 100 2016
 * Author: Christine Alvarado and YOU
 * TODO: Add more tests
 */
int main() {

    /* Create an STL vector of some ints */
    /*test*/
    vector<int> v;
    vector<int> emptyV;
    vector<int> oneV;
    vector<int> twoV;
    vector<int> onesideV;
    vector<int> perfectV;
    vector<int> completeV;
    vector<int> fullV;
    
    /* fill for v */
    v.push_back(3);
    v.push_back(4);
    v.push_back(1);
    v.push_back(100);
    v.push_back(-33);

    /* fill for oneV */
    oneV.push_back(0);
    
    /* fill for twoB */
    twoV.push_back(-1);
    twoV.push_back(2);
    
    /* fill for onesideV */
    for ( int i = 0; i < 10; ++i) {
        onesideV.push_back(i);
    }
    
    /* fill for full tree */
    fullV.push_back(14);
    fullV.push_back(8);
    fullV.push_back(15);
    fullV.push_back(6);
    fullV.push_back(11);
    fullV.push_back(9);
    fullV.push_back(12);
    
    /* fill for complete tree */
    completeV.push_back(14);
    completeV.push_back(8);
    completeV.push_back(15);
    completeV.push_back(6);
    completeV.push_back(11);
    completeV.push_back(4);
    completeV.push_back(7);
    completeV.push_back(9);
    completeV.push_back(12);

    /* fill for perfect tree */
    perfectV.push_back(6);
    perfectV.push_back(2);
    perfectV.push_back(10);
    perfectV.push_back(7);
    perfectV.push_back(11);
    perfectV.push_back(1);
    perfectV.push_back(5);

    /* Create an instance of BST holding int */
    BSTInt b;
    BSTInt empty;
    BSTInt oneElement;
    BSTInt twoElement;
    BSTInt onesideTree;
    BSTInt perfectTree;
    BSTInt completeTree;
    BSTInt fullTree;
    
    // Could use: for(auto item : v) { instead of the line below
    //insert for perfect tree
    for(int item : fullV) {
        bool pr = fullTree.insert(item);
        if(! pr ) {
            cout << "Incorrect bool return value when inserting " << item
            << "for full tree. " << endl;
            return -1;
        }
    }
    
    for(int item : perfectV) {
        bool pr = perfectTree.insert(item);
        if(! pr ) {
            cout << "Incorrect bool return value when inserting " << item
            << "for perfect tree. " << endl;
            return -1;
        }
    }
    
    for(int item : completeV) {
        bool pr = completeTree.insert(item);
        if(! pr ) {
            cout << "Incorrect bool return value when inserting " << item
            << "for complete tree. " << endl;
            return -1;
        }
    }

    //insert for onesideTree
    for(int item : onesideV) {
        bool pr = onesideTree.insert(item);
        if(! pr ) {
            cout << "Incorrect bool return value when inserting " << item
                 << "for onesided right tree. " << endl;
            return -1;
        }
    }
    
    //insert for full tree
    for(int item : v) {
        bool pr = b.insert(item);
        if(! pr ) {
            cout << "Incorrect bool return value when inserting  " << item
                 << "for full tree" << endl;
            return -1;
        }
    }
    
    //insert for two element tree
    for(int item : twoV) {
        bool pr = twoElement.insert(item);
        if(! pr ) {
            cout << "Incorrect bool return value when inserting " << item
                 << " for two element tree" << endl;
            return -1;
        }
    }
    
    // insert element for oneElement tree
    bool oneTree = oneElement.insert(0);
    if (!oneTree) {
        cout << "Incorrect boolean value return" << endl;
        return -1;
    }

    /* Test size. */
    cout << "Size is: " << b.size() << endl;
    if(b.size() != v.size()) {
        cout << "... which is incorrect." << endl;
        return -1;
    }
    
    /* TEST empty size */
    //Test for full tree
    cout << "Size is: " << empty.size() << endl;
    if(empty.size() != emptyV.size()) {
        cout << "not full complete or perfect tree size is incorrect." << endl;
        return -1;
    }


    /* TEST one size tree */
    //Test for one node tree
    cout << "Size is: " << oneElement.size() << endl;
    if(oneElement.size() != oneV.size()) {
        cout << "one node tree size is incorrect." << endl;
        return -1;
    }
    
    
    cout << "Size is: " << twoElement.size() << endl;
    if(twoElement.size() != twoV.size()) {
        cout << "two node tree size is incorrect." << endl;
        return -1;
    }
    
    cout << "Size is: " << onesideTree.size() << endl;
    if(onesideTree.size() != onesideV.size()) {
        cout << "oneside sorted right tree size is incorrect." << endl;
        return -1;
    }
    
    /* general TESTS for find method */

    /* Test find return value. */
    // Test the items that are already in the tree
    for(int item : v) {
        if(!b.find(item)) {
            cout << "Incorrect return value when finding " << item << " for full tree" << endl;
            return -1;
        }
    }
    
    for(int item : onesideV) { 
        if(!onesideTree.find(item)) {
            cout << "Incorrect return value when finding " << item <<" for one sided right tree" << endl;
            return -1;
        }
    }
    
    for(int item : oneV) {
        if(!oneElement.find(item)) {
            cout << "Incorrect return value when finding " << item << " for one node tree" << endl;
            return -1;
        }
    }
    
    for(int item : twoV) {
        if(!twoElement.find(item)) {
            cout << "Incorrect return value when finding " << item << " for two node tree" << endl;
            return -1;
        }
    }
    
    /* Test for finding value that is not in there */
    if (b.find(-1)) {
      cout << "Incorrect return value when finding the element 0 that"
      " is not in the full tree" << endl;
      return -1;
    }
    
    if (empty.find(0)) {
      cout << "Incrroect return value when finding the element 0 that"
      " is not in the empty tree" << endl;
      return -1;
    }

    if (oneElement.find(1)) {
      cout << "Incrroect return value when finding the element 0 that"
      " is not in one node tree" << endl;
      return -1;
    }

    if (onesideTree.find(-1)) {
      cout << "Incorrect return value when finding the element 4 that"
      " is not in one sided right tree" << endl;
      return -1;
    }
    
    /* general TESTS for insert method */
    if (b.insert(-33)) {
      cout << "Same element inserted twice for full tree that's size of 5" << endl;
      return -1;
    }

    //check if tree with size of 1 insertion duplicate
    if (oneElement.insert(0)) {
      cout << "Same element inserted twice for one node that's size of 1" << endl;
      return -1;
    }
    
    if (twoElement.insert(-1)) {
        cout << "Same element inserted twice for two node tree that's size of 2" << endl;
        return -1;
    }
    
    /* Test tree height */
    
    //Test case for not full not complete not perfect tree
    if (b.height() != 2) {
        cout << "tree height for not full not complete not perfect tree is incorrect" << endl;
        return -1;
    }
    
    //Test case height for empty tree
    if (empty.height() != -1) {
        cout << "tree height for empty tree is incorrect" << endl;
        return -1;
    }
    
    //Test case height for one element tree
    if (oneElement.height() != 0) {
        cout << "tree height for one element tree is incorrect" << endl;
        return -1;
    }
    
    //Test case height for two element tree
    if (twoElement.height() != 1) {
        cout << "tree height for two element tree is incorrect" << endl;
        return -1;
    }
    
    //Test case height for onesideTree
    if (onesideTree.height() != 9) {
        cout << "tree height for onesideTree is incorrect your height is " <<  onesideTree.height() << endl;
        return -1;
    }
    
    //Test case height for perfect tree
    if (perfectTree.height() != 2) {
        cout << "tree height for perfect tree is incorrect your height is " << perfectTree.height() << endl;
        return -1;
    }
    
    //Test case height for complete tree
    if (completeTree.height() != 3) {
        cout << "tree height for perfect tree is incorrect your height is " << completeTree.height() << endl;
        return -1;
    }
    
    //Test case height for complete tree
    if (fullTree.height() != 3) {
        cout << "tree height for perfect tree is incorrect your height is " << fullTree.height() << endl;
        return -1;
    }
    
    /* Test case empty */
    bool emptyCT = empty.empty();
    
    if (!emptyCT && empty.size() != 0) {
        cout << "empty tree is not empty size is " << empty.size() << endl;
        return -1;
    }
    
    /* UNCOMMENT THE LINES BELOW TO TEST THE TEMPLATE-BASED ITERATOR */

    
    // Test the template version of the BST  with ints 
    BST<int> btemp;
    for (int item : v) {
        // The auto type here is the pair of BSTIterator<int>, bool
        cout << "Inserting " << item << " into the int template-based BST...";
        auto p = btemp.insert(item);
     
        if (*(p.first) != item) {
            cout << "Wrong iterator returned.  "
                 << "Expected " << item << " but got " << *(p.first) << endl;
            return -1;
        }
     
        if (!p.second) {
            cout << "Wrong boolean returned.  Expected true but got " 
                 << p.second << endl;
            return -1;
        }
        cout << "success!" << endl;
    }

    // Now test finding the elements we just put in
    for (int item: v) {
        cout << "Finding " << item << "...." << endl;
        BSTIterator<int> foundIt = btemp.find(item);
        if (*(foundIt) != item) {
            cout << "incorrect value returned.  Expected iterator pointing to "
                 << item << " but found iterator pointing to " << *(foundIt) 
                 << endl;
            return -1;
        }
        cout << "success!" << endl;
    }



    // Test the iterator: The iterator should give an in-order traversal
  
    // Sort the vector, to compare with inorder iteration on the BST
    sort(v.begin(),v.end());

    cout << "traversal using iterator..." << endl;
    auto vit = v.begin();
    auto ven = v.end();

    // This is equivalent to BSTIterator<int> en = btemp.end();
    auto en = btemp.end();

    //This is equivalent to BST<int>::iterator it = btemp.begin();
    auto it = btemp.begin();

    for(; vit != ven; ++vit) {
        if(! (it != en) ) {
            cout << *it << "," << *vit 
                 << ": Early termination of BST iteration." << endl;
            return -1;

        }
        cout << *it << endl;
        
        if(*it != *vit) {
            cout << *it << "," << *vit 
                 << ": Incorrect inorder iteration of BST." << endl;
            return -1;
        }
        ++it;
         
    }

    cout << "success!" << endl;

    

    // ADD MORE TESTS HERE.  You might also want to change what is input
    // into the vector v.
    cout << "All tests passed!" << endl;
    return 0;
}
