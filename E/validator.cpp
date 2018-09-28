#include <testlib.h>

int main(int argc, char **argv) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1'000'000, "n");
    inf.readSpace();
    /* int k = */ inf.readInt(1, n, "k");
    inf.readEoln();

    inf.readToken(format("[01]{%d}", n), "s");
    inf.readEoln();

    inf.readToken(format("[01]{%d}", n), "t");
    inf.readEoln();
    inf.readEof();
}
