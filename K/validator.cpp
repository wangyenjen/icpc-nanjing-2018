#include <testlib.h>

#include <cassert>
#include <string>

using namespace std;

const int MAX_N = 20 + 7;
const int DX[2] = {1, 0};
const int DY[2] = {0, 1};

int par[MAX_N * MAX_N];
int a[MAX_N][MAX_N];

int find(int x) {
    if (x == par[x]) return x;
    else return par[x] = find(par[x]);
}

bool merge(int x, int y) {
    x = find(x);
    y = find(y);
    if (x == y) return 0;
    par[y] = x;
    return 1;
}

int main(int argc, char **argv) {
    registerValidation(argc, argv);
    
    int n = inf.readInt(1, 20, "n");
    inf.readSpace();
    int m = inf.readInt(1, 20, "m");
    inf.readEoln();

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            char c = inf.readChar();
            assert(c == '0' || c == '1');
            a[i][j] = c - '0';
        }
        inf.readEoln(); 
    }

    inf.readEof();

    for (int i = 0; i < n * m; i++) par[i] = i;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (a[i][j] == 0) continue;
            for (int k = 0; k < 2; k++) {
                int x = i + DX[k];
                int y = j + DY[k];
                if (x < 0 || x >= n || y < 0 || y >= m) continue;
                if (a[x][y] == 0) continue;
                if (!merge(x * m + y, i * m + j)) return 1;
            }
        }
    }

    int id = -1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (a[i][j] == 1) {
                if (id == -1) id = find(i * m + j);
                else if (id != find(i * m + j)) return 1;
            }
        }
    }

    return 0;
}
