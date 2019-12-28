//
//  main.cpp
//  sixDegree
//
//  Created by Jorden Tang on 5/30/18.
//  Copyright © 2018 Jorden Tang. All rights reserved.
//

#include <iostream>
#include "ActorGraph.h"
#include <unordered_map>
using namespace std;

int main(int argc, const char * argv[]) {
    int total = 0;
    ActorGraph i;   
    i.loadFromFile("movie_casts.tsv", false);
    
    for(auto c: i.actorMap){
       cout << c.first << endl;
        
    }
   
    for(auto c : i.movieMap){
      for(auto b: c.second->actors){
        total++;
      }
    }
    
      


    cout << i.movieMap.size() << endl;
    cout << i.actorMap.size() << endl;
    cout << total << endl;
}	
