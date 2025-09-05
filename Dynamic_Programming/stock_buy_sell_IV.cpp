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

// HACK: Done using k transactions
//  NOTE: Recursion
//  TC: O(2^n) SC: (n) -> stack space
int helper(int index, vector<int> &prices, int n, int buy, int k) {
  // Jaise hi zero operations bacha return zero
  if (k == 0 || index >= n) {
    return 0;
  }

  int profit = 0;
  if (buy) {
    profit = -prices[index] + helper(index + 1, prices, n, 0, k);
  } else {
    profit = prices[index] + helper(index + 1, prices, n, 1, k - 1);
  }

  int do_nothing = helper(index + 1, prices, n, buy, k);

  return max(profit, do_nothing);
}

int stock_recursion(vector<int> &prices, int n, int k) {
  return helper(0, prices, n, 1, k);
}

// NOTE: Memoization
// TC: O(n*2*4) SC: O(n*2*5) + (n) -> stack space
int memo_helper(int index, vector<int> &prices, int n, int buy, int k,
                vector<vector<vector<int>>> &dp) {

  // Jaise hi zero operations bacha return zero
  if (k == 0 || index >= n) {
    return 0;
  }

  if (dp[index][buy][k] != -1) {
    return dp[index][buy][k];
  }

  int profit = 0;
  if (buy) {
    profit = -prices[index] + memo_helper(index + 1, prices, n, 0, k, dp);
  } else {
    profit = prices[index] + memo_helper(index + 1, prices, n, 1, k - 1, dp);
  }

  int do_nothing = memo_helper(index + 1, prices, n, buy, k, dp);

  int result = max(profit, do_nothing);
  dp[index][buy][k] = result;

  return result;
}

int memo(vector<int> &prices, int n, int k) {
  vector<vector<vector<int>>> dp(
      n, vector<vector<int>>(2, vector<int>(k + 1, -1)));
  return memo_helper(0, prices, n, 1, k, dp);
}

// NOTE: Tabulation
//  TC: O(n*2*4) SC: O(n*2*5)
int tabulation(vector<int> &prices, int n, int k) {
  vector<vector<vector<int>>> dp(n + 1,
                                 vector<vector<int>>(2, vector<int>(k + 1, 0)));

  for (int index = n - 1; index >= 0; index--) {
    for (int buy = 0; buy <= 1; buy++) {
      for (int ops = 1; ops <= k; ops++) {
        if (buy) {
          dp[index][buy][ops] = max(dp[index + 1][buy][ops],
                                    -prices[index] + dp[index + 1][0][ops]);
        } else {
          dp[index][buy][ops] = max(dp[index + 1][buy][ops],
                                    prices[index] + dp[index + 1][1][ops - 1]);
        }
      }
    }
  }

  return dp[0][1][k];
}

// NOTE: Space optimization
//  TC: O(n*2*4) SC: O(2*5)
int space_op(vector<int> &prices, int n, int k) {

  vector<vector<int>> ahead(2, vector<int>(k + 1, 0));

  for (int index = n - 1; index >= 0; index--) {
    vector<vector<int>> temp(2, vector<int>(k + 1, 0));

    for (int buy = 0; buy <= 1; buy++) {
      for (int ops = 1; ops <= k; ops++) {
        if (buy) {
          temp[buy][ops] = max(ahead[buy][ops], -prices[index] + ahead[0][ops]);
        } else {
          temp[buy][ops] =
              max(ahead[buy][ops], prices[index] + ahead[1][ops - 1]);
        }
      }
    }

    ahead = temp;
  }

  return ahead[1][k];
}

// HACK: Done using 2*k transactions
//  NOTE: Recursion
//  TC: O(2^n) SC: (n) -> stack space
int helper(int index, vector<int> &prices, int n, int k) {
  // Jaise hi zero operations bacha return zero
  if (k == 0 || index >= n) {
    return 0;
  }

  int profit = 0;
  if (k % 2 == 0) {
    profit = -prices[index] + helper(index + 1, prices, n, k - 1);
  } else {
    profit = prices[index] + helper(index + 1, prices, n, k - 1);
  }

  int do_nothing = helper(index + 1, prices, n, k);

  return max(profit, do_nothing);
}

int stock_recur(vector<int> &prices, int n, int k) {
  return helper(0, prices, n, 2 * k);
}

// NOTE: Memoization
// TC: O(n*2*4) SC: O(n*2*5) + (n) -> stack space
int memo_helper(int index, vector<int> &prices, int n, int k,
                vector<vector<int>> &dp) {

  // Jaise hi zero operations bacha return zero
  if (k == 0 || index >= n) {
    return 0;
  }

  if (dp[index][k] != -1) {
    return dp[index][k];
  }

  int profit = 0;
  if (k % 2 == 0) {
    profit = -prices[index] + memo_helper(index + 1, prices, n, k - 1, dp);
  } else {
    profit = prices[index] + memo_helper(index + 1, prices, n, k - 1, dp);
  }

  int do_nothing = memo_helper(index + 1, prices, n, k, dp);

  int result = max(profit, do_nothing);

  return dp[index][k] = result;
}

int memo_second(vector<int> &prices, int n, int k) {
  vector<vector<int>> dp(n, vector<int>(2 * k + 1, -1));
  return memo_helper(0, prices, n, 2 * k, dp);
}

// NOTE: Tabulation
//  TC: O(n*2*4) SC: O(n*2*5)
int tabulation_second(vector<int> &prices, int n, int k) {
  vector<vector<int>> dp(n + 1, vector<int>(2 * k + 1, 0));

  for (int index = n - 1; index >= 0; index--) {
    for (int ops = 1; ops <= 2 * k; ops++) {
      if (ops % 2 == 0) {
        dp[index][ops] =
            max(dp[index + 1][ops], -prices[index] + dp[index + 1][ops - 1]);
      } else {
        dp[index][ops] =
            max(dp[index + 1][ops], prices[index] + dp[index + 1][ops - 1]);
      }
    }
  }

  return dp[0][2 * k];
}

// NOTE: Space optimization
//  TC: O(n*2*4) SC: O(2*5)
int space_op_second(vector<int> &prices, int n, int k) {

  vector<int> ahead(2 * k + 1, 0);

  for (int index = n - 1; index >= 0; index--) {
    vector<int> temp(2 * k + 1, 0);

    for (int ops = 1; ops <= 2 * k; ops++) {
      if (ops % 2 == 0) {
        temp[ops] = max(ahead[ops], -prices[index] + ahead[ops - 1]);
      } else {
        temp[ops] = max(ahead[ops], prices[index] + ahead[ops - 1]);
      }
    }

    ahead = temp;
  }

  return ahead[2 * k];
}

int main() {
#ifndef ONLINE_JUDGE
  freopen("Error.txt", "w", stderr);
  freopen("input.txt", "r", stdin);
#endif
  ratnesh();
}
