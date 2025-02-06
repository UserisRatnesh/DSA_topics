#ifndef ONLINE_JUDGE
#include "/usr/local/include/bits/stdc++.h"
#else
#include <bits/stdc++.h>
#endif

using namespace std;

#define fastio()                                                               \
  ios_base::sync_with_stdio(false);                                            \
  cin.tie(NULL);                                                               \
  cout.tie(NULL)
#define MOD 1000000007
#define MOD1 998244353
#define INF 1e18
#define nline "\n"
#define pb push_back
#define ppb pop_back
#define mp make_pair
#define ff first
#define ss second
#define PI 3.141592653589793238462
#define set_bits __builtin_popcountll
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()

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

// NOTE: Recursion
// TC: O(2^n) -> TLE
int get_profit(vector<int> &prices, int index, int buy, int transactions) {
  int n = prices.size();
  if (index >= n || transactions >= 2) {
    return 0;
  }

  int profit = 0;
  if (buy) {
    int bought =
        -prices[index] + get_profit(prices, index + 1, 0, transactions);
    int notBought = 0 + get_profit(prices, index + 1, 1, transactions);

    profit = max(profit, max(bought, notBought));
  } else {
    int sell =
        prices[index] + get_profit(prices, index + 1, 1, transactions + 1);
    int notSell = 0 + get_profit(prices, index + 1, 0, transactions);

    profit = max(profit, max(sell, notSell));
  }

  return profit;
}

int stockBuySell_III_Better(vector<int> &prices) {
  return get_profit(prices, 0, 1, 0);
}

// NOTE: Recursion + Memoization
// TC: O(n*2*3)
int get_profit_memo(vector<int> &prices, int index, int buy, int transactions,
                    vector<vector<vector<int>>> &dp) {
  int n = prices.size();
  if (index >= n || transactions == 0) {
    return 0;
  }

  if (dp[index][buy][transactions] != -1) {
    return dp[index][buy][transactions];
  }

  int profit = 0;
  if (buy) {
    int bought = -prices[index] +
                 get_profit_memo(prices, index + 1, 0, transactions, dp);
    int notBought = 0 + get_profit_memo(prices, index + 1, 1, transactions, dp);

    profit = max(profit, max(bought, notBought));
  } else {
    int sell = prices[index] +
               get_profit_memo(prices, index + 1, 1, transactions - 1, dp);
    int notSell = 0 + get_profit_memo(prices, index + 1, 0, transactions, dp);

    profit = max(profit, max(sell, notSell));
  }

  dp[index][buy][transactions] = profit;

  return profit;
}

int stockBuySell_III_Memo(vector<int> &prices) {

  int n = prices.size();
  vector<vector<vector<int>>> dp(n, vector<vector<int>>(2, vector<int>(3, -1)));
  get_profit_memo(prices, 0, 1, 2, dp);

  // HACK: Return max among 0, 1 ans 2 transactions since at most TWO
  // transactions are allowed
  return max(dp[0][1][0], max(dp[0][1][1], dp[0][1][2]));
}

// NOTE: Tabulation
// TC: O(n*2*3)
// SC: O(1)
int stockBuySell_III_tabulation(vector<int> &prices) {

  int n = prices.size();
  vector<vector<vector<int>>> dp(n + 1,
                                 vector<vector<int>>(2, vector<int>(3, 0)));

  for (int index = n - 1; index >= 0; index--) {
    for (int buy = 0; buy <= 1; buy++) {
      for (int transactions = 1; transactions <= 2; transactions++) {
        int profit = 0;
        if (buy) {
          int bought = -prices[index] + dp[index + 1][0][transactions];
          int notBought = 0 + dp[index + 1][1][transactions];

          profit = max(profit, max(bought, notBought));

        } else {
          int sell = prices[index] + dp[index + 1][1][transactions - 1];
          int notSell = 0 + dp[index + 1][0][transactions];

          profit = max(profit, max(sell, notSell));
        }

        dp[index][buy][transactions] = profit;
      }
    }
  }

  return max(dp[0][1][0], max(dp[0][1][1], dp[0][1][2]));
}

// NOTE: Tabulation + space optimization
// TC: O(n*2*3)
// SC: O(1)
int stockBuySell_III_tabulation_spaceOptimization(vector<int> &prices) {

  int n = prices.size();
  vector<vector<int>> ahead(2, vector<int>(3, 0)), curr(2, vector<int>(3, 0));

  for (int index = n - 1; index >= 0; index--) {
    for (int buy = 0; buy <= 1; buy++) {
      for (int transactions = 1; transactions <= 2; transactions++) {
        int profit = 0;
        if (buy) {
          int bought = -prices[index] + ahead[0][transactions];
          int notBought = 0 + ahead[1][transactions];

          profit = max(profit, max(bought, notBought));

        } else {
          int sell = prices[index] + ahead[1][transactions - 1];
          int notSell = 0 + ahead[0][transactions];

          profit = max(profit, max(sell, notSell));
        }

        curr[buy][transactions] = profit;
      }
    }
    ahead = curr;
  }

  return max(ahead[1][0], max(ahead[1][1], ahead[1][2]));
}

int main() {
#ifndef ONLINE_JUDGE
  freopen("Error.txt", "w", stderr);
#endif
  fastio();
}
