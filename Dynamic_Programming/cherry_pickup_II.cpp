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
// TC: O(3^n * 3^n)  SC: O(n) -> stack space, n = rows
int helper(int row, int j1, int j2, vector<vector<int>> &matrix) {

  if (j1 < 0 || j1 >= matrix[0].size() || j2 < 0 || j2 >= matrix[0].size()) {
    return 0;
  }

  if (row == matrix.size() - 1) {
    if (j1 == j2) {
      return matrix[row][j1];
    }
    return matrix[row][j1] + matrix[row][j2];
  }

  int maxi = INT_MIN;

  for (int di = -1; di < 2; di++) {
    for (int dj = -1; dj < 2; dj++) {
      int ans = 0;
      if (j1 == j2) {
        ans = matrix[row][j1] + helper(row + 1, j1 + di, j2 + dj, matrix);
      } else {
        ans = matrix[row][j1] + matrix[row][j2] +
              helper(row + 1, j1 + di, j2 + dj, matrix);
      }

      maxi = max(ans, maxi);
    }
  }

  return maxi;
}

int cherryPickup_recursion(vector<vector<int>> &matrix) {

  int rows = matrix.size();
  int cols = matrix[0].size();

  return helper(0, 0, cols - 1, matrix);
}

// NOTE: Memoization
// TC: O(9*n*m*m)  SC: O(n*m*m) + O(n) -> stack space, n = rows
int memo(int row, int j1, int j2, vector<vector<int>> &matrix,
         vector<vector<vector<int>>> &dp) {

  if (j1 < 0 || j1 >= matrix[0].size() || j2 < 0 || j2 >= matrix[0].size()) {
    return 0;
  }

  if (row == matrix.size() - 1) {
    if (j1 == j2) {
      return matrix[row][j1];
    }
    return matrix[row][j1] + matrix[row][j2];
  }

  if (dp[row][j1][j2] != -1) {
    return dp[row][j1][j2];
  }

  int maxi = INT_MIN;

  for (int di = -1; di < 2; di++) {
    for (int dj = -1; dj < 2; dj++) {
      int ans = 0;
      if (j1 == j2) {
        ans = matrix[row][j1] + memo(row + 1, j1 + di, j2 + dj, matrix, dp);
      } else {
        ans = matrix[row][j1] + matrix[row][j2] +
              memo(row + 1, j1 + di, j2 + dj, matrix, dp);
      }

      maxi = max(ans, maxi);
    }
  }

  return dp[row][j1][j2] = maxi;
}

int cherryPickup_memo(vector<vector<int>> &matrix) {
  int rows = matrix.size();
  int cols = matrix[0].size();
  vector<vector<vector<int>>> dp(
      rows, vector<vector<int>>(cols, vector<int>(cols, -1)));
  int ans = memo(0, 0, cols - 1, matrix, dp);

  return ans;
}

// NOTE: Tabulation
// TC: O(9*n*m*m)  SC: O(n*m*m)
int tabulation(vector<vector<int>> &matrix) {

  int rows = matrix.size();
  int cols = matrix[0].size();
  vector<vector<vector<int>>> dp(
      rows, vector<vector<int>>(cols, vector<int>(cols, -1)));

  for (int j1 = 0; j1 < cols; j1++) {
    for (int j2 = 0; j2 < cols; j2++) {
      if (j1 == j2) {
        dp[rows - 1][j1][j2] = matrix[rows - 1][j1];
      } else {
        dp[rows - 1][j1][j2] = matrix[rows - 1][j1] + matrix[rows - 1][j2];
      }
    }
  }

  for (int i = rows - 2; i >= 0; i--) {

    for (int j1 = 0; j1 < cols; j1++) {
      for (int j2 = 0; j2 < cols; j2++) {
        int maxi = INT_MIN;

        for (int di = -1; di < 2; di++) {
          for (int dj = -1; dj < 2; dj++) {
            int ans = 0;
            if (j1 == j2) {
              ans = matrix[i][j1];
            } else {
              ans = matrix[i][j1] + matrix[i][j2];
            }

            // HACK: This may lead to integer overflow
            // if (j1 + di < 0 || j1 + di >= cols || j2 + dj < 0 ||
            //     j2 + dj >= cols) {
            //   // This indicates there is no valid path to
            //   // reach last row
            //   ans += INT_MIN;
            // } else {
            //   ans += dp[i + 1][j1 + di][j2 + dj];
            // }

            // Update maxi if only valid path exists
            if (j1 + di >= 0 && j1 + di < cols && j2 + dj >= 0 &&
                j2 + dj < cols) {
              ans += dp[i + 1][j1 + di][j2 + dj];
              maxi = max(maxi, ans);
            }
          }
        }

        dp[i][j1][j2] = maxi;
      }
    }
  }

  return dp[0][0][cols - 1];
}

// NOTE: Space optimization
// TC: O(9*n*m*m)  SC: O(m*m)
int space_op(vector<vector<int>> &matrix) {
  int rows = matrix.size();
  int cols = matrix[0].size();

  vector<vector<int>> next(cols, vector<int>(cols, 0));

  for (int i = rows - 1; i >= 0; i--) {

    vector<vector<int>> temp(cols, vector<int>(cols, -1));
    for (int j1 = 0; j1 < cols; j1++) {
      for (int j2 = 0; j2 < cols; j2++) {

        int maxi = INT_MIN;
        for (int di = -1; di < 2; di++) {
          for (int dj = -1; dj < 2; dj++) {
            int ans = 0;
            if (j1 == j2) {
              ans += matrix[i][j1];
            } else {
              ans += matrix[i][j1] + matrix[i][j2];
            }

            if (j1 + di >= 0 && j1 + di < cols && j2 + dj >= 0 &&
                j2 + dj < cols) {
              ans += next[j1 + di][j2 + dj];
              maxi = max(maxi, ans);
            }
          }
        }

        temp[j1][j2] = maxi;
      }
    }

    next = temp;
  }

  return next[0][cols - 1];
}

int main() {
#ifndef ONLINE_JUDGE
  freopen("Error.txt", "w", stderr);
  freopen("input.txt", "r", stdin);
#endif
  ratnesh();
}
