#include <stdio.h>
#include <vector>

constexpr int maxN = 2e5+5, maxLOG = 18;

class Tree {

    int n;
    std::vector<int> adj[maxN];

public:

    Tree(int n) : n(n) {} 

    void AddEdge(int a, int b) {
        this->adj[a].push_back(b);
        this->adj[b].push_back(a);
    }

private:

    int tIn[maxN], tOut[maxN], timer = 0;
    int up[maxN][maxLOG+1]; // Binary Lift
    int depth[maxN];
    void DFS(int node, int parent) {
        tIn[node] = ++timer;
        up[node][0] = parent;
        depth[node] = (parent != -1) ? (depth[parent]+1) : 0;

        for(int i = 1; i <= maxLOG && up[node][i-1] >= 0 && up[node][i-1] <= n; i++)
            up[node][i] = up[up[node][i-1]][i-1];
        
        for(int e : this->adj[node])
            if(e != parent) DFS(e, node);

        tOut[node] = ++timer;
    }

    bool isAncestor(int a, int b) {
        return tIn[a] <= tIn[b] && tOut[a] >= tOut[b];
    }

    int LCA(int a, int b) {
        if (isAncestor(a, b)) return a;
        if (isAncestor(b, a)) return b;
        for (int i = maxLOG; i >= 0; i--)
            if (up[a][i] > 0 && up[a][i] <= n && !isAncestor(up[a][i], b))
                a = up[a][i];

        return up[a][0];
    }

public:

    void Preprocess() {
        for(int i = 0; i <= n; i++)
            for(int p = 0; p <= maxLOG; p++)
                up[i][p] = -1;

        depth[1] = 0;
        DFS(1, -1);
    }

    int Distance(int from, int to) {
        int lca = LCA(from, to);
        return depth[from] + depth[to] - 2 * depth[lca]; 
    }
};

int main() {

    int n, q;
    scanf("%d%d", &n, &q);

    Tree tree = Tree(n+1);
    
    int a, b;
    for(int i = 0; i < n-1; i++) {
        scanf("%d%d", &a, &b);
        tree.AddEdge(a, b);
    }

    tree.Preprocess();

    while(q--) {
        scanf("%d%d", &a, &b);
        printf("%d\n", tree.Distance(a, b));
    }

    return 0;
}