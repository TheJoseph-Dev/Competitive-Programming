#include <stdio.h>
#include <vector>

constexpr int maxN = 1e5+2;

int v;
int w[maxN];
class Tree {
    std::vector<int> adj[maxN];

public:
    void AddEdge(int a, int b) {
        this->adj[a].push_back(b);
    }

private:

    int dp[maxN] = {0};
    void DFS(int node, std::vector<int>& lis) {
        int val = w[node];
        int pos = std::lower_bound(lis.begin(), lis.end(), val) - lis.begin();
        bool appended = false;
        int old = 0;

        if (pos == lis.size()) {
            lis.push_back(val);
            appended = true;
        } else {
            old = lis[pos];
            lis[pos] = val;
        }

        dp[node] = lis.size();

        for (int e : adj[node]) 
            DFS(e, lis);

        if (appended) lis.pop_back();
        else lis[pos] = old;
    }

public:

    void GenDP() {
        std::vector<int> lis;
        DFS(1, lis);
        for(int i = 2; i <= v; i++) printf("%d ", dp[i]);
    } 
};

int main() {
    scanf("%d", &v);

    Tree tree;

    int a;
    for(int i = 0; i < v-1; i++) {
        scanf("%d", &a);
        tree.AddEdge(a, i+2);
    }

    w[0] = 0;
    for(int i = 0; i < v; i++) scanf("%d", w+i+1);
    tree.GenDP();

    return 0;
}