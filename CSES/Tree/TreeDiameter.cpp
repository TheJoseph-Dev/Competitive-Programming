#include <stdio.h>
#include <queue>

constexpr int maxN = 2e5+1;

class Graph {

    int v;
    std::vector<int> adj[maxN];

public:

    Graph(int v) : v(v) {}

    void AddEdge(int a, int b) {
        this->adj[a].push_back(b);
        this->adj[b].push_back(a);
    }

private:

    struct Node {
        int v = 0, d = 0;
    };

    Node MaxDepth(int src) {
        bool visited[maxN] = {false};
        std::queue<Node> q;
        q.push({src, 0});
        visited[src] = true;

        Node lastNode;
        while(!q.empty()) {
            Node node = q.front();
            q.pop();

            for(int e : this->adj[node.v]) {
                if(visited[e]) continue;
                visited[e] = true;
                q.push({e, node.d + 1});
            }

            lastNode = node;
        }

        return lastNode;
    }

public:

    int Diameter() {
        Node deepest = this->MaxDepth(0);
        Node diameter = this->MaxDepth(deepest.v);
        return diameter.d;
    }

};

int main() {

    int n;
    scanf("%d", &n);

    Graph graph = Graph(n);

    int a, b;
    for(int i = 0; i < n-1; i++) {
        scanf("%d%d", &a, &b);
        graph.AddEdge(a-1, b-1);
    }

    printf("%d\n", graph.Diameter());

    return 0;
}