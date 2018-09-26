/// Author: Wang, Yen-Jen
#include <testlib.h>

int main(int argc, char **argv) {
	registerValidation(argc, argv);
	int N = inf.readInt(1, 100, "N");
	inf.readEoln();
	for (int i = 1; i <= N; i++) {
		inf.readInt(-100000, 100000, "X_i");
		inf.readSpace();
		inf.readInt(-100000, 100000, "Y_i");
		inf.readSpace();
		inf.readInt(-100000, 100000, "Z_i");
		inf.readEoln();
	}
	inf.readEof();
	return 0;
}
