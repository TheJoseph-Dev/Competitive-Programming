#include <stdio.h>
#include <vector>
using ll = long long;

constexpr int maxN = 2e5+5, maxLOG = 18;

ll acc[maxN];
 
int n;
std::vector<int> adj[maxN];

void AddEdge(int a, int b) {
    adj[a].push_back(b);
    adj[b].push_back(a);
}
 
int tIn[maxN], tOut[maxN], timer = 0;
int up[maxN][maxLOG+1]; // Binary Lift

void DFS(int node, int parent) {
    tIn[node] = ++timer;
    up[node][0] = parent;
    
    for(int i = 1; i <= maxLOG && up[node][i-1] >= 0 && up[node][i-1] <= n; i++)
        up[node][i] = up[up[node][i-1]][i-1];

    for(int e : adj[node])
        if(e != parent) DFS(e, node);

    tOut[node] = ++timer;
}

bool isAncestor(int a, int b) {
    return tIn[a] <= tIn[b] && tOut[a] >= tOut[b];
}

void Preprocess() {
    for(int i = 0; i < n; i++)
        for(int p = 0; p <= maxLOG; p++)
            up[i][p] = -1;

    DFS(0, -1);
}

int LCA(int a, int b) {
    if (isAncestor(a, b)) return a;
    if (isAncestor(b, a)) return b;
    for (int i = maxLOG; i >= 0; i--)
        if (up[a][i] > 0 && up[a][i] <= n && !isAncestor(up[a][i], b))
            a = up[a][i];

    return up[a][0];
}

void accumulate(int node, int parent) {
    for(int e : adj[node]) {
        if(e == parent) continue;
        accumulate(e, node);
        acc[node] += acc[e];
    }
}

int main() {

    int m;
    scanf("%d%d", &n, &m);

    int a, b;
    for(int i = 0; i < n-1; i++) {
        scanf("%d%d", &a, &b);
        AddEdge(a-1, b-1);
    }

    Preprocess();

    int cnt[maxN] = {0};
    while(m--) {
        scanf("%d%d", &a, &b);
        acc[a-1]++;
        acc[b-1]++;
        int lca = LCA(a-1, b-1);
        acc[lca] -= 2;
        cnt[lca]++;
    }

    accumulate(0, -1);

    for(int i = 0; i < n; i++) printf("%lld ", acc[i] + cnt[i]);

    return 0;
}