#include <iostream>
#include <math.h>
#include <cstring>
#include <queue>
#include <algorithm>
#include <map>
#include <array>
#include <set>
 
using ll = long long;
constexpr int maxN = 5e2+5, INF = 2e9, MOD = 998244353;
constexpr ll LLINF = 1e18;
 
using i128 = ll;
 
#define f_io() \
    std::ios::sync_with_stdio(0);
 
#ifndef ONLINE_JUDGE
#define DEBUG_H
#include "Debug.h"
#else
    #define dbgf(fmt, x)
    #define p_vi(v)
    #define dbgvi(v)
    #define dbgmi(mtx, rows)
    #define p_v(v)
    #define dbgv(v)
    #define dbgm(m)
    #define dbg(...)
    #define dbg2(...)
    #define dbgbin(n)
#endif
 
 
// Max Flow
// Dinic
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
			while(int flow = this->Augment(src, INF)) // Updates a path from src to sink, contributing to find the max flow
				maxFlow += flow;
		}
 
		return maxFlow;
	}
 
    void PrintPaths(int mf) {
        std::set<std::pair<int, int>> usedEdges;
        while(mf--) {
 
            std::vector<int> stk;
            int parent[maxN];
            memset(parent, -1, sizeof(parent));
            bool visited[maxN] = {false};
            stk.push_back(this->src);
            visited[this->src] = true;
 
            while(!stk.empty()) {
                int node = stk.back();
                stk.pop_back();
                if(node == this->sink) break;
                for(int eidx : this->adj[node]) {
                    if(!(!edges[eidx].w && edges[eidx^1].w && !(eidx&1) && usedEdges.find({node, edges[eidx].b}) == usedEdges.end() && !visited[edges[eidx].b])) continue;
                    parent[edges[eidx].b] = node;
                    visited[edges[eidx].b] = true;
                    stk.push_back(edges[eidx].b);
                }
            }
            
            std::vector<int> path;
            int tracker = this->sink;
            while(tracker+1) {
                usedEdges.insert({parent[tracker], tracker});
                path.push_back(tracker);
                tracker = parent[tracker];
            }
            std::reverse(path.begin(), path.end());
            
            printf("%d\n", path.size());
            for(int v : path) printf("%d ", v+1);
            putchar('\n');
        }
    }
 
};
 
int main() {
    int n, m;
    scanf("%d%d", &n, &m);
 
 
    DinicNetwork dNet = DinicNetwork(n+2, 0, n-1);
    int a, b;
    while(m--) {
        scanf("%d%d", &a, &b);
        dNet.AddEdge(a-1, b-1, 1);
    }
 
    int mf = dNet.MaxFlow();
    printf("%d\n", mf);
    dNet.PrintPaths(mf);
 
    return 0;
}