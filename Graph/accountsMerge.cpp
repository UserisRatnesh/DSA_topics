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

// TOPIC: Disjoint set data structure
class DisjointSet {
  vector<int> rank, size, parent;

public:
  DisjointSet(int n) {

    rank.resize(n + 1, 0);
    size.resize(n + 1, 1);
    parent.resize(n + 1);
    for (int i = 0; i <= n; i++) {
      parent[i] = i;
    }
  }

  // First time log n and after that constant time
  int findParent(int u) {
    if (u == parent[u]) {
      return u;
    }
    return parent[u] = findParent(parent[u]);
  }

  void unionByRank(int u, int v) {
    int ulp_u = findParent(u);
    int ulp_v = findParent(v);

    if (ulp_u == ulp_v) {
      return;
    }

    if (rank[ulp_u] < rank[ulp_v]) {
      parent[ulp_u] = ulp_v;
    } else if (rank[ulp_v] < rank[ulp_u]) {
      parent[ulp_v] = ulp_u;
    } else {
      parent[ulp_v] = ulp_u;
      rank[ulp_u]++;
    }
  }

  void unionBySize(int u, int v) {
    int ulp_u = findParent(u);
    int ulp_v = findParent(v);

    if (ulp_u == ulp_v) {
      return;
    }

    if (size[ulp_u] < size[ulp_v]) {
      parent[ulp_u] = ulp_v;
      size[ulp_v] += size[ulp_u];
    } else {
      parent[ulp_v] = ulp_u;
      size[ulp_u] += size[ulp_v];
    }
  }
};

vector<vector<string>> accountsMerge(vector<vector<string>> accounts) {
  int n = accounts.size();

  // map => {mail, name index}
  map<string, int> mpp;
  DisjointSet ds = DisjointSet(n);
  for (int i = 0; i < n; i++) {
    for (int j = 1; j < accounts[i].size(); j++) {
      string mail = accounts[i][j];
      if (mpp.find(mail) == mpp.end()) {
        // does not belong to any other name till now
        // just add to mpp
        mpp[mail] = i;
      } else {
        // find the parent index using mpp and connect this i and parent
        int parent = mpp[mail];
        ds.unionByRank(i, parent);
      }
    }
  }

  //  iterate over mpp
  // and store all the mail corresponding to their ultimate parent
  vector<string> mergedMail[n];
  for (pair<string, int> p : mpp) {
    string mail = p.first;
    int ultimateParent = ds.findParent(p.second);
    mergedMail[ultimateParent].pb(mail);
  }

  vector<vector<string>> ans;
  for (int i = 0; i < n; i++) {
    if (mergedMail[i].size() == 0) {
      continue;
    }

    sort(all(mergedMail[i]));

    vector<string> temp;
    temp.pb(accounts[i][0]);
    for (string mail : mergedMail[i]) {
      temp.pb(mail);
    }
    ans.pb(temp);
  }

  return ans;
}

int main() {
#ifndef ONLINE_JUDGE
  freopen("Error.txt", "w", stderr);
#endif
}
