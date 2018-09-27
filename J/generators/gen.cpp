#include <testlib.h>

#include <numeric>
#include <vector>
#include <utility>

int main(int argc, char **argv) {
    registerGen(argc, argv, 1);

    int n = atoi(argv[1]);
    int m = atoi(argv[2]);

    println(n);

    std::vector<int> arr;
    for (int i = 0; i < n; i++) {
        arr.push_back(rnd.next(1, m));
    }
    println(arr);
}
