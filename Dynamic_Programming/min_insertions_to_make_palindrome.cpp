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

// NOTE: Tabulation
//  TC: O(N * N)   SC: O(N * N)
int minInsertions(string s) {
  string s1 = s;
  string s2 = s;
  reverse(s2.begin(), s2.end());

  int n = s1.size();
  vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));

  for (int i = n - 1; i >= 0; i--) {
    for (int j = n - 1; j >= 0; j--) {
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

  return n - dp[0][0];
}

// NOTE: Space optimization
//  TC: O(N * N)   SC: O(N)
int spaceOptimization(string s) {
  string s1 = s;
  string s2 = s;
  reverse(s2.begin(), s2.end());

  int n = s1.size();
  vector<int> next(n + 1, 0);

  for (int i = n - 1; i >= 0; i--) {
    vector<int> curr(n + 1, 0);
    for (int j = n - 1; j >= 0; j--) {
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

  return n - next[0];
}

int main() {
#ifndef ONLINE_JUDGE
  freopen("Error.txt", "w", stderr);
  freopen("input.txt", "r", stdin);
#endif
  ratnesh();
}
