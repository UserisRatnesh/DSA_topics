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
// TC: O(2^n)  SC: O(n)
int helper(int index, int W, vector<int> &wt, vector<int> &val) {
  int n = val.size();

  if (index == n) {
    return 0;
  }
  if (W <= 0) {
    return 0;
  }

  int take = 0;
  if (W >= wt[index]) {
    take = val[index] + helper(index + 1, W - wt[index], wt, val);
  }

  int notTake = helper(index + 1, W, wt, val);

  return max(take, notTake);
}

int knapsack01(vector<int> &wt, vector<int> &val, int n, int W) {

  return helper(0, W, wt, val);
}

// NOTE: Memoization
// TC: O(n * W)  SC: O(n * W) + O(n)
int helper_memo(int index, int W, vector<int> &wt, vector<int> &val,
                vector<vector<int>> &dp) {
  int n = val.size();

  if (index == n) {
    return 0;
  }
  if (W <= 0) {
    return 0;
  }

  if (dp[index][W] != -1) {
    return dp[index][W];
  }

  int take = 0;
  if (W >= wt[index]) {
    take = val[index] + helper_memo(index + 1, W - wt[index], wt, val, dp);
  }

  int notTake = helper_memo(index + 1, W, wt, val, dp);

  return dp[index][W] = max(take, notTake);
}

int knapsack01_memo(vector<int> &wt, vector<int> &val, int n, int W) {

  vector<vector<int>> dp(n + 1, vector<int>(W + 1, -1));
  return helper_memo(0, W, wt, val, dp);
}

// NOTE: Tabulation
// TC: O(n * W)  SC: O(n * W)
int tabulation(int n, int W, vector<int> &wt, vector<int> &val) {

  vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));
  for (int i = n - 1; i >= 0; i--) {
    for (int j = 0; j <= W; j++) {

      int take = 0;
      if (j >= wt[i]) {
        take = val[i] + dp[i + 1][j - wt[i]];
      }

      int notTake = dp[i + 1][j];

      dp[i][j] = max(take, notTake);
    }
  }

  return dp[0][W];
}

// NOTE: Space optmization
//  TC: O(n * W)  SC: O(W)
int space(int n, int W, vector<int> &wt, vector<int> &val) {

  vector<int> next(W + 1, 0);
  for (int i = n - 1; i >= 0; i--) {
    vector<int> curr(W + 1, 0);
    for (int j = 0; j <= W; j++) {

      int take = 0;
      if (j >= wt[i]) {
        take = val[i] + next[j - wt[i]];
      }
      int notTake = next[j];

      curr[j] = max(take, notTake);
    }

    next = curr;
  }

  return next[W];
}

int main() {
#ifndef ONLINE_JUDGE
  freopen("Error.txt", "w", stderr);
  freopen("input.txt", "r", stdin);
#endif
  ratnesh();
}
