#include <climits>
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

// NOTE: DFS approach only works if it does not have negative cycle
// If it has negative cycle then will lead to infinite loop
// And here it does not hvae negative cycle since the it is unit weighted graph
void dfs(int start, vector<int> adj[], vector<int> &ans) {
  for (int child : adj[start]) {
    int currCost = ans[start] + 1;
    if (currCost < ans[child]) {
      ans[child] = currCost;
      dfs(child, adj, ans);
    }
  }
}

vector<int> shortestPath(vector<vector<int>> &edges, int n, int m) {
  vector<int> adj[n];
  for (int i = 0; i < m; ++i) {
    int u = edges[i][0];
    int v = edges[i][1];
    adj[u].pb(v);
    adj[v].pb(u);
  }

  vector<int> ans(n, INT_MAX);
  ans[0] = 0;
  dfs(0, adj, ans);

  for (int i = 0; i < n; ++i) {
    if (ans[i] == INT_MAX) {
      ans[i] = -1;
    }
  }

  return ans;
}

// NOTE: BFS approach

vector<int> shortesPath_bfs(vector<vector<int>> &edges, int n, int m) {
  vector<int> adj[n];
  for (int i = 0; i < m; ++i) {
    int u = edges[i][0];
    int v = edges[i][1];
    adj[u].pb(v);
    adj[v].pb(u);
  }

  vector<int> dist(n, INT_MAX);
  dist[0] = 0;

  // DFS
  queue<pair<int, int>> que;
  que.push({0, 0});
  while (!que.empty()) {
    int node = que.front().first;
    int cost = que.front().second;
    que.pop();

    for (auto child : adj[node]) {

      // HACK: Agar comment kiya hua code use karenge to negative cycle me phir
      // se infinite loop chal jayega, kyoki negative weight har baar cost ko
      // reduce kar dega
      // And here it will not cause any problem since it is unit weighted graph
      // So we can use either of two

      // if (cost + 1 < dist[child]) {
      //   dist[child] = cost + 1;
      //   que.push({child, cost + 1});
      // }

      if (dist[child] == INT_MAX) {
        dist[child] = cost + 1;
        que.push({child, cost + 1});
      }
    }
  }

  for (auto &it : dist) {
    if (it == INT_MAX) {
      it = -1;
    }
  }

  return dist;
}

int main() {
  fastio(); // To enable fast IO.
}
