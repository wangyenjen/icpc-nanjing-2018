#include <testlib.h>
#include <cstring>

int main(int argc, char **argv) {
    registerGen(argc, argv, 1);

    auto s = rnd.next(argv[1]);

    println(s.size());
    println(s);
}
