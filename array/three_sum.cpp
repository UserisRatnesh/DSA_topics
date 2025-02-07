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

// NOTE: Brute force -> checking all the triplets
// TC: O(n^3 * log(number of triplest possible)) -> TLE

vector<vector<int>> three_sum(vector<int> &nums, int target) {
  int n = nums.size();
  set<vector<int>> st;

  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      for (int k = j + 1; k < n; k++) {
        int sum = nums[i] + nums[j] + nums[k];
        if (sum == target) {
          vector<int> temp = {nums[i], nums[j], nums[k]};
          sort(temp.begin(), temp.end());
          st.insert(temp);
        }
      }
    }
  }

  vector<vector<int>> ans;
  for (auto it : st) {
    ans.pb(it);
  }

  return ans;
}

// NOTE: Still checking all triplets but in better way
// TC: O(n^2 * log(number of triplets)) -> TLE

vector<vector<int>> three_sum_better(vector<int> &nums, int target) {

  int n = nums.size();

  set<vector<int>> triplets;

  for (int i = 0; i < n; i++) {

    set<int> st;
    for (int j = i + 1; j < n; j++) {
      int req = target - nums[i] - nums[j];
      if (st.find(req) != st.end()) {

        // triplet found
        vector<int> temp = {nums[i], nums[j], req};
        sort(temp.begin(), temp.end());
        triplets.insert(temp);
      }
      st.insert(nums[j]);
    }
  }

  vector<vector<int>> ans(triplets.begin(), triplets.end());
  return ans;
}

// NOTE: Most optimal
// TC: O(n^2 + n*log(n))

vector<vector<int>> three_sum_optimal(vector<int> &nums, int target) {
  int n = nums.size();

  sort(all(nums));
  vector<vector<int>> ans;
  for (int i = 0; i < n; i++) {

    if (i > 0 && nums[i] == nums[i - 1]) {
      continue;
    }
    int newTarget = target - nums[i];
    int left = i + 1;
    int right = n - 1;
    while (left < right) {
      int sum = nums[left] + nums[right];
      if (sum == newTarget) {
        vector<int> temp = {nums[i], nums[left], nums[right]};
        ans.pb(temp);

        left++;
        while (left < right && nums[left] == nums[left - 1]) {
          left++;
        }

        right--;
        while (right > left && nums[right] == nums[right + 1]) {
          right--;
        }
      } else if (sum > newTarget) {
        right--;
      } else {
        left++;
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
