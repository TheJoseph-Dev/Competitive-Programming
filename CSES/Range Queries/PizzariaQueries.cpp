#include <stdio.h>
#include <algorithm>
#include <climits>

constexpr int maxN = 2e5+1, INF = 0x3f3f3f3f;

// 0-index Segment Tree
class SegmentTree {
private:
    int n;
    int* tree;
    int array[maxN];
    bool up;
public:
    SegmentTree(int array[maxN], int n, bool up) : n(n), up(up) {
        this->tree = new int[4*n];
        for(int i = 0; i < n; i++)
            this->array[i] = array[i] + (up ? i : -i);

        this->Build(0, 0, n-1);
    }

    ~SegmentTree() {
        delete[] tree;
    }

private:
    void Build(int node, int si, int sf) {
        bool isLeaf = si == sf;
        if (isLeaf) { tree[node] = this->array[si]; return; } 

        int mid = (si+sf) / 2;
        // Build the left and right subtrees
        Build(2 * node + 1, si, mid);
        Build(2 * node + 2, mid + 1, sf);
        // Internal node
        tree[node] = std::min(tree[2 * node + 1], tree[2 * node + 2]);
    }

    void UpdateTree(int node, int si, int sf, int index, int v) {
        bool outUpdateRange = si > index || sf < index;
        if(outUpdateRange) return;

        // Current segment is fully in range
        bool isLeaf = (si == sf);
        if(isLeaf) {
            tree[node] = v;
            return;
        }

        int mid = (si+sf)/2;
        UpdateTree(node*2+1, si, mid, index, v);
        UpdateTree(node*2+2, mid+1, sf, index, v);
    
        // And use the result of children calls to update this node
        tree[node] = std::min(tree[node*2+1], tree[node*2+2]);
    }

    int Get(int node, int si, int sf, int l, int r) {
        bool outRange = si > r || sf < l;
        if(outRange) return INT_MAX;

        // If this segment lies in range
        bool rangeCovered = l <= si && r >= sf;
        if (rangeCovered) return tree[node];

        int mid = (si+sf)/2;
        return std::min(Get(2*node+1, si, mid, l, r), Get(2*node+2, mid+1, sf, l, r));
    }

public:
    void Update(int index, int v) {
        UpdateTree(0, 0, n-1, index, v + (this->up ? index : -index));
    }

    int Query(int l, int r) {
        if(r <= l) return INF;
        return Get(0, 0, n-1, l, r);
    }
};

int main() {
    int n, q;
    scanf("%d%d", &n, &q);

    int prices[maxN];
    for(int i = 0; i < n; i++)
        scanf("%d", prices+i);
    
    SegmentTree upSeg = SegmentTree(prices, n, true), downSeg = SegmentTree(prices, n, false);
    
    int type, b, x;
    while(q--) {
        scanf("%d%d", &type, &b);
        if(type == 2) printf("%d\n", std::min(upSeg.Query(b-1, n-1) - (b-1), downSeg.Query(0, b-2) + (b-1)));
        else {
            scanf("%d", &x);
            upSeg.Update(b-1, x);
            downSeg.Update(b-1, x);
        }
    }
}