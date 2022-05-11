# Copyright 2022
# Jack Oberman

astar:	src/astar.cc
	g++ -std=c++17 -I.. -Wall -o astar src/astar.cc

clean:
	rm astar
