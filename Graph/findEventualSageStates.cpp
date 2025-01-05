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

int main() {
  fastio(); // To enable fast IO.
}
