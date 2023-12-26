#include "bits/stdc++.h"
using namespace std;

#define rep(i,a,b) for(LL i = a;i < b;i++)
#define trav(nx, v) for(auto &nx : v)
#define sz(v) (LL) v.size()
#define all(v) begin(v), end(v)
#define fi first
#define se second
#define pb push_back
#define int long long 
typedef long long LL;

string fine(){
  string tmp = "";
  while(getline(cin, tmp)) {
    if(tmp == "") continue;
    else break;
  }
  return tmp;
}

vector <string> split(const string &s, const char delim){
  string tmp = "";
  vector <string> ret;
  trav(ch, s){
    if(ch == delim){
      ret.pb(tmp);
      tmp = "";
    } else {
      tmp.pb(ch);
    }
  }
  ret.pb(tmp);
  return ret;
}

void strip(string &s, const char delim = ' '){
  while(s.back() == delim) s.pop_back();
  reverse(all(s));
  while(s.back() == delim) s.pop_back();
  reverse(all(s));
}

map <string, int> table;
string revMap[100005];
typedef pair<LL, LL> PLL;
PLL nx[100000];

int getNode(string &s){
  if(table.count(s)) return table[s];
  int idx = sz(table);
  revMap[idx] = s;
  return table[s] = idx;
}

typedef long long ll;


ll euclid(ll a, ll b, ll &x, ll &y) {
    if (b) { ll d = euclid(b, a % b, y, x);
        return y -= a/b * x, d; }
    return x = 1, y = 0, a;
}

ll crt(ll a, ll m, ll b, ll n) {
    if (n > m) swap(a, b), swap(m, n);
    ll x, y, g = euclid(m, n, x, y);
    assert((a - b) % g == 0); // else no solution
    x = (b - a) % n * x % n / g * m + a;
    return x < 0 ? x + m*n/g : x;
}

LL getInverse(LL n, LL p){
    assert(__gcd(n,p) == 1);
    LL x,y; euclid(n,p,x,y);
    return (x%p+p)%p;
}


int32_t main(){
  string dirs; cin >> dirs;
  while(1){
    string now = fine();
    if(now == "") break;
    // cout << now << endl;
    auto splitted = split(now, '=');
    string source = splitted[0];
    strip(source);
    string targetPair = splitted[1];
    strip(targetPair);
    strip(targetPair, '(');
    strip(targetPair, ')');
    splitted = split(targetPair, ',');
    string kiri = splitted[0];
    string kanan = splitted[1];
    // cout << source << " " << kiri << " " << kanan << endl;
    strip(kiri);
    strip(kanan);
    int u = getNode(source);
    int a = getNode(kiri);
    int b = getNode(kanan);
    // cout << u << " " << a << " " << b << endl;
    nx[u] = {a, b};
  }
  vector <LL> starts;
  trav(cur, table){
    if(cur.fi.back() == 'A') starts.pb(cur.se);
  }
  // trav(cur, starts) cout << cur << endl;
  LL ans = 0;
  int idx = 0;
  vector <LL> last(sz(starts));
  int peler = 0;
  const int kStop = 10000000;
  while(peler < kStop){
    peler++;
    ans++;
    char cur = dirs[idx%sz(dirs)];
    trav(pos, starts){
      if(cur == 'L') pos = nx[pos].fi;
      else pos = nx[pos].se;
    }
    idx++;
    // cout << ans << endl;
  }
  vector <PLL> retarded;
  rep(i,0,sz(starts)){
    int pos = starts[i];
    // cout << pos << " " << revMap[pos] << endl;
    PLL tmpRet = {0, 0};
    LL tmpIdx = idx;
    bool reached = 0;
    int ori2 = tmpIdx;
    int ori = pos;
    do {
      if(revMap[pos].back() == 'Z') reached = 1;
      if(!reached) tmpRet.fi++;
      tmpRet.se++;
      char cur = dirs[tmpIdx%sz(dirs)];
      if(cur == 'L') pos = nx[pos].fi;
      else pos = nx[pos].se;
      tmpIdx++;
    } while(pos != ori || tmpIdx%sz(dirs) != ori2%sz(dirs));
    retarded.pb(tmpRet);
    // cout << tmpRet.se << endl;
  }
  // trav(cur, retarded) cur.se /= 307;
  // trav(cur, retarded) cur.fi %= cur.se;
  // retarded.clear();
  // retarded.emplace_back(0, 2);
  // retarded.emplace_back(2, 6);
  // trav(cur, retarded) cout << cur.fi << " " << cur.se << endl;

  PLL res = retarded[0];
  // cout << res.fi << " " << res.se << endl;
  rep(i,1,sz(retarded)){
    PLL nxRes;
    nxRes.se = retarded[i].se * res.se / __gcd(res.se, retarded[i].se);
    cout << retarded[i].fi << " " << retarded[i].se << " " << res.fi << " " << res.se << endl;
    nxRes.fi = crt(retarded[i].fi, retarded[i].se, res.fi, res.se);
    res = nxRes;
  }
  // 6665 16271
  // 17717 22411
  // 13726 14429
  // 218 18727
  // 4823 21797
  // 16489 18113
  cout << res.fi << " " << res.se << endl;
  cout << res.fi + kStop << endl;
}