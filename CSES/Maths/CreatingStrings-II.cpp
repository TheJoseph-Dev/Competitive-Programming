#include <stdio.h>

constexpr int maxN = 1e6+2, MOD = 1e9+7;

int factorial(int n) {
    if(n <= 1) return 1;
    long long r = n;
    while(--n) r = (r*n)%MOD;
    return r;
}

long long powmod(long long base, long long exp) {
    long long res = 1;
    base %= MOD;
    while (exp > 0) {
        if (exp & 1) res = (res * base) % MOD;
        base = (base * base) % MOD;
        exp >>= 1;
    }
    return res;
}

long long modinv(long long x) {
    return powmod(x, MOD - 2);
}

char s[maxN];
int main() {
    scanf("%s", s);
    
    int c[26] = {0}, i = 0;
    while(s[i] != '\0') {
        c[s[i]-'a']++;
        i++;
    }

    long long count = factorial(i);
    for(i = 0; i < 26; i++)
        if(c[i]) count = (count*modinv(factorial(c[i])))%MOD;
    
    printf("%lld\n", count);
    return 0;
}