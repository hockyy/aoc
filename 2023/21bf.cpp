#include "bits/stdc++.h"
using namespace std;

#define rep(i,a,b) for(int i = a;i < b;i++)
#define trav(nx, v) for(auto &nx : v)
#define all(v) begin(v), end(v)
#define sz(v) (int) v.size()
#define pb push_back
#define fi first
#define se second
typedef long long LL;
typedef pair<LL, LL> PLL;
// 0  1  2  3
// R, D, L, U
string let2 = ">v<^";
string let = "RDLU";
map <char, LL> goDir;
LL dx[] = {0, 1, 0, -1, 1, 1, -1, -1};
LL dy[] = {1, 0, -1, 0, 1, -1, 1, -1};

LL n, m;
LL vis[10][4005][4005];
LL maxTurn[15];

const LL base = 131;
LL kotak[105][105];

bool safe(int x, int y) {
  return x >= 0 && x < n && y >= 0 && y <= m;
}

LL quadrant(LL x, LL y) {
  assert(x || y);
  if (x) x /= abs(x);
  if (y) y /= abs(y);
  rep(i, 0, 8) if (dx[i] == x && dy[i] == y) return i;
  assert(0);
  return -1;
}


LL distance(PLL a, PLL b) {
  return abs(a.fi - b.fi) + abs(a.se - b.se);
}


inline void fasterios(){
  cin.tie(0)->sync_with_stdio(0);
  // cin.exceptions(cin.failbit);
}

vector <string> isi;
int main() {
  fasterios();
  memset(vis, -1, sizeof(vis));
  const LL kStep = 504;
  string s;
  while (cin >> s) {
    if (s == "") break;
    // cout << s << endl;
    isi.pb(s);
  }

  n = sz(isi);
  m = sz(isi[0]);
  cout << n << " " << m << endl;
  assert(n%2 == 1);
  assert(m%2 == 1);
  PLL middle;
  rep(i, 0, n) {
    rep(j, 0, m) {
      if (isi[i][j] == 'S') {
        middle = {i, j};
      }
    }
  }
  middle = {n / 2, m / 2};
  LL nonEmpty[2] = {0, 0};
  rep(i, 0, n) rep(j, 0, m) nonEmpty[(i + j) % 2] += isi[i][j] != '#';
  PLL startTurn[] = {
    {middle.fi, 0},
    {0, middle.se},
    {middle.fi, m - 1},
    {n - 1, middle.se},
    {0, 0},
    {0, m - 1},
    {n - 1, m - 1},
    {n - 1, 0},
    middle,
  };

  rep(turn, 0, 9) {
    queue <PLL> antri;
    PLL mulai = startTurn[turn];
    vis[turn][mulai.fi][mulai.se] = 0;
    antri.push(mulai);
    while (!antri.empty()) {
      auto pos = antri.front();
      antri.pop();
      rep(dir, 0, 4) {
        int nx = dx[dir] + pos.fi;
        int ny = dy[dir] + pos.se;
        if (!safe(nx, ny)) continue;
        if (vis[turn][nx][ny] != -1) continue;
        if (isi[nx][ny] == '#') {
          continue;
        }
        vis[turn][nx][ny] = vis[turn][pos.fi][pos.se] + 1;
        antri.push({nx, ny});
      }
    }
    rep(i, 0, n) rep(j, 0, m) maxTurn[turn] = max(maxTurn[turn], vis[turn][i][j]);
    // rep(i, 0, n) rep(j, 0, m) {
    //   cout << vis[turn][i][j] << " \n"[j == m - 1];
    //   if (isi[i][j] == '#') vis[turn][i][j] = 1e14;
    // }
    // cout << endl;
  }
  LL ans = 0;
  LL curans = 0;
  auto debugisi = isi;
  rep(x, 0, n) {
    rep(y, 0, m) {
      LL needstep = vis[8][x][y];
      // cout << needstep << endl;
      if (needstep <= kStep && needstep % 2 == kStep % 2) {
        kotak[x/base][y/base]++;
        debugisi[x][y] = 'O';
        curans++;
      }
    }
  }
  for(int i = 0;i < 20;i++){
    for(int j = 0;j < 20;j++) {
      cout << kotak[i][j] << " ";
    }
    cout << endl;
  }
  // trav(cur, debugisi) cout << cur << endl;
  cout << "got single " << curans << endl;
  ans += curans;
  cout << "ans bf " << ans << endl;
}