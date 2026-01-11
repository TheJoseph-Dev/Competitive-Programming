#include <stdio.h>

using ll = long long;
constexpr int mtxN = 101, MOD = 1e9+7;
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

int T[mtxN][mtxN];
int main() {

    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);

    int a, b, c;
    while(m--) {
        scanf("%d%d%d", &a, &b, &c);
        T[a-1][b-1]++;
    }

    mtxexp(T, k);
    if(T[0][n-1]) printf("%d\n", T[0][n-1]); // Get min path
    else puts("-1");

    return 0;
}