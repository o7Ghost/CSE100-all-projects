#include "actorSet.h"
#include "ActorGraph.h"
#include <queue>
#include <stack>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <climits>
using namespace std;


int main(int argc, const char* argv[]){
  actorSet iSet;
  ActorGraph iGraph;
  stack<actorNode*> clearA;
  ifstream rFile;
  ofstream wFile;
  actorNode* found = nullptr;
  stack<string> rPrint;
  bool have_header = false;
  rFile.open(argv[2]);
  wFile.open(argv[3]);
  string ufindOrWide = argv[4];

  //create graph and set depending on argument

  if(ufindOrWide == "widestp"){
    iGraph.loadFromFile(argv[1], false);
  }
  else{    
    iSet.loadFromFile(argv[1], false);
    ufindOrWide = "ufind";
  }

  wFile << "Actor1" << "\t" << "Actor2" << "\t" << "Year" << endl;
      
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
        

	//when ufind is called

	if(ufindOrWide == "ufind"){
	  iSet.ufind(actor_name1, actor_name2, wFile);
	}else{
	  

	priority_queue<pair<int, actorNode*>, vector<pair<int, actorNode*>>, connectionCompare> BFS;
        //travese through the graph and find the path
        int tmpW = 0;
        BFS.push(make_pair(tmpW, iGraph.actorMap.find(record[0])->second));
        actorNode* setPrev = iGraph.actorMap.find(record[0])->second;
        setPrev->prev = nullptr; 
	setPrev->dist = INT_MAX;

        while (!BFS.empty()) {
            
            pair<int, actorNode*> tmp = BFS.top();
	    //cout << tmp.first << "pop---" << endl;

	    if (tmp.second->actorName == actor_name2) {
		        goto actfound;
            }  
	
	    tmp.second->visited = true;

            BFS.pop();
            
                for (auto actorlist: tmp.second->neighbors) {
		  if(!(actorlist.second.second)->visited){
		     

		      int calDist = (2015 - actorlist.second.first.top()->movieYear + 1);  
		      calDist = min(calDist, tmp.second->dist);		     	

			if (actorlist.second.second->dist < calDist) {
                      	  (actorlist.second.second)->dist = calDist;
    			  (actorlist.second.second)->prev = tmp.second;
                          BFS.push(make_pair(actorlist.second.second->dist, actorlist.second.second));
		          clearA.push(actorlist.second.second);
			  //cout << actorlist.second.second->prev->actorName << "====" << endl;
		      }
                   }
                 }
		}

   actfound:
	found = iGraph.actorMap.find(record[1])->second;
	wFile << actor_name1 << "\t" << actor_name2 << "\t" << 2016 - found->dist;
        wFile << endl;


        while(!clearA.empty()) {
          clearA.top()->dist = -1;
	  clearA.top()->prev = nullptr;
	  clearA.top()->visited = false;
          clearA.pop();
		}

        }
	}

	}

//	}
