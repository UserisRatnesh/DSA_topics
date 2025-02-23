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

// NOTE: Using merge sort algorithm
void merge(vector<int> &nums, ll start, ll mid, ll end) {

  vector<int> temp;
  ll left = start;
  ll right = mid + 1;
  ll ans = 0;

  while (left <= mid && right <= end) {

    if (nums[left] <= nums[right]) {
      temp.pb(nums[left]);
      left++;
    } else {
      temp.pb(nums[right]);
      right++;
    }
  }

  while (left <= mid) {
    temp.pb(nums[left++]);
  }
  while (right <= end) {
    temp.pb(nums[right++]);
  }

  for (ll i = start; i <= end; i++) {
    nums[i] = temp[i - start];
  }
  return;
}

ll count_pairs(vector<int> &nums, ll start, ll mid, ll end) {

  ll right = mid + 1;
  ll left = start;
  ll ans = 0;

  while (left <= mid && right <= end) {
    if (nums[left] > 2 * 1LL * nums[right]) {
      ans += mid - left + 1;
      right++;
    } else {
      left++;
    }
  }

  return ans;
}

ll merge_sort(vector<int> &nums, ll start, ll end) {
  if (start >= end) {
    return 0;
  }

  ll mid = (start + end) / 2;

  ll ans = 0;
  ans += merge_sort(nums, start, mid);
  ans += merge_sort(nums, mid + 1, end);
  ans += count_pairs(nums, start, mid, end);
  merge(nums, start, mid, end);

  return ans;
}

ll reverse_pairs(vector<int> nums) {

  ll n = nums.size();

  // sort left part
  ll inversions = merge_sort(nums, 0, n - 1);

  return inversions;
}

int main() {
#ifndef ONLINE_JUDGE
  freopen("Error.txt", "w", stderr);
  freopen("input.txt", "r", stdin);
#endif
  fastio();
}
