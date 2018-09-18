#include "testlib.h"

int main(int argc, char **argv) {
  registerValidation(argc, argv);
  int N, M, Q;
  N = inf.readInt(3, 400, "N");
  inf.readSpace();
  M = inf.readInt(N, 400000, "M");
  inf.readSpace();
  Q = inf.readInt(1, 400, "Q");
  inf.readEoln();

  while (M--) {
    inf.readInt(0, N - 1, "u_i");
    inf.readSpace();
    inf.readInt(0, N - 1, "v_i");
    inf.readEoln();
  }
  while (Q--) {
    int L = inf.readInt(1, 500, "L");
    inf.readEoln();
    int prv, now = -1;
    while (L--) {
      prv = now;
      now = inf.readInt(0, N - 1, "x_i");
      if (L) {
        inf.readSpace();
        ensuref(prv != now, "Query invalid: Adjacent targets need to be different");
      } else {
        inf.readEoln();
      }
    }
  }
  inf.readEof();
}
