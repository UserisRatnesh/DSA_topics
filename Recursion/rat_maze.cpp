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

void helper(int x, int y, vector<vector<int>> &grid, string &path,
            vector<string> &ans, vector<vector<bool>> &vis) {
  int n = grid.size();
  if (x == n - 1 && y == n - 1) {
    ans.push_back(path);
    return;
  }

  if (grid[x][y] == 0) {
    return;
  }

  vis[x][y] = true;

  if (y + 1 < n && !vis[x][y + 1] && grid[x][y + 1] == 1) {
    path += "R";
    helper(x, y + 1, grid, path, ans, vis);
    path.pop_back();
  }

  if (x + 1 < n && !vis[x + 1][y] && grid[x + 1][y] == 1) {
    path += "D";
    helper(x + 1, y, grid, path, ans, vis);
    path.pop_back();
  }

  if (y - 1 >= 0 && !vis[x][y - 1] && grid[x][y - 1] == 1) {
    path += "L";
    helper(x, y - 1, grid, path, ans, vis);
    path.pop_back();
  }

  if (x - 1 >= 0 && !vis[x - 1][y] && grid[x - 1][y] == 1) {
    path += "U";
    helper(x - 1, y, grid, path, ans, vis);
    path.pop_back();
  }

  vis[x][y] = false;
}

vector<string> find_path(vector<vector<int>> &grid) {

  int n = grid.size();
  vector<string> ans;
  string path = "";
  vector<vector<bool>> vis(n, vector<bool>(n, false));
  helper(0, 0, grid, path, ans, vis);

  return ans;
}

int main() {
#ifndef ONLINE_JUDGE
  freopen("Error.txt", "w", stderr);
  freopen("input.txt", "r", stdin);
#endif
  fastio();

  vector<vector<int>> grid = {
      {1, 0, 0, 0}, {1, 1, 0, 1}, {1, 1, 0, 0}, {0, 1, 1, 1}};

  vector<string> ans = find_path(grid);

  for (auto it : ans) {
    cout << it << nl;
  }
}
