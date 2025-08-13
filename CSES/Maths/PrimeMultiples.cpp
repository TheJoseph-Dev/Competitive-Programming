#include <stdio.h>
using ll = long long;

ll n;
int k;
ll p[21];

ll PIE() {
    ll c = 0;
    for(int mask = 1; mask < (1<<k); mask++) {
        ll tn = n;
        for(int b = 0; b < k; b++)
            if(mask&(1<<b))
                tn /= p[b];
        c += __builtin_parity(mask) ? tn : -tn;
    }

    return c;
}

int main() {
    scanf("%lld%d", &n, &k);
    for(int i = 0; i < k; i++) scanf("%lld", p+i);
    printf("%lld\n", PIE());
}