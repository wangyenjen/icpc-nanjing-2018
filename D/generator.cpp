/// Author: Wang, Yen-Jen
#include <testlib.h>

#include <string>
#include <algorithm>

inline int Rnd(int a, int b) {
	return rnd.next(b - a + 1) + a;
}

int main(int argc, char **argv) {
	if (argc != 3) exit(1);
  	registerGen(argc, argv, 1);

	int N = std::stoi(std::string(argv[1]));

	println(N);
	for (int i = 1; i <= N; i++) {
		int x = Rnd(-100000, 100000);
		int y = Rnd(-100000, 100000);
		int z = Rnd(-100000, 100000);
		println(x, y, z);
	}

	return 0;
}
