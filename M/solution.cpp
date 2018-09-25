#include <cstdio>
#include <cstring>
#include <algorithm>

constexpr int maxn = 1'000'000;

void z_value(char *s, int n, int *z) {
    z[0] = n;
    for (int i = 1, l = 0, r = 0; i < n; i++) {
        int j = std::max(std::min(z[i - l], r - i), 0);
        while (i + j < n && s[i + j] == s[j])
            j++;
        z[i] = j;
        if (i + z[i] > r)
            l = i, r = i + z[i];
    }
}

void manacher(char *s, int n, int *z) {
    for (int i = 0, l = 0, r = 0; i < n; i++) {
        int j = i < r ? std::min(z[2 * l - i], r - i) : 0;
        while (i - j >= 0 && i + j < n && s[i - j] == s[i + j])
            j++;
        z[i] = j;
        if (i + z[i] > r)
            l = i, r = i + z[i];
    }
}

char s[maxn + 1], t[maxn];
char b[maxn * 2 + 1];
int z[maxn * 2];
long cz[maxn + 1];

int main() {
    scanf("%s%s", s, t);
    int n = std::strlen(s);
    int m = std::strlen(t);

    std::copy_n(t, m, b);
    b[m] = '$';
    std::reverse_copy(s, s + n, b + m + 1);
    b[m + 1 + n] = '\0';
    z_value(b, m + 1 + n, z);

    cz[0] = cz[1] = 0;
    for (int i = 1; i < n; i++)
        cz[i + 1] = cz[i] + z[m + 1 + n - i];

    b[0] = '.';
    for (int i = 0; i < n; i++) {
        b[2 * i + 1] = s[i];
        b[2 * i + 2] = '.';
    }
    b[2 * n + 1] = '\0';
    manacher(b, 2 * n + 1, z);

    long ans = 0;
    for (int i = 0; i < 2 * n + 1; i++)
        ans += cz[(i + 1) / 2] - cz[(i - z[i] + 1) / 2];
    printf("%ld\n", ans);
}
