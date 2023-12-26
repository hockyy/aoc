/*
Author : Hocky Yudhiono
Sen 25 Des 2023 01:08:32
*/

#include "bits/stdc++.h"
using namespace std;

typedef long long LL;
typedef vector<int> vi;
typedef vector<LL> vl;
typedef vector<vi> vvi;
typedef vector<vl> vvl;
typedef pair<int, int> PII;
typedef pair<int, int> pii;
typedef pair<LL, LL> PLL;
typedef pair<LL, LL> pll;
typedef long double ld;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
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

map <string, int> mapIdx;
int ubah(string s) {
  if (mapIdx.count(s)) return mapIdx[s];
  int cursz = sz(mapIdx);
  return mapIdx[s] = cursz;
}

struct UF {
  vi e;
  UF(int n) : e(n + 1, -1) {}
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


pair<int, vi> globalMinCut(vector<vi> mat) {
  pair<int, vi> best = {INT_MAX, {}};
  int n = sz(mat);
  vector<vi> co(n);
  rep(i, 0, n) co[i] = {i};
  rep(ph, 1, n) {
    vi w = mat[0];
    size_t s = 0, t = 0;
    rep(it, 0, n - ph) { // O(V^2) -> O(E log V) with prio. queue
      w[t] = INT_MIN;
      s = t, t = max_element(all(w)) - w.begin();
      rep(i, 0, n) w[i] += mat[t][i];
    }
    best = min(best, {w[t] - mat[t][t], co[t]});
    co[s].insert(co[s].end(), all(co[t]));
    rep(i, 0, n) mat[s][i] += mat[t][i];
    rep(i, 0, n) mat[i][s] = mat[s][i];
    mat[0][t] = INT_MIN;
  }
  return best;
}

int main() {
  string s;
  vector <PII> edges;
  vector <vi> edge(1435);
  while (getline(cin, s)) {
    stringstream ss(s);
    string head;
    ss >> head;
    head.pop_back();
    int u = ubah(head);
    string vv;
    while (ss >> vv) {
      int v = ubah(vv);
      edges.emplace_back(u, v);
      edge[u].pb(v);
      edge[v].pb(u);
    }
  }
  int n = sz(mapIdx);
  cout << n << endl;
  vector <vi> mat(n, vi(n));
  rep(i,0,n) {
    trav(nx, edge[i]) {
      mat[i][nx] = 1;
    }
  }
  cout << sz(edges) << endl;
  auto res = globalMinCut(mat);
  cout << res.fi << ": ans" << endl;
  cout << sz(res.se) * (n - sz(res.se)) << endl;
  // trav(cur, res.se) cout << cur << endl;
}