#include <stdio.h>
#include <vector>
#include <set>
#include <algorithm>
constexpr int maxN = 2e5+5;
int n, m;
std::vector<int> adj[maxN];
int tin[maxN], low[maxN], time = 1;
std::set<int> artpt;
void dfs(int node, int parent) {
    tin[node] = low[node] = time++;
    int deg = 0;
    for(int e : adj[node]) {
        if(e == parent) continue; // Only works for simple graphs
        if(tin[e]) { // Back edge
            low[node] = std::min({low[node], tin[e]});
            continue;
        }
        // Tree edge
        dfs(e, node);
        deg++;
        low[node] = std::min({low[node], low[e]});
        if(low[e] >= tin[node] && parent != -1) artpt.insert(node); // if low[e] > tin[node], then node <=> e is a bridge
    }
    if(parent == -1 && deg > 1) artpt.insert(node); // No special root case for bridges
}

int main() {
    scanf("%d%d", &n, &m);
    int a, b;
    for(int i = 0; i < m; i++) {
        scanf("%d%d", &a, &b);
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    dfs(1, -1);
    printf("%d\n", artpt.size());
    for(int v : artpt) printf("%d ", v);
    return 0;
}