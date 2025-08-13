#include <stdio.h>

constexpr int maxN = 1e6+1, MOD = 1e9+7;

long long fact[maxN], invFact[maxN];

int n;
long long binpow(long long a, long long b) {
    long long res = 1;
    while (b > 0) {
        if (b & 1)
            res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

long long modInv(long long x) {
    return binpow(x, MOD - 2);
}

void preprocess() {
    fact[0] = invFact[0] = 1;
    for (int i = 1; i <= n; i++) {
        fact[i] = fact[i - 1] * i % MOD;
        invFact[i] = modInv(fact[i]);
    }
}

long long catalan(int n) {
    if (n == 0) return 1;
    long long c = fact[2*n] * invFact[n] % MOD * invFact[n] % MOD;
    c = c * modInv(n + 1) % MOD;
    return c;
}

int main() {
    scanf("%d", &n);
    
    /*
    
    dp[0] = 1 
    dp[1] = 0
    dp[2] = 1
    dp[3] = 0
    dp[4] = 2
    dp[5] = 0
    dp[6] = dp[0]*dp[4] + dp[2]*dp[2] + dp[4]*dp[0] = 5
    dp[7] = 0
    */
   
    if(n&1) { puts("0"); return 0; }
    preprocess();
    printf("%lld\n", catalan(n>>1)); 

    return 0;
}