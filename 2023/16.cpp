#include "bits/stdc++.h"
using namespace std;

#define rep(i,a,b) for(int i = a;i < b;i++)
#define trav(nx, v) for(auto &nx : v)
#define all(v) begin(v), end(v)
#define sz(v) (int) v.size()
#define pb push_back
#define fi first
#define se second

// 0  1  2  3
// R, D, L, U
string let = ">v<^";
int dx[] = {0, 1, 0, -1};
int dy[] = {1, 0, -1, 0};
int n, m;
bool safe(int x, int y) {
  return x >= 0 && y >= 0 && x < n && y < m;
}
vector <string> isi;
typedef pair<int, int> PII;
bool vis[1005][1005][4];

string mirrorChar = "-|/\\";
int couple2[] = {3, 2, 1, 0};
int couple3[] = {1, 0, 3, 2};

pair<int, int> getNext(int x, int y, int dir) {
  return {x + dx[dir], y + dy[dir]};
}

set <PII> viss;
vector <string> wow;

void go(int x, int y, int dir) {
  if (!safe(x, y)) return;
  wow[x][y] = let[dir];
  // cout << x << " " << y << " " << dir << endl;
  viss.insert({x, y});
  if (vis[x][y][dir]) return;
  vis[x][y][dir] = 1;
  // cout << isi[x][y] << endl;
  if (mirrorChar[0] == isi[x][y]) {
    if (dir % 2 == 0) {
      auto nx = getNext(x, y, dir);
      go(nx.fi, nx.se, dir);
    } else {
      // Pecah 2
      go(x, y, 0);
      go(x, y, 2);
    }
  } else if (mirrorChar[1] == isi[x][y]) {
    // cout << "here " << endl;
    if (dir % 2 == 1) {
      auto nx = getNext(x, y, dir);
      go(nx.fi, nx.se, dir);
    } else {
      // Pecah 2
      go(x, y, 1);
      go(x, y, 3);
    }
  } else if (mirrorChar[2] == isi[x][y]) {
    auto nx = getNext(x, y, couple2[dir]);
    go(nx.fi, nx.se, couple2[dir]);
  } else if (mirrorChar[3] == isi[x][y]) {
    auto nx = getNext(x, y, couple3[dir]);
    go(nx.fi, nx.se, couple3[dir]);
  } else {
    auto nx = getNext(x, y, dir);
    go(nx.fi, nx.se, dir);
  }
}

int solve(int x, int y, int dir){

  memset(vis, 0, sizeof(vis));
  viss.clear();
  go(x,y,dir);
  return viss.size();
}

int main() {
  string s;
  while (getline(cin, s)) {
    if (s == "") break;
    cout << s << endl;
    isi.pb(s);
  }
  n = isi.size();
  m = isi[0].size();
  wow = isi;
  int ans = 0;
  rep(i, 0, n) {
    ans = max(ans, solve(i, 0, 0));
  }
  rep(i, 0, n) {
    ans = max(ans, solve(i, m - 1, 2));
  }
  rep(i, 0, m) {
    ans = max(ans, solve(0, i, 1));
  }
  rep(i, 0, m) {
    ans = max(ans, solve(n - 1, i, 3));
  }
  cout << ans << endl;
}