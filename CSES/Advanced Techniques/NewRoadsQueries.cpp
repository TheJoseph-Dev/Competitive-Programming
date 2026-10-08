#include <stdio.h>
#include <queue>
#include <array>
#include <algorithm>
using ll = long long;
constexpr int maxN = 2e5+4;

class DSU {
    int ds[maxN];
public:
    int sz;
    DSU() {}
    DSU(int n) {
        for(int i = 1; i <= n; i++) ds[i] = i;
        sz = 0;
    }

    // Find the set which 'x' belongs
    int find(int x) {
        if(ds[x] == x) return x;
        return ds[x] = find(ds[x]);
    }

    bool same(int x, int y) {
        return find(x) == find(y); // Check their Leaders
    }

    void merge(int x, int y) {
        sz++;
        ds[find(x)] = find(y);
    }
};

struct E {
    int a, b;
} edges[maxN];

struct Q {
    int a, b;
    int i;
};
Q qr[maxN];
int n, m, q;
int times[maxN];

int main() {
    for(int i = 0; i < maxN; i++) times[i] = 1e9+1;
    scanf("%d%d%d", &n, &m, &q);
    for(int i = 0; i < m; i++) scanf("%d%d", &edges[i].a, &edges[i].b);
    for(int i = 0; i < q; i++) { scanf("%d%d", &qr[i].a, &qr[i].b); qr[i].i = i; }
    std::queue<std::array<int, 5>> qu;
    int d = -1;
    qu.push({0, m-1, 0, q, d+1});
    DSU dsu;
    while(!qu.empty()) {
        auto [l, r, lq, rq, depth] = qu.front();
        qu.pop();
        if(l > r) continue;
        if(depth > d) dsu = DSU(n+1);
        d = depth;
        int t = (l+r)>>1;
        //printf("(%d) [%d %d] [%d %d]: %d\n", depth, l, r, lq, rq, t);
        for(int i = dsu.sz; i <= t; i++) dsu.merge(edges[i].a, edges[i].b);
        int cnt = 0;
        for(int i = lq; i < rq; i++) {
            if(qr[i].a == qr[i].b) times[qr[i].i] = 0;
            //printf("q(%d, %d): %d\n", qr[i].a, qr[i].b, dsu.same(qr[i].a, qr[i].b));
            if(dsu.same(qr[i].a, qr[i].b)) { times[qr[i].i] = std::min(times[qr[i].i], t+1); cnt++; }
        }
        std::partition(qr+lq, qr+rq, [t](Q qry){
            return times[qry.i] <= t+1;
        });
        qu.push({l,t-1,lq,lq+cnt,depth+1});
        qu.push({t+1,r,lq+cnt,rq,depth+1});
    }

    for(int i = 0; i < q; i++) printf("%d\n", times[i] < 1e9 ? times[i] : -1);
    return 0;
}