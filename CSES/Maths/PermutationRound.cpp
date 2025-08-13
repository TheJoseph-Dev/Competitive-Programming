#include <stdio.h>
#include <algorithm>
using ll = long long unsigned;
constexpr int maxN = 2e5 + 2, MOD = 1e9 + 7;

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

int spf[maxN];
void sieve() {
    for (int i = 0; i < maxN; i++) spf[i] = i;
    for (int i = 2; i * i < maxN; i++)
        if (spf[i] == i)
            for (int j = i * i; j < maxN; j += i)
                if (spf[j] == j) spf[j] = i;
}

void factorize(int n, int* exp) {
    while(n > 1) {
        int p = spf[n];
        int cnt = 0;
        while (n % p == 0) {
            cnt++;
            n /= p;
        }
        exp[p] = std::max(exp[p], cnt);
    }
}

int n, to[maxN];
bool seen[maxN];
int szs[maxN], s = 0;
int main() {
    sieve();

    scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf("%d", to + i);

    for (int i = 0; i < n; i++) {
        if (seen[i]) continue;
        int j = i, c = 0;
        while (!seen[j]) {
            seen[j] = true;
            j = to[j] - 1;
            c++;
        }
        szs[s++] = c;
    }

    // Compute LCM using prime factorization
    int maxExp[maxN] = {0}; // Maximum exponent for each prime
    for (int i = 0; i < s; i++)
        factorize(szs[i], maxExp);

    ll lcm = 1;
    for (int p = 2; p < maxN; p++)
        if (maxExp[p])
            lcm = (lcm * binpow(p, maxExp[p])) % MOD;

    printf("%llu\n", lcm);
    return 0;
}