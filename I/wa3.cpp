/**
 * It's a typical maximum flow problem. Add the edge(u, v) with capacity 1
 * if hero u can kill monster v. For all potions and hero, we add an edge with
 * capacity 1 between them. The hero himself have the capacity 2.
 *
 * Connect source to all heroes and potions with capacity 1.
 * Connect all monster to the sink with capacity 1.
 */
#include<bits/stdc++.h>
using namespace std;

#define PB push_back

struct Dinic{
  static const int MXN = 2005;
  struct Edge{ int v,f,re; };
  int n,s,t,level[MXN];
  vector<Edge> E[MXN];
  void init(int _n, int _s, int _t){
    n = _n; s = _s; t = _t;
    for (int i=0; i<n; i++) E[i].clear();
  }
  void add_edge(int u, int v, int f){
    E[u].PB({v,f,(int) (E[v].size())});
    E[v].PB({u,0,(int) (E[u].size())-1});
  }
  bool BFS(){
    for (int i=0; i<n; i++) level[i] = -1;
    queue<int> que;
    que.push(s);
    level[s] = 0;
    while (!que.empty()){
      int u = que.front(); que.pop();
      for (auto it : E[u]){
        if (it.f > 0 && level[it.v] == -1){
          level[it.v] = level[u]+1;
          que.push(it.v);
        }
      }
    }
    return level[t] != -1;
  }
  int DFS(int u, int nf){
    if (u == t) return nf;
    int res = 0;
    for (auto &it : E[u]){
      if (it.f > 0 && level[it.v] == level[u]+1){
        int tf = DFS(it.v, min(nf,it.f));
        res += tf; nf -= tf; it.f -= tf;
        E[it.v][it.re].f += tf;
        if (nf == 0) return res;
      }
    }
    if (!res) level[u] = -1;
    return res;
  }
  int flow(int res=0){
    while ( BFS() )
      res += DFS(s,2147483647);
    return res;
  }
}flow;

int main() {
    int n, m, k;

    set<int> bst;
    int ret = scanf("%d%d%d", &n, &m, &k);
    assert(ret == 3);
    int sss = n + n + m + k;
    int ttt = n + n + m + k + 1;
    flow.init(2 + sss, sss, ttt);
    for (int i = 0; i < n; i++) {
        int t;
        int ret = scanf("%d", &t);
        assert(ret == 1);
        flow.add_edge(sss, i, 1);
        flow.add_edge(i, i + n, 1);
        for (int j = 0; j < t; j++) {
            int x;
            int ret = scanf("%d", &x);
            bst.insert(x);
            assert(ret == 1);
            flow.add_edge(i + n, n + n + x - 1, 1);
        }
    }
    for (int i = 0; i < m; i++) {
        flow.add_edge(n + n + i, ttt, 1);
    }

    for (int i = 0; i < k; i++) {
        flow.add_edge(sss, n + n + m + i, 1);
        for (int j = 0; j < n; j++) {
            flow.add_edge(n + n + m + i, j, 1);
        }
    }
    cout << min((int) bst.size(), n + k) << endl;
    //cout << flow.flow() << endl;
}
