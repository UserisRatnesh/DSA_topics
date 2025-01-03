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

// Topological sort using dfs algorithm
void topoSortDfs(int i, vector<int> adj[], stack<int> &stk, vector<bool> &vis) {
  vis[i] = true;
  for (int child : adj[i]) {
    if (!vis[child]) {
      topoSortDfs(child, adj, stk, vis);
    }
  }
  stk.push(i);
}

void topoMain(int v, vector<int> adj[]) {
  stack<int> stk;
  vector<bool> vis(v, false);
  for (int i = 0; i < v; ++i) {
    if (!vis[i]) {
      topoSortDfs(i, adj, stk, vis);
    }
  }

  // print the nodes in topo sort order
  while (!stk.empty()) {
    cout << stk.top() << " ";
    stk.pop();
  }
  cout << endl;
}

// Topo sort using BFS algorithm
vector<int> bfs(int v, vector<int> adj[]) {

  vector<int> indeg(v, 0);
  // update indeg vector
  for (int i = 0; i < v; ++i) {
    for (int child : adj[i]) {
      indeg[child]++;
    }
  }

  queue<int> que;
  // put all nodes having indeg as zero
  for (int i = 0; i < v; ++i) {
    int deg = indeg[i];
    if (deg == 0) {
      que.push(i);
    }
  }

  vector<int> ans;
  while (!que.empty()) {
    int node = que.front();
    ans.push_back(node);
    que.pop();
    for (int child : adj[node]) {
      indeg[child]--;
      if (indeg[child] == 0) {
        que.push(child);
      }
    }
  }

  return ans;
}

int main() {
  fastio(); // To enable fast IO.
}
