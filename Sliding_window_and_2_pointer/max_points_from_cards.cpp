#ifndef ONLINE_JUDGE
#include "/usr/local/include/bits/stdc++.h"
#else
#include <bits/stdc++.h>
#endif

using namespace std;

#define ratnesh()                                                              \
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
#define yes cout << "YES\n"
#define no cout << "NO\n"

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

// OPTIMAL: self
int maxScore(vector<int> &cardScore, int k) {

  int n = cardScore.size();
  int sum = 0;
  int left = 0;
  int right = 0;
  int segLen = n - k;
  while (right < n && right - left + 1 <= segLen) {
    sum += cardScore[right];
    right++;
  }

  int totalSum = accumulate(cardScore.begin(), cardScore.end(), 0);

  int ans = totalSum - sum;

  // Now seg len is n-k
  while (right < n) {
    sum += cardScore[right];
    sum -= cardScore[left];
    ans = max(ans, totalSum - sum);

    right++;
    left++;
  }

  return ans;
}

// NOTE: Taken
int maxScore_I(vector<int> &cardScore, int k) {
  int lSum = 0, rSum = 0, maxSum = 0;

  // Calculate the initial sum of the first k cards
  for (int i = 0; i < k; i++) {
    lSum += cardScore[i];

    /* Initialize maxSum with the
    sum of the first k cards*/
    maxSum = lSum;
  }

  // Initialize rightIndex to iterate array from last
  int rightIndex = cardScore.size() - 1;

  for (int i = k - 1; i >= 0; i--) {

    // Remove the score of the ith card from left sum
    lSum -= cardScore[i];

    /* Add the score of the card
    from the right to the right sum*/
    rSum += cardScore[rightIndex];

    // Move to the next card from the right
    rightIndex--;

    // Update maxSum with the maximum sum found so far
    maxSum = max(maxSum, lSum + rSum);
  }

  // Return the maximum score found
  return maxSum;
}

int main() {
#ifndef ONLINE_JUDGE
  // freopen("Error.txt", "w", stderr);
  freopen("input.txt", "r", stdin);
#endif
  ratnesh();
}
