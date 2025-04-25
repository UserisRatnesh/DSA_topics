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

double median(vector<int> &A, vector<int> &B) {

  int n1 = A.size(), n2 = B.size();
  int len = n1 + n2;
  int midIndex1 = len / 2;
  int midIndex2 = midIndex1 + 1;
  int mid1 = -1;
  int mid2 = -1;

  int ai = 0, bi = 0;

  int cnt = 0;
  while (ai < n1 && bi < n2) {

    cnt++;
    int small;

    if (A[ai] < B[bi]) {
      small = A[ai];
      ai++;
    } else {
      small = B[bi];
      bi++;
    }

    if (cnt == midIndex1) {
      mid1 = small;
    }
    if (cnt == midIndex2) {
      mid2 = small;
    }
  }

  while (ai < n1) {
    cnt++;
    if (cnt == midIndex1) {
      mid1 = A[ai];
    }
    if (cnt == midIndex2) {
      mid2 = A[ai];
    }
    ai++;
  }

  while (bi < n2) {
    cnt++;
    if (cnt == midIndex1) {
      mid1 = B[bi];
    }
    if (cnt == midIndex2) {
      mid2 = B[bi];
    }
    bi++;
  }

  if (len % 2 == 0) {
    return (mid1 + mid2) / 2.0;
  } else {
    return mid2;
  }
}

double median_binary_search(vector<int> &A, vector<int> &B) {

  int n1 = A.size();
  int n2 = B.size();
  int n = n1 + n2;

  if (n1 > n2) {
    return median_binary_search(B, A);
  }
  int half = n / 2;
  int mid1 = -1;
  int mid2 = -1;

  // We are going to find how many elements from A will be there in left half
  // when both merged

  int low = 0;
  int high = n1;

  while (low <= high) {
    int mid = low + (high - low) / 2;

    int l1 = mid == 0 ? INT_MIN : A[mid - 1];
    int r1 = mid == n1 ? INT_MAX : A[mid];

    int b = half - mid;

    int l2 = b == 0 ? INT_MIN : B[b - 1];
    int r2 = b == n2 ? INT_MAX : B[b];

    if (l1 <= r2 && r1 >= l2) {
      // found ans
      mid1 = max(l1, l2);
      mid2 = min(r1, r2);

      break;
    }

    if (l1 > r2) {
      high = mid - 1;
    } else {
      low = mid + 1;
    }
  }

  if (n % 2 == 1) {
    return mid2;
  }

  return (mid1 + mid2) / 2.0;
}

int main() {
#ifndef ONLINE_JUDGE
  freopen("Error.txt", "w", stderr);
  freopen("input.txt", "r", stdin);
#endif
}
