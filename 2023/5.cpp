#include "bits/stdc++.h"
using namespace std;

#define rep(i,a,b) for(LL i = a;i < b;i++)
#define trav(nx, v) for(auto &nx : v)
#define sz(v) (int) v.size()
#define all(a) begin(a), end(a)
#define pb push_back
#define fi first
#define se second
typedef long long LL;

string getFineLine() {
  string s;
  while (getline(cin, s)) {
    if (s == "") continue;
    return s;
  }
  return "";
}

vector <string> split(const string &s, const char delim) {
  string tmp = "";
  vector <string> ret;
  trav(ch, s) {
    if (ch == delim) {
      ret.pb(tmp);
      tmp = "";
    } else tmp.pb(ch);
  }
  ret.pb(tmp);
  return ret;
}
typedef pair<LL, LL> PLL;
string dummyS;
char dummyC;
LL dummyI;

int main() {
  string seedsString = getFineLine();
  stringstream ssSeeds(seedsString);
  ssSeeds >> dummyS;
  vector <PLL> seeds;
  while (ssSeeds >> dummyI) {
    LL len;
    ssSeeds >> len;
    seeds.emplace_back(dummyI, dummyI + len - 1);
  }
  while (1) {
    cout << "fining " << endl;
    string mapString = getFineLine();
    if (mapString == "") break;
    cerr << mapString << endl;
    auto splittedMap = split(mapString, ' ')[0];
    auto sAndT = split(splittedMap, '-');
    auto s = sAndT[0];
    auto t = sAndT[1];
    vector <PLL> nextMap;
    vector <PLL> ranges;
    while (getline(cin, dummyS)) {
      if (dummyS == "") break;
      stringstream currentMap(dummyS);
      LL a, b, c;
      currentMap >> a;
      currentMap >> b;
      currentMap >> c;
      cerr << a << " " << b << " " << c << endl;
      LL kiri = b;
      LL kanan = b + c - 1;
      LL delta = a - b;
      ranges.emplace_back(kiri, kanan);
      rep(i, 0, sz(seeds)) {
        auto &cur = seeds[i];
        LL l = max(kiri, cur.fi);
        LL r = min(kanan, cur.se);
        if (l > r) continue;
        PLL newRange = {l + delta, r + delta};
        nextMap.pb(newRange);
      }
    }
    sort(all(ranges));
    vector <PLL> inverseRange;
    inverseRange.emplace_back(LLONG_MIN, ranges[0].fi - 1);
    rep(i, 0, sz(ranges) - 1) {
      PLL tmp = {ranges[i].se + 1, ranges[i + 1].fi - 1};
      if (tmp.fi <= tmp.se) inverseRange.pb(tmp);
    }
    inverseRange.emplace_back(ranges.back().se + 1, LLONG_MAX);
    trav(cur, seeds) {
      trav(tmp, inverseRange) {
        auto kiri = tmp.fi;
        auto kanan = tmp.se;
        LL l = max(kiri, cur.fi);
        LL r = min(kanan, cur.se);
        if (l > r) continue;
        PLL newRange = {l, r};
        nextMap.pb(newRange);
      }
    }
    swap(nextMap, seeds);
  }
  LL ans = LLONG_MAX;
  trav(cur, seeds) ans = min(ans, cur.fi);
  // ans = *min_element(all(seeds));
  cout << ans << endl;
}