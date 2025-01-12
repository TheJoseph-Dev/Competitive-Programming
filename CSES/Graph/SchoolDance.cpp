// Max Matching
// Hopcraft-Karp / Max Flow

#include <stdio.h>
#include <queue>

constexpr int maxN = 1010, INF = 0x3f3f3f3f; 

// 0-indexed
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
        for(int i = 0; i < this->v; i++) level[i] = -1;

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
	int Augment(int node, int flow) {
		if (node == sink) return flow;

		for (int &i = this->edgesSize[node]; i >= 0; i--) {
			int eidx = this->adj[node][i];
			Edge e = edges[eidx];

            // Edge must not be saturated and need to be one level ahead
			if (e.w == 0 || level[e.b] != level[node] + 1) continue;
			int bottleneck = Augment(e.b, std::min(e.w, flow));
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

	int MaxFlow() {
		int maxFlow = 0;

        // While min-cut doesn't happen, generate the next level graph (BFS)
		while(this->GenLevelGraph()) {
			// Find augmenting paths and update in residual network
			for (int i = 0; i < this->v; i++) this->edgesSize[i] = this->adj[i].size() - 1; // Update active edges
			while(int flow = this->Augment(0, INF)) // Updates a path from src to sink, contributing to find the max flow
				maxFlow += flow;
		}

		return maxFlow;
	}

    void PrintMatchings(int xx) {
        for(Edge e : this->edges) {
            if(e.w || e.a >= e.b || e.a-xx > 0 || e.a == src || e.a == sink) continue;
            printf("%d %d\n", e.a, e.b-xx);
        }
    }

};


int main() {

    int xy, xx, k;
    scanf("%d%d%d", &xx, &xy, &k);

    DinicNetwork dNetwork = DinicNetwork(xx+xy+2, 0, xx+xy+1);

    int a, b;
    while(k--)
        scanf("%d%d", &a, &b), dNetwork.AddEdge(a, b+xx, 1);

    for(int i = 1; i <= xx; i++) dNetwork.AddEdge(0, i, 1);
    for(int i = 1; i <= xy; i++) dNetwork.AddEdge(xx+i, xx+xy+1, 1);

    printf("%d\n", dNetwork.MaxFlow());
    dNetwork.PrintMatchings(xx);

    return 0;
}