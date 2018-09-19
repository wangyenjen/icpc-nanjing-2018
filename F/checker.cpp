#include "testlib.h"

const double kEpsilon = 1e-5;

int main(int argc, char* argv[]) {
  setName("Compare two sequences of doubles, "
          "max absolute or relative error = %.2e", kEpsilon);
  registerTestlibCmd(argc, argv);
  int N = 0;
  for (; !ans.seekEof(); N++) {
    double j = ans.readDouble();
    double p = ouf.readDouble();
    if (!doubleCompare(j, p, kEpsilon)) {
      quitf(_wa, "%d%s numbers differ - expected: '%.7f', found: '%.7f', "
          "error = '%.7f'", N + 1, englishEnding(N + 1).c_str(), j, p,
          doubleDelta(j, p));
    }
  }
  quitf(_ok, "%d numbers", N);
}
