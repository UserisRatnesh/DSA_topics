#include <iostream>
#include <map>
#include <set>
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

// This is giving TLE on Leetcode
vector<vector<string>> findSequences(string beginWord, string endWord,
                                     vector<string> &wordList) {

  set<string> st(wordList.begin(), wordList.end());

  vector<vector<string>> ans;
  if (beginWord == endWord) {
    ans.pb({beginWord});
    return ans;
  }
  if (st.find(endWord) == st.end()) {
    return ans;
  }

  queue<vector<string>> que;
  que.push({beginWord});

  vector<string> used;
  used.push_back(beginWord);
  int level = 0;
  while (!que.empty()) {
    vector<string> vec = que.front();
    que.pop();
    if (vec.size() > level) {
      level++;
      for (string str : used) {
        st.erase(str);
      }
      used.clear();
    }
    string str = vec.back(); // gets the last string of the vector
    if (str == endWord) {
      ans.pb(vec);
      continue;
    }
    if (ans.size() != 0) {
      continue;
    }

    int len = sz(str);
    for (int i = 0; i < len; ++i) {
      char ithChar = str[i];
      for (char c = 'a'; c <= 'z'; ++c) {
        if (c == ithChar) {
          continue;
        }
        string newStr = str;
        newStr[i] = c;
        if (st.find(newStr) != st.end()) {
          vec.pb(newStr);
          used.push_back(newStr);
          que.push({vec});
          vec.pop_back();
        }
      }
    }
  }

  return ans;
}

// Optimized solution for Leetcode

void dfs(string str, string &beginWord, map<string, int> &mpp,
         vector<string> vec, vector<vector<string>> &ans) {

  if (str == beginWord) {
    reverse(all(vec));
    ans.pb(vec);
    return;
  }

  int steps = mpp[str];

  for (int i = 0; i < str.size(); ++i) {
    char original = str[i];
    for (char c = 'a'; c <= 'z'; c++) {
      if (c == original) {
        continue;
      }
      str[i] = c;
      if (mpp.find(str) != mpp.end() && mpp[str] == steps - 1) {
        vec.pb(str);
        dfs(str, beginWord, mpp, vec, ans);
        vec.ppb();
      }
    }
    str[i] = original;
  }
}

vector<vector<string>> findSequencesBetter(string beginWord, string endWord,
                                           vector<string> &wordList) {
  set<string> st(wordList.begin(), wordList.end());

  vector<vector<string>> ans;
  if (beginWord == endWord) {
    ans.pb({beginWord});
    return ans;
  }

  if (st.find(endWord) == st.end()) {
    return ans;
  }

  map<string, int> mpp;
  mpp[beginWord] = 0;
  queue<string> que;
  que.push(beginWord);
  st.erase(beginWord);
  while (!que.empty()) {
    string str = que.front();
    int step = mpp[str];
    que.pop();

    if (str == endWord) {
      break;
    }
    for (int i = 0; i < str.size(); ++i) {
      char original = str[i];
      for (char c = 'a'; c <= 'z'; c++) {
        if (c == original) {
          continue;
        }
        str[i] = c;
        if (st.find(str) != st.end()) {
          que.push(str);
          st.erase(str);
          mpp[str] = step + 1;
        }
      }
      str[i] = original;
    }
  }

  if (mpp.find(endWord) == mpp.end()) {
    return ans;
  }

  vector<string> temp;
  temp.pb(endWord);
  dfs(endWord, beginWord, mpp, temp, ans);

  return ans;
}

int main() {
  fastio(); // To enable fast IO.
}
