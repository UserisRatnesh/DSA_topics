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

// we can also use color vector to keep track of unvisited(uncoloredd)
bool bfs(int i, vector<int> adj[], vector<bool> &vis, vector<int> &color) {
  queue<pair<int, int>> que;
  vis[i] = true;
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

      if (vis[child] && color[child] == col) {
        return false;
      }
      if (!vis[child]) {
        vis[child] = true;
        color[child] = col ^ 1;
        que.push({child, node});
      }
    }
  }
  return true;
}

bool isBipartite(int v, vector<int> adj[]) {
  vector<int> color(v, -1);
  vector<bool> vis(v, false);

  for (int i = 0; i < v; ++i) {
    if (!vis[i]) {
      // bfs call
      if (!bfs(i, adj, vis, color)) {
        return false;
      }
    }
  }

  return true;
}

int main() {
  fastio(); // To enable fast IO.
}
