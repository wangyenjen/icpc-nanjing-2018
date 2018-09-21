/**
 * The "inner loop" is not implemented.
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
        c1[i + 1] = c1[i] + (s[i] == '1');
        c2[i + 1] = c2[i] + (s[i] == '2');
    }

    for (int i = 1; i <= n; i++) {
        if (c1[i] > i / 2) {
            // answer += 111...1 (2c1[i] - i)
            ans[0] += 1;
            ans[2 * c1[i] - i] -= 1;
        } else if (c2[i] > i / 2) {
            // answer += 222...2 (2c2[i] - i)
            ans[0] += 2;
            ans[2 * c2[i] - i] -= 2;
        } else if ((i - c1[i] - c2[i]) <= i / 2 && i % 2 == 1) {
            // answer += 0, 1, or 2 (hard)
            // FIXME implement this
        }
    }

    std::partial_sum(ans, ans + n + 1, ans);
    for (int i = 0; i < n; i++) {
        ans[i + 1] += ans[i] / 10;
        ans[i] %= 10;
    }

    bool skip = true;
    for (int i = n - 1; i >= 0; i--) {
        if (skip && !ans[i])
            continue;
        skip = false;
        putchar('0' + ans[i]);
    }
    putchar('\n');
}
