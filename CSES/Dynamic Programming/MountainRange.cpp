#include <stdio.h>
#include <algorithm>
#include <vector>
#include <stack>

constexpr int maxN = 2e5+3;

// 0-index Segment Tree
class SegmentTree {
private:
    int n;
    int* tree;
public:
    SegmentTree(int n) : n(n) {
        this->tree = new int[4*n]();
    }

    ~SegmentTree() {
        delete[] tree;
    }

private:
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
        tree[node] = std::max(tree[node*2+1], tree[node*2+2]);
    }

    int Get(int node, int si, int sf, int l, int r) {
        bool outRange = si > r || sf < l;
        if(outRange) return 0;

        // If this segment lies in range
         bool rangeCovered = l <= si && r >= sf;
        if (rangeCovered) return tree[node];

        int mid = (si+sf)/2;
        return std::max(Get(2*node+1, si, mid, l, r),
                        Get(2*node+2, mid+1, sf, l, r));
    }

public:
    void Update(int index, int v) {
        UpdateTree(0, 0, n-1, index, v);
    }

    int Query(int l, int r) {
        return Get(0, 0, n-1, l, r);
    }
};

int n;
std::pair<int, int> a[maxN];

int ngr[maxN], ngl[maxN];
void nearestGreater() {
    //memset(ngr, -1, sizeof(ngr));
    std::stack<int> monostk;
    for(int i = 1; i <= n+1; i++) {
        while(!monostk.empty() && a[monostk.top()].first <= a[i].first) {
            ngr[monostk.top()] = i;
            monostk.pop();
        }
        monostk.push(i);
    }
    while(!monostk.empty()) monostk.pop();

    //memset(ngl, -1, sizeof(ngr));
    for(int i = n; i >= 0; i--) {
        while(!monostk.empty() && a[monostk.top()].first <= a[i].first) {
            ngl[monostk.top()] = i;
            monostk.pop();
        }
        monostk.push(i);
    }
    while(!monostk.empty()) monostk.pop();
}

int dp[maxN];
int main() {
    
    scanf("%d", &n);
    
    int v;
    for(int i = 1; i <= n; i++) { scanf("%d", &v); a[i].first = v; a[i].second = i; }
    a[0].first = a[n+1].first = 0x3f3f3f3f;
    nearestGreater();
    
    std::sort(a+1, a+n+1);
    SegmentTree st = SegmentTree(n+1);
    
    int max = 0;
    for(int i = 1; i <= n; i++) {
        dp[a[i].second] = 1 + st.Query(ngl[a[i].second]+1, ngr[a[i].second]-1);
        st.Update(a[i].second, dp[a[i].second]);
        max = std::max(max, dp[a[i].second]);
    }

    printf("%d\n", max);

    return 0;
}