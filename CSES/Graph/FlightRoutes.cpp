#include <stdio.h>
#include <vector>
#include <queue>

#define ll long long

#define INF 0x3f3f3f3f3f3f3fLL
#define PQ std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> 
#define PQLL std::priority_queue<ll> 


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

    PQLL dist[100001];
    void Dijkstra(int k) {
        
        PQ pq = PQ();
        pq.push({1, 0});

        while(!pq.empty()) {
            auto node = pq.top();
            pq.pop();

            for(auto e : this->adj[node.v]) {
                if(dist[e.v].size() < k) {  // Save the k shortest distances
                    pq.push({e.v, node.w + e.w});
                    dist[e.v].push(node.w + e.w);
                }
                else if(dist[e.v].top() > node.w + e.w) { // Given the k shortest distances, if found a shortest distance smaller than the bigger one, then update the k distances 
                    dist[e.v].pop();
                    dist[e.v].push(node.w + e.w);
                    pq.push({e.v, node.w + e.w});
                }
            }
        }
        
    }
    

public:

    void FlightRoutes(int k) {
        this->Dijkstra(k);

        std::vector<ll> dists = std::vector<ll>();
        while(!dist[this->v-1].empty()) {
            dists.push_back(dist[this->v-1].top());
            dist[this->v-1].pop();
        }

        for(int i = dists.size() - 1; i >= 0; i--)
            printf("%lli ", dists[i]);
    }
};


int main() {

    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);

    Graph graph = Graph(n+1);

    int a, b, w;
    for(int i = 0; i < m; i++) {
        scanf("%d%d%d", &a, &b, &w);
        graph.AddEdge(a, b, w);
    }

    graph.FlightRoutes(k);



    return 0;
}