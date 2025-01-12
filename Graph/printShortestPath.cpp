#include <climits>
#include <iostream>
#include <queue>
#include <unordered_set>
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

// Optimized code

vector<int> shortestPathDijkstra(int n, int m, vector<vector<int>> &edges) {
  vector<pair<int, int>> adj[n + 1];
  for (int i = 0; i < m; i++) {
    int u = edges[i][0];
    int v = edges[i][1];
    int wt = edges[i][2];
    adj[u].pb({v, wt});
    adj[v].pb({u, wt});
  }

  vector<int> dist(n + 1, INT_MAX);
  dist[1] = 0;
  vector<int> parent(n + 1, -1);

  priority_queue<pair<int, int>, vector<pair<int, int>>,
                 greater<pair<int, int>>>
      minHeap;
  minHeap.push({0, 1});
  while (!minHeap.empty()) {
    int node = minHeap.top().second;
    int wt = minHeap.top().first;
    minHeap.pop();
    for (pair<int, int> p : adj[node]) {
      int child = p.first;
      int edgeWt = p.second;
      int totalCost = edgeWt + wt;
      if (totalCost < dist[child]) {
        dist[child] = totalCost;
        parent[child] = node;
        minHeap.push({totalCost, child});
      }
    }
  }

  vector<int> ans;
  if (dist[n] == INT_MAX) {
    ans.pb(-1);
    return ans;
  }
  ans.pb(n);
  int node = n;
  while (parent[node] != -1) {
    ans.pb(parent[node]);
    node = parent[node];
  }
  ans.pb(dist[n]);
  reverse(ans.begin(), ans.end());

  return ans;
}

// This gives TLE
void dfs(int source, int n, vector<pair<int, int>> adj[], int currCost,
         unordered_set<int> &unset, pair<vector<int>, int> &ans) {
  if (source == n) {
    if (currCost < ans.second) {
      ans.first = vector<int>(unset.begin(), unset.end());
      ans.second = currCost;
    }
    return;
  }

  for (pair<int, int> p : adj[source]) {
    int child = p.first;
    int edgeWt = p.second;
    int totalCost = currCost + edgeWt;
    if (unset.find(child) == unset.end()) {
      unset.insert(child);
      dfs(child, n, adj, totalCost, unset, ans);
      unset.erase(child);
    }
  }
}

vector<int> shortestPath(int n, int m, vector<vector<int>> &edges) {

  vector<pair<int, int>> adj[n + 1];
  for (int i = 0; i < m; ++i) {
    int u = edges[i][0];
    int v = edges[i][1];
    int wt = edges[i][2];

    adj[u].pb({v, wt});
    adj[v].pb({u, wt});
  }

  unordered_set<int> unset;
  unset.insert(1);
  pair<vector<int>, int> ans;
  ans.first.pb(1);
  ans.second = INT_MAX;
  dfs(1, n, adj, 0, unset, ans);

  ans.first.insert(ans.first.begin(), ans.second);
  return ans.first;
}

int main() {
  fastio(); // To enable fast IO.
}
