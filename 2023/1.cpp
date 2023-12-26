#include "bits/stdc++.h"
using namespace std;

#define trav(nx, v) for(auto &nx : v)
#define fi first
#define se second
#define pb push_back
typedef long long LL;
LL totans = 0;
int solve(string s){
  pair<char, char> ans = {0, 0};
  trav(ch, s) {
    if(isdigit(ch)) {
      if(!ans.fi) ans.fi = ch;
      ans.se = ch;
    }
  }
  string tmpans = "";
  tmpans.pb(ans.fi);
  tmpans.pb(ans.se);
  totans += stoll(tmpans);
  return 0;
}

int main(){
  string s;
  while(cin >> s) solve(s);
  cout << totans << endl;
}