#include <cmath>
#include <cstdio>
#include <algorithm>

using Data = long double;

const int kN = 403;
using Row = Data[kN];

Data Inverse(Row a[], Row b[], int N) {
  static int ord_x[kN], ord_y[kN], ord[kN];
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
  for (int i = 0; i < N; i++) ord[ord_x[i]] = ord_y[i];
  for (int i = 0; i < N; i++) {
    int x = ord[i];
    if (x == i) continue;
    for (int j = 0; j < N; j++) std::swap(b[i][j], b[x][j]);
    std::swap(ord[x], ord[i]);
  }

  return det;
}

int cnt[kN];
Row mat[kN], now[kN], inv[kN], tmpinv[kN], table[kN];

inline void RemoveRC(int x, int y, int N) {
  for (int i = 0; i < x; i++) {
    for (int j = 0; j < y; j++) now[i][j] = mat[i][j];
    for (int j = y + 1; j < N; j++) now[i][j - 1] = mat[i][j];
  }
  for (int i = x + 1; i < N; i++) {
    for (int j = 0; j < y; j++) now[i - 1][j] = mat[i][j];
    for (int j = y + 1; j < N; j++) now[i - 1][j - 1] = mat[i][j];
  }
}

#ifdef N3
const int kBlock = 50;

Row v, vA;
inline void ChangeRow(int a, int b, int x, int y, int N) {
  for (int i = 0; i < b; i++) v[i] = mat[y][i] - mat[x][i];
  for (int i = b + 1; i < N; i++) v[i - 1] = mat[y][i] - mat[x][i];
  for (int i = 0; i < N - 1; i++) vA[i] = 0;
  for (int i = 0; i < N - 1; i++) {
    for (int j = 0; j < N - 1; j++) vA[j] += v[i] * inv[i][j];
  }
  Data denom = vA[a] + 1;
  for (int i = 0; i < N - 1; i++) {
    Data A_ia = inv[i][a] / denom;
    for (int j = 0; j < N - 1; j++) inv[i][j] -= vA[j] * A_ia;
  }
}
inline void ChangeCol(int a, int b, int x, int y, int N) {
  for (int i = 0; i < b; i++) v[i] = mat[i][y] - mat[i][x];
  for (int i = b + 1; i < N; i++) v[i - 1] = mat[i][y] - mat[i][x];
  for (int i = 0; i < N - 1; i++) {
    vA[i] = 0;
    for (int j = 0; j < N - 1; j++) vA[i] += v[j] * inv[i][j];
  }
  Data denom = vA[a] + 1;
  for (int i = 0; i < N - 1; i++) v[i] = inv[a][i];
  for (int i = 0; i < N - 1; i++) {
    Data vA_i = vA[i] / denom;
    for (int j = 0; j < N - 1; j++) inv[i][j] -= vA_i * v[j];
  }
}
#endif

inline void MakeTable(int i, int N) {
  for (int j = 0; j < i; j++) {
    for (int k = 0; k < N; k++) table[j][i] += inv[j][k];
  }
  for (int j = i + 1; j < N; j++) {
    for (int k = 0; k < N; k++) table[j][i] += inv[j - 1][k];
  }
}

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
  for (int L = 0; L < N; L += kBlock) {
    int R = std::min(N, L + kBlock);
    int mid = (L + R) / 2;
    RemoveRC(L, L, N);
    Inverse(now, inv, N - 1);
    for (int i = 0; i < N - 1; i++) {
      for (int j = 0; j < N - 1; j++) tmpinv[i][j] = inv[i][j];
    }
    for (int i = L; i < R - 1; i++) {
      MakeTable(i, N);
      ChangeRow(i, i, i + 1, i, N);
      ChangeCol(i, i + 1, i + 1, i, N);
    }
    MakeTable(R - 1, N);
    /*for (int i = 0; i < N - 1; i++) {
      for (int j = 0; j < N - 1; j++) inv[i][j] = tmpinv[i][j];
    }
    for (int i = mid - 1; i >= L; i--) {
      ChangeCol(i, i + 1, i, i + 1, N);
      ChangeRow(i, i, i, i + 1, N);
      MakeTable(i, N);
    }*/
  }
#else
  for (int i = 0; i < N; i++) {
    RemoveRC(i, i, N);
    Inverse(now, inv, N - 1);
    MakeTable(i, N);
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
