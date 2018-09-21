#include <algorithm>
#include <cassert>
#include <climits>
#include <cstdio>
#include <cstring>
#include <iterator>
#include <numeric>
#include <set>
#include <utility>

constexpr int maxn = 100000;

char s[maxn + 1];
int c1[maxn + 1], c2[maxn + 1];
int ans[maxn + 1];

int main() {
    int n;
    int ret = std::scanf("%d", &n);
    assert(ret == 1);
    assert(1 <= n && n <= maxn);

    ret = std::scanf("%100000s", s);
    assert(ret == 1);
    assert((int) std::strlen(s) == n);
    assert(std::all_of(s, s + n, [](char c){ return c >= '0' && c <= '2'; }));

    std::reverse(s, s + n);
        
    for (int i = 0; i < n; i++) {
        c1[i + 1] = c1[i] + 2 * (s[i] == '1') - 1;
        c2[i + 1] = c2[i] + 2 * (s[i] == '2') - 1;
    }

    std::set<std::pair<int, int>> set[2];

    for (int i = 1; i <= n; i++) {
        if (c1[i] >= 0) {
            // answer += 111...1
            ans[0] += 1;
            ans[c1[i]] -= 1;
        } else if (c2[i] >= 0) {
            // answer += 222...2
            ans[0] += 2;
            ans[c2[i]] -= 2;
        } else if (i + c1[i] + c2[i] > 0 && i % 2 == 1) {
            // answer += 0, 1, or 2 (hard)
            int a = 2;

            auto it1 = set[1].lower_bound(std::make_pair(c1[i], INT_MIN));
            if (it1 != set[1].end() && it1->second >= c2[i])
                a = 1;

            auto it0 = set[0].lower_bound(std::make_pair(c1[i], INT_MIN));
            if (it0 != set[0].end() && it0->second >= c2[i])
                a = 0;

            ans[0] += a;
            ans[1] -= a;
        }

        if (i < n && i % 2 == 0 && c1[i] <= 0 && c2[i] <= 0 && s[i] < '2') {
            int t = s[i] - '0'; // t == 0 || t == 1
            // add (c1[i + 1], c2[i + 1]) to set[t]
            auto it = set[t].emplace(c1[i + 1], c2[i + 1]).first;
            if (std::next(it) != set[t].end() &&
                    std::next(it)->second >= it->second) {
                set[t].erase(it);
            } else {
                while (it != set[t].begin() &&
                       std::prev(it)->second <= it->second)
                    set[t].erase(std::prev(it));
            }
        }
    }

    std::partial_sum(ans, ans + n + 1, ans);
    for (int i = 0; i < n; i++) {
        ans[i + 1] += ans[i] / 10;
        ans[i] %= 10;
    }

    bool skip = true;
    for (int i = n - 1; i >= 0; i--) {
        if (skip && i && !ans[i])
            continue;
        skip = false;
        putchar('0' + ans[i]);
    }
    putchar('\n');
}
