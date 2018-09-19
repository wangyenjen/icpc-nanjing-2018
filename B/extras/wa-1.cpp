#include <cstdio>
#include <algorithm>

const int MN = 300003;
const long kInf = 1l << 61;

int stkmem[MN * 2], top;
inline int* Alloc(int z) {
  int* p = stkmem + top; top += z; stkmem[top++] = z;
  return p;
}

struct Node {
  long val; int p;
  bool operator<(const Node& x) const {
    return val < x.val || (val == x.val && p < x.p);
  }
} dp[MN];
long sum[MN], penalty;
inline long Cost(int i, int j) { //[)
  return sum[i] + sum[j] - sum[(i + j) / 2] - sum[(i + j + 1) / 2];
}
inline Node Func(int i, int j) { //[), i > j
  return {dp[j].val + Cost(j, i) + penalty, dp[j].p + 1};
}

void Smawk(int A, int B, int M, const int* cols, int* result, int depth) {
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

inline void Smawk(int l, int r, int tl, int tr, int* result) {
  static int cols[MN];
  for (int i = tl; i < tr; i++) cols[i - tl] = i;
  Smawk(l, r, tr - tl, cols, result, 0);
}

Node ConcaveCal(int N, long penal) {
  static int res[MN];
  static Node nm[MN];
  penalty = penal;
  int c = 1, r = 0;
  for (int i = 1; i <= N; i++) nm[i].val = kInf;
  while (c <= N) {
    int p = std::min(2 * c - r, N);
    top = 0; Smawk(c, p + 1, r, c, res);
    auto F = [&](int i) { return std::min(nm[i], Func(i, res[i])); };

    dp[c] = F(c);
    int j = c + 1;
    for (; j <= p; j++) {
      if (Func(j, j - 1) < F(j)) {
        dp[j] = Func(j, j - 1); break;
      }
      dp[j] = F(j);
      if (Func(p, j - 1) < F(p)) {
        for (int k = j + 1; k <= p; k++) nm[k] = F(k);
        break;
      }
    }
    if (j <= p) {
      c = j + 1, r = j - 1;
    } else {
      c = p + 1, r = std::max(r, res[p]);
    }
  }
  return dp[N];
}

long D[MN];

int main() {
  int N, K;
  scanf("%d%d", &N, &K);
  if (K >= N) { puts("0"); return 0; }
  for (int i = 1; i < N; i++) scanf("%ld", D + i);
  for (int i = 0; i < N; i++) sum[i + 1] = sum[i] + D[i];

  Node l; long mn = kInf;
  long L = 0, R = sum[N] + 1;
  while (L + 1 < R) {
    long M = (L + R) / 2;
    Node res = ConcaveCal(N, M - 1);
    if (res.p > K) {
      L = M;
    } else if (res.p < K) {
      R = M;
      if (mn > M - 1) mn = M - 1, l = res;
    } else {
      printf("%ld", res.val - K * (M - 1)); return 0;
    }
  }
  printf("%ld\n", l.val - L * K);
}

