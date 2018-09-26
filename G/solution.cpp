/**
 * C(N + 3, 4)
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
        long long N = n + 3;
        long long ans = 1;
        ans = ans * N % mod;
        ans = ans * (N - 1) % mod;
        ans = ans * (N - 2) % mod;
        ans = ans * (N - 3) % mod;
        ans = ans * poww(4, mod - 2) % mod;
        ans = ans * poww(3, mod - 2) % mod;
        ans = ans * poww(2, mod - 2) % mod;
        ans = ans * poww(1, mod - 2) % mod;
        printf("%lld\n", ans);
    }
}
