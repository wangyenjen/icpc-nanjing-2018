#include <cstdio>
#include <algorithm>

const int MN = 300003;

int stkmem[MN * 2], top;
inline int* Alloc(int z) {
  int* p = stkmem + top; top += z; stkmem[top++] = z;
  return p;
}

long sum[MN], mem[2][MN], D[MN];
long *dp = mem[0], *prv = mem[1];
inline long Cost(int i, int j) { //[)
  return sum[i] + sum[j] - sum[(i + j) / 2] - sum[(i + j + 1) / 2];
}
inline long Func(int i, int j) { //[]
  return j > i ? prv[j + 1] : prv[j] + Cost(j, i + 1);
}

void Smawk(int A, int B, int M, const int* cols, int result[], int depth = 0) {
  int N = B - A, R = ((N - 1) >> depth) + 1, R2 = 1 << depth;
  int* stk = Alloc(R);
  int sz = 0;
  for (int i = 0; i < M; i++) {
    while (sz && !(Func(A + R2 * (sz - 1), stk[sz - 1]) <
            Func(A + R2 * (sz - 1), cols[i]))) sz--;
    if (sz < R) stk[sz++] = cols[i];
  }
  if (R == 1) {
    result[A] = *stk;
    return;
  }
  Smawk(A, B, sz, stk, result, depth + 1);

  for (int i = R2, j = 0; i < N; i += 2 * R2, j--) {
    int q = A + i, nxt = i + R2 < N ? result[q + R2] : stk[sz - 1];
    while (j < sz && stk[j] < result[q - R2]) j++;
    for (result[A + i] = stk[j++]; j < sz && stk[j] <= nxt; j++) {
      if (Func(q, stk[j]) < Func(q, result[q])) {
        result[q] = stk[j];
      }
    }
  }
}

int col[MN], res[MN];

int main() {
  int N, K;
  scanf("%d%d", &N, &K);
  if (K >= N) { puts("0"); return 0; }
  for (int i = 0; i < N; i++) scanf("%ld", D + i);
  for (int i = 0; i < N; i++) sum[i + 1] = sum[i] + D[i];

  for (int i = 0; i < N; i++) {
    col[i] = i;
    prv[i + 1] = Cost(0, i + 1);
  }
  for (int i = 1; i < K; i++) {
    top = 0; Smawk(0, N, N, col, res);
    for (int j = 0; j < N; j++) dp[j + 1] = Func(j, res[j]);
    std::swap(dp, prv);
  }
  printf("%ld\n", prv[N]);
}

