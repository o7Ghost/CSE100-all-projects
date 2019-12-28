#ifndef CNActor_h
#define CNActor_h

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
using namespace std;
class CNMovie;

class CNActor{
  public:

    string actorName;
    CNActor* parent;
    CNActor(string name): actorName(name), parent(this){}  
};
#endif
