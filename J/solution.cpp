/**
 * For each prime calculate the number of interval that contain it.
 */
#include<bits/stdc++.h>
using namespace std;

typedef long long int LL;

const int N = 1000005;

int is[N];
vector<int> pri;
vector<int> pos[N];
int fac[N];

int main() {
    for (int i = 2; i < N; i++) {
        if (is[i]) continue;
        pri.push_back(i);
        for (int j = i; j < N; j += i) {
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


    for (int x: pri)
        pos[x].push_back(0);
    set<int> bst;
    for (int i = 1; i <= n; i++) {
        int k = arr[i];
        while (k > 1) {
            int tmp = fac[k];
            bst.insert(tmp);
            pos[tmp].push_back(i);
            while (k % tmp == 0) k /= fac[k];
        }
    }
    for (int x: pri)
        pos[x].push_back(n + 1);

    LL ans = 1LL * n * (n + 1) / 2 * bst.size();
    for (int x: bst) {
        for (int i = 1; i < (int) pos[x].size(); i++) {
            int len = pos[x][i] - pos[x][i - 1] - 1;
            ans -= 1LL * len * (len + 1) / 2;
        }
    }

    printf("%lld\n", ans);
}
