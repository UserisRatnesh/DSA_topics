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

// NOTE: Finding MST weight using Prime's algorithm

// TC: E*logE

int mstWeight(int v, vector<vector<int>> adj[]) {

  int mstWt = 0;
  vector<pair<int, int>> edges;
  vector<bool> vis(v, false);
  priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>,
                 greater<pair<int, pair<int, int>>>>
      que;

  // {edgeWt, {node, parent}}
  que.push({0, {0, -1}});

  while (!que.empty()) {
    int wt = que.top().first;
    int node = que.top().second.first;
    int parent = que.top().second.second;
    que.pop();

    if (vis[node]) {
      continue;
    }

    // Add the edge to edges and increase mstWt
    // First node should not be added that node having parent -1 should not be
    // added
    if (parent != -1) {
      edges.pb({node, parent});
    }

    mstWt += wt;
    vis[node] = true;
    for (vector<int> vec : adj[node]) {
      int child = vec[0];
      int edgeWt = vec[1];
      if (!vis[child]) {
        que.push({edgeWt, {child, node}});
      }
    }
  }
  return mstWt;
}

int main() {
#ifndef ONLINE_JUDGE
  freopen("Error.txt", "w", stderr);
#endif
}
