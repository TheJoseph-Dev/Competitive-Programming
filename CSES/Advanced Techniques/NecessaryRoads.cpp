#include <stdio.h>
#include <vector>
#include <set>
#include <algorithm>
#include <cstring>
using pii = std::pair<int, int>;
constexpr int maxN = 2e5+5;
int n, m;
class Graph {
    struct Edge {
        int to;
        int id;
    };
    std::vector<Edge> adj[maxN];
    int tin[maxN], low[maxN], sz[maxN], time = 1, id = 1;
    std::set<pii> bridges;
    void dfs(int node, int parent) {
        sz[node] = 1;
        tin[node] = low[node] = time++;
        for(auto [e, id] : adj[node]) {
            if(id == parent) continue;
            if(tin[e]) { // Back edge
                low[node] = std::min({low[node], tin[e]});
                continue;
            }
            // Tree edge
            dfs(e, id);
            sz[node] += sz[e];
            low[node] = std::min({low[node], low[e]});
            //printf("low[%d]: %d | tin[%d]: %d\n", e, low[e], node, tin[node]);
            if(low[e] > tin[node]) bridges.insert({node, e}); // if low[e] > tin[node], then node <=> e is a bridge
        }
    }
public:
    Graph() {
        memset(tin, 0, sizeof(tin));
        memset(low, 0, sizeof(low));
    }
    void AddEdge(int a, int b) {
        adj[a].push_back({b, id});
        adj[b].push_back({a, id});
        id++;
    }
    void Preprocess() { dfs(1, -1); }
    std::set<pii> GetBridges() const { return this->bridges; }
};

int main() {
    scanf("%d%d", &n, &m);
    Graph g = Graph();
    int a, b;
    for(int i = 0; i < m; i++) {
        scanf("%d%d", &a, &b);
        g.AddEdge(a, b);
    }
    g.Preprocess();
    auto bridges = g.GetBridges();
    printf("%d\n", bridges.size());
    for(auto [u,v] : bridges) printf("%d %d\n", u, v);
    return 0;
}