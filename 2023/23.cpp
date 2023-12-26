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
// 0  1  2  3
// R, D, L, U
string let = ">v<^";
int dx[] = {0, 1, 0, -1};
int dy[] = {1, 0, -1, 0};
LL n, m;
bool safe(int x, int y) {
  return x >= 0 && y >= 0 && x < n && y < m;
}
vector <string> isi;
typedef pair<int, int> PII;
LL vis[1005][1005];

LL toIdx(LL x, LL y) {
  return x * n + y;
}

typedef vector <int> vi;
struct UF {
  vi e;
  UF(int _n) : e(_n + 1, -1) {}
  bool sameSet(int a, int b) { return find(a) == find(b); }
  int size(int x) { return -e[find(x)]; }
  int find(int x) { return e[x] < 0 ? x : e[x] = find(e[x]); }
  bool join(int a, int b) {
    a = find(a), b = find(b);
    if (a == b) return false;
    if (e[a] > e[b]) swap(a, b);
    e[a] += e[b]; e[b] = a;
    return true;
  }
};


UF *solver;

void dfs(LL x, LL y) {
  vis[x][y] = 1;
  int cnt = 0;
  rep(dir, 0, 4) {
    int nx = dx[dir] + x;
    int ny = dy[dir] + y;
    if (vis[nx][ny]) continue;
    if (!safe(nx, ny)) continue;
    if (isi[nx][ny] != '.') continue;
    solver->join(toIdx(x, y), toIdx(nx, ny));
    dfs(nx, ny);
    cnt++;
  }
  if (cnt > 1) cout << "Warning " << x << " " << y << endl;
}

vector <int> edge[100005];
LL target;
LL memo[100005];
LL dfs(LL pos) {
  if (pos == target) return solver->size(pos);
  LL &ret = memo[pos];
  if (~ret) return ret;
  ret = INT_MIN;
  trav(nx, edge[pos]) {
    LL goThere = dfs(nx);
    if (goThere == INT_MIN) continue;
    ret = max(ret, goThere + solver->size(pos) + 1);
  }
  return ret;
}

LL mapIdx[100005];
LL szMap;
vector <LL> kuncup[100005];

LL ubah(LL pos) {
  if (mapIdx[pos]) return mapIdx[pos];
  LL tmp = ++szMap;
  return mapIdx[pos] = tmp;
}

int main() {
  memset(memo, -1, sizeof(memo));
  string s;
  while (getline(cin, s)) {
    if (s == "") break;
    // cout << s << endl;
    isi.pb(s);
  }
  n = isi.size();
  m = isi[0].size();
  solver = new UF(n * m + 1000);
  dfs(0, 1);
  rep(i, 0, n) {
    rep(j, 0, m) {
      if (isi[i][j] == 'v' && !vis[i + 1][j]) dfs(i + 1, j);
      else if (isi[i][j] == '>' && !vis[i][j + 1]) dfs(i, j + 1);
    }
  }
  rep(i, 0, n) {
    rep(j, 0, m) {
      if (isi[i][j] == '>') {
        int u = solver->find(toIdx(i, j - 1));
        int v = solver->find(toIdx(i, j + 1));
        assert(safe(i, j - 1));
        assert(safe(i, j + 1));
        assert(toIdx(i, j + 1) == v);
        assert(isi[i][j - 1] == '.');
        assert(isi[i][j + 1] == '.');
        // cout << u << " " << v << endl;
        edge[u].pb(v);
        edge[v].pb(u);
      }
      if (isi[i][j] == 'v') {
        int u = solver->find(toIdx(i - 1, j));
        int v = solver->find(toIdx(i + 1, j));
        assert(safe(i - 1, j));
        assert(safe(i + 1, j));
        assert(isi[i - 1][j] == '.');
        assert(isi[i + 1][j] == '.');
        assert(toIdx(i + 1, j) == v);
        // cout << u << " " << v << endl;
        edge[u].pb(v);
        edge[v].pb(u);
      }
    }
  }
  LL node = 0;
  typedef pair<LL, LL> PLL;
  vector <PLL> edges;
  target = solver->find(toIdx(n - 1, m - 2));
  int root = toIdx(0, 1);
  ubah(1);
  ubah(target);
  LL cnt = 0;
  rep(i, 0, n) {
    rep(j, 0, m) {
      // if(isi[i][j] != '.') cout << isi[i][j];
      if (toIdx(i, j) == solver->find(toIdx(i, j))) {
        if (isi[i][j] == '.') {
          auto &connectors = edge[toIdx(i, j)];
          if (solver->size(toIdx(i, j)) != 1) {
            cnt++;
            node++;
            // cout << sz(connectors) << endl;
            // if (sz(connectors) == 0) cout << i << " " << j << endl;
            assert(sz(connectors) <= 2);
            if (sz(connectors) == 2) {
              cout << ubah(connectors[0]) << " " << ubah(connectors[1]) << " " << solver->size(toIdx(i, j)) << endl;
            } else {
              cout << "begin " << ubah(connectors[0]) << " " << solver->size(toIdx(i, j)) << endl;
            }
          } else {
            cout << sz(connectors) << " here " << endl;
            trav(cur, connectors) {
              cout << solver->size(cur) << ",";
            }
            cout << endl;
          }
        }
      }
      // cout << 1;
    }
  }
  cout << ubah(1) << " " << ubah(target) << endl;
  cout << cnt << endl;
  cout << node << endl;
  cout << endl;
  // LL ans = dfs(root);
  // cout << ans << endl;
  cout << root << " " << target << endl;
  trav(cur, edges) cout << cur.fi << " " << cur.se << endl;
}