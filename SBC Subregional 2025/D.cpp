#include <stdio.h>
#include <algorithm>
#include <vector>
#include <set>
constexpr int maxN = 21;
constexpr int maxMsk = (1<<maxN);
int dp[maxMsk];
constexpr std::pair<int, int> p[22] = {{1,1},{1,2},{1,3},{1,4},{1,5},{1,6}, {2,2},{2,3},{2,4},{2,5},{2,6}, {3,3},{3,4},{3,5},{3,6}, {4,4},{4,5},{4,6}, {5,5},{5,6}, {6,6}};
int mp[6][6];

void dfs(int node, int g[7][7], bool seen[7]) {
    seen[node] = true;
    for(int e = 1; e <= 6; e++)
        if(g[node][e] && !seen[e])
            dfs(e, g, seen);
}
bool hasEulerTrail(int mask) {
    int deg[7] = {};
    bool seen[7] = {};
    int g[7][7] = {};
    for(int b = 0; b < 21; b++)
        if(mask&(1<<b)) {
            int u = p[b].first, v = p[b].second;
            deg[u]++; deg[v]++;
            g[u][v] = g[v][u] = 1;
        }
    
    int oc = 0, start = 0;
    for(int i = 1; i <= 6; i++) { if(deg[i]&1) oc++; if(deg[i]) start = i; }
    if(oc != 0 && oc != 2) return false;
    if(!start) return false;
    dfs(start, g, seen);
    for(int i = 1; i <= 6; i++)
        if(deg[i] && !seen[i]) return false;
    
    return true;
}

int main() {
    int t, n;
    scanf("%d", &t);
    
    for(int i = 0, idx = 0; i < 6; i++)
        for(int j = i; j < 6; j++, idx++)
            mp[i][j] = idx;
    
    //printf("%d\n", hasEulerTrail((1<<6) )); return 0;
    for(int msk = 0; msk < maxMsk; msk++) dp[msk] = hasEulerTrail(msk);
    
    for(int b = 0; b < maxN; b++)
        for(int msk = 0; msk < maxMsk; msk++)
            if(msk&(1<<b)) dp[msk] += dp[msk^(1<<b)];
        
    while(t--) {
        scanf("%d", &n);
        int msk = 0;
        int a, b;
        for(int i = 0; i < n; i++) {
            scanf("%d%d", &a, &b);
            msk |= (1<<mp[a-1][b-1]);
        }
        printf("%d\n", dp[msk]);
    }
    return 0;
}