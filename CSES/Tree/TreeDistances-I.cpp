#include <stdio.h>
#include <queue>

constexpr int maxN = 2e5+1;

class Graph {

    int v;
    std::vector<int> adj[maxN];

public:

    Graph(int v) : v(v) {}

    void AddEdge(int a, int b) {
        this->adj[a].push_back(b);
        this->adj[b].push_back(a);
    }

private:


    int MaxDepth(int src, int depth[maxN]) {
        bool visited[maxN] = {false};
        std::queue<int> q;
        q.push(src);
        visited[src] = true;
        depth[src] = 0;

        int lastNode;
        while(!q.empty()) {
            int node = q.front();
            q.pop();

            for(int e : this->adj[node]) {
                if(visited[e]) continue;
                visited[e] = true;
                depth[e] = depth[node] + 1;
                q.push(e);
            }

            lastNode = node;
        }

        return lastNode;
    }

public:

    void PrintNodesLargestDistance() {
        int depth[2][maxN];
        int deepest = this->MaxDepth(0, depth[0]);
        int diameterFirstEndpoint = this->MaxDepth(deepest, depth[0]);
        int diameterSecondEndpoint = this->MaxDepth(diameterFirstEndpoint, depth[1]);

        for(int i = 0; i < this->v; i++) printf("%d ", std::max(depth[0][i], depth[1][i]));
    }

};

int main() {

    int n;
    scanf("%d", &n);

    Graph graph = Graph(n);

    int a, b;
    for(int i = 0; i < n-1; i++) {
        scanf("%d%d", &a, &b);
        graph.AddEdge(a-1, b-1);
    }

    graph.PrintNodesLargestDistance();

    return 0;
}