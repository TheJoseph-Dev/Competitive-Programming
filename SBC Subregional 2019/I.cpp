#include <stdio.h>
#include <map>
#include <algorithm>

constexpr int maxN = 4e2+2, INF = 0x3f3f3f3;

struct T {
    int t, i;
    bool operator<(const T& other) const {
        if(this->t != other.t) return this->t < other.t;
        return this->i < other.i;
    }
};

struct Query {
    int t, k, a, b, id, v;
};

bool byK(const Query& lhs, const Query& rhs) {
    return lhs.k < rhs.k;
}

bool byID(const Query& lhs, const Query& rhs) {
    return lhs.id < rhs.id;
}

Query queries[100001];
int distCold[maxN][maxN], distHot[maxN][maxN];
int main() {

    int n, m;
    scanf("%d%d", &n, &m);

    T temperature[maxN];
    for(int i = 1; i <= n; i++) { scanf("%d", &temperature[i].t); temperature[i].i = i; }

    std::map<int, int> tMap = std::map<int, int>();
    std::sort(temperature+1, temperature+n+1);
    int cM[maxN], hM[maxN];
    for(int i = 1; i <= n; i++) {
        cM[temperature[i].i] = i;
        hM[temperature[n-i+1].i] = i;
        tMap[temperature[i].t]++;
    }

    // 1: 3
    // 2: 2
    // cPrfx = { - , 3, 5 }
    // hPrfx = { - , 2, 5 }
    int cPrfx[maxN], hPrfx[maxN];
    cPrfx[0] = 0;
    for(int i = 1, k = 1; k <= tMap.size(); k++) {
        int f = tMap[temperature[i].t];
        cPrfx[k] = cPrfx[k-1] + f;
        i+=f;
    }

    hPrfx[0] = 0;
    for(int i = 1, k = 1; k <= tMap.size(); k++) {
        int f = tMap[temperature[n-i+1].t];
        hPrfx[k] = hPrfx[k-1] + f;
        i+=f;
    }

    for(int i = 0; i <= n; i++)
    for(int j = 0; j <= n; j++)
        distHot[i][j] = distCold[i][j] = INF*(i != j);

    int a, b, w;
    while(m--) {
        scanf("%d%d%d", &a, &b, &w);
        distCold[cM[a]][cM[b]] = distCold[cM[b]][cM[a]] = w;
        distHot[hM[a]][hM[b]] = distHot[hM[b]][hM[a]] = w;
    }

    int q, t;
    scanf("%d", &q);

    for(int i = 0; i < q; i++) {
        scanf("%d%d%d%d", &queries[i].a, &queries[i].b, &queries[i].k, &queries[i].t);
        queries[i].k = std::min(queries[i].k, (int)tMap.size());
        queries[i].k = queries[i].t ? hPrfx[queries[i].k] : cPrfx[queries[i].k];
        queries[i].a = queries[i].t ? hM[queries[i].a] : cM[queries[i].a];
        queries[i].b = queries[i].t ? hM[queries[i].b] : cM[queries[i].b];
        queries[i].id = i;
        queries[i].v = INF;
    }

    std::sort(queries, queries+q, byK);
    int qIdx = 0;
    for(int k = 1; k <= n; k++) {
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= n; j++) {
                distCold[i][j] = std::min(distCold[i][j], distCold[i][k] + distCold[k][j]);
                distHot[i][j] = std::min(distHot[i][j], distHot[i][k] + distHot[k][j]);
            }
        }

        while(k == queries[qIdx].k) {
            queries[qIdx].v = queries[qIdx].t ? distHot[queries[qIdx].a][queries[qIdx].b] : distCold[queries[qIdx].a][queries[qIdx].b];
            qIdx++;
        }
    }

    std::sort(queries, queries+q, byID);

    for(int i = 0; i < q; i++)
        printf("%d\n", queries[i].v == INF ? -1 : queries[i].v);

    return 0;
}