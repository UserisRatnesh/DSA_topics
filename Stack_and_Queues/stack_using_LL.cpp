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

// NOTE: This uses prev pointer
class Node_1 {
public:
  int data;
  Node_1 *next;
  Node_1 *prev;

  Node_1() {
    this->data = 0;
    this->next = NULL;
    this->prev = NULL;
  }

  Node_1(int x) {
    this->data = x;
    this->next = NULL;
    this->prev = NULL;
  }
};

class LinkedListStack_1 {
public:
  Node_1 *head;
  Node_1 *curr;
  Node_1 *prev;
  int size;

  LinkedListStack_1() {
    this->size = 0;
    Node_1 *newNode = new Node_1();
    this->head = newNode;
    this->curr = newNode;
    this->prev = newNode;
  }

  void push(int x) {

    Node_1 *newNode = new Node_1(x);
    newNode->prev = this->curr;
    this->curr->next = newNode;
    this->prev = this->curr;
    this->curr = this->curr->next;
    this->size++;
  }

  int pop() {
    int val = this->curr->data;
    this->curr = this->prev;
    this->curr->next = NULL;
    this->prev = this->prev->prev;
    size--;

    return val;
  }

  int top() {
    if (this->isEmpty()) {
      return -1;
    }
    return this->curr->data;
  }

  bool isEmpty() { return size == 0; }
};

// NOTE: This does not use prev pointer
// Picche ke taraf element add karo
struct Node {
  int data;
  Node *next;
  Node(int data) {
    this->data = data;
    this->next = NULL;
  }
};

class LinkedListStack {
public:
  Node *head;
  int size;
  LinkedListStack() {
    this->head = NULL;
    this->size = 0;
  }

  void push(int x) {
    Node *ele = new Node(x);
    ele->next = this->head;
    this->head = ele;
    this->size++;
  }

  int pop() {
    if (this->size == 0) {
      return -1;
    }
    int val = this->head->data;
    Node *temp = this->head;
    this->head = this->head->next;
    delete temp;
    this->size--;
    return val;
  }

  int top() {
    if (this->size == 0) {
      return -1;
    }
    return this->head->data;
  }

  bool isEmpty() { return size == 0; }
};

int main() {
#ifndef ONLINE_JUDGE
  freopen("Error.txt", "w", stderr);
  freopen("input.txt", "r", stdin);
#endif
  ratnesh();
}
