#include <iostream>
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

int wordLadderLength(string startWord, string targetWord,
                     vector<string> &wordList) {

  // special case
  if (startWord == targetWord) {
    return 1;
  }

  set<string> wordMap;
  for (string word : wordList) {
    wordMap.insert(word);
  }

  if (wordMap.find(targetWord) == wordMap.end()) {
    return 0;
  }

  queue<pair<string, int>> que;
  que.push({startWord, 1});

  while (!que.empty()) {
    string str = que.front().first;
    int step = que.front().second;
    que.pop();

    wordMap.erase(str);

    // Now go and change each character one by one and search if present in set
    // or not
    int len = sz(str);
    for (int i = 0; i < len; ++i) {
      char ithChar = str[i];
      for (int j = 0; j < 26; ++j) {
        char newChar = j + 'a';
        if (ithChar == newChar) {
          continue;
        }
        string newStr = str;
        int currStep = step + 1;
        newStr[i] = newChar;
        if (newStr == targetWord) {
          return currStep;
        }
        if (wordMap.find(newStr) != wordMap.end()) {
          que.push({newStr, currStep});
        }
      }
    }
  }
  return 0;
}
}

int main() {
  fastio(); // To enable fast IO.
}
