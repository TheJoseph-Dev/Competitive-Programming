#include <stdio.h>
#include <vector>
#include <array>

constexpr int maxN = 2e5+5;

using ll = long long;


// Sum Fenwick Tree 
// Use 1-index to avoid infinite loops!

class FenwickTree {
    ll* tree;
    int size;

public:
    FenwickTree(int n) : size(n) {
        tree = new ll[n + 1]();
    }

    /*
    ~FenwickTree() {
        delete[] tree;
    }
    */

private:
    void Update(int idx, ll val) {
        while (idx <= size) {
            tree[idx] += val;
            idx += idx & -idx;
        }
    }

    ll Query(int idx) {
        ll sum = 0;
        while (idx > 0) {
            sum += tree[idx];
            idx -= idx & -idx;
        }
        return sum;
    }

public:
    // Add val to every element in [l, r]
    void RangeUpdate(int l, int r, ll val) {
        Update(l, val);
        if (r + 1 <= size)
            Update(r + 1, -val);
    }

    // Value at index idx
    ll PointQuery(int idx) {
        return Query(idx);
    }
};

class Tree {

    int n;
    std::vector<int> adj[maxN];
    FenwickTree tree;

public:

    Tree(int n) : n(n), tree(n+1) {}

    void AddEdge(int a, int b) {
        this->adj[a].push_back(b);
        this->adj[b].push_back(a);
    }

private:

    // ll acc[maxN];
    // void DFS(int node, int parent, int v[maxN]) {
    //     acc[node] = v[node];
    //     if(parent != -1) acc[node] += acc[parent];
    //     for(int e : this->adj[node])
    //         if(e != parent)
    //             DFS(e, node, v);
    // }

    std::array<int, 2> tRanges[maxN];
    void Flat(int node, int& idx, int parent, int v[maxN]) {
        int l = idx;
        for(int e : this->adj[node]) if(e != parent) { Flat(e, idx, node, v); idx++; }
        tree.RangeUpdate(l, idx, v[node]);
        tRanges[node] = {l, idx};
    }

public:

    void Process(int values[maxN]) {
        //DFS(1, -1, values);
        int idx = 1;
        Flat(1, idx, -1, values);
    }

    void UpdateValue(int node, ll diff) {
        this->tree.RangeUpdate(tRanges[node][0], tRanges[node][1], diff);
    }

    ll GetNodeValue(int node) {
        return this->tree.PointQuery(tRanges[node][1]);
    }
};

int main() {

    int n, q;
    scanf("%d%d", &n, &q);

    int values[maxN];
    for(int i = 1; i <= n; i++)
        scanf("%d", values+i);

    Tree tree = Tree(n+1);
    
    int a, b;
    for(int i = 0; i < n-1; i++) {
        scanf("%d%d", &a, &b);
        tree.AddEdge(a, b);
    }

    tree.Process(values);

    int type;
    while(q--) {
        scanf("%d%d", &type, &a);
        if(type == 2) printf("%lld\n", tree.GetNodeValue(a));
        else {
            scanf("%d", &b); 
            ll diff = b-values[a];
            values[a] = b;
            tree.UpdateValue(a, diff);
        }
    }

    return 0;
}