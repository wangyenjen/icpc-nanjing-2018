/**
 * Let Cherry's first choice be p1.
 * Let Chocolate's choice be b.
 * Let Cherry's second choice be p2.
 *
 * It is clear that if p1 and b are fixed,
 * p2 must be adjacent to b.
 * Therefore, it suffices to test all of b's neighbors.
 * This is O(deg(b)).
 *
 * If only p1 is fixed, it suffices to test all possible b.
 * This is O(n).
 *
 * Let b_p1 be the optimal b for p1.
 * The answer will not get greater if p1 is moved further away
 * from b_p1.
 * This halves the possible p1 by half if p1 is the centroid
 * of the tree.
 * Therefore, only O(log n) p1 are needed to test and
 * the solution is O(n log n) overall.
 */
#include <algorithm>
#include <cassert>
#include <cstdio>
#include <vector>

namespace {

constexpr int maxn = 1'000'000;

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
 * size2[v] is the size of subtree v, with unstored parent.
 *
 * If mask_centroid[v] is true, it is removed from the tree
 * for this purpose.
 */
bool mask_centroid[maxn];
int size2[maxn];

/**
 * Fills size2[] for the tree containing v.
 */
void dfs2(int v, int p) {
    size2[v] = 1;
    for (int c : adj[v])
        if (c != p && !mask_centroid[c]) {
            dfs2(c, v);
            size2[v] += size2[c];
        }
}

/**
 * Returns the deepest decedent with size2 >= limit.
 */
int dfs3(int v, int p, int limit) {
    for (int c : adj[v])
        if (c != p && !mask_centroid[c] && size2[c] >= limit)
            return dfs3(c, v, limit);
    return v;
}

/**
 * Get the centroid of the tree containing v.
 *
 * If mask_centroid[u] is true, it is removed from the tree
 * for this purpose.
 */
int get_centroid(int v) {
    assert(!mask_centroid[v]);
    dfs2(v, v);
    return dfs3(v, v, size2[v] / 2);
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

    int ans = 0;
    for (int v = 0; !mask_centroid[v]; ) {
        int p1 = get_centroid(v);
        mask_centroid[p1] = true;

        int ans2 = n;
        for (int b0 : adj[p1]) {
            int ans3 = solve1(b0, p1, get_size(p1, b0));
            if (ans2 > ans3) {
                ans2 = ans3;
                v = b0;
            }
        }
        ans = std::max(ans, ans2);
    }

    printf("%d\n", ans);
}
