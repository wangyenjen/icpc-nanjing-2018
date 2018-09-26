#include <testlib.h>

#include <numeric>
#include <vector>
#include <utility>

int main(int argc, char **argv) {
    registerGen(argc, argv, 1);

    int t = atoi(argv[1]);
    long long N = atoll(argv[2]);

    println(t);
    for (int i = 0; i < t; i++) {
        long long n = rnd.next(1LL, N);
        println(n);
    }
}
