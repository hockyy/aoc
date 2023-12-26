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
int n, m;
bool safe(int x, int y) {
  return x >= 0 && y >= 0 && x < n && y < m;
}
vector <string> isi;
typedef pair<int, int> PII;
LL memo[1005][1005][4];
int kMaxStep = 3;

LL dp(int x, int y, int lastDir){
  if(x == n - 1 && y == m - 1) return 0;
  LL &ret = memo[x][y][lastDir];
  if(~ret) return ret;
  ret = INT_MAX;
  rep(dir,0,4){
    if(dir == lastDir) continue;
    if(dir == (lastDir^2)) continue;
    LL curGo = 0;
    rep(i,1,kMaxStep + 1){
      int nx = x + dx[dir] * i;
      int ny = y + dy[dir] * i;
      if(!safe(nx, ny)) break;
      curGo += isi[nx][ny] - '0';
      auto curans = dp(nx, ny, dir) + curGo;
      ret = min(curans, ret);
    }
  }
  // cout << x << " " << y << " " << lastDir << " " << ret << endl;
  return ret;
}


int main() {
  memset(memo,-1,sizeof(memo));
  string s;
  while (getline(cin, s)) {
    if (s == "") break;
    // cout << s << endl;
    isi.pb(s);
  }
  n = isi.size();
  m = isi[0].size();
  cout << n << " " << m << endl;
  auto ans = dp(0, 0, 0);
  auto ans2 = dp(0, 0, 1);
  cout << min(ans, ans2) << endl;
}