#include <iostream>
#include <math.h>
#include <cstring>
#include <queue>
#include <algorithm>
#include <map>
#include <array>
#include <set>
 
using ll = long long;
constexpr int maxN = 1e2+2 + 1e6+1, maxLOG = 20, INF = 1e9+2, MOD = 998244353;
constexpr ll LLINF = 1e18;
 
using i128 = ll;
 
#define f_io() \
    std::ios::sync_with_stdio(0);
 
#ifndef ONLINE_JUDGE
#define DEBUG_H
#include "Debug.h"
#else
    #define dbgf(fmt, x)
    #define p_vi(v)
    #define dbgvi(v)
    #define dbgmi(mtx, rows)
    #define p_v(v)
    #define dbgv(v)
    #define dbgm(m)
    #define dbg(...)
    #define dbg2(...)
    #define dbgbin(n)
#endif

int n, m;
std::vector<int> adj[maxN];
 
int ds[maxN];
class DSU {
 
public:
 
    DSU(int n) {
        for(int i = 1; i <= n; i++)
            ds[i] = i; // Each "leader" points itself
    }
 
    // Find the set which 'x' belongs
    int find(int x) {
        if(ds[x] == x) return x; // Checks if the Leader is x
        
        // Set's been merged, then find the Leader of who merged
        
        // return find(ds[x]); Naive => O(n) in unbalanced trees
        return ds[x] = find(ds[x]); // "Dynamic Programming" optimization => O(logN) amortized => This optimization is called Path Compression
    }
 
    // Checks if 2 elements belongs to the same set
    bool same(int x, int y) {
        return find(x) == find(y); // Check their Leaders
    }
 
    // Union
    void merge(int x, int y) {
        ds[find(x)] = find(y); // Leader of Set which x belongs is now Leader of Set which y belongs
        // Leader of y keeps y
    }
};
 
int parent[maxN];
int tIn[maxN], tOut[maxN], timer = 0;
int up[maxN][maxLOG+1]; // Binary Lift
int depth[maxN];
void DFS(int node, int p) {
    tIn[node] = ++timer;
    up[node][0] = p;
    depth[node] = (p != -1) ? (depth[p]+1) : 0;

    for(int i = 1; i <= maxLOG && up[node][i-1] >= 0 && up[node][i-1] <= n+m; i++)
        up[node][i] = up[up[node][i-1]][i-1];
    
    for(int e : adj[node])
        if(e != p) {
            parent[e] = node;
            DFS(e, node);
        }

    tOut[node] = ++timer;
}

bool isAncestor(int a, int b) {
    return tIn[a] <= tIn[b] && tOut[a] >= tOut[b];
}

int LCA(int a, int b) {
    if (isAncestor(a, b)) return a;
    if (isAncestor(b, a)) return b;
    for (int i = maxLOG; i >= 0; i--)
        if (up[a][i] > 0 && up[a][i] <= n+m && !isAncestor(up[a][i], b))
            a = up[a][i];

    return up[a][0];
}

void preprocess(const std::vector<int>& srcs) {
    for(int i = 0; i <= n+m; i++)
        for(int p = 0; p <= maxLOG; p++)
            up[i][p] = -1;

    for(int src: srcs) {
        depth[src] = 0;
        DFS(src, -1);
    }
}

std::vector<int> getPath(int src, int target) {
    std::vector<int> path;
    std::vector<int> path2;
    int lca = LCA(src, target);

    for (int tracker = src; tracker != lca; tracker = parent[tracker])
        path.push_back(tracker);

    for (int tracker = target; tracker != lca; tracker = parent[tracker])
        path2.push_back(tracker);

    path.push_back(lca);
    std::reverse(path2.begin(), path2.end());
    path.insert(path.end(), path2.begin(), path2.end());

    return path;
}

bool seen[maxN];

int main() {
    scanf("%d%d", &n, &m);
    
    DSU dsu = DSU(n+m+1);
    for(int i = 0; i < n; i++) {
        int ni;
        scanf("%d", &ni);
        
        int a;
        while(ni--) {
            scanf("%d", &a);
            if(dsu.find(i+1) == dsu.find(a+n)) continue;
            dsu.merge(i+1, a+n);
            adj[i+1].push_back(a+n);
            adj[a+n].push_back(i+1);
            //dbg(i+1, a+n);
        }
    }
    
    std::vector<int> srcs;
    for(int i = 1; i <= n+m; i++)
        if(!seen[dsu.find(i)]) {
            seen[dsu.find(i)] = true;
            srcs.push_back(i);
        }

    preprocess(srcs);

    int q;
    scanf("%d", &q);
    int a, b;
    while(q--) {
        scanf("%d%d", &a, &b);
        a += n;
        b += n;
        if(!dsu.same(a, b)) { puts("-1"); continue; }
        
        std::vector<int> path = getPath(a, b);
        printf("%d\n", path.size()/2+1);
        for(int node : path)
            printf("%d ", node - (node > n)*n);
        putchar('\n');
    }
    
 
    return 0;
}