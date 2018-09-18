#include "testlib.h"
#include <cstring>

bool G[403][403];
bool vis[403];

void DFS1(int x, int N, int& cnt, int& nxt) {
  vis[x] = true;
  for (int i = 0; i < N; i++) {
    if (G[x][i] && !vis[i]) DFS1(i, N, cnt, nxt);
  }
  nxt = x;
}
void DFS2(int x, int N) {
  vis[x] = false;
  for (int i = 0; i < N; i++) {
    if (G[i][x] && vis[i]) DFS2(i, N);
  }
}

bool Korasaju(int N) {
  int x = -1;
  for (int i = 0, cnt = 0; i < N; i++) {
    if (!vis[i]) DFS1(i, N, cnt, x);
  }
  for (int i = 0; i < N; i++) {
    if (!vis[i]) throw;
  }
  DFS2(x, N);
  for (int i = 0; i < N; i++) {
    if (vis[i]) return false;
  }
  return true;
}

int main(int argc, char **argv) {
  registerValidation(argc, argv);
  int N, M, Q;
  N = inf.readInt(3, 400, "N");
  inf.readSpace();
  M = inf.readInt(N, 400000, "M");
  inf.readSpace();
  Q = inf.readInt(1, 400, "Q");
  inf.readEoln();

  while (M--) {
    int u = inf.readInt(0, N - 1, "u_i");
    inf.readSpace();
    int v = inf.readInt(0, N - 1, "v_i");
    inf.readEoln();
    G[u][v] = true;
  }
  ensuref(Korasaju(N), "Graph is not strongly-connected");
  while (Q--) {
    int L = inf.readInt(1, 500, "L");
    inf.readEoln();
    int prv, now = -1;
    while (L--) {
      prv = now;
      now = inf.readInt(0, N - 1, "x_i");
      if (L) {
        inf.readSpace();
        ensuref(prv != now, "Query invalid: Adjacent targets need to be different");
      } else {
        inf.readEoln();
      }
    }
  }
  inf.readEof();
}
