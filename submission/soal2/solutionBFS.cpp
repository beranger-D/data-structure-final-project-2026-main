// solution.cpp — THIS IS WHAT YOU WILL WORK ON.
//
// Write your algorithm ONLY inside the solve() function below.
// Do not add other functions. Do not modify harness.h.
//
// Compile: g++ -O2 -std=c++17 solution.cpp -o solution
// Run:     ./solution ../maps/soal1.txt output.txt
// View:    open engine/index.html, select the question/map, drag output.txt, click Play/Run.

#include "../harness.h"
// Tambahkan include yang kalian butuhkan, contoh:
#include <queue>
// #include <set>
// #include <map>

vector<Cell> solve(vector<vector<char>>& grid, Cell start, Cell goal){
  vector<Cell> visited;  // list of visited cells (ordered) — return this

  // ===================== WRITE YOUR ALGORITHM HERE =====================
  //
  // Four movement directions (up, down, left, right):
  //   int dr[] = {-1, 1, 0, 0};
  //   int dc[] = { 0, 0,-1, 1};
  // Neighbor of cell (r,c) is calculated: nr = r + dr[k], nc = c + dc[k] (loop k = 0..3)
  //
  // Tools from harness.h that you can use:
  //   inBounds(nr, nc)         -> true if (nr,nc) is still inside the grid
  //   isWall(grid[nr][nc])     -> true if the cell is a wall (cannot be passed through)
  //   cellCost(grid[nr][nc])   -> cost to enter the cell: 1, or numbers 1-9 for weighted cells
  //
  // REQUIRED: every time you find a new neighbor to be processed, record its parent:
  //   came_from[neighbor] = current_cell;
  // Without this line, the final path cannot be reconstructed and the visualization tool will show FAILED.
  //
  // When a cell is processed, insert it into the exploration trace:
  //   visited.push_back(current_cell);
  //
  // =========================================================================
  

  /////////////////
  // BFS

  int dr[] = {0, -1, 0, 1};
  int dc[] = {-1, 0, 1, 0};
  int rows = grid.size();
  int cols = grid.at(0).size();
  vector<vector<bool>> discovered(rows, vector<bool>(cols, false));

  queue<Cell> queue;
  queue.push(start);
  discovered[start.first][start.second] = true;


  while(!queue.empty())
  {
    Cell cur = queue.front();
    queue.pop();

    visited.push_back(cur);

    if(cur == goal) break;

    for(int x = 0; x < 4; x++)
    {
      int nr = cur.first + dr[x];
      int nc = cur.second + dc[x];
      if(inBounds(nr,nc) && !isWall(grid[nr][nc]) && !discovered[nr][nc])
      {
        Cell nx = {nr, nc};
        came_from[nx] = cur; 
        discovered[nr][nc] = true;
        queue.push(nx);
        
      }
    }
  }

  return visited;
}

//  g++ -O2 -std=c++17 solution.cpp -o solution 
//  ./solution ../maps/soal1.txt output.txt


// For report:
// introduce participants, data structure used for the algorithms, explain which solutions used for each pb and do comparative analysis

/*

res     DFS   BFS    Djikstra
map 1   11,10 36,10  36,10
map 2   15,14 37,14  35,14
map 3                272,46

*/