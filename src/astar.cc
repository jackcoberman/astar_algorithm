// Copyright 2022
// Jack Oberman

#include <iostream>
#include <cstdlib>  // srand, rand
#include <time.h>  // time (to seed rand)
#include <stdio.h>  // itoa
#include <vector>
#include <cstring>
#include <cfloat>  // FLT_MAX
#include <set>
#include <tuple>
#include <queue>
#include <math.h>
#include <stack>

class Grid {
 public:
  std::vector<std::vector<char>> grid;

  Grid(int num_r, int num_c, double o_density) {
    this->num_r = num_r;
    this->num_c = num_c;
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

  int getRowSize() {
    return num_r;
  }

  int getColSize() {
    return num_c;
  }

 private:
  int num_r = 0;
  int num_c = 0;
};

// shortcut for <int,int> pair
typedef std::pair<int, int> Pair;

// shortcut for <double, pair<int,int>> pair
typedef std::tuple<double, std::pair<int, int>> Tuple;

struct cell {
  Pair parent;
  // f = g + h
  double f, g, h;
  cell() :
    parent(-1,-1),
    f(-1),
    g(-1),
    h(-1) {}
};

// Utility Function to check whether the given cell is valid
bool isValid(Grid grid, const Pair& point) {
  return (point.first >= 0) && (point.first < grid.getRowSize())
         && (point.second >= 0)
	 && (point.second < grid.getColSize());
}

// Utility Function to check whether the given cell is blocked or not
bool isUnblocked(Grid grid, const Pair& point) {
  return grid.grid[point.first][point.second] == '1';
}

double calculateHValue(Grid grid, const Pair& src) {
  // h is estimated with the two points distance formula
  // temp: dest is bottom right
  Pair dest(grid.getRowSize() - 1, grid.getColSize() - 1);
  // h is calculated using euclidean distance
  return sqrt(pow((src.first - dest.first), 2.0)
              + pow((src.second - dest.second), 2.0));
}

void tracePath(cell *cellDetails, int num_r, int num_c) {
  
  cell **cellDetail;
  cellDetail = &cellDetails;
  std::stack<Pair> Path;
  int row = num_r - 1;
  int col = num_c - 1;
  std::cout << "row: " << num_r << " and col: " << num_c << std::endl;
  Pair next_node = cellDetail[row][col].parent;
  std::cout << "wehre we breaking" << std::endl;
  Pair third_node = cellDetail[2][2].parent;
  std::cout << "(2,2)'s parent: (" << third_node.first << "," << third_node.second << ")" << std::endl;
  do {
    Path.push(next_node);
    row = next_node.first;
    col = next_node.second;
  } while (cellDetail[row][col].parent != next_node);
  
  Path.push(Pair(row, col));
  while (!Path.empty()) {
    Pair p = Path.top();
    Path.pop();
    std::cout << "-> (" << p.first << "," << p.second << ") ";
  }
}

void aSearchAlgorithm(Grid grid) {
  // 1) Initialize Open List
  // 2) Initialize the Closed List. Put the starting node
  // on the open list (leaving its f-val at zero)
  bool closedList[grid.getRowSize()][grid.getColSize()];
  memset(closedList, false, sizeof(closedList));

  cell cellDetails[grid.getRowSize()][grid.getColSize()];

  for (int r = 0; r < grid.getRowSize(); ++r) {
    for (int c = 0; c < grid.getColSize(); ++c) {
      cellDetails[r][c].f = FLT_MAX;
      cellDetails[r][c].g = FLT_MAX;
      cellDetails[r][c].h = FLT_MAX;
      cellDetails[r][c].parent = { -1,-1 };
    }
  }

  // Initialize starting node
  cellDetails[0][0].f = 0.0;
  cellDetails[0][0].g = 0.0;
  cellDetails[0][0].h = 0.0;
  cellDetails[0][0].parent = {0, 0};

  std::priority_queue<Tuple, std::vector<Tuple>,
	              std::greater<Tuple>> openList;
  openList.push(std::make_tuple(0.0, std::pair(0,0)));
  // 3) While the open list is not empty
  while (!openList.empty()) {
    // a) find the open node with the least f on the open list, "q"
    const Tuple& p = openList.top();
    int r = std::get<0>(std::get<1>(p));
    int c = std::get<1>(std::get<1>(p));

    // b) pop q off the open list and add to closed list
    closedList[r][c] = true;
    openList.pop();

    // c) generate q's 4 successors and set their parents to q
    for (int x = -1; x <= 1; ++x) {
      for (int y = -1; y <= 1; ++y) {
        Pair neighbor(r + x, c + y);
	// Only process neighboring cell if it's valid
	if (isValid(grid, neighbor)) {
	  std::cout << "(" << x << "," << y << ") is Valid" << std::endl;
	  // TO-DO: i) if the dest cell is same as current successor
	  if (neighbor.first == grid.getRowSize() - 1 &&
              neighbor.second == grid.getColSize() - 1) {
	    std::cout << "Destination cell reached" << std::endl;
	    cellDetails[neighbor.first][neighbor.second].parent = { r, c };
	    tracePath((cell *)cellDetails,
                      grid.getRowSize(),
		      grid.getColSize());
	    return;
	  // ii) else, compute both g and h for successor
	  // successor.g = q.g + distance between successor and q
	  // successor.f = successor.g + successor.h
	  } else if (!closedList[neighbor.first][neighbor.second] &&
                     isUnblocked(grid, neighbor)) {
	    double gNew = cellDetails[r][c].g + 1.0;
	    double hNew = calculateHValue(grid, neighbor); // TO-DO: variable dest
            double fNew = gNew + hNew;
	    std::cout << "f-val: " << fNew << std::endl;

	    // if cell isn't on the open list, add it and record f, g, and h
	    // if cell is on the open list, check to see if its f > fNew
	    // if so, new path is better. update cell's parent and costs
	    if (cellDetails[neighbor.first][neighbor.second].f == -1 ||
                cellDetails[neighbor.first][neighbor.second].f > fNew) {
	      
              openList.push(std::make_tuple(fNew,
                            std::pair(neighbor.first,neighbor.second)));

	      cellDetails[neighbor.first][neighbor.second].g = gNew;
	      cellDetails[neighbor.first][neighbor.second].h = hNew;
	      cellDetails[neighbor.first][neighbor.second].f = fNew;
	      cellDetails[neighbor.first][neighbor.second].parent = {x, y};
	    }
	  }
	}
      }
    }
  }
  std::cout << "Failed to find the destination cell." << std::endl;
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

  aSearchAlgorithm(grid);

  return 1;
}
