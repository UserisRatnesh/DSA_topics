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

// NOTE: Recursive
// TC : O(2 ^ n)  SC: O(n) -> recursive stack space
int stock_recursive(int index, vector<int> &arr, bool buy) {
  if (index == arr.size()) {
    return 0;
  }

  int profit = 0;
  if (buy) {
    profit = -arr[index] + stock_recursive(index + 1, arr, !buy);
  } else {
    profit = arr[index] + stock_recursive(index + 1, arr, !buy);
  }

  int do_nothing = stock_recursive(index + 1, arr, buy);

  int ans = max(profit, do_nothing);

  return ans;
}

int buySell_stock(vector<int> &arr, int n) {
  return stock_recursive(0, arr, true);
}

// NOTE: Memoization
// TC : O(2*n)  SC: O(2*n) + O(n) -> recursive stack space
ll memo(int index, vector<int> &arr, bool buy, vector<vector<ll>> &dp) {
  if (index == arr.size()) {
    return 0;
  }

  if (dp[index][buy] != -1) {
    return dp[index][buy];
  }

  ll profit = 0;
  if (buy) {
    profit = -arr[index] + memo(index + 1, arr, !buy, dp);
  } else {
    profit = arr[index] + memo(index + 1, arr, !buy, dp);
  }

  ll do_nothing = memo(index + 1, arr, buy, dp);

  ll ans = max(profit, do_nothing);

  return dp[index][buy] = ans;
}

ll stock_memo(vector<int> &arr, int n) {
  vector<vector<ll>> dp(n + 1, vector<ll>(2, -1));
  return memo(0, arr, true, dp);
}

// NOTE: Tabulation
// TC : O(2*n)  SC: O(2*n)
int tabulation(vector<int> &arr, int n) {

  vector<vector<int>> dp(n + 1, vector<int>(2, -1));
  dp[n][0] = dp[n][1] = 0;

  for (int index = n - 1; index >= 0; index--) {
    for (int buy = 0; buy <= 1; buy++) {
      ll profit = 0;
      if (buy == 1) {
        profit = max(dp[index + 1][1], -arr[index] + dp[index + 1][0]);
      } else {
        profit = max(dp[index + 1][0], arr[index] + dp[index + 1][1]);
      }

      dp[index][buy] = profit;
    }
  }

  return dp[0][1];
}

// NOTE: Space optimization
// TC : O(2*n)  SC: O(1)
int space_op(vector<int> &arr, int n) {
  vector<int> next(2, 0);

  for (int index = n - 1; index >= 0; index--) {
    vector<int> temp(2, -1);
    for (int buy = 0; buy <= 1; buy++) {
      if (buy == 1) {
        temp[1] = max(next[1], -arr[index] + next[0]);
      } else {
        temp[0] = max(next[0], arr[index] + next[1]);
      }
    }

    next = temp;
  }

  return next[1];
}

// HACK:
// TC : O(n)  SC: O(1)
int stock(vector<int> arr, int n) {

  int mini = INT_MAX;
  int profit = 0;
  for (auto it : arr) {
    mini = min(mini, it);
    if (it > mini) {
      profit += (it - mini);
      mini = it;
    }
  }

  if (profit < 0) {
    return 0;
  }
  return profit;
}

int main() {
#ifndef ONLINE_JUDGE
  freopen("Error.txt", "w", stderr);
  freopen("input.txt", "r", stdin);
#endif
  ratnesh();
}
