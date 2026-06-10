// solution.cpp — THIS IS WHAT YOU WILL WORK ON.
//
// Write your algorithm ONLY inside the solve() function below.
// Do not add other functions. Do not modify harness.h.
//
// Compile: g++ -O2 -std=c++17 solution.cpp -o solution
// Run:     ./solution ../maps/soal1.txt output.txt
// View:    open engine/index.html, select the question/map, drag output.txt, click Play/Run.

#include "harness.h"
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

  // for cycling the neighbouring cells
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


// First approach, simple DFS - will find the path but not the shortest path.
// Code example
// Cell cur = start;
// visited.push_back(cur);
// while(cur != goal)
// {
//   int nr = cur.first + 0;
//   int nc = cur.second + 1;
//   if(!inBounds(nr,nc) || isWall(grid[nr][nc])) break;
//   Cell nx = {nr, nc};
//   came_from[nx] = cur;
//   visited.push_back(nx);
//   cur = nx;
// }

// Simple DFS - working solution for map 1 and map 2
//lets try simple DFS
/* Steps
1. if the current cell is the target - stop
2. add all in bounds, non visited, non walls neighbours to stack
3. repeat from step 1 until stack is empty or target found
*/
/*
  int dr[] = {0, -1, 0, 1};
  int dc[] = {-1, 0, 1, 0};
  int rows = grid.size();
  int cols = grid.at(0).size();
  vector<vector<bool>> discovered(rows, vector<bool>(cols, false));

  vector<Cell> stack;
  stack.push_back(start);
  discovered[start.first][start.second] = true;


  while(!stack.empty())
  {
    Cell cur = stack.back();
    stack.pop_back();

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
        stack.push_back(nx);
        
      }
    }
  }
*/



// BFS for map 2
/*
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
*/




// Working solution for all 3 maps - Djikstra's algorithm
// map 1 - Visited=36  PathLen=10
// map 2 - Visited=35  PathLen=14
// map 3 - Visited=272  PathLen=46
/*
  int dr[] = {1, 0, -1, 0};
  int dc[] = {0, 1, 0, -1};
  int rows = grid.size();
  int cols = grid.at(0).size();
  
  struct Compare {
    bool operator()(const pair<int,Cell>& a, const pair<int,Cell>& b) const {
      return a.first > b.first; // smaller weight = higher priority
    }
  };

  priority_queue<pair<int, Cell>, vector<pair<int, Cell>>, Compare> pq;
  vector<vector<int>> distance(rows, vector<int>(cols, INT_MAX));

  pq.push({0, start});
  distance[start.first][start.second] = 0;

  while(!pq.empty())
  {
    pair<int, Cell> element = pq.top();
    pq.pop();

    int cost = element.first;
    Cell cur = element.second;

    if(cost != distance[cur.first][cur.second]) continue;

    visited.push_back(cur);

    if(cur == goal) break;

    for(int x = 0; x < 4; x++)
    {
      int nr = cur.first + dr[x];
      int nc = cur.second + dc[x];
      if(inBounds(nr,nc) && !isWall(grid[nr][nc]))
      {
        int newCost = cost + cellCost(grid[nr][nc]);
        if(newCost < distance[nr][nc])
        {
          distance[nr][nc] = newCost;
          came_from[{nr, nc}] = cur; 
          pq.push({newCost, {nr, nc}});
        }
      }
    }
  }

*/



//  g++ -O2 -std=c++17 solution.cpp -o solution 
//  ./solution ../maps/soal1.txt output.txt


// For report:
// introduce participants, data structure used for the algorithms, explain which solutions used for each pb and do comparative analysis