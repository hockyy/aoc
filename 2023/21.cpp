#include "bits/stdc++.h"
using namespace std;

#define rep(i,a,b) for(LL i = a;i < b;i++)
#define trav(nx, v) for(auto &nx : v)
#define all(v) begin(v), end(v)
#define sz(v) (LL) v.size()
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
LL dy[] = {1, 0, -1, 0, 1, -1, -1, 1};

LL n, m;
LL vis[10][500][500];
LL maxTurn[15];

bool safe(LL x, LL y) {
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

vector <string> isi;
int main() {
  memset(vis, -1, sizeof(vis));
  // const LL kStep = 504;
  const LL kStep = 26501365;
  string s;
  while (getline(cin, s)) {
    if (s == "") break;
    // cout << s << endl;
    isi.pb(s);
  }

  n = sz(isi);
  m = sz(isi[0]);
  // cout << n << " " << m << endl;
  PLL middle;
  rep(i, 0, n) {
    rep(j, 0, m) {
      if (isi[i][j] == 'S') {
        middle = {i, j};
      }
    }
  }
  LL nonEmpty[2] = {0, 0};
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
        LL nx = dx[dir] + pos.fi;
        LL ny = dy[dir] + pos.se;
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
    rep(i, 0, n) rep(j, 0, m) {
      // cout << vis[turn][i][j] << " \n"[j == m - 1];
      if (isi[i][j] == '#' || vis[turn][i][j] == -1) vis[turn][i][j] = 1e12;
    }
    // cout << endl;
  }
  rep(i, 0, n) rep(j, 0, m) nonEmpty[(i + j) % 2] += (vis[0][i][j] <= INT_MAX);
  auto getPos = [&](LL x, LL y) {
    PLL ret = {n * x, m * y};
    LL curQuad = quadrant(x, y);
    // cout << curQuad << " quad " << endl;
    // cout << ret.fi << " " << ret.se << endl;
    ret.fi += startTurn[curQuad].fi;
    ret.se += startTurn[curQuad].se;
    // cout << ret.fi << " " << ret.se << endl;
    return ret;
  };
  LL ans = 0;
  rep(turn, 0, 4) {
    LL curans = 0;
    // RDLU
    // cout << "now " << turn << endl;
    for (LL kotak = 1;; kotak++) {
      // cout << kotak << " kotak "<< endl;
      PLL realKotak = {dx[turn] * kotak, dy[turn] * kotak};
      PLL stPos = getPos(realKotak.fi, realKotak.se);
      LL curDist = distance(middle, stPos);
      // cout << curDist << " " << middle.fi << " " << middle.se << " " << stPos.fi << " " << stPos.se << endl;
      // cout << maxTurn[turn] << endl;
      if (curDist > kStep) break;
      // cout << curDist << " " << maxTurn[turn] << endl;
      if (curDist + maxTurn[turn] <= kStep) {
        // cout << "Hah " << nonEmpty[(kotak % 2)^(kStep%2)] << endl;
        curans += nonEmpty[(kotak % 2)^(kStep%2)];
        continue;
      }
      LL satuan = 0;
      rep(x, 0, n) {
        rep(y, 0, m) {
          LL needstep = curDist + vis[turn][x][y];
          if (needstep <= kStep && needstep % 2 == kStep % 2) {
            // cout << "Hah " << needstep << " " << curDist << " " << vis[turn][x][y] << endl;
            satuan++;
          }
        }
      }
      // cout << satuan << " lah " << endl;
      curans += satuan;
    }
    cout << curans << endl;
    ans += curans;
  }
  // cout << ans << " OK2 " << endl;
  // return 0;
  rep(turn, 4, 8) {
    // cout << "Cpt " << turn << endl;
    LL curans = 0;
    LL dirY = dy[turn];
    LL dirX = dx[turn];
    LL ptrY = kStep * dirY;
    for (LL i = dirX;; i += dirX) {
      LL tmpans3 = 0;
      do {
        if (ptrY == 0) break;
        PLL pojok = getPos(i, ptrY);
        if (distance(pojok, middle) + maxTurn[turn] <= kStep) break;
        else ptrY -= dirY;
      } while (1);
      // cout << "i " << i << endl;
      // cout << ptrY << endl;
      LL tmpans = (nonEmpty[0] + nonEmpty[1]) * (abs(ptrY) / 2);
      if (ptrY % 2) {
        LL tmpans2 = nonEmpty[(!(abs(i) % 2))^(kStep%2)];
        tmpans += tmpans2;
      }
      tmpans3 += tmpans;
      // cout << "WTF " << tmpans << endl;
      // cout << ptrY + 1 << endl;
      // go search for i, ptrY + 1
      LL satuan = 0;
      rep(addition,1,max(n, m) + 5){
        PLL stPojok = getPos(i, ptrY + dirY * addition);
        LL beginDist = distance(middle, stPojok);
        if(beginDist > kStep) break;
        // cout << stPojok.fi << " " << stPojok.se << " " << beginDist << endl;
        rep(x, 0, n) {
          rep(y, 0, m) {
            LL needstep = beginDist + vis[turn][x][y];
            if (needstep <= kStep && needstep % 2 == kStep % 2) {
              satuan++;
            }
          }
        }
      }
      // cout << "Here " << satuan << endl;
      curans += satuan;
      curans += tmpans3;
      if(distance(middle, getPos(i, ptrY)) > kStep) break;
    }
    // cout << "OK " << curans << endl;
    ans += curans;
  }
  // cout << ans << "OK " << endl;
  // buat tengah
  // cout << "tmp " << ans << endl;
  LL curans = 0;
  rep(x, 0, n) {
    rep(y, 0, m) {
      LL needstep = vis[8][x][y];
      // cout << needstep << " ";
      if (needstep <= kStep && needstep % 2 == kStep % 2) {
        curans++;
      }
    }
    // cout << endl;
  }
  cout << "got single " << curans << endl;
  ans += curans;
  cout << "Ans submit " << ans << endl;
}