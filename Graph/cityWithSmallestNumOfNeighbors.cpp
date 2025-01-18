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

// Use floyd warshall algorithm
int findCity(int n, int m, vector<vector<int>> &edges, int distanceThreshold) {

  vector<vector<int>> mat(n, vector<int>(n, 1e9));
  for (int i = 0; i < n; i++) {
    mat[i][i] = 0;
  }

  for (vector<int> edge : edges) {
    int u = edge[0];
    int v = edge[1];
    int wt = edge[2];
    mat[u][v] = wt;
    mat[v][u] = wt;
  }

  for (int k = 0; k < n; k++) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        mat[i][j] = min(mat[i][j], mat[i][k] + mat[k][j]);
      }
    }
  }

  int ans = -1;
  int mm = n;
  for (int i = 0; i < n; i++) {
    int count =
        count_if(mat[i].begin(), mat[i].end(),
                 [distanceThreshold](int x) { return x <= distanceThreshold; });

    if (count <= mm) {
      ans = i;
      mm = count;
    }
  }

  return ans;
}

int main() {
#ifndef ONLINE_JUDGE
  freopen("Error.txt", "w", stderr);
#endif
}
