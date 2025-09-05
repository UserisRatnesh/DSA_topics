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

// NOTE : Recursion
// TC: O(2^n) SC: O(n) -> stack space
int helper(int index, vector<int> &arr, int n, int fee, int buy) {

  if (index == n) {
    return 0;
  }

  int profit = 0;
  if (buy) {
    profit = -arr[index] + helper(index + 1, arr, n, fee, 0);
  } else {
    profit = -fee + arr[index] + helper(index + 1, arr, n, fee, 1);
  }

  int do_nothing = helper(index + 1, arr, n, fee, buy);

  return max(profit, do_nothing);
}

int stock(vector<int> &arr, int n, int fee) {
  return helper(0, arr, n, fee, 1);
}

// NOTE: Memoization
// TC: O(2*n) SC: O(2*n) + O(n) -> stack space
int memo(int index, vector<int> &arr, int n, int fee, int buy,
         vector<vector<int>> &dp) {
  if (index == n) {
    return 0;
  }

  if (dp[index][buy] != -1) {
    return dp[index][buy];
  }

  int profit = 0;
  if (buy) {
    profit = -arr[index] + memo(index + 1, arr, n, fee, 0, dp);
  } else {
    profit = -fee + arr[index] + memo(index + 1, arr, n, fee, 1, dp);
  }

  int do_nothing = memo(index + 1, arr, n, fee, buy, dp);

  return dp[index][buy] = max(profit, do_nothing);
}

int stock_memo(vector<int> &arr, int n, int fee) {
  vector<vector<int>> dp(n, vector<int>(2, -1));
  return memo(0, arr, n, fee, 1, dp);
}

// NOTE: Tabulation
// TC: O(2*n) SC: O(2*n)
int tabulation(vector<int> &arr, int n, int fee) {

  vector<vector<int>> dp(n + 1, vector<int>(2, 0));
  for (int index = n - 1; index >= 0; index--) {
    for (int buy = 0; buy <= 1; buy++) {
      if (buy) {
        dp[index][buy] = max(dp[index + 1][1], -arr[index] + dp[index + 1][0]);
      } else {
        dp[index][buy] =
            max(dp[index + 1][0], -fee + arr[index] + dp[index + 1][1]);
      }
    }
  }

  return dp[0][1];
}

// NOTE: Space optimization
// TC: O(2*n) SC: O(1)
int space_op(vector<int> &arr, int n, int fee) {
  vector<int> ahead(2, 0);

  for (int index = n - 1; index >= 0; index--) {
    vector<int> temp(2, 0);
    for (int buy = 0; buy <= 1; buy++) {
      if (buy) {
        temp[buy] = max(ahead[1], -arr[index] + ahead[0]);
      } else {
        temp[buy] = max(ahead[0], -fee + arr[index] + ahead[1]);
      }
    }

    ahead = temp;
  }
  return ahead[1];
}

int main() {
#ifndef ONLINE_JUDGE
  freopen("Error.txt", "w", stderr);
  freopen("input.txt", "r", stdin);
#endif
  ratnesh();
}
