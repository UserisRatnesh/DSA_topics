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
int non_adjacent(int index, vector<int> &nums) {

  if (index == 0) {
    return nums[0];
  }
  if (index < 0) {
    return 0;
  }

  int pick = nums[index] + non_adjacent(index - 2, nums);

  int notPick = non_adjacent(index - 1, nums);

  return max(pick, notPick);
}

// NOTE: Memoization
// TC: O(n); SC: O(n)+O(n)
int memo(int index, vector<int> &nums, vector<int> &dp) {

  if (index == 0) {
    return nums[0];
  }
  if (index < 0) {
    return 0;
  }

  if (dp[index] != -1) {
    return dp[index];
  }

  int pick = nums[index] + memo(index - 2, nums, dp);

  int notPick = memo(index - 1, nums, dp);

  return dp[index] = max(pick, notPick);
}

// NOTE: Tabulation
// TC: O(n); SC: O(n)
int tabulation(vector<int> &nums) {
  int n = nums.size();
  vector<int> dp(n + 1, -1); // dp[i] = max of pick and not pick at i
  dp[0] = nums[0];

  for (int i = 1; i < n; i++) {

    int pick = nums[i];
    if (i > 1) {
      pick += dp[i - 2];
    }

    int not_pick = dp[i - 1];

    dp[i] = max(pick, not_pick);
  }

  return dp[n - 1];
}

// NOTE: Space optimization
// TC: O(n); SC: O(1)
int space_opt(vector<int> &nums) {

  int n = nums.size();
  int prev_pick = 0;
  int prev_not_pick = 0;

  for (int i = 0; i < n; i++) {

    int pick = prev_not_pick + nums[i];
    int not_pick = max(prev_pick, prev_not_pick);

    prev_pick = pick;
    prev_not_pick = not_pick;
  }

  return max(prev_not_pick, prev_pick);
}

int main() {
#ifndef ONLINE_JUDGE
  freopen("Error.txt", "w", stderr);
  freopen("input.txt", "r", stdin);
#endif
  ratnesh();
}
