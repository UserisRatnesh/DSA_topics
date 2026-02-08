#include <climits>
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

// ERROR: Wrong
int helper(int index, int mask, vector<int> &nums) {
  int n = nums.size();
  if (index == n - 1) {
    return 0;
  }

  int notTake = helper(index + 1, mask, nums);
  int take = INT_MAX;
  int prev = -1;
  int next = -1;
  for (int i = index - 1; i >= 0; i--) {
    if (mask & (1 << i)) {
      // Available
      prev = i;
      break;
    }
  }
  for (int i = index + 1; i < n; i++) {
    if (mask & (1 << i)) {
      next = i;
      break;
    }
  }

  if (prev != -1 && next != -1) {
    take = nums[index] * nums[prev] * nums[next] +
           helper(index + 1, mask ^ (1 << index), nums);
  }

  return min(take, notTake);
}

int mcm(vector<int> &nums) {
  int n = nums.size();
  int mask = (1 << n) - 1;
  return helper(1, mask, nums);
}

// NOTE: Recursion

int helper_rec(int i, int j, vector<int> &nums) {
  int n = nums.size();
  if (i == j) {
    return 0;
  }

  int ans = INT_MAX;
  for (int k = i; k < j; k++) {
    int tempAns = nums[i - 1] * nums[k] * nums[j] + helper_rec(i, k, nums) +
                  helper_rec(k + 1, j, nums);
    ans = min(ans, tempAns);
  }

  return ans;
}

int mcm_rec(vector<int> &nums) {
  int n = nums.size();
  return helper_rec(1, n - 1, nums);
}

// NOTE: Memoization
// TC: O(n * n * n)   SC: O(n * n) + O(n)
int memo(int i, int j, vector<int> &nums, vector<vector<int>> &dp) {
  if (i == j) {
    return 0;
  }

  if (dp[i][j] != -1) {
    return dp[i][j];
  }

  int ans = INT_MAX;
  for (int k = i; k < j; k++) {
    int tempAns = nums[i - 1] * nums[k] * nums[j] + memo(i, k, nums, dp) +
                  memo(k + 1, j, nums, dp);
    ans = min(ans, tempAns);
  }

  return dp[i][j] = ans;
}

int mcm_memo(vector<int> &nums) {
  int n = nums.size();
  vector<vector<int>> dp(n + 1, vector<int>(n + 1, -1));
  return memo(1, n - 1, nums, dp);
}

// NOTE: Tabulation
//  TC: O(n * n * n)   SC: O(n * n)
int tabulation(vector<int> &nums) {
  int n = nums.size();
  vector<vector<int>> dp(n + 1, vector<int>(n + 1, INT_MAX));

  for (int i = 1; i < n; i++) {
    dp[i][i] = 0;
  }

  for (int i = n - 1; i >= 1; i--) {
    for (int j = i + 1; j < n; j++) {
      int ans = INT_MAX;
      for (int k = i; k < j; k++) {
        int tempAns = nums[i - 1] * nums[k] * nums[j] + dp[i][k] + dp[k + 1][j];
        ans = min(ans, tempAns);
      }
      dp[i][j] = ans;
    }
  }

  return dp[1][n - 1];
}

int main() {
#ifndef ONLINE_JUDGE
  freopen("Error.txt", "w", stderr);
  freopen("input.txt", "r", stdin);
#endif
  ratnesh();
}
