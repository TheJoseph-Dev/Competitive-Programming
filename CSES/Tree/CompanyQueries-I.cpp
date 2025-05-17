#include <stdio.h>
#include <vector>

constexpr int maxN = 2e5+5, maxLOG = 18;

std::vector<int> adj[maxN];
int up[maxN][maxLOG+1];

void dfs(int node, int parent) {
    up[node][0] = parent;

    for(int e : adj[node])
        if(e != parent) dfs(e, node);

}

void preprocess(int n) {
    for(int i = 1; i <= n; i++)
        for(int p = 1; p <= maxLOG; p++)
            up[i][p] = -1;

    dfs(1, -1);

    for(int i = 1; i <= n; i++)
        for(int p = 1; p <= maxLOG && up[i][p-1] > 0; p++)
            up[i][p] = up[up[i][p-1]][p-1];
}

int main() {

    int n, q;
    scanf("%d%d", &n, &q);

    int boss;
    for(int i = 0; i < n-1; i++) {
        scanf("%d", &boss);
        adj[boss].push_back(i+2);
        adj[i+2].push_back(boss);
    }

    preprocess(n);

    int employee, k;
    while(q--) {
        scanf("%d%d", &employee, &k);

        int kBoss = employee;
        for(int p = maxLOG; p >= 0 && kBoss > 0; p--)
            if(k&(1<<p)) kBoss = up[kBoss][p];

        printf("%d\n", kBoss);
    }

    return 0;
}