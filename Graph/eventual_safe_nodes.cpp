#ifndef ONLINE_JUDGE
#include "/usr/local/include/bits/stdc++.h"
#else
#include <bits/stdc++.h>
#endif

using namespace std;

#define ratnesh()                                                              \
  ios_base::sync_with_stdio(false);                                            \
  cin.tie(NULL);                                                               \
  cout.tie(NULL)
#define MOD 1000000007
#define MOD1 998244353
#define INF 1e18
#define nl "\n"
#define pb push_back
#define ppb pop_back
#define mp make_pair
#define ff first
#define ss second
#define PI 3.141592653589793238462
#define set_bits __builtin_popcountll
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()
#define yes cout << "YES\n"
#define no cout << "NO\n"

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

template <class T, class V> void _print(pair<T, V> p);
template <class T> void _print(vector<T> v);
template <class T> void _print(set<T> v);
template <class T, class V> void _print(map<T, V> v);
template <class T> void _print(multiset<T> v);
template <class T, class V> void _print(pair<T, V> p) {
  cerr << "{";
  _print(p.ff);
  cerr << ",";
  _print(p.ss);
  cerr << "}";
}
template <class T> void _print(vector<T> v) {
  cerr << "[ ";
  for (T i : v) {
    _print(i);
    cerr << " ";
  }
  cerr << "]";
}
template <class T> void _print(set<T> v) {
  cerr << "[ ";
  for (T i : v) {
    _print(i);
    cerr << " ";
  }
  cerr << "]";
}
template <class T> void _print(multiset<T> v) {
  cerr << "[ ";
  for (T i : v) {
    _print(i);
    cerr << " ";
  }
  cerr << "]";
}
template <class T, class V> void _print(map<T, V> v) {
  cerr << "[ ";
  for (auto i : v) {
    _print(i);
    cerr << " ";
  }
  cerr << "]";
}

/*
   _____          _        ____       _
  / ____|        | |      |  _ \     | |
 | |     ___   __| | ___  | |_) | ___| | _____      __
 | |    / _ \ / _` |/ _ \ |  _ < / _ \ |/ _ \ \ /\ / /
 | |___| (_) | (_| |  __/ | |_) |  __/ | (_) \ V  V /
  \_____\___/ \__,_|\___| |____/ \___|_|\___/ \_/\_/

*/

// NOTE: Done using DFS method of cycle detection in directed graph
// TC: O(V+E)
bool isCycle(int node, vector<int> adj[], vector<bool> &vis,
             vector<bool> &pathVis, vector<bool> &check) {

  vis[node] = true;
  pathVis[node] = true;

  for (auto child : adj[node]) {
    if (!vis[child]) {
      if (isCycle(child, adj, vis, pathVis, check)) {
        return true;
      }
    } else if (pathVis[child]) {
      return true;
    }
  }

  // It means the path containing this node does not have any cycle
  // therefore it is a safe node
  check[node] = true;
  pathVis[node] = false;

  return false;
}

// All nodes whose path has at least one cycle is not safe node
vector<int> eventualSafeNodes(int v, vector<int> adj[]) {

  vector<int> safeNodes;
  vector<bool> vis(v, false);
  vector<bool> pathVis(v, false);
  vector<bool> check(v, false);
  for (int i = 0; i < v; i++) {
    if (!vis[i]) {
      isCycle(i, adj, vis, pathVis, check);
    }
  }

  for (int i = 0; i < v; i++) {
    if (check[i]) {
      safeNodes.push_back(i);
    }
  }
  return safeNodes;
}

// NOTE: BFS kahn's algorithm
// TC: O(V+E) + O(V*logV)
vector<int> eventualSafeNodes_kahn(int v, vector<int> adj[]) {

  vector<vector<int>> revAdj(v, vector<int>());
  for (int i = 0; i < v; i++) {
    for (auto it : adj[i]) {
      revAdj[it].push_back(i);
    }
  }

  vector<int> indeg(v, 0);
  for (int i = 0; i < v; i++) {
    for (auto it : revAdj[i]) {
      indeg[it]++;
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
    ans.push_back(node);

    for (auto it : revAdj[node]) {
      indeg[it]--;
      if (indeg[it] == 0) {
        que.push(it);
      }
    }
  }

  sort(ans.begin(), ans.end());
  return ans;
}

int main() {
#ifndef ONLINE_JUDGE
  freopen("Error.txt", "w", stderr);
  freopen("input.txt", "r", stdin);
#endif
  ratnesh();
}
