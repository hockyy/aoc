#include "bits/stdc++.h"
using namespace std;
#define rep(i,a,b) for(int i = a;i < b;i++)
#define trav(nx, v) for(auto &nx : v)
#define all(a) begin(a), end(a)
#define sz(a) (int) a.size()
#define fi first
#define se second
#define pb push_back

vector <string> isi;
bool isMarked[5005][5005];
int dx[] = {1, 0, 0, -1, 1, 1, -1, -1};
int dy[] = {0, 1, -1, 0, 1, -1, 1, -1};
typedef long long LL;

int main() {
  string s;
  while (getline(cin, s)) {
    isi.pb(s);
  }
  int n = sz(isi);
  int m = sz(isi[0]);
  auto isInside = [&](int x, int y) {
    return x >= 0 && y >= 0 && x < n && y < m;
  };
  typedef pair<int, int> PII;
  auto cntVal = [&](PII pos) {
    int x = pos.fi;
    int y = pos.se;
    LL last = 0;
    for (; y < m; y++) {
      if (!isdigit(isi[x][y])) break;
      last *= 10;
      last += isi[x][y] - '0';
    }
    return last;
  };
  auto getFirst = [&](int x, int y) {
    int last = y;
    for (; y >= 0; y--) {
      if (isdigit(isi[x][y])) {
        last = y;
      } else break;
    }
    return last;
  };
  LL ans = 0 ;
  rep(i, 0, n) {
    rep(j, 0, m) {
      if (isdigit(isi[i][j])) continue;
      if (isi[i][j] == '.') continue;
      // Symbol
      if (isi[i][j] != '*') continue;
      set <PII> tmp;
      rep(dir, 0, 8) {
        int nx = i + dx[dir];
        int ny = j + dy[dir];
        if (!isInside(nx, ny)) continue;
        if (isdigit(isi[nx][ny])) {
          auto fs = getFirst(nx, ny);
          tmp.insert({nx, fs});
        }
      }
      if (sz(tmp) != 2) continue;
 
      ans += cntVal(*tmp.begin()) * cntVal(*next(tmp.begin()));
    }
  }
  rep(i, 0, n) {
    rep(j, 0, m) {
      if (isdigit(isi[i][j])) {
        LL last = 0;
        bool marked = 0;
        if (marked) ans += last;
      }
    }
  }
  cout << ans << endl;
  return 0;
}