#include <testlib.h>
#include <cstdlib>

int main(int argc, char **argv) {
    registerGen(argc, argv, 1);

    int n = atoi(argv[1]);
    int k = atoi(argv[2]);

    println(n, k);
    println(rnd.next("[01]{%d}", n));
    println(rnd.next("[01]{%d}", n));
}
