/// Author: Wang, Yen-Jen
#include <cstdio>
#include <algorithm>

using namespace std;

const int MAX_N = 5000 + 7;
const int INF = 0x3f3f3f3f;

int A[MAX_N];
int dp[2][MAX_N<<1][3][3][2];

int main() {
	int N, X, Y;
	scanf("%d%d%d", &N, &X, &Y);
	int M = 0;
	for(int i = 1; i <= N; i++) {
		scanf("%d",&A[i]);
		if(A[i] == X) A[i] = 0;
        else if(A[i] == Y) A[i] = 1;
        else A[i] = 2, M++;
	}
	for(int i = 0; i <= M + M; i++) {
		for(int j = 0; j < 3; j++) {
			for(int k = 0; k < 3; k++) {
				for(int l = 0; l < 2; l++) dp[0][i][j][k][l] = INF;
			}
		}
	}
	dp[0][M][2][0][0] = 0;
	dp[0][M][0][2][1] = 0;
	for(int i = 1; i <= N; i++) {
		for(int j = 0; j <= M + M; j++) {
			for(int k = 0; k < 3; k++) {
				for(int x = 0; x < 3; x++) {
					for(int y = 0; y < 2; y++) dp[i&1][j][k][x][y] = INF;
				}
			}
		}
		for(int j = 0; j <= M + M; j++) {
			for(int k = 0; k < 3; k++) {
				for(int x = 0; x < 3; x++) {
					for(int y = 0; y < 2; y++) {
						if(dp[~i&1][j][k][x][y] == INF) continue;
						if(A[i] == 0) {
							if(y == 0) {
								dp[i&1][j][k][x][y] = min(dp[i&1][j][k][x][y] , dp[~i&1][j][k][x][y]);
								if(j + 1 <= M + M) {
									dp[i&1][j + 1][k][2][1] = min(dp[i&1][j + 1][k][2][1] , dp[~i&1][j][k][x][y] + 1);
								}
							}
							else {
								if(k == 0) {
									dp[i&1][j][1][x][y] = min(dp[i&1][j][1][x][y] , dp[~i&1][j][k][x][y] + 1);
									if(j + 1 <= M + M) {
										dp[i&1][j + 1][2][x][0] = min(dp[i&1][j + 1][2][x][0] , dp[~i&1][j][k][x][y] + 1);
									}
								}
								else if(k == 1) {
									dp[i&1][j][k][x][y] = min(dp[i&1][j][k][x][y] , dp[~i&1][j][k][x][y] + 1);
									if(j + 1 <= M + M) {
										dp[i&1][j + 1][2][x][0] = min(dp[i&1][j + 1][2][x][0] , dp[~i&1][j][k][x][y] + 1);
									}
								}
								else {
									dp[i&1][j][k][x][y] = min(dp[i&1][j][k][x][y] , dp[~i&1][j][k][x][y] + 1);
									if(j + 1 <= M + M) {
										dp[i&1][j + 1][2][x][1] = min(dp[i&1][j + 1][2][x][1] , dp[~i&1][j][k][x][y] + 1);
									}
								}
							}
						}
						else if(A[i] == 1) {
							if(y == 1) {
								dp[i&1][j][k][x][y] = min(dp[i&1][j][k][x][y] , dp[~i&1][j][k][x][y]);
								if(j + 1 <= M + M) {
									dp[i&1][j + 1][2][x][0] = min(dp[i&1][j + 1][2][x][0] , dp[~i&1][j][k][x][y] + 1);
								}
							}
							else {
								if(x == 0) {
									dp[i&1][j][k][1][y] = min(dp[i&1][j][k][1][y] , dp[~i&1][j][k][x][y] + 1);
									if(j + 1 <= M + M) {
										dp[i&1][j + 1][k][2][1] = min(dp[i&1][j + 1][k][2][1] , dp[~i&1][j][k][x][y] + 1);
									}
								}
								else if(x == 1) {
									dp[i&1][j][k][x][y] = min(dp[i&1][j][k][x][y] , dp[~i&1][j][k][x][y] + 1);
									if(j + 1 <= M + M) {
										dp[i&1][j + 1][k][2][1] = min(dp[i&1][j + 1][k][2][1] , dp[~i&1][j][k][x][y] + 1);
									}
								}
								else {
									dp[i&1][j][k][x][y] = min(dp[i&1][j][k][x][y] , dp[~i&1][j][k][x][y] + 1);
									if(j + 1 <= M + M) {
										dp[i&1][j + 1][k][2][0] = min(dp[i&1][j + 1][k][2][0] , dp[~i&1][j][k][x][y] + 1);
									}
								}
							}
						}
						else {
							dp[i&1][j][k][x][y] = min(dp[i&1][j][k][x][y] , dp[~i&1][j][k][x][y]);
							if(j >= 1) dp[i&1][j - 1][k][x][y] = min(dp[i&1][j - 1][k][x][y] , dp[~i&1][j][k][x][y]);
							if(y == 0) {
								dp[i&1][j][k][2][1] = min(dp[i&1][j][k][2][1] , dp[~i&1][j][k][x][y]);
							}
							else {
								dp[i&1][j][2][x][0] = min(dp[i&1][j][2][x][0] , dp[~i&1][j][k][x][y]);
							}
						}
					}
				}
			}
		}
	}
	int ans = INF;
	ans = min(ans , dp[N&1][M][2][0][0]);
	ans = min(ans , dp[N&1][M][2][2][0]);
	ans = min(ans , dp[N&1][M][0][2][1]);
	ans = min(ans , dp[N&1][M][2][2][1]);
	if(ans == INF) puts("-1");
	else printf("%d\n",ans);
    return 0;
}

