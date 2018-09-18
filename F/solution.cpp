#include <cmath>
#include <cstdio>
#include <algorithm>

using Data = long double;

const int kN = 403;
using Row = Data[kN];

Data Inverse(Row a[], Row b[], int N) {
  static int ord_x[kN], ord_y[kN];
  for (int i = 0; i < N; i++) ord_x[i] = ord_y[i] = i;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) b[i][j] = 0;
    b[i][i] = 1;
  }
  auto A = [&](int x, int y)->Data&{ return a[ord_x[x]][ord_y[y]]; };
  auto B = [&](int x, int y)->Data&{ return b[ord_x[x]][ord_y[y]]; };

  for (int i = 0; i < N; i++) {
    int x = i, y = i;
    for (int j = i; j < N; j++) {
      for (int k = i; k < N; k++) {
        if (std::fabs(A(x, y)) < std::fabs(A(j, k))) x = j, y = k;
      }
    }
    std::swap(ord_x[x], ord_x[i]);
    std::swap(ord_y[y], ord_y[i]);

    for (int j = 0; j < N; j++) {
      if (j == i) continue;
      Data p = A(j, i) / A(i, i);
      for (int k = 0; k < N; k++) A(j, k) -= A(i, k) * p;
      for (int k = 0; k < N; k++) B(j, k) -= B(i, k) * p;
    }
  }
  Data det = 1;
  for (int i = 0; i < N; i++) {
    det *= A(i, i);
    for (int j = 0; j < N; j++) B(i, j) /= A(i, i);
  }
  return det;
}

int cnt[kN];
Row mat[kN], now[kN], inv[kN], table[kN];

#ifdef N3

#else
void RemoveRC(int x, int y, int N) {
  for (int i = 0; i < x; i++) {
    for (int j = 0; j < y; j++) now[i][j] = mat[i][j];
    for (int j = y + 1; j < N; j++) now[i][j - 1] = mat[i][j];
  }
  for (int i = x + 1; i < N; i++) {
    for (int j = 0; j < y; j++) now[i - 1][j] = mat[i][j];
    for (int j = y + 1; j < N; j++) now[i - 1][j - 1] = mat[i][j];
  }
}
#endif

int main() {
  int N, M, Q, a, b;
  scanf("%d%d%d", &N, &M, &Q);
  while (M--) {
    scanf("%d%d", &a, &b);
    mat[a][b] += 1;
    cnt[a]++;
  }
  for (int i = 0; i < N; i++) {
    if (!cnt[i]) continue;
    Data p = Data(-1) / cnt[i];
    for (int j = 0; j < N; j++) mat[i][j] *= p;
    mat[i][i] += 1;
  }
#ifdef N3

#else
  for (int i = 0; i < N; i++) {
    RemoveRC(i, i, N);
    Inverse(now, inv, N - 1);
    for (int j = 0; j < i; j++) {
      for (int k = 0; k < N; k++) table[j][i] += inv[j][k];
    }
    for (int j = i + 1; j < N; j++) {
      for (int k = 0; k < N; k++) table[j][i] += inv[j - 1][k];
    }
  }
#endif
  while (Q--) {
    int N, prv, now;
    Data ans = 0;
    scanf("%d%d", &N, &prv);
    for (; --N; prv = now) scanf("%d", &now), ans += table[prv][now];
    printf("%.10Lf\n", ans);
  }
}
