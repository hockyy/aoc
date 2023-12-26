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

typedef pair<string, LL> PSL;

int getType(string s){
  sort(all(s));
  if(s[0] == s[4]) return 6;
  if(s[0] == s[3] || s[1] == s[4]) return 5;
  if(s[0] == s[1] && s[2] == s[4]) return 4;
  if(s[0] == s[2] && s[3] == s[4]) return 4;
  if(s[0] == s[2] || s[1] == s[3] || s[2] == s[4]) return 3;
  if(s[0] == s[1] && s[2] == s[3]) return 2;
  if(s[0] == s[1] && s[3] == s[4]) return 2;
  if(s[1] == s[2] && s[3] == s[4]) return 2;
  if(s[0] == s[1] || s[1] == s[2] || s[2] == s[3] || s[3] == s[4]) return 1;
  return 0;
}

int toInt(char s){
  if(s == 'T') return 10;
  if(s == 'J') return 0;
  if(s == 'Q') return 12;
  if(s == 'K') return 13;
  if(s == 'A') return 14;
  return s - '0';
}

string tryLetter = "23456789TQKA";

string target;
int dfs(int pos){
  if(pos == 5) {
    return getType(target);
  }
  int curans = 0;
  if(target[pos] != 'J') return dfs(pos + 1);
  trav(ch, tryLetter){
    target[pos] = ch;
    curans = max(curans, dfs(pos + 1));
  }
  target[pos] = 'J';
  return curans;

}

bool compare(const string &s, const string &t){
  rep(i,0,5) {
    if(s[i] != t[i]) return toInt(s[i]) < toInt(t[i]);
  }
  return 0;
}

int main(){
  string s; 
  vector <pair<PSL, LL>> cards;
  while(getline(cin, s)) {
    stringstream ss(s);
    string card;
    ss >> card;
    LL bid; ss >> bid;
    target = card;
    cards.emplace_back(make_pair(card, bid), dfs(0));
  }
  LL ans = 0;
  sort(all(cards), [&](const pair<PSL, LL> &a, const pair<PSL, LL> &b)  {
    if(a.se != b.se) return a.se < b.se;
    return compare(a.fi.fi, b.fi.fi);
  });
  rep(i,0,sz(cards)){
    ans += 1LL * (i + 1) * cards[i].fi.se;
  }
  trav(cur, cards) cout << cur.fi.fi << " " << cur.fi.se << endl;
  cout << ans << endl;
}