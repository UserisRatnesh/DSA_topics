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

// NOTE: Can be done using DFS or BFS
vector<vector<int>> flood_fill_dfs(vector<vector<int>> &image, int sr, int sc,
                                   int color) {

  int row = image.size();
  int col = image[0].size();

  int oldColor = image[sr][sc];

  queue<pair<int, int>> que;
  que.push({sr, sc});
  image[sr][sc] = color;

  int dirX[] = {0, 1, 0, -1};
  int dirY[] = {1, 0, -1, 0};

  // HACK: We need to maintain visited matrix, oldColor and newColor(color) is
  // same In this case we won't be able to keep track of visited using the
  // colors

  vector<vector<bool>> vis(row, vector<bool>(col, false));
  vis[sr][sc] = true;

  while (!que.empty()) {

    auto it = que.front();
    que.pop();

    int x = it.first;
    int y = it.second;

    // Go to each child having old color and color them with new one
    for (int i = 0; i < 4; i++) {
      int newX = x + dirX[i];
      int newY = y + dirY[i];
      if (newX >= 0 && newX < row && newY >= 0 && newY < col &&
          image[newX][newY] == oldColor && vis[newX][newY] == false) {
        vis[newX][newY] = true;
        image[newX][newY] = color;
        que.push({newX, newY});
      }
    }
  }

  return image;
}

int main() {
#ifndef ONLINE_JUDGE
  freopen("Error.txt", "w", stderr);
#endif
  fastio();
}
