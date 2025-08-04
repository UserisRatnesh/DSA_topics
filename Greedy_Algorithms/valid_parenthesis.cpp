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

// NOTE : Self -> working
bool isValid(string s) {

  int n = s.size();
  stack<int> openStk;
  stack<int> starStk;

  // This ')' is handelled very well
  for (int i = 0; i < n; i++) {
    char ch = s[i];
    if (ch == '(') {
      openStk.push(i);
    } else if (ch == '*') {
      starStk.push(i);
    } else {
      if (!openStk.empty()) {
        openStk.pop();
      } else if (!starStk.empty()) {
        starStk.pop();
      } else {
        return false;
      }
    }
  }

  while (!openStk.empty() && !starStk.empty()) {
    if (starStk.top() > openStk.top()) {
      // * is after '(' => good thing
      starStk.pop();
      openStk.pop();
    } else {
      return false;
    }
  }

  return openStk.empty();
}

// OPTIMAL:
// we will try to maintain the range of opening brackets possible
bool isValid_optimal(string s) {

  int mini = 0;
  int maxi = 0;
  for (auto it : s) {
    if (it == '(') {
      mini++;
      maxi++;
    } else if (it == ')') {
      mini--;
      maxi--;
    } else {
      mini--;
      maxi++;
    }

    if (mini < 0) {
      mini = 0; //  We used maxi to get rid of ) as * pretending as )
    }
    if (maxi < 0) {
      return false;
    }
  }

  return mini == 0;
}

int main() {
#ifndef ONLINE_JUDGE
  freopen("Error.txt", "w", stderr);
  freopen("input.txt", "r", stdin);
#endif
  ratnesh();
  string s = "**(**(***";

  cout << isValid(s) << nl;
}
