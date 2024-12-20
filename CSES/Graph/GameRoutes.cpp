#include <stdio.h>
#include <vector>

#define MOD 1000000007

class Graph {
    int v;

    std::vector<int> adj[100001];

public:

    Graph(int v): v(v) {};

    void AddEdge(int a, int b) {
        this->adj[a].push_back(b);
    }

private:

    int dp[100001];
    int countRoutes(int node) {
        if(node == this->v-1) return 1;
        if(dp[node] != -1) return dp[node];

        int count = 0;
        for(int e : this->adj[node])
            count = ((count%MOD) + (countRoutes(e)%MOD))%MOD;

        return dp[node] = count;
    }

public:

    int GameRoutes() {
        for(int i = 0; i < v; i++) dp[i] = -1;
        return countRoutes(1);
    }
};

int main() {

    int n, m;
    scanf("%d%d", &n, &m);

    Graph graph = Graph(n+1);

    int a, b;
    for(int i = 0; i < m; i++) {
        scanf("%d%d", &a, &b);
        graph.AddEdge(a, b);
    }

    printf("%d\n", graph.GameRoutes());

    return 0;
}