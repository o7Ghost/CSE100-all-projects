//
//  movieNode.hpp
//  sixDegree
//
//  Created by Jorden Tang on 5/30/18.
//  Copyright © 2018 Jorden Tang. All rights reserved.
//

#ifndef movieNode_hpp
#define movieNode_hpp

#include <stdio.h>
#include <unordered_map>
#include <string>

//there exists a actorNode
class actorNode;

using namespace std;
class movieNode{
  public:
    actorNode* prev;
    unordered_map<string, actorNode* > actors;
    int weight;
    string movieName;
    int movieYear;
    bool visited;
    movieNode(string name, int year): movieName(name), movieYear(year) {} 
};
#endif /* movieNode_hpp */
