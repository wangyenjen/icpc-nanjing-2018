/// Author: Wang, Yen-Jen
#include <testlib.h>

#include <cassert>

int main(int argc, char **argv) {
    registerValidation(argc, argv);
    int N = inf.readInt(1, 5000, "N");
    inf.readSpace();
    int X = inf.readInt(1, 1000000, "X");
    inf.readSpace();
    int Y = inf.readInt(1, 1000000, "Y");
    inf.readEoln();
    assert(X != Y);
    inf.readInt(1, 1000000, "a_1");
    for (int i = 2; i <= N; i++) {
        inf.readSpace();
        inf.readInt(1, 1000000, "a_i");
    }
    inf.readEoln();
    inf.readEof();
    return 0;
}
