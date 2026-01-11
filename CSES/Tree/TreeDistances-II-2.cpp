/*
    Let dp[u] = d1 + d2 + ... + dn
    If v -> u, and reroot the tree to v, it must shift the dp like this:
    dp[v] = (d1 + 1) + (d2 + 1) + ... + (dn + 1) + 1
    dp[v] = dp[u] + sz[u]-1 + 1
    dp[v] = dp[u] + sz[u]

    Given that sz is also rerootable, the algorithm becomes:
    1. Solve for root u
    2. Solve for any arbitrary adjacent root by:
        dp[u] -= dp[v] + sz[v]
        sz[u] -= sz[v]
        sz[v] += sz[u]
        dp[v] += dp[u] + sz[u]
*/

#include <stdio.h>
#include <vector>
using ll = long long;
constexpr int maxN = 2e5+2;
std::vector<int> adj[maxN];

ll dp[maxN], ans[maxN];
int sz[maxN];
void solve(int node, int parent) {
    sz[node]++;
    for(int e : adj[node]) {
        if(e == parent) continue;
        solve(e, node);
        sz[node] += sz[e];
        dp[node] += dp[e] + sz[e];
    }
}

void reroot(int node, int parent) {
    ans[node] = dp[node];
    for(int e : adj[node]) {
        if(e == parent) continue;
        dp[node] -= dp[e] + sz[e];
        sz[node] -= sz[e];
        sz[e] += sz[node];
        dp[e] += dp[node] + sz[node];
        reroot(e, node);
        dp[e] -= dp[node] + sz[node];
        sz[e] -= sz[node];
        sz[node] += sz[e];
        dp[node] += dp[e] + sz[e];
    }
}

int main() {

    int n;
    scanf("%d", &n);

    int a, b;
    for(int i = 0; i < n-1; i++) {
        scanf("%d%d", &a, &b);
        a--;b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    solve(0, -1);
    reroot(0, -1);

    for(int i = 0; i < n; i++) printf("%lld ", ans[i]);

    return 0;
}