/*
 * ActorGraph.cpp
 * Author: <YOUR NAME HERE>
 * Date:   <DATE HERE>
 *
 * This file is meant to exist as a container for starter code that you can use to read the input file format
 * defined in movie_casts.tsv. Feel free to modify any/all aspects as you wish.
 */
#include <unordered_map>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "ActorGraph.h"

using namespace std;

ActorGraph::ActorGraph(void) {}

ActorGraph::~ActorGraph() {

  for (auto i: actorMap) {
	delete i.second;
  }

  for (auto j: movieMap) {
      delete j.second;
  }
}

bool ActorGraph::loadFromFile(const char* in_filename, bool use_weighted_edges) {
    
    // Initialize the file stream
    ifstream infile(in_filename);

    bool have_header = false;
  
    // keep reading lines until the end of file is reached
    while (infile) {
        string s;
    
        // get the next line
        if (!getline( infile, s )) break;

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
    
        if (record.size() != 3) {
            // we should have exactly 3 columns
            continue;
        }

        string actor_name(record[0]);
        string movie_title(record[1]);
        int movie_year = stoi(record[2]);
        string movieName = movie_title;
        movieName.append(to_string(movie_year));
        
        movieNode* newMovie;
        actorNode* newActor;

    
        // we have an actor/movie relationship, now what?
        //create new movie Node if only it appears the first time
        if(movieMap.find(movieName) == movieMap.end()){
            newMovie = new movieNode(movie_title, movie_year);
            movieMap.insert(make_pair(movieName, newMovie));
//	    delete newMovie; 
        }
        else{
            newMovie = movieMap.find(movieName)->second;
        }
        
        
        //create new actor Node if only it appears the firs time
        if(actorMap.find(actor_name) == actorMap.end()){
            newActor = new actorNode(actor_name);
            actorMap.insert(make_pair(actor_name, newActor));
   
        }
        else{
            newActor = actorMap.find(actor_name)->second;
  
        }
        
        // actor's Node doesn't have this movie
        if(newActor->movies.find(movie_title) == newActor->movies.end()){
            newActor->movies.insert(make_pair(movieName, newMovie));
        }

	if(newMovie->actors.size() > 0){
  
        for (auto actor: newMovie->actors) {
            //newly inserted node, need to create newNode in neighbors and movie's actors' neighbors   	
            priority_queue<movieNode*, vector<movieNode*>, movieCompare> temp;
            if(actor.second->neighbors.find(newActor->actorName) == actor.second->neighbors.end()){
                pair<priority_queue<movieNode*, vector<movieNode*>, movieCompare>, actorNode*> tmp1 = make_pair(temp, newActor);
                pair<priority_queue<movieNode*, vector<movieNode*>, movieCompare>, actorNode*> tmp2 = make_pair(temp, actor.second);
               
                actor.second->neighbors.insert(make_pair(newActor->actorName, tmp1));
		newActor->neighbors.insert(make_pair(actor.second->actorName, tmp2));		
            }
	    
	    (((actor.second->neighbors).at(newActor->actorName)).first).push(newMovie);
	    (newActor->neighbors.at(actor.second->actorName).first).push(newMovie);   
        }
	}

	// movie's Node doesn't have this actor
        if(newMovie->actors.find(actor_name) == newMovie->actors.end()){
            newMovie->actors.insert(make_pair(actor_name, newActor));
        }
    }
    if (!infile.eof()) {
        cerr << "Failed to read " << in_filename << "!\n";
        return false;
    }
    infile.close();

    return true;
}
