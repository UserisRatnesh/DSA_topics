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
// TC: O(2^n)   SC: O(n)
int helper(int index, int target, vector<int> &arr) {
  int n = arr.size();

  if (index == n - 1) {
    if (target == 0 && arr[index] == 0) {
      return 2; // Kyoki take and notTake both gives zero which is correct
    }

    if (target == 0 || arr[index] == target) {
      return 1;
    }

    return 0;
  }

  int take = 0;
  if (target - arr[index] >= 0) {
    take = helper(index + 1, target - arr[index], arr);
  }

  int notTake = helper(index + 1, target, arr);

  return (take + notTake) % MOD;
}

int countPartition(int n, int diff, vector<int> &arr) {

  int totalSum = accumulate(arr.begin(), arr.end(), 0);
  int ans = 0;
  if ((totalSum - diff) < 0 || (totalSum - diff) % 2 == 1) {
    return 0;
  }
  int target = (totalSum - diff) / 2;
  return helper(0, target, arr);
}

// NOTE: Memoization
// TC: O(n * target)  SC: O(n * target) + O(n)
int helper(int index, int target, vector<int> &arr, vector<vector<int>> &dp) {

  int n = arr.size();

  if (index == n - 1) {
    if (target == 0 && arr[index] == 0) {
      return 2;
    }

    if (target == 0 || target == arr[index]) {
      return 1;
    }

    return 0;
  }

  if (dp[index][target] != -1) {
    return dp[index][target];
  }

  int take = 0;
  if (target - arr[index] >= 0) {
    take = helper(index + 1, target - arr[index], arr, dp);
  }
  int notTake = helper(index + 1, target, arr, dp);

  return dp[index][target] = (take + notTake) % MOD;
}

int countPartition_memo(int n, int diff, vector<int> &arr) {

  int totalSum = accumulate(arr.begin(), arr.end(), 0);

  int ans = 0;

  if ((totalSum - diff) < 0 || (totalSum - diff) % 2 == 1) {
    return 0;
  }

  int target = (totalSum - diff) / 2;

  vector<vector<int>> dp(n + 1, vector<int>(target + 1, -1));

  return helper(0, target, arr, dp);
}

// NOTE: Tabulation
// TC: O(n * target)  SC: O(n * target)
int countPartition_tabulation(int n, int diff, vector<int> &arr) {

  int totalSum = accumulate(arr.begin(), arr.end(), 0);

  if (totalSum - diff < 0) {
    return 0;
  }
  if ((totalSum - diff) % 2 == 1) {
    return 0;
  }

  int target = (totalSum - diff) / 2;

  vector<vector<int>> dp(n + 1, vector<int>(target + 1, 0));
  for (int i = 0; i <= n; i++) {
    dp[i][0] = 1;
  }

  for (int i = n - 1; i >= 0; i--) {
    for (int j = 0; j <= target; j++) {
      int take = 0;
      if (j - arr[i] >= 0) {
        take = dp[i + 1][j - arr[i]];
      }
      int notTake = dp[i + 1][j];

      dp[i][j] = (take + notTake) % MOD;
    }
  }

  return dp[0][target];
}

// NOTE: Space optimization
// TC: O(n * target)  SC: O(target)
int countPartition_spaceOpt(int n, int diff, vector<int> &arr) {
  int totalSum = accumulate(arr.begin(), arr.end(), 0);

  if (totalSum - diff < 0) {
    return 0;
  }
  if ((totalSum - diff) % 2 == 1) {
    return 0;
  }

  int target = (totalSum - diff) / 2;
  vector<int> next(target + 1, 0);
  next[0] = 1;

  for (int i = n - 1; i >= 0; i--) {
    vector<int> curr(target + 1, 0);
    for (int j = 0; j <= target; j++) {
      int take = 0;
      if (j - arr[i] >= 0) {
        take = next[j - arr[i]];
      }
      int notTake = next[j];

      curr[j] = (take + notTake) % MOD;
    }

    next = curr;
  }

  return next[target];
}

int main() {
#ifndef ONLINE_JUDGE
  freopen("Error.txt", "w", stderr);
  freopen("input.txt", "r", stdin);
#endif
  ratnesh();
}
