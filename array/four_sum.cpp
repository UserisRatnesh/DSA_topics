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

// NOTE: Optimal -> same as three sum just with ans extra loop
// TC: O(n^3)
vector<vector<int>> four_sum(vector<int> &nums, int target) {
  int n = nums.size();

  sort(all(nums));

  vector<vector<int>> ans;
  for (int i = 0; i < n; i++) {

    if (i > 0 && nums[i] == nums[i - 1]) {
      continue;
    }

    for (int j = i + 1; j < n; j++) {
      if (j > i + 1 && nums[j] == nums[j - 1]) {
        continue;
      }

      int left = j + 1;
      int right = n - 1;
      while (left < right) {
        ll sum = (ll)nums[i] + (ll)nums[j] + (ll)nums[left] + (ll)nums[right];
        if (sum == target) {
          ans.pb({nums[i], nums[j], nums[left], nums[right]});

          left++;
          while (left < right && nums[left] == nums[left - 1]) {
            left++;
          }

          right--;
          while (right > left && nums[right] == nums[right + 1]) {
            right--;
          }

        } else if (sum > target) {
          right--;
        } else {
          left++;
        }
      }
    }
  }

  return ans;
}

int main() {
#ifndef ONLINE_JUDGE
  freopen("Error.txt", "w", stderr);
#endif
  fastio();
}
