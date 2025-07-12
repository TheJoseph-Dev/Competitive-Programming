#include <stdio.h>
#include <vector>
#include <array>

constexpr int maxN = 2e5+5;

using ll = long long;


// Sum Fenwick Tree 
// Use 1-index to avoid infinite loops!

class FenwickTree {
    ll tree[maxN] = {0};
    int size;
 
public:
    FenwickTree(int n) : size(n) {
        //tree = new ll[n + 1]();  // Indexed from 1 to n
    }

    /* 
    Destructor: Use it when inside a loop or need to avoid memory leak
    ~FenwickTree() {
	    delete[] tree;
    }
    */
 
    // Updates the Fenwick tree at position idx by adding val
    void Update(int idx, int val) {
        while (idx <= size) {
            tree[idx] += val;
            idx += idx & -idx;  // Move to the next index
        }
    }
 
private:

    // Queries the sum in the range [1, idx]
    ll Query(int idx) {
        ll sum = 0;
        while (idx > 0) {
            sum += tree[idx];
            idx -= idx & -idx;  // Move to the parent index
        }
        return sum;
    }
 
 public:
    // Queries the sum in the range [a, b]
    ll RangeQuery(int a, int b) {
        return Query(b) - Query(a - 1);
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

    std::array<int, 2> tRanges[maxN];
    void Flat(int node, int& idx, int values[maxN], int parent) {
        int l = idx;
        for(int e : this->adj[node]) if(e != parent) { Flat(e, idx, values, node); idx++; }
        tree.Update(idx, values[node]);
        tRanges[node] = {l, idx};
    }

public:

    void Process(int values[maxN]) {
        int idx = 1;
        Flat(1, idx, values, -1);
    }

    void UpdateValue(int node, int value) {
        this->tree.Update(tRanges[node][1], value-this->tree.RangeQuery(tRanges[node][1], tRanges[node][1]));
    }

    ll GetSubtreeValue(int node) {
        return this->tree.RangeQuery(tRanges[node][0], tRanges[node][1]);
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
        if(type == 2) printf("%lld\n", tree.GetSubtreeValue(a));
        else {
            scanf("%d", &b); 
            tree.UpdateValue(a, b);
        }
    }

    return 0;
}