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


int main(){
  string s;
  LL ans = 0;
  while(getline(cin, s)) {
    cout << s << endl;
    stringstream in(s);
    vector <vector <LL>> pattern(1);
    LL dummy;
    while(in >> dummy){
      pattern[0].pb(dummy);
    }
    reverse(all(pattern[0]));
    int cnt = 0;
    while(1){
      cnt++;
      vector <LL> tmp;
      rep(i,1,sz(pattern.back())) {
        tmp.pb(pattern.back()[i] - pattern.back()[i - 1]);
      }
      auto copas = tmp;
      sort(all(copas));
      if(sz(copas) == 0) break;
      if(copas.front() == copas.back() && copas.front() == 0) break;
      pattern.pb(tmp);
    }
    for(int i = sz(pattern) - 1;i >= 1;i--){
      pattern[i - 1].pb(pattern[i - 1].back() + pattern[i].back());
    }
    ans += pattern[0].back();
  }
  cout << ans << endl;

}