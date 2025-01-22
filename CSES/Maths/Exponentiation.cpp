#include <stdio.h>

#define ll long long
constexpr int MOD = 1e9+7;

int binpow(ll b, int e) {
    int r = 1;
    while(e) {
        if(e&1) r = (r * b)%MOD;
        b = (b * b)%MOD;
        e >>= 1;
    }

    return r;
}

int main() {

    int t;
    scanf("%d", &t);

    int a, b;
    while(t--) {
        scanf("%d%d", &a, &b);
        printf("%d\n", binpow(a, b));
    }

    return 0;
}