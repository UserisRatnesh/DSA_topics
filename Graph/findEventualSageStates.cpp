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

bool isSafeNode(int i, vector<int> adj[], vector<bool> &vis) {
  vis[i] = true;
  for (int child : adj[i]) {
    if (!vis[child]) {
      if (!isSafeNode(child, adj, vis)) {
        vis[i] = false;
        return false;
      }
    } else {
      vis[i] = false;
      return false;
    }
  }

  vis[i] = false;
  return true;
}

vector<int> eventualSafeNodes(int v, vector<int> adj[]) {

  // Go to each node and ask that if each of it's child finish at terminal node
  // or not
  vector<int> ans;
  vector<bool> vis(v, false);
  for (int i = 0; i < v; ++i) {
    if (isSafeNode(i, adj, vis)) {
      ans.pb(i);
    }
  }

  sort(all(ans));
  return ans;
}

// using kahn algorithm
// This is will not all the nodes that are part of cycle and that are pointing
// to cycle

vector<int> eventualSafeNodesUsingKahn(int v, vector<int> adj[]) {

  // we have to find indegree so reverse the nodes connections
  vector<int> revAdj[v];
  for (int i = 0; i < v; i++) {
    for (int child : adj[i]) {
      revAdj[child].pb(i);
    }
  }

  vector<int> indeg(v, 0);
  for (int i = 0; i < v; i++) {
    for (int child : revAdj[i]) {
      indeg[child]++;
    }
  }

  queue<int> que;
  for (int i = 0; i < v; i++) {
    if (indeg[i] == 0) {
      que.push(i);
    }
  }

  vector<int> ans;
  while (!que.empty()) {
    int node = que.front();
    que.pop();
    ans.pb(node);

    for (int child : revAdj[node]) {
      indeg[child]--;
      if (indeg[child] == 0) {
        que.push(child);
      }
    }
  }

  sort(ans.begin(), ans.end());
  return ans;
}

int main() {
  fastio(); // To enable fast IO.
}
