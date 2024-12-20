#include <stdio.h>
#include <vector>

class Graph {
    int v;

    std::vector<int> adj[100001];

public:

    Graph(int v): v(v) {};

    void AddEdge(int a, int b) {
        this->adj[a].push_back(b);
    }

private:

    int parent[100001];
    // Returs cycle source if finds a cycle, otherwise 0
    int DFS(int node, bool visited[100001], bool onStack[100001]) {
        if(visited[node]) return 0;
        visited[node] = true;
        onStack[node] = true;

        for(int e : this->adj[node]) {
            parent[e] = node;
            int cycle = DFS(e, visited, onStack);
            if(cycle) return cycle;
            if(onStack[e]) return e;
        }

        onStack[node] = false;
        return 0;
    }

public:

    void RoundTrip() {
        bool visited[100001] = {false}, onStack[100001] = {false};
        for(int i = 1; i < this->v; i++) {
            if(visited[i]) continue;
            int cycle = DFS(i, visited, onStack); 
            if(cycle) {
                int tracker = parent[cycle];
                std::vector<int> path = std::vector<int>();
                path.push_back(cycle);
                while(tracker != cycle) {
                    path.push_back(tracker);
                    tracker = parent[tracker];
                }
                path.push_back(cycle);

                printf("%d\n", path.size());
                for(int i = path.size()-1; i >= 0; i--)
                    printf("%d ", path[i]);

                return;
            }
        }

        puts("IMPOSSIBLE");
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

    graph.RoundTrip();

    return 0;
}