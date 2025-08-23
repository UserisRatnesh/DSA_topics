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
// TC: O(3^(n*m)) SC: O(rows) -> Height of recursion stack
int helper(int row, int col, vector<vector<int>> &matrix) {
  if (col < 0 || col >= matrix[0].size()) {
    return INT_MAX;
  }
  if (row == 0) {
    return matrix[row][col];
  }

  int up = helper(row - 1, col, matrix);
  int up_left = helper(row - 1, col - 1, matrix);
  int up_right = helper(row - 1, col + 1, matrix);

  return matrix[row][col] + min({up, up_left, up_right});
}

int min_falling_path_sum_recursion(vector<vector<int>> &matrix) {
  int rows = matrix.size();
  int cols = matrix[0].size();

  int ans = INT_MAX;
  for (int j = cols - 1; j >= 0; j--) {
    int smallAns = helper(rows - 1, j, matrix);
    ans = min(ans, smallAns);
  }

  return ans;
}

// NOTE: Memoization
// TC: O(n*m) SC: O(n*m) + O(rows) -> Height of recursion stack
int memo(int row, int col, vector<vector<int>> &matrix,
         vector<vector<int>> &dp) {

  if (col < 0 || col >= matrix[0].size()) {
    return INT_MAX;
  }
  if (row == 0) {
    return matrix[row][col];
  }

  if (dp[row][col] != -1) {
    return dp[row][col];
  }

  int up = memo(row - 1, col, matrix, dp);
  int up_left = memo(row - 1, col - 1, matrix, dp);
  int up_right = memo(row - 1, col + 1, matrix, dp);

  return dp[row][col] = matrix[row][col] + min({up, up_left, up_right});
}

int minFallingPathSum_memo(vector<vector<int>> &matrix) {
  int rows = matrix.size();
  int cols = matrix[0].size();

  int ans = INT_MAX;
  vector<vector<int>> dp(rows, vector<int>(cols, -1));
  for (int j = cols - 1; j >= 0; j--) {
    int smallAns = memo(rows - 1, j, matrix, dp);
    ans = min(ans, smallAns);
  }

  return ans;
}

// NOTE: Tabulation
// TC: O(n*m) SC: O(n*m)
int minFallingPathSum(vector<vector<int>> &matrix) {
  int rows = matrix.size();
  int cols = matrix[0].size();
  vector<vector<int>> dp(rows, vector<int>(cols, -1));

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if (i == 0) {
        dp[i][j] = matrix[i][j];
        continue;
      }
      int up = dp[i - 1][j];
      int up_left = INT_MAX;
      if (j - 1 >= 0) {
        up_left = dp[i - 1][j - 1];
      }
      int up_right = INT_MAX;
      if (j + 1 < cols) {
        up_right = dp[i - 1][j + 1];
      }

      dp[i][j] = matrix[i][j] + min({up, up_left, up_right});
    }
  }

  int ans = INT_MAX;
  for (int j = 0; j < cols; j++) {
    ans = min(ans, dp[rows - 1][j]);
  }

  return ans;
}

// NOTE: Space optimization
// TC: O(n*m) SC: O(cols)
int space_op(vector<vector<int>> &matrix) {

  int rows = matrix.size();
  int cols = matrix[0].size();
  vector<int> prev(cols, 0);

  for (int i = 0; i < rows; i++) {
    vector<int> temp(cols, -1);
    for (int j = 0; j < cols; j++) {
      int up = prev[j];
      int up_left = INT_MAX;
      if (j - 1 >= 0) {
        up_left = prev[j - 1];
      }
      int up_right = INT_MAX;
      if (j + 1 < cols) {
        up_right = prev[j + 1];
      }

      temp[j] = matrix[i][j] + min({up, up_left, up_right});
    }

    prev = temp;
  }

  int ans = INT_MAX;
  for (auto it : prev) {
    ans = min(ans, it);
  }
  return ans;
}

int main() {
#ifndef ONLINE_JUDGE
  freopen("Error.txt", "w", stderr);
  freopen("input.txt", "r", stdin);
#endif
  ratnesh();
}
