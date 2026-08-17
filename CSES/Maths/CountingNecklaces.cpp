#include <stdio.h>
#include <algorithm>
constexpr int maxN = 1e6+2, MOD = 1e9+7;
using ll = long long;
/*
S = all possible necklaces
|S| = m^n;
 
G = (S, p)
(e, p1, p2, ..., pn-1) in G
 
I(e) = n;
I(p1) = m; {a1+1, a2+1, ..., am+1} = {a1, a2, ..., am}
I(p2) = ; {a1+2, a2+2, ..., am+2} = {a1, a2, ..., am}
...
*/
ll binpow(ll b, ll e) {
    ll r = 1;
    while(e) {
        if(e&1) r = (r*b)%MOD;
        b = (b*b)%MOD;
        e >>= 1;
    }
    return r;
}
 
ll modinv(ll x) {
    return binpow(x, MOD - 2);
}
 
int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    ll c = 0;
    for(int i = 0; i < n; i++) c = (c + binpow(m, std::__gcd(n, i)))%MOD;
    printf("%lld\n", (c*modinv(n))%MOD);
    return 0;
}