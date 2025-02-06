#ifndef ONLINE_JUDGE
#include "/usr/local/include/bits/stdc++.h"
#else
#include <bits/stdc++.h>
#endif

using namespace std;

#define fastio()                                                               \
  ios_base::sync_with_stdio(0);                                                \
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

// NOTE: Most optimized one
int stockBuySell(vector<int> arr, int n) {
  int ans = 0;
  int mini = arr[0];
  for (int i = 1; i < n; i++) {

    int currProfit = 0;
    if (arr[i] > mini) {
      // will sell the stock on ith day and buy new one on the same ith day
      currProfit = arr[i] - mini;
      mini = arr[i];
    } else {
      // sell on same prev day i.e day at which it is bought
      mini = min(mini, arr[i]);
    }

    ans += currProfit;
  }
  return ans;
}

// NOTE: Recursion + Memoization

int get_profit(vector<int> &arr, int n, int index, int buy,
               vector<vector<int>> &dp) {

  // Base cases
  if (index >= n) {
    return 0;
  }

  if (dp[index][buy] != -1) {
    return dp[index][-1];
  }

  int profit = 0;
  if (buy) {

    // buy this stock
    int bought = -arr[index] + get_profit(arr, n, index + 1, 0, dp);

    // not buy this stock
    int notBought = get_profit(arr, n, index + 1, 1, dp);

    profit = max(profit, max(bought, notBought));
  } else {

    // sell at this day
    int sell = arr[index] + get_profit(arr, n, index + 1, 1, dp);

    // not sell on this day
    int notSell = get_profit(arr, n, index + 1, 0, dp);

    profit = max(profit, max(sell, notSell));
  }

  dp[index][buy] = profit;

  return profit;
}

int stockBuySell_II(vector<int> arr, int n) {

  int maxProfit = 0;

  vector<vector<int>> dp(n, vector<int>(2, -1));
  maxProfit = max(maxProfit, get_profit(arr, n, 0, 1, dp));

  return maxProfit;
}

// NOTE: Done using Tabulation

int stockBuySell_II_tabulation(vector<int> &arr, int n) {

  vector<vector<int>> dp(n + 1, vector<int>(2, 0));
  dp[n][0] = dp[n][1] = 0;

  for (int index = n - 1; index >= 0; index--) {
    for (int buy = 0; buy <= 1; buy++) {

      int profit = 0;
      if (buy) {
        // buy this stock
        int bought = -arr[index] + dp[index + 1][0];

        // not buy this stock
        int notBought = dp[index + 1][1];

        profit = max(profit, max(bought, notBought));
      } else {
        // sell at this day
        int sell = arr[index] + dp[index + 1][1];

        // not sell on this day
        int notSell = dp[index + 1][0];

        profit = max(profit, max(sell, notSell));
      }
      dp[index][buy] = profit;
    }
  }

  return dp[0][1];
}

// NOTE: Tabulation + space optimization

int stockBuySell_II_optimization(vector<int> &arr, int n) {

  vector<int> ahead(2, 0), curr(2, 0);

  ahead[0] = ahead[1] = 0;
  for (int index = n - 1; index >= 0; index--) {
    for (int buy = 0; buy <= 1; buy++) {
      int profit = 0;
      if (buy) {
        int bought = -arr[index] + ahead[0];
        int notBought = 0 + ahead[1];

        profit = max(profit, max(bought, notBought));

      } else {

        int sell = arr[index] + ahead[1];
        int notSell = 0 + ahead[0];

        profit = max(profit, max(sell, notSell));
      }

      curr[buy] = profit;
    }

    ahead = curr;
  }

  return ahead[1];
}

int main() {
#ifndef ONLINE_JUDGE
  freopen("Error.txt", "w", stderr);
#endif
  fastio();
}
