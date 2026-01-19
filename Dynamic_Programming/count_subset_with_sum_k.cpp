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
// TC: O(2^n)  SC: (n) -> Recursion stack space
int helper(int index, int target, vector<int> &arr) {

  int n = arr.size();
  if (target == 0) {
    return 1;
  }
  if (index == n) {
    return 0;
  }

  int take = 0;
  if (target - arr[index] >= 0) {
    take = helper(index + 1, target - arr[index], arr);
  }

  int notTake = helper(index + 1, target, arr);

  return (take + notTake) % MOD;
}

int perfectSum_rec(vector<int> &arr, int k) { return helper(0, k, arr); }

// NOTE: Memoization
// TC : O(n * target) -> Total index * target unique states honge
// SC: O(n + n * target)
int helper_memo(int index, int target, vector<int> &arr,
                vector<vector<int>> &dp) {

  int n = arr.size();
  if (target == 0) {
    return 1;
  }
  if (index == n) {
    return 0;
  }

  if (dp[index][target] != -1) {
    return dp[index][target];
  }

  int take = 0;
  if (target - arr[index] >= 0) {
    take = helper_memo(index + 1, target - arr[index], arr, dp);
  }

  int notTake = helper_memo(index + 1, target, arr, dp);

  return dp[index][target] = (take + notTake) % MOD;
}

int perfectSum_memo(vector<int> &arr, int k) {

  int n = arr.size();
  vector<vector<int>> dp(n + 1, vector<int>(k + 1, -1));

  return helper_memo(0, k, arr, dp);
}

// NOTE : Tabulation
// TC : O(n * target)  SC: O(n * target)
int tabulation(vector<int> &arr, int k) {

  int n = arr.size();
  vector<vector<int>> dp(n + 1, vector<int>(k + 1, 0));

  for (int i = 0; i <= n; i++) {
    dp[i][0] = 1;
  }

  for (int i = n - 1; i >= 0; i--) {
    for (int j = 0; j <= k; j++) {
      int take = 0;
      if (j - arr[i] >= 0) {
        take = dp[i + 1][j - arr[i]];
      }
      int notTake = dp[i + 1][j];

      dp[i][j] = (take + notTake) % MOD;
    }
  }

  return dp[0][k];
}

// NOTE : Space optmization
// TC : O(n * target)  SC: O(k)
int space_optm(vector<int> &arr, int k) {
  int n = arr.size();
  vector<int> next(k + 1, 0);
  next[0] = 1;

  for (int i = n - 1; i >= 0; i--) {
    vector<int> curr(k + 1, 0);
    for (int j = 0; j <= k; j++) {

      int take = 0;
      if (j - arr[i] >= 0) {
        take = next[j - arr[i]];
      }
      int notTake = next[j];

      curr[j] = (take + notTake) % MOD;
    }

    next = curr;
  }

  return next[k];
}

int main() {
#ifndef ONLINE_JUDGE
  freopen("Error.txt", "w", stderr);
  freopen("input.txt", "r", stdin);
#endif
  ratnesh();
}
