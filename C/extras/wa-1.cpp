/**
 * Choose centroid for p1.
 *
 * Counterexample:
 *
 * [a] \
 * [a] - 1 - 2 - [b]
 * [a] /
 *
 * [1] -> Lose max((a + 1) / 2, (b + 2) / 2)
 * [2] -> Lose max(2 * a, (b + 1) / 2)
 *
 * For [2] to be the only centroid,
 * 3 * a + 1 = b
 *
 * Take a=4 b=13, then [1]=7, [2]=8
 */
#include <algorithm>
#include <cassert>
#include <cstdio>
#include <vector>

namespace {

constexpr int maxn = 100'000;

/**
 * The adjacency list of the tree.
 */
std::vector<int> adj[maxn];

/**
 * size[v] is the size of subtree v,
 * assuming parent[v] is the parent of v.
 */
int parent[maxn], size[maxn];

/**
 * Fills parent[] and size[].
 */
void dfs(int v, int p) {
    size[v] = 1;
    parent[v] = p;
    for (int c : adj[v])
        if (c != p) {
            dfs(c, v);
            size[v] += size[c];
        }
}

/**
 * Returns the size of subtree v, assuming p is the parent.
 *
 * This also assumes size[0] == n.
 */
int get_size(int v, int p) {
    return (p == parent[v]) ? size[v] : size[0] - size[p];
}

/**
 * `solve1(b0, p1, get_size(p1, b0))` returns the answer
 * if Cherry chose p1 and Chocolate can only choose from
 * subtree b0.
 */
int solve1(int b, int bp, int p1size) {
    int ans = 0;
    for (int p2 : adj[b])
        if (p2 == bp)
            ans = std::max(ans, get_size(p2, b));
        else
            ans = std::max(ans, get_size(p2, b) + p1size);

    for (int p2 : adj[b])
        if (p2 != bp)
            ans = std::min(ans, solve1(p2, b, p1size));
    return ans;
}

/**
 * Returns the deepest decedent with size >= limit.
 */
int dfs3(int v, int p, int limit) {
    for (int c : adj[v])
        if (c != p && size[c] >= limit)
            return dfs3(c, v, limit);
    return v;
}

/**
 * Get all centroids of the tree.
 */
std::vector<int> get_centroids() {
    int v = dfs3(0, 0, (size[0] + 1) / 2);
    if (size[v] * 2 == size[0])
        return {v, parent[v]};
    else
        return {v};
}

} // namespace {

int main() {
    int n;
    int ret = std::scanf("%d", &n);
    assert(ret == 1);
    assert(3 <= n && n <= maxn);

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        ret = scanf("%d%d", &u, &v);
        assert(ret == 2);
        assert(1 <= u && u <= n);
        assert(1 <= v && v <= n);
        u--, v--;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs(0, 0);

    std::vector<int> centroids = get_centroids();

    int ans = 0;
    for (int p1 : get_centroids()) {
        int ans2 = n;
        for (int b0 : adj[p1])
            ans2 = std::min(ans2, solve1(b0, p1, get_size(p1, b0)));
        ans = std::max(ans, ans2);
    }

    printf("%d\n", ans);
}
