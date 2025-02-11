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

// NOTE: Brute is storing freq of the elements

// NOTE: Using Mathematical approach
vector<ll> find_missing_and_repeating(vector<int> &nums) {
  ll n = nums.size();

  ll sn = n * (n + 1) / 2;
  ll s2n = n * (n + 1) * (2 * n + 1) / 6;

  ll s = 0;
  ll s2 = 0;
  for (auto it : nums) {
    s += it;
    s2 += ((ll)it * (ll)it);
  }

  // x + y
  ll val1 = s - sn;
  ll val2 = (s2 - s2n) / val1;

  ll repeating = (val1 + val2) / 2;
  ll missing = repeating - val1;

  return {(int)repeating, (int)missing};
}

// NOTE: Using xor operation
vector<ll> find_miss_and_repeat(vector<int> &nums) {

  ll n = nums.size();
  ll xr = 0; // xr of missing and repeating
  for (ll i = 1; i <= n; i++) {
    xr ^= i;
    xr ^= nums[i - 1];
  }

  // find position of first set bit in xr
  ll bitNo = 0;
  while (1) {
    if ((xr & (1 << bitNo)) != 0) {
      break;
    }
    bitNo++;
  }

  ll one = 0;
  ll zero = 0;
  for (ll i = 1; i <= n; i++) {
    if ((nums[i - 1] & (1 << bitNo)) != 0) {
      one ^= nums[i - 1];
    } else {
      zero ^= nums[i - 1];
    }

    if ((i & (1 << bitNo)) != 0) {
      one ^= i;
    } else {
      zero ^= i;
    }
  }

  ll count = 0;
  for (auto it : nums) {
    if (one == it) {
      count++;
    }
  }

  if (count) {
    // one is repeating
    return {(int)one, (int)zero};
  }

  return {(int)zero, (int)one};
}

int main() {
#ifndef ONLINE_JUDGE
  freopen("Error.txt", "w", stderr);
#endif
  fastio();
}
