#include <stdio.h>
#include <vector>
#include <algorithm>

constexpr int maxN = 1e5+5, maxLOG = 18, INF = 0x3f3f3f3f;

struct Lift {
    int node, minW;
};

int tIn[maxN], tOut[maxN], timer = 0;
Lift up[maxN][maxLOG+1]; // Binary Lift

class Tree {

    struct Node {
        int v;
        int w;
    };

    int n;
    std::vector<Node> adj[maxN];

public:

    Tree(int n) : n(n) {} 

    void AddEdge(int a, int b, int w) {
        this->adj[a].push_back({b, w});
        this->adj[b].push_back({a, w});
    }

private:

    void DFS(int node, Node parent) {
        tIn[node] = ++timer;
        up[node][0].node = parent.v;
        up[node][0].minW = parent.w;

        for(int i = 1; i <= maxLOG && up[node][i-1].node >= 0 && up[node][i-1].node <= n; i++) {
            up[node][i] = up[up[node][i-1].node][i-1];
            up[node][i].minW = std::min(up[node][i].minW, up[node][i-1].minW);
        }
        
        for(Node e : this->adj[node])
            if(e.v != parent.v) DFS(e.v, {node, e.w});

        tOut[node] = ++timer;
    }

    bool isAncestor(int a, int b) {
        return tIn[a] <= tIn[b] && tOut[a] >= tOut[b];
    }

    int LCA(int a, int b) {
        if (isAncestor(a, b)) return a;
        if (isAncestor(b, a)) return b;
        for (int i = maxLOG; i >= 0; i--)
            if (up[a][i].node > 0 && up[a][i].node <= n && !isAncestor(up[a][i].node, b))
                a = up[a][i].node;

        return up[a][0].node;
    }

    int GetFromLow(int from, int target) {
        int power = 0, minW = up[from][0].minW;
        for (int i = maxLOG; i >= 0; i--) {
            if(up[from][i].node == target) { power = i; break; }
            if (up[from][i].node > 0 && up[from][i].node <= n && !isAncestor(up[from][i].node, target)) {
                minW = std::min(up[from][i].minW, minW);
                from = up[from][i].node;
            }
        }

        return std::min(up[from][power].minW, minW);
    }

    int GetMin(int a, int b) {
        if (isAncestor(a, b)) return GetFromLow(b, a);
        if (isAncestor(b, a)) return GetFromLow(a, b);
        int lca = LCA(a, b);
        //printf("(%d, %d) lca: %d\n", a, b, lca);
        return std::min(GetFromLow(a, lca), GetFromLow(b, lca));
    }

public:

    void Preprocess() {
        for(int i = 0; i <= n; i++)
            for(int p = 0; p <= maxLOG; p++) {
                up[i][p].node = -1;
                up[i][p].minW = INF;
            }

        DFS(1, {-1, INF});
    }

    int MaxFlow(int from, int to) {
        return GetMin(from, to); 
    }
};

class DSU {
    int ds[maxN];

public:

    DSU(int n) {
        for(int i = 1; i <= n; i++)
            ds[i] = i; // Each "leader" points itself
    }

    // Find the set which 'x' belongs
    int find(int x) {
        if(ds[x] == x) return x; // Checks if the Leader is x
        
        // Set's been merged, then find the Leader of who merged
        
        // return find(ds[x]); Naive => O(n) in unbalanced trees
        return ds[x] = find(ds[x]); // "Dynamic Programming" optimization => O(logN) amortized => This optimization is called Path Compression
    }

    // Checks if 2 elements belongs to the same set
    bool same(int x, int y) {
        return find(x) == find(y); // Check their Leaders
    }

    // Union
    void merge(int x, int y) {
        ds[find(x)] = find(y); // Leader of Set which x belongs is now Leader of Set which y belongs
        // Leader of y keeps y
    }
};

struct Edge {
	int v, d;
    int w;

	bool operator<(const Edge& other) const {
		return this->w > other.w;
	}
};

class MST {

	int v;
	std::vector<Edge> edges, mst;

public:
	MST(int v) : v(v), edges(std::vector<Edge>()), mst(std::vector<Edge>()) {}

	void AddEdge(const Edge& edge) {
		edges.push_back(edge);
	}
	
	void Build() {
		
		this->mst = std::vector<Edge>();
		std::sort(edges.begin(), edges.end());
		
		// Disjoint Set
		DSU dsu = DSU(v);
		for(auto& edge : this->edges) {
			// Check if the edge forms a cycle
			if(dsu.find(edge.v) == dsu.find(edge.d)) continue;
			dsu.merge(edge.v, edge.d);
			this->mst.push_back(edge);
		}
	}


	inline std::vector<Edge> GetMST() const {
		return this->mst;
	}
};

int main() {

    int n, m, q;
    while(scanf("%d%d%d", &n, &m, &q)+1) {
        
        MST mst = MST(n+1);

        int a, b, w;
        while(m--) {
            scanf("%d%d%d", &a, &b, &w);
            mst.AddEdge({a, b, w});
        }
        
        mst.Build();
        auto edges = mst.GetMST();
        Tree tree = Tree(n+2);
        for(Edge e : edges)
            tree.AddEdge(e.v, e.d, e.w);

        tree.Preprocess();

        while(q--) {
            scanf("%d%d", &a, &b);
            printf("%d\n", tree.MaxFlow(a, b));
        }
    }

    return 0;
}