#include <testlib.h>

int main(int argc, char **argv) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 500, "n");
    inf.readSpace();
    int m = inf.readInt(1, 500, "m");
    inf.readSpace();
    inf.readInt(1, 500, "k");
    inf.readEoln();

    for (int i = 0; i < n; i++) {
        int t = inf.readInt(1, m, "t");
        for (int j = 0; j < t; j++) {
            inf.readSpace();
            inf.readInt(1, m, "x");
        }
        inf.readEoln();
    }
    inf.readEof();
}
