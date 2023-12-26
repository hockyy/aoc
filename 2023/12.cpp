#include "bits/stdc++.h"
using namespace std;
#define pb push_back
#define rep(i,a,b) for(int i = a;i < b;i++)
#define sz(v) (int) v.size()
#define trav(nx, v) for(auto &nx : v)
#define all(v) begin(v), end(v)
typedef long long LL;

string plain;
const int kLim = 1005;
vector <LL> crumbs;
LL memo[kLim + 5][kLim + 5];

LL dp(LL pos, int crumb){
  LL &ret = memo[pos][crumb];
  if(~ret) return ret;
  if(pos >= sz(plain)) {
    if(crumb == sz(crumbs)) return 1;
    return 0;
  }
  ret = 0;
  if(plain[pos] == '.' || plain[pos] == '?') ret += dp(pos + 1, crumb);
  // Take
  cout << pos << " " << crumb << endl;
  if(crumb < sz(crumbs)){
    cout << "Here " << crumb << " " << crumbs[crumb] << endl;
    int kiri = pos;
    int kanan = pos + crumbs[crumb] - 1;
    if(kanan < sz(plain)) {
      bool allSafe = 1;
      rep(i,kiri, kanan + 1) {
        if(plain[i] == '.') {
          allSafe = 0;
          break;
        }
      }
      cout << kiri << " " << kanan << " " << allSafe << endl;
      if(allSafe){
        if(kanan + 1 < sz(plain)) {
          if(plain[kanan + 1] != '#'){
            ret += dp(kanan + 2, crumb + 1);
          }
        } else {
          ret += dp(kanan + 1, crumb + 1);
        }
      }
    }
  }
  return ret;
}

vector <string> split(string s, const char &delim){
  vector <string> ret;
  string acc = "";

  trav(ch, s){
    if(ch == delim){
      ret.pb(acc);
      acc = "";
    } else acc.pb(ch);
  }
  ret.pb(acc);
  return ret;

}

int main(){
  LL ans = 0;
  while(cin >> plain){
    string ori = plain;
    rep(i,0,4) {
      plain.pb('?');
      plain += ori;
    }
    memset(memo,-1,sizeof(memo));
    string cnt; cin >> cnt;
    ori = cnt;
    rep(i,0,4) {
      cnt.pb(',');
      cnt += ori;
    }
    auto splitted  = split(cnt, ',');
    crumbs.clear();
    trav(cur, splitted){
      crumbs.pb(stoll(cur));
      // cout << crumbs.back() << " ";
    }
    // cout << endl;
    // cout << plain << " " << sz(crumbs) << endl;
    ans += dp(0, 0);
    cout << dp(0,0) << endl;
  }
  cout << ans << endl;
}