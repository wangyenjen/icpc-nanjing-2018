#include <cstdio>
#include <cstdint>
#include <cstring>
#include <algorithm>

const int MN = 300003;

#ifdef USE_MPFR
#include "mpreal.h"
using Data = mpfr::mpreal;
#define kFormat "%s"
inline const char* Out(const Data& a) {
  static std::string i;
  i = a.toString("%.23RNf");
  return i.c_str();
}
#else
using Data = long double;
#define kFormat "%.16Le"
inline Data Out(const Data& a) {return a;}
#endif

Data *sum, *sum2;
struct Node { Data v; int a; } dp[MN];
struct Range { int l, p; } rg[MN];

inline Data W(int i, int j) {
  //return sum[i] + sum[j] - sum[(i + j) / 2] - sum[(i + j + 1) / 2];
  Data sm = sum[j] - sum[i];
  return (sum2[j] - sum2[i]) - sm * sm / (j - i);
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
#ifdef USE_MPFR
  mpfr::mpreal::set_default_prec(512);
#endif
  int N, K;
  long long a;
  scanf("%d%d", &N, &K);
  sum = new Data[MN];
  sum2 = new Data[MN];
  sum[0] = sum2[0] = 0;
  for (int i = 0; i < N; i++) {
    scanf("%lld", &a);
    sum[i + 1] = sum[i] + a;
    sum2[i + 1] = sum2[i] + a * a;
  }

  Node l;
#ifdef USE_MPFR
  double mx = -1, L = 1e-12, R = sum2[N].toDouble() * 1.1 + 1, M;
#else
  double mx = -1, L = 1e-12, R = sum2[N] * 1.1 + 1, M;
#endif
  while (1) {
    uint64_t lL, lR;
    memcpy(&lL, &L, 8), memcpy(&lR, &R, 8);
    if (lR - lL < (1ll << 10)) break;
    uint64_t lM = (lL + lR) / 2;
    memcpy(&M, &lM, 8);
    Node res = Cal(M, N);
    if (res.a > K) {
      L = M;
      if (mx < M) mx = M, l = res;
    } else if (res.a < K) {
      R = M;
    } else {
      printf(kFormat"\n", Out(res.v - K * M));
      return 0;
    }
  }
  printf(kFormat"\n", Out(l.v - mx * K));
}

