#include <stdio.h>
#include <cmath>
using ll = long long;
constexpr int MOD = 1e9+7, maxN = 1e6+1;

// Derangement: 
// !n = n! * \sum_{k=0}^n (-1)^k/k! 
// !n = (n-1)(!(n-1)+!(n-2))
// !n ~= round(n!/e)

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

constexpr double e = 2.718281828459045;
int derangement(int n) {
    int s = 0;
    for(int i = 0; i <= n; i++) s = (s + (i&1 ? -1 : 1)*modinv(fact[i]) + MOD)%MOD;
    return ((ll)fact[n]*s)%MOD;
}

int main() {
    genFact();
    int n;
    scanf("%d", &n);
    printf("%d\n", derangement(n));

    return 0;
}