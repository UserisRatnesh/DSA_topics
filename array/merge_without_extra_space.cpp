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

// NOTE: Optimal I
void merge(vector<int> &nums1, int m, vector<int> &nums2, int n) {

  int left = m - 1;
  int right = 0;
  while (left >= 0 && right < n) {
    if (nums1[left] > nums2[right]) {
      swap(nums1[left], nums2[right]);
      left--;
      right++;
    } else {
      break;
    }
  }

  sort(nums1.begin(), nums1.begin() + m - 1);
  sort(all(nums2));

  for (int i = 0; i < n; i++) {
    nums1[m + i] = nums2[i];
  }
}

// NOTE: Optimal II
void merge_optimal_II(vector<int> &nums1, int m, vector<int> &nums2, int n) {

  for (int i = 0; i < n; i++) {
    nums1[m + i] = nums2[i];
  }

  int len = m + n;
  int gap = (len / 2) + (len % 2);
  while (gap) {
    int left = 0;
    int right = left + gap;
    while (right < len) {
      if (nums1[left] > nums1[right]) {
        swap(nums1[left], nums1[right]);
      }
      right++;
      left++;
    }
    if (gap == 1) {
      break;
    }
    gap = (gap / 2) + (gap % 2);
  }
}

int main() {
#ifndef ONLINE_JUDGE
  // freopen("Error.txt", "w", stderr);
  freopen("input.txt", "r", stdin);
#endif
  fastio();
  vector<int> num1 = {-5, -2, 4, 5, 0, 0, 0};
  vector<int> num2 = {-3, 1, 8};
  merge_optimal_II(num1, 4, num2, 3);
  debug(num1);
}
