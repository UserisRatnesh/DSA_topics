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
int ninja_training_helper(int day, vector<vector<int>> &matrix,
                          int lastChoosen) {

  if (day == 0) {
    int maxi = -1;
    for (int i = 0; i < 3; i++) {
      if (i != lastChoosen) {
        maxi = max(maxi, matrix[day][i]);
      }
    }

    return maxi;
  }

  int ans = -1;
  for (int i = 0; i < 3; i++) {
    if (i != lastChoosen) {
      int smallAns = matrix[day][i] + ninja_training_helper(day - 1, matrix, i);
      ans = max(ans, smallAns);
    }
  }

  return ans;
}

int ninjaTraining_recur(vector<vector<int>> &matrix) {
  int days = matrix.size();
  int a = ninja_training_helper(days - 1, matrix, 3);
  return a;
}

// NOTE: Memoization
// TC: O(n*4), SC: O(n*4) + o(n)
int memo(int day, vector<vector<int>> &matrix, int lastChoosen,
         vector<vector<int>> &dp) {

  if (day == 0) {
    int maxi = -1;
    for (int i = 0; i < 3; i++) {
      if (i != lastChoosen) {
        maxi = max(maxi, matrix[day][i]);
      }
    }

    return maxi;
  }

  if (dp[day][lastChoosen] != -1) {
    return dp[day][lastChoosen];
  }

  int ans = -1;
  for (int i = 0; i < 3; i++) {
    if (i != lastChoosen) {
      int smallAns = matrix[day][i] + memo(day - 1, matrix, i, dp);
      ans = max(ans, smallAns);
    }
  }

  return dp[day][lastChoosen] = ans;
}

int ninjaTraining_memo(vector<vector<int>> &matrix) {
  int n = matrix.size();

  vector<vector<int>> dp(n, vector<int>(4, -1));
  int a = memo(n - 1, matrix, 3, dp);

  return a;
}

// NOTE: Tabulation
// TC: O(n*4), SC: O(n*4)
int tabulation(vector<vector<int>> matrix) {

  int n = matrix.size();

  // dp[i][j] => Stores what is the maximum points possible when we pick jth
  // item at ith day
  vector<vector<int>> dp(n, vector<int>(4, -1));

  dp[0][0] = matrix[0][0];
  dp[0][1] = matrix[0][1];
  dp[0][2] = matrix[0][2];

  for (int i = 1; i < n; i++) {
    for (int j = 0; j < 3; j++) {
      dp[i][j] =
          matrix[i][j] + max(dp[i - 1][(j + 1) % 3], dp[i - 1][(j + 2) % 3]);
    }
  }

  return max({dp[n - 1][0], dp[n - 1][1], dp[n - 1][2]});
}

// NOTE: Space optimization
// TC: O(n*4), SC: O(4)
int space_op(vector<vector<int>> &matrix) {

  int n = matrix.size();
  vector<int> dp(4, 0);
  dp[0] = matrix[0][0];
  dp[1] = matrix[0][1];
  dp[2] = matrix[0][2];

  for (int i = 1; i < n; i++) {

    vector<int> temp(4, 0);
    for (int j = 0; j < 3; j++) {
      temp[j] = matrix[i][j] + max(dp[(j + 1) % 3], dp[(j + 2) % 3]);
    }

    dp = temp;
  }

  return max({dp[0], dp[1], dp[2]});
}

int main() {
#ifndef ONLINE_JUDGE
  freopen("Error.txt", "w", stderr);
  freopen("input.txt", "r", stdin);
#endif
  ratnesh();
}
