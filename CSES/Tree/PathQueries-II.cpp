#include <stdio.h>
#include <vector>
#include <algorithm>
 
constexpr int maxN = 2e5+4;
std::vector<int> adj[maxN];
 
namespace seg {
    int tree[2 * maxN];
    int n;
 
    void build(int a[], int sz) {
        n = sz;
        for (int i = 0; i < n; ++i)
            tree[n + i] = a[i];
 
        for (int i = n - 1; i; --i)
            tree[i] = std::max(tree[i << 1], tree[i << 1 | 1]);
    }
 
    void update(int idx, int x) {
        idx += n;
        tree[idx] = x;
 
        for (idx >>= 1; idx; idx >>= 1)
            tree[idx] = std::max(tree[idx << 1], tree[idx << 1 | 1]);
    }
 
    int query(int l, int r) {
        int mx = 0; // values are >= 1
        l += n;
        r += n + 1;
        while (l < r) {
            if (l & 1) mx = std::max(mx, tree[l++]);
            if (r & 1) mx = std::max(mx, tree[--r]);
            l >>= 1; r >>= 1;
        }
        return mx;
    }
}
 
// tree size; array pos; heavy chain head; parent; hld array; vertex value; timer
int sz[maxN], idx[maxN], head[maxN], parent[maxN], hlda[maxN], vv[maxN], t = 0;
void dfs(int node, int prev = -1) {
    sz[node] = 1;
    for(int& e : adj[node]) {
        if(e == prev) continue;
        dfs(e, node);
        sz[node] += sz[e];
        // Places the heavy child in the first position of the adj. list
        // This enforces dfs to traverse the heavy path first and build the flat chain array properly
        if(sz[e] > sz[adj[node][0]] || adj[node][0] == prev) std::swap(e, adj[node][0]); 
    }
}
 
void build_hld(int node, int prev = -1) {
    idx[node] = t++;
    hlda[idx[node]] = vv[node];
    for(int e : adj[node]) {
        if(e == prev) continue;
        parent[e] = node;
        // If same chain (heavy edge) head[e] = head[node], if need new chain (light edge) head[e] = e
        head[e] = (e == adj[node][0] ? head[node] : e); 
        build_hld(e, node);
    }
}
 
void build(int root) {
    dfs(root);
    t = 0;
    head[root] = root;
    build_hld(root);
    seg::build(hlda, t);
}
 
int lca(int a, int b) {
    if(idx[a] > idx[b]) std::swap(a,b);
    return head[a] == head[b] ? a : lca(parent[head[b]], a);
}
 
int query_path(int a, int b) {
    if(idx[a] > idx[b]) std::swap(a,b);
    if(head[a] == head[b]) return seg::query(idx[a], idx[b]);
    return std::max(seg::query(idx[head[b]], idx[b]), query_path(a, parent[head[b]])); // min, max, +, ...
    // For path: seg::query(idx[head[b]] + 1, idx[b]); seg::query(idx[a] + 1, idx[b])
}
 
int main() {
    int n, q;
    scanf("%d%d", &n, &q);
    for(int i = 0; i < n; i++) scanf("%d", vv+i+1);
 
    int a, b;
    for(int i = 0; i < n-1; i++) {
        scanf("%d%d", &a, &b);
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
 
    build(1);
 
    int t;
    while(q--) {
        scanf("%d%d%d", &t, &a, &b);
        if(t == 2) printf("%d ", query_path(a, b));
        else seg::update(idx[a], b);
    }
}