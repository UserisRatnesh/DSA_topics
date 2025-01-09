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

string findOrder(string dict[], int n, int k) {

  // Create adj list
  vector<int> adj[k];
  for (int i = 1; i < n; ++i) {
    string prev = dict[i - 1];
    string curr = dict[i];
    int pi = 0, ci = 0, pl = sz(prev), cl = sz(curr);
    while (pi < pl && ci < cl) {
      char prevChar = prev[pi];
      char currChar = curr[ci];
      if (prevChar != currChar) {
        adj[prevChar - 'a'].pb(currChar - 'a');
        break;
      }
      pi++;
      ci++;
    }
  }

  // Now we have adj List

  vector<int> indeg(k, 0);
  for (int i = 0; i < k; i++) {
    for (int child : adj[i]) {
      indeg[child]++;
    }
  }

  queue<int> que;
  for (int i = 0; i < k; ++i) {
    if (indeg[i] == 0) {
      que.push(i);
    }
  }

  string ans;

  while (!que.empty()) {
    int node = que.front();
    que.pop();
    char c = node + 'a';
    ans += c;
    ans += " ";
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

  string arr[] = {"baa", "abcd", "abca", "cab", "cad"};
  cout << findOrder(arr, 5, 4);
}
