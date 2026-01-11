#include <stdio.h>
constexpr int MOD = 1e9+7;
int binpow(long long b, int exp) {
    long long r = 1;
    while(exp) {
        if(exp&1) r = (r*b)%MOD;
        b = (b * b)%MOD;  
        exp >>= 1;
    }
    return r;
}

int main() {
    int n;
    scanf("%d", &n);
    printf("%d\n", binpow(2, n));
    return 0;
}