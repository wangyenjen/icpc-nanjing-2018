#include <testlib.h>

int main(int argc, char **argv) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100'000, "n");
    inf.readEoln();

    inf.readToken(format("[0-2]{%d}", n), "s");
    inf.readEoln();
    inf.readEof();
}
