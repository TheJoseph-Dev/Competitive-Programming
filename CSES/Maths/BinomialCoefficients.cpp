#include <stdio.h>
using ll = long long;
constexpr int MOD = 1e9+7, maxN = 1e6+1;

int fact[maxN];
void genFact() {
    fact[0] = fact[1] = 1;
    for(int i = 2; i < maxN; i++) fact[i] = ((ll)fact[i-1]*i)%MOD;
}

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

ll modinv(ll x) { // Fernat's Little Theorem
    return binpow(x, MOD - 2);
}

int nCm(int a, int b) {
    return (fact[a] * modinv((ll)fact[b]*fact[a-b]))%MOD;
}

int main() {
    genFact();
    int n;
    scanf("%d", &n);
    
    int a, b;
    while(n--) {
        scanf("%d%d", &a, &b);
        printf("%d\n", nCm(a, b));
    }

    return 0;
}