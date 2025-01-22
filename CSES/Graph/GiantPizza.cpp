/*
    2-SAT
    https://cp-algorithms.com/graph/2SAT.html
    
    The trick here is to interpret each line as a logic predicate (Normal Disjunctive Form (FND))
    Ex: (a + ~b) * (c + ~a)
    Then you can transform each disjunction as an implication and construct a directed graph.
    If a contradiction is found in a SCC, then it's unsatisfiable
*/

#include <stdio.h>
#include <vector>

constexpr int maxN = 2e5+1;

class Graph {

    int v;
    std::vector<int> adj[maxN], rAdj[maxN];

public:

    Graph(int v) : v(v) {};

    void AddEdge(int a, int b) {
        this->adj[a].push_back(b);
        this->rAdj[b].push_back(a);
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

public:

    void SAT() {
        int nodes[maxN];
        bool visited[2][maxN] = {{false}};
        
        std::vector<int> postOrder = std::vector<int>();
 
        // Get post order
        for (int i = 0; i < this->v; i++)
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

        for(int i = 0; i < this->v/2; i++)
            if(nodes[i] == nodes[i+this->v/2]) { puts("IMPOSSIBLE"); return; }
        
        for(int i = 0; i < this->v/2; i++)
            if(nodes[i] < nodes[i + this->v/2]) printf("- ");
            else printf("+ ");
    }

};

int main() {

    int n, m;
    scanf("%d%d", &n, &m);

    Graph impGraph = Graph(2*m);

    int x1, x2;
    char p1, p2;
    for(int i = 0; i < n; i++) {
        scanf(" %c%d %c%d", &p1, &x1, &p2, &x2);
        impGraph.AddEdge(x1 + m*(p1 == '+') - 1, x2 + m*(p2 != '+') - 1);
        impGraph.AddEdge(x2 + m*(p2 == '+') - 1, x1 + m*(p1 != '+') - 1);
    }

    impGraph.SAT();

    return 0;
}