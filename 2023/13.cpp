#include "bits/stdc++.h"
using namespace std;

#define rep(i,a,b) for(int i = a;i < b;i++)
#define sz(v) (int) v.size()
#define all(v) begin(v), end(v)
#define trav(nx, v) for(auto &nx : v)
#define pb push_back
#define fi first
#define se second
typedef long long LL;
typedef pair<LL, LL> PLL;
vector <string> isi;
int main() {
  LL tot = 0;
  while (1) {
    isi.clear();
    string tmp;
    while (getline(cin, tmp)) {
      if (tmp == "") break;
      isi.pb(tmp);
    }
    int n = sz(isi);
    if(n == 0) break;
    int m = sz(isi[0]);
    cout << "Size " << n << " " << m << endl;
    auto sameRow = [&](int a, int b) {
      LL ret = 0;
      rep(i, 0, m) if (isi[a][i] != isi[b][i]) ret++;
      return ret;
    };
    auto sameCol = [&](int a, int b) {
      LL ret = 0;
      rep(i, 0, n) if (isi[i][a] != isi[i][b]) ret++;
      return ret;
    };
    vector <PLL> ans;
    rep(i, 1, n) {
      int kiri = i - 1;
      int kanan = i;
      LL diff = 0;
      while(kiri >= 0 && kanan < n){
        diff += sameRow(kiri, kanan);
        kiri--; kanan++;
      }
      if(diff == 1) {
        ans.emplace_back(100, i);
      }
    }
    rep(i, 1, m) {
      int kiri = i - 1;
      int kanan = i;
      LL diff = 0;
      while(kiri >= 0 && kanan < m){
        diff += sameCol(kiri, kanan);
        kiri--; kanan++;
      }
      if(diff == 1) {
        ans.emplace_back(1, i);
      }
    }
    trav(cur, ans) tot += cur.fi * cur.se;
    assert(sz(ans) <= 1);
    if(sz(ans) == 0){
      trav(cur, isi) cout << cur << endl;
    }
    trav(cur, ans) cout << cur.fi << " " << cur.se << endl;

  }
  cout << tot << endl;
}