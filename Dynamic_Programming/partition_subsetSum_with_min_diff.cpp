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

// TOPIC: Solution same as Subset sum equals to sum

// NOTE: Recursive + Memoization
// TC : O(totalSum * n)  SC: O(n + n*totalSum)
bool helper(int index, int target, vector<int> &arr, vector<vector<int>> &dp) {

  int n = arr.size();
  if (target == 0) {
    return true;
  }
  if (index == n) {
    return 0;
  }

  if (dp[index][target] != -1) {
    return dp[index][target];
  }

  bool take = false;
  if (target - arr[index] >= 0) {
    take = helper(index + 1, target - arr[index], arr, dp);
  }
  bool notTake = helper(index + 1, target, arr, dp);

  return dp[index][target] = take || notTake;
}

int minDiff_rec(vector<int> &arr, int n) {

  int totalSum = accumulate(arr.begin(), arr.end(), 0);
  int ans = INT_MAX;
  vector<vector<int>> dp(n + 1, vector<int>(totalSum + 1, -1));

  for (int i = 0; i <= totalSum; i++) {
    if (helper(0, i, arr, dp)) {
      ans = min(ans, abs((totalSum - i) - i));
    }
  }

  return ans;
}

// NOTE: Tabulation
// TC: O(n*totalSum) SC: O(n*totalSum)
int minDiff_Tabulation(vector<int> &arr, int n) {

  int totalSum = accumulate(arr.begin(), arr.end(), 0);

  vector<vector<bool>> dp(n + 1, vector<bool>(totalSum + 1, false));
  for (int i = 0; i <= n; i++) {
    dp[i][0] = true;
  }

  for (int i = n - 1; i >= 0; i--) {
    for (int j = totalSum; j >= 0; j--) {
      bool notTake = dp[i + 1][j];
      bool take = false;
      if (j - arr[i] >= 0) {
        take = dp[i + 1][j - arr[i]];
      }

      dp[i][j] = take || notTake;
    }
  }

  int mini = INT_MAX;
  for (int i = 0; i <= totalSum; i++) {
    int diff = abs((totalSum - i) - i);
    if (dp[0][i]) {
      mini = min(mini, diff);
    }
  }

  return mini;
}

// NOTE: Space optimization
// TC : O(totalSum  * n + totalSum)    SC: O(2 * totalSum)
int minDiff_space(vector<int> &arr, int n) {

  int totalSum = accumulate(arr.begin(), arr.end(), 0);

  vector<bool> next(totalSum + 1, false);
  next[0] = true;

  for (int i = n - 1; i >= 0; i--) {
    vector<bool> curr(totalSum + 1, false);
    for (int j = 0; j <= totalSum; j++) {

      bool take = false;
      if (j - arr[i] >= 0) {
        take = next[j - arr[i]];
      }
      bool notTake = next[j];

      curr[j] = take || notTake;
    }

    next = curr;
  }

  int ans = INT_MAX;
  for (int i = 0; i <= totalSum; i++) {
    if (next[i]) {
      ans = min(ans, abs((totalSum - i) - i));
    }
  }

  return ans;
}

// TOPIC: Intuitive solution
//  NOTE: Recursive + Memoization

void helper(int index, int currSum, int totalSum, int &ans, vector<int> &arr,
            vector<vector<int>> &dp) {
  int n = arr.size();
  if (index == n) {
    return;
  }

  if (dp[index][currSum] != -1) {
    return;
  }

  // Take
  helper(index + 1, currSum + arr[index], totalSum, ans, arr, dp);

  // notTake
  helper(index + 1, currSum, totalSum, ans, arr, dp);

  // Update the ans
  int firstHalf = currSum;
  int secondHalf = totalSum - currSum;
  int diff = abs(firstHalf - secondHalf);
  ans = min(ans, diff);
  dp[index][currSum] = ans;

  return;
}

int minDifference(vector<int> &arr, int n) {
  int ans = INT_MAX;
  int totalSum = accumulate(arr.begin(), arr.end(), 0);
  vector<vector<int>> dp(n, vector<int>(totalSum, -1));
  helper(0, 0, totalSum, ans, arr, dp);
  return ans;
}

int main() {
#ifndef ONLINE_JUDGE
  freopen("Error.txt", "w", stderr);
  freopen("input.txt", "r", stdin);
#endif
  ratnesh();
}
