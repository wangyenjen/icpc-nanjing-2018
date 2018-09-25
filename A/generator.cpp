/// Author: Wang, Yen-Jen
#include <testlib.h>

#include <string>
#include <algorithm>

int main(int argc, char **argv) {
    if (argc != 3) exit(1);
    registerGen(argc, argv, 1);
    int N = std::stoi(std::string(argv[1]));
    int K = std::stoi(std::string(argv[2]));
    println(N, K);
    return 0;
}
