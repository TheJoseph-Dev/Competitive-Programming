#include <stdio.h>
#include <vector>

struct Road {
    int a, b;
};

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

    void DFS(int s, bool visited[100001]) {
        std::vector<int> stk = std::vector<int>();
        stk.push_back(s);
        while(!stk.empty()) {
            int node = stk.back();
            stk.pop_back();

            for(auto e : this->adj[node]) {
                if(visited[e]) continue;
                visited[e] = true;
                stk.push_back(e);
            }
        }
    }

public:

    void ConnectComponents() {
        std::vector<Road> roads = std::vector<Road>();
        int c = 0;
        bool visited[100001] = {false};
        
        for(int i = 1; i < this->v; i++) {
            if(visited[i]) continue;
            DFS(i, visited);
            if(c == 0) c = i;
            else {
                roads.push_back({c, i});
                c = i;
            }
        }

        printf("%d\n", roads.size());
        for(auto road : roads) printf("%d %d\n", road.a, road.b);
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

    graph.ConnectComponents();

    return 0;
}