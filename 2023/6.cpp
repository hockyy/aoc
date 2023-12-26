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
vector <LL> getNumbers(){ 
  string s; getline(cin, s);
  stringstream ss(s);
  LL dummyLL;
  vector <LL> ret;
  while(ss >> dummyLL){
    ret.pb(dummyLL);
  }
  return ret;
}

int main(){
  string s; cin >> s;
  auto speeds = getNumbers();
  string t; cin >> t;
  auto distance = getNumbers();
  int n = sz(speeds);
  LL ans = 1;
  rep(i,0,n){
    LL curans = 0;
    rep(j,0,speeds[i]){
      // cout << j * (speeds[i] - j) << " " << j << " " << distance[i] << endl;
      if(j * (speeds[i] - j) > distance[i]) {
        curans++;
      }
    }
    cout << i << " " << speeds[i] << " " << distance[i] << " " << curans << endl;
    ans *= curans;
  }
  cout << ans << endl;
}