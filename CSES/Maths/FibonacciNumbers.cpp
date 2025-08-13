#include <stdio.h>
constexpr int mtxM = 2, MOD = 1e9+7;
using ll = long long;

void multiply(ll F[mtxM][mtxM], ll M[mtxM][mtxM]) {
    ll R[mtxM][mtxM] = {0};
    for (int i = 0; i < mtxM; ++i)
        for (int j = 0; j < mtxM; ++j)
            for (int k = 0; k < mtxM; ++k)
                R[i][j] = (R[i][j] + F[i][k] * M[k][j])%MOD;

    for (int i = 0; i < mtxM; ++i)
        for (int j = 0; j < mtxM; ++j)
            F[i][j] = R[i][j];
}

void mtxexp(ll F[mtxM][mtxM], ll n) {
    if (n == 0 || n == 1) return;
    ll M[mtxM][mtxM], R[mtxM][mtxM] = { {1,0}, {0,1} };
    
    for (int i = 0; i < mtxM; ++i)
        for (int j = 0; j < mtxM; ++j)
            M[i][j] = F[i][j];

    while(n) {
        if (n&1) multiply(R, M);
        multiply(M, M);
        n >>= 1;
    }

    for(int i = 0; i < mtxM; i++)
        for(int j = 0; j < mtxM; j++)
            F[i][j] = R[i][j];
}

ll fib(ll n) {
    if (n == 0) return 0;
    ll F[mtxM][mtxM] = { { 1, 1 }, { 1, 0 } };
    mtxexp(F, n - 1);
 
    return F[0][0]%MOD;
}

int main() {
    ll n;
    scanf("%lld", &n);
    printf("%d\n", fib(n));
    return 0;
}