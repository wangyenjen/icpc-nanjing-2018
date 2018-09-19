#include <iostream>
#include <algorithm>
#define INF (1ll<<50)
using namespace std;

const int kN = 3005;
long long N, K, h[kN][kN], dp[kN][kN], w[kN][kN], p[kN];

int main() {
  cin >> N >> K;
  for (int i = 0; i < N; ++i) cin >> p[i];
  sort(p, p + N);
  for (int i = 0; i < N; ++i) for (int j = i + 1; j < N; ++j) w[i][j] = w[i][j - 1] + p[j] - p[(i + j) >> 1];
  for (int j = 0; j < N; ++j) dp[0][j] = w[0][j];
  for (int i = 1; i < N; ++i) {
    h[i][N] = N - 1;
    for (int j = N - 1; j >= i; --j) {
      dp[i][j] = INF;
      for (int k = h[i - 1][j]; k <= h[i][j + 1]; ++k) {
        if (dp[i - 1][k] + w[k + 1][j] < dp[i][j]) dp[i][j] = dp[i - 1][k] + w[k + 1][j], h[i][j] = k;
      }
    }
  }
  cout << dp[K - 1][N - 1] << endl;
  return 0;
}
