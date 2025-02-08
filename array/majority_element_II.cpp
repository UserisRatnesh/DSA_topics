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

// NOTE: Maintain frequency in map
vector<int> majority_element_II(vector<int> &nums) {

  int n = nums.size();
  map<int, int> mpp;
  for (auto it : nums) {
    mpp[it]++;
  }

  vector<int> ans;
  for (auto it : mpp) {
    if (it.second > n / 3) {
      ans.pb(it.first);
    }
  }

  return ans;
}

// NOTE: Optimal is just the extension of the approach used in
// majority_element_I
vector<int> majority_element_II_optimal(vector<int> &nums) {

  int ele1, ele2;
  int count1 = 0, count2 = 0;

  for (auto it : nums) {
    if (count1 == 0 && it != ele2) {
      count1 = 1;
      ele1 = it;
    } else if (count2 == 0 && it != ele1) {
      count2 = 1;
      ele2 = it;
    } else if (it == ele1) {
      count1++;
    } else if (it == ele2) {
      count2++;
    } else {
      count1--;
      count2--;
    }
  }

  // Now verify if really occur > n/3 times or not

  int freq1 = 0;
  int freq2 = 0;
  for (auto it : nums) {
    if (it == ele1) {
      freq1++;
    }
    if (it == ele2) {
      freq2++;
    }
  }

  int n = nums.size();
  int mini = (n / 3) + 1;
  vector<int> ans;
  if (freq1 >= mini) {
    ans.pb(ele1);
  }
  if (freq2 >= mini) {
    ans.pb(ele2);
  }

  return ans;
}

int main() {
#ifndef ONLINE_JUDGE
  freopen("Error.txt", "w", stderr);
#endif
  fastio();

  vector<int> nums = {1, 3, 3, 4};
  vector<int> ans = majority_element_II_optimal(nums);

  for (auto it : ans) {
    cout << it << " ";
  }
  cout << endl;
}
