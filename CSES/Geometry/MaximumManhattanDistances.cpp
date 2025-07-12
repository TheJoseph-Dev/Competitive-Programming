#include <stdio.h>
#include <math.h>
#include <cstring>
#include <algorithm>

using ll = long long;
constexpr int maxN = 2e5+1, INF = 2e9, MOD = 998244353;
constexpr ll LLINF = 1e18;
 
/*
    p1 = (x1, y1), p2 = (x2, y2)

    |x1 - x2| + |y1 - y2| = max(
        (x1 + y1) - (x2 + y2)
        -(x1 + y1) + (x2 + y2)
        (x1 - y1) - (x2 - y2)
        -(x1 - y1) + (x2 - y2)
    )

    Let f1 = x + y, f2 = x - y

    |x1 - x2| + |y1 - y2| = max(
        f1(p1) - f1(p2)
        f1(p2) - f1(p1)
        f2(p1) - f2(p2)
        f2(p2) - f2(p1)
    )

    |x1 - x2| + |y1 - y2| = max(|f1(p1)-f1(p2)|, |f2(p1)-f2(p2)|)
    
    |a - b| = max(a-b, b-a) = max(a, b) - min(a, b)
    |x1 - x2| + |y1 - y2| = max(x1, x2)-min(x1, x2) + max(y1, y2)-min(y1, y2)
    
    max_ij(|xi - xj| + |yi - yj|) = max_ij( max(|f1(pi)-f1(pj)|, |f2(pi)-f2(pj)|) )
    max_ij(|xi - xj| + |yi - yj|) = max_ij( max(f1(pi), f1(pj))-min(f1(pi), f1(pj)) + max(f2(pi), f2(pj))-min(f2(pi), f2(pj)) )
    
    mxf1 = max(f1(pi), f1(pj))
    mnf1 = min(f1(pi), f1(pj))
    mxf2 = max(f2(pi), f2(pj))
    mnf2 = min(f2(pi), f2(pj))
*/

struct Point {
    ll x, y;
};
 
int main() {
    int n;
    scanf("%d", &n);
 
    ll mxf1 = -LLINF, mxf2 = -LLINF, mnf1 = LLINF, mnf2 = LLINF, dist = 0;
    Point p;
    for(int i = 0; i < n; i++) {
        scanf("%lld%lld", &p.x, &p.y);
        mxf1 = std::max(mxf1, p.x+p.y);
        mnf1 = std::min(mnf1, p.x+p.y);
        mxf2 = std::max(mxf2, p.x-p.y);
        mnf2 = std::min(mnf2, p.x-p.y);
        
        dist = std::max(dist, std::max(mxf1-mnf1, mxf2-mnf2));
        printf("%lld\n", dist);
    }
 
    return 0;
}