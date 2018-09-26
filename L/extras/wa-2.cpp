#include <cstdio>
#include <string>
#include <cstring>
#include <algorithm>

using namespace std;

int _mem[2][2][5001];
auto dp = _mem[0], prv = _mem[1];

int main()
{
    int N, a, X, Y;
    string str;
    int cnt[3] = {0, 0, 0};
    scanf("%d%d%d", &N, &X, &Y);
    for (int i = 0; i < N; i++) {
        scanf("%d", &a);
        if (a == X) a = 0;
        else if (a == Y) a = 1;
        else a = 2;
        cnt[a]++;
        str.push_back(a ^ '0');
    }
    if (!cnt[0] || !cnt[1]) { puts("0"); return 0; }
    if (cnt[0] && cnt[1] && !cnt[2]) { puts("-1"); return 0; }

    int L = 0, R = cnt[2];
    memset(_mem, 0x3f, sizeof(_mem));
    prv[0][0] = prv[1][0] = 0;
    int pos = 0;
    for (char c : str) {
        for (int i : {0, 1})
            for (int j = L; j <= R; j++) dp[i][j] = 1000000;
        if (c == '2') {
            for (int i : {0, 1})
                for (int j = L; j <= R; j++) dp[i][j + 1] = min(prv[i][j], prv[!i][j]);
            for (int i : {0, 1})
                for (int j = L; j <= R; j++) dp[i][j] = min(dp[i][j], prv[i][j]);
            swap(dp, prv);
            continue;
        }
        for (int i : {0, 1}) {
            if (int(c ^ '0') != i) {
                for (int j = L; j <= R; j++) {
                    dp[!i][j + 1] = min(dp[!i][j + 1], prv[i][j] + 1);
                    dp[i][j] = min(dp[i][j], prv[i][j] + 1);
                }
            }
            else {
                for (int j = L; j <= R; j++)
                    dp[i][j] = min(dp[i][j], prv[i][j]);
            }
        }

        /*for (int i : {0, 1}) {
            for (int j = L; j <= R; j++) printf("%d ", dp[i][j]);
            puts("");
        }puts("");*/
        swap(dp, prv);
        pos++;
    }

    printf("%d\n", min(prv[0][R], prv[1][R]));
}

