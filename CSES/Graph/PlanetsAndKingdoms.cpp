#include <stdio.h>
#include <vector>

class Graph {
    int v;
    std::vector<int> adj[100001], rAdj[100001];
    
public:
    Graph(int v): v(v) {}
    
    void AddEdge(int a, int b) {
        adj[a].push_back(b);
        rAdj[b].push_back(a);
    }

private:

    void DFS(int node, bool visited[100001], std::vector<int>& postOrder) {
        visited[node] = true;
        for (int e : adj[node]) {
            if (visited[e]) continue;
            DFS(e, visited, postOrder);
        }

        postOrder.push_back(node);
    }

    // Reverse DFS to assign kingdoms
    void rDFS(int node, int kingdom, int kingdoms[100001], bool visited[100001]) {
        visited[node] = true;
        kingdoms[node] = kingdom;
        for (int e : rAdj[node]) {
            if (visited[e]) continue;
            rDFS(e, kingdom, kingdoms, visited);
        }
    }

public:
    void Kingdoms() {
        int kingdoms[100001];
        bool visited[2][100001];
        
        for (int i = 1; i < this->v; i++)
            visited[0][i] = visited[1][i] = false;

        std::vector<int> postOrder;

        // Get post order
        for (int i = 1; i < v; i++)
            if (!visited[0][i]) 
                DFS(i, visited[0], postOrder);

        int kingdom = 1;
        while (!postOrder.empty()) {
            int node = postOrder.back();
            postOrder.pop_back();
            
            if (visited[1][node]) continue;

            rDFS(node, kingdom, kingdoms, visited[1]);
            kingdom++;
        }

        printf("%d\n", kingdom - 1);
        for (int i = 1; i < v; i++)
            printf("%d ", kingdoms[i]);
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

    graph.Kingdoms();

    return 0;
}