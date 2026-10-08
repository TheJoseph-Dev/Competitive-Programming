#include <stdio.h>
#include <vector>
#include <set>
#include <algorithm>
 
constexpr int maxN = 1e5+1;
 
int n, m;
std::set<int> adj[maxN];
 
bool isEulerian() {
    for(int i = 1; i <= n; i++)
        if(adj[i].size()&1) return false;
    return true;
}
 
std::vector<int> circuit;
 
void dfs(int node) {
    while(!adj[node].empty()) {
        int e = *adj[node].begin();
        adj[node].erase(e);
        adj[e].erase(node);
        dfs(e);
    }
    circuit.push_back(node);
}
 
void eulerian_circuit() {
    dfs(1);
}
 
int main() {
    scanf("%d%d", &n, &m);
 
    int a, b;
    for(int i = 0; i < m; i++) {
        scanf("%d%d", &a, &b);
        adj[a].insert(b);
        adj[b].insert(a);
    }
    
    if(!isEulerian()) {
        puts("IMPOSSIBLE");
        return 0;
    }
    
    eulerian_circuit();
    for(int i = 1; i <= n; i++) if(!adj[i].empty()) { puts("IMPOSSIBLE"); return 0; }
    for(int node : circuit) printf("%d ", node);
    return 0;
}