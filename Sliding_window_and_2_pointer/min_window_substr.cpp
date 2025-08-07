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

string minWindow(string s, string t) {

  map<char, int> freqMap;
  for (auto it : t) {
    freqMap[it]++;
  }

  int n = s.size();
  int left = 0;
  int right = 0;
  map<char, int> mpp;

  string ans = s + t;

  while (right < n) {

    mpp[s[right]]++;

    while (mpp[s[left]] > freqMap[s[left]]) {
      mpp[s[left]]--;
      left++;
    }

    bool isAns = true;
    for (auto &[ch, f] : freqMap) {
      if (mpp[ch] < f) {
        isAns = false;
      }
    }

    if (isAns && ans.size() > right - left + 1) {
      ans = s.substr(left, right - left + 1);
    }

    right++;
  }

  if (ans == (s + t)) {
    return "";
  }
  return ans;
}

// OPTIMAL:
string minWindow_op(string s, string t) {

  int minLen = INT_MAX;

  int sIndex = -1;

  int hash[256] = {0}; // This hash is used to maintain that ith char is needed
                       // hahs[i] times to create string t

  for (char c : t) {
    hash[c]++;
  }

  int count = 0;
  int l = 0, r = 0;

  while (r < s.size()) {

    if (hash[s[r]] > 0) {
      count++; // It means now we need one less char to create string t
    }
    hash[s[r]]--;

    // Now this means string t can be created from selected window
    while (count == t.size()) {

      if (r - l + 1 < minLen) {
        minLen = r - l + 1;
        sIndex = l;
      }

      hash[s[l]]++; // It means s[l] char is being removed from selected window
                    // so we need it one more time
      if (hash[s[l]] >
          0) { // If it is < 0 then we have more than required of this s[l] char
        count--;
      }
      l++;
    }
    r++;
  }

  // Return minimum length substring from s
  return (sIndex == -1) ? "" : s.substr(sIndex, minLen);
}

int main() {
#ifndef ONLINE_JUDGE
  freopen("Error.txt", "w", stderr);
  freopen("input.txt", "r", stdin);
#endif
  ratnesh();
}
