#include <stdio.h>
#include <vector>

class Graph {
    int v;

    std::vector<int> adj[100001];

public:

    Graph(int v): v(v) {};

    void AddEdge(int a, int b) {
        this->adj[a].push_back(b);
    }

private:

    // Returs true if it's a DAG
    bool DFS(int node, bool visited[100001], bool stack[100001], std::vector<int>& sortStack) {
        if(visited[node]) return true;
        visited[node] = true;
        stack[node] = true;

        for(int e : this->adj[node]) {
            DFS(e, visited, stack, sortStack);
            if(stack[e]) return false;
        }

        stack[node] = false;
        sortStack.push_back(node);

        return true;
    }

public:

    void PrintTopologicallySorted() {
        bool visited[100001] = {false}, onStack[100001] = {false};
        std::vector<int> stack = std::vector<int>(); 
        for(int i = 1; i < this->v; i++) {
            if(visited[i]) continue;
            if(!DFS(i, visited, onStack, stack)) { puts("IMPOSSIBLE"); return; }
        }

        while(!stack.empty()) {
            printf("%d ", stack.back());
            stack.pop_back();
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

    graph.PrintTopologicallySorted();

    return 0;
}