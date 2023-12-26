/*
Author : Hocky Yudhiono
Mon Dec 11 22:25:07 2023

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

#include "bits/stdc++.h"
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

const double EPS = 1e-9;
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
const int dx[8] = {0,0,1,-1,1,-1,1,-1};
const int dy[8] = {1,-1,0,0,1,-1,-1,1};
const char dch[4] = {'R','L','D','U'};

// Do (dir + 2)%4 to get reverse direction
// const int dx[8] = {-1,0,1,0,-1,1,1,-1};
// const int dy[8] = {0,1,0,-1,1,1,-1,-1};
// const char dch[4] = {'U','R','D','L'};
const double PI = 3.141592653589793;

inline void fasterios(){
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);
}

// Remember to undefine if the problem is interactive
#define endl '\n'

// In multi dimensional vector, avoid using
// vector.resize() to reset between each testcases
// use assign instead

vector <string> isi;
vector <string> newIsi;

void go(int m){
  newIsi.pb("");
  rep(i,0,m)
  newIsi.back().pb('.');
}

int main(){
  string s;
  while(cin >> s) {
    if(s == "") break;
    isi.pb(s);
  }
  int n = sz(isi);
  int m = sz(isi[0]);
  vector <LL> okRows;
  vector <LL> okCols;
  rep(i,0,n) {
    bool coolRow = 1;
    rep(j,0,m){
      if(isi[i][j] == '#') coolRow = 0;
    }
    if(coolRow) okRows.pb(i);
  } 
  rep(j,0,m){
    bool coolColumn = 1;
    rep(i,0,n){
      if(isi[i][j] == '#') coolColumn = 0;
    }
    if(coolColumn) okCols.pb(j);
  }
  vector <PLL> poss;
  rep(i,0,n){
    rep(j,0,m){ 
      cout << isi[i][j];
      if(isi[i][j] == '#') {
        poss.emplace_back(i, j);
      }
    }
    cout << endl;
  }
  const LL kLim = 1000000 - 1;
  LL ans = 0;
  trav(a, poss){
    trav(b, poss){

      ans += abs(a.fi - b.fi) + abs(a.se - b.se);
      {
        LL kiri = a.fi;
        LL kanan = b.fi;
        if(kiri > kanan) swap(kiri, kanan);
        ans += kLim * (upper_bound(all(okRows), kanan)  - upper_bound(all(okRows), kiri));
      }
      {
        LL kiri = a.se;
        LL kanan = b.se;
        if(kiri > kanan) swap(kiri, kanan);
        ans += kLim * (upper_bound(all(okCols), kanan)  - upper_bound(all(okCols), kiri));
      }
    }
  }
  cout << ans / 2 << endl;
}