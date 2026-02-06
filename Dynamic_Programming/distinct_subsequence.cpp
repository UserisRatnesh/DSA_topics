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
// TC: O(2^n)   SC:O(n)
int helper(int i, int j, string &s, string &t) {
  int n = s.size();
  int m = t.size();
  if (j == m) {
    return 1;
  }
  if (i == n) {
    return 0;
  }

  int take = 0;
  if (s[i] == t[j]) {
    take = helper(i + 1, j + 1, s, t);
  }
  int notTake = helper(i + 1, j, s, t);

  return (take + notTake) % MOD;
}

int distictSubsequence(string s, string t) { return helper(0, 0, s, t); }

// NOTE: Memoization
// TC: O(n * m)   SC: O(n * m) + O(n)
int memo(int i, int j, string &s, string &t, vector<vector<int>> &dp) {
  int n = s.size();
  int m = t.size();
  if (j == m) {
    return 1;
  }
  if (i == n) {
    return 0;
  }

  if (dp[i][j] != -1) {
    return dp[i][j];
  }

  int take = 0;
  if (s[i] == t[j]) {
    take = memo(i + 1, j + 1, s, t, dp);
  }
  int notTake = memo(i + 1, j, s, t, dp);

  return dp[i][j] = (take + notTake) % MOD;
}

int memoization(string s, string t) {
  int n = s.size();
  int m = t.size();
  vector<vector<int>> dp(n + 1, vector<int>(m + 1, -1));

  int ans = memo(0, 0, s, t, dp);
  return ans;
}

// NOTE: Tabulation
// TC: O(n * m )   SC:O(n * M)
int tabulation(string s, string t) {
  int n = s.size();
  int m = t.size();

  vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
  for (int i = 0; i <= n; i++) {
    dp[i][m] = 1;
  }

  for (int i = n - 1; i >= 0; i--) {
    for (int j = m - 1; j >= 0; j--) {
      int take = 0;
      if (s[i] == t[j]) {
        take = dp[i + 1][j + 1];
      }
      int notTake = dp[i + 1][j];

      dp[i][j] = (take + notTake) % MOD;
    }
  }

  return dp[0][0];
}

// NOTE: Space optimization
//  TC: O(n * m)   SC: O(m)
int space(string s, string t) {
  int n = s.size();
  int m = t.size();

  vector<int> next(m + 1, 0);
  next[m] = 1;

  for (int i = n - 1; i >= 0; i--) {
    vector<int> curr(m + 1, 0);
    curr[m] = 1;
    for (int j = m - 1; j >= 0; j--) {
      int take = 0;
      if (s[i] == t[j]) {
        take = next[j + 1];
      }
      int notTake = next[j];

      curr[j] = (take + notTake) % MOD;
    }
    next = curr;
  }

  return next[0];
}

int main() {
#ifndef ONLINE_JUDGE
  // freopen("Error.txt", "w", stderr);
  freopen("input.txt", "r", stdin);
#endif
  ratnesh();

  string s = "axbxax";
  string t = "axa";
  int ans = memoization(s, t);
}
