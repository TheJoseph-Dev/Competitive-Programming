#include <stdio.h>

// We will use fermat theorem for this. a^(p−1) ≡ 1 mod p
// So using the above, we will find b^c mod (p−1) and then a^(b^c) mod p, where p=1e9+7.

#define ll long long
constexpr int MOD = 1e9+7;

int binpow(ll b, int e, int M) {
    int r = 1;
    while(e) {
        if(e&1) r = (r * b)%M;
        b = (b * b)%M;
        e >>= 1;
    }

    return r;
}

int main() {

    int t;
    scanf("%d", &t);

    int a, b, c;
    while(t--) {
        scanf("%d%d%d", &a, &b, &c);
        printf("%d\n", binpow(a, binpow(b, c, MOD-1), MOD));
    }

    return 0;
}