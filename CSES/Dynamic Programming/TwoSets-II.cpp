#include <stdio.h>

#define MOD 1000000007

int dp[2][62626] = {{0}};

int gcdExtended(int a, int b, int *x, int *y) {
    if (a == 0) {
        *x = 0, *y = 1;
        return b;
    }
 
    int x1, y1; // To store results of recursive call
    int gcd = gcdExtended(b%a, a, &x1, &y1);

    *x = y1 - (b/a) * x1;
    *y = x1;
 
    return gcd;
}

int modInverse(int b, int m) {
    int x, y;
    int g = gcdExtended(b, m, &x, &y);
 
    if (g != 1) return -1;
 
    return (x%m + m) % m;
}
 
int modDivide(int a, int b, int m) {
    a = a % m;
    long long inv = modInverse(b, m);
    return (inv * a) % m;
}

/*
int countSets(int i, int s, int n) {
    if(4*s > (1+n)*n) return 0;
    if(i == n+1) return (4*s == (1+n)*n);
    if(dp[i][s] != -1) return dp[i][s];
    return dp[i][s] = ((countSets(i+1, s+i, n)%MOD) + (countSets(i+1, s, n)%MOD))%MOD;
}*/

int countSets(int n) {
    if(((1+n)*n) % 4 != 0) return 0;
    int k = ((1+n)*n)/4;
    dp[0][k] = 1;

    bool si = true;
    for(int i = n; i >= 1; i--) {
        for(int s = 0; s <= k; s++)
            dp[si][s] = (dp[!si][s] + (s+i <= k ? dp[!si][s+i] : 0))%MOD;
     
        si = !si;
    }

    return modDivide(dp[!si][0], 2, MOD);
}

int main() {

    int n;
    scanf("%d", &n);

    printf("%d\n", countSets(n));

    return 0;
}