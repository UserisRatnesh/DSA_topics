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

// NOTE: Kadane's algorithm
int max_subarray_sum(vector<int> &nums) {
  int max_sum = INT_MIN;

  int sum = 0;
  for (auto it : nums) {
    sum += it;
    max_sum = max(max_sum, sum);
    if (sum < 0) {
      sum = 0;
    }
  }

  return max_sum;
}

// NOTE: Print subarray with maximum sum

int max_subarray(vector<int> &nums) {

  int n = nums.size();
  int ans = INT_MIN;

  int ans_start = -1;
  int ans_end = -1;

  int start = 0;
  int sum = 0;

  for (int i = 0; i < n; i++) {
    if (sum == 0) {
      start = i;
    }
    sum += nums[i];
    if (sum > ans) {
      ans_start = start;
      ans_end = i;
      ans = sum;
    }

    if (sum < 0) {
      sum = 0;
    }
  }

  for (int i = ans_start; i <= ans_end; i++) {
    cout << nums[i] << " ";
  }
  cout << endl;
  return ans;
}

int main() {
#ifndef ONLINE_JUDGE
  freopen("Error.txt", "w", stderr);
#endif
  fastio();
}
