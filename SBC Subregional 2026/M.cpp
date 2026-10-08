#include <stdio.h>
#include <algorithm>
#include <queue>
using ll = long long;
constexpr int maxN = 1e5+4;
constexpr ll LLINF = 1e18;
struct E {
    int v;
    ll w;
    bool f;
};

std::vector<E> adj[maxN];

struct S {
    int v;
    ll w;
    int ck;
    bool operator>(const S& other) const { return w > other.w; }
};

using PQ = std::priority_queue<S, std::vector<S>, std::greater<S>>;

int n, m, k;
ll dist[12][maxN];
ll dijkstra() {
    for(int i = 0; i <= k; i++) for(int j = 0; j <= n; j++) dist[i][j] = LLINF;
    dist[0][1] = 0;
    PQ pq;
    pq.push({1, 0, 0});
    while(!pq.empty()) {
        auto [v, w, ck] = pq.top(); pq.pop();
        for(E e : adj[v]) {
            if(!e.f && ck < k) {
                if(dist[ck+1][e.v] <= dist[ck][v] + e.w) continue;
                dist[ck+1][e.v] = dist[ck][v] + e.w;
                pq.push({e.v, dist[ck+1][e.v], ck+1});
            }
            else if(e.f) {
                if(dist[ck][e.v] <= dist[ck][v] + e.w) continue;
                dist[ck][e.v] = dist[ck][v] + e.w;
                pq.push({e.v, dist[ck][e.v], ck});
            }
        }
    }
    ll mn = LLINF;
    for(int i = 0; i <= k; i++) mn = std::min(mn, dist[i][n]);
    return mn;
}

int main() {
    scanf("%d%d%d", &n, &m, &k);
    int a, b;
    ll w1, w2;
    while(m--) {
        scanf("%d%d%lld%lld", &a, &b, &w1, &w2);
        if(w1 != -1) {
            adj[a].push_back({b, w1, 1});
            adj[b].push_back({a, w1, 1});
        }
        if(w2 != -1) {
            adj[a].push_back({b, w2, 0});
            adj[b].push_back({a, w2, 0});
        }
    }

    printf("%lld\n", dijkstra());
    return 0;
}