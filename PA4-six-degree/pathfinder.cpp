//
//  pathfinder.cpp
//  six Degree
//
//  Created by Joseph Lu on 5/31/18.
//  Copyright © 2018 Joseph Lu. All rights reserved.
//

#include "ActorGraph.h"
#include <queue>
#include <stack>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;
int main(int argc, const char * argv[]) {
    //declaration
    ActorGraph i;
    ifstream rFile;
    ofstream wFile;
    string wOu = argv[2];
    bool have_header = false;
    stack<string> rPrint;
    actorNode* found = nullptr;
    stack<movieNode*> clearM;
    stack<actorNode*> clearA; 
    //open both files
    rFile.open(argv[3]);
    wFile.open(argv[4]);
   
    //load map
    i.loadFromFile(argv[1], false);
    wFile << "(actor)--[movie#@year]-->(actor)--..." << endl; 
    //get stuff from file
    while (rFile) {
        string s;
        
        // get the next line
        if (!getline( rFile, s )) break;
        
        if (!have_header) {
            // skip the header
            have_header = true;
            continue;
        }
        
        istringstream ss( s );
        vector <string> record;
        
        while (ss) {
            string next;
            // get the next string before hitting a tab character and put it in 'next'
            if (!getline( ss, next, '\t' )) break;
            record.push_back( next );
        }
        
        if (record.size() != 2) {
            continue;
        }
        
        string actor_name1(record[0]);
        string actor_name2(record[1]);
       /* 
        if (wOu == "w") {

	  //priority_queue<pair<int, actorNode*>, vector<pair<int, actorNode*>>, weightCompare> BFS;
        }
        else {
        //  queue<actorNode*> BFS;
        } 
    */

        if (wOu != "w") {
        queue<actorNode*> BFS;
        //travese through the graph and find the path
      
        BFS.push(i.actorMap.find(record[0])->second);
        actorNode* setPrev = i.actorMap.find(record[0])->second;
        setPrev->prev = nullptr;
        setPrev->dist = 0;
   
        while (!BFS.empty()) {
            
            actorNode* tmp = BFS.front();
            BFS.pop();
            
                for (auto actorlist: tmp->neighbors) {

		  if((actorlist.second.second)->dist == -1){
                      (actorlist.second.second)->dist = tmp->dist + 1;
                      (actorlist.second.second)->prev = tmp;
                      BFS.push(actorlist.second.second);
		      clearA.push(actorlist.second.second);
                  }    
 	          
                  if ((actorlist.second.second)->actorName == actor_name2) {
                        found = actorlist.second.second;
                        goto actfound;
                  }

                }
            
            }
        }
        else {

	priority_queue<pair<int, actorNode*>, vector<pair<int, actorNode*>>, weightCompare> BFS;
        //travese through the graph and find the path
        int tmpW = 0;
        BFS.push(make_pair(tmpW, i.actorMap.find(record[0])->second));
        actorNode* setPrev = i.actorMap.find(record[0])->second;
        setPrev->prev = nullptr; 
	setPrev->dist = tmpW;

        while (!BFS.empty()) {
            
            pair<int, actorNode*> tmp = BFS.top();
	    //cout << tmp.first << "pop---" << endl;	
	
           if ((tmp.second)->actorName == actor_name2) {
                        found = tmp.second;
			//cout <<"hi"<<endl;
                        goto actfound;
                  }

	    tmp.second->visited = true;
            BFS.pop();
            
                for (auto actorlist: tmp.second->neighbors) {

		  if(!(actorlist.second.second)->visited){
		      int calDist =  (2015 - actorlist.second.first.top()->movieYear + 1) + tmp.second->dist;
/*
//		      cout << tmp.second->actorName << endl;
		      cout << actorlist.second.second->actorName << endl;
		      cout << actorlist.second.first.top()->movieName << endl;
		      cout << actorlist.second.first.top()->movieYear << endl;
		      //cout << calDist << endl;
		      */
		      if ( (actorlist.second.second)->dist  == -1) { 
                      	(actorlist.second.second)->dist = calDist;
			//cout << actorlist.second.second->actorName << "---" << endl;	
    			(actorlist.second.second)->prev = tmp.second;

                        BFS.push(make_pair(actorlist.second.second->dist, actorlist.second.second));
		        clearA.push(actorlist.second.second);
		      }
		      else {
			if (actorlist.second.second->dist > calDist) {
                      	  (actorlist.second.second)->dist = calDist;
    			  (actorlist.second.second)->prev = tmp.second;

                        BFS.push(make_pair(actorlist.second.second->dist, actorlist.second.second));
		        clearA.push(actorlist.second.second);
			  //cout << actorlist.second.second->prev->actorName << "====" << endl;
			}
		      }
                  
                  }

/* 	          
                  if ((actorlist.second.second)->actorName == actor_name2) {
                        found = actorlist.second.second;
                        goto actfound;
                  }
*/
                }
            
            }

        }

   actfound: 
//        found = i.actorMap.find(record[1])->second;
        while (found->prev != nullptr) {
            rPrint.push(found->actorName);
	    string movieY = to_string(found->neighbors.at(found->prev->actorName).first.top()->movieYear); 
	    string movieN = found->neighbors.at(found->prev->actorName).first.top()->movieName;             
            rPrint.push(movieY);
            rPrint.push(movieN);
            found = found->prev; 
 }

            rPrint.push(found->actorName);

        wFile << "(" << rPrint.top() << ")";
        rPrint.pop();

        while (!rPrint.empty()) {
            wFile << "--[" << rPrint.top() << "#@";
            rPrint.pop();
            wFile << rPrint.top() << "]-->";
            rPrint.pop();
            wFile << "(" << rPrint.top() << ")";
            rPrint.pop();
        }
    
        wFile << endl;
        while(!clearA.empty()) {
          clearA.top()->dist = -1;
	  clearA.top()->prev = nullptr;
	  clearA.top()->visited = false;
          clearA.pop();
        }

    }
	
}
