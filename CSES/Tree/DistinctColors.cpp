#include <stdio.h>
#include <vector>
#include <unordered_set>

constexpr int maxN = 2e5+2;

std::vector<int> adj[maxN];
int colors[maxN];
std::unordered_set<int> dset[maxN];
int dsz[maxN];
void dfs(int node, int parent) {
    dset[node].insert(colors[node]);
    for(int e : adj[node]) {
        if(e == parent) continue;
        dfs(e, node);
        
        if (dset[node].size() < dset[e].size())
            dset[node].swap(dset[e]);
        dset[node].insert(dset[e].begin(), dset[e].end());
    }
    dsz[node] = dset[node].size();
}

int main() {
    int n;
    scanf("%d", &n);

    for(int i = 0; i < n; i++)
        scanf("%d", colors+i+1);

    int a, b;
    for(int i = 0; i < n-1; i++) {
        scanf("%d%d", &a,&b);
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    dfs(1, -1);
    for(int i = 1; i <= n; i++) printf("%d ", dsz[i]); 
}