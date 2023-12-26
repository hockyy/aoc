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
LL dx[] = {0, 1, 0, -1};
LL dy[] = {1, 0, -1, 0};

LL n, m;
// const LL kShift = 1e8L;
const LL kShift = 1;
template<class T> inline T doubleMax(T x, T y) { return lt(x, y) ? y : x; }
template<class T> inline T doubleMin(T x, T y) { return lt(x, y) ? x : y; }
template <class T> int sgn(T x) { return (x > 0) - (x < 0); }
template<class T>
struct Point {
  typedef Point P;
  T x, y;
  explicit Point(T X = 0, T Y = 0) : x(X), y(Y) {}
  bool operator<(P p) const { return tie(x, y) < tie(p.x, p.y); }
  bool operator==(P p) const { return tie(x, y) == tie(p.x, p.y); }
  P operator+(P p) const { return P(x + p.x, y + p.y); }
  P operator-(P p) const { return P(x - p.x, y - p.y); }
  P operator*(T d) const { return P(x * d, y * d); }
  P operator/(T d) const { return P(x / d, y / d); }
  T dot(P p) const { return x * p.x + y * p.y; }
  T cross(P p) const { return x * p.y - y * p.x; }
  T cross(P a, P b) const { return (a - *this).cross(b - *this); }
  // return the orientation of (*this,a,b), 1 if ccw
  int ccw(P a, P b) const { return sgn((a - *this).cross(b - *this)); }
  T dist2() const { return x * x + y * y; }
  double dist() const { return sqrt((double)dist2()); }
  // angle to x-axis in interval [-pi, pi]
  double angle() const { return atan2(y, x); }
  P unit() const { return *this / dist(); } // makes dist()=1
  P perp() const { return P(-y, x); } // rotates +90 degrees
  P normal() const { return perp().unit(); }
  // returns point rotated 'a' radians ccw around the origin
  P rotate(double a) const {
    return P(x * cos(a) - y * sin(a), x * sin(a) + y * cos(a));
  }
  friend ostream& operator<<(ostream& os, P p) {
    return os << "(" << p.x << "," << p.y << ")";
  }
};

typedef Point<LL> PL;

PL getNext(LL x, LL y, LL dir, LL amount) {
  return PL(x + dx[dir] * amount, y + dy[dir] * amount);
}

string hexa = "0123456789abcdef";
map <int, char> hexaDir;

LL colorToInt(string tmp) {
  LL multiplier = 1;
  LL ret = 0;
  while (tmp.back() != '#') {
    char current = tmp.back();
    tmp.pop_back();
    ret += hexaDir[current] * multiplier;
    multiplier *= 16;
  }
  return ret;
}

// predir = kiri
// pre = atas
// dir = kanan
// ok1 = predir
// ok2 = atas

// dir = kiri
// ok2 = bawah

// if(dir == predir) ok2 = !pre
// else ok2 = pre

// predir = atas
// pre = kanan
// dir = bawah
// ok1 = atas
// ok2 = kanan

// dir = atas
// ok2 = kiri
template<class T>
T polygonArea2(vector<Point<T>>& v) {
  T a = v.back().cross(v[0]);
  rep(i,0,sz(v)-1) a += v[i].cross(v[i+1]);
  return a;
}


int main() {
  rep(i, 0, 4) {
    goDir[let[i]] = i;
  }
  rep(i, 0, 17) {
    hexaDir[hexa[i]] = i;
  }
  char arah;
  PL pos = PL(kShift, kShift);
  vector <PL> tanah;
  tanah.pb(pos);
  int pre = 3;
  PL outer = tanah.front();
  outer.x--;
  outer.y--;
  vector <PL> poly;
  int predir = 2;
  while (cin >> arah) {
    LL amount; cin >> amount;
    string color; cin >> color;
    color.pop_back();
    int dir = color.back() - '0';
    // int dir = goDir[arah];
    color.pop_back();
    amount = colorToInt(color);
    amount *= 2;
    PL nx = getNext(pos.x, pos.y, dir, amount);
    // cout << predir << endl;
    int ok1 = predir;
    int ok2 = pre;
    if(dir == predir) ok2 = pre^2;
    cout << let2[ok1] << let2[ok2] << endl;
    PL sudut(pos.x + dx[ok1] + dx[ok2], pos.y + dy[ok1] + dy[ok2]);
    poly.pb(sudut);
    cout << "here " << let2[dir] << endl;
    if(pre == dir) {
      cout << "ASU" << endl;
      exit(0);
    }
    cout << sudut << endl;
    tanah.pb(nx);
    pos = nx;
    pre = dir;
    cout << ok2 << endl;
    predir = ok2;
  }
  // cout << ans << endl;
  // LL ans = 0;
  auto ans = -polygonArea2(poly) / 8;
  cout << ans << endl;



}