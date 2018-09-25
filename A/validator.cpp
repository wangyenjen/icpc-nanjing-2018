/// Author: Wang, Yen-Jen
#include <testlib.h>

int main(int argc, char **argv) {
    registerValidation(argc, argv);
    inf.readInt(0, 1000000, "N");
    inf.readSpace();
    inf.readInt(1, 1000000, "K");
    inf.readEoln();
    inf.readEof();
    return 0;
}
