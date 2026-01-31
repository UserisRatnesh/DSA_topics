#include <algorithm>
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
// TC: O(2^N)  SC:O(n)
int helper(int index, int prevIndex, vector<int> &nums) {
  int n = nums.size();
  if (index == n) {
    return 0;
  }

  int take = 0;
  if (prevIndex == -1 || nums[index] > nums[prevIndex]) {
    take = 1 + helper(index + 1, index, nums);
  }
  int notTake = helper(index + 1, prevIndex, nums);

  return max(take, notTake);
}

int LIS(vector<int> &nums) { return helper(0, -1, nums); }

// NOTE: Memoization => We will do co-ordinate shift -> -1 to 0, 0 to 1 and so
// on...
// TC: O(n * n)  SC: O(n * n) + O(n)
int helper_memo(int index, int prevIndex, vector<int> &nums,
                vector<vector<int>> &dp) {
  int n = nums.size();
  if (index == n) {
    return 0;
  }

  if (dp[index][prevIndex + 1] != -1) {
    return dp[index][prevIndex + 1];
  }

  int take = 0;
  if (prevIndex == -1 || nums[index] > nums[prevIndex]) {
    take = 1 + helper_memo(index + 1, index, nums, dp);
  }
  int notTake = helper_memo(index + 1, prevIndex, nums, dp);

  return dp[index][prevIndex + 1] = max(take, notTake);
}

int LIS_memo(vector<int> &nums) {

  int n = nums.size();
  vector<vector<int>> dp(n + 1, vector<int>(n + 1, -1));
  return helper_memo(0, -1, nums, dp);
}

// NOTE: Tabulation
// TC: O(n * n)  SC:O(n * n)
int tabulation(vector<int> &nums) {

  int n = nums.size();
  vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));

  for (int i = n - 1; i >= 0; i--) {
    for (int prevIndex = -1; prevIndex < i; prevIndex++) {
      int take = 0;
      if (prevIndex == -1 || nums[i] > nums[prevIndex]) {
        take = 1 + dp[i + 1][i + 1]; // Ek shifted hai prevIndex isliye
      }
      int notTake = dp[i + 1][prevIndex + 1];

      dp[i][prevIndex + 1] = max(take, notTake);
    }
  }

  return dp[0][0];
}

// NOTE: Space optimization
// TC: O(n * n)  SC: O(n)
int space(vector<int> &nums) {

  int n = nums.size();
  vector<int> next(n + 1, 0);

  for (int i = n - 1; i >= 0; i--) {
    vector<int> curr(n + 1, 0);
    for (int prevIndex = -1; prevIndex < i; prevIndex++) {
      int take = 0;
      if (prevIndex == -1 || nums[i] > nums[prevIndex]) {
        take = 1 + next[i + 1];
      }
      int notTake = next[prevIndex + 1];

      curr[prevIndex + 1] = max(take, notTake);
    }
    next = curr;
  }

  return next[0];
}

// NOTE: Space optimization Better
// HACK: Dp[i] stores what is the longest increasing subsequence that is ending
// with element at index i
int space_better(vector<int> &nums) {

  int n = nums.size();
  vector<int> dp(n + 1, 1);

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < i; j++) {
      if (nums[i] > nums[j]) {
        dp[i] = max(dp[i], dp[j] + 1);
      }
    }
  }

  return *max_element(dp.begin(), dp.end());
}

// HACK: Binary Search
//  NOTE:Binary Search
// TC: O( n * log(n) )  SC: O(n)
int best(vector<int> &nums) {
  int n = nums.size();
  vector<int> temp;
  temp.push_back(nums[0]);
  for (int i = 1; i < n; i++) {
    if (nums[i] > temp.back()) {
      temp.push_back(nums[i]);
    } else {
      // Find the correct position of this value in the present temp
      int pos = lower_bound(temp.begin(), temp.end(), nums[i]) - temp.begin();
      temp[pos] = nums[i];
    }
  }

  return temp.size();
}

int main() {
#ifndef ONLINE_JUDGE
  freopen("Error.txt", "w", stderr);
  freopen("input.txt", "r", stdin);
#endif
  ratnesh();
}
