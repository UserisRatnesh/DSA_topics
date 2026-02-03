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
// TC: O(2^(n+m))  SC:O(n+m)
int helper(int index1, int index2, string &s1, string &s2) {
  int n = s1.size();
  int m = s2.size();
  if (index1 == n || index2 == m) {
    return 0;
  }

  if (s1[index1] == s2[index2]) {
    return 1 + helper(index1 + 1, index2 + 1, s1, s2);
  }

  int skipFirst = helper(index1 + 1, index2, s1, s2);
  int skipSecond = helper(index1, index2 + 1, s1, s2);

  return max(skipFirst, skipSecond);
}

int lcs(string &s1, string &s2) { return helper(0, 0, s1, s2); }

// NOTE: Memoization
// TC:O(n*m)    SC: O(n*m) + O(n+m)
int helper_memo(int index1, int index2, string &s1, string &s2,
                vector<vector<int>> &dp) {
  int n = s1.size();
  int m = s2.size();
  if (index1 == n || index2 == m) {
    return 0;
  }

  if (dp[index1][index2] != -1) {
    return dp[index1][index2];
  }

  if (s1[index1] == s2[index2]) {
    return dp[index1][index2] =
               1 + helper_memo(index1 + 1, index2 + 1, s1, s2, dp);
  }

  int skipFirst = helper_memo(index1 + 1, index2, s1, s2, dp);
  int skipSecond = helper_memo(index1, index2 + 1, s1, s2, dp);

  return dp[index1][index2] = max(skipFirst, skipSecond);
}

int lcs_memo(string &s1, string &s2) {
  int n = s1.size();
  int m = s2.size();
  vector<vector<int>> dp(n + 1, vector<int>(m + 1, -1));
  return helper_memo(0, 0, s1, s2, dp);
}

// NOTE: Tabulation
// TC: O(n * m)  SC: O(n * m)
int tabulation(string &s1, string &s2) {
  int n = s1.size();
  int m = s2.size();
  vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
  for (int i = n - 1; i >= 0; i--) {
    for (int j = m - 1; j >= 0; j--) {
      int maxLen = 0;
      if (s1[i] == s2[j]) {
        maxLen = 1 + dp[i + 1][j + 1];
      } else {
        int skipFirst = dp[i + 1][j];
        int skipSecond = dp[i][j + 1];
        maxLen = max(skipFirst, skipSecond);
      }

      dp[i][j] = maxLen;
    }
  }

  return dp[0][0];
}

// NOTE: Space optimization
// TC: O(n * m)   SC: O(m)
int space(string &s1, string &s2) {
  int n = s1.size();
  int m = s2.size();
  vector<int> next(m + 1, 0);

  for (int i = n - 1; i >= 0; i--) {
    vector<int> curr(m + 1, 0);
    for (int j = m - 1; j >= 0; j--) {
      int maxLen = 0;
      if (s1[i] == s2[j]) {
        maxLen = 1 + next[j + 1];
      } else {
        int skipFirst = next[j];
        int skipSecond = curr[j + 1];
        maxLen = max(skipFirst, skipSecond);
      }

      curr[j] = maxLen;
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
