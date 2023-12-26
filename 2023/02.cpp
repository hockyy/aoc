#include "bits/stdc++.h"
using namespace std;
#define rep(i,a,b) for(int i = a;i < b;i++)
#define trav(nx, v) for(auto &nx : v)
#define sz(v) (int) v.size()
#define all(a) begin(a), end(a)
typedef long long LL;
#define fi first
#define se second
#define pb push_back
// #define endl '\n'

map <string, LL> color;

vector<string> split(const string &tmp, char delim) {
  vector<string> ret = {""};
  trav(ch, tmp) {
    if (ch == delim) ret.pb("");
    else ret.back().pb(ch);
  }
  return ret;
}


int main() {
  LL tot = 0;
  string s;
  while (getline(cin, s)) {
    color.clear();
    auto tmp = split(s, ':');
    stringstream sid(tmp[0]);
    string dummy; sid >> dummy;
    int id; sid >> id;
    bool can = 1;
    map <string, int> curcnt;
    auto sets = split(tmp[1], ';');
    trav(cur, sets) {
      auto balls = split(cur, ',');
      trav(ball, balls) {
        stringstream ballss(ball);
        LL cnt; ballss >> cnt;
        string col; ballss >> col;
        color[col] = max(color[col], cnt);
      }
    }
    LL cube = color["red"] * color["green"] * color["blue"];
    // cout << "id " << id << " " << can << endl;
    if (can) tot += cube;
  }
  cout << tot << endl;
  return 0;
}