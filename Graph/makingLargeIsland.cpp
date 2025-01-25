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

// TOPIC: Disjoint set data structure
class DisjointSet {

public:
  vector<int> rank, size, parent;

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

int largestIsland(vector<vector<int>> &grid) {

  int n = grid.size();
  int ans = 1;
  DisjointSet ds = DisjointSet(n * n);

  int dirX[] = {0, 1, 0, -1};
  int dirY[] = {1, 0, -1, 0};

  vector<pair<int, int>> zeros;

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (grid[i][j] == 0) {
        zeros.pb({i, j});
        continue;
      }
      int cell = i * n + j;
      for (int k = 0; k < 4; k++) {
        int newI = i + dirX[k];
        int newJ = j + dirY[k];
        int adjCell = newI * n + newJ;
        if (newI >= 0 && newI < n && newJ >= 0 && newJ < n &&
            grid[newI][newJ] == 1) {
          // make them union
          int ultPCell = ds.findParent(cell);
          int ultPAdjCell = ds.findParent(adjCell);
          if (ultPCell != ultPAdjCell) {
            ds.unionBySize(ultPAdjCell, ultPCell);
          }
        }
      }
    }
  }

  for (int i = 0; i < n * n; i++) {
    ans = max(ans, ds.size[i]);
  }

  // now to each zero and try to make it one and increament island size
  for (auto it : zeros) {
    int x = it.first;
    int y = it.second;
    int cell = x * n + y;
    int tempAns = 1;
    set<int> parentSet;
    for (int k = 0; k < 4; k++) {
      int newI = x + dirX[k];
      int newJ = y + dirY[k];
      int adjCell = newI * n + newJ;
      if (newI >= 0 && newI < n && newJ >= 0 && newJ < n &&
          grid[newI][newJ] == 1) {
        // make them union
        int ultPAdjCell = ds.findParent(adjCell);
        if (parentSet.find(ultPAdjCell) == parentSet.end()) {
          parentSet.insert(ultPAdjCell);
          tempAns += ds.size[ultPAdjCell];
        }
      }
    }
    ans = max(ans, tempAns);
  }

  return ans;
}

int main() {
#ifndef ONLINE_JUDGE
  freopen("Error.txt", "w", stderr);
#endif
}
