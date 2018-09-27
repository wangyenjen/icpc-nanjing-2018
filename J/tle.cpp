/**
 * For each prime calculate the number of interval that contain it.
 */
#include<bits/stdc++.h>
using namespace std;

typedef long long int LL;
int is[1000005];
vector<int> pri;
int fac[1000005];

int main() {
    for (int i = 2; i <= 1000000; i++) {
        if (is[i]) continue;
        pri.push_back(i);
        for (int j = i; j <= 1000000; j += i) {
            fac[j] = i;
            is[j] = 1;
        }
    }
    int n;
    int ret = scanf("%d", &n);
    assert(ret == 1);
    vector<int> arr;
    arr.push_back(0);
    for (int i = 1; i <= n; i++) {
        int x;
        int ret = scanf("%d", &x);
        assert(ret == 1);
        arr.push_back(x);
    }

    LL ans = 0;
    for (int i = 1; i <= n; i++) {
        set<int> bst;
        for (int j = i; j <= n; j++) {
            for (int x: pri) {
                if (x > arr[j]) break;
                if (arr[j] % x) continue;
                bst.insert(x);
            }
            ans += bst.size();
        }
    }
    printf("%lld\n", ans);
}
