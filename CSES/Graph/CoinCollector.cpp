#include <stdio.h>
#include <vector>

#define ll long long
constexpr int maxN = 1e5+2;

class DAG {

    int v;
    std::vector<int> adj[maxN];
    ll coins[maxN];

public:

    DAG(int v, ll coins[maxN]) : v(v) {
        for(int i = 0; i < v; i++) this->coins[i] = coins[i];
    };

    void AddEdge(int a, int b) {
        adj[a].push_back(b);
    }


private:

    ll dp[maxN];
    ll DFS(int node) {
        if(dp[node] != -1) return dp[node];

        ll c = 0;
        for(int e : this->adj[node])
            c = std::max(c, DFS(e));

        return dp[node] = c + this->coins[node];
    }


public:

    ll GetMaxCoins() {
        for(int i = 0; i <= v; i++) this->dp[i] = -1;

        ll maxCoins = 0;
        for(int i = 1; i <= v; i++) {
            maxCoins = std::max(maxCoins, dp[i]);
            if(dp[i] != -1) continue;
            this->DFS(i);
            maxCoins = std::max(maxCoins, dp[i]);
        }

        return maxCoins;
    }
};

class Graph {

    int v;
    std::vector<int> adj[maxN], rAdj[maxN];
    int coins[maxN];

public:

    Graph(int v, int coins[maxN]) : v(v) {
        for(int i = 0; i < v; i++) this->coins[i] = coins[i];
    };

    void AddEdge(int a, int b) {
        adj[a].push_back(b);
        rAdj[b].push_back(a);
    }

private:

    void DFS(int node, bool visited[maxN], std::vector<int>& postOrder) {
        visited[node] = true;
        for (int e : adj[node]) {
            if (visited[e]) continue;
            DFS(e, visited, postOrder);
        }
 
        postOrder.push_back(node);
    }
 
    // Reverse DFS to assign scc
    void rDFS(int node, int scc, int nodes[maxN], bool visited[maxN]) {
        visited[node] = true;
        nodes[node] = scc;
        for (int e : rAdj[node]) {
            if (visited[e]) continue;
            rDFS(e, scc, nodes, visited);
        }
    }

    void GenSSC(int nodes[maxN]) {
        bool visited[2][maxN] = {{false}};
        
        std::vector<int> postOrder = std::vector<int>();
 
        // Get post order
        for (int i = 1; i <= v; i++)
            if (!visited[0][i]) 
                DFS(i, visited[0], postOrder);
 
        int scc = 1;
        while (!postOrder.empty()) {
            int node = postOrder.back();
            postOrder.pop_back();
            
            if (visited[1][node]) continue;
 
            rDFS(node, scc, nodes, visited[1]);
            scc++;
        }
    }

public:

    // Condensates the Graph by SCC, turning it into a DAG
    DAG Condensated() {
        int nodes[maxN];
        this->GenSSC(nodes);

        ll cCoins[maxN] = {0};
        int cV = 0;
        for(int i = 1; i <= v; i++)
            cCoins[nodes[i]] += this->coins[i-1], cV = std::max(cV, nodes[i]);
        
        DAG cGraph = DAG(cV+1, cCoins);
        for(int i = 1; i <= v; i++)
            for(int e : this->adj[i])
                if(nodes[i] != nodes[e])
                    cGraph.AddEdge(nodes[i], nodes[e]);

        return cGraph;
    }
};

int main() {

    int n, m;
    scanf("%d%d", &n, &m);

    int coins[maxN];
    for(int i = 0; i < n; i++)
        scanf("%d", coins+i);

    Graph oGraph = Graph(n, coins);

    int a, b;
    for(int i = 0; i < m; i++)
        scanf("%d%d", &a, &b), oGraph.AddEdge(a, b);

    DAG cGraph = oGraph.Condensated();
    printf("%lli\n", cGraph.GetMaxCoins());

    return 0;
}