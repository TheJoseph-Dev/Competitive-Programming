#include <stdio.h>
#include <vector>
#include <set>

constexpr int maxN = 1e5+1;

class Graph {

    int v;
    std::set<int> adj[maxN];

public:

    Graph(int v) : v(v) {}

    void AddEdge(int a, int b) {
        this->adj[a].insert(b);
        this->adj[b].insert(a);
    }

private:

    // In an undirected graph, the necessary condition is that all vertices have an even degree
    // That is, all vertices must have an even amount of edges connecting to them
    bool isEulerian() {
        for(int i = 0; i < this->v; i++)
            if(this->adj[i].size()&1) return false;

        return true;
    }


    void EulerianCircuit(int target, std::vector<int>& circuit) {
        std::vector<int> stk = std::vector<int>();
        stk.push_back(target);
    
        while(!stk.empty()) {
            int node = stk.back();
            if(this->adj[node].empty()) { 
                circuit.push_back(node);
                stk.pop_back();
                continue;
            }

            int nextNode = *this->adj[node].begin();
            this->adj[node].erase(this->adj[node].begin());
            this->adj[nextNode].erase(this->adj[nextNode].find(node));
            stk.push_back(nextNode);
        }
    }

public:

    void PrintEulerianCircuit() {
        if(!this->isEulerian()) {
            puts("IMPOSSIBLE");
            return;
        }
        
        std::vector<int> circuit;
        EulerianCircuit(0, circuit);

        for(int i = 0; i < this->v; i++) if(!this->adj[i].empty()) { puts("IMPOSSIBLE"); return; } // Graph not fully connected
        for(int node : circuit) printf("%d ", node+1);
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

    graph.PrintEulerianCircuit();

    return 0;
}