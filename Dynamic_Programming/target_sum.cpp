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

// NOTE: Recursion Brute force
// TC:O(2^n)  SC: O(n)
int helper(int index, int target, vector<int> &nums) {
  int n = nums.size();

  if (index == n) {
    return target == 0;
  }

  int add = helper(index + 1, target - nums[index], nums);
  int subtract = helper(index + 1, target + nums[index], nums);

  return (add + subtract) % MOD;
}

int targetSum(int n, int target, vector<int> &nums) {
  return helper(0, target, nums);
}

// NOTE: Recursion With the help of Count partition with given diff
// TC:O(2^n)  SC: O(n)
int helper_rec(int index, int target, vector<int> &nums) {
  int n = nums.size();
  if (target < 0) {
    return 0;
  }
  if (index == n) {
    return target == 0;
  }
  int take = 0;
  if (target - nums[index] >= 0) {
    take = helper_rec(index + 1, target - nums[index], nums);
  }
  int notTake = helper_rec(index + 1, target, nums);

  return (take + notTake) % MOD;
}

int targetSum_rec(int n, int target, vector<int> &nums) {
  int totalSum = accumulate(nums.begin(), nums.end(), 0);
  if ((totalSum - target) < 0 || (totalSum - target) % 2 == 1) {
    return 0;
  }
  int newTarget = (totalSum - target) / 2;

  return helper_rec(0, newTarget, nums);
}

// NOTE: Memoization
// TC:O(n * newTarget)  SC: O(n * newTarget) + O(n)
int helper_memo(int index, int target, vector<int> &nums,
                vector<vector<int>> &dp) {
  int n = nums.size();
  if (target < 0) {
    return 0;
  }
  if (index == n) {
    return target == 0;
  }

  if (dp[index][target] != -1) {
    return dp[index][target];
  }

  int take = 0;
  if (target - nums[index] >= 0) {
    take = helper_memo(index + 1, target - nums[index], nums, dp);
  }
  int notTake = helper_memo(index + 1, target, nums, dp);

  return dp[index][target] = (take + notTake) % MOD;
}

int targetSum_memo(int n, int target, vector<int> &nums) {

  int totalSum = accumulate(nums.begin(), nums.end(), 0);
  if ((totalSum - target) < 0 || (totalSum - target) % 2 == 1) {
    return 0;
  }

  int newTarget = (totalSum - target) / 2;
  vector<vector<int>> dp(n + 1, vector<int>(newTarget + 1, -1));

  return helper_memo(0, newTarget, nums, dp);
}

// NOTE: Tabulation
// TC: O(n * newTarget)  SC: O(n * newTarget)
int tabulation(int n, int target, vector<int> &nums) {

  int totalSum = accumulate(nums.begin(), nums.end(), 0);

  if ((totalSum - target) < 0 || (totalSum - target) % 2 == 1) {
    return 0;
  }

  int newTarget = (totalSum - target) / 2;
  vector<vector<int>> dp(n + 1, vector<int>(newTarget + 1, 0));
  dp[n][0] = 1;
  for (int i = n - 1; i >= 0; i--) {
    for (int j = 0; j <= newTarget; j++) {
      int take = 0;
      if (j - nums[i] >= 0) {
        take = dp[i + 1][j - nums[i]];
      }
      int notTake = dp[i + 1][j];

      dp[i][j] = (take + notTake) % MOD;
    }
  }

  return dp[0][newTarget];
}

// NOTE: Space optimization
//  TC: O(n * newTarget)  SC: O(newTarget)
int space(int n, int target, vector<int> &nums) {
  int totalSum = accumulate(nums.begin(), nums.end(), 0);
  if ((totalSum - target) < 0 || (totalSum - target) % 2 == 1) {
    return 0;
  }

  int newTarget = (totalSum - target) / 2;

  vector<int> next(newTarget + 1, 0);
  next[0] = 1;

  for (int i = n - 1; i >= 0; i--) {
    vector<int> curr(newTarget + 1, 0);
    for (int j = 0; j <= newTarget; j++) {
      int take = 0;
      if (j - nums[i] >= 0) {
        take = next[j - nums[i]];
      }
      int notTake = next[j];

      curr[j] = (take + notTake) % MOD;
    }
    next = curr;
  }

  return next[newTarget];
}

int main() {
#ifndef ONLINE_JUDGE
  freopen("Error.txt", "w", stderr);
  freopen("input.txt", "r", stdin);
#endif
  ratnesh();
}
