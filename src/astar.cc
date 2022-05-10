// Copyright 2022
// Jack Oberman

#include <iostream>
#include <cstdlib>  // srand, rand
#include <time.h>  // time
#include <vector>
#include <cstring>

class Grid {
 public:
  int num_r;  // number of rows
  int num_c;  // number of columns
  int o_density;  // density of obstacles (0<= x < 99)
  std::vector<std::vector<int>> grid;

  Grid(int num_row, int num_col, double obstacle_density) {
    num_r = num_row;
    num_c = num_col;
    o_density = obstacle_density;
    int rand_res;
    for (int r = 0; r < num_row; ++r) {
      std::vector<int> row;
      for (int c = 0; c < num_col; ++c) {
        rand_res = rand() % 100;
	std::cout << "rand_res: " << rand_res << " ";
	if (rand_res <= obstacle_density) {
          row.push_back(0);
	  std::cout << "zero" << std::endl;
	} else {
          row.push_back(1);
	  std::cout << "one" << std::endl;
	}
      }
      std::cout << "row size: " + row.size() << std::endl;
      std::cout << "row: ";
      for (int i = 0; i < row.size(); ++i) {
	std::cout << row.at(i) + " ";
      }
      std::cout << "\n";
      grid.push_back(row);
    }
  }

  std::string toString() {
    std::string str;
    for (int r = 0; r < num_r; ++r) {
      for (int c = 0; c < num_c - 1; ++c) {
        str += grid.at(r).at(c) + " ";
	std::cout << grid.at(r).at(c) + " ";
      }
      str += grid.at(r).at(num_c - 1) + "\n";
      std::cout << grid.at(r).at(num_c - 1) << std::endl;
    }
    return str;
  }
};

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

  srand(time(NULL));
  std::vector<std::vector<int>> grid;
  //Grid grid(num_r, num_c, o_density);
  int rand_res;
  int one = 1;
  int zero = 0;
  for (int r = 0; r < num_r; ++r) {
    int count = 0;
    std::vector<int> row;
    while (count < num_c) {
      rand_res = rand() % 100;
      std::cout << "rand_res: " << rand_res << " ";
      if (rand_res <= o_density) {
        row.push_back(zero);
        std::cout << "zero" << std::endl;
      } else {
        row.push_back(one);
        std::cout << "one" << std::endl;
      }
      count++;
    }
    std::cout << "row size: " + row.size() << std::endl;
    std::cout << "row: ";
    for (int i = 0; i < row.size(); ++i) {
      std::cout << row.at(i) + " ";
    }
    std::cout << "\n";
    grid.push_back(row);
  }

  std::cout << "col count: " << grid.size() << std::endl;
  for (int r = 0; r < grid.size(); ++r) {
    std::cout << "row " << r << ": " << grid.at(r).size() << std::endl;
    for (int c = 0; c < grid.at(r).size() - 1; ++c) {
      std::cout << grid.at(r).at(c) + " ";
    }
    std::cout << grid.at(r).at(grid.at(r).size() - 1) << std::endl;
  }
  //std::cout << grid.toString() << std::endl;

  return 1;
}
