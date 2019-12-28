#include <stdlib.h>
#include <stdio.h>
#include "CNActor.h"
#include "CNMovie.h"
#include "actorSet.h"
#include <unordered_map>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

CNActor* actorSet::findParent(CNActor* a1){
  CNActor* curr = a1;
  while(curr->parent != curr){
    //path compression 
    if(curr != root){
      curr->parent = root;
    }
    curr = curr->parent;
  }
  return curr;
}

void actorSet::connectUnion(CNActor* a1, CNActor* a2){
  
 // cout << a1->actorName << endl;
//  cout << a2->actorName << endl;
 // cout << "-----------------------" << endl;
  CNActor* a1Root = findParent(a1);
  CNActor* a2Root = findParent(a2);
  if(a1Root != a2Root){
    a1Root->parent = a2Root;
    root = a2Root;
    root->parent = root; 
  }
}

void actorSet::ufind(string actorOne, string actorTwo, ofstream& i){
  CNActor* startActor = actorMap.at(actorOne);
  CNActor* endActor = actorMap.at(actorTwo);

  while(!sortedMovies.empty()){
    CNMovie* tempMovie = sortedMovies.top();
    //cout << tempMovie->movieName << " " << tempMovie->movieYear << endl;
    sortedMovies.pop();
    for(int i = 0; i < tempMovie->twoActors.size() - 1; i++){
      CNActor* tempOne = tempMovie->twoActors.at(i);
      CNActor* tempTwo = tempMovie->twoActors.at(i+1);
      //cout << tempOne->actorName << endl;
      //cout << tempTwo ->actorName << endl;
      if(root == nullptr){
        root = tempOne;
	//cout << tempOne->actorName << endl;
 	connectUnion(tempTwo, tempOne);
      }
      else{
        connectUnion(tempTwo, tempOne);
      }
    }

      for(int i = 0; i < tempMovie->twoActors.size(); i++){
       // cout << tempMovie->twoActors.at(i)->actorName << endl;
      }
      //cout << "-------" << endl;
   //cout << tempMovie->twoActors.size();
   // cout << startActor->actorName <<"'s root is " << findParent(startActor)->actorName << endl;
   // cout << endActor->actorName << "'s root is " << findParent(endActor)->actorName << endl;
   // cout << "-------------" << endl;
    if(findParent(startActor) == findParent(endActor)){
    //  cout << actorOne << " " << actorTwo << " " << tempMovie->movieYear << endl;
      
      //reset conditions back 
      while(!sortedMovies.empty()){
        sortedMovies.pop();
      }
      for(auto movie : movieMap){
        sortedMovies.push(movie.second);
      }
      for( auto actor: actorMap){
        actor.second->parent = actor.second;	
      }
      i << actorOne << "\t" << actorTwo << "\t" << tempMovie->movieYear << endl;
      root = nullptr; 
      return;
    }
  }

}

bool actorSet::loadFromFile(const char* in_filename, bool use_weighted_edges) {
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
        
        CNMovie* newMovie;
        CNActor* newActor;
   
        // we have an actor/movie relationship, now what?
        //create new movie Node if only it appears the first time
        if(movieMap.find(movieName) == movieMap.end()){
            newMovie = new CNMovie(movie_title, movie_year);
            movieMap.insert(make_pair(movieName, newMovie));
        }
        else{
            newMovie = movieMap.find(movieName)->second;
        }
        
        
        //create new actor Node if only it appears the firs time
        if(actorMap.find(actor_name) == actorMap.end()){
            newActor = new CNActor(actor_name);
            actorMap.insert(make_pair(actor_name, newActor));
        }
        else{
            newActor = actorMap.find(actor_name)->second;
        }       

	// movie's Node doesn't have this actor
        if(newMovie->actors.find(actor_name) == newMovie->actors.end()){
            newMovie->actors.insert(make_pair(actor_name, newActor));
	    newMovie->twoActors.push_back(newActor);
        }
    }
   
    //sort all the movies by year
   
    for( auto movie : movieMap){
        sortedMovies.push(movie.second);
    }

    if (!infile.eof()) {
        cerr << "Failed to read " << in_filename << "!\n";
        return false;
    }
    infile.close();

    return true;
}



