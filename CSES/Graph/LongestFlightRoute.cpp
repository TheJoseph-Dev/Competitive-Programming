#include <stdio.h>
#include <vector>

#define INF 0x3f3f3f3f

class Graph {
    int v;

    std::vector<int> adj[100001];

public:

    Graph(int v): v(v) {};

    void AddEdge(int a, int b) {
        this->adj[a].push_back(b);
    }

private:
    
    int parent[100001], dist[100001];
    void DFS(int node, bool visited[100001], bool onStack[100001], std::vector<int>& sortStack) {
        if(visited[node]) return;
        visited[node] = true;
        onStack[node] = true;

        for(int e : this->adj[node]) {
            DFS(e, visited, onStack, sortStack);
            if(onStack[e]) return;
        }

        onStack[node] = false;
        sortStack.push_back(node);

        return;
    }

public:

    void LongestFlightRoute() {
        for(int i = 0; i < this->v; i++) dist[i] = -INF;
        dist[1] = 0;

        bool visited[100001] = {false}, onStack[100001] = {false};
        std::vector<int> stack = std::vector<int>(); 

        DFS(1, visited, onStack, stack);

        if(!visited[this->v-1]) {
            puts("IMPOSSIBLE");
            return;
        }

        while(!stack.empty()) {
            int node = stack.back();
            for(int e : this->adj[node]) {
                if(dist[e] >= dist[node] + 1) continue;
                dist[e] = dist[node] + 1;
                parent[e] = node;
            }

            stack.pop_back();
        }

        std::vector<int> path = std::vector<int>();
        path.push_back(this->v-1);
        int tracker = parent[this->v-1];
        while(tracker != 1) {
            path.push_back(tracker);
            tracker = parent[tracker];
        }
        path.push_back(1);

        printf("%d\n", path.size());
        for(int i = path.size()-1; i >= 0; i--)
            printf("%d ", path[i]);

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

    graph.LongestFlightRoute();

    return 0;
}