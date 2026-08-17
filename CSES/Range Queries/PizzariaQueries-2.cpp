#include <stdio.h>
#include <algorithm>
 
// pi + |a-b|
// node[0] = min(pi - b)
// node[1] = min(pi + b)
// 
// if k in left: min(t[r][1]-k); GetMin(left)
// if k in right: min(t[l][0]+k); GetMin(right)
 
using ll = long long;
constexpr int maxN = 2e5+4;
constexpr ll LLINF = 1e18;
int n, q, a[maxN];
namespace seg {
    struct Node {
        ll cm;
        ll cp;
        //Node(ll a = LLINF, ll b = LLINF): cm(a), cp(b) {}
    };
 
    Node tree[maxN*4];
 
    void build(int l, int r, int node) {
        if(l > r) return;
        if(l == r) { tree[node] = {a[l]-l, a[l]+l}; return; }
        int m = (l+r)>>1;
        build(l, m, node*2+1);
        build(m+1, r, node*2+2);
        tree[node] = {std::min(tree[node*2+1].cm, tree[node*2+2].cm), std::min(tree[node*2+1].cp, tree[node*2+2].cp)};
    }
 
    void update(int i, int x, int sl, int sr, int node) {
        if(sl > sr || i > sr || i < sl) return;
        if(sl == sr) { tree[node] = {x-i, x+i}; return; }
        int m = (sl+sr) >> 1;
        int left = 2*node + 1, right = 2*node+2;
        if(i <= m) update(i, x, sl, m, 2*node+1);
        else update(i, x, m+1, sr, 2*node+2);
        tree[node] = {std::min(tree[left].cm, tree[right].cm), std::min(tree[left].cp, tree[right].cp)};
    }
 
    ll query(int i, int sl, int sr, int node) {
        if(sl > sr || i > sr || i < sl) return LLINF;
        if(sl == sr) return tree[node].cp-i;
        int m = (sl+sr) >> 1;
        int left = 2*node + 1, right = 2*node+2;
        ll mn = LLINF;
        if(i <= m) mn = std::min(tree[right].cp-i, query(i, sl, m, left));
        else mn = std::min(tree[left].cm+i, query(i, m+1, sr, right));
        //printf("%d %d %d %d | %lld\n", i, sl, sr, node, mn);
        return mn;
    }
}
 
int main() {
    scanf("%d%d", &n, &q);
    for(int i = 0; i < n; i++) scanf("%d", a+i);
    seg::build(0, n-1, 0);
    int t, k, x;
    while(q--) {
        scanf("%d%d", &t, &k);
        if(t == 1) { scanf("%d", &x); seg::update(k-1, x, 0, n-1, 0); }
        else printf("%lld\n", seg::query(k-1, 0, n-1, 0));
    }
    return 0;
}