#include <testlib.h>

int main(int argc, char **argv) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 1000000, "t");
    inf.readEoln();

    for (int i = 0; i < t; i++) {
        inf.readLong(1, 1000000000LL, "a_i");
        inf.readEoln();
    }
    inf.readEof();
}
