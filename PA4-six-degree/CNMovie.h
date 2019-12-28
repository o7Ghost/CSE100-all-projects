#ifndef CNMovie_h
#define CNMovie_h

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <unordered_map>
#include <queue>
using namespace std;

class CNActor;

class CNMovie{

  public:
  unordered_map<string,CNActor*> actors;
  vector<CNActor*> twoActors;
  string movieName;
  int movieYear;
  CNMovie(string name, int year): movieName(name), movieYear(year){}

};

#endif
