#include <stdio.h>
#include <algorithm>
#include <queue>
#include <numeric>

constexpr int maxN = 505;
constexpr int INF = 0x3f3f3f3f;

// 0-indexed
template<typename T>
class MCMFNet {

    struct Edge {
        int a, b, w;
        T cost;
    };

    int v, src, sink;
    std::vector<int> adj[maxN];
    std::vector<Edge> edges;

    int parent[maxN];
    int parentEdge[maxN];

    T dist[maxN];
    T pot[maxN];
    T inf;

public:

    MCMFNet(int v, int src, int sink) : v(v), src(src), sink(sink) {
        inf = std::numeric_limits<T>::max() / 3;
        for (int i = 0; i < v; i++) pot[i] = 0;
    }

    void AddEdge(int a, int b, int w, T cost) {
        edges.push_back({a, b, w, cost});
        adj[a].push_back(edges.size() - 1);

        edges.push_back({b, a, 0, -cost});
        adj[b].push_back(edges.size() - 1);
    }

private:

    // SPFA: Initial shortest path distances.
    // Required when the original graph contains negative-cost edges.
    void InitPotentials() {
        std::fill(dist, dist + v, inf);

        std::queue<int> q;
        std::vector<bool> inQueue(v, false);

        dist[src] = 0;
        q.push(src);
        inQueue[src] = true;

        while (!q.empty()) {
            int node = q.front();
            q.pop();

            inQueue[node] = false;
            for (int eidx : adj[node]) {
                Edge e = edges[eidx];
                if (e.w == 0 || dist[node] + e.cost >= dist[e.b]) continue;
                dist[e.b] = dist[node] + e.cost;
                if (inQueue[e.b]) continue;
                q.push(e.b);
                inQueue[e.b] = true;
            }
        }

        for (int i = 0; i < v; i++)
            pot[i] = dist[i] < inf ? dist[i] : 0;
    }

    // Dijkstra with reduced costs.
    bool Dijkstra() {
        std::fill(dist, dist + v, inf);
        std::priority_queue<
            std::pair<T, int>,
            std::vector<std::pair<T, int>>,
            std::greater<>
        > pq;

        dist[src] = 0;
        pq.push({0, src});

        while (!pq.empty()) {
            auto [d, node] = pq.top();
            pq.pop();
            if (d > dist[node]) continue;
            for (int eidx : adj[node]) {
                Edge e = edges[eidx];
                if (e.w == 0) continue;
                T cost = e.cost + pot[node] - pot[e.b];
                if (dist[node] + cost >= dist[e.b]) continue;
                dist[e.b] = dist[node] + cost;
                parent[e.b] = node;
                parentEdge[e.b] = eidx;
                pq.push({dist[e.b], e.b});
            }
        }

        return dist[sink] < inf;
    }

public:

    // Returns {maximum flow, minimum cost}.
    std::pair<int, T> MinCostFlow(int maxFlow = INF) {
        //InitPotentials();
        int flow = 0;
        T cost = 0;
        while (flow < maxFlow && Dijkstra()) {
            // Update vertex potentials.
            for (int i = 0; i < v; i++)
                if (dist[i] < inf)
                    pot[i] += dist[i];

            // Find bottleneck capacity.
            int bottleneck = maxFlow - flow;
            int node = sink;
            while (node != src) {
                int eidx = parentEdge[node];
                bottleneck = std::min(bottleneck, edges[eidx].w);
                node = parent[node];
            }
            // Update total cost.
            cost += pot[sink] * bottleneck;
            // Update residual network.
            node = sink;
            while (node != src) {
                int eidx = parentEdge[node];
                edges[eidx].w -= bottleneck;
                edges[eidx ^ 1].w += bottleneck;
                node = parent[node];
            }
            flow += bottleneck;
        }
        return {flow, cost};
    }

    // Recover original edges carrying positive flow.
    std::vector<std::pair<int, int>> Recover() {
        std::vector<std::pair<int, int>> used;
        for (int i = 0; i < (int)edges.size(); i += 2) {
            Edge e = edges[i];
            int usedFlow = edges[i ^ 1].w;
            if (usedFlow > 0) used.push_back({e.a, e.b});
        }

        return used;
    }
};

int n, m, k;
std::vector<int> adj[maxN];
std::vector<int> path;
bool dfs(int node) {
    bool good = false;
    path.push_back(node);
    for(int e : adj[node]) {
        good = dfs(e);
        if(!good) continue; 
        adj[node].erase(std::find(adj[node].begin(), adj[node].end(), e));
        break;
    }
    if(node == n) {
        good = true;
        printf("%d\n", path.size());
        for(int v : path) printf("%d ", v);
        putchar('\n');
    }
    path.pop_back();
    return good;
}

int main() {
    scanf("%d%d%d", &n, &m, &k);

    MCMFNet<int> net(n+3, 1, n);
    while(m--) {
        int a, b;
        scanf("%d%d", &a, &b);
        net.AddEdge(a, b, 1, 1);
    }
    //net.AddEdge(n+1, 1, k, 0);
    auto [mf, cst] = net.MinCostFlow(k);
    if(mf != k) puts("-1");
    else {
        printf("%d\n", cst);
        auto edges = net.Recover();
        for(auto [a, b] : edges) adj[a].push_back(b);
        while(k--) dfs(1);
    }
    return 0;
}