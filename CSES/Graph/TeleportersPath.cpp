#include <stdio.h>
#include <vector>

constexpr int maxN = 1e5+1;

class Graph {

    int v;
    std::vector<int> adj[maxN];

public:

    Graph(int v) : v(v) {}

    void AddEdge(int a, int b) {
        this->adj[a].push_back(b);
    }

private:

    // In a directed graph, the necessary condition is that all vertices have an even degree or exactly 2 of them have odd degree
    // In the second case, the odd degree ones must be the start and finish nodes
    bool isEulerian() {
        int odd = 0;
        for(int i = 0; i < this->v; i++)
            odd += (this->adj[i].size()&1);

        return odd == 0 || odd == 2;
    }

    std::pair<int, int> GetEndpoints() {
        int nodes[3], n = 0;
        for(int i = 0; i < this->v; i++)
            if(this->adj[i].size()&1) nodes[n++] = i;
        
        if(n == 2) return {nodes[0], nodes[1]};
        return {0, 0};
    }

    void EulerianPath(int src, int target, std::vector<int>& path) {
        std::vector<int> stk = std::vector<int>();
        stk.push_back(src);
    
        while(!stk.empty()) {
            int node = stk.back();
            if(this->adj[node].empty()) { 
                path.push_back(node);
                stk.pop_back();
                continue;
            }

            int nextNode = this->adj[node].back();
            this->adj[node].pop_back();
            stk.push_back(nextNode);
        }
    }

public:

    void PrintEulerianPath() {
        if(!this->isEulerian()) {
            puts("IMPOSSIBLE");
            return;
        }
        
        auto endpoints = this->GetEndpoints();
        std::vector<int> path;
        EulerianPath(endpoints.first, endpoints.second, path);

        for(int i = 0; i < this->v; i++) if(!this->adj[i].empty()) { puts("IMPOSSIBLE"); return; } // Graph not fully connected
        for(int node : path) printf("%d ", node+1);
    }

};

int main() {

    int n, m;
    scanf("%d%d", &n, &m);

    Graph graph = Graph(n);

    int a, b;
    for(int i = 0; i < m; i++) {
        scanf("%d%d", &a, &b);
        graph.AddEdge(a-1, b-1);
    }

    graph.PrintEulerianPath();

    return 0;
}