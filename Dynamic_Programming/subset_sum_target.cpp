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
// TC: O(2^n) SC: (n) -> stack space
bool helper(int index, vector<int> &arr, int target) {

  int n = arr.size();

  if (target == 0) {
    return true;
  }
  if (index == n - 1) {
    return arr[n - 1] == target;
  }

  bool pick = false;

  // Agar target hi chhota hai to bada value lenge to negative chala jayega
  // And we are not handelling that
  if (target >= arr[index]) {
    pick = helper(index + 1, arr, target - arr[index]);
  }
  bool not_pick = helper(index + 1, arr, target);

  return pick || not_pick;
}

int isSubsetSum(vector<int> &arr, int target) { return helper(0, arr, target); }

// NOTE: Memoization
// TC: O(n*target) SC: O(n*target) + (n) -> stack space
bool memo(int index, vector<int> &arr, int target, vector<vector<int>> &dp) {

  int n = arr.size();

  if (target == 0) {
    return true;
  }
  if (index == n - 1) {
    return arr[n - 1] == target;
  }

  if (dp[index][target] != -1) {
    return dp[index][target];
  }

  bool pick = false;
  if (target >= arr[index]) {
    pick = memo(index + 1, arr, target - arr[index], dp);
  }
  bool not_pick = memo(index + 1, arr, target, dp);

  return dp[index][target] = (pick || not_pick);
}

bool isSubsetSum_memo(vector<int> &arr, int target) {
  vector<vector<int>> dp(arr.size(), vector<int>(target + 1, -1));
  return memo(0, arr, target, dp);
}

// NOTE: Tabulation
// TC: O(n*target) SC: O(n*target)
bool tabulation(vector<int> &arr, int target) {

  int n = arr.size();
  vector<vector<bool>> dp(n, vector<bool>(target + 1, false));

  // Base case ->  When target == 0
  for (int i = 0; i < n; i++) {
    dp[i][0] = true;
  }

  // Base case -> When at last index. Can only be true if target == arr[n-1]
  dp[n - 1][arr[n - 1]] = true;

  for (int index = n - 2; index >= 0; index--) {
    for (int tempTarget = 0; tempTarget <= target; tempTarget++) {

      bool not_pick = dp[index + 1][tempTarget];
      bool pick = false;
      if (tempTarget >= arr[index]) {
        pick = dp[index + 1][tempTarget - arr[index]];
      }

      dp[index][tempTarget] = pick || not_pick;
    }
  }

  return dp[0][target];
}

// NOTE: Space optimization
// TC: O(n*target) SC: O(target)
bool space_op(vector<int> &arr, int target) {

  int n = arr.size();
  vector<bool> next(target + 1, false);
  next[0] = true;

  for (int index = n - 1; index >= 0; index--) {

    vector<bool> temp(target + 1, false);
    for (int tempTarget = 0; tempTarget <= target; tempTarget++) {

      bool not_pick = next[tempTarget];
      bool pick = false;
      if (tempTarget >= arr[index]) {
        pick = next[tempTarget - arr[index]];
      }

      temp[tempTarget] = pick || not_pick;
    }

    next = temp;
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
