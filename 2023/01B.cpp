#include "bits/stdc++.h"
using namespace std;

#define rep(i,a,b) for(int i = a;i < b;i++)
#define trav(nx, v) for(auto &nx : v)
#define fi first
#define se second
#define pb push_back
#define sz(v) (int) v.size()
typedef long long LL;
LL totans = 0;
string checker[] = {"", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

int solve(string s) {
  int n = sz(s);
  pair<int, int> ans = {0, 0};
  rep(i, 0, n) {
    int ch = s[i] - '0';
    if (isdigit(s[i])) {
      if (!ans.fi) ans.fi = ch;
      ans.se = ch;
      continue;
    }
    rep(j, 1, 10) {
      string tmp = s.substr(i, sz(checker[j]));
      if (tmp == checker[j]) {
        if (!ans.fi) ans.fi = j;
        ans.se = j;
        break;
      }
    }
  }
  totans += ans.fi * 10 + ans.se;
  return 0;
}

int main() {
  string s;
  while (cin >> s) solve(s);
  cout << totans << endl;
}