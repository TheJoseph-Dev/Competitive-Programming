/*

Algorithm:

- Shortest Path (Dijkstra) do nó P (partida) para todos os nós.
- Para todo e qualquer nó que puder ser atingido sem passar pelo nó G (chegada) 
  deve-se removê-lo da lista de possibilidades.
- Após calcular as distâncias, verificar nos nós restantes se equivalem à 1/2 do Shortest Path 
  de P até G

*/

#include <stdio.h>
#include <queue>

#define ll long long

struct Edge {
    int v;
    ll w;

    Edge(int v, ll w) : v(v), w(w) {}
};

struct Node {
    int v;
    ll d;

    bool operator>(const Node& other) const {
        return this->d > other.d;
    }
};

typedef std::priority_queue<Node, std::vector<Node>, std::greater<Node>> MINPQ;

class Graph {

    int v;
    std::vector<std::vector<Edge>> adj;

    ll dist[2][100001];

public:

    Graph(int v) : v(v) {
        this->adj = std::vector<std::vector<Edge>>(v);

        ll maxLL = 0;
        for(int i = 0; i < 63; i++) maxLL |= (1LL << i);

        for(int i = 0; i < v; i++) {
            dist[0][i] = maxLL;
            dist[1][i] = maxLL;
        }
    }

    void AddEdge(int a, int b, ll w) {
        adj[a].emplace_back(b, w);
        adj[b].emplace_back(a, w);
    }

    void Dijkstra(int p, int g, bool wG = true) {

        bool visited[100001] = {false};
        MINPQ pq = MINPQ();
        pq.push({p, 0});

        this->dist[wG][p] = 0;

        while(!pq.empty()) {
            Node node = pq.top();
            pq.pop();

            if(visited[node.v] || (node.v == g && !wG)) continue;
            visited[node.v] = true;

            for(const Edge& e : adj[node.v]) {
                if(e.v == g && !wG) continue;
                dist[wG][e.v] = std::min(dist[wG][e.v], dist[wG][node.v]+e.w);
                pq.push({e.v, dist[wG][e.v]});
            }
        }
    }

    void PrintMisleading(int g) {
        bool any = false;
        for(int i = 1; i < this->v; i++) {
            if(dist[1][i] == dist[1][g]*2 && dist[0][i] > dist[1][i]) {
                printf("%d ", i);
                any = true;
            }
        }

        if(!any) putchar('*');
        putchar('\n');
    }
};

int main() {

    int n, m, p, g;
    scanf("%d%d%d%d", &n, &m, &p, &g);

    Graph graph = Graph(n+1);

    for(int i = 0; i < m; i++) {
        int u, v;
        ll d;
        scanf("%d%d%lli", &u, &v, &d);
        graph.AddEdge(u, v, d);
    }

    graph.Dijkstra(p, g, true);
    graph.Dijkstra(p, g, false);
    graph.PrintMisleading(g);

    return 0;
}