#include <stdio.h>
#include <vector>

class Graph {

    int v;
    std::vector<std::vector<int>> adj;

public:

    Graph(int v): v(v), adj(std::vector<std::vector<int>>(v)) {}
    
    void AddEdge(int a, int b) {
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

private:

    int DFS(int s, bool gVis[100001]) {
        int parent[100001] = {0};
        bool visited[100001] = {false};
        std::vector<int> stk = std::vector<int>();
        stk.push_back(s);

        while(!stk.empty()) {
            int node = stk.back();
            stk.pop_back();

            gVis[node] = visited[node] = true;

            for(auto e : this->adj[node]) {
                if(!visited[e]) {
                    parent[e] = node;
                    stk.push_back(e);
                }
                else if(e != parent[node]) {
                    // Found Cycle
                    std::vector<int> path = std::vector<int>();
                    path.push_back(e);
                    int tracker = node;
                    while(tracker != e) {
                        path.push_back(tracker);
                        tracker = parent[tracker];
                    }

                    printf("%d\n", path.size()+1);
                    printf("%d ", e);
                    for(int i = path.size()-1; i >= 0; i--)
                        printf("%d ", path[i]);
                    return true;
                }

            }
        }

        return false;
    }

    bool FindCycle(int seed) {
        bool gVis[100001] = {false};
        if(this->DFS(seed, gVis)) return true;
        for(int i = 1; i < this->v; i++) {
            if(gVis[i]) continue;
            if(this->DFS(i, gVis)) return true;
        }

        return false;
    };

public:

    void RoundTrip(int seed) {
        bool cycle = this->FindCycle(seed); 
        if(!cycle) {
            puts("IMPOSSIBLE");
            return;
        }
    }
};


int main() {

    int n, m;
    scanf("%d%d", &n, &m);

    Graph graph = Graph(n+1);

    int a, b;
    for(int i = 0; i < m; i++) {
        scanf("%d%d", &a, &b);
        graph.AddEdge(a, b);
    }

    graph.RoundTrip(a);

    return 0;
}