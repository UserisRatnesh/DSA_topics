#ifndef ONLINE_JUDGE
#include "/usr/local/include/bits/stdc++.h"
#else
#include <bits/stdc++.h>
#endif

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

#ifndef ONLINE_JUDGE
#define debug(x)                                                               \
  cerr << #x << " ";                                                           \
  _print(x);                                                                   \
  cerr << endl;
#else
#define debug(x)
#endif

void _print(ll t) { cerr << t; }
void _print(int t) { cerr << t; }
void _print(string t) { cerr << t; }
void _print(char t) { cerr << t; }
void _print(lld t) { cerr << t; }
void _print(double t) { cerr << t; }
void _print(ull t) { cerr << t; }

int primeAlgo(int n, int start, vector<int> adj[], vector<bool> &vis) {

  int edgeUsed = 0;
  queue<pair<int, int>> que; // {node, parent}
  que.push({start, -1});
  while (!que.empty()) {
    int node = que.front().first;
    int parent = que.front().second;
    que.pop();

    if (vis[node]) {
      continue;
    }
    vis[node] = true;

    if (parent != -1) {
      edgeUsed++;
    }
    for (int child : adj[node]) {
      if (!vis[child]) {
        que.push({child, node});
      }
    }
  }

  return edgeUsed;
}

int makeConnected(int n, vector<vector<int>> &edges) {

  // make adj list
  vector<int> adj[n];
  for (auto it : edges) {
    int u = it[0];
    int v = it[1];
    adj[u].pb(v);
    adj[v].pb(u);
  }

  vector<bool> vis(n, false);
  int components = 0;
  int edgesUsed = 0;
  for (int i = 0; i < n; i++) {
    if (!vis[i]) {
      components++;
      // performs prime's algorithm
      edgesUsed += primeAlgo(n, i, adj, vis);
    }
  }

  int totalEdges = edges.size();
  if ((totalEdges - edgesUsed) >= components - 1) {
    return components - 1;
  }
  return -1;
}

// TOPIC: Disjoint set data structure
class DisjointSet {
  vector<int> rank, size, parent;

public:
  DisjointSet(int n) {

    rank.resize(n + 1, 0);
    size.resize(n + 1, 1);
    parent.resize(n + 1);
    for (int i = 0; i <= n; i++) {
      parent[i] = i;
    }
  }

  // First time log n and after that constant time
  int findParent(int u) {
    if (u == parent[u]) {
      return u;
    }
    return parent[u] = findParent(parent[u]);
  }

  void unionByRank(int u, int v) {
    int ulp_u = findParent(u);
    int ulp_v = findParent(v);

    if (ulp_u == ulp_v) {
      return;
    }

    if (rank[ulp_u] < rank[ulp_v]) {
      parent[ulp_u] = ulp_v;
    } else if (rank[ulp_v] < rank[ulp_u]) {
      parent[ulp_v] = ulp_u;
    } else {
      parent[ulp_v] = ulp_u;
      rank[ulp_u]++;
    }
  }

  void unionBySize(int u, int v) {
    int ulp_u = findParent(u);
    int ulp_v = findParent(v);

    if (ulp_u == ulp_v) {
      return;
    }

    if (size[ulp_u] < size[ulp_v]) {
      parent[ulp_u] = ulp_v;
      size[ulp_v] += size[ulp_u];
    } else {
      parent[ulp_v] = ulp_u;
      size[ulp_u] += size[ulp_v];
    }
  }
};

int makeConnectedBetter(int n, vector<vector<int>> &edges) {

  int totalEdges = edges.size();

  if (totalEdges < n - 1) {
    return -1;
  }

  DisjointSet ds = DisjointSet(n);
  for (auto it : edges) {
    ds.unionByRank(it[0], it[1]);
  }

  int count = 0;
  for (int i = 0; i < n; i++) {
    if (ds.findParent(i) == i) {
      count++;
    }
  }

  return count - 1;
}

int main() {
#ifndef ONLINE_JUDGE
  freopen("Error.txt", "w", stderr);
#endif
}
