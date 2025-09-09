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

bool bfs(int node, vector<int> adj[], vector<int> &colors) {
  queue<int> que;
  que.push(node);
  colors[node] = 0;

  while (!que.empty()) {
    int u = que.front();
    que.pop();

    for (auto child : adj[u]) {
      if (colors[child] == -1) { // can not be parent
        // not visited
        colors[child] = 1 ^ colors[u];
        que.push(child);
      } else if (colors[child] == colors[u]) {
        return false;
      }
    }
  }

  return true;
}

// using DFS

bool dfs(int node, vector<int> adj[], vector<int> &colors) {

  for (int child : adj[node]) {
    if (colors[child] == -1) {
      // not visited
      colors[child] = colors[node] ^ 1;
      if (!dfs(child, adj, colors)) {
        return false;
      }
    } else if (colors[child] == colors[node]) {
      return false;
    }
  }

  return true;
}

bool isBipartite(int v, vector<int> adj[]) {
  vector<int> colors(v, -1);
  for (int i = 0; i < v; ++i) {
    if (colors[i] == -1) {
      // dfs call
      colors[i] = 0;
      if (!dfs(i, adj, colors)) {
        return false;
      }
    }
  }

  return true;
}

int main() {
  fastio(); // To enable fast IO.
}
