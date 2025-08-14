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

// NOTE: Recursion
int recur(int n, vector<int> &heights, int k) {

  if (n == 0) {
    return 0;
  }

  int mini = INT_MAX;
  for (int i = n - 1; i >= max(n - k, 0); i--) {
    mini = min(mini, abs(heights[n] - heights[i]) + recur(i, heights, k));
  }

  return mini;
}

// NOTE: Memoization
// TC: O(n*k), SC: O(n) + O(n)
int memo(int n, vector<int> &heights, int k, vector<int> &dp) {
  if (n == 0) {
    return 0;
  }

  if (dp[n] != -1) {
    return dp[n];
  }

  int mini = INT_MAX;
  for (int i = n - 1; i >= max(n - k, 0); i--) {

    int call = abs(heights[n] - heights[i]) + memo(i, heights, k, dp);

    mini = min(mini, call);
  }

  return dp[n] = mini;
}

// NOTE: Tabulation
// TC: O(n*k), SC: O(n)
int tabulation(vector<int> &heights, int k) {

  int n = heights.size();
  vector<int> dp(n, -1);
  dp[0] = 0;

  for (int i = 1; i < n; i++) {

    int mini = INT_MAX;
    for (int j = i - 1; j >= max(0, i - k); j--) {
      int curr = abs(heights[i] - heights[j]) + dp[j];
      mini = min(mini, curr);
    }

    dp[i] = mini;
  }

  return dp[n - 1];
}

// NOTE: Space optimization
// TC: O(n*k), SC: O(k)
int space(vector<int> &heights, int k) {

  int n = heights.size();
  vector<int> vec(k, 0);

  for (int i = 1; i < n; i++) {

    int mini = INT_MAX;
    for (int j = i - 1; j >= max(0, i - k); j--) {

      int curr = abs(heights[i] - heights[j]) + vec[(j % k)];

      mini = min(mini, curr);
    }

    vec[i % k] = mini;
  }

  return vec[(n - 1) % k];
}

int main() {
#ifndef ONLINE_JUDGE
  freopen("Error.txt", "w", stderr);
  freopen("input.txt", "r", stdin);
#endif
  ratnesh();
}
