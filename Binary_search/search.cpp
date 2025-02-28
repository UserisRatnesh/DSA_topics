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

// NOTE: Binary search
int search(vector<int> &nums, int target) {

  int n = nums.size();
  int low = 0;
  int high = n - 1;

  while (low <= high) {
    int mid = low + (high - low) / 2;

    if (nums[mid] == target) {
      return mid;
    } else if (nums[mid] > target) {
      high = mid - 1;
    } else {
      low = mid + 1;
    }
  }

  return -1;
}

// NOTE: Binary search in rotated array

int binarySearch(vector<int> &nums, int low, int high, int target) {
  if (low > high) {
    return -1;
  }

  int mid = low + (high - low) / 2;

  if (nums[mid] == target) {
    return mid;
  }

  int ans = -1;
  if (nums[mid] > target) {
    ans = binarySearch(nums, low, mid - 1, target);
  } else {
    ans = binarySearch(nums, mid + 1, high, target);
  }

  return ans;
}

// TC: O(n)
int search_rotated(vector<int> &nums, int target) {
  int n = nums.size();
  int low = 0;
  int high = n - 1;

  int rotatePoint = -1;

  int prev = nums[0];
  int i = 1;
  while (i < n) {
    if (prev > nums[i]) {
      rotatePoint = i;
      break;
    }
    prev = nums[i];
    i++;
  }

  int ans = binarySearch(nums, low, rotatePoint - 1, target);
  if (ans == -1) {
    return binarySearch(nums, rotatePoint, high, target);
  }

  return ans;
}

// NOTE: Binary search in rotated array
// TC: O(logN)
int search_rotated_optimal(vector<int> &nums, int target) {
  int n = nums.size();

  int low = 0;
  int high = n - 1;

  while (low <= high) {
    int mid = low + (high - low) / 2;

    if (nums[mid] == target) {
      return mid;
    }

    if (nums[low] <= nums[mid]) {
      if (target >= nums[low] && target < nums[mid]) {
        high = mid - 1;
      } else {
        low = mid + 1;
      }
    } else {
      if (target > nums[mid] && target <= nums[high]) {
        low = mid + 1;
      } else {
        high = mid - 1;
      }
    }
  }

  return -1;
}

int main() {
#ifndef ONLINE_JUDGE
  freopen("Error.txt", "w", stderr);
  freopen("input.txt", "r", stdin);
#endif
  fastio();
}
