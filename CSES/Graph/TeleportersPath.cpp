#include <iostream>
#include <algorithm>
#include <vector>
constexpr int maxN = 1e5+4;
int n, m;
std::vector<int> adj[maxN];
std::vector<int> path;
void dfs(int node) {
    while(!adj[node].empty()) {
        int e = adj[node].back();
        adj[node].pop_back();
        dfs(e);
    }
    path.push_back(node);    
}
 
bool directed_euler_trail() {
    static int indeg[maxN];
    for(int i = 1; i <= n; i++)
        for(int e : adj[i]) indeg[e]++;
    int start = -1, end = -1;
    for(int i = 1; i <= n; i++) {
        int outdeg = adj[i].size();
        if(outdeg == indeg[i]) continue;
        if(outdeg == indeg[i]+1) {
            if(start != -1) return false;
            start = i;
        }
        if(indeg[i] == outdeg+1) {
            if(end != -1) return false;
            end = i;
        }
    }
    
    if(start == -1 || end == -1) return false;
    
    dfs(start);
    std::reverse(path.begin(), path.end());
    return true;
}
 
 
int main() {
    scanf("%d%d", &n, &m);
    int a, b;
    for(int i = 0; i < m; i++) {
        scanf("%d%d", &a, &b);
        adj[a].push_back(b);
    }
    
    if(directed_euler_trail() && path.size() == m+1 && path.back() == n) for(int v : path) printf("%d ", v);
    else puts("IMPOSSIBLE");
    return 0;
}