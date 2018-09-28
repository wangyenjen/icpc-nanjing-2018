#include <testlib.h>
#include <cstdlib>
#include <algorithm>

char base[1'000'000 + 1];
char a[1'000'000 + 1];

void generate(int n, int k, int m) {
    std::copy_n(base, n, a);
    while (m) {
        int i = rnd.next(n - k + 1);
        if (std::find(a + i, a + i + k, a[i] ^ '0' ^ '1')
                == a + i + k) {
            for (int j = i; j < i + k; j++)
                a[j] ^= '0' ^ '1';
            m--;
        }
    }
}

int main(int argc, char **argv) {
    registerGen(argc, argv, 1);

    int n = atoi(argv[1]);
    int k = atoi(argv[2]);
    int n1 = atoi(argv[3]);
    int m = atoi(argv[4]);

    println(n, k);

    for (int i = 0; i < 2; i++) {
        std::fill_n(base, n1, '1');
        std::fill_n(base + n1, n - n1, '0');
        shuffle(base, base + n);
        generate(n, k, m);
        println(a);
    }
}

