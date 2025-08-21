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
// TC: O(2^(m*n))  SC: O(m+n) -> Path length of recursion
int recur_helper(int m, int n) {
  if (m == 0 && n == 0) {
    return 1;
  }

  if (m < 0 || n < 0) {
    return 0;
  }

  int top = recur_helper(m - 1, n);
  int left = recur_helper(m, n - 1);

  return top + left;
}

int uniquePath(int m, int n) { return recur_helper(m - 1, n - 1); }

// NOTE: Memoization
// TC: O(m*n)  SC: O(n+m) + O(n*m)
int memo_helper(int m, int n, vector<vector<int>> &dp) {
  if (m == 0 && n == 0) {
    return 1;
  }
  if (m < 0 || n < 0) {
    return 0;
  }
  if (dp[m][n] != -1) {
    return dp[m][n];
  }

  int top = memo_helper(m - 1, n, dp);
  int left = memo_helper(m, n - 1, dp);

  return dp[m][n] = top + left;
}

int memo(int m, int n) {
  vector<vector<int>> dp(m, vector<int>(n, -1));
  return memo_helper(m - 1, n - 1, dp);
}

// NOTE: Tabulation
// TC: O(m*n)  SC: O(n*m)
int tabulation(int m, int n) {
  vector<vector<int>> dp(m, vector<int>(n, -1));
  dp[0][0] = 1;
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      if (i == 0 && j == 0) {
        continue;
      }
      int top = i - 1 >= 0 ? dp[i - 1][j] : 0;
      int left = j - 1 >= 0 ? dp[i][j - 1] : 0;

      dp[i][j] = top + left;
    }
  }

  return dp[m - 1][n - 1];
}

// NOTE: Space optimization
int space_op(int m, int n) {

  vector<int> dp(n, 0);
  for (int i = 0; i < m; i++) {
    vector<int> temp(n, 0);
    for (int j = 0; j < n; j++) {
      if (i == 0 && j == 0) {
        temp[j] = 1;
        continue;
      }

      if (j - 1 >= 0) {
        temp[j] = dp[j] + temp[j - 1];
      } else {
        temp[j] = dp[j];
      }
    }

    dp = temp;
  }

  return dp[n - 1];
}

int main() {
#ifndef ONLINE_JUDGE
  freopen("Error.txt", "w", stderr);
  freopen("input.txt", "r", stdin);
#endif
  ratnesh();
}
