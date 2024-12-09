#include <stdio.h>
#include <vector>
#include <queue>

#define INF 0x3f3f3f3f3f3f3fLL

#define ll long long

class Graph {

    struct Edge {
        int v;
        int u;
        ll w;

        bool operator>(const Edge& other) const {
            return this->w > other.w;
        }
    };

    int v;
    std::vector<Edge> edges;
    std::vector<int> adj[2501];

public:

    Graph(int v): v(v), edges(std::vector<Edge>()) {}
    
    void AddEdge(int a, int b, int w) {
        edges.push_back({a, b, w});
        adj[a].push_back(b);
    }

private:

    bool BFS(int src) {
        bool visited[2501] = {false};
        std::queue<int> q = std::queue<int>();
        q.push(src);

        while(!q.empty()) {
            int node = q.front();
            q.pop();

            if(node == this->v) return true;

            for(int e : this->adj[node]) {
                if(visited[e]) continue;
                visited[e] = true;
                q.push(e);
            }
        }

        return false;
    }

    void RemoveTargetUnreachableEdges() {
        bool good[2501] = {false};
        good[1] = good[this->v] = true;
        for(int i = 2; i < this->v; i++)
            good[i] = this->BFS(i);

        // Remove edges which lead or start with node i
        std::vector<Edge> goodEdges = std::vector<Edge>();
        for(auto& e : this->edges)
            if(good[e.v] && good[e.u])
                goodEdges.push_back(e);
        this->edges = goodEdges;
    }

    ll BellmanFord() {
        ll dist[5001];
        for(int i = 0; i <= this->v; i++) dist[i] = -INF;
        dist[1] = 0;

        for(int i = 0; i < this->v; i++)
            for(const Edge& edge : this->edges) {
                if(dist[edge.v] == -INF || dist[edge.v] + edge.w <= dist[edge.u]) continue;
                if(i == this->v-1) return -1;
                dist[edge.u] = dist[edge.v] + edge.w;
            }

        return dist[this->v];
    }

public:

    void HighestScore() {
        this->RemoveTargetUnreachableEdges();
        printf("%lli\n", this->BellmanFord());
    }
};


int main() {

    int n, m;
    scanf("%d%d", &n, &m);

    Graph graph = Graph(n);

    int a, b, w;
    for(int i = 0; i < m; i++) {
        scanf("%d%d%d", &a, &b, &w);
        graph.AddEdge(a, b, w);
    }

    graph.HighestScore();

    return 0;
}