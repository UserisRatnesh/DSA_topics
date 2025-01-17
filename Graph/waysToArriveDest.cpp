#include <climits>
#include <iostream>
#include <queue>
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

int countRoads(int n, vector<vector<int>> &roads) {

  // First make adj list
  vector<pair<int, int>> adj[n];
  for (vector<int> edge : roads) {
    int u = edge[0];
    int v = edge[1];
    int time = edge[2];
    adj[u].pb({v, time});
    adj[v].pb({u, time});
  }

  vector<int> dist(n, 1e9);
  dist[0] = 0;

  // keeps track of number of ways to reach this node in shortest time
  vector<int> ways(n, 0);
  ways[0] = 1;

  priority_queue<pair<int, int>, vector<pair<int, int>>,
                 greater<pair<int, int>>>
      que;
  que.push({0, 0}); // {time, node}

  while (!que.empty()) {
    auto [time, node] = que.top();
    que.pop();

    for (pair<int, int> p : adj[node]) {
      int newTime = p.second + time;
      int child = p.first;

      // This is the first time we are arriving at this child with shortest path
      if (newTime < dist[child]) {
        que.push({newTime, child});
        dist[child] = newTime;
        ways[child] = ways[node];
      }
      // Not the first time so add the ways to existing ways
      else if (newTime == dist[child]) {
        ways[child] = ways[child] + ways[node];
      }
    }
  }

  return ways[n - 1];
}

int main() {
  fastio(); // To enable fast IO.
}
