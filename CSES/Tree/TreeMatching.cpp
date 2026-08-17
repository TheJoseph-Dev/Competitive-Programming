#include <stdio.h>
#include <vector>
#include <algorithm>
#include <array>
constexpr int maxN = 2e5+4;
std::vector<int> adj[maxN];
int m = 0;
bool dfs(int node, int parent) {
    //if(adj[node].size() == 1) return true;
    int link = -1;
    for(int e : adj[node]) {
        if(e != parent)
            if(dfs(e, node)) link = e;
    }
    if(link != -1) m++;
    else return true; 
    return false;
}

int main() {

    int n;
    scanf("%d", &n);

    int a, b;
    for(int i = 0; i < n-1; i++) {
        scanf("%d%d", &a, &b);
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    dfs(1, -1);
    printf("%d\n", m);
    return 0;
}