#include <stdio.h>

constexpr int maxN = 2e5+1;
typedef long long unsigned ll;
constexpr ll INF = 1e18;

ll products(int period[maxN], int n, ll time) {
    ll p = 0;
    for(int i = 0; i < n; i++) {
        p += time/period[i];
        if(p > INF) return INF;
    }

    return p;
}

int main() {

    int n, target;
    scanf("%d%d", &n, &target);

    int period[maxN];
    for(int i = 0; i < n; i++)
        scanf("%d", period+i);

    ll l = 0, r = 1e18;
    while(l < r) {
        ll mid = l + ((r-l) >> 1);
        if(products(period, n, mid) >= target) r = mid;
        else l = mid + 1;
    }

    printf("%llu\n", l);

    return 0;
}