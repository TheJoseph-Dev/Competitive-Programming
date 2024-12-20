#include <stdio.h>
#include <vector>
#include <algorithm>

#define ll long long

class DSU {
    int ds[100001];

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
    ll w;

	bool operator<(const Edge& other) const {
		return this->w < other.w;
	}
};

class MST {

	int v;
	std::vector<Edge> edges, mst;
	ll mstCost = 0;

public:
	MST(int v) : v(v), edges(std::vector<Edge>()), mst(std::vector<Edge>()) {}

	void AddEdge(const Edge& edge) {
		edges.push_back(edge);
	}
	
	void Build() {
		
		this->mstCost = 0;
		this->mst = std::vector<Edge>();
		std::sort(edges.begin(), edges.end());
		
		// Disjoint Set
		DSU dsu = DSU(v);
		for(auto& edge : this->edges) {
			// Check if the edge forms a cycle
			if(dsu.find(edge.v) == dsu.find(edge.d)) continue;
			dsu.merge(edge.v, edge.d);
			this->mstCost += edge.w;
			this->mst.push_back(edge);
		}
	}

	inline ll GetCost() const {
		return this->mstCost;
	}

	inline const std::vector<Edge>& GetMST() const {
		return this->mst;
	}
};

std::vector<int> adj[100001];

bool Reacheable(int src, int n) {
    bool visited[100001] = {false};

    std::vector<int> stk = std::vector<int>();
    stk.push_back(src);

    visited[src] = true;
    int reach = 1;
    while(!stk.empty()) {
        int node = stk.back();
        stk.pop_back();

        for(int e : adj[node]) {
            if(visited[e]) continue;
            visited[e] = true;
            stk.push_back(e);
            reach++;
        }
    }

    return (reach == n);
}

int main() {

    int n, m;
    scanf("%d%d", &n, &m);

    MST mst = MST(n+1);
    int a, b, w;
    for(int i = 0; i < m; i++) {
        scanf("%d%d%d", &a, &b, &w);
        mst.AddEdge({a, b, w});
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    if(!Reacheable(1, n)) { puts("IMPOSSIBLE"); return 0; }

    mst.Build();

    printf("%lli\n", mst.GetCost());


    return 0;
}