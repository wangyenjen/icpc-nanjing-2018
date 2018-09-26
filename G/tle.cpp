/**
 * O(N)
 */
#include <algorithm>
#include <cstdio>
#include <cassert>

const long long mod = 1000000007;

long long poww(long long a, long long  b) {
    long long tmp = 1;
    while (b) {
        if (b & 1) tmp = tmp * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return tmp;
}

int main() {
    int t;
    int ret = scanf("%d", &t);
    assert(ret == 1);

    for (int i = 0; i < t; i++) {
        long long n;
        int ret = scanf("%lld", &n);
        assert(ret == 1);
        long long ans = 0;
        for (int a = 1; a <= n; a++) {
            ans += a * ((1 + (n - a + 1)) * (n - a + 1) / 2 % mod) % mod;
            ans %= mod;
        }
        printf("%lld\n", ans);
    }
}
