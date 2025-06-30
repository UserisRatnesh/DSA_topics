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

bool helper(int x, int y, int index, vector<vector<char>> &board, string &word,
            vector<vector<bool>> &vis) {
  if (index >= word.size()) {
    return true;
  }

  vis[x][y] = true;

  int rows = board.size();
  int cols = board[0].size();

  int dirX[] = {0, 1, 0, -1};
  int dirY[] = {1, 0, -1, 0};

  for (int i = 0; i < 4; i++) {
    int newX = x + dirX[i];
    int newY = y + dirY[i];

    if (newX >= 0 && newX < rows && newY >= 0 && newY < cols &&
        !vis[newX][newY] && board[newX][newY] == word[index]) {
      bool smallAns = helper(newX, newY, index + 1, board, word, vis);
      if (smallAns) {
        return true;
      }
    }
  }

  vis[x][y] = false;

  return false;
}

bool exist(vector<vector<char>> &board, string word) {

  int rows = board.size();
  int cols = board[0].size();
  vector<vector<bool>> vis(rows, vector<bool>(cols, false));

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if (board[i][j] != word[0]) {
        continue;
      }

      // Zeroth char is same then only call this method
      bool smallAns = helper(i, j, 1, board, word, vis);
      if (smallAns) {
        return true;
      }
    }
  }
  return false;
}

int main() {
#ifndef ONLINE_JUDGE
  freopen("Error.txt", "w", stderr);
  freopen("input.txt", "r", stdin);
#endif
  fastio();

  vector<vector<char>> board = {
      {'G', 'e', 'G', 'k', 'Q', 'I'}, {'T', 'g', 'x', 'x', 'k', 'j'},
      {'G', 'w', 'i', 'O', 's', 'T'}, {'K', 'Z', 'W', 'O', 'M', 'h'},
      {'M', 'E', 'q', 'i', 't', 'o'}, {'B', 'R', 'J', 'K', 'p', 'z'}};
  string word = "JqEZWOitpK";

  bool ans = exist(board, word);

  cout << ans << nl;
}
