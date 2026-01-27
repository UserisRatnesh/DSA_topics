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
int helper(int index, int amount, vector<int> &coins) {

  int n = coins.size();
  if (amount == 0) {
    return 1;
  }
  if (index == n) {
    return 0;
  }

  int take = 0;
  if (coins[index] <= amount) {
    take = helper(index, amount - coins[index], coins);
  }

  int notTake = helper(index + 1, amount, coins);

  return (take + notTake) % MOD;
}

int count(vector<int> &coins, int n, int amount) {

  return helper(0, amount, coins);
}

// NOTE: Memoization
// TC: O(n * amount)  SC: O(n * amount) + O(n)
int helper_memo(int index, int amount, vector<int> &coins,
                vector<vector<int>> &dp) {
  int n = coins.size();
  if (amount == 0) {
    return 1;
  }
  if (index == n) {
    return 0;
  }

  if (dp[index][amount] != -1) {
    return dp[index][amount];
  }

  int take = 0;
  if (coins[index] <= amount) {
    take = helper_memo(index, amount - coins[index], coins, dp);
  }

  int notTake = helper_memo(index + 1, amount, coins, dp);

  return dp[index][amount] = (take + notTake) % MOD;
}

int memo(vector<int> &coins, int n, int amount) {

  vector<vector<int>> dp(n + 1, vector<int>(amount + 1, -1));
  return helper_memo(0, amount, coins, dp);
}

// NOTE: Tabulation
// TC: O(n * amount)  SC: O(n * amount)
int tabulation(int n, int amount, vector<int> &coins) {

  vector<vector<int>> dp(n + 1, vector<int>(amount + 1, 0));
  dp[n][0] = 1;

  for (int i = n - 1; i >= 0; i--) {
    for (int j = 0; j <= amount; j++) {
      int take = 0;
      if (coins[i] <= j) {
        take = dp[i][j - coins[i]];
      }
      int notTake = dp[i + 1][j];

      dp[i][j] = (take + notTake) % MOD;
    }
  }

  return dp[0][amount];
}

// NOTE: Space optimization
// TC: O(n * amount)  SC: O(amount)
int space(int n, int amount, vector<int> &coins) {

  vector<int> next(amount + 1, 0);
  next[0] = 1;

  for (int i = n - 1; i >= 0; i--) {
    vector<int> curr(amount + 1, 0);
    for (int j = 0; j <= amount; j++) {
      int take = 0;
      if (coins[i] <= j) {
        take = curr[j - coins[i]];
      }
      int notTake = next[j];

      curr[j] = (take + notTake) % MOD;
    }
    next = curr;
  }

  return next[amount];
}

int main() {
#ifndef ONLINE_JUDGE
  freopen("Error.txt", "w", stderr);
  freopen("input.txt", "r", stdin);
#endif
  ratnesh();
}
