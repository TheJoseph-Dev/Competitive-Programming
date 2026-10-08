#include <stdio.h>
#include <vector>
#include <algorithm>

constexpr int maxN = 2e5 + 4;

class DSU {
    int ds[maxN];

public:
    DSU() {}
    DSU(int n) {
        for (int i = 1; i <= n; i++)
            ds[i] = i;
    }

    int find(int x) {
        if (ds[x] == x) return x;
        return ds[x] = find(ds[x]);
    }

    bool same(int x, int y) {
        return find(x) == find(y);
    }

    void merge(int x, int y) {
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
int main() {
    scanf("%d%d%d", &n, &m, &q);

    for (int i = 0; i < m; i++)
        scanf("%d%d", &edges[i].a, &edges[i].b);

    for (int i = 0; i < q; i++) {
        scanf("%d%d", &qr[i].a, &qr[i].b);
        qr[i].i = i;
    }

    // lo[i] <= answer < hi[i]
    int lo[maxN], hi[maxN];
    for (int i = 0; i < q; i++) {
        lo[i] = 0;
        hi[i] = m + 1;
    }

    while (true) {
        std::vector<int> bucket[maxN];
        bool done = true;
        for (int i = 0; i < q; i++) {
            if (lo[i] + 1 < hi[i]) {
                done = false;
                int mid = (lo[i] + hi[i]) >> 1;
                bucket[mid].push_back(i);
            }
        }

        if (done) break;
        DSU dsu(n);
        // After adding edges[0..day-1], we have the graph
        // after 'day' days.
        for (int day = 1; day <= m; day++) {
            dsu.merge(edges[day - 1].a, edges[day - 1].b);
            for (int qi : bucket[day]) {
                if (dsu.same(qr[qi].a, qr[qi].b)) hi[qi] = day;
                else lo[qi] = day;
            }
        }
    }

    for (int i = 0; i < q; i++) {
        if (qr[i].a == qr[i].b) printf("0\n");
        else if (hi[i] == m + 1) printf("-1\n");
        else printf("%d\n", hi[i]);
    }

    return 0;
}
