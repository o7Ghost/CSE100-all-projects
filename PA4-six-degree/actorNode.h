//
//  actorNode.hpp
//  sixDegree
//
//  Created by Jorden Tang on 5/30/18.
//  Copyright © 2018 Jorden Tang. All rights reserved.
//

#ifndef actorNode_hpp
#define actorNode_hpp

#include <stdio.h>
#include <unordered_map>
#include <stdlib.h>
#include <string>
#include <vector>
#include <queue>
using namespace std;
//there exists a movieNode
class movieNode;

class movieCompare {
  public:
  bool operator() (movieNode* lhs, movieNode* rhs) const

  {
  return (lhs->movieYear < rhs->movieYear);
}
};

class weightCompare {
  public:
  bool operator() (pair<int, actorNode*> lhs, pair<int, actorNode*> rhs) const {
  return (lhs.first > rhs.first);
  }
};
 
class connectionCompare {
  public:
  bool operator() (pair<int, actorNode*> lhs, pair<int, actorNode*> rhs) const {
  return (lhs.first < rhs.first);
  }
};

class actorNode{
  public:
    
    actorNode* prev;
    string actorName;
    unordered_map<string, movieNode* > movies;
    unordered_map<string, pair<priority_queue<movieNode*, vector<movieNode*>, movieCompare>, actorNode*>> neighbors;
    int dist;
    bool visited;
    
    actorNode(string name): prev(nullptr), actorName(name), dist(-1), visited(false) {} 
};
#endif /* actorNode_hpp */
