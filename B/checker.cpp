#include "testlib.h"

const double kEpsilon = 1e-8;

int main(int argc, char* argv[]) {
  setName("Compare two sequences of doubles, "
          "max absolute or relative error = %.2e", kEpsilon);
  registerTestlibCmd(argc, argv);
  double j = ans.readDouble();
  double p = ouf.readDouble();
  double del = doubleDelta(j, p);
  if (!doubleCompare(j, p, kEpsilon)) {
    quitf(_wa, "Numbers differ - expected: '%.9e', found: '%.9e', "
        "error = '%.3e'", j, p, del);
  }
  quitf(_ok, "Error: %.3e", del);
}
