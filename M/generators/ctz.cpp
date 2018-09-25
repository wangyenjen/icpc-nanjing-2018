#include <testlib.h>
#include <cassert>
#include <cstdlib>
#include <numeric>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

std::string generate(int n, int start) {
    std::string s(n, 'a');
    for (int i = 0; i < n; i++)
        s[i] = 'a' + __builtin_ctz(start + i);
    return std::move(s);
}

int main(int argc, char **argv) {
    registerGen(argc, argv, 1);
    int n = std::atoi(argv[1]);
    int m = std::atoi(argv[2]);
    int start1 = std::atoi(argv[3]);
    int start2 = std::atoi(argv[4]);

    println(generate(n, start1));
    println(generate(m, start2));
}
