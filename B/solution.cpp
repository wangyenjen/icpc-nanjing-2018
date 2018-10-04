#include <cstdio>
#include <algorithm>

const int MN = 300003;

using Data = long long;

Data sum[MN];
struct Node { Data v; int a; } dp[MN];
struct Range { int l, p; } rg[MN];

inline Data W(int i, int j) {
  return sum[i] + sum[j] - sum[(i + j) / 2] - sum[(i + j + 1) / 2];
}

Node Cal(Data P, int N) {
  dp[0] = {0, 0};
  int tL = 0, tR = 0;
  rg[tR++] = {0, 0}; rg[tR].l = N + 1;

  auto F = [&](int i, int j) { return dp[i].v + W(i, j); };
  auto Check = [&](int a, int b, int i) { return F(a, i) >= F(b, i); };
  for (int i = 1;; i++) {
    dp[i] = {F(rg[tL].p, i) + P, dp[rg[tL].p].a + 1};
    if (i == N) return dp[N];
    if (rg[tL + 1].l <= i + 1) tL++;
    if (rg[tL].l <= i) rg[tL].l = i + 1;
    while (tL != tR && Check(rg[tR - 1].p, i, rg[tR - 1].l)) tR--;
    if (tL == tR) {
      rg[tR++] = {i + 1, i};
    } else if (rg[tR - 1].l != rg[tR].l) {
      int l = rg[tR - 1].l, r = rg[tR].l + 1;
      while (l + 1 < r) {
        int m = (l + r) / 2;
        (Check(rg[tR - 1].p, i, m - 1) ? r : l) = m;
      }
      rg[tR++] = {l, i};
    }
    rg[tR].l = N + 1;
  }
}

int main() {
  int N, K;
  scanf("%d%d", &N, &K);
  if (K >= N) { puts("0"); return 0; }
  for (int i = 0; i < N; i++) scanf("%lld", sum + i + 1);
  for (int i = 1; i <= N; i++) sum[i] += sum[i - 1];

  Node l;
  Data mx = -1, L = 0, R = sum[N] + 2;
  while (L + 1 < R) {
    Data M = (L + R) / 2;
    Node res = Cal(M - 1, N);
    if (res.a > K) {
      L = M;
      if (mx < M - 1) mx = M - 1, l = res;
    } else if (res.a < K) {
      R = M;
    } else {
      printf("%lld\n", res.v - K * (M - 1));
      return 0;
    }
  }
  printf("%lld\n", l.v - (L - 1) * K);
}

