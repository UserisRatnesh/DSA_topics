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

int recursion(int n, vector<int> &heights) {
  if (n == 0) {
    return 0;
  }
  if (n == 1) {
    return abs(heights[n] - heights[0]);
  }

  return min(abs(heights[n] - heights[n - 1]) + recursion(n - 1, heights),
             abs(heights[n] - heights[n - 2]) + recursion(n - 2, heights));
}

int frogJump(vector<int> &heights) {

  int n = heights.size();
  return recursion(n - 1, heights);
}

// NOTE: Memoization
// TC: O(n), SC: O(n) + O(n)
int memo(int n, vector<int> &heights, vector<int> &dp) {
  if (n == 0) {
    return 0;
  }
  if (n == 1) {
    return abs(heights[1] - heights[0]);
  }

  if (dp[n] != -1) {
    return dp[n];
  }

  return dp[n] =
             min(abs(heights[n] - heights[n - 1]) + memo(n - 1, heights, dp),
                 abs(heights[n] - heights[n - 2]) + memo(n - 2, heights, dp));
}

// NOTE: Tabulation
// TC: O(n), SC: O(n)
int tabulation(vector<int> &heights) {

  int n = heights.size();
  vector<int> dp(n, -1);
  dp[0] = 0;
  dp[1] = abs(heights[1] - heights[0]);

  for (int i = 2; i < n; i++) {

    int one = dp[i - 1] + abs(heights[i] - heights[i - 1]);
    int two = dp[i - 2] + abs(heights[i] - heights[i - 2]);

    dp[i] = min(one, two);
  }

  return dp[n - 1];
}

// NOTE: Space optimization
// TC: O(n), SC: O(1)
int space(vector<int> &heights) {

  int n = heights.size();
  if (n == 1) {
    return 0;
  }
  int prev2 = 0;
  int prev = abs(heights[1] - heights[0]);
  for (int i = 2; i < n; i++) {

    int one = prev + abs(heights[i] - heights[i - 1]);
    int two = prev2 + abs(heights[i] - heights[i - 2]);

    int curr = min(one, two);

    prev2 = prev;
    prev = curr;
  }

  return prev;
}

int main() {
#ifndef ONLINE_JUDGE
  freopen("Error.txt", "w", stderr);
  freopen("input.txt", "r", stdin);
#endif
  ratnesh();

  vector<int> hts = {2, 1, 3, 5, 4};
  int n = hts.size();
  vector<int> dp(n, -1);
  int ans = memo(n - 1, hts, dp);
  cout << ans << nl;
}
