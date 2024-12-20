#include <stdio.h>
#include <vector>

class Graph {

    int v;
    std::vector<int> adj[100001], rAdj[100001];

public:

    Graph(int v): v(v) {}
    
    void AddEdge(int a, int b) {
        adj[a].push_back(b);
        rAdj[b].push_back(a);
    }

private:

    void DFS(int src, bool visited[100001]) {
        
        std::vector<int> stk = std::vector<int>();
        stk.push_back(src);

        visited[src] = true;

        while(!stk.empty()) {
            int node = stk.back();
            stk.pop_back();

            for(int e : this->adj[node]) {
                if(visited[e]) continue;
                visited[e] = true;
                stk.push_back(e);
            }
        }
    }

    void rDFS(int src, bool visited[100001]) {
        
        std::vector<int> stk = std::vector<int>();
        stk.push_back(src);

        visited[src] = true;

        while(!stk.empty()) {
            int node = stk.back();
            stk.pop_back();

            for(int e : this->rAdj[node]) {
                if(visited[e]) continue;
                visited[e] = true;
                stk.push_back(e);
            }
        }
    }

public:

    void SCC() {
        bool visited[100001];
        for(int i = 0; i < this->v; i++) visited[i] = false;

        for(int i = 1; i < this->v; i++) {
            if(!visited[i] && i > 1) {
                // Not SCC
                printf("NO\n1 %d\n", i);
                return;
            }
            this->DFS(i, visited);
        }


        for(int i = 0; i < this->v; i++) visited[i] = false;
        for(int i = 1; i < this->v; i++) {
            if(!visited[i] && i > 1) {
                // Not SCC
                printf("NO\n%d 1\n", i);
                return;
            }
            this->rDFS(i, visited);
        }

        puts("YES");
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

    graph.SCC();

    return 0;
}