#include <stdio.h>
#include <vector>
#include <queue>

class Graph {

    int v;
    std::vector<std::vector<int>> adj;

public:

    Graph(int v): v(v), adj(std::vector<std::vector<int>>(v)) {}
    
    void AddEdge(int a, int b) {
        adj[a].push_back(b);
        adj[b].push_back(a);
    }


    void ShortestPath() {
        std::queue<int> q = std::queue<int>();
        q.push(1);

        int parent[200001];
        bool visited[200001] = {false};

        while(!q.empty()) {
            int node = q.front();
            q.pop();
            
            for(auto e : this->adj[node]) {
                if(visited[e]) continue;
                visited[e] = true;
                parent[e] = node;
                q.push(e);
            }
        }

        if(!visited[this->v-1]) { puts("IMPOSSIBLE"); return; }
        std::vector<int> path = std::vector<int>();
        path.push_back(this->v-1);
        int tracer = this->v-1;
        while(tracer != 1) {
            path.push_back(parent[tracer]);
            tracer = parent[tracer];
        }

        printf("%d\n", path.size());
        for(int i = path.size()-1; i >= 0; i--)
            printf("%d ", path[i]);
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

    graph.ShortestPath();

    return 0;
}