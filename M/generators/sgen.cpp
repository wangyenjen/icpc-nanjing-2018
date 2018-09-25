#include <testlib.h>
#include <cassert>
#include <cstdlib>
#include <numeric>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

std::string generate(int n,
        std::vector<std::string_view> elements,
        std::vector<int> weights) {
    std::string s;
    while ((int) s.size() < n) {
        int x = rnd.next(weights.back());

        auto it = std::upper_bound(weights.begin(), weights.end(), x);
        s += elements[it - weights.begin()];
    }
    return std::move(s);
}

int main(int argc, char **argv) {
    registerGen(argc, argv, 1);
    int n = std::atoi(argv[1]);
    int m = std::atoi(argv[2]);

    std::vector<std::string_view> elements;
    std::vector<int> weights;

    for (int i = 3; i < argc; i += 2) {
        assert(i + 2 <= argc);

        elements.push_back(argv[i]);
        weights.push_back(std::atoi(argv[i + 1]));
    }

    std::partial_sum(weights.begin(), weights.end(),
                     weights.begin());

    println(generate(n, elements, weights));
    println(generate(m, elements, weights));
}
