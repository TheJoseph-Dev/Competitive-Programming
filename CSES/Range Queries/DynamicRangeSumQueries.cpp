#include <stdio.h>

#define ll long long

class SSegmentTree {
private:
    ll* tree;
    ll* lazy;
    ll* array;
    ll n;

private:
    void Build(int node, int si, int sf) {
        bool isLeaf = si == sf;
        if (isLeaf) { tree[node] = this->array[si]; return; } 

        int mid = (si+sf) / 2;
        // Build the left and right subtrees
        Build(2 * node + 1, si, mid);
        Build(2 * node + 2, mid + 1, sf);
        // Internal node
        tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
    }

public:
    SSegmentTree(const int* array, int n) {
        // Iteratively: Tree => 2*n - 1
        // Recursively: Tree => 4*n => Useful when need to range/lazy update, because it divides each range in half
        this->tree = new ll[4*n];
        this->lazy = new ll[4*n]();
        this->array = new ll[n];
        this->n = n;

        for(int i = 0; i < n; i++) {
            //this->tree[i+n-1] = array[i];
            this->array[i] = array[i];
        }
        //for(int i = n-1; i > 0; i--) this->tree[i-1] = tree[i*2-1] + tree[i*2];

        Build(0, 0, n-1);
    };

    SSegmentTree(int n) {
        this->tree = new ll[4*n];
        this->lazy = new ll[4*n]();
        this->array = new ll[n]();
        this->n = n;

        Build(0, 0, n-1);
    };

    ~SSegmentTree() {
        delete[] tree;
        delete[] lazy;
        delete[] array;
    }

    void Print() {
        printf("\nTree (%d):\n", this->n);
        for(int i = 0; i < n*4; i++) printf("%d, ", tree[i]);
        putchar('\n');
        printf("  Lazy (%d):\n  ", this->n);
        for(int i = 0; i < n*4; i++) printf("%d, ", lazy[i]);
        puts("\n");
    };

private:
    void LazyChildren(int node, int si, int sf, ll v) {
        bool isLeaf = si == sf;
        if(!isLeaf) { // Lazy next nodes
            lazy[node*2+1] += v;
            lazy[node*2+2] += v;
        }
    }

    void Unlazy(int node, int si, int sf) {
        if(lazy[node]) {
            tree[node] += (sf-si+1)*lazy[node];
            LazyChildren(node, si, sf, lazy[node]);
            lazy[node] = 0;
        }
    }

    void UpdateRangeLazy(int node, int si, int sf, int l, int r, ll v) {
        Unlazy(node, si, sf);
        bool treeEnd = si > sf;
        bool outUpdateRange = si > r || sf < l;
        if(treeEnd || outUpdateRange) return;

        // Current segment is fully in range
        bool updateCovered = l <= si && r >= sf;
        if(updateCovered) {
            tree[node] += (sf-si+1)*v;
            LazyChildren(node, si, sf, v);
            return;
        }

        int mid = (si+sf)/2;
        UpdateRangeLazy(node*2+1, si, mid, l, r, v);
        UpdateRangeLazy(node*2+2, mid+1, sf, l, r, v);
    
        // And use the result of children calls to update this node
        tree[node] = tree[node*2+1] + tree[node*2+2];
    }

    ll GetSumLazy(int node, int si, int sf, int l, int r) {
        Unlazy(node, si, sf);

        bool treeEnd = si > sf;
        bool outUpdateRange = si > r || sf < l;
        if(treeEnd || outUpdateRange) return 0;

        // If this segment lies in range
         bool sumCovered = l <= si && r >= sf;
        if (sumCovered) return tree[node];

        int mid = (si+sf)/2;
        return GetSumLazy(2*node+1, si, mid, l, r) +
               GetSumLazy(2*node+2, mid+1, sf, l, r);
    }

public:
    void UpdateRange(int l, int r, ll v) {
        UpdateRangeLazy(0, 0, n-1, l, r, v);
    }

    ll GetSum(int l, int r) {
        return GetSumLazy(0, 0, n-1, l, r);
    }

    void Propagate() {

    }

    inline const ll* const GetTree() const { return this->tree; }
};

int main() {
    
    int n, q;
    scanf("%d%d", &n, &q);
 
    int nums[200001];
    for(int i = 0; i < n; i++)
        scanf("%d", nums + i);
 
    SSegmentTree lazySumSegtree = SSegmentTree(nums, n);
 
    int t, a, b;
    while(q--) {
        scanf("%d%d%d", &t, &a, &b);
        if(t == 1) {
            lazySumSegtree.UpdateRange(a-1, a-1, (b-nums[a-1]));
            nums[a-1] = b;
        }
        else printf("%lli\n", lazySumSegtree.GetSum(a-1, b-1));
    }
}