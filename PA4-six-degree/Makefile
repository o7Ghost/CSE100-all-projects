# A simple makefile for CSE 100 PA4

CC=g++
CXXFLAGS=-std=c++11 -Wall -pedantic
LDFLAGS=

# if passed "type=opt" at command-line, compile with "-O3" flag (otherwise use "-g" for debugging)

ifeq ($(type),opt)
	CPPFLAGS += -O3
	LDFLAGS += -O3
else
	CPPFLAGS += -g
	LDFLAGS += -g
endif


all: actorconnections pathfinder


# include what ever source code *.h files pathfinder relies on (these are merely the ones that were used in the solution)

pathfinder: ActorGraph.o

actorconnections: actorSet.o ActorGraph.o

# include what ever source code *.h files ActorGraph relies on (these are merely the ones that were used in the solution)

# Note: you do not have to include a *.cpp file if it aleady has a paired *.h file that is already included with class/method headers

#main: ActorGraph.o actorNode.o movieNode.o

ActorGraph.o: actorNode.h movieNode.h ActorGraph.h

actorSet.o: CNActor.o CNMovie.o actorSet.h

CNMovie.o: CNMovie.h

CNActor.o: CNActor.h

clean:
	rm -f pathfinder *.o core*

