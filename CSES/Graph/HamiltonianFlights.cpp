#include <stdio.h>

constexpr int maxN = 21, MOD = 1e9+7;

// Travelling Salesman (like) problem
class TSP {

    int v;
    int graph[maxN][maxN] = {{0}};

    int maxMask;

public:

    TSP(int v) : v(v), maxMask((1<<v)-1) {}

    void AddEdge(int a, int b) {
        this->graph[a][b]++;
    }

private:

    int dp[maxN][(1<<(maxN-1))];
    int DFS(int node, int visited, int target) {
        if(node == target) return (visited == maxMask);

        if(dp[node][visited] != -1) return dp[node][visited];

        int count  = 0;
        for(int i = 0; i < this->v; i++) {
            if(this->graph[node][i] && (visited&(1<<i)) == 0)
                count = (count + ((graph[node][i]*((long long)this->DFS(i, visited | (1 << i), target) % MOD))%MOD))%MOD;
        }

        return dp[node][visited] = count;
    }

public:

    int CountPaths(int src, int target) {
        for(int i = 0; i < this->v; i++)
            for(int j = 0; j < (1<<(maxN-1)); j++)
                dp[i][j] = -1;
        
        return DFS(src, 1, target);
    }

};

int main() {

    int n, m;
    scanf("%d%d", &n, &m);

    TSP tsp = TSP(n);

    int a, b;
    for(int i = 0; i < m; i++) {
        scanf("%d%d", &a, &b);
        tsp.AddEdge(a-1, b-1);
    }

    printf("%d\n", tsp.CountPaths(0, n-1));

    return 0;
}