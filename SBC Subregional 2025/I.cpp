#include <stdio.h>
#include <algorithm>
#include <cmath>
using ll = long long;
constexpr int maxN = 1e5+2;
struct P {
    ll x,y;
} p[maxN];

ll dst(P p1, P p2) {
    return llabs(p1.x-p2.x) + llabs(p1.y-p2.y);
}

int n;
int main() {
    scanf("%d", &n);
    for(int i = 0; i < n; i++)
        scanf("%lld%lld", &p[i].x, &p[i].y);

    // R1 >= 1
    // R1 < D1
    // R1 > D1-D2 (R2 < D2)
    // R1 < D3-D2+D1 (R3 < D3)

    ll l = 1, r = 1e18, s = 0;
    for(int i = 0; i < n-1; i++) {
        s += ((i&1) ? -1 : 1)*dst(p[i], p[i+1]);
        if(i&1) l = std::max(l, s+1);
        else r = std::min(r, s-1);
    }

    if(r >= l) printf("%lld\n", r);
    else puts("-1");

    return 0;
}