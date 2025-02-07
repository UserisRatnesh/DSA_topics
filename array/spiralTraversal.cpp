#ifndef ONLINE_JUDGE
#include "/usr/local/include/bits/stdc++.h"
#else
#include <bits/stdc++.h>
#endif

using namespace std;

#define fastio()                                                               \
  ios_base::sync_with_stdio(false);                                            \
  cin.tie(NULL);                                                               \
  cout.tie(NULL)
#define MOD 1000000007
#define MOD1 998244353
#define INF 1e18
#define nline "\n"
#define pb push_back
#define ppb pop_back
#define mp make_pair
#define ff first
#define ss second
#define PI 3.141592653589793238462
#define set_bits __builtin_popcountll
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()

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

vector<int> spiralOrder(vector<vector<int>> &matrix) {
  int minRow = 0;
  int maxRow = matrix.size() - 1;
  int minCol = 0;
  int maxCol = matrix[0].size() - 1;

  vector<int> ans;
  while (minRow <= maxRow && minCol <= maxCol) {
    for (int i = minCol; i <= maxCol; i++) {
      ans.pb(matrix[minRow][i]);
    }
    minRow++;

    for (int i = minRow; i <= maxRow; i++) {
      ans.pb(matrix[i][maxCol]);
    }
    maxCol--;

    if (maxRow >= minRow) {
      for (int i = maxCol; i >= minCol; i--) {
        ans.pb(matrix[maxRow][i]);
      }
      maxRow--;
    }

    if (minCol <= maxCol) {
      for (int i = maxRow; i >= minRow; i--) {
        ans.pb(matrix[i][minCol]);
      }
      minCol++;
    }
  }

  return ans;
}

int main() {
#ifndef ONLINE_JUDGE
  freopen("Error.txt", "w", stderr);
#endif
  fastio();
}
