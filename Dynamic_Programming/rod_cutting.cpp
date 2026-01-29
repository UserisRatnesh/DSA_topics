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
int helper_rec(int index, int length, vector<int> &price) {
  int n = price.size();
  if (length == 0) {
    return 0;
  }
  if (index == n) {
    return 0;
  }

  int pick = 0;
  if (length >= index + 1) {
    pick = price[index] + helper_rec(index, length - (index + 1), price);
  }
  int notPick = helper_rec(index + 1, length, price);

  return max(pick, notPick);
}

int rodCutting(vector<int> price, int n) { return helper_rec(0, n, price); }

// NOTE: Memoization
// TC: O(n * RodLength) SC: O(n * RodLength)+ O(n)
int helper_memo(int index, int length, vector<int> &price,
                vector<vector<int>> &dp) {
  int n = price.size();
  if (length == 0) {
    return 0;
  }
  if (index == n) {
    return 0;
  }

  if (dp[index][length] != -1) {
    return dp[index][length];
  }

  int currLen = index + 1;
  int pick = 0;
  if (length >= currLen) {
    pick = price[index] + helper_memo(index, length - currLen, price, dp);
  }
  int notPick = helper_memo(index + 1, length, price, dp);

  return dp[index][length] = max(pick, notPick);
}

int rodCutting_memo(int n, vector<int> &price) {

  vector<vector<int>> dp(n + 1, vector<int>(n + 1, -1));
  return helper_memo(0, n, price, dp);
}

// NOTE: Tabulation
// TC: O(n * RodLength) SC: O(n * RodLength)
int tabulation(int n, vector<int> &price) {
  int RodLen = n;
  vector<vector<int>> dp(n + 1, vector<int>(RodLen + 1, 0));

  for (int i = n - 1; i >= 0; i--) {
    int currLen = i + 1;
    for (int len = 0; len <= RodLen; len++) {
      int pick = 0;
      if (currLen <= len) {
        pick = price[i] + dp[i][len - currLen];
      }
      int notPick = dp[i + 1][len];

      dp[i][len] = max(pick, notPick);
    }
  }

  return dp[0][RodLen];
}

// NOTE: Space optimization
// TC:(n * RodLength)  SC: O(RodLength)
int space(int n, vector<int> &price) {
  int RodLen = n;
  vector<int> next(RodLen + 1, 0);
  for (int i = n - 1; i >= 0; i--) {
    int currLen = i + 1;
    vector<int> temp(RodLen + 1, 0);
    for (int len = 0; len <= RodLen; len++) {
      int pick = 0;
      if (currLen <= len) {
        pick = price[i] + temp[len - currLen];
      }
      int notPick = next[len];

      temp[len] = max(pick, notPick);
    }
    next = temp;
  }

  return next[RodLen];
}

int main() {
#ifndef ONLINE_JUDGE
  freopen("Error.txt", "w", stderr);
  freopen("input.txt", "r", stdin);
#endif
  ratnesh();
}
