#include "testlib.h"
#include <cmath>

const double kEpsilon = 1e-8;

int main(int argc, char* argv[]) {
  setName("Compare two sequences of doubles, "
          "max absolute or relative error = %.2e", kEpsilon);
  registerTestlibCmd(argc, argv);
  int N = 0;
  double mx = 0;
  for (; !ans.seekEof(); N++) {
    double j = ans.readDouble();
    double p = ouf.readDouble();
    mx = std::max(mx, std::fabs(j - p) / std::max(1., j));
    if (!doubleCompare(j, p, kEpsilon)) {
      quitf(_wa, "%d%s numbers differ - expected: '%.7f', found: '%.7f', "
          "error = '%.7f'", N + 1, englishEnding(N + 1).c_str(), j, p,
          doubleDelta(j, p));
    }
  }
  quitf(_ok, "%d numbers, max error: %.3e", N, mx);
}
