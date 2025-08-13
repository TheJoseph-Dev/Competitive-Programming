#include <stdio.h>
constexpr int mtxN = 6, MOD = 1e9+7;
using ll = long long;

void multiply(int A[mtxN][mtxN], int B[mtxN][mtxN]) {
    int R[mtxN][mtxN] = {0};
    for (int i = 0; i < mtxN; i++)
        for (int j = 0; j < mtxN; j++)
            for (int k = 0; k < mtxN; k++)
                R[i][j] = (R[i][j] + (ll)A[i][k] * B[k][j]) % MOD;

    for (int i = 0; i < mtxN; i++)
        for (int j = 0; j < mtxN; j++)
            A[i][j] = R[i][j]; 
}

void mtxexp(int F[mtxN][mtxN], ll exp) {
    int R[mtxN][mtxN] = {0}, M[mtxN][mtxN];
    for (int i = 0; i < mtxN; i++) 
        R[i][i] = 1;

    for (int i = 0; i < mtxN; i++)
        for (int j = 0; j < mtxN; j++)
            M[i][j] = F[i][j];

    while (exp) {
        if (exp & 1) 
            multiply(R, M);
        multiply(M, M);
        exp >>= 1; 
    }

    for (int i = 0; i < mtxN; i++)
        for (int j = 0; j < mtxN; j++)
            F[i][j] = R[i][j];
}

int f(ll n) {
    // Base cases
    if (n == 0) return 1;
    if (n == 1) return 1;
    if (n == 2) return 2;
    if (n == 3) return 4;
    if (n == 4) return 8;
    if (n == 5) return 16;

    // Always remember: [Fn, Fn-1] = T * [Fn-1, Fn-2]
    int T[mtxN][mtxN] = {
        {1, 1, 1, 1, 1, 1},    // 16
        {1, 0, 0, 0, 0, 0},    // 8
        {0, 1, 0, 0, 0, 0},    // 4
        {0, 0, 1, 0, 0, 0},    // 2 
        {0, 0, 0, 1, 0, 0},    // 1
        {0, 0, 0, 0, 1, 0}     // 1
    };

    // Initial vector for F(5), F(4), F(3), F(2), F(1), F(0)
    int F[mtxN] = {16, 8, 4, 2, 1, 1};

    mtxexp(T, n - mtxN + 1);
    // F(N) is the first element of the resulting matrix multiplied by the initial vector F
    ll fn = 0;
    for (int i = 0; i < mtxN; i++)
        fn = (fn + (ll)T[0][i] * F[i]) % MOD;

    return fn;
}

int main() {
    ll n;
    scanf("%lld", &n);
    printf("%d\n", f(n));
    /*
        ll dp(ll n) {
            if(n < 0) return 0;
            if(n == 0) return 1;
            return dp(n-1) + dp(n-2) + dp(n-3) + dp(n-4) + dp(n-5) + dp(n-6);
        }
    */

    return 0;
}