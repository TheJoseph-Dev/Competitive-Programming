#include <stdio.h>
#include <algorithm>
#include <queue>
#include <set>
#include <map>
using ll = long long;
constexpr int maxN = 1e5+4;
constexpr ll LLINF = 1e18;

std::map<int, ll> w;
std::set<int> vis;
std::map<int, std::vector<int>> adj;
void dfs(int node) {
    if(vis.find(node) != vis.end()) return;
    vis.insert(node);
    for(int e : adj[node]) {
        dfs(e);
        //printf("%d => %d\n", node, e);
        w[node] += w[e];
    }
}

struct E {
    bool s;
    int t;
    int i;
    bool operator<(const E& other) const { if(t != other.t) return t < other.t; return s < other.s; }
};

int k[maxN], p;
int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    for(int i = 0; i < m; i++) {
        scanf("%d%d", k+i, &p);
        w[k[i]] += p;
    }

    std::vector<E> ev;
    char c;
    int a, t;
    for(int i = 0; i < m; i++) {
        scanf(" %c", &c);
        if(c == 'A') {
            scanf("%d%d", &a, &t);
            ev.push_back({1, a, k[i]});
            ev.push_back({0, a+t, k[i]});
        }
        else if(c == 'T') {
            scanf("%d", &a);
            adj[a].push_back(k[i]);
        }
    }

    for(int i = 0; i < m; i++) dfs(k[i]);

    std::sort(ev.begin(), ev.end());

    ll s = 0, mx = 0;
    for(int i = 0; i < ev.size(); i++) {
        E e = ev[i];
        //printf("(%d) %d %d | %lld\n", e.s, e.t, e.i, w[e.i]);
        if(e.s) s += w[e.i];
        else s -= w[e.i];
        mx = std::max(mx, s);
    }
    printf("%lld\n", mx);
    return 0;
}