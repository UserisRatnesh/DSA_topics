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

bool isSafe(int x, int y, vector<string> &vec) {

  // Can we keep a queen at this co-ordinate
  int n = vec.size();

  bool isOk = true;
  for (int i = 0; i < x; i++) {
    if (vec[i][y] == 'Q') {
      isOk = false;
      break;
    }
  }
  for (int j = 0; j < y; j++) {
    if (vec[x][j] == 'Q') {
      isOk = false;
      break;
    }
  }

  // check diagonal left up
  for (int i = x, j = y; i >= 0 && j >= 0; i--, j--) {
    if (vec[i][j] == 'Q') {
      isOk = false;
      break;
    }
  }
  // diagonal right up
  for (int i = x, j = y; i >= 0 && j < n; i--, j++) {
    if (vec[i][j] == 'Q') {
      isOk = false;
      break;
    }
  }

  return isOk;
}

void helper(int x, int n, vector<string> &vec, vector<vector<string>> &ans) {
  if (n == 0) {
    ans.push_back(vec);
    return;
  }

  int N = vec.size();
  for (int col = 0; col < N; col++) {
    if (isSafe(x, col, vec)) {
      vec[x][col] = 'Q';
      helper(x + 1, n - 1, vec, ans);
      vec[x][col] = '.';
    }
  }
}

vector<vector<string>> solve_queen(int n) {
  vector<vector<string>> ans;
  vector<string> vec(n, string(n, '.'));

  helper(0, n, vec, ans);
  return ans;
}

int main() {
#ifndef ONLINE_JUDGE
  // freopen("Error.txt", "w", stderr);
  freopen("input.txt", "r", stdin);
#endif
  fastio();

  vector<vector<string>> output = solve_queen(5);
  for (auto it : output) {
    for (string str : it) {
      cout << str << nl;
    }
    cout << nl;
  }
}
