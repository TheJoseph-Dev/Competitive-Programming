#include <stdio.h>
using ll = long long;
constexpr int MOD = 1e9+7, maxN = 2e6+1;

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

int main() {
    genFact();
    int a, b;
    scanf("%d%d", &a, &b);
    printf("%d\n", ((fact[a+b-1] * modinv(fact[a-1]))%MOD * modinv(fact[b]))%MOD);

    return 0;
}