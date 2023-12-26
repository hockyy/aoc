/*
Author : Hocky Yudhiono
Sat Dec 23 20:42:40 2023

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

#include <bits/stdc++.h>
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
#include <chrono>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
struct custom_hash {
  static uint64_t splitmix64(uint64_t x) {
    x += 0x9e3779b97f4a7c15;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    return x ^ (x >> 31);
  }

  size_t operator()(uint64_t x) const {
    static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
    return splitmix64(x + FIXED_RANDOM);
  }
};
vector <PII> edge[61];
int curval = 0;
int root = 0;
int target = 1;
int ans = 0;

vector <int> path;

void dfs(int pos, LL mask) {
  // if(memo[pos][mask]) return memo[60][mask];
  if (pos == target) {
    if(ans < curval){
      ans = curval;
      cout << ans << endl;
    }
  }
  trav(nx, edge[pos]) {
    if (mask & (1LL << nx.fi)) continue;
    int curPlus = nx.se + 3;
    curval += curPlus;
    dfs(nx.fi, mask | (1LL << nx.fi));
    curval -= curPlus;
  }
  path.pop_back();
  // memo[pos][mask] = 
}

int main() {
  int n; cin >> n;
  int m; cin >> m;
  for (int i = 1; i <= m; i++) {
    int u, v; cin >> u >> v;
    u--;
    v--;
    int c; cin >> c;
    edge[u].emplace_back(v, c);
    edge[v].emplace_back(u, c);
  }
  dfs(0, 0);
  cout << ans - 4 << endl;
  cout << "Done " << endl;
  swap(root, target);
  ans = 0;
  dfs(1, 0);
  cout << ans - 4 << endl;

}