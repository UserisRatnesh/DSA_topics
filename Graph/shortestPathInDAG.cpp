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
  for (int i = 0; i < n; ++i) {
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

int main() {
  fastio(); // To enable fast IO.
}
