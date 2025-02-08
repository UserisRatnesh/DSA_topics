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

// NOTE: Maintain count in map
int majority_element(vector<int> &nums) {

  map<int, int> mpp;
  for (auto it : nums) {
    mpp[it]++;
  }

  int freq = 0;
  int ans = -1;
  for (auto it : mpp) {
    if (it.second > freq) {
      ans = it.first;
      freq = it.second;
    }
  }

  return ans;
}

// NOTE: Track for elements
int majority_element_optimal(vector<int> &nums) {
  int ele = -1;
  int count = 0;
  for (auto it : nums) {
    if (count == 0) {
      // start tracking for this element
      ele = it;
      count = 1;
    } else if (it == ele) {
      count++;
    } else {
      count--;
    }
  }

  // HACK: If it not sure that majority element exists then verify by counting
  // the ele if countEle > n/2 then majority element else not present

  return ele;
}

int main() {
#ifndef ONLINE_JUDGE
  freopen("Error.txt", "w", stderr);
#endif
  fastio();
}
