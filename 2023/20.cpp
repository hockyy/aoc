#include "bits/stdc++.h"
using namespace std;

#define rep(i,a,b) for(LL i = a;i < b;i++)
#define sz(v) (LL) v.size()
#define all(v) begin(v), end(v)
#define trav(nx, v) for(auto &nx : v)
#define pb push_back
#define fi first
#define se second
typedef long long LL;
typedef pair<LL, LL> PLL;
#define int long long

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

void strip(string &s, string rm) {
  trav(ch, rm) {
    while (s.back() == ch) s.pop_back();
  }
  reverse(all(s));
  trav(ch, rm) {
    while (s.back() == ch) s.pop_back();
  }
  reverse(all(s));
}

map <string, LL> mapIdx;
string revMap[1000005];

LL ubah(string pos) {
  if (mapIdx.count(pos)) return mapIdx[pos];
  LL cursz = sz(mapIdx);
  revMap[cursz] = pos;
  return mapIdx[pos] = cursz;
}



struct Module {
  LL type;
  LL condition;
  LL idx;
  vector <LL> go;
  LL rememberCount;
  map <LL, LL> remember;
  Module() {}
  Module(string u, const string &vs) {
    if (u != "broadcaster") {
      type = u[0] == '%' ? 1 : 2;
      u = u.substr(1);
    } else {
      type = 0;
    }
    idx = ubah(u);
    go.resize(0);
    condition = 0;
    auto split2 = split(vs, ',');
    trav(v, split2) {
      strip(v, " ");
      LL vIdx = ubah(v);
      go.pb(vIdx);
      // cout << revMap[idx] << " " << revMap[vIdx] << endl;
    }
    // reverse(all(go));
    rememberCount = 0;
    condition = 0;
  }
};

LL loIdx = 0;
LL hiIdx = 0;

struct BFSNode {
  LL fi, se;
};

typedef array<LL, 2> IP;

vector <Module> isi(100000);
int32_t main() {
  string s;
  auto root = ubah("broadcaster");
  while (getline(cin, s)) {
    if (s == "") break;
    auto split1 = split(s, '>');
    split1[0].pop_back();
    split1[0].pop_back();
    Module curModule(split1[0], split1[1]);
    isi[curModule.idx] = curModule;
  }
  queue <PLL> antri;
  array<LL, 2> tot = {0, 0};
  LL n = sz(mapIdx);
  // trav(cur, mapIdx) cout << cur.fi << " " << cur.se << endl;
  rep(i, 0, n) {
    trav(nx, isi[i].go) {
      // cout << revMap[i] << " " << revMap[nx] << endl;
      isi[nx].remember[i] = 0;
    }
  }
  const LL kButtonPress = 20000;
  rep(iter, 0, kButtonPress) {
    if (iter % 1000000 == 0) cout << fixed << setprecision(3) << (double) iter * 100 / kButtonPress << "%" << endl;
    while (!antri.empty()) antri.pop();
    antri.push({root, 0});
    array<LL, 2> tmptot = {0, 0};
    while (!antri.empty()) {
      LL pos = antri.front().fi;
      LL pulse = antri.front().se;
      // cout << revMap[sender] << " sending " << pulse << " to " << revMap[pos] << endl;
      tmptot[pulse]++;

      antri.pop();
      auto &curNode = isi[pos];

      // cout << iter << ": " << tmptot[0] << "  " << tmptot[1] << endl;
      auto asu = ubah("lb");
      // cout << "Iter: " << endl;
      if (pos == asu) {
        trav(cur, isi[asu].remember) {
          if (cur.se) {
            cout << iter << " " << revMap[cur.fi] << " " << cur.se << endl;
          }
        }
      }

      LL whatToSend = 1;
      if (curNode.type == 2) {
        whatToSend = curNode.rememberCount != sz(curNode.remember);
      } else if (curNode.type == 1) {
        whatToSend = -1;
        if (!pulse) {
          curNode.condition = !curNode.condition;
          whatToSend = curNode.condition;
        }
      } else {
        whatToSend = pulse;
      }

      // Relax
      if (whatToSend != -1) {
        trav(nx, curNode.go) {
          if (isi[nx].type == 2) {
            if (isi[nx].remember[pos] != whatToSend) {
              if (whatToSend == 0) isi[nx].rememberCount--;
              else isi[nx].rememberCount++;
            }
            isi[nx].remember[pos] = whatToSend;
          }
          antri.push({nx, whatToSend});
        }
      }
    }
    tot[0] += tmptot[0];
    tot[1] += tmptot[1];
    // cout << iter << ": " << tmptot[0] << "  " << tmptot[1] << endl;
    auto asu = ubah("lb");
    // cout << "Iter: " << endl;
    trav(cur, isi[asu].remember) {
      trav(sumber, isi[cur.fi].remember) {
        if (!sumber.se) {
          cout << iter << " " << revMap[cur.fi] << " " << cur.se << " " << sumber.fi << " " << sumber.se << endl;
        }
      }
    }
  }
  cout << tot[0] << " " << tot[1] << endl;
  cout << tot[0] * tot[1] << endl;

}