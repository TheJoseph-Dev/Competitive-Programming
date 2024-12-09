#include <stdio.h>
#include <vector>
#include <queue>
#include <functional>

#define INF 0x3f3f3f3f3f3f3fLL
#define PQ std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> 

#define ll long long

class Graph {

    struct Edge {
        int v;
        ll w;

        bool operator>(const Edge& other) const {
            return this->w > other.w;
        }
    };

    int v;
    std::vector<std::vector<Edge>> adj;

public:

    Graph(int v): v(v), adj(std::vector<std::vector<Edge>>(v)) {}
    
    void AddEdge(int a, int b, int w) {
        adj[a].push_back({b, w});
    }

private:

    ll dist[100001];
    void Dijkstra() {
        bool visited[100001] = {false};
        for(int i = 2; i < this->v; i++) dist[i] = INF;
        PQ q = PQ();
        q.push({1, 0});
        dist[1] = 0;

        while(!q.empty()) {
            auto node = q.top();
            q.pop();

            if(visited[node.v]) continue;
            visited[node.v] = true;

            for(auto e : this->adj[node.v])
                q.push({e.v, dist[e.v] = std::min(dist[e.v], dist[node.v] + e.w) });
        }
    }
    

public:

    void ShortestRoutes() {
        this->Dijkstra();
        for(int i = 1; i < this->v; i++)
            printf("%lli ", dist[i]);
    }
};


int main() {

    int n, m;
    scanf("%d%d", &n, &m);

    Graph graph = Graph(n+1);

    int a, b, w;
    for(int i = 0; i < m; i++) {
        scanf("%d%d%d", &a, &b, &w);
        graph.AddEdge(a, b, w);
    }

    graph.ShortestRoutes();

    return 0;
}