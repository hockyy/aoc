/*
Author : Hocky Yudhiono
Min 24 Des 2023 08:55:44
*/

#pragma GCC optimize("Ofast,no-stack-protector,O3,unroll-loops")

#include "bits/stdc++.h"
using namespace std;

typedef __int128 LL;
typedef vector<int> vi;
typedef vector<LL> vl;
typedef vector<vi> vvi;
typedef vector<vl> vvl;
typedef pair<int, int> PII;
typedef pair<int, int> pii;
typedef pair<LL, LL> PLL;
typedef pair<LL, LL> pll;
typedef long double ld;

#define rep(i, a, b) for(LL i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define popf pop_front
#define pf push_front
#define popb pop_back
#define pb push_back
#define fi first
#define se second

const double EPS = 1e-9;
const int INFMEM = 63;

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
const int MOD = 1000000007;
// const int MOD = 998244353;

struct P3 {
  array <LL, 3> coord;

  P3() {
    coord = {0, 0, 0};
  }
};
LL __gcd(LL x, LL y) {
  if (y == 0) return x;
  return __gcd(y, x % y);
}


LL abs(LL pos) {
  if (pos < 0) return -pos;
  return pos;
}

map <vector <PLL>, int> counter;

void simplify(PLL &a) {
  LL g = __gcd(abs(a.fi), abs(a.se));
  if (g == 0) return;
  if (a.fi < 0) a.fi = -a.fi, a.se = -a.se;
  a.fi /= g;
  a.se /= g;
}
// ax + by = c;
// dx + ey = f;
pair<bool, pair<PLL, PLL>> solve(LL a, LL b, LL c, LL d, LL e, LL f) {
  // Samain a dan d
  if (a < 0) {
    a = -a;
    b = -b;
    c = -c;
  }
  if (d < 0) {
    d = -d;
    e = -e;
    f = -f;
  }
  if (a == 0 || d == 0) {
    return {0, pair<PLL, PLL>()};
  }
  LL nxA = a / __gcd(a, d) * d;
  LL multA = nxA / a;
  LL multB = nxA / d;
  a *= multA; b *= multA; c *= multA;
  d *= multB; e *= multB; f *= multB;
  b -= e;
  c -= f;
  PLL y = {c, b};
  if (!b) return {0, pair<PLL, PLL>()};
  simplify(y);
  // Sama ratakan
  d *= y.se;
  f *= y.se;
  // dx + ey = f
  f = f - y.fi * e;
  PLL x = {f, d};
  if (!d) return {0, pair<PLL, PLL>()};
  simplify(x);
  return {1, {x, y}};
}


#include <random>
#include <chrono>
// mt19937 rng(chrono::steady_clock::now().time_since_epoch().count()); //For int
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count()); //For LL
// cout << rng() << endl;
// shuffle(isi.begin(),isi.end(),rng);

LL getRange(LL a, LL b) {
  LL ran = b - a + 1;
  return (rng() % ran) + a;
}
int getRandomSqrt(int a, int b) {
  assert(a <= b);
  LL len = b - a + 1;
  int ret = sqrtl(getRange(0, len * len - 1)) + a;
  assert(a <= ret && ret <= b);
  return ret;
}

istream &operator>>(istream &s, LL &x) {
  long long tmp; s >> tmp;
  x = tmp;
  return s;
}

// ostream &operator<<(ostream &os, LL x){
//   string tmp = "";
//   while(x){
//     tmp.pb((char) ('0' + x % 10));
//     x /= 10;
//   }
//   reverse(all(tmp));
//   os << tmp;
//   return os;
// }

int main() {
  // LL memkkk; cin >> memkkk;
  // cout << memkkk << endl;
  // return 0;
  string s;
  vector <pair<P3, P3>> isi;
  while (getline(cin, s)) {
    if (s == "") break;
    stringstream ss(s);
    P3 curPoint, speed;
    char dummy;
    ss >> curPoint.coord[0] >> dummy >> curPoint.coord[1] >> dummy >> curPoint.coord[2] >> dummy >> speed.coord[0] >> dummy >> speed.coord[1] >> dummy >> speed.coord[2];
    isi.emplace_back(curPoint, speed);
  }
  // return 0;
  auto getPair = [&](int idx, int part, LL v) -> PLL {
    return {isi[idx].se.coord[part] - v, isi[idx].fi.coord[part]};
  };

  auto getNormal = [&](int idx, int part, LL pos, LL v) -> PLL {
    PLL ret = {isi[idx].fi.coord[part] - pos, v - isi[idx].se.coord[part]};
    simplify(ret);
    return ret;
  };

  auto getCFromT = [&](int idx, int part, PLL t) -> LL {
    LL c = t.fi * isi[idx].se.coord[part] + isi[idx].fi.coord[part] * t.se;
    return c;
  };;
  auto getValue = [](PLL equation, PLL x) ->pair<bool, LL> {

    LL atas = x.fi * equation.fi;
    if (abs(atas) % abs(x.se) == 0) {
      LL ret = atas / x.se + equation.se;
      return {1, ret};
    }
    return {0, 0};
  };
  int n = sz(isi);
  const LL kLim = 1000;
  const LL lb = -kLim;
  const LL ub = kLim;
  LL pivot[] = {0, 0};
  do {
    pivot[0] = rng() % n;
    pivot[1] = rng() % n;
  } while (pivot[0] == pivot[1]);
  // rep(p1, 0, n) rep(p2, p1 + 1, n) {
  // pivot[0] = p1;
  // pivot[1] = p2;
  rep(iter, 0, 20) {
    cout << (long long) iter << endl;
    do {
      pivot[0] = rng() % n;
      pivot[1] = rng() % n;
    } while (pivot[0] == pivot[1]);
    rep(vx, lb, ub + 1) {
      rep(vy, lb, ub + 1) {
        PLL x1 = getPair(pivot[0], 0, vx);
        PLL y1 = getPair(pivot[0], 1, vy);
        PLL x2 = getPair(pivot[1], 0, vx);
        PLL y2 = getPair(pivot[1], 1, vy);
        auto tmpres = solve(x1.fi, -x2.fi, x2.se - x1.se, y1.fi, -y2.fi, y2.se - y1.se);
        if (!tmpres.fi) continue;
        auto t12 = tmpres.se;
        simplify(t12.fi);
        simplify(t12.se);
        // cout << t12.fi.fi << " " << t12.fi.se << " " << t12.se.fi << " " << t12.se.se << endl;
        // Get x and y
        // return 0;
        auto x = getValue(x1, t12.fi);
        auto y = getValue(y1, t12.fi);
        if (!x.fi || !y.fi) continue;

        // Get z and vz with 0
        // vz * t1.fi + z * t1.se = t1.fi * isi[idx].se.coord[2] + isi[idx].fi.coord[2] * t1.se;
        LL c1 = getCFromT(pivot[0], 2, t12.fi);
        LL c2 = getCFromT(pivot[1], 2, t12.se);
        // cout << c1 << " " << c2 << endl;
        tmpres = solve(t12.fi.fi, t12.fi.se, c1, t12.se.fi, t12.se.se, c2);
        if (!tmpres.fi) continue;
        auto vzAndZ = tmpres.se;
        // cout << vzAndZ.fi.fi << " " << vzAndZ.se.fi << endl;
        if (abs(vzAndZ.fi.se) != 1) continue;
        if (abs(vzAndZ.se.se) != 1) continue;
        auto z = vzAndZ.se.fi / vzAndZ.se.se;
        auto vz = vzAndZ.fi.fi / vzAndZ.fi.se;
        // return 0;
        // cout << "Here " << endl;
        vector <PLL> goodVal = {{x.se, vx}, {y.se, vy}, {z, vz}};
        bool can = 1;
        // if (can) {
        //   cout << "Here " << endl;
        //   trav(cur, goodVal) cout << cur.fi << " " << cur.se << endl;
        // }
        rep(i, 0, n) {
          bool donePut = 0;
          PLL memo = {0, 0};
          rep(part, 0, 3) {
            auto tmp = getNormal(i, part, goodVal[part].fi, goodVal[part].se);
            if (!donePut) memo = tmp;
            donePut = 1;
            if (tmp.se < 0) can = 0;
            if (memo != tmp && tmp.se) can = 0;
            // if (tmp.fi % tmp.se != 0) can = 0;
          }
          if (!can) break;
          // Check for this equation for the z
        }
        if (can) {
          cout << "Here " << endl;
          rep(i, 0, n) {
            rep(part, 0, 3) {
              auto tmp = getNormal(i, part, goodVal[part].fi, goodVal[part].se);
              cout << (long long) i << " " << (long long) tmp.fi << " " << (long long) tmp.se << endl;
            }
          }
          trav(cur, goodVal) cout << (long long) cur.fi << " " << (long long) cur.se << endl;
          exit(0);
        }
      }
    }
  }
  // int ans = 0;
  // trav(tmp, counter) {
  //   if (tmp.se > ans) {
  //     ans = tmp.se;
  //     cout << "Baru " << tmp.se << endl;
  //     trav(cur, tmp.fi) cout << cur.fi << " " << cur.se << endl;
  //   }
  // }
}