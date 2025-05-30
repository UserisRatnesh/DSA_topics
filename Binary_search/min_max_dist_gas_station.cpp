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

// TC : O(k*n) => TLE
long double minimiseMaxDistance(vector<int> &arr, int k) {

  int n = arr.size();
  vector<int> howMany(n - 1, 0);

  while (k--) {

    long double maxGap = -1;
    int maxGapIndex = -1;

    for (int i = 0; i < n - 1; i++) {
      long double gap = (arr[i + 1] - arr[i]) / (1.0 * (howMany[i] + 1));
      if (gap > maxGap) {
        maxGap = gap;
        maxGapIndex = i;
      }
    }

    howMany[maxGapIndex]++;
  }

  long double ans = -1;
  for (int i = 0; i < n - 1; i++) {
    long double gap = (arr[i + 1] - arr[i]) / (1.0 * (howMany[i] + 1));
    ans = max(ans, gap);
  }

  return ans;
}

// TC : O(k * log(n))
long double minimiseMaxDistance_Better(vector<int> &arr, int k) {

  int n = arr.size();
  priority_queue<pair<long double, int>> maxHeap; // { gap, index}
  vector<int> howMany(n - 1, 0);

  for (int i = 0; i < n - 1; i++) {
    long double gap = arr[i + 1] - arr[i];
    maxHeap.push({gap, i});
  }

  while (k--) {

    int index = maxHeap.top().second;
    maxHeap.pop();

    howMany[index]++;

    long double newGap =
        (long double)(arr[index + 1] - arr[index]) / (howMany[index] + 1);
    maxHeap.push({newGap, index});
  }

  return maxHeap.top().first;
}

// TC : O(n* log(len of ans))
int numberOfStationsReq(long double dist, vector<int> &arr) {
  int n = arr.size();
  int cnt = 0;

  for (int i = 0; i < n - 1; i++) {
    long double gap = arr[i + 1] - arr[i];
    int stationReq = gap / dist;

    if ((arr[i + 1] - arr[i]) == dist * stationReq) {
      stationReq--;
    }

    cnt += stationReq;
  }

  return cnt;
}

long double minimiseMaxDistance_optimal(vector<int> &arr, int k) {

  int n = arr.size();
  long double low = 0;
  long double high = 0;

  for (int i = 0; i < n - 1; i++) {
    high = max(high, (long double)(arr[i + 1] - arr[i]));
  }

  long double diff = 1e-6;
  long double ans = 0;
  while (high - low > diff) {
    long double mid = (low + high) / 2.0;
    int cnt = numberOfStationsReq(mid, arr);

    if (cnt > k) {
      low = mid;
    } else {
      ans = mid;
      high = mid;
    }
  }

  return ans;
}

int main() {
#ifndef ONLINE_JUDGE
  // freopen("Error.txt", "w", stderr);
  freopen("input.txt", "r", stdin);
#endif
  fastio();

  vector<int> arr = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  int k = 10;
  long double ans = minimiseMaxDistance_Better(arr, k);
  cout << ans << nl;
}
