#include <stdio.h>

#define MAX(a,b) ((a) > (b) ? (a) : (b))
constexpr int maxN = 2e5+1, INT_MIN = -(1<<30);

#define ll long long

// 0-index Segment Tree
class SegmentTree {
private:
    struct Segment {
        ll sum, prefix, suffix, subarray;
    };

    int n;
    Segment* tree;
    int array[maxN];

public:
    SegmentTree(int array[maxN], int n) : n(n) {
        this->tree = new Segment[4*n];
        for(int i = 0; i < n; i++) this->array[i] = array[i];

        this->Build(0, 0, n-1);
    }

    ~SegmentTree() {
        delete[] tree;
    }

private:
    Segment Merge(const Segment& left, const Segment& right) {
        Segment segment;
        segment.sum = left.sum + right.sum;
        segment.prefix = MAX(left.prefix, left.sum + right.prefix);
        segment.suffix = MAX(right.suffix, left.suffix + right.sum);
        segment.subarray = MAX(MAX(left.subarray, right.subarray), left.suffix + right.prefix);
        return segment;
    }
    
    void Build(int node, int si, int sf) {
        bool isLeaf = si == sf;
        if (isLeaf) { tree[node] = {this->array[si], MAX(this->array[si], 0), MAX(this->array[si], 0), MAX(this->array[si], 0) }; return; } 

        int mid = (si+sf) / 2;
        // Build the left and right subtrees
        Build(2 * node + 1, si, mid);
        Build(2 * node + 2, mid + 1, sf);
        // Internal node
        tree[node] = this->Merge(tree[2 * node + 1], tree[2 * node + 2]);
    }

    void UpdateTree(int node, int si, int sf, int index, int v) {
        bool outUpdateRange = si > index || sf < index;
        if(outUpdateRange) return;

        // Current segment is fully in range
        bool isLeaf = (si == sf);
        if(isLeaf) {
            tree[node] = {v, MAX(v, 0), MAX(v, 0), MAX(v, 0)};
            return;
        }

        int mid = (si+sf)/2;
        UpdateTree(2*node+1, si, mid, index, v);
        UpdateTree(2*node+2, mid+1, sf, index, v);

    
        // And use the result of children calls to update this node
        tree[node] = Merge(tree[node*2+1], tree[node*2+2]);
    }

    Segment Get(int node, int si, int sf, int l, int r) {
        bool treeEnd = si > sf;
        bool outUpdateRange = si > r || sf < l;
        if(treeEnd || outUpdateRange) return {0, INT_MIN, INT_MIN, INT_MIN};

        // If this segment lies in range
         bool rangeCovered = l <= si && r >= sf;
        if (rangeCovered) return tree[node];

        int mid = (si+sf)/2;
        return Merge(Get(2*node+1, si, mid, l, r),
                     Get(2*node+2, mid+1, sf, l, r));
    }

public:
    void Update(int index, int v) {
        UpdateTree(0, 0, n-1, index, v);
    }

    ll Query(int l, int r) {
        return Get(0, 0, n-1, l, r).subarray;
    }
};

int main() {
    int n, q;
    scanf("%d%d", &n, &q);

    int arr[maxN];
    for(int i = 0; i < n; i++)
        scanf("%d", arr+i);

    SegmentTree seg = SegmentTree(arr, n);

    int index, v;
    while(q--) {
        scanf("%d%d", &index, &v);
        seg.Update(index-1, v);
        printf("%lli\n", seg.Query(0, n-1));
    }
}