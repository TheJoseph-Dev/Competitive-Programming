#include <stdio.h>
#include <algorithm>
constexpr int maxN = 2e5+4;
using ll = long long;
struct P {
    int c, k;
    bool operator<(const P& other) const { if(c-k != other.c-other.k) return c-k < other.c-other.k; return c < other.c; }
} p[maxN];
int main() {
    int n;
    scanf("%d", &n);
    for(int i = 0; i < n; i++) scanf("%d", &p[i].c);
    for(int i = 0; i < n; i++) scanf("%d", &p[i].k);
    for(int i = 0; i < n; i++) if(p[i].c < p[i].k) { puts("-1"); return 0; }
    std::sort(p, p+n);
    ll s = 0;
    for(int i = 1; i < n; i++) s += p[i].c;
    printf("%lld\n", s+p[0].k);
    return 0;
}