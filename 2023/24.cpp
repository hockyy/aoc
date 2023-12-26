/*
Author : Hocky Yudhiono
Sun Dec 24 13:46:45 2023

1. You can sort the query if offline!
2. Don't bring the dp remaining state when dfsing on DP on Tree.
3. Try to reverse (Think from the back) if you stuck.
4. Be careful when submitting Div. 2 D-F, dont waste it on stupid WAs.
5. Try to reduce a problem, think of it when you're making subtasks
   like when problemsetting.
6. Matching problems can be solved with DP and vice versa.
   Counting and optimizing problems can be solved with DP.
   Try bitmasking when N is small. When big, consider greedy-ing.
7. map<string,int> is faster than you think

*/

#include <algorithm>
#include <iostream>
#include <numeric>
#include <cstdlib>
#include <cassert>
#include <cstring>
#include <iomanip>
#include <cstdio>
#include <limits>
#include <string>
#include <vector>
#include <cmath>
#include <deque>
#include <queue>
#include <stack>
#include <map>
#include <set>
using namespace std;

// Suffix Literal:
// U: Unsigned
// L: Long double
// LL: Long long
typedef long long ll;
typedef long long LL;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<vi> vvi;
typedef vector<vl> vvl;
typedef pair<int, int> PII;
typedef pair<int, int> pii;
typedef pair<ll, ll> PLL;
typedef pair<ll, ll> pll;
typedef long double ld;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define rrep(i, a, b) for(int i = a; i > (b); --i)
#define trav(a, x) for(auto& a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define popf pop_front
#define pf push_front
#define popb pop_back
#define mp make_pair
#define pb push_back
#define fi first
#define se second

// If the time limit is strict, try not to use long double

const int INFMEM = 63;
// inf constant close to, but not 2^30 - 1
// the value is 0x3f3f... and aligns with INFMEM
// Can replace with INT_MAX or LLONG_MAX for 2^31-1 and 2^63-1
const int INF = 1061109567;
const ll LINF = 4557430888798830399LL;
const double DINF = numeric_limits<double>::infinity();
const int MOD = 1000000007;
// const int MOD = 998244353;

// Do dir^1 to get reverse direction
const int dx[8] = {0, 0, 1, -1, 1, -1, 1, -1};
const int dy[8] = {1, -1, 0, 0, 1, -1, -1, 1};
const char dch[4] = {'R', 'L', 'D', 'U'};

// Do (dir + 2)%4 to get reverse direction
// const int dx[8] = {-1,0,1,0,-1,1,1,-1};
// const int dy[8] = {0,1,0,-1,1,1,-1,-1};
// const char dch[4] = {'U','R','D','L'};
const double PI = 3.141592653589793;

inline void fasterios() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);
}

// Remember to undefine if the problem is interactive

// In multi dimensional vector, avoid using
// vector.resize() to reset between each testcases
// use assign instead

typedef long double DD;
typedef __float128 LD;
const LD EPS = 1e-14L;
LD fabs(LD x) {
  if (x < 0) return -x;
  return x;
}
template<class T> inline bool eq(T x, T y) { return fabs(x - y) < EPS; }
template<class T> inline bool le(T x, T y) { return x < y + EPS; }
template<class T> inline bool lt(T x, T y) { return x + EPS < y; }
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
    return os << "(" << (long double)p.x << "," << (long double)p.y << ")";
  }
};

typedef Point<LD> PL;
vector <pair<PL, PL>> isi;

template<class P>
pair<int, P> lineInter(P s1, P e1, P s2, P e2) {
  auto d = (e1 - s1).cross(e2 - s2);
  if (eq(d, (LD)(0.0L))) {
    // if parallel
    return { -(eq(s1.cross(e1, s2), (LD)(0.0L))), P(0, 0)};
  }
  auto p = s2.cross(e1, e2), q = s2.cross(e2, s1);
  return {1, (s1 * p + e1 * q) / d};
}


typedef LD T;

struct Point3D {
  typedef Point3D P;
  typedef const P& R;
  T x, y, z;
  Point3D(){}
  Point3D(LD _x, LD _y, LD _z): x(_x), y(_y), z(_z) {}
  Point3D(LL _x, LL _y, LL _z): x(_x), y(_y), z(_z) {}
  Point3D(long double _x, long double _y, long double _z): x(_x), y(_y), z(_z) {}
  bool operator<(R p) const {
    return tie(x, y, z) < tie(p.x, p.y, p.z);
  }
  bool operator==(R p) const {
    return tie(x, y, z) == tie(p.x, p.y, p.z);
  }
  P operator+(R p) const { return P(x + p.x, y + p.y, z + p.z); }
  P operator-(R p) const { return P(x - p.x, y - p.y, z - p.z); }
  P operator*(T d) const { return P(x * d, y * d, z * d); }
  P operator/(T d) const { return P(x / d, y / d, z / d); }
  T dot(R p) const { return x * p.x + y * p.y + z * p.z; }
  T operator|(R p) const { return (*this).dot(p); }
  // v * w = (v.dist() * w.dist() * sin(theta)) n;
  // n is the vector perp to the plane made by v and w
  P cross(R p) const {return P(y * p.z - z * p.y, z * p.x - x * p.z, x * p.y - y * p.x);}
  P operator*(R p) const { return (*this).cross(p); }
  // given plane, check whether this point is below or above it
  T orient(R p, R q, R r) {return (q - p) * (r - p) | ((*this) - p);}
  // (*this) is a normal vector of plane p,q,r
  // determine the 2d orientation of p.ccw(q, r). normal got by cross
  T orientByNormal(R p, R q, R r) {return (q - p) * (r - p) | (*this);}
  T dist2() const { return x * x + y * y + z * z; }
  T dist() const { return sqrtl((long double)dist2()); }
  //Azimuthal angle (longitude) to x-axis in interval [-pi, pi]
  P unit() const { return *this / (T)dist(); } //makes dist()=1
  //returns unit vector normal to *this and p
  P normal(P p) const { return cross(p).unit(); }
  //returns point rotated 'angle' radians ccw around axis
  P rotate(double angle, P axis) const {
    double s = sin(angle), c = cos(angle); P u = axis.unit();
    return u * dot(u) * (1 - c) + (*this) * c - cross(u) * s;
  }
  friend ostream& operator<<(ostream& os, P p) {
    return os << "(" << (DD)p.x << "," << (DD)p.y << "," << (DD)p.z << ")";
  }
};
typedef Point3D p3;
struct Plane {
  // normal vector is better if its a unit vector.
  p3 n; T d;
  // From normal n and offset d
  Plane(p3 _n, T _d) : n(_n.unit()), d(_d) {}
  // From normal n and point P
  Plane(p3 _n, p3 p) : n(_n.unit()), d(n | p) {}
  // From three non-collinear points P,Q,R
  Plane(p3 p, p3 q, p3 r) : Plane((q - p) * (r - p), p) {}
  // weighted distance of point p, if n is unit vector, its signed distance
  T side(p3 p) {return (n | p) - d;}
  LD dist(p3 p) {return fabs(side(p));}
  // translate a plane by vector t
  Plane translate(p3 t) {return {n, d + (n | t)};}
  Plane shiftUp(T shift) {return {n, d + shift};}
  p3 proj(p3 p) {return p - n * side(p);}
  p3 refl(p3 p) {return p - n * 2 * side(p);}
};


struct Line3d {
  // d is a unit shift vector
  p3 d, o;
  Line3d(p3 p, p3 q) : d((q - p).unit()), o(p) {}
  // From two planes p1, p2 (requires T = double)
  // if d == 0, plane is parallel
  Line3d(Plane p1, Plane p2) {
    d = (p1.n * p2.n).unit();
    o = (p2.n * p1.d - p1.n * p2.d) * d;
  }
  LD dist2(p3 p) const {return (d * (p - o)).dist2();}
  LD dist(p3 p) const {return sqrtl((long double)dist2(p));}
  bool cmpProj(p3 p, p3 q) {return (d | p) < (d | q);}
  p3 proj(p3 p) {return o + d * (d | (p - o));}
  p3 refl(p3 p) {return proj(p) * 2 - p;}
  // when d dot p.n is 0, line is parallel with plane
  p3 inter(Plane p) {return o - d * p.side(o) / (d | p.n);}
  LD dist(const Line3d &other) const {
    p3 n = d * other.d;
    if (n == p3()) // parallel
      return dist(other.o);
    return fabs((other.o - o) | n);
  }
  // Use with care
  pair<bool, p3> closestFromLine(const Line3d &other) const {
    p3 n2 = other.d * (d * other.d);
    if (eq((double)(d | n2), 0.0)) return {0, o};
    return {1, o + d * ((other.o - o) | n2) / (d | n2)};
  }
};

int main() {
  cout << fixed << setprecision(10);
  // const LD lb = 7;
  // const LD ub = 27;
  const LD lb = 2e14L;
  const LD ub = 4e14L;
  string s;
  LL z1, z2;
  LD zz1, zz2;
  vector <pair<p3, p3>> isiBuff;
  while (getline(cin, s)) {
    if (s == "") break;
    stringstream ss(s);
    PL curPoint;
    char dummy;
    LL tmp;
    ss >> tmp;
    curPoint.x = tmp;
    ss >> dummy;
    ss >> tmp;
    curPoint.y = tmp;
    ss >> dummy;
    ss >> z1;
    zz1 = z1;
    ss >> dummy;
    PL speed;
    ss >> tmp;
    speed.x = tmp;
    ss >> dummy;
    ss >> tmp;
    speed.y = tmp;
    ss >> dummy;
    ss >> z2;
    zz2 = z2;
    isi.emplace_back(curPoint, speed);
    isiBuff.emplace_back(p3(curPoint.x, curPoint.y, zz1), p3(speed.x, speed.y, zz2));
  }
  int n = sz(isi);
  LL ans = 0;
  auto oneDirection = [&](int idx, PL c) {
    auto firstShot = isi[idx].se;
    auto secondShot = c - isi[idx].fi;
    if (le((LD)(0.0L), firstShot.dot(secondShot))) return 1;
    return 0;
  };
  vector <Plane> waduh;
  rep(i, 0, n) rep(j, i + 1, n) {
    auto res = lineInter(isi[i].fi, isi[i].fi + isi[i].se, isi[j].fi, isi[j].fi + isi[j].se);
    if (res.fi == -1) {
      // cout << "Wadhu" << endl;
      ans++;
    } else if (res.fi == 0) {
      cout << "Sejajar ---" << endl;
      Plane alhamdulillah(isiBuff[i].fi, isiBuff[i].fi + isiBuff[i].se, isiBuff[j].fi);
      // Plane alhamdulillah(isiBuff[j].fi, isiBuff[j].fi + isiBuff[j].se, isiBuff[i].fi);
      cout << (DD)alhamdulillah.dist(isiBuff[j].fi + isiBuff[j].se) << endl;
      cout << isi[i].fi << " " << isi[i].se << " " << isi[j].fi << " " << isi[j].se << endl;
      waduh.pb(alhamdulillah);
    } else {
      // cout << "Here " << endl;
      if (oneDirectiona(i, res.se) && oneDirection(j, res.se)) {
        // cout << isi[i].fi << " " << isi[i].se << " " << isi[j].fi << " " << isi[j].se << " " << res.se << endl;
        // cout << "OK " << endl;
        if (le(lb, res.se.x) && le(res.se.x, ub)) {
          if (le(lb, res.se.y) && le(res.se.y, ub)) {
            ans++;
          }
        }
      }
    }
  }
  int N = sz(waduh);
  rep(i,0,N){
    rep(j,i + 1, N){
      Line3d asu(waduh[i], waduh[j]);
      cout << "Cek " << endl;
      cout << asu.d << "  " << asu.o << endl;
    }
  }
  // trav(cur, waduh){
  //   cout << cur.n << " " << (DD)cur.d << endl;
  // }
  cout << ans << endl;
}