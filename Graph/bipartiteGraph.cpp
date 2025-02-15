#include <iostream>
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

// using BFS
// we can also use color vector to keep track of unvisited(uncoloredd)
bool bfs(int i, vector<int> adj[], vector<int> &color) {
  queue<pair<int, int>> que;
  que.push({i, -1});
  color[i] = 0; // assign a color

  while (!que.empty()) {
    pair<int, int> p = que.front();
    que.pop();
    int node = p.first;
    int parent = p.second;
    int col = color[node];
    for (int child : adj[node]) {
      if (child == parent) {
        continue;
      }

      if (color[child] == -1) {
        color[child] = color[node] ^ 1;
        que.push({child, node});
      } else if (color[child] == color[node]) {
        return false;
      }
    }
  }
  return true;
}

// using DFS

bool dfs(int node, vector<int> adj[], vector<int> &color) {

  for (int child : adj[node]) {
    if (color[child] == -1) {
      // not visited
      color[child] = color[node] ^ 1;
      if (!dfs(child, adj, color)) {
        return false;
      }
    } else if (color[child] != -1 && color[child] == color[node]) {
      return false;
    }
  }

  return true;
}

bool isBipartite(int v, vector<int> adj[]) {
  vector<int> color(v, -1);
  for (int i = 0; i < v; ++i) {
    if (color[i] == -1) {
      // bfs call
      color[i] = 0;
      if (!dfs(i, adj, color)) {
        return false;
      }
    }
  }

  return true;
}

int main() {
  fastio(); // To enable fast IO.
}
