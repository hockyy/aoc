#include "bits/stdc++.h"
using namespace std;

#define rep(i,a,b) for(int i = a;i < b;i++)
#define trav(nx, v) for(auto &nx : v)
#define all(v) begin(v), end(v)
#define sz(v) (int) v.size()
#define fi first
#define se second
#define endl '\n'
#define pb push_back
typedef long long LL;

typedef array <LL, 3> Blocks;
struct Cube {
  Blocks fi, se;
  int idx;
  Cube (const Blocks &a, const Blocks &b, int _idx){
    fi = a; se = b; idx = _idx;
  }
};

const int kHeight = 100000;
int kotak[15][15][100005];
vector <Cube> isi;
vector <int> indegreeCount;
vector <int> edge[100005];
vector <int> induced;
vector <int> oriInduced;
vector <int> relaxed;
vector <int> paksa;
LL curans = 0;
void dfs(LL pos){
  relaxed[pos] = 1;
  trav(nx, edge[pos]){
    induced[nx]++;
    if(!relaxed[nx]) dfs(nx);
  }
  return;
}
int root;
void color(LL pos){
  bool isDestroyed = 1;
  if(root == pos) isDestroyed = 1;
  else {
    if(oriInduced[pos] == indegreeCount[pos]) {
      // Cek apakah dia dapat aturan
      if(!paksa[pos]) isDestroyed = 1;
      else isDestroyed = 0;
    } else isDestroyed = 0;
  }
  if(root != pos && isDestroyed) curans++;
  trav(nx, edge[pos]){
    if(!isDestroyed) paksa[nx] = 1;
    induced[nx]--;
    if(induced[nx] == 0) color(nx);
  }
  return;
}
int main(){
  string s;
  int idx = 1;
  while(getline(cin, s)){
    if(s == "") break;
    stringstream ss1(s);
    Blocks st, ed;
    char delim;
    ss1 >> st[0];
    rep(i,1,3){
      ss1 >> delim;
      ss1 >> st[i];
    }
    rep(i,0,3){
      ss1 >> delim;
      ss1 >> ed[i];
    }
    isi.emplace_back(st, ed, idx);
    idx++;
  }
  sort(all(isi), [](const Cube &a, const Cube &b){
    return min(a.se[2], a.fi[2]) < min(b.se[2], b.fi[2]);
  });
  // simulate drop
  vector <set<int>> deps(sz(isi) + 3);
  rep(i,0,sz(isi)){
    int shift = 1;
    auto &curCube = isi[i];
    for(;;shift++){
      // Check shift
      bool can = 1;

      rep(x,curCube.fi[0], curCube.se[0] + 1){
        rep(y,curCube.fi[1], curCube.se[1] + 1){
          rep(z,curCube.fi[2], curCube.se[2] + 1){
            int curZ = z - shift + 1;
            if(curZ < 0 || kotak[x][y][curZ]) {
              can = 0;
            }
          }
        }
      }
      if(!can) break;
    }
    shift--;
    rep(x,curCube.fi[0], curCube.se[0] + 1){
      rep(y,curCube.fi[1], curCube.se[1] + 1){
        rep(z,curCube.fi[2], curCube.se[2] + 1){
          int curZ = z - shift + 1;
          kotak[x][y][curZ] = curCube.idx;
          if(curZ - 1 >= 0 && z == min(curCube.fi[2], curCube.se[2])){
            if(kotak[x][y][curZ - 1]){
              deps[curCube.idx].insert(kotak[x][y][curZ - 1]);
            }
          }
        }
      }
    }
  }
  indegreeCount.resize(sz(isi) + 5);
  rep(i,0,sz(isi)){
    auto &curCube = isi[i];
    cout << "Current " << curCube.idx << ": " << endl;
    trav(tmp, deps[curCube.idx]){
      cout << tmp << endl;
      edge[tmp].pb(curCube.idx);
      indegreeCount[curCube.idx]++;
    }
  }
  LL ans = 0;
  rep(i,0,sz(isi)){
    auto &curCube = isi[i];
    root = curCube.idx;
    curans = 0;
    induced.assign(sz(indegreeCount), 0);
    relaxed.assign(sz(indegreeCount), 0);
    dfs(curCube.idx);
    oriInduced = induced;
    paksa.assign(sz(indegreeCount), 0);
    color(curCube.idx);
    cout << curCube.idx << " " << curans << endl;
    ans += curans;
  }
  cout << ans << endl;
}