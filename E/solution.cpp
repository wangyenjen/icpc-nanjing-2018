#include <cstdio>
#include <algorithm>

constexpr int maxn = 1'000'000;

void magic(int n, int k, const char *s, int *d) {
    std::fill_n(d, 2 * n, -1);
    for (int i = 0, r = 0; i < n; i++)
        if (s[i] == '1') {
            if (r > 0 && d[r - 1] == i % k) {
                d[--r] = -1;
                if (r > 0 && d[r - 1] == (i + 1) % k)
                    d[--r] = -1;
                else
                    d[r++] = (i + 1) % k;
            } else {
                d[r++] = i % k;
                d[r++] = (i + 1) % k;
            }
        }
}

char a[maxn + 1], b[maxn + 1];
int a2[2 * maxn], b2[2 * maxn];

bool solve(int n, int k) {
    if (k == 1)
        return true;
    magic(n, k, a, a2);
    magic(n, k, b, b2);
    return std::equal(a2, a2 + 2 * n, b2);
}

int main() {
    int n, k;
    std::scanf("%d%d%s%s", &n, &k, a, b);
    std::puts(solve(n, k) ? "Yes" : "No");
}
