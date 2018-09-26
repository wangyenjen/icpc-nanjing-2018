/// Author: Wang, Yen-Jen
#include <testlib.h>

int main(int argc, char **argv) {
    registerValidation(argc, argv);
    int N = inf.readInt(1, 5000, "N");
    inf.readSpace();
    inf.readInt(1, 1000000, "X");
    inf.readSpace();
    inf.readInt(1, 1000000, "Y");
    inf.readEoln();
    inf.readInt(1, 1000000, "a_1");
    for (int i = 2; i <= N; i++) {
        inf.readSpace();
        inf.readInt(1, 1000000, "a_i");
    }
    inf.readEoln();
    inf.readEof();
    return 0;
}
