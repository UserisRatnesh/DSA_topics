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

// BRUTE: TC = O(n^2)
int numberOfSubstrings(string s) {

  int n = s.size();
  int ans = 0;

  for (int i = 0; i < n; i++) {

    bool a = false;
    bool b = false;
    bool c = false;

    for (int j = i; j < n; j++) {
      if (s[j] == 'a') {
        a = true;
      } else if (s[j] == 'b') {
        b = true;
      } else if (s[j] == 'c') {
        c = true;
      }

      if (a && b && c) {
        ans++;
      }
    }
  }

  return ans;
}

// BRUTE: A bit optimized. TC = O(n^2)
int numberOfSubstrings_I(string s) {

  int n = s.size();
  int ans = 0;

  for (int i = 0; i < n; i++) {

    bool a = false;
    bool b = false;
    bool c = false;

    for (int j = i; j < n; j++) {
      if (s[j] == 'a') {
        a = true;
      } else if (s[j] == 'b') {
        b = true;
      } else if (s[j] == 'c') {
        c = true;
      }

      if (a && b && c) {
        ans += (n - j);
        break;
      }
    }
  }

  return ans;
}

// BETTER: TC = O(2n)
int numberOfSubstr_better(string s) {
  int n = s.size();
  int ans = 0;

  int l = 0;
  int r = 0;

  vector<int> seen(3, 0);

  while (r < n) {

    seen[s[r] - 'a']++;

    while (seen[0] > 0 && seen[1] > 0 && seen[2] > 0) {
      ans += (n - r);
      seen[s[l] - 'a']--;
      l++;
    }

    r++;
  }

  return ans;
}

// OPTIMAL: TC = (n)
int numberOfSubstr_op(string s) {

  int n = s.size();
  int ans = 0;
  vector<int> lastSeen(3, -1);

  int l = 0;
  int r = 0;
  while (r < n) {
    lastSeen[s[r] - 'a'] = r;

    int minIndex = *min_element(lastSeen.begin(), lastSeen.end());

    // Even if we do not check it does not matter since, In that case
    // minIndex = -1 and 1 + (-1) == 0. So zero will be added to ans
    if (minIndex != -1) {
      ans += 1 + minIndex;
    }
    r++;
  }

  return ans;
}

int main() {
#ifndef ONLINE_JUDGE
  freopen("Error.txt", "w", stderr);
  freopen("input.txt", "r", stdin);
#endif
  ratnesh();
}
