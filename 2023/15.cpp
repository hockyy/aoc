#include "bits/stdc++.h"
using namespace std;

#define trav(nx, v) for(auto &nx : v)
#define rep(i,a,b) for(int i = a;i < b;i++)
#define sz(v) (int) v.size()
typedef long long LL;
#define pb push_back

const LL kBase = 17;
const LL kMod = 256;

LL hashString(const string &s){
  LL ret = 0;
  trav(ch, s){
    ret += ch;
    ret = ret * 17 % kMod;
  } 
  return ret;
}

vector <string> split(string s, const char delim){
  vector <string> res;
  string ret = "";
  trav(ch, s){
    if(ch == delim){
      res.pb(ret);
      ret = "";
    } else ret.pb(ch);
  }
  res.pb(ret);
  return res;
}

#define fi first
#define se second
typedef pair<string, LL> PSL;
vector <PSL> boxes[kMod];

int main(){
  string s;
  getline(cin, s);
  auto res = split(s, ',');
  LL ans = 0;
  trav(tmp, res){
    if(tmp.back() == '-'){
      tmp.pop_back();
      LL currentHash = hashString(tmp);
      int idx = 0;
      trav(slot, boxes[currentHash]) {
        if(slot.fi == tmp){
          boxes[currentHash].erase(begin(boxes[currentHash]) + idx);
          break;
        }
        idx++;
      }
    } else {
      LL focal = tmp.back() - '0';
      tmp.pop_back();
      tmp.pop_back();
      LL currentHash = hashString(tmp);
      int idx = 0;
      bool put = 0;
      trav(slot, boxes[currentHash]) {
        if(slot.fi == tmp){
          slot.se = focal;
          put = 1;
          break;
        }
        idx++;
      }
      if(!put) {
        boxes[currentHash].emplace_back(tmp, focal);
      }
    }
  }
  rep(i,0,kMod){
    cout << "Box " << i << endl;
    rep(j,0,sz(boxes[i])){
      ans += 1LL * (j + 1) * (i + 1) * boxes[i][j].se;
    }
    trav(cur, boxes[i]){
      cout << cur.fi << " " << cur.se << endl;
    }
  }
  cout << ans << endl;
}