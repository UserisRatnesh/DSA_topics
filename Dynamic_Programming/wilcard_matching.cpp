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

bool isAllStars(int j, string pat) {
  for (int ind = j; ind < pat.size(); ind++) {
    if (pat[ind] != '*') {
      return false;
    }
  }
  return true;
}

// NOTE: Recursion
// TC: O(2^n)  SC: O(n)
bool helper(int i, int j, string &str, string &pat) {
  int n = str.size();
  int m = pat.size();
  if (i == n) {
    return j == m || isAllStars(j, pat);
  }

  bool isOkay = false;
  if (str[i] == pat[j] || pat[j] == '?') {
    isOkay = helper(i + 1, j + 1, str, pat);
  } else if (pat[j] == '*') {
    isOkay |= helper(i, j + 1, str, pat);
    isOkay |= helper(i + 1, j, str, pat);
  }
  return isOkay;
}

bool wildcard(string str, string pat) { return helper(0, 0, str, pat); }

// NOTE: Memoization
// TC: O(n * m)  SC: O(n * m) + O(n)
bool memo_helper(int i, int j, string &str, string &pat,
                 vector<vector<int>> &dp) {
  int n = str.size();
  int m = pat.size();

  if (i == n) {
    return j == m || isAllStars(j, pat);
  }
  if (dp[i][j] != -1) {
    return dp[i][j];
  }

  bool isOkay = false;
  if (str[i] == pat[j] || pat[j] == '?') {
    isOkay = memo_helper(i + 1, j + 1, str, pat, dp);
  } else if (pat[j] == '*') {
    isOkay |= memo_helper(i, j + 1, str, pat, dp);
    isOkay |= memo_helper(i + 1, j, str, pat, dp);
  }

  return dp[i][j] = isOkay;
}

int memoization(string str, string pat) {
  int n = str.size();
  int m = pat.size();

  vector<vector<int>> dp(n + 1, vector<int>(m + 1, -1));
  return memo_helper(0, 0, str, pat, dp);
}

// NOTE: Tabulation
// TC: O(n * m)  SC: O(n * m)
int tabulation(string str, string pat) {
  int n = str.size();
  int m = pat.size();

  vector<vector<bool>> dp(n + 1, vector<bool>(m + 1, false));

  for (int j = 0; j <= m; j++) {
    if (j == m || isAllStars(j, pat)) {
      dp[n][j] = true;
    }
  }

  for (int i = n - 1; i >= 0; i--) {
    for (int j = m - 1; j >= 0; j--) {
      bool isOkay = false;
      if (str[i] == pat[j] || pat[j] == '?') {
        isOkay = dp[i + 1][j + 1];
      } else if (pat[j] == '*') {
        isOkay = dp[i][j + 1] || dp[i + 1][j];
      }
      dp[i][j] = isOkay;
    }
  }

  return dp[0][0];
}

// NOTE: Space optimization
// TC: O(n * m)  SC: O(m)
int space(string str, string pat) {
  int n = str.size();
  int m = pat.size();
  vector<bool> next(m + 1, false);
  for (int j = 0; j <= m; j++) {
    if (j == m || isAllStars(j, pat)) {
      next[j] = true;
    }
  }

  for (int i = n - 1; i >= 0; i--) {
    vector<bool> curr(m + 1, false);
    for (int j = m - 1; j >= 0; j--) {
      bool isOkay = false;
      if (str[i] == pat[j] || pat[j] == '?') {
        isOkay = next[j + 1];
      } else if (pat[j] == '*') {
        isOkay = curr[j + 1] || next[j];
      }
      curr[j] = isOkay;
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
