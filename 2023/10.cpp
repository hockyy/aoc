#include "bits/stdc++.h"
using namespace std;

#define rep(i,a,b) for(LL i = a;i < b;i++)
#define trav(nx, v) for(auto &nx : v)
#define sz(v) (LL) v.size()
#define all(v) begin(v), end(v)
#define fi first
#define se second
#define pb push_back
typedef long long LL;

// R, D, L, U
int dx[] = {0, 1, 0, -1};
int dy[] = {1, 0, -1, 0};
map <char, int> dir;
vector <string> isi;
int n, m;
bool safe(int x, int y){
  return (0 <= x && x < n && 0 <= y && y < m);
}
typedef pair<int, int> PLL;
LL ans;
bool vis[1005][1005];
vector <PLL> stacks;

/**
 * Author: Victor Lecomte, chilli
 * Date: 2019-04-26
 * License: CC0
 * Source: https://vlecomte.github.io/cp-geo.pdf
 * Description: Returns true if p lies within the polygon. If strict is true,
 * it returns false for points on the boundary. The algorithm uses
 * products in intermediate steps so watch out for overflow.
 * Time: O(n)
 * Usage:
 * vector<P> v = {P{4,4}, P{1,2}, P{2,1}};
 * bool in = inPolygon(v, P{3, 3}, false);
 * Status: stress-tested and tested on kattis:pointinpolygon
 */

template<class T> inline T doubleMax(T x, T y) { return lt(x,y) ? y : x; }
template<class T> inline T doubleMin(T x, T y) { return lt(x,y) ? x : y; }
template <class T> int sgn(T x) { return (x > 0) - (x < 0); }
template<class T>
struct Point {
    typedef Point P;
    T x, y;
    explicit Point(T X=0, T Y=0) : x(X), y(Y) {}
    bool operator<(P p) const { return tie(x,y) < tie(p.x,p.y); }
    bool operator==(P p) const { return tie(x,y)==tie(p.x,p.y); }
    P operator+(P p) const { return P(x+p.x, y+p.y); }
    P operator-(P p) const { return P(x-p.x, y-p.y); }
    P operator*(T d) const { return P(x*d, y*d); }
    P operator/(T d) const { return P(x/d, y/d); }
    T dot(P p) const { return x*p.x + y*p.y; }
    T cross(P p) const { return x*p.y - y*p.x; }
    T cross(P a, P b) const { return (a-*this).cross(b-*this); }
    // return the orientation of (*this,a,b), 1 if ccw
    int ccw(P a, P b) const { return sgn((a-*this).cross(b-*this)); }
    T dist2() const { return x*x + y*y; }
    double dist() const { return sqrt((double)dist2()); }
    // angle to x-axis in interval [-pi, pi]
    double angle() const { return atan2(y, x); }
    P unit() const { return *this/dist(); } // makes dist()=1
    P perp() const { return P(-y, x); } // rotates +90 degrees
    P normal() const { return perp().unit(); }
    // returns point rotated 'a' radians ccw around the origin
    P rotate(double a) const {
        return P(x*cos(a)-y*sin(a),x*sin(a)+y*cos(a)); }
    friend ostream& operator<<(ostream& os, P p) {
        return os << "(" << p.x << "," << p.y << ")"; }
};


template<class P> bool onSegment(P s, P e, P p) {
  return p.cross(s, e) == 0 && (s - p).dot(e - p) <= 0;
}

template<class P>
bool inPolygon(vector<P> &p, P a, bool strict = true) {
  int cnt = 0, N = sz(p);
  rep(i,0,N) {
    P q = p[(i + 1) % N];
    if (onSegment(p[i], q, a)) return !strict;
    //or: if (segDist(p[i], q, a) <= eps) return !strict;
    cnt ^= ((a.y<p[i].y) - (a.y<q.y)) * a.cross(p[i], q) > 0;
  }
  return cnt;
}
LL ansTot = 0;
typedef Point<LL> PL;
void dfs(int x, int y, int go){
  cout << x << " " << y << " " << go << endl;
  if(vis[x][y] || isi[x][y] == 'S') {
    cout << "vis " << endl;
    if(isi[x][y] == 'S'){
      stacks.emplace_back(x, y);
      vector <Point<LL>> tmp;
      trav(cur, stacks){
        tmp.emplace_back(cur.fi, cur.se);
      }
      rep(i,0,n) rep(j,0,m){
        if(inPolygon(tmp, PL(i, j), 1)) ansTot++;
      }
      trav(cur, stacks) cout << cur.fi << " " << cur.se << endl;
      // Loop
      LL len = (sz(stacks) + 1) / 2;
      ans = max(ans, len);
    }
    return;
  }
  auto &ch = isi[x][y];
  if(!dir.count(ch)) return;
  int from = go^2;
  if(!((dir[ch]>>from)&1)) return;
  vis[x][y] = 1;
  stacks.emplace_back(x, y);
  LL nxPos = dir[ch]^(1<<from);
  cout << "here " << nxPos << " " << ch << " " << from << endl;
  int nxDir = 31-__builtin_clz(nxPos);
  cout << nxDir << endl;
  int nx = x + dx[nxDir];
  int ny = y + dy[nxDir];
  cout << nx << " " << ny << endl;
  if(safe(nx, ny)) {
    dfs(nx, ny, nxDir);
  }
  stacks.pop_back();
  vis[x][y] = 0;
}

int main(){     // 1248
  dir['|'] = 10;// 0101
  dir['-'] = 5;
  dir['F'] = 3;
  dir['L'] = 9;
  dir['J'] = 12;
  dir['7'] = 6;

  // 0011
  string tmp;
  while(cin >> tmp){
    if(tmp == "") break;
    isi.pb(tmp);
  }
  n = sz(isi);
  m = sz(isi[0]);
  rep(i,0,n) rep(j,0,m) if(isi[i][j] == 'S'){
    int go = 1;
    int nx = dx[go] + i;
    int ny = dy[go] + j;
    dfs(nx, ny, go);
  }
  cout << ansTot << endl;
}