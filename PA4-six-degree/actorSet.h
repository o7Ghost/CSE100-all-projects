#ifndef actorSet_h
#define actorSet_h

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "CNActor.h"
#include "CNMovie.h"
#include <unordered_map>
#include <vector>
#include <queue>


using namespace std;

class CNmovieCompare{
  public:
  bool operator() (CNMovie* lhs, CNMovie* rhs) const
  {
    return(lhs->movieYear > rhs->movieYear); 
  }

};

class actorSet{
  public:
 
  CNActor* root = nullptr;
  int height = 0;
  int setSize = 0;

  CNActor* findParent(CNActor* a);
  void connectUnion(CNActor* a1, CNActor* a2);
  void ufind(string actor1, string actor2, ofstream& i);
  bool loadFromFile(const char* in_filename, bool use_weighted_edges);
  unordered_map<string, CNMovie*> movieMap;
  unordered_map<string, CNActor*> actorMap;
  priority_queue<CNMovie*, vector<CNMovie*>, CNmovieCompare>sortedMovies;

  private:

};
#endif
