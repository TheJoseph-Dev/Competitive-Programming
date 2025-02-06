#include <stdio.h>
#include <vector>
#include <stack>

struct Node {
    int n;
    int age;
};

class Graph {

    int v;
    std::vector<std::vector<int>> adj;
    std::vector<Node> workers;

public:
    Graph(int v): v(v) {
        this->adj = std::vector<std::vector<int>>(v);
        this->workers = std::vector<Node>(v);
    };

    void AddWorker(int i, int age) {
        workers[i] = {i, age};
    }

    void SwapWorkers(int a, int b) {
        int i = 0, j = 0;
        for(int k = 1; k <= v && (!i || !j); k++) {
            if(workers[k].n == a) i = k;
            if(workers[k].n == b) j = k;
        }

        Node aux = workers[i];
        workers[i] = workers[j];
        workers[j] = aux;

    }

    void AddEdge(int v, int e) {
        adj[v].push_back(e);
    }

    int GetMinAge(int s) {

        bool visited[501] = {false};
        std::stack<int> stk = std::stack<int>();

        int i = 0;
        for(int j = 1; j <= v && !i; j++)
            if(workers[j].n == s) i = j;

        if(this->adj[i].empty()) return -1;

        stk.push(i);

        int minAge = 101;
        while(!stk.empty()) {
            int up = stk.top();
            Node worker = this->workers[up];
            stk.pop();

            if(visited[up]) continue;
            visited[up] = true;

            if(worker.n != s) minAge = std::min(minAge, worker.age);

            for(int e : this->adj[up])
                stk.push(e);
        }

        return minAge;
    }
};

int main() { 

    int n, m, q;
    while(scanf("%d%d%d", &n, &m, &q) != EOF) {
        Graph graph = Graph(n+1);
        for(int i = 0; i < n; i++) {
            int age;
            scanf("%d", &age);
            graph.AddWorker(i+1, age);
        }

        for(int i = 0; i < m; i++) {
            int v, e;
            scanf("%d%d", &v, &e);
            graph.AddEdge(e, v); // Reverse
        }

        for(int i = 0; i < q; i++) {
            char t;
            int a, b;
            scanf(" %c%d", &t, &a);
            
            if(t == 'P') {
                int minAge = graph.GetMinAge(a);
                if(minAge == -1) puts("*");
                else printf("%d\n", minAge);
            }
            else {
                scanf("%d", &b);
                graph.SwapWorkers(a, b);
            }

        }
    }

    return 0;
}