#include <stdio.h>
#include <vector>

constexpr int maxN = 2e5+2;

std::vector<int> adj[maxN];

int n;
int sz[maxN];
void dfs(int node, int parent) {
    sz[node]++;
    for(int e : adj[node]) {
        if(e == parent) continue;
        dfs(e, node);
        sz[node] += sz[e];
    }
}

int reroot(int node, int parent) {
    int centroid = -1;
    bool isCentroid = true;
    for(int e : adj[node]) {
        isCentroid &= (sz[e] <= n/2);
        if(e == parent) continue;
        sz[node] -= sz[e];
        sz[e] += sz[node];
        centroid = reroot(e, node);
        sz[e] -= sz[node];
        sz[node] += sz[e];
        if(centroid+1) break;
    }

    if(isCentroid) centroid = node;
    return centroid;
}

int main() {

    scanf("%d", &n);

    int a, b;
    for(int i = 0; i < n-1; i++) {
        scanf("%d%d", &a, &b);
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    dfs(1, -1);
    int centroid = reroot(1, -1);
    printf("%d\n", centroid);

    return 0;
}