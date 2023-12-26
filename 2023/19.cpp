#include "iostream"
#include "map"
#include "cassert"
#include "vector"
#include "iomanip"
#include "algorithm"
#include "array"
using namespace std;

#define rep(i,a,b) for(int i = a;i < b;i++)
#define sz(v) (int) v.size()
#define all(v) begin(v), end(v)
#define trav(nx, v) for(auto &nx : v)
#define pb push_back
#define fi first
#define se second
typedef long long LL;
typedef pair<LL, LL> PLL;

vector <string> split(string s, const char delim) {
  vector <string> res;
  string ret = "";
  trav(ch, s) {
    if (ch == delim) {
      res.pb(ret);
      ret = "";
    } else ret.pb(ch);
  }
  res.pb(ret);
  return res;
}

map <char, int> charMapper;
string xmas = "xmas";

vector <LL> globalDecisions[4];

struct Sequence {
  Sequence (string s) {
    var = charMapper[s[0]];
    isGT = s[1] == '>';
    val = stoll(s.substr(2));
    if (isGT) globalDecisions[var].pb(val + 1);
    else globalDecisions[var].pb(val);
  }
  Sequence() {
    var = -1;
  }
  int var;
  bool isGT;
  LL val;
};
typedef pair<Sequence, LL> ComVal;
typedef array<LL, 4> Nilai;


struct Node {
  vector <ComVal> comparisons;
  LL test(Nilai now) {
    trav(cur, comparisons) {
      if (cur.fi.var == -1) return cur.se;
      if (!cur.fi.isGT) {
        // <
        if (now[cur.fi.var] < cur.fi.val) {
          return cur.se;
        }
      } else {
        if (now[cur.fi.var] > cur.fi.val) {
          return cur.se;
        }        // >
      }
    }
    assert(0);
    return -1;
  }
};

map <string, int> mapIdx;
vector <Node> processor;

int ubah(string pos) {
  if (mapIdx.count(pos)) return mapIdx[pos];
  int cursz = sz(mapIdx);
  return mapIdx[pos] = cursz;
}

int main() {
  processor.resize(1000);
  rep(i, 0, 4) charMapper[xmas[i]] = i;
  string s;
  while (getline(cin, s)) {
    if (s == "") break;
    auto split1 =  split(s, '{');
    int nodeIdx = ubah(split1[0]);
    split1[1].pop_back();
    auto split2 = split(split1[1], ',');
    trav(cur, split2) {
      auto split3 = split(cur, ':');
      cout << cur << endl;
      Sequence * curSeq;
      LL tujuan;
      string tujuanStr = split3[0];
      if (split3.size() == 1) {
        curSeq = new Sequence();
      } else {
        curSeq = new Sequence(split3[0]);
        tujuanStr = split3[1];
      }
      if (tujuanStr == "A") tujuan = -1;
      else if (tujuanStr == "R") tujuan = -2;
      else tujuan = ubah(tujuanStr);
      processor[nodeIdx].comparisons.emplace_back(*curSeq, tujuan);
    }
  }
  LL ans = 0;
  LL finish = 1;
  LL root = ubah("in");
  rep(i, 0, 4) {
    globalDecisions[i].pb(1);
    sort(all(globalDecisions[i]));
    globalDecisions[i].erase(unique(all(globalDecisions[i])), globalDecisions[i].end());
    while (globalDecisions[i].back() > 4000) globalDecisions[i].pop_back();
    reverse(all(globalDecisions[i]));
    while (globalDecisions[i].back() < 1) globalDecisions[i].pop_back();
    reverse(all(globalDecisions[i]));
    globalDecisions[i].pb(4001);
    cout << sz(globalDecisions[i]) << " " << xmas[i] << endl;
    finish *= sz(globalDecisions[i]) - 1;
  }
  Nilai now;
  LL preval = 1;
  LL idx = 0;
  cout << finish << endl;
  rep(X, 1, sz(globalDecisions[0])) {
    now[0] = globalDecisions[0][X - 1];
    preval *= globalDecisions[0][X] - globalDecisions[0][X - 1];
    rep(M, 1, sz(globalDecisions[1])) {
      preval *= globalDecisions[1][M] - globalDecisions[1][M - 1];
      now[1] = globalDecisions[1][M - 1];
      rep(A, 1, sz(globalDecisions[2])) {
        preval *= globalDecisions[2][A] - globalDecisions[2][A - 1];
        now[2] = globalDecisions[2][A - 1];
        rep(S, 1, sz(globalDecisions[3])) {
          preval *= globalDecisions[3][S] - globalDecisions[3][S - 1];
          now[3] = globalDecisions[3][S - 1];
          int res = root;
          do {
            res = processor[res].test(now);
          } while (res >= 0);
          if (res == -1) ans += preval;
          preval /= globalDecisions[3][S] - globalDecisions[3][S - 1];
          idx += 1;
          if(idx % 10000000 == 0){
            cout << fixed << setprecision(8) << (double)(idx * 100) / finish << "%" << endl;
          }
        }
        preval /= globalDecisions[2][A] - globalDecisions[2][A - 1];
      }
      preval /= globalDecisions[1][M] - globalDecisions[1][M - 1];
    }
    preval /= globalDecisions[0][X] - globalDecisions[0][X - 1];
  }
  cout << ans << endl;
}