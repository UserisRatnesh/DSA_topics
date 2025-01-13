#include <climits>
#include <ios>
#include <iostream>
#include <queue>
#include <vector>
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
#define P pair<int, int>

typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;

// Done using Dijkstra's algorithm
// The biggest questions is which is given the priority stops or cost
// if we give the priority to cost then it not explore paths with more cost but
// less stops so stops needs to be given the priority But we know stops
// increaments peroidically so we do not need to use minHeap rather simple queue
// will do the job
int cheapestFlight(int n, vector<vector<int>> &flights, int source, int dest,
                   int k) {
  vector<vector<pair<int, int>>> adj(n);
  for (vector<int> flight : flights) {
    adj[flight[0]].pb({flight[1], flight[2]});
  }

  // {stops, {node, cost}}
  // ******     QUESTION-> Why is it important to keep cost in que ?
  // Ans -> Kyoki koi vertex kisi path se c1 cost pe reachable hai, and next
  // time wahi vertex kisi aur path ke through c2 cost pe reachable hai to agar
  // hum cost que me pass kiye bina sirf dist ka use karenge to ye hum minimum
  // kar denge kyoki iteration ke time karte hai assign minimum cost to dist let
  // say c1 minimum tha. lekin jab c2 waala que se pop hoga to hum dist se fetch
  // karke bokenge ki ye is cost me reachable hai lekin ye galat hoga. isliye
  // cost ko pass karna jaruri hai

  // ****** SEE NEXT FUNCTION IMPLEMENTED WITHOUT PASSING COST IN QUEUE WITH
  // THIS EXPLAINED PROBLEM ******

  queue<pair<int, pair<int, int>>> q;
  q.push({0, {source, 0}});

  vector<int> dist(n, INT_MAX);
  dist[source] = 0;

  while (!q.empty()) {
    auto [stops, nodeCostPair] = q.front();
    q.pop();

    int node = nodeCostPair.first;
    int cost = nodeCostPair.second;

    // Do not go through path where k exceeds the limit
    if (stops > k)
      continue;

    for (const auto &neighbor : adj[node]) {
      int adjNode = neighbor.first;
      int edgeWeight = neighbor.second;

      if (cost + edgeWeight < dist[adjNode] && stops <= k) {
        dist[adjNode] = cost + edgeWeight;
        q.push({stops + 1, {adjNode, cost + edgeWeight}});
      }
    }
  }

  return dist[dest] == INT_MAX ? -1 : dist[dest];
}

// Not correct solution explained inside above function

int findCheapestPrice(int n, vector<vector<int>> &flights, int source, int dest,
                      int k) {

  // Make graph
  vector<P> adj[n];
  int edges = flights.size();
  for (int i = 0; i < edges; i++) {
    int u = flights[i][0];
    int v = flights[i][1];
    int cost = flights[i][2];

    adj[u].pb({v, cost});
  }

  //{cost}
  vector<int> dist(n, INT_MAX);
  dist[source] = 0; // we do not need any stop to reach source

  // {stops, vertex}
  queue<pair<int, int>> que;
  que.push({0, source});

  while (!que.empty()) {
    int node = que.front().second;
    int cost = dist[node];
    int stops = que.front().first;
    que.pop();

    if (stops > k) {
      continue;
    }

    for (pair<int, int> p : adj[node]) {
      int child = p.first;
      int wt = p.second;

      if (wt + cost < dist[child] && stops <= k) {
        que.push({stops + 1, child});
        dist[child] = wt + cost;
      }
    }
  }
  if (dist[dest] == INT_MAX) {
    return -1;
  }
  return dist[dest];
}

int main() {
  fastio(); // To enable fast IO.
}
