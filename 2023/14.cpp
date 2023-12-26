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
  LL ans = 0;
  isi.clear();
  string tmp;
  while (getline(cin, tmp)) {
    if (tmp == "") break;
    isi.pb(tmp);
  }
  int n = sz(isi);
  if (n == 0) return 0;
  int m = sz(isi[0]);
  // Geser ke atas
  auto push = [&]() {
    n = sz(isi);
    m = sz(isi[0]);
    rep(j, 0, m) {
      rep(i, 0, n) {
        if (isi[i][j] == '.') {
          rep(go, i, n) {
            if (isi[go][j] == '.') continue;
            if (isi[go][j] == '#') break;
            swap(isi[i][j], isi[go][j]);
            break;
          }
        }
      }
    }
  };
  auto rotate = [&]() {
    n = sz(isi);
    m = sz(isi[0]);
    vector<string> newIsi(m, string(n, ' '));
    rep(i, 0, n) rep(j, 0, m) {
      newIsi[j][n - i - 1] = isi[i][j];
    }
    isi = move(newIsi);
  };
  const LL kLim = 4 * 1000000;
  for (int iter = 0; iter < kLim; iter++) {
    push();
    rotate();
    if ((iter + 1)% 4 == 0) {
      ans = 0;
      n = sz(isi);
      m = sz(isi[0]);
      rep(i, 0, n) {
        rep(j, 0, m) {
          if (isi[i][j] == 'O') ans += n - i;
        }
      }
      cout << iter << " " << ans << endl;
    }
  }
  // push();
  // trav(cur, isi) cout << cur << endl;

  cout << ans << endl;
}