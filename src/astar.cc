// Copyright 2022
// Jack Oberman

#include <iostream>
#include <cstdlib>  // srand, rand
#include <time.h>  // time (to seed rand)
#include <stdio.h>  // itoa
#include <vector>
#include <cstring>

class Grid {
 public:
  std::vector<std::vector<char>> grid;

  Grid(int num_r, int num_c, double o_density) {
    srand(time(NULL));  // seed rand()
    std::vector<std::vector<char>> temp(num_r, std::vector<char> (num_c));
    for (int r = 0; r < num_r; ++r) {
      for (int c = 0; c < num_c; ++c) {
        temp[r][c] = (rand() % 100 < o_density ? '0' : '1');
      }
    }
    temp[0][0] = '+';
    temp[num_r-1][num_c-1] = 'X';
    grid = temp;
  }

  std::string toString() {
    std::cout << "Random Grid:" << std::endl;
    std::string str = "";
    for (std::vector row : grid) {
      for (char e : row) {
        //sprintf(buffer, "%d", e);
        str = str + e + " ";
      }
      str += "\n";
    }
    return str;
  }
};

void aSearchAlgorithm(Grid grid) {
  // 1) Initialize Open List
  // 2) Initialize the Closed List. Put the starting node
  // on the open list (leaving its f-val at zero)
  // 3) While the open list is not empty
  // a) find the open node with the least f on the open list, "q"
  // b) pop q off the open list
  // c) generate q's 4 successors and set their parents to q
  // d) for each successor
  // i) if successor is the goal, stop search,
  // ii) else, compute both g and h for successor
  // successor.g = q.g + distance between successor and q (using Manhatten distance)
  // successor.f = successor.g + successor.h
  // iii) if a node with the same position as successor is in 
  // the OPEN list which has a lower f than successor, skip this successor
  // iv) if a node with the same position as successor is in the CLOSED
  // list which has a lower f than successor, skip this
  // successor otherwise, add the node to the open list
  // end (for loop)
  // e) push q on the closed list
  // end (while loop)
}

int main(int argc, char* argv[]) {
  if (argc != 4) {
    std::cout << "Need # rows, # cols, and obstacle density" << std::endl;
    exit(-1);
  }
  int num_r = atoi(argv[1]);
  int num_c = atoi(argv[2]);
  int o_density = atoi(argv[3]);

  if (num_r <= 0 || num_c <= 0) {
    std::cout << "Number of rows and columns must be greater than 0" << std::endl;
  }

  if (o_density < 0 || o_density > 99) {
    std::cout << "0 <= Obstacle density < 100" << std::endl;
    exit(-1);
  }

  Grid grid(num_r, num_c, o_density);
  std::cout << grid.toString() << std::endl;
  
  return 1;
}
