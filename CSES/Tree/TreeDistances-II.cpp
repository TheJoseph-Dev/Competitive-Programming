#include <stdio.h>
#include <vector>

constexpr int maxN = 2e5+1;

std::vector<int> adj[maxN];

// DP
long long sDist[maxN] = {0};
int subtree[maxN] = {0}; 

void rootDFS(int node = 1, int parent = 0, long long depth = 0) {
    sDist[1] += depth; // Compute the root sum
    subtree[node] = 1;
    for(int e : adj[node]) { 
        if(e == parent) continue;
        rootDFS(e, node, depth+1);
        subtree[node] += subtree[e]; 
    }

}

// Reroot the tree to each node offseting the sum based on the subtrees
void sumDistances(int n, int node = 1, int parent = 0) {
    for(int e : adj[node]) {
        if(e == parent) continue;
        sDist[e] = sDist[node] + n - 2*subtree[e];

        sumDistances(n, e, node);
    }
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

    rootDFS();
    sumDistances(n);

    for(int i = 1; i <= n; i++) printf("%lld ", sDist[i]);

    return 0;
}