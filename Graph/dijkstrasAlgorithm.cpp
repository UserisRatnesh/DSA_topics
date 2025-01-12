#include <iostream>
#include <queue>
#include <set>
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

// Gives TLE
void dfs(int source, vector<vector<int>> adj[], vector<int> &ans) {

  int cost = ans[source];
  for (vector<int> vec : adj[source]) {
    int child = vec[0];
    int currCost = vec[1];
    int totalCost = cost + currCost;

    if (totalCost < ans[child]) {
      ans[child] = totalCost;
      dfs(child, adj, ans);
    }
  }
}

vector<int> shortestPathToEachNode(int v, vector<vector<int>> adj[], int s) {
  vector<int> ans(v, 1e9);
  ans[s] = 0;
  dfs(s, adj, ans);

  return ans;
}

// Now we will be using Dijkstra's algorithm

// ### USING MIN HEAP
vector<int> dijkstraMinHeap(int source, int v, vector<vector<int>> adj[]) {

  vector<int> ans(v, 1e9);
  ans[source] = 0;
  vector<bool> vis(v, false);
  vis[source] = true;

  priority_queue<pair<int, int>, vector<pair<int, int>>,
                 greater<pair<int, int>>>
      minHeap;
  minHeap.push({0, source});

  while (!minHeap.empty()) {
    int node = minHeap.top().second;
    int wt = minHeap.top().first;
    minHeap.pop();

    for (vector<int> vec : adj[node]) {
      int child = vec[0];
      int dt = vec[1];
      int totalCost = wt + dt;
      if (totalCost < ans[child]) {
        minHeap.push({totalCost, child});
        ans[child] = totalCost;
      }
    }
  }

  return ans;
}

vector<int> dijkstraSet(int source, int v, vector<vector<int>> adj[]) {

  vector<int> dist(v, 1e9);
  dist[source] = 0;
  set<pair<int, int>> st;
  st.insert({0, source});

  while (!st.empty()) {
    int node = st.begin()->second;
    int wt = st.begin()->first;
    st.erase(st.begin());

    for (vector<int> vec : adj[node]) {
      int edgeWt = vec[1];
      int adjNode = vec[0];

      int totalCost = wt + edgeWt;
      if (totalCost < dist[adjNode]) {
        if (dist[adjNode] != 1e9) {
          // It means that there exists path that is more costly to reach
          // adjNode this the current one so delete that path
          st.erase({dist[adjNode], adjNode});
        }
        dist[adjNode] = totalCost;
        st.insert({totalCost, adjNode});
      }
    }
  }

  return dist;
}

int main() {
  fastio(); // To enable fast IO.
}
