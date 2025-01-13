#include <climits>
#include <iostream>
#include <vector>
using namespace std;

#define fastio()                                                               \
  ios_base::sync_with_stdio(false);                                            \
  cin.tie(NULL);                                                               \
  cout.tie(NULL)
#define MOD 1000000007
#define MOD1 998244353
#define INF 1e18
#define nline "\n"
#define pb push_back
#define ppb pop_back
#define mp make_pair
#define ff first
#define ss second
#define PI 3.141592653589793238462
#define set_bits __builtin_popcountll
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()

typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;

// Using BFS that is usnig Dijkstra's algorithm
// Working
int shortestPathBFS(vector<vector<int>> &grid, pair<int, int> source,
                    pair<int, int> dest) {
  if (grid[source.first][source.second] == 0 ||
      grid[dest.first][dest.second] == 0) {
    return -1;
  }

  if (source.first == dest.first && source.second == dest.second) {
    return 0;
  }

  int rows = grid.size();
  int cols = grid[0].size();
  vector<vector<int>> mat(rows, vector<int>(cols, INT_MAX));
  mat[source.first][source.second] = 0;
  queue<pair<int, pair<int, int>>> que;
  que.push({0, source});

  int dx[] = {0, 1, 0, -1};
  int dy[] = {1, 0, -1, 0};

  while (!que.empty()) {
    int cost = que.front().first;
    int x = que.front().second.first;
    int y = que.front().second.second;
    que.pop();

    for (int i = 0; i < 4; ++i) {
      int newX = x + dx[i];
      int newY = y + dy[i];

      if (newX >= 0 && newX < rows && newY >= 0 && newY < cols &&
          grid[newX][newY] == 1) {
        int totalCost = cost + 1;
        if (totalCost < mat[newX][newY]) {
          mat[newX][newY] = totalCost;
          que.push({totalCost, {newX, newY}});

          if (newX == dest.first && newY == dest.second) {
            return totalCost;
          }
        }
      }
    }
  }

  return -1;
}

// We can also use priority Queue
int shortestPathPriorityQ(vector<vector<int>> &grid, pair<int, int> source,
                          pair<int, int> dest) {
  if (grid[source.first][source.second] == 0 ||
      grid[dest.first][dest.second] == 0) {
    return -1;
  }

  if (source.first == dest.first && source.second == dest.second) {
    return 0;
  }

  int rows = grid.size();
  int cols = grid[0].size();
  vector<vector<int>> dist(rows, vector<int>(cols, INT_MAX));
  dist[source.first][source.second] = 0;
  priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>,
                 greater<pair<int, pair<int, int>>>>
      que;
  que.push({0, source});

  int dx[] = {0, 1, 0, -1};
  int dy[] = {1, 0, -1, 0};

  while (!que.empty()) {
    int cost = que.top().first;
    int x = que.top().second.first;
    int y = que.top().second.second;
    que.pop();

    for (int i = 0; i < 4; ++i) {
      int newX = x + dx[i];
      int newY = y + dy[i];

      if (newX >= 0 && newX < rows && newY >= 0 && newY < cols &&
          grid[newX][newY] == 1) {
        int totalCost = cost + 1;
        if (totalCost < dist[newX][newY]) {
          dist[newX][newY] = totalCost;
          que.push({totalCost, {newX, newY}});

          if (newX == dest.first && newY == dest.second) {
            return totalCost;
          }
        }
      }
    }
  }

  return -1;
}

// Using DFS
// TLE
void dfs(vector<vector<int>> &grid, pair<int, int> source, pair<int, int> dest,
         int cost, vector<vector<bool>> &vis, int &ans) {

  if (source.first == dest.first && source.second == dest.second) {
    ans = min(ans, cost);
    return;
  }
  int row = grid.size();
  int col = grid[0].size();
  int dx[] = {0, 1, 0, -1};
  int dy[] = {1, 0, -1, 0};
  vis[source.first][source.second] = true;
  for (int i = 0; i < 4; i++) {
    int newX = source.first + dx[i];
    int newY = source.second + dy[i];
    if (newX >= 0 && newX < row && newY >= 0 && newY < col &&
        vis[newX][newY] == false && grid[newX][newY] == 1) {
      dfs(grid, {newX, newY}, dest, cost + 1, vis, ans);
    }
  }
  vis[source.first][source.second] = false;
}

int shortestPath(vector<vector<int>> &grid, pair<int, int> source,
                 pair<int, int> dest) {
  if (grid[source.first][source.second] == 0 ||
      grid[dest.first][dest.second] == 0) {
    return -1;
  }
  int ans = INT_MAX;
  int rows = grid.size();
  int cols = grid[0].size();
  vector<vector<bool>> vis(rows, vector<bool>(cols, false));
  dfs(grid, source, dest, 0, vis, ans);

  if (ans == INT_MAX) {
    return -1;
  }

  return ans;
}

int main() {
  fastio(); // To enable fast IO.
}
