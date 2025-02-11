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

// NOTE: Using merge sort algorithm
ll merge(vector<int> &nums, int start, int mid, int end) {

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
      ans += mid - left + 1;
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
  return ans;
}

ll merge_sort(vector<int> &nums, int start, int end) {
  if (start >= end) {
    return 0;
  }

  ll mid = (start + end) / 2;

  ll ans = 0;
  ans += merge_sort(nums, start, mid);
  ans += merge_sort(nums, mid + 1, end);
  ans += merge(nums, start, mid, end);

  return ans;
}

ll number_of_inversion(vector<int> nums) {

  ll n = nums.size();

  // sort left part
  ll inversions = merge_sort(nums, 0, n - 1);

  return inversions;
}

int main() {
#ifndef ONLINE_JUDGE
  freopen("Error.txt", "w", stderr);
#endif
  fastio();
}
