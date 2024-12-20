#include <stdio.h>
#include <queue>
 
#define ll long long
#define INF 0x3f3f3f3f3f3f
#define MOD 1000000007
 
struct Node {
    int v;
    ll d;
 
    bool operator>(const Node& other) const {
        return this->d > other.d;
    }
};
 
typedef std::priority_queue<Node, std::vector<Node>, std::greater<Node>> PQ;
 
class Graph {
 
    int v;
    std::vector<Node> adj[100001];
 
public:
 
    Graph(int v): v(v) {};
 
    void AddEdge(int a, int b, int w) {
        this->adj[a].push_back({b, w});
    }
 
private:
 
    struct GraphData {
        ll minPrice;
        int paths, minNodes, maxNodes;
    };
 
    ll price[100001];
    int minNodes[100001], maxNodes[100001], ways[100001];
    GraphData Dijkstra(int src) {
        for(int i = 0; i < this->v; i++) {
            price[i] = INF;
            ways[i] = 0;
        }
 
        price[src] = 0;
        ways[src] = 1;
        minNodes[src] = 0;
        maxNodes[src] = 0;
 
        PQ pq = PQ();
        pq.push({src, 0});
 
        while(!pq.empty()) {
            Node node = pq.top();
            pq.pop();
 
            for(Node e : this->adj[node.v]) {
                if(price[e.v] < node.d + e.d) continue;
                if(price[e.v] == node.d + e.d) {
                    // Because all the values will be computed at this stage, we can use them to update the new paths and data of each node
                    ways[e.v] = (ways[e.v] + ways[node.v])%MOD;
                    minNodes[e.v] = std::min(minNodes[e.v], minNodes[node.v] + 1);
                    maxNodes[e.v] = std::max(maxNodes[e.v], maxNodes[node.v] + 1);
                    continue;
                }
                
                price[e.v] = node.d + e.d;
                ways[e.v] = ways[node.v];
                minNodes[e.v] = minNodes[node.v] + 1;
                maxNodes[e.v] = maxNodes[node.v] + 1;
                pq.push({e.v, price[e.v]});
            }
        }
 
        return {price[this->v-1], ways[this->v-1], minNodes[this->v-1], maxNodes[this->v-1]};
    }
 
public:
 
    void Investigation() {
        GraphData gd = this->Dijkstra(1);
        printf("%lli %d %d %d\n", gd.minPrice, gd.paths, gd.minNodes, gd.maxNodes);
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
 
    graph.Investigation();
 
    return 0;
}