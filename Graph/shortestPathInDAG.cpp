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

// Without using topo sort
void dfs(int start, vector<pair<int, int>> adj[], vector<int> &ans) {
  for (pair<int, int> p : adj[start]) {
    int child = p.first;
    int cost = p.second;
    int small = min(ans[child], ans[start] + cost);
    if (small < ans[child]) {
      ans[child] = small;
      dfs(child, adj, ans);
    }
  }
}

vector<int> shortestPath(int n, int m, vector<vector<int>> &edges) {
  vector<pair<int, int>> adj[n];
  for (int i = 0; i < m; ++i) {
    int u = edges[i][0];
    int v = edges[i][1];
    int cost = edges[i][2];
    adj[u].pb({v, cost});
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

// Using topo sort
vector<int> topoSort(int n, vector<pair<int, int>> adj[]) {
  vector<int> ans;
  vector<int> indeg(n, 0);
  for (int i = 0; i < n; ++i) {
    for (pair<int, int> p : adj[i]) {
      int child = p.first;
      indeg[child]++;
    }
  }

  queue<int> que;
  for (int i = 0; i < n; ++i) {
    if (indeg[i] == 0) {
      que.push(i);
    }
  }

  while (!que.empty()) {
    int node = que.front();
    que.pop();
    ans.push_back(node);
    for (pair<int, int> p : adj[node]) {
      int child = p.first;
      indeg[child]--;
      if (indeg[child] == 0) {
        que.push(child);
      }
    }
  }
  return ans;
}
vector<int> shortestPathTopoSort(int n, int m, vector<vector<int>> &edges) {
  vector<pair<int, int>> adj[n];
  for (int i = 0; i < m; ++i) {
    int u = edges[i][0];
    int v = edges[i][1];
    int cost = edges[i][2];
    adj[u].push_back({v, cost});
  }

  vector<int> topo = topoSort(n, adj);
  vector<int> ans(n, INT_MAX);
  ans[0] = 0;
  for (int i = 0; i < n; ++i) {
    int node = topo[i];
    if (ans[node] == INT_MAX) {
      // It is of different component where zero is not present
      continue;
    }
    int costI = ans[node];
    for (pair<int, int> p : adj[node]) {
      int child = p.first;
      int cost = p.second;
      if (costI + cost < ans[child]) {
        ans[child] = costI + cost;
      }
    }
  }

  for (int i = 0; i < n; ++i) {
    if (ans[i] == INT_MAX) {
      ans[i] = -1;
    }
  }

  return ans;
}

int main() {
  fastio(); // To enable fast IO.
}
