#include <testlib.h>
#include <cstring>

int main(int argc, char **argv) {
  registerValidation(argc, argv);
  int N = inf.readInt(2, 300000, "N");
  inf.readSpace();
  inf.readInt(1, N - 1, "K");
  inf.readEoln();

  int prv = inf.readInt(0, 0, "a_0");
  for (int i = 1; i < N; i++) {
    inf.readSpace();
    prv = inf.readInt(prv + 1, 1'000'000'000, "a_i");
  }
  inf.readEoln();
  inf.readEof();
}
