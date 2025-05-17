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
 
    void DFS(int node, int parent) {
        tIn[node] = ++timer;
        up[node][0] = parent;
        
        for(int i = 1; i <= maxLOG && up[node][i-1] >= 0 && up[node][i-1] <= n; i++)
            up[node][i] = up[up[node][i-1]][i-1];
 
        for(int e : this->adj[node])
            if(e != parent) DFS(e, node);
 
        tOut[node] = ++timer;
    }
 
    bool isAncestor(int a, int b) {
        return tIn[a] <= tIn[b] && tOut[a] >= tOut[b];
    }
 
 
public:
 
    void Preprocess() {
        for(int i = 0; i < n; i++)
            for(int p = 0; p <= maxLOG; p++)
                up[i][p] = -1;

        DFS(1, -1);
    }
    
    int LCA(int a, int b) {
        if (isAncestor(a, b)) return a;
        if (isAncestor(b, a)) return b;
        for (int i = maxLOG; i >= 0; i--)
            if (up[a][i] > 0 && up[a][i] <= n && !isAncestor(up[a][i], b))
                a = up[a][i];
 
        return up[a][0];
    }
 
};
 
int main() {
 
    int n, q;
    scanf("%d%d", &n, &q);
 
    Tree company = Tree(n+1);
 
    int boss;
    for(int i = 0; i < n-1; i++) {
        scanf("%d", &boss);
        company.AddEdge(boss, i+2);
    }
 
    company.Preprocess();
 
    int a, b; 
    while(q--) {
        scanf("%d%d", &a, &b);
        printf("%d\n", company.LCA(a, b));
    }
 
    return 0;
}