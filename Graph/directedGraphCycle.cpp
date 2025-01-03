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

// Detect cycle in a directed graph
bool isCycle(int n, vector<int> adj[]) {
  // I will use kahn's algorithm
  vector<int> indegree(n, 0);
  for (int i = 0; i < n; ++i) {
    for (int child : adj[i]) {
      indegree[child]++;
    }
  }

  queue<int> que;
  for (int i = 0; i < n; ++i) {
    if (indegree[i] == 0) {
      que.push(i);
    }
  }

  vector<int> ans;
  while (!que.empty()) {
    int node = que.front();
    que.pop();
    ans.pb(node);
    for (int child : adj[node]) {
      indegree[child]--;
      if (indegree[child] == 0) {
        que.push(child);
      }
    }
  }

  return ans.size() != n;
}

int main() {
  fastio(); // To enable fast IO.
}
