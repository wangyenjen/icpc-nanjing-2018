/**
 * The "inner loop" is implemented naively
 * with break when a = 0.
 */
#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <numeric>

constexpr int maxn = 100000;

char s[maxn + 1];
int c1[maxn + 1], c2[maxn + 1];
int ans[maxn + 1];

int main() {
    int n;
    int ret = std::scanf("%d", &n);
    assert(ret == 1);
    assert(1 <= n && n <= maxn);

    ret = std::scanf("%100000s", s);
    assert(ret == 1);
    assert((int) std::strlen(s) == n);
    assert(std::all_of(s, s + n, [](char c){ return c >= '0' && c <= '2'; }));

    std::reverse(s, s + n);
        
    for (int i = 0; i < n; i++) {
        c1[i + 1] = c1[i] + 2 * (s[i] == '1') - 1;
        c2[i + 1] = c2[i] + 2 * (s[i] == '2') - 1;
    }

    for (int i = 1; i <= n; i++) {
        if (c1[i] >= 0) {
            // answer += 111...1
            ans[0] += 1;
            ans[c1[i]] -= 1;
        } else if (c2[i] >= 0) {
            // answer += 222...2
            ans[0] += 2;
            ans[c2[i]] -= 2;
        } else if (i + c1[i] + c2[i] > 0 && i % 2 == 1 && s[0] != '0') {
            // answer += 0, 1, or 2 (hard)
            // FIXME this loop take too much time
            int a = 2;
            for (int j = 0; j < i; j += 2)
                if (c1[j] <= 0 && c2[j] <= 0 &&
                        c1[i] <= c1[j + 1] && c2[i] <= c2[j + 1]) {
                    int b = s[j] - '0';
                    if (b < a) {
                        a = b;
                        if (a == 0)
                            break;
                    }
                }
            ans[0] += a;
            ans[1] -= a;
        }
    }

    std::partial_sum(ans, ans + n + 1, ans);
    for (int i = 0; i < n; i++) {
        ans[i + 1] += ans[i] / 10;
        ans[i] %= 10;
    }

    bool skip = true;
    for (int i = n - 1; i >= 0; i--) {
        if (skip && i && !ans[i])
            continue;
        skip = false;
        putchar('0' + ans[i]);
    }
    putchar('\n');
}
