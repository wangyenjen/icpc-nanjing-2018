/// Author: Wang, Yen-Jen
#include <cstdio>

int main() {
    int n, k;
    scanf("%d%d", &n, &k);
    if (n == 0) puts("Austin");
    else {
        if (k == 1) {
            if (n % 2 == 0) puts("Austin");
            else puts("Adrien");
        }
        else puts("Adrien");
    }
    return 0;
}
