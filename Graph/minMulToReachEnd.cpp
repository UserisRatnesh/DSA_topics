#include <climits>
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

int minimumMultiplications(vector<int> &arr, int start, int end) {

  if (start == end) {
    return 0;
  }
  queue<pair<int, int>> que;
  que.push({start, 0});

  vector<int> dist(
      100000, INT_MAX); // because MOD = 10^5 so value can not exceed this MOD
  dist[start] = 0;

  while (!que.empty()) {
    auto [product, steps] = que.front();
    que.pop();

    for (int factor : arr) {
      int newProduct = (product * factor) % MOD;
      if (newProduct == end) {
        return steps + 1;
      }
      if (steps + 1 < dist[newProduct]) {
        que.push({newProduct, steps + 1});
        dist[newProduct] = steps + 1;
      }
    }
  }

  return -1;
}

int main() {
  fastio(); // To enable fast IO.
}
