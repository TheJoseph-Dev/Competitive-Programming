#include <iostream>
constexpr int MOD = 1e9+7;
using ll = long long;
 
ll binpow(ll base, ll exp) {
    ll res = 1;
    base %= MOD;
    while (exp > 0) {
        if (exp & 1) res = (res * base) % MOD;
        base = (base * base) % MOD;
        exp >>= 1;
    }
    return res;
}
 
ll modinv(ll x) {
    return binpow(x, MOD - 2);
}
 
int main() {
    int n, x, k;
    scanf("%d", &n);
    
    ll c = 1, s = 1, ans = 1, c2 = 1;
    while(n--) {
        scanf("%d%d", &x, &k);
 
        ans = binpow(ans, k + 1);
        ans *= binpow(x, (ll)k * (k + 1) / 2 % (MOD - 1) * c2 % (MOD - 1));
        ans %= MOD;
 
        c = c * (k + 1) % MOD;
 
        s = s * ((binpow(x, k + 1) - 1 + MOD) % MOD) % MOD * modinv(x - 1) % MOD;
 
        c2 = c2 * (k + 1) % (MOD - 1);
    }
    
    printf("%lld %lld %lld\n", c, s, ans);
    return 0;
}