#include "bits/stdc++.h"
using namespace std;

typedef long long LL;
#define fi first
#define se second
#define pb push_back
#define trav(nx, v) for(auto &nx : v)

vector<string> split(const string &tmp, char delim) {
  vector<string> ret = {""};
  trav(ch, tmp) {
    if (ch == delim) ret.pb("");
    else ret.back().pb(ch);
  }
  return ret;
}

int main() {
  LL ans = 0;
  string s; cin >> s;
  const int kLIM = 10000000;
  vector <LL> preCard(kLIM, 0);
  int idx = 0;
  while (getline(cin, s)) {
    if(s == "") continue;
    if(idx - 1 >= 0) preCard[idx] += preCard[idx - 1];
    ans += preCard[idx] + 1;
    // cout << "Here " << preCard[idx] << endl;
    set <LL> winningNumbers;
    auto id = split(s, ':');
    stringstream gameId(id[0]);
    auto card = split(id[1], '|');
    stringstream card1(card[0]);
    stringstream card2(card[1]);
    int c1, c2;
    while(card1 >> c1){
      winningNumbers.insert(c1);
    }
    LL curans = 0;
    while(card2 >> c2) {
      if(winningNumbers.count(c2)) curans++;
    }
    // cout << curans << endl;
    preCard[idx + 1] += preCard[idx] + 1;
    preCard[idx + curans + 1] -= preCard[idx] + 1;
    idx++;
  }
  cout << ans << endl;
}