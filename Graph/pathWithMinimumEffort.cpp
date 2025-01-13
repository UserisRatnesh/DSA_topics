#include <climits>
#include <iostream>
#include <queue>
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

int pathWithMinimumEffort(vector<vector<int>> &heights) {

  int rows = heights.size();
  int cols = heights[0].size();
  pair<int, int> source = {0, 0};
  pair<int, int> dest = {rows - 1, cols - 1};

  int dx[] = {0, 1, 0, -1};
  int dy[] = {1, 0, -1, 0};

  vector<vector<int>> effort(rows, vector<int>(cols, INT_MAX));
  effort[source.first][source.second] = 0;
  priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>,
                 greater<pair<int, pair<int, int>>>>
      que;
  que.push({0, source});

  while (!que.empty()) {
    int effTillNow = que.top().first;
    int x = que.top().second.first;
    int y = que.top().second.second;
    que.pop();

    // Since once it is queue, comes to popping.
    // It means it is the smallest among all present in priority_queue.
    // so this will be the ans.
    if (dest.first == x && dest.second == y) {
      return effTillNow;
    }

    for (int i = 0; i < 4; i++) {
      int newX = x + dx[i];
      int newY = y + dy[i];
      if (newX >= 0 && newX < rows && newY >= 0 && newY < cols) {
        int currEff = abs(heights[x][y] - heights[newX][newY]);
        int maxEff = max(effTillNow, currEff);
        if (maxEff < effort[newX][newY]) {
          effort[newX][newY] = maxEff;
          que.push({maxEff, {newX, newY}});
        }
      }
    }
  }

  // Not reachable
  return -1;
}

int main() {
  fastio(); // To enable fast IO.
}
