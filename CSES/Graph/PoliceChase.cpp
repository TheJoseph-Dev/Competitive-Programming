#include <stdio.h>
#include <queue>

#define ll long long
constexpr int maxN = 501, INF = 0x3f3f3f3f; 

class DinicNetwork {

	struct Edge {
		int a, b, w;
	};

	int v, src, sink;
	std::vector<int> adj[maxN];
	std::vector<Edge> edges;
	int edgesSize[maxN];
	int level[maxN]; // Level Graph

public:

	DinicNetwork(int v, int src, int sink) : v(v), src(src), sink(sink)  {}

	void AddEdge(int a, int b, int w) {
		this->edges.push_back({a, b, w});
		this->adj[a].push_back(this->edges.size()-1);
		this->edges.push_back({b, a, 0});
		this->adj[b].push_back(this->edges.size()-1);
	}

private:

    // BFS
	bool GenLevelGraph() {
        for(int i = 0; i <= this->v; i++) level[i] = -1;

		std::queue<int> q;
		q.push(this->src);

		while (!q.empty()) {
			int node = q.front();
			q.pop();

            if(node == sink) continue;

			for (int eidx : this->adj[node]) {
				Edge e = this->edges[eidx];
				if (e.w == 0 || level[e.b] != -1 || e.b == src) continue;
                level[e.b] = level[node] + 1;
                q.push(e.b);
			}
		}

		return level[sink] != -1;
	}

    // DFS
	ll Augment(int node, int flow) {
		if (node == sink) return flow;

		for (int &i = this->edgesSize[node]; i >= 0; i--) {
			int eidx = this->adj[node][i];
			Edge e = edges[eidx];

            // Edge must not be saturated and need to be one level ahead
			if (e.w == 0 || level[e.b] != level[node] + 1) continue;
			ll bottleneck = Augment(e.b, std::min(e.w, flow));
            if (bottleneck == 0) continue;

            // Forward edge according to current augmented path
            edges[eidx].w -= bottleneck;
            // Backward edge
            edges[eidx ^ 1].w += bottleneck;

            return bottleneck;
		}

		return 0;
	}

public:

	ll MaxFlow() {
		ll maxFlow = 0;

        // While min-cut doesn't happen, generate the next level graph (BFS)
		while(this->GenLevelGraph()) {
			// Find augmenting paths and update in residual network
			for (int i = 0; i < this->v; i++) this->edgesSize[i] = this->adj[i].size() - 1; // Update active edges
			while(ll flow = this->Augment(0, INF)) // Updates a path from src to sink, contributing to find the max flow
				maxFlow += flow;
		}

		return maxFlow;
	}

    void PrintMinCut() {
        bool visited[maxN] = {false};
        
        std::queue<int> q = std::queue<int>();
        q.push(0);
        visited[0] = true;

        while(!q.empty()) {
            int node = q.front();
            q.pop();

            for(int eidx : this->adj[node]) {
                Edge e = this->edges[eidx];
                if(visited[e.b] || e.w == 0) continue;
                visited[e.b] = true;
                q.push(e.b);
            }
        }

        bool seen[maxN][maxN] = {{false}};
        for(Edge e : edges)
            if(visited[e.a] && !visited[e.b] && !seen[e.a][e.b]) {
                printf("%d %d\n", e.a+1, e.b+1);
                seen[e.a][e.b] = true;
            }
    }
};


class Graph {

    struct Edge {
        int a, b;
    };

    int v;
    std::vector<int> adj[maxN];

public:

    Graph(int v) : v(v) {}

    void AddEdge(int a, int b) {
        this->adj[a].push_back(b);
        this->adj[b].push_back(a);
    }

private:

    std::vector<Edge> DirectEdges(int src) {
        bool visited[maxN] = {false};

        std::vector<Edge> edges = std::vector<Edge>();

        std::queue<int> q = std::queue<int>();
        q.push(src);
        visited[src] = true;

        while(!q.empty()) {
            int node = q.front();
            q.pop();

            for(int e : this->adj[node]) {
                edges.push_back({node, e});
                if(visited[e]) continue;
                visited[e] = true;
                q.push(e);
            }
        }

        return edges;
    }

public:

    DinicNetwork GetNetwork() {
        auto edges = this->DirectEdges(0);

        DinicNetwork dNet = DinicNetwork(this->v, 0, this->v-1);

        for(Edge e : edges) dNet.AddEdge(e.a, e.b, 1);

        return dNet;
    }

};

int main() {

    int n, m;
    scanf("%d%d", &n, &m);

    Graph graph = Graph(n);

    int a, b;
    for(int i = 0; i < m; i++)
        scanf("%d%d", &a, &b), graph.AddEdge(a-1, b-1);

    DinicNetwork dNetwork = graph.GetNetwork();

    printf("%d\n", dNetwork.MaxFlow());
    dNetwork.PrintMinCut();

    return 0;
}