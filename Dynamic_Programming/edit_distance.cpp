#include <climits>
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
// TC: O(3^n)   SC:O(n)
int helper(int i, int j, string &start, string &target) {
  int n = start.size();
  int m = target.size();

  if (j == m) {
    return n - i;
  }
  if (i == n) {
    return m - j;
  }

  int first = INT_MAX;
  if (start[i] == target[j]) {
    first = helper(i + 1, j + 1, start, target);
  }
  int replace = 1 + helper(i + 1, j + 1, start, target);
  int delFirst = 1 + helper(i + 1, j, start, target);
  int insertFirst = 1 + helper(i, j + 1, start, target);

  return min({first, replace, delFirst, insertFirst});
}

int editDistance(string start, string target) {
  int n = start.size();
  int m = target.size();

  return helper(0, 0, start, target);
}

// NOTE: Memoization
// TC: O(n * m)  SC:O(n * m) + O(n)
int memo_helper(int i, int j, string &start, string &target,
                vector<vector<int>> &dp) {

  int n = start.size();
  int m = target.size();
  if (j == m) {
    return n - i;
  }
  if (i == n) {
    return m - j;
  }

  if (dp[i][j] != -1) {
    return dp[i][j];
  }

  int first = INT_MAX;
  if (start[i] == target[j]) {
    first = memo_helper(i + 1, j + 1, start, target, dp);
  }
  int replace = 1 + memo_helper(i + 1, j + 1, start, target, dp);
  int delFirst = 1 + memo_helper(i + 1, j, start, target, dp);
  int insertFirst = 1 + memo_helper(i, j + 1, start, target, dp);

  return dp[i][j] = min({first, replace, delFirst, insertFirst});
}

int memoization(string start, string target) {
  int n = start.size();
  int m = target.size();
  vector<vector<int>> dp(n + 1, vector<int>(m + 1, -1));

  return memo_helper(0, 0, start, target, dp);
}

// NOTE: Tabulation
// TC: O(n * m)   SC:O(n * m)
int tabulation(string start, string target) {
  int n = start.size();
  int m = target.size();

  vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

  // Base case
  for (int i = 0; i <= n; i++) {
    dp[i][m] = n - i;
  }
  for (int j = 0; j <= m; j++) {
    dp[n][j] = m - j;
  }

  for (int i = n - 1; i >= 0; i--) {
    for (int j = m - 1; j >= 0; j--) {
      int first = INT_MAX;
      if (start[i] == target[j]) {
        first = dp[i + 1][j + 1];
      }
      int replace = 1 + dp[i + 1][j + 1];
      int delFirst = 1 + dp[i + 1][j];
      int insertFirst = 1 + dp[i][j + 1];

      dp[i][j] = min({first, replace, delFirst, insertFirst});
    }
  }

  return dp[0][0];
}

// NOTE: Space optimization
//  TC:(n * m)   SC: O(m)
int space(string start, string target) {
  int n = start.size();
  int m = target.size();

  vector<int> next(m + 1, 0);
  for (int j = 0; j <= m; j++) {
    next[j] = m - j;
  }

  for (int i = n - 1; i >= 0; i--) {
    vector<int> curr(m + 1, 0);
    curr[m] = n - i;
    for (int j = m - 1; j >= 0; j--) {
      int first = INT_MAX;
      if (start[i] == target[j]) {
        first = next[j + 1];
      }
      int replace = 1 + next[j + 1];
      int delFirst = 1 + next[j];
      int insertFirst = 1 + curr[j + 1];

      curr[j] = min({first, replace, delFirst, insertFirst});
    }
    next = curr;
  }

  return next[0];
}

int main() {
#ifndef ONLINE_JUDGE
  freopen("Error.txt", "w", stderr);
  freopen("input.txt", "r", stdin);
#endif
  ratnesh();
}
