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

vector<int> findOrder(int N, vector<vector<int>> arr) {
  // First create the adj list
  vector<int> adj[N];
  int e = arr.size();
  for (int i = 0; i < e; ++i) {
    int source = arr[i][1];
    int dest = arr[i][0];
    adj[source].pb(dest);
  }

  // Now we have adj list
  // Now perform topo sort if result vector has all the vertices then possible

  vector<int> indeg(N, 0);
  for (int i = 0; i < N; i++) {
    for (int child : adj[i]) {
      indeg[child]++;
    }
  }

  queue<int> que;
  for (int i = 0; i < N; i++) {
    if (indeg[i] == 0) {
      que.push(i);
    }
  }

  vector<int> ans;
  while (!que.empty()) {
    int node = que.front();
    que.pop();
    ans.pb(node);
    for (int child : adj[node]) {
      indeg[child]--;
      if (indeg[child] == 0) {
        que.push(child);
      }
    }
  }
  if (ans.size() == N) {
    return ans;
  }
  ans.clear();
  return ans;
}

int main() {
  fastio(); // To enable fast IO.
}
