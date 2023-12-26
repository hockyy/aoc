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
LL memo[150][150][4];
int kMaxStep = 3;
struct Dijkstra {
  int x, y, lastDir;
  LL cost;
  Dijkstra(int _x, int _y, int _lastDir, LL _cost) : x(_x), y(_y), lastDir(_lastDir), cost(_cost){}
  bool operator <(const Dijkstra &other)const {
    return cost > other.cost;
  }
};
priority_queue <Dijkstra> antri;

void dp(Dijkstra now){
  if(memo[now.x][now.y][now.lastDir] < now.cost) {
    return;
  }
  // cout << now.x << " " << now.y << " " << now.lastDir << " " << now.cost << endl;
  if(now.x == n - 1 && now.y == m - 1) {
    cout << now.cost << endl;
    exit(0);
  }
  rep(dir,0,4){
    if(dir == now.lastDir) continue;
    if(dir == (now.lastDir^2)) continue;
    LL curGo = 0;
    rep(i,1,11){
      int nx = now.x + dx[dir] * i;
      int ny = now.y + dy[dir] * i;
      if(!safe(nx, ny)) break;
      curGo += isi[nx][ny] - '0';
      if(!(1 <= i && i <= 3)) continue;
      auto nxCost = now.cost + curGo;
      if(nxCost >= memo[nx][ny][dir]) {
        continue;
      }
      // cout << now.x << " " << now.y << " " << nx << " " << ny << " " << nxCost << endl;
      memo[nx][ny][dir] = nxCost;
      antri.push(Dijkstra(nx, ny, dir, nxCost));
    }
  }
}


int main() {
  memset(memo,63,sizeof(memo));
  string s;
  while (getline(cin, s)) {
    if (s == "") break;
    // cout << s << endl;
    isi.pb(s);
  }
  n = isi.size();
  m = isi[0].size();
  cout << n << " " << m << endl;
  memo[0][0][0] = 0;
  memo[0][0][1] = 0;
  antri.push(Dijkstra(0, 0, 0, 0));
  antri.push(Dijkstra(0, 0, 1, 0));
  while(!antri.empty()){
    auto now = antri.top();
    antri.pop();
    dp(now);
  }
}