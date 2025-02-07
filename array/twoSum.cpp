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

// NOTE: Better
vector<int> twoSumBetter(vector<int> &nums, int target) {

  int n = nums.size();
  map<int, int> mpp;
  for (int i = 0; i < n; i++) {
    int req = target - nums[i];
    if (mpp.find(req) != mpp.end()) {
      return {mpp[req], i};
    }

    mpp[i] = nums[i];
  }

  return {-1, -1};
}

// NOTE: Optimal

vector<int> towSum_optimal(vector<int> &nums, int target) {
  int n = nums.size();

  // sort the nums array with index inhand
  vector<pair<int, int>> vec;
  for (int i = 0; i < n; i++) {
    vec.pb({nums[i], i});
  }

  sort(vec.begin(), vec.end(),
       [](const pair<int, int> p1, const pair<int, int> p2) {
         return p1.first < p2.first;
       });

  int left = 0, right = n - 1;
  while (left < right) {
    int sum = vec[left].first + vec[right].first;
    if (sum == target) {
      return {vec[left].second, vec[right].second};
    }
    if (sum > target) {
      right--;
    } else {
      left++;
    }
  }
  return {-1, -1};
}

int main() {
#ifndef ONLINE_JUDGE
  freopen("Error.txt", "w", stderr);
#endif
  fastio();
}
