#include <testlib.h>
#include <vector>

int find(std::vector<int> &dsu, int a) {
    return dsu[a] == a ? a : (dsu[a] = find(dsu, dsu[a]));
}

bool merge(std::vector<int> &dsu, int a, int b) {
    a = find(dsu, a);
    b = find(dsu, b);
    if (a == b)
        return false;
    dsu[a] = b;
    return true;
}

int main(int argc, char **argv) {
    registerValidation(argc, argv);

    int n = inf.readInt(3, 100'000, "n");
    inf.readEoln();

    std::vector<int> dsu(n);
    for (int i = 0; i < n; i++)
        dsu[i] = i;

    for (int i = 0; i < n - 1; i++) {
        int a = inf.readInt(1, n, "a_i");
        inf.readSpace();
        int b = inf.readInt(1, n, "b_i");
        inf.readEoln();

        a--;
        b--;

        ensuref(merge(dsu, a, b), "Tree can't contain cycles");
    }
    inf.readEof();
}
