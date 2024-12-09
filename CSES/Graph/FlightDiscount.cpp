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
        bool hasDiscount;

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

    ll dist[100001][2];
    void Dijkstra() {
        bool visited[100001][2] = {{false}};
        for(int i = 2; i < this->v; i++) dist[i][0] = dist[i][1] = INF;
        PQ q = PQ();
        q.push({1, 0, true});
        dist[1][1] = dist[1][0] = 0;

        while(!q.empty()) {
            auto node = q.top();
            q.pop();

            if(visited[node.v][node.hasDiscount]) continue;
            visited[node.v][node.hasDiscount] = true;

            for(auto e : this->adj[node.v]) {
                if(dist[e.v][node.hasDiscount] > node.w + e.w) {
                    dist[e.v][node.hasDiscount] = node.w + e.w;
                    q.push({ e.v, dist[e.v][node.hasDiscount], node.hasDiscount });
                }

                if(!node.hasDiscount || dist[e.v][0] <= node.w + e.w/2) continue;
                dist[e.v][0] = node.w + e.w/2;
                q.push({ e.v, dist[e.v][0], false });
            }
        }
    }
    

public:

    void CheapestRoute() {
        this->Dijkstra();
        printf("%lli\n", std::min(dist[this->v-1][1], dist[this->v-1][0]));
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

    graph.CheapestRoute();

    return 0;
}