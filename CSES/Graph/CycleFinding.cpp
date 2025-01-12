#include <stdio.h>
#include <vector>

#define ll long long
constexpr int maxN = 2501;
constexpr ll INF = 0x3f3f3f3f3f3f3fLL;

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

public:

    Graph(int v): v(v), edges(std::vector<Edge>()) {}
    
    void AddEdge(int a, int b, int w) {
        edges.push_back({a, b, w});
    }

private:

    void BellmanFord() {
        int parent[maxN] = {0};
        ll dist[maxN];
        for(int i = 0; i <= this->v; i++) dist[i] = INF;
        dist[1] = 0;

        int cycleSrc = 0;
        for(int i = 0; i <= this->v; i++) {
            cycleSrc = 0;
            for(const Edge& edge : this->edges) {
                if(dist[edge.v] + edge.w >= dist[edge.u]) continue;
                parent[edge.u] = edge.v;
                dist[edge.u] = dist[edge.v] + edge.w;
                cycleSrc = edge.u;
            }
        }

        if(cycleSrc == 0) { puts("NO"); return; } 
        puts("YES");

        for(int i = 0; i < v; i++) cycleSrc = parent[cycleSrc];

        std::vector<int> path = std::vector<int>();
        
        int tracker = parent[cycleSrc];
        while(tracker != cycleSrc)
            path.push_back(tracker), tracker = parent[tracker];
        
        printf("%d ", cycleSrc);
        for(int i = path.size()-1; i >= 0; i--)
            printf("%d ", path[i]);
        printf("%d ", cycleSrc);
    }

public:

    void FindNegativeCycle() {
        this->BellmanFord();
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

    graph.FindNegativeCycle();

    return 0;
}