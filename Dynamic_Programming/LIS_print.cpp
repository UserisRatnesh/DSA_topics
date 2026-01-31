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
void helper(int index, int prevIndex, vector<int> &nums, vector<int> &curr,
            vector<int> &ans) {

  int n = nums.size();
  if (index == n) {
    if (curr.size() > ans.size()) {
      ans = curr;
    }
    return;
  }

  // take
  if (prevIndex == -1 || nums[index] > nums[prevIndex]) {
    curr.push_back(nums[index]);
    helper(index + 1, index, nums, curr, ans);
    curr.pop_back();
  }

  // notTake
  helper(index + 1, prevIndex, nums, curr, ans);
}

vector<int> LIS(vector<int> &nums) {
  vector<int> ans;
  vector<int> curr;
  helper(0, -1, nums, curr, ans);
  return ans;
}

// ERROR: Why is it not working
//  NOTE: Memoization
//
void helper(int index, int prevIndex, vector<int> &nums, vector<int> &curr,
            vector<int> &ans, vector<vector<int>> &dp) {
  int n = nums.size();
  if (index == n) {
    if (ans.size() < curr.size()) {
      ans = curr;
    }
    return;
  }

  if (dp[index][prevIndex + 1] != -1) {
    return;
  }

  // take
  if (prevIndex == -1 || nums[index] > nums[prevIndex]) {
    curr.push_back(nums[index]);
    helper(index + 1, index, nums, curr, ans, dp);
    curr.pop_back();
  }

  helper(index + 1, prevIndex, nums, curr, ans, dp);
  dp[index][prevIndex + 1] = 1;
}

vector<int> LIS_memo(vector<int> &nums) {

  int n = nums.size();
  vector<int> ans, curr;
  vector<vector<int>> dp(n + 1, vector<int>(n + 1, -1));
  helper(0, -1, nums, curr, ans, dp);
  return ans;
}

// NOTE: Find the largest size of LIS possible in the array
int longest_LIS(vector<int> &nums) {

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

// HACK: Take help from above solution
vector<int> print_LIS(vector<int> &nums) {

  int n = nums.size();
  vector<int> dp(n + 1, 1);
  vector<int> parent(n + 1);
  for (int i = 0; i < n; i++) {
    parent[i] = i;
  }

  int maxLen = 0;
  int lastIndex = -1;

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < i; j++) {
      if (nums[i] > nums[j]) {
        if (dp[i] < dp[j] + 1) {
          // update the dp[i] and prevIndex
          dp[i] = dp[j] + 1;
          parent[i] = j;
        }
      }
    }
    // Maintain the maxLen and
    // Store index jaha agar LIS end ho with maxLen
    if (dp[i] > maxLen) {
      maxLen = dp[i];
      lastIndex = i;
    }
  }

  vector<int> ans;
  int i = lastIndex;
  ans.push_back(nums[lastIndex]);
  while (parent[i] != i) {
    i = parent[i];
    ans.push_back(nums[i]);
  }

  reverse(ans.begin(), ans.end());
  return ans;
}

int main() {
#ifndef ONLINE_JUDGE
  freopen("Error.txt", "w", stderr);
  freopen("input.txt", "r", stdin);
#endif
  ratnesh();
}
