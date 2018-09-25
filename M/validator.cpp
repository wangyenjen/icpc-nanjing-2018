#include <testlib.h>

int main(int argc, char **argv) {
    registerValidation(argc, argv);

    auto s = inf.readToken("[a-z]{2,1000000}", "s");
    inf.readEoln();
    /* auto t = */ inf.readToken(format("[a-z]{1,%zd}", s.size() - 1), "t");
    inf.readEoln();
    inf.readEof();
}
