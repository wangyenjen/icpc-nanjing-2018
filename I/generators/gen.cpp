#include <testlib.h>

#include <numeric>
#include <vector>
#include <utility>

int main(int argc, char **argv) {
    registerGen(argc, argv, 1);

    int n = atoi(argv[1]);
    int m = atoi(argv[2]);
    int k = atoi(argv[3]);

    println(n, m, k);

    for (int i = 0; i < n; i++) {
        std::vector<int> arr;

        for (int j = 0; j < m; j++) {
            if (rnd.next(m) < 3) arr.push_back(j + 1);
        }
        if (arr.empty()) println(0);
        else println(arr.size(), arr);
    }
}
