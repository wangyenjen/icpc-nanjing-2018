#include <testlib.h>

#include <cassert>
#include <cstdlib>
#include <cstring>
#include <numeric>
#include <vector>
#include <utility>

static std::vector<int> generate_tree(int argc, char **argv) {
    std::vector<int> parent;

    parent.push_back(0); // parent[root] = ignored
    int i = 1;

    while (argc) {
        char *type = argv[0];
        if (std::strcmp(type, "random") == 0) {
            assert(argc >= 2);
            int m = std::atoi(argv[1]);

            for (int j = 0; j < m; i++, j++)
                parent.push_back(rnd.next(i));

            argc -= 2, argv += 2;
        } else if (std::strcmp(type, "linear") == 0) {
            assert(argc >= 2);
            int m = std::atoi(argv[1]);

            for (int j = 0; j < m; i++, j++)
                parent.push_back(i - 1);

            argc -= 2, argv += 2;
        } else if (std::strcmp(type, "star") == 0) {
            assert(argc >= 2);
            int m = std::atoi(argv[1]);

            int centor = i - 1;
            for (int j = 0; j < m; i++, j++)
                parent.push_back(centor);

            argc -= 2, argv += 2;
        } else {
            assert(false);
        }
    }

    return std::move(parent);
}

static void print_tree(const std::vector<int> &parent) {
    int n = parent.size();
    std::vector<int> perm(n);
    std::iota(perm.begin(), perm.end(), 0);
    shuffle(perm.begin(), perm.end());

    std::vector<std::pair<int, int>> edges;
    for (int i = 1; i < n; i++) {
        int u = perm[i];
        int v = perm[parent[i]];

        if (rnd.next(2))
            std::swap(u, v);

        edges.emplace_back(u, v);
    }
    shuffle(edges.begin(), edges.end());

    println(n);
    for (auto edge : edges)
        println(edge.first + 1, edge.second + 1);
}

int main(int argc, char **argv) {
    registerGen(argc, argv, 1);

    print_tree(generate_tree(argc - 1, argv + 1));
}
